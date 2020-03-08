/*
 * N0006_Signal_ipc.h
 *
 *  Created on: 8 мар. 2020 г.
 *      Author: safronoff2006
 */

#ifndef N0006_SIGNAL_IPC_H_
#define N0006_SIGNAL_IPC_H_

#include <stdlib.h>

void sig_func(int);
void start_signalset();
void message_for_parents(pid_t);
void wait_for_parents();
void message_for_child(pid_t);
void wait_for_child(void) ;

#endif /* N0006_SIGNAL_IPC_H_ */
