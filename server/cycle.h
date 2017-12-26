#ifndef _MASTER_CYCLE_H
#define _MASTER_CYCLE_H

#include "core.h"
#include "log.h"

typedef struct cycle_t {
	logger 	*log;
	pid_t 	pid;
	int_t 	pid_fd;
} cycle_t;

typedef struct worker_cycle_t {
	logger *log;
} worker_cycle_t;

int_t init_cycle(logger *log);

void destroy_cycle();

void master_process_cycle();

//void worker_process_cycle();

#endif /* _MASTER_CYCLE_H */
