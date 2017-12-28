#ifndef _MASTER_CYCLE_H
#define _MASTER_CYCLE_H

#include "core.h"
#include "log.h"
#include "config.h"

typedef struct cycle_t {
	logger 		*log;
	pid_t 		pid;
	int_t 		pid_fd;
	time_t  	cur_time;
	srv_conf_t 	*conf;
} cycle_t;

extern cycle_t *master_cycle;

typedef struct worker_cycle_t {
	logger *log;
} worker_cycle_t;

int_t init_cycle(logger *log);

void set_conf(srv_conf_t *c);

void destroy_cycle();

void master_process_cycle();

//void worker_process_cycle();

#endif /* _MASTER_CYCLE_H */
