#ifndef _PROCESS_H
#define _PROCESS_H

#include "core.h"

int_t daemon_process();

pid_t spawn_process(const char * filepath);

int_t init_signals();

extern uint_t reload_flag;
extern uint_t quit_flag;
extern uint_t stop_flag;

#endif /* _PROCESS_H */

