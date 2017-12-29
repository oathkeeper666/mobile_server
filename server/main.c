#include "config.h"
#include "process.h"
#include "log.h"
#include "cycle.h"
#include "palloc.h"

static uint_t show_help;
static uint_t show_version;
static uint_t run_deamon;
static const char *signal_name;
static uint_t process_signal;
static const char *conf_path;

static uint_t process_options(int argc, const char *argv[]);
static void show_help_info();
static void show_version_info();
static logger * init_log(const char *filepath);

int main(int argc, const char *argv[])
{
	logger *log;
	srv_conf_t *conf;

	if (process_options(argc, argv) != RET_OK) {
		return 1;
	}
	if (show_help) {
		show_help_info();
		return 0;
	}
	if (show_version) {
		show_version_info();
		return 0;
	}		
	if (process_signal) {
		master_signal(signal_name);
		return 0;
	}
		
	if (run_deamon) {
		if (daemon_process() == RET_ERROR) {
			fprintf(stderr, "daemon_process failed.\n");
			return 1;
		}
	}	
	
	if (init_signals() == RET_ERROR) {
		fprintf(stderr, "init signal handler failed.\n");
		return 1;
	}

	conf = load_srv_cfg(conf_path);		
	if (NULL == conf) {
		fprintf(stderr, "load config failed.\n");
		return 1;
	}

	log = init_log(conf->log_path);	
	if (NULL == log) {
		fprintf(stderr, "init debug failed.\n");
		free_srv_config(conf);
		return 1;
	}		

	if (init_cycle(log) == RET_ERROR) {
		log_write(log, LOG_ERR, "init cycle failed.");
		log_close(log);
		free_srv_config(conf);
		return 1;
	}		
	set_conf(conf);	
	
	master_process_cycle();

	print_config(master_cycle->conf);

	destroy_cycle();
	
	memory_statistic();

	return 0;
}

static uint_t process_options(int argc, const char *argv[])
{	
	uint_t i;
	const char *p;

	for (i = 1; i < argc; i++) {
		p = argv[i];
		
		if (*p++ != '-') {
			fprintf(stderr, "invalid option: \"%s\"\n", argv[i]);
			return RET_ERROR;		
		}
		while (*p) {
			switch (*p++) {
				case '?':
				case 'h':
				case 'H':
					show_help = 1;
					break;			
				case 'v':
				case 'V':
					show_version = 1;
					break;
				case 's':
				case 'S':
					if (*p) {
						signal_name = p;				
					} else if (argv[++i]) {
						signal_name = argv[i]; 
					} else {
						fprintf(stderr, "option \"-s\" requires parameter\n");
						return RET_ERROR; 
					}

					if (strncmp(signal_name, "stop", FILENAME_LEN) == 0
						|| strncmp(signal_name, "quit", FILENAME_LEN) == 0 
						|| strncmp(signal_name, "reload", FILENAME_LEN) == 0
						|| strncmp(signal_name, "start", FILENAME_LEN) == 0) {
						process_signal = 1;
						goto next;
					}
					
					fprintf(stderr, "invalid option: \"-s %s\"\n", signal_name);
					return RET_ERROR;
				case 'd':
				case 'D':
					run_deamon = 1;
					break;	
				case 'c':
				case 'C':
					if (*p) {
						conf_path = p;
					} else if (argv[++i]) {
						conf_path = argv[i];	
					} else {
						fprintf(stderr, "option \"-c\" requires parameter\n");
						return RET_ERROR;
					}	
					
					goto next;
						
				default:
					fprintf(stderr, "invalid option: \"%c\"\n", *(p - 1));
					return RET_ERROR;	
			}	
		}
	next:
		continue;
	}

	return RET_OK;	
}

static void show_help_info()
{
	show_version_info();
	
	fprintf(stderr, 
		"Usage: ./server [-?hHvVdD] [-sS] signal \x0a"
		"Options: \x0a"
		"	-?, -h, -H: show help \x0a"
		"	-v, -v, -V: show version \x0a"
		"	-s, -S	  : send signal to master process \x0a"
		"	-d, -D	  : master process run in deamon way \x0a"
		"	-c, -C    : config file path \x0a");
}

static void show_version_info()
{
	fprintf(stderr, "version: %s\n", MOBILE_VERSION);
}

static logger * init_log(const char *filepath) 
{
	logger *log;	
	char file[256];

	sprintf(file, "%s/master", filepath);	
	log = log_open(file, LOG_DEBUG);
	if (NULL == log) {
		return NULL;
	}

	return log;
}
