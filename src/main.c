#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <libnetfilter_log/libnetfilter_log.h>

void ip_to_string(int ip, char *str)
{
	char ipstr[13] = {0}, tmpd, tmps[5];
	sprintf(ipstr, "%d.%d.%d.%d", ((unsigned char *) &ip)[0], ((unsigned char *) &ip)[1], ((unsigned char *) &ip)[2], ((unsigned char *) &ip)[3]);
	strcat(ipstr, tmps);
	printf("%s\n", ipstr);
}

int cb(struct nflog_g_handle *gh, struct nfgenmsg *nfmsg, struct nflog_data *nfd, void *data)
{
	char *str;
	int d = nflog_get_payload(nfd, &str);
	printf("CALLBACK\nPREFIX: %s\nPAYLOAD LENGTH: %d\nPAYLOAD: %s\n", nflog_get_prefix(nfd), d, str);
	struct iphdr *iph = (struct iphdr *) str;
	void *protoh = (uint32_t *) iph + iph->ihl;
	struct tcphdr *tcph = (struct tcphdr *)protoh;
	printf("SRC: %08x:%d\nDST: %08x:%d\n", iph->saddr, ntohs(tcph->source), iph->daddr, ntohs(tcph->dest));
	ip_to_string(iph->saddr, 0);
	ip_to_string(iph->daddr, 0);
	return 0;
}

int main()
{
	printf("--------------\ntest\n");

	struct nflog_handle *nh = nflog_open();
	if (nh == NULL) {
		perror("Error nflog_open()");
		exit(1);
	}

	int i = nflog_bind_pf(nh, PF_INET);
	if (i != 0) {
		perror("Error nflog_bind_pf()");
		exit(1);
	}

	struct nflog_g_handle *ngh = nflog_bind_group(nh, 2);
	if (ngh == NULL) {
		perror("Error nflog_bind_group()");
		exit(1);
	}

	if (nflog_set_mode(ngh, NFULNL_COPY_PACKET, 0xffff) < 0) {
			perror("Error nflog_set_mode()");
			exit(1);
	}

	nflog_callback_register(ngh, (nflog_callback*)cb, 0);
	
	int fd = nflog_fd(nh);
	int rv;

	char buf[1024];

	while ((rv = recv(fd, buf, sizeof(buf), 0)) && rv >= 0) {
		nflog_handle_packet(nh, buf, rv);
	}

	return 0;
}