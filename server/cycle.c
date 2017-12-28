#include "cycle.h"
#include "palloc.h"
#include "queue.h"
#include "files.h"
#include "log.h"
#include "process.h"

cycle_t *master_cycle;
//static queue_t *worker_cycle_queue;

//static void start_worker_process();
//static void worker_process_exit();

int_t init_cycle(logger *log)
{
	if (NULL == log) {
		return RET_ERROR;
	}

	if (NULL == master_cycle) {
		master_cycle = (cycle_t *)MALLOC(sizeof(cycle_t));
	}
	memset(master_cycle, 0, sizeof(cycle_t));
	master_cycle->log = log;
	master_cycle->pid = getpid();
	if (master_cycle->pid == INVALID_PID) {
		log_write(log, LOG_ERR, "%s: get pid failed.", __FUNCTION__);
		return RET_ERROR;
	}	
	master_cycle->pid_fd = create_pid_file(master_cycle->pid);
	if (master_cycle->pid_fd == INVALID_FD) {
		log_write(log, LOG_ERR, "%s: create pid file failed.", __FUNCTION__);
		return RET_ERROR;
	}

	return RET_OK;
}

void set_conf(srv_conf_t *c)
{
	if (master_cycle) {
		master_cycle->conf = c;
	}
}

void destroy_cycle()
{
	if (master_cycle) {
		if (master_cycle->log) {
			log_close(master_cycle->log);
			master_cycle->log = NULL;
		}
		if (master_cycle->pid_fd != INVALID_FD) {
			close(master_cycle->pid_fd);	
		}
		if (master_cycle->conf) {	
			free_srv_config(master_cycle->conf);
		}	

		FREE(master_cycle);
		master_cycle = NULL;
	}
}

void master_process_cycle()
{
	//sigset_t set;
	//sigemptyset(&set);

	if (master_cycle == NULL) {
		return;
	}

	for ( ;; ) {
		if (quit_flag || stop_flag) {
			log_write(master_cycle->log, LOG_DEBUG, "%s: master process exit.", __FUNCTION__);	
			break;
		}
		log_write(master_cycle->log, LOG_DEBUG, "%s: master running ...", __FUNCTION__);
		sleep(1);	
	}
}

/*void worker_process_cycle()
{
	for ( ;; ) {

	}
}

static void start_worker_process()
{
	
}

static void worker_process_exit()
{

}*/
