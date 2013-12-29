// bidirectional list implementation

#include "bList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bListNode *get_ptr( const bList *self, LENGTH_TYPE index ){
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
		return now;
	}
	return NULL;
}

static bListNode *make( void ){
	bListNode *new = malloc( sizeof(bListNode) );
	new->prev = NULL;
	new->next = NULL;
	memset( &(new->data), 0, sizeof(TYPE) );
	return new;
}

static TYPE* array( const bList *self ){
	LENGTH_TYPE i = 0;
	TYPE* array = malloc( sizeof(TYPE) * self->size( self ) );

	if( array == NULL )
		return NULL;

	for( i = 0; i < self->size( self ); i++ )
		array[i] = *self->get( self, i );

	return array;
}

static void array_free( const bList *self, TYPE *array ){
	free( array );
	return;
}
static TYPE* back( const bList *self ){
	return &(self->begin->data);
}

static void clear( bList *self ){
	if( self->begin != NULL && self->end != NULL )
		while( self->erase( self, 0 ) );

	self->begin = NULL;
	self->end = NULL;

	return;
}

static void delete( bList *self, const TYPE* data ){
	LENGTH_TYPE i = 0;
	for( i = 0; i < self->size(self); i++ )
		if( *self->get(self, i) == *data )
			self->erase( self, i );
}

static int empty( const bList *self ){
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
		self->length--;
		if( !self->size( self ) ){
			self->begin = NULL;
			self->end = NULL;
		}
		return 1;
	}
	return 0;
}

static TYPE* front( const bList *self ){
	return &(self->begin->data);
}

static TYPE* get( const bList *self, LENGTH_TYPE index ){
	bListNode *indexPtr = get_ptr( self, index );
	if( indexPtr != NULL )
		return &(indexPtr->data);
	return NULL;
}

static void insert( bList *self, LENGTH_TYPE index, const TYPE *data ){
	bListNode *indexPtr = get_ptr( self, index );
	bListNode *new = make();
	new->data = *data;

	if( !self->size( self ) ){
		self->begin = new;
		self->end = new;
		self->length++;
		return;
	}

	if( indexPtr != NULL ){
		if( indexPtr->prev != NULL ){
			indexPtr->prev->next = new;
			indexPtr->prev = new;
			new->prev = indexPtr->prev;
			new->next = indexPtr;
		}
		else{
			self->begin = new;
			indexPtr->prev = new;
			new->prev = NULL;
			new->next = indexPtr;
		}
		self->length++;
		return;
	}
	free( new );
	return;
}

static void merge( bList *self, const bList *src ){
	LENGTH_TYPE i = 0;
	for( i = 0; i < src->size( src ); i++ )
		self->push_back( self, src->get( src, i ) );
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

static void push_back( bList *self, const TYPE *data ){
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

static void push_front( bList *self, const TYPE *data ){
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

static LENGTH_TYPE size( const bList *self ){
	return self->length;
}

static int comp( const void *a, const void *b ){
	if( *(TYPE *)a < *(TYPE *)b )
		return -1;
	else if( *(TYPE *)a == *(TYPE *)b )
		return 0;
	else
		return 1;
}

static void sort( const bList *self ){
	LENGTH_TYPE i = 0;
	TYPE *data = self->array( self );
	qsort( data, self->size( self ), sizeof( TYPE ), comp );
	for( i = 0; i < self->size( self ); i++ )
		*self->get( self, i ) = data[i];

	self->array_free( self, data );

	return;
}

static void unique( bList *self ){
	LENGTH_TYPE i = 0;
	for( i = 0; i < self->size( self ) - 1; i++ )
		if( *self->get( self, i ) ==  *self->get( self, i + 1 ) )
			self->erase( self, i + 1 );

	return;
}

void bList_init( bList *self ){

	self->array = array;
	self->array_free = array_free;
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
	self->init = bList_init;
	self->insert = insert;
	self->pop_back = pop_back;
	self->pop_front = pop_front;
	self->push_back = push_back;
	self->push_front = push_front;
	self->reverse = reverse;
	self->size = size;
	self->sort = sort;
	self->unique = unique;
	
	return;
}

