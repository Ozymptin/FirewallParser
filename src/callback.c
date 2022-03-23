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
			printf("\t%d:%d\n", (p->port), p->count);
		}
	}
}

int callback(struct nflog_g_handle *gh, struct nfgenmsg *nfmsg, struct nflog_data *nfd, void *data)
{
	char *payload;
	int len = nflog_get_payload(nfd, &payload);

	struct iphdr *iph = (struct iphdr *) payload;
	void *protoh = (uint32_t *) iph + iph->ihl;
	struct tcphdr *tcph = (struct tcphdr *) protoh;

	port_add(ip_add(&list, iph->saddr), tcph->dest);

	print();

	return 0;
}

void s()
{
	struct ip_endpoint *i = ip_add(&list, 0xDEADBEEF);
	port_add(i, 1234);
	port_add(i, 5678);
	port_add(i, 3456);
	port_add(i, 3456);
	port_add(i, 3456);

	i = ip_add(&list, 0xAAAAAAAA);
	port_add(i, 1234);
	port_add(i, 5678);
	port_add(i, 3456);
	port_add(i, 3456);
	port_add(i, 3456);
	print();
}