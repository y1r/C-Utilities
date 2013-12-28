#ifndef _BLIST_H_INCLUDED_
#define _BLIST_H_INCLUDED_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TYPE int
#define LENGTH_TYPE unsigned long long

//#define bList->method(param) bList->method(bList, param)

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

static bListNode *get_ptr( bList *self, LENGTH_TYPE index ){
	LENGTH_TYPE i = 0;
	bListNode *now;
	if( index < self->size(self) ){
		if( self->size(self) / 2 > index ){
			now = self->begin;
			for( i = 0; i < index; i++ )
				now = now->next;
		}
		else{
			now = self->end;
			for( i = self->size(self) - 1; index < i; i-- )
				now = now->prev;
		}
		printf("index:%llu %p\n", index, now);
		return now;
	}
	printf("index:%llu %p\n", index, NULL);
	return NULL;
}

static bListNode *make( void ){
	bListNode *new = malloc( sizeof(bListNode) );
	new->prev = NULL;
	new->next = NULL;
	memset( &(new->data), 0, sizeof(TYPE) );
	return new;
}

static TYPE* back( bList *self ){
	return &(self->begin->data);
}

static void clear( bList *self ){
	if( self->begin != NULL && self->end != NULL )
		while( !self->erase( self, 0 ) );

	self->begin = NULL;
	self->end = NULL;

	return;
}

static void delete( bList *self, TYPE* data ){
	LENGTH_TYPE i = 0;
	for( i = 0; i < self->size(self); i++ )
		if( *self->get(self, i) == *data )
			self->erase( self, i );
}

static int empty( bList *self ){
	return !(self->size(self));
}

static int erase( bList *self, LENGTH_TYPE index ){
	bListNode *indexPtr = get_ptr( self, index );
	if( indexPtr != NULL ){
		if( indexPtr->prev != NULL )
			indexPtr->prev->next = indexPtr->next;
		else
			self->begin = indexPtr->next;
		if( indexPtr->next != NULL )
			indexPtr->next->prev = indexPtr->prev;
		else
			self->end = indexPtr->prev;
		
		free(indexPtr);
		self->size--;
		return 1;
	}
	return 0;
}

static TYPE* front( bList *self ){
	return &(self->begin->data);
}

static TYPE* get( bList *self, LENGTH_TYPE index ){
	bListNode *indexPtr = get_ptr( self, index );
	if( indexPtr != NULL )
		return &(indexPtr->data);
	return NULL;
}

static void insert( bList *self, LENGTH_TYPE index, TYPE *data ){
	bListNode *indexPtr = get_ptr( self, index );
	bListNode *new = make();
	if( indexPtr != NULL ){
		if( indexPtr->prev != NULL ){
			if( indexPtr->prev->prev != NULL ){
				indexPtr->prev->prev->next = new;
				new->prev = indexPtr->prev->prev;
			}
			else{
				self->begin = new;
				new->prev = NULL;
			}
			new->next = indexPtr->prev;
		}
		self->begin = new;
		new->prev = NULL;
		new->next = indexPtr;
	}
	new->data = *data;
	self->length++;

	return;
}

static void pop_back( bList *self ){
	self->erase(self, 0);
	return;
}

static void pop_front( bList *self ){
	self->erase(self, self->size(self) - 1 );
	return;
}

static void push_back( bList *self, TYPE *data ){
	bListNode *new = make();

	new->data = *data;
	if( self->end != NULL ){
		self->end->next = new;
		new->prev = self->end;
	}
	else
		self->begin = new;

	self->length++;
	self->end = new;
	return;
}

static void push_front( bList *self, TYPE *data ){
	bListNode *new = make();
	new->data = *data;
	self->begin->prev = new;
	new->next = self->begin;
	self->length++;
	self->begin = new;
	return;
}

static void reverse( bList *self ){
	bListNode *now = self->begin, *tmp;
	LENGTH_TYPE i = 0;
	for( i = 0; i < self->size(self); i++ ){
		tmp = now->next;
		now->next = now->prev;
		now->prev = tmp;
		now = tmp;
	}
	tmp = self->begin;
	self->begin = self->end;
	self->end = tmp;
	return;
}

static void set( bList *self, LENGTH_TYPE index, TYPE *data ){
	bListNode *indexPtr = get_ptr( self, index );
	if( indexPtr != NULL )
		indexPtr->data = *data;
	return;
}

static LENGTH_TYPE size( bList *self ){
	return self->length;
}

void init( bList *self ){

	self->begin = NULL;
	self->end = NULL;
	self->length = 0;
	self->back = back;
	self->clear = clear;
	self->delete = delete;
	self->empty = empty;
	self->erase = erase;
	self->front = front;
	self->get = get;
	self->init = init;
	self->insert = insert;
	self->pop_back = pop_back;
	self->pop_front = pop_front;
	self->push_back = push_back;
	self->push_front = push_front;
	self->reverse = reverse;
	self->set = set;
	self->size = size;
//	self->sort = sort;
//	self->unique = unique;
	
	return;
}

#endif

int main( void ){
	int num = 10;

	printf("%d\n", sizeof(bList));
	puts("HEY");
	bList array;
	puts("HEY");
	init( &array );
	printf("array: %p init:length:%llu %p\n", &array, array.size( &array ), array.size);
	array.push_back( &array, &num );
	printf("%d\n", *array.get(&array, 0));
	printf("array: %p push_back:length:%llu %p\n", &array, array.size( &array ), array.size);
	array.erase( &array, 0);
	printf("array: %p erase:length:%llu %p\n", &array, array.length, array.size);
	array.clear( &array );
	printf("array: %p clear:length:%llu %p\n", &array, array.length, array.size);
	printf("%llu\n", size( &array ));

	return 0;
}
