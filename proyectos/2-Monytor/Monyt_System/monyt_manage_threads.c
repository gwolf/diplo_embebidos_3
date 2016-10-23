
#include "monyt_manage_threads.h"

/** Function to manage the static variable thread counter */
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

/** Initialize the threads counter */
int init_thread_counter() {
	return thread_counter(Thread_INIT, 0, 0, NULL);
}

/** Get the value of a given thread */
char getValue_thread(uint thread, char *i_value) {
	return thread_counter(Thread_GET, thread, 0, i_value);
}

/** Set the value of a given thread */
int setValue_thread(uint thread, char value) {
	return thread_counter(Thread_SET, thread, value, NULL);
}

/** Search an available thread */
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

