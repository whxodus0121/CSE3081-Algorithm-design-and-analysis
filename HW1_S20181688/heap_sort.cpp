#include <stdio.h>
#include <string.h>
#include "my_types.h"

void swap(ELEMENT *a,ELEMENT *b);
void make_heap(ELEMENT data[],int root, int size);
void build_heap(ELEMENT data[],int size);

void swap(ELEMENT *a,ELEMENT *b){
	ELEMENT temp;
	temp = *a;
	*a=*b;
	*b=temp;

}

void make_heap(ELEMENT data[], int root, int size){

	int left_chi,right_chi;
	ELEMENT *ptr=data;
	left_chi = root*2+1;
	right_chi = root*2+2;
	int parent =root;

	memcpy(ptr,data,size);

	if(left_chi<size && ptr[left_chi].key>ptr[parent].key){

		parent = left_chi;
	}

	if(right_chi<size && ptr[right_chi].key>ptr[parent].key){

		parent = right_chi;
	}

	if ( parent!=root){

		swap(&ptr[parent],&ptr[root]);		
		make_heap(ptr,parent,size);

	}

}

void build_heap(ELEMENT data[],int size){
	ELEMENT *ptr=data;

	int i,j;
	for(i=size/2-1;i>=0;i--){
		make_heap(ptr,i,size);
	}
}

int HEAP_SORT(ELEMENT data[], int left, int right) {
	int i;
	int size =right-left+1;
	ELEMENT *ptr=data;
	
	build_heap(ptr,size);

	for(i=size-1;i>=0;i--){

		swap(&ptr[0],&ptr[i]);
		make_heap(ptr,0,i);
	}
	

	return 1;
}