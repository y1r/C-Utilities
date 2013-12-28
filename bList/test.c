#define TYPE int
#include "bList.h"

#include <stdio.h>

int main( void ){
	int num = 10;

	printf("%d\n", sizeof(bList));
	puts("HEY");
	bList array;
	puts("HEY");
	bList_init( &array );
	printf("array: %p init:length:%llu %p\n", &array, array.size( &array ), array.size);
	array.push_back( &array, &num );
	printf("%d\n", *array.get(&array, 0));
	printf("array: %p push_back:length:%llu %p\n", &array, array.size( &array ), array.size);
	array.erase( &array, 0);
	printf("array: %p erase:length:%llu %p\n", &array, array.length, array.size);
	array.clear( &array );
	printf("array: %p clear:length:%llu %p\n", &array, array.length, array.size);
	printf("%llu\n", array.size( &array ));

	return 0;
}
