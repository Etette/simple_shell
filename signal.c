#include "shell.h"

/**
 * signal_handler - handles the ctrl-c signal
 * @signo: signal recieved
 */

void signal_handler(int signo)
{
	(vod) signo;
	_write("\n");
	print_cmdline();
}
