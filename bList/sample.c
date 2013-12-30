#include <stdio.h>
#include "bList.h"

int main( void ){
	int num = 0;
	int i = 0;

	bList array;
	bList_init( &array );
	for( i = 0; i < 10; i++ ){
		array.push_back( &array, &i );
	}
	printf("0-9までpush_back\n");
	printf("begin:%p end:%p\n", array.begin, array.end);
	for( i = 0; i < array.size(&array); i++ ){
		printf("%d要素目: %d\n", i, *array.get( &array, i ));
	}
	for( i = 0; i < 10; i++ ){
		array.push_front( &array, &i );
	}
	printf("0-9までpush_front\n");
	printf("begin:%p end:%p\n", array.begin, array.end);
	for( i = 0; i < array.size(&array); i++ ){
		printf("%d要素目: %d\n", i, *array.get( &array, i ));
	}

	num = *array.get( &array, 5 );
	array.erase( &array, 5 );
	printf("5要素目削除\n");
	printf("begin:%p end:%p\n", array.begin, array.end);
	for( i = 0; i < array.size(&array); i++ ){
		printf("%d要素目: %d\n", i, *array.get( &array, i ));
	}
	array.insert( &array, 5, &num );
	printf("5要素目挿入\n");
	printf("begin:%p end:%p\n", array.begin, array.end);
	for( i = 0; i < array.size(&array); i++ ){
		printf("%d要素目: %d\n", i, *array.get( &array, i ));
	}
	array.reverse( &array );
	printf("Reversed\n");
	printf("begin:%p end:%p\n", array.begin, array.end);
	for( i = 0; i < array.size( &array ); i++ ){
		printf("%d要素目: %d\n", i, *array.get( &array, i ));
	}
	array.sort( &array );
	printf("Sorted\n");
	for( i = 0; i < array.size( &array ); i++ ){
		printf("%d要素目: %d\n", i, *array.get( &array, i ));
	}
	array.unique( &array );
	printf("Unique\n");
	for( i = 0; i < array.size( &array ); i++ ){
		printf("%d要素目: %d\n", i, *array.get( &array, i ));
	}
	array.clear( &array );
	return 0;
}
