
#include "monyt_manage_threads.h"

/**
 * @brief Function to manage the static variable thread counter
 * @param The action to be done
 * @param The number of the thread, must be between 0 and LIMIT_CONNECTIONS
 * @param In case of a SET action this is the value to be set
 * @param In case of a GET action this is the value returned
 * @return 1 if success, 0 otherwise
 */
static int thread_counter(Thread_action i_action, uint i_thread, char i_value, char *o_value)
{
	static char l_threads[LIMIT_CONNECTIONS];

	switch(i_action)
	{
		case Thread_INIT:
			/** clean threads counter */
			if (memset(l_threads, 0, sizeof(char)*LIMIT_CONNECTIONS))
				return 1;
			break;
		case Thread_SET:
			if (i_thread >= 0 && i_thread < LIMIT_CONNECTIONS) {
				l_threads[i_thread] = (i_value) ? 1: 0;
				return 1;
			}
			break;
		case Thread_GET:
			if (i_thread >= 0 && i_thread < LIMIT_CONNECTIONS) {
				*o_value = l_threads[i_thread];
				return 1;
			}
			break;
	}
	return 0;
}

/**
 * @brief Initialize the threads counter
 * @return 1 if success, 0 otherwise
 */
int init_thread_counter() {
	return thread_counter(Thread_INIT, 0, 0, NULL);
}

/**
 * @brief Get the value of a given thread
 * @param the number of the thread
 * @param the value of the thread
 * @return 1 if success, 0 otherwise
 */
char getValue_thread(uint thread, char *i_value) {
	return thread_counter(Thread_GET, thread, 0, i_value);
}

/**
 * @brief Set the value of a given thread
 * @param the number of the thread
 * @return 1 if success, 0 otherwise
 */
int setValue_thread(uint thread, char value) {
	return thread_counter(Thread_SET, thread, value, NULL);
}

/**
 * @brief Set the value of a given thread
 * @param the thread available
 * @return the thread value
 */
char getAvailable_thread(uint *thread) {
	uint i = LIMIT_CONNECTIONS;
	char l_value;
	while(i--) {
		if(getValue_thread(i, &l_value)) {
			if(!l_value) {
				*thread = i;
				return 1;
			}
		}
	}
	return 0;
}

