#include "shell.h"

/**
 * _free - frees memory and removes address from defered free list
 * @address: address to free
 */

void _free(void *address)
{
	defer_free(address);
	free(address);
}

/**
 * defer_free - sets address to be free'd on exit
 * and removes from list if exits
 * @address: address to be set
 */
void defer_free(void *address)
{
	static addr_list list = {NULL, NULL};
	addr_list *tmp;

	tmp = &list;
	/* if not given signal to free all and address not already in list, add it*/
	if (address != FREE_ADDRESSES && clear_addr_list_node(tmp, address))
	{
		while (1)
		{
			if (tmp->address == NULL)
			{
				tmp->address = address;
				return;
			}
			else if (tmp->next == NULL)
			{
				add_addr_list_node(tmp, address);
				return;
			}
			tmp = tmp->next;
		}
	}
	else if (address == FREE_ADDRESSES)
	{
		free_addr_list(list.next);
		if (list.address != NULL)
			free(list.address);
	}
}


/**
 * clear_addr_list_node - clear an address from the list
 * @list: addr_list list
 * @address: address to search and clear
 * Return: 0 if address found else 1
 */
int clear_addr_list_node(addr_list *list, void *address)
{
	while (list != NULL)
	{
		if (list->address == address)
		{
			list->address = NULL;
			return (0);
		}
		list = list->next;
	}
	return (1);
}

/**
 * add_addr_list_node - add a node to the addr_list list
 * @list: addr_list list
 * @address: addresss to add to node
 */
void add_addr_list_node(addr_list *list, void *address)
{
	addr_list *node;

	node = malloc(sizeof(addr_list));
	if (node == NULL)
	{
		_write("Out of Memory, Exiting (._.)\n");
		defer_free(FREE_ADDRESSES);
		_exit(4);
	}
	node->address = address;
	node->next = list->next;
	list->next = node;
}

/**
 * free_addr_list - free the addr-list and all addresses stored
 * @list: addr_list tto free
 */
void free_addr_list(addr_list *list)
{
	addr_list *tmp;

	while (list != NULL)
	{
		tmp = list;
		list = list->next;
		if (tmp->address != NULL)
			free(tmp->address);
		free(tmp);
	}
}
