// bidirectional list header

#ifndef _BLIST_H_INCLUDED_
#define _BLIST_H_INCLUDED_

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
	TYPE* (*array)( const struct bList *self );
	void (*array_free)( const struct bList *self, TYPE* array );
	TYPE* (*back)( const struct bList *self );
	void (*clear)( struct bList *self );
	void (*delete)( struct bList *self, const TYPE *data );
	int (*empty)( const struct bList *self );
	int (*erase)( struct bList *self, LENGTH_TYPE index );
	TYPE* (*front)( const struct bList *self );
	TYPE* (*get)( const struct bList *self, LENGTH_TYPE index );
	void (*init)( struct bList *self );
	void (*insert)( struct bList *self, LENGTH_TYPE index, const TYPE *data );
	void (*merge)( struct bList *self, const struct bList *src );
	void (*pop_back)( struct bList *self );
	void (*pop_front)( struct bList *self );
	void (*push_back)( struct bList *self, const TYPE *data );
	void (*push_front)( struct bList *self, const TYPE *data );
	void (*reverse)( struct bList *self );
	LENGTH_TYPE (*size)( const struct bList *self );
	void (*sort)( const struct bList *self );
	void (*unique)( struct bList *self );
}bList;

void bList_init( bList *self );

#endif
