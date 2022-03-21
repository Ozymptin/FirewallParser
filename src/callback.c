#include <stdio.h>
#include <stdint.h>

#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <libnetfilter_log/libnetfilter_log.h>

#include "callback.h"

int callback(struct nflog_g_handle *gh, struct nfgenmsg *nfmsg, struct nflog_data *nfd, void *data)
{
	return 0;
}