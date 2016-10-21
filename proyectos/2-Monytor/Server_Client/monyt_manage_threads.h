#ifndef _MONYT_MANAGE_THREADS_
#define _MONYT_MANAGE_THREADS_

#include "monyt_socket.h"
#include <pthread.h>


/**
 * @brief Thread actions available
 *
 * This is use because we want to hide a variable
 * that is use as if it were global, we need some
 * actions to be perform on it
 */
typedef enum _thread_actions_ {
	Thread_INIT=0,
	Thread_GET,
	Thread_SET
} Thread_action;

/**
 * @brief Initialize the threads counter
 * @return 1 if success, 0 otherwise
 */
int init_thread_counter();

/**
 * @brief Get the value of a given thread
 * @param the number of the thread
 * @param the value of the thread
 * @return 1 if success, 0 otherwise
 */
char getValue_thread(uint thread, char *i_value);

/**
 * @brief Set the value of a given thread
 * @param the number of the thread
 * @return 1 if success, 0 otherwise
 */
int setValue_thread(uint thread, char value);

/**
 * @brief Search an available thread
 * @param the thread available
 * @return 1 if success, 0 otherwise
 */
char getAvailable_thread(uint *thread);

#endif /* _MONYT_MANAGE_THREADS_ */
