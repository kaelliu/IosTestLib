//
//  kDoubleLinkList.h
//
//  Created by kael on 12/17/12.
//
//

#ifndef _kDoubleLinkList_h
#define _kDoubleLinkList_h
#include <stdlib.h>
struct kDoubleLinkNode;
typedef struct kDoubleLinkNode
{
    struct kDoubleLinkNode *next;
    struct kDoubleLinkNode *prev;
    void *value;
}kDoubleLinkNode;

typedef struct kDoubleLinkList
{
    int count;
    kDoubleLinkNode *first;
    kDoubleLinkNode *last;
}kDoubleLinkList;

kDoubleLinkList* dlink_create();
void dlist_destory(kDoubleLinkList* list);
void dlist_clear(kDoubleLinkList* list);
void dlist_clear_and_destory(kDoubleLinkList* list);

#define DLIST_COUNT(L) ((L)->count)
#define DLIST_FIRST(L) ((L)->first != NULL ? (L)->first->value : NULL)
#define DLIST_LAST(L) ((L)->last != NULL ? (L)->last->value : NULL)

void dlist_push(kDoubleLinkList *list, void *value);
void *dlist_pop(kDoubleLinkList *list);

void dlist_unshift(kDoubleLinkList *list,void* value);
void* dlist_shift(kDoubleLinkList *list);
void* dlist_remove(kDoubleLinkList* list,kDoubleLinkNode* node);

// marco for iterator contents in dlist,value you can used after call this marco
#define DLIST_FOREACH(LIST,FIRST,NEXT,VALUE) kDoubleLinkNode *_node = NULL; \
        kDoubleLinkNode *VALUE = NULL; \
        for(VALUE = _node = LIST->FIRST;_node != NULL;VALUE = _node = _node->NEXT)
#endif
