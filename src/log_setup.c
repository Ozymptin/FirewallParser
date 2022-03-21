#include <stdio.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <libnetfilter_log/libnetfilter_log.h>

#include "callback.h"

static struct nflog_handle *nfh;
static struct nflog_g_handle *ngh;

void log_init()
{
	if ((nfh = nflog_open()) == NULL) {
		perror("Error nflog_open()");
		exit(1);
	}

	if (nflog_bind_pf(nfh, PF_INET) != 0) {
		perror("Error nflog_bind_pf()");
		exit(1);
	}

	if ((ngh = nflog_bind_group(nfh, 2)) == NULL) {
		perror("Error nflog_bind_group()");
		exit(1);
	}

	if (nflog_set_mode(ngh, NFULNL_COPY_PACKET, 0xffff) < 0) {
			perror("Error nflog_set_mode()");
			exit(1);
	}

	nflog_callback_register(ngh, (nflog_callback *) callback, 0);
}

void log_uninit()
{
	nflog_unbind_group(ngh);
	nflog_unbind_pf(nfh, PF_INET);
	nflog_close(nfh);
}

void log_handle()
{
	char buf[1024];
	int fd = nflog_fd(nfh);
	int rv;

	while ((rv = recv(fd, buf, sizeof(buf), 0)) && rv >= 0) {
		nflog_handle_packet(nfh, buf, rv);
	}
}