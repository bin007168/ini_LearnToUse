/*
 *  list.h
 *
 *  General list structure
 *
 *  Author:  IAN
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#ifndef _LIST_HEADER
#define _LIST_HEADER

/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */

typedef struct tagList {
	struct tagList *next, *prev;
}List, *pList;

#ifdef __cplusplus
extern "C" {
#endif

void INIT_LIST_HEAD(List *list);

void list_add(List *node, List *head);
void list_add_tail(List *node, List *head);

void list_move(List *list, List *head);
void list_move_tail(List *list,List *head);

int list_is_last(const List *list,const List *head);

int list_empty(const List *head);
int list_empty_careful(const List *head);

void list_splice(List *list, List *head);
void list_splice_init(List *list,List *head);

void list_del(List *entry);
void list_del_init(List *entry);

void list_replace(List *old,List *node);
void list_replace_init(List *old,List *node);

#ifdef __cplusplus
}
#endif

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	List name = LIST_HEAD_INIT(name)

#define offsetof2(TYPE, MEMBER) (size_t)( &((TYPE *)0)->MEMBER)

/**
* container_of - cast a member of a structure out to the containing structure
* @ptr:     the pointer to the member.
* @type:     the type of the container struct this is embedded in.
* @member:     the name of the member within the struct.
*
*/
/*
#define container_of(ptr, type, member) \
	{const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
         (type *)( (char *)__mptr - offsetof(type,member) );}
*/
/*
#define container_of(ptr, type, member) \
	((char *)__mptr = (char *)(ptr),   \
         (type *)( (char *)__mptr - offsetof(type,member) ))
*/

#define container_of(ptr, type, member) \
	( (type *)( (char *)ptr - offsetof2(type,member) ))

/**
 * list_entry - get the struct for this entry
 * @ptr:	the &List pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member) container_of(ptr, type, member)

/**
 * list_first_entry - get the first element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_first_entry(ptr, type, member)	list_entry((ptr)->next, type, member)

/**
 * list_for_each	-	iterate over a list
 * @pos:	the &List to use as a loop cursor.
 * @head:	the head for your list.
 */
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); \
        	pos = pos->next)

/**
 * list_for_each_prev	-	iterate over a list backwards
 * @pos:	the &List to use as a loop cursor.
 * @head:	the head for your list.
 */
#define list_for_each_prev(pos, head) \
	for (pos = (head)->prev; pos != (head); \
        	pos = pos->prev)

/**
 * list_for_each_safe - iterate over a list safe against removal of list entry
 * @pos:	the &List to use as a loop cursor.
 * @n:		another &List to use as temporary storage
 * @head:	the head for your list.
 */
#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

#endif
