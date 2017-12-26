#include "process.h"
#include "files.h"

uint_t reload_flag;
uint_t quit_flag;
uint_t stop_flag;

static void signal_handler(int signo, siginfo_t *info, void *ctx);

typedef struct signal_t {
	int 	signo;
	char 	*signame;
	void 	(*handler)(int signo, siginfo_t *info, void *ctx);
} signal_t;

static signal_t signals[] = {
	{
		SIGHUP,
		"reload",
		signal_handler
	},
	{	SIGQUIT,
		"quit",
		signal_handler 
	},
	{
		SIGTERM,
		"stop",
		signal_handler
	},
	{
		SIGINT,
		"stop",
		signal_handler
	},
	{ 0, NULL, NULL }
};

pid_t spawn_process(const char * filepath)
{
	return 0;	
}

int_t init_signals()
{
	signal_t *sig;;
	struct sigaction sa;

	for (sig = signals; sig->signo != 0; sig++) {
		memset(&sa, 0, sizeof(sigaction));
		if (sig->handler) {
			sa.sa_sigaction = sig->handler;
			sa.sa_flags = SA_SIGINFO;
		}
		else {
			sa.sa_handler = SIG_IGN;
		}
		sigemptyset(&sa.sa_mask);
		if (sigaction(sig->signo, &sa, NULL) == -1) {
			return RET_ERROR;
		}
	}

	return RET_OK;
}

int_t daemon_process()
{
	pid_t pid;
	int fd;

	pid = fork();	
	if (-1 == pid) {	
		fprintf(stderr, "%s: fork faild.\n", __FUNCTION__);
		return RET_ERROR;
	}
	else if (pid > 0) {
		exit(0);
	}
	
	if (setsid() == -1) {
		fprintf(stderr, "%s: setsid() failed.\n", __FUNCTION__);
		return RET_ERROR;
	}
	
	fd = open("/dev/null", O_RDWR);
	if (fd == -1) {
		fprintf(stderr, "%s: open \"/dev/null\" failed.\n", __FUNCTION__);
		return RET_ERROR;
	}
	if (dup2(fd, STDOUT_FILENO) == -1) {
		fprintf(stderr, "%s: dup2(STDOUT) failed.\n", __FUNCTION__);
		return RET_ERROR;
	}
	if (dup2(fd, STDIN_FILENO) == -1) {
		fprintf(stderr, "%s: dup2(STDIN) failed.\n", __FUNCTION__);
		return RET_ERROR;
	}
	/*if (dup2(fd, STDERR_FILENO) == -1) {
		fprintf(stderr, "%s: dup2(STDERR) failed.\n", __FUNCTION__);
		return RET_ERROR;
	}*/

	return RET_OK;	
}

int_t send_signal(pid_t pid, int signo)
{
	if (kill(pid, signo) == -1) {
		return RET_ERROR;
	}	
	
	return RET_OK;	
}

int_t master_signal(const char * name)
{
	int i;
	pid_t pid;

	pid = master_pid();
	
	for (i = 0; signals[i].signo != 0; ++i) {
		if (strncmp(signals[i].signame, name, FILENAME_LEN) == 0) {					
			return send_signal(pid, signals[i].signo);
		}
	}
	
	return RET_ERROR;
}

static void signal_handler(int signo, siginfo_t *info, void *ctx)
{
	switch (signo) {
		case SIGHUP:
			reload_flag = 1;
			break;		
		case SIGQUIT:
			quit_flag = 1;
			break;			
		case SIGTERM:
		case SIGINT:
			stop_flag = 1;
			break;
	}	
}
