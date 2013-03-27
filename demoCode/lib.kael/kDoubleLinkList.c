//
//  kDoubleLinkList.c
//
//  Created by kael on 12/17/12.
//
//

#include "kDoubleLinkList.h"

kDoubleLinkList* dlist_create()
{
    // make 1 kDoubleLinkList
    return calloc(1, sizeof(kDoubleLinkList));
}

void dlist_destory(kDoubleLinkList* list)
{
    DLIST_FOREACH(list, first, next, cur){
        if(cur->prev){
            free(cur->prev);
        }
    }
    free(list->last);
    free(list);
}

void dlist_clear(kDoubleLinkList* list)
{
    DLIST_FOREACH(list, first, next, cur){
        if(cur->value)
        {
            free(cur->value);// delete maybe
        }
    }
}

void dlist_clear_destroy(kDoubleLinkList *list)
{
    dlist_clear(list);
    dlist_destory(list);
}

void dlist_push(kDoubleLinkList *list, void *value)
{
    kDoubleLinkNode *node = calloc(1, sizeof(kDoubleLinkNode));
    node->value = value;
    if (list->last == NULL) {
        list->first = node;
        list->last  = node;
    }
    else
    {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }
    list->count++;
}

void* dlist_pop(kDoubleLinkList* list)
{
    kDoubleLinkNode *node = list->last;
    return (node != NULL)?dlist_remove(list,node):NULL;
}

// shift is from behind
void dlist_unshift(kDoubleLinkList* list,void* value)
{
    kDoubleLinkNode* node = calloc(1, sizeof(kDoubleLinkNode));
    if(list->first == NULL)
    {
        list->first = node;
        list->last = node;
    }else{
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }
    list->count++;
}

void* dlist_shift(kDoubleLinkList* list)
{
    kDoubleLinkNode* node = list->first;
    return (node != NULL)?dlist_remove(list, node):NULL;
}

void* dlist_remove(kDoubleLinkList *list, kDoubleLinkNode *node)
{
    void *result = NULL;
    if(node == NULL || list == NULL)
        return result;
    // empty list
    if(list->first == NULL || list->last == NULL)
        return result;
    // one
    if (node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    }
    else if(node == list->first)
    {
        list->first = node->next;
        if(list->first == NULL)
            return  result;
        list->first->prev = NULL;
    }
    else if(node == list->last){
        list->last = node->next;
        if(list->last == NULL)
            return  result;
        list->last->next = NULL;
    }
    else{
        kDoubleLinkNode* prev = node->prev;
        kDoubleLinkNode* next = node->next;
        prev->next = next;
        next->prev = prev;
    }
    
    list->count--;
    result = node->value;
    free(node);
    return result;
}