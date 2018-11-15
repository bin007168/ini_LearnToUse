/*
 *  list.cpp
 *
 *  General list structure
 *
 *  Author:  IAN
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#include "list.h"
#include <stdio.h>

#define LIST_POISON1  NULL
#define LIST_POISON2  NULL

void INIT_LIST_HEAD(List *list)
{
	list->next = list;
	list->prev = list;
}

/*
 * Insert a node entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */

void __list_add(List *node,
			      List *prev,
			      List *next)
{
	next->prev = node;
	node->next = next;
	node->prev = prev;
	prev->next = node;
}


/**
 * list_add - add a node entry
 * @node: node entry to be added
 * @head: list head to add it after
 *
 * Insert a node entry after the specified head.
 * This is good for implementing stacks.
 */

void list_add(List *node, List *head)
{
	__list_add(node, head, head->next);
}



/**
 * list_add_tail - add a node entry
 * @node: node entry to be added
 * @head: list head to add it before
 *
 * Insert a node entry before the specified head.
 * This is useful for implementing queues.
 */
void list_add_tail(List *node, List *head)
{
	__list_add(node, head->prev, head);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
void __list_del(List * prev, List * next)
{
	next->prev = prev;
	prev->next = next;
}

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */
void list_del(List *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
}

/**
 * list_replace - replace old entry by node one
 * @old : the element to be replaced
 * @node : the node element to insert
 *
 * If @old was empty, it will be overwritten.
 */
void list_replace(List *old,
				List *node)
{
	node->next = old->next;
	node->next->prev = node;
	node->prev = old->prev;
	node->prev->next = node;
}

void list_replace_init(List *old,
					List *node)
{
	list_replace(old, node);
	INIT_LIST_HEAD(old);
}


/**
 * list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */
void list_del_init(List *entry)
{
	__list_del(entry->prev, entry->next);
	INIT_LIST_HEAD(entry);
}

/**
 * list_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 */
void list_move(List *list, List *head)
{
	__list_del(list->prev, list->next);
	list_add(list, head);
}

/**
 * list_move_tail - delete from one list and add as another's tail
 * @list: the entry to move
 * @head: the head that will follow our entry
 */
void list_move_tail(List *list,
				  List *head)
{
	__list_del(list->prev, list->next);
	list_add_tail(list, head);
}

/**
 * list_is_last - tests whether @list is the last entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
int list_is_last(const List *list,
				const List *head)
{
	return list->next == head;
}

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
int list_empty(const List *head)
{
	return head->next == head;
}

/**
 * list_empty_careful - tests whether a list is empty and not being modified
 * @head: the list to test
 *
 * Description:
 * tests whether a list is empty _and_ checks that no other CPU might be
 * in the process of modifying either member (next or prev)
 *
 * NOTE: using list_empty_careful() without synchronization
 * can only be safe if the only activity that can happen
 * to the list entry is list_del_init(). Eg. it cannot be used
 * if another CPU could re-list_add() it.
 */
int list_empty_careful(const List *head)
{
	List *next = head->next;
	return (next == head) && (next == head->prev);
}

void __list_splice(List *list,
				 List *head)
{
	List *first = list->next;
	List *last = list->prev;
	List *at = head->next;

	first->prev = head;
	head->next = first;

	last->next = at;
	at->prev = last;
}

/**
 * list_splice - join two lists
 * @list: the node list to add.
 * @head: the place to add it in the first list.
 */
void list_splice(List *list, List *head)
{
	if (!list_empty(list))
		__list_splice(list, head);
}

/**
 * list_splice_init - join two lists and reinitialise the emptied list.
 * @list: the node list to add.
 * @head: the place to add it in the first list.
 *
 * The list at @list is reinitialised
 */
void list_splice_init(List *list,
				    List *head)
{
	if (!list_empty(list)) {
		__list_splice(list, head);
		INIT_LIST_HEAD(list);
	}
}

