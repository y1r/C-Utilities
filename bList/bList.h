#ifndef _INCLUDED_BLIST_H_
#define _INCLUDED_BLIST_H_
#define TYPE int
#define LENGTH_TYPE unsigned long long

typedef struct bListNode{
	struct bListNode *prev;
	TYPE data;
	struct bListNode *next;
}bListNode;

typedef struct bList{
	struct bListNode *begin;
	struct bListNode *end;
	LENGTH_TYPE length;
	TYPE* (*back)( struct bList *self );
	void (*clear)( struct bList *self );
	void (*delete)( struct bList *self, TYPE *data );
	int (*empty)( struct bList *self );
	int (*erase)( struct bList *self, LENGTH_TYPE index );
	TYPE* (*front)( struct bList *self );
	TYPE* (*get)( struct bList *self, LENGTH_TYPE index );
	void (*init)( struct bList *self );
	void (*insert)( struct bList *self, LENGTH_TYPE index, TYPE *data );
	void (*pop_back)( struct bList *self );
	void (*pop_front)( struct bList *self );
	void (*push_back)( struct bList *self, TYPE *data );
	void (*push_front)( struct bList *self, TYPE *data );
//	void (*remove)( struct bList *self, TYPE *data );
	void (*reverse)( struct bList *self );
	void (*set)( struct bList *self, LENGTH_TYPE index, TYPE *data );
	LENGTH_TYPE (*size)( struct bList *self );
	void (*sort)( struct bList *self );
	void (*unique)( struct bList *self );
}bList;

void bList_init( bList *self );

#endif
