 /** EXTRA CREDITS **/

 /*
 * This file is where you should implement your doubly-linked list.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function). Feel free to implement any additional
 * functions you might need. Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Kaushik Dontula
 * Email: dontulak@oregonstate.edu
 */

#include <stdlib.h>
#include <assert.h>
#include "db_list.h"

/*
 * This structure is used to represent a single node in a doubly-linked list.
 * It is not defined in db_list.h, so it is not visible to the user. You should not
 * modify this structure.
 */
struct db_node
{
    void* val;
    struct db_node* prev; // a pointer to the previous node
    struct db_node* next; // a pointer to the next node
};

/*
 * This structure is used to represent an entire doubly-linked list. Note that
 * we're keeping track of both the head and the tail of the list here.
 */
struct db_list
{
    struct db_node* head;
    struct db_node* tail;
};

/*
 * This function should allocate and initialize a new, empty doubly linked list and
 * return a pointer to it.
 *
 * Note: it is your choice to include sentinels or not
 */
struct db_list* db_list_create()
{
    //creates the new doubly linked list
    struct db_list* list = malloc(sizeof(struct db_list));

    //initializes the head and tail to NULL
    list->head = NULL;
    list->tail = NULL;

    //returns the list
    return list;
}

/*
 * This function should free the memory associated with a doubly-linked list. In
 * particular, while this function should up all memory used in the list
 * itself (i.e. the space allocated for all of the individual nodes), it should
 * not free any memory allocated to the pointer values stored in the list. In
 * other words, this function does not need to free the `val` fields of the
 * list's nodes.
 *
 * Params:
 * db_list - the doubly-linked list to be destroyed. May not be NULL.
 */
void db_list_free(struct db_list* db_list)
{
    //creates two temp nodes
    struct db_node* temp = NULL;
	struct db_node* current = db_list->head;

    //traverse through the list and free the nodes until the tail
	while(current != NULL){
		temp = current->next;
		free(current);
		current = temp;
	}

    //set head to NULL and free the list itself 
	db_list->head = NULL;
    free(db_list);

    return;
}

/*
 * This function should insert a new value into a given doubly-linked list.
 * Importantly, this function will need to allocate a new `struct db_node` in
 * which to store the new value and add that node at the head of the list. 
 * This function should only insert elements at the *beginning* of
 * the list. In other words, it should always insert the new element as the
 * head of the list.
 *
 * Params:
 * db_list - the doubly-linked list into which to insert an element. May not be NULL.
 * val - the value to be inserted. Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void db_list_insert(struct db_list* db_list, void* val)
{
    //create a temp dynamic node
    struct db_node* temp = malloc(sizeof(struct db_node));

    //initialize value, next, prev
    temp->val = val;
    temp->next = db_list->head;
    temp->prev = NULL;

    //if the list is not empty
    if(db_list->head != NULL ){
        //head prev = temp
        db_list->head->prev = temp;
    }
    //the head is now the new node
    db_list->head = temp;


    //if the list is empty
    if (db_list->head->next == NULL){
        //set the tail to the new node
        db_list->tail = temp;
    }
    
    return;
}

/*
 * This function should insert a new value into a given doubly-linked list.
 * Importantly, this function will need to allocate a new `struct db_node` in
 * which to store the new value and add that node at the tail of the list.  
 * This function should only insert elements at the *end* of
 * the list. In other words, it should always insert the new element as the
 * tail of the list.
 *
 * Params:
 * db_list - the doubly-linked list into which to insert an element.  May not be NULL.
 * val - the value to be inserted. Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void db_list_insert_end(struct db_list* db_list, void* val)
{

    //create new dynamic node
    struct db_node* temp = malloc(sizeof(struct db_node));

    //initialize the val, prev, and next
    temp->val = val;
    temp->prev = db_list->tail;
    temp->next = NULL;

    //if the list is not empty
    if(db_list->tail != NULL){

        //set tail->next to the new node
        db_list->tail->next = temp;
    }
    //set the tail to the new node
    db_list->tail = temp;

    //if the list is empty sead the head to the new node
    if (db_list->tail->prev == NULL){
        db_list->head = temp;
    }
    return;
}


/*
 * This function should remove the last element from a given doubly-linked list. 
 * If the list is empty, this function doesn't need to do anything.
 * Importantly, this function will also need to free the
 * memory held by the node being removed (it does not need to free the stored
 * value itself, just the node).

 * Params:
 * db_list - the doubly-linked list from which to remove an element. May not be NULL.

 */
void db_list_remove_end(struct db_list* db_list)
{
    //initialize node to the tail node
	struct db_node* temp = db_list->tail;

    //make the temp the prev
    temp = temp->prev;

    //free the temp->next AKA the last node and set it to NULL
    free(temp->next);
    temp->next = NULL;

    //initialize the tail as the new node
    db_list->tail = temp;
    return;
}


/*
 * This function should display/print all the elements of the given doubly-linked list 
 * from beginning to the end. 
 *
 * This function will be passed a *function pointer* called `p` that you
 * should use to print the value of `val` of each db_node.
 * 
 * For example, part of your code here might look something like this (assuming
 * you're printing the 'val' of a specific db_list node):
 * 
 * p(db_node->val)
 *
 * Params:
 * db_list - the doubly-linked list from which to display. May not be NULL.
 * cmp - pointer to a function that can be passed one void* value from
 *     to print it out, as described above.
 */
void db_list_display_forward(struct db_list* db_list, void (*p)(void* a))
{
    //initialize the new node as the head
	struct db_node *temp = db_list->head;

    //if the list is not empty
    if(temp != NULL){

        //traverse through the list until the tail
        while(temp != NULL){

            //print the val
            p(temp->val);
            temp = temp->next;

        }
    }
	return;
}

/*
 * This function should display/print all the elements of the given doubly-linked list 
 * from the end to the beginning. 
 *
 * This function will be passed a *function pointer* called `p` that you
 * should use to print the value of `val` of each db_node.
 * 
 * For example, part of your code here might look something like this (assuming
 * you're printing the 'val' of a specific db_list node):
 * 
 * p(db_node->val)
 *
 * Params:
 * db_list - the doubly-linked list from which to display. May not be NULL.
 * cmp - pointer to a function that can be passed one void* value from
 *     to print it out, as described above.
 */
void db_list_display_backward(struct db_list* db_list, void (*p)(void* a))
{
    //initialize new node as the tail
	struct db_node *temp = db_list->tail;

    //if the list is not empty
    if(temp != NULL){

        //traverse through the list until the tail
        while(temp != NULL){

            //print the list out
            p(temp->val);
            temp = temp->prev;
        }
    }

	return;
}

