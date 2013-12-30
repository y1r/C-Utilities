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

static TYPE* array( bList *self ){
	LENGTH_TYPE i = 0;
	TYPE* array = malloc( sizeof(TYPE) * self->size( self ) );
	bListNode *now = self->begin;

	if( array == NULL )
		return NULL;

	for( i = 0; i < self->size( self ); i++ ){
		array[i] = now->data;
		now = now->next;
	}

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

static TYPE* get( bList *self, LENGTH_TYPE index ){
	LENGTH_TYPE i = 0;
	TYPE tmp;
	memset( &tmp, 0, sizeof(TYPE) );
	bListNode *indexPtr = get_ptr( self, index );
	if( indexPtr == NULL ){
		self->resize( self, index );
		indexPtr = get_ptr( self, index );
	}
	return &(indexPtr->data);
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
			new->prev = indexPtr->prev;
			indexPtr->prev = new;
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
	LENGTH_TYPE i = 0, all = self->size(self) + src->size(src);
	TYPE *tmp = malloc( sizeof(TYPE) * all );
	bListNode *selfPtr = self->begin, *srcPtr = src->begin;

	while( selfPtr != NULL && srcPtr != NULL ){
		if( srcPtr->data < selfPtr->data ){
			tmp[i] = srcPtr->data;
			srcPtr = srcPtr->next;
		}
		else{
			tmp[i] = selfPtr->data;
			selfPtr = selfPtr->next;
		}
		i++;
	}

	while( selfPtr != NULL ){
		tmp[i] = selfPtr->data;
		selfPtr = selfPtr->next;
		i++;
	}

	while( srcPtr != NULL ){
		tmp[i] = srcPtr->data;
		srcPtr = srcPtr->next;
		i++;
	}

	self->resize( self, all );
	selfPtr = self->begin;
	for( i = 0; i < all; i++ ){
		selfPtr->data = tmp[i];
		selfPtr = selfPtr->next;
	}

	free(tmp);

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

static void resize( bList *self, LENGTH_TYPE index ){
	TYPE tmp;
	memset( &tmp, 0, sizeof( TYPE ) );

	while( self->size( self ) - 1 > index )
		self->pop_back( self );
	while( self->size( self ) - 1 < index )
		self->push_back( self, &tmp );

	return;

}

static void reverse( bList *self ){
	bListNode *now = self->begin, *tmp;
	LENGTH_TYPE i = 0;

	for( i = 0; i < self->size(self); i++ ){
//		printf("要素%llu ptr = %p prev = %p next = %p\n", i, now, now->prev, now->next );
		now = now->next;
	}
	now = self->begin;

	for( i = 0; i < self->size(self); i++ ){
		tmp = now->next;
		now->next = now->prev;
		now->prev = tmp;
		now = tmp;
	}
	tmp = self->begin;
	self->begin = self->end;
	self->end = tmp;
	now = self->begin;
	for( i = 0; i < self->size(self); i++ ){
//		printf("要素%llu ptr = %p prev = %p next = %p\n", i, now, now->prev, now->next );
		now = now->next;
	}
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

static void sort( bList *self ){
	LENGTH_TYPE i = 0;

	TYPE *data = self->array( self );

//	puts("ARRAY");
//	for( i = 0; i < self->size( self ); i++ )
//		printf("%d\n", data[i]);

	qsort( data, self->size( self ), sizeof( TYPE ), comp );
	for( i = 0; i < self->size( self ); i++ )
		*(self->get( self, i )) = data[i];

	self->array_free( self, data );

	return;
}

static void splice( bList *self, LENGTH_TYPE index, const bList *src ){
	LENGTH_TYPE i = 0;
	bListNode *tmp = src->begin;

	for( i = 0; i < src->size( src ); i++ ){
		self->insert( self, index + i, &(tmp->data) );
		tmp = tmp->next;
	}

	return;
}

static void unique( bList *self ){
	LENGTH_TYPE i = 0;
	bListNode *now = self->begin;

	for( i = 0; i < self->size( self ) - 1; i++ ){
		if( now->data == now->next->data )
			self->erase( self, i + 1 );
		now = now->next;
	}

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
	self->merge = merge;
	self->pop_back = pop_back;
	self->pop_front = pop_front;
	self->push_back = push_back;
	self->push_front = push_front;
	self->resize = resize;
	self->reverse = reverse;
	self->size = size;
	self->sort = sort;
	self->splice = splice;
	self->unique = unique;
	
	return;
}

