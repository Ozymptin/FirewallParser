#include <stdlib.h>
#include <stdint.h>

#include "linkedlist.h"

#include <stdio.h>

struct list_node *list_add(struct list_node **head, uint32_t size)
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

	*head = ptr;
	return ptr;
}

void list_remove(struct list_node *node)
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
	struct port_info *ptr = ip->port;
	if (ptr == NULL) {
		ptr = malloc(sizeof());
		ptr->next = NULL;

		*head = ptr;
		return ptr;
	}

	for(; ptr->next != NULL; ptr = ptr->next);

	ptr->next = malloc(size);
	ptr->next->next = NULL;

	*head = ptr;
	return ptr;

	struct port_info *p = NULL;
	for (struct port_info *ptr = ip->port; ptr != NULL; ptr = ptr->next) {
		if (ptr->port == port) {
			p = ptr;
		}
	}

	if (p == NULL) {
		p = (struct port_info *) list_add((struct list_node **) &ip->port, sizeof(struct port_info));
		p->port = port;
		p->count = 0;
		printf("new port\n");
	}

	p->count += 1;
}