#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <libnetfilter_log/libnetfilter_log.h>

#include "callback.h"
#include "linked_list.h"

struct ip_endpoint *list = NULL;

static void print()
{
	for(struct ip_endpoint *ptr = list; ptr != NULL; ptr = ptr->next) {
		printf("IP: 0x%08x\n", ptr->ip);
		for (struct port_info *p = ptr->port; p != NULL; p = p->next) {
			printf("\t%d:%d\n", htons(p->port), p->count);
		}
	}
	printf("-----------------\n");
}

int callback(struct nflog_g_handle *gh, struct nfgenmsg *nfmsg, struct nflog_data *nfd, void *data)
{
	char *payload;
	int len = nflog_get_payload(nfd, &payload);

	struct iphdr *ip = (struct iphdr *) payload;
	void *protoh = (uint32_t *) ip + ip->ihl;
	struct tcphdr *tcph = (struct tcphdr *) protoh;

	port_add(ip_add(&list, ip->saddr), tcph->dest);

	print();

	return 0;
}