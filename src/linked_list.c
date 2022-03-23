#include <stdlib.h>
#include <stdint.h>

#include "linked_list.h"

static struct list_node *list_add(struct list_node **head, uint32_t size)
{
	struct list_node *ptr = *head;
	if (ptr == NULL) {
		ptr = malloc(size);
		ptr->next = NULL;

		*head = ptr;
		return ptr;
	}

	for(; ptr->next != NULL; ptr = ptr->next);
	ptr->next = malloc(size);
	ptr->next->next = NULL;

	return ptr->next;
}

static void list_remove(struct list_node *node)
{

}

struct ip_endpoint *ip_add(struct ip_endpoint **head, uint32_t ip)
{
	for (struct ip_endpoint *ptr = *head; ptr != NULL; ptr = ptr->next) {
		if (ptr->ip == ip) {
			return ptr;
		}
	}

	struct ip_endpoint *new = (struct ip_endpoint *) list_add((struct list_node **) head, sizeof(struct ip_endpoint));
	new->ip = ip;
	new->port = NULL;

	return new;
}

struct ip_endpoint *ip_find_by_ip(struct ip_endpoint *head, uint32_t ip)
{
	for (struct ip_endpoint *ptr = head; ptr != NULL; ptr = ptr->next) {
		if (ptr->ip == ip) {
			return ptr;
		}
	}

	return NULL;
}

void port_add(struct ip_endpoint *ip, uint16_t port)
{
	for (struct port_info *ptr = ip->port; ptr != NULL; ptr = ptr->next) {
		if (ptr->port == port) {
			ptr->count++;
			return;
		}
	}

	struct port_info *new = (struct port_info *) list_add((struct list_node **) &ip->port, sizeof(struct port_info));
	new->port = port;
	new->count = 1;
}