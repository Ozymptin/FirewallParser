#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "log_setup.h"

void int_handler(int sig)
{
	log_uninit();
	exit(0);
}

int main()
{
	signal(SIGINT, int_handler);

	printf("--------------\ntest\n");

	log_init();
	log_handle();
	log_uninit();

	return 0;
}