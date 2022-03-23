#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER

struct list_node {
	struct list_node *next;
};

struct port_info {
	struct port_info *next;
	uint16_t port;
	uint32_t count;
};

struct ip_endpoint {
	struct ip_endpoint *next;
	uint32_t ip;
	struct port_info *port;
};

struct ip_endpoint *ip_add(struct ip_endpoint **head, uint32_t ip);
struct ip_endpoint *ip_remove(struct ip_endpoint **head, uint32_t ip);
struct ip_endpoint *ip_find_by_ip(struct ip_endpoint *head, uint32_t ip);

void port_add(struct ip_endpoint *ip, uint16_t port);
void port_remove(struct ip_endpoint *ip, uint16_t port);

#endif