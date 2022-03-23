#ifndef CALLBACK_HEADER
#define CALLBACK_HEADER

#include <libnetfilter_log/libnetfilter_log.h>

int callback(struct nflog_g_handle *gh, struct nfgenmsg *nfmsg, struct nflog_data *nfd, void *data);
void s();
#endif