#include "config.h"
#include "process.h"
#include "log.h"

static uint_t show_help;
static uint_t show_version;
static uint_t run_deamon;
static const char *signal_name;
static uint_t process_signal;

static uint_t process_options(int argc, const char *argv[]);
static void show_help_info();
static void show_version_info();
static logger * init_debug();

int main(int argc, const char *argv[])
{
	logger *log;

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

	if (run_deamon) {
		if (daemon_process() == RET_ERROR) {
			fprintf(stderr, "daemon_process failed.");
			return 1;
		}
	}
	
	log = init_debug();	
	if (NULL == log) {
		fprintf(stderr, "init debug failed.\n");
		return 1;
	}		
		
	log_write(log, LOG_INFO, "hello server: %d", mobile_version);
	
	log_close(log);

	while (1);

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
					|| strncmp(signal_name, "reload", FILENAME_LEN) == 0) {
					process_signal = 1;
					goto next;
				}
				
				fprintf(stderr, "invalid option: \"-s %s\"\n", signal_name);
				return RET_ERROR;
			case 'd':
			case 'D':
				run_deamon = 1;
				break;			
	
			default:
				fprintf(stderr, "invalid option: \"%c\"\n", *(p - 1));
				return RET_ERROR;	
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
		"	-d, -D	  : master process run in deamon way \x0a");
}

static void show_version_info()
{
	fprintf(stderr, "version: %s\n", MOBILE_VERSION);
}

static logger * init_debug() 
{
	logger *log;	
	
	log = log_open("../log/master", LOG_DEBUG);
	if (NULL == log) {
		return NULL;
	}

	return log;
}
