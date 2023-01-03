#include <stdio.h>
#include <string.h>
#include "my_types.h"

int QUICK_SORT(ELEMENT data[], int left, int right) {
	// must return 1 if the function finishes normally or return 0 otherwise
	//	return 0;
	ELEMENT* ptr = data;
	ELEMENT pivot;
	ELEMENT temp;
	int start,end;
	start = left;
	end = right;
	pivot = ptr[(left+right)/2];
	
	if((pivot.key<ptr[left].key && ptr[left].key<ptr[right].key) || (pivot.key>ptr[left].key && ptr[left].key>ptr[right].key)){

		pivot = ptr[left];
		start = left+1;
		end = right;
	}
	else if((pivot.key<ptr[right].key && ptr[right].key<ptr[left].key) || (pivot.key>ptr[right].key && ptr[right].key>ptr[left].key)){

		pivot = ptr[right];
		start = left;
		end = right - 1;
	}
	else{

		start = left;
		end=right;
	}
	
	do {
		while (ptr[start].key < pivot.key) {

			start++;
		}
		while (ptr[end].key > pivot.key) {
			end--;
		}
		if (start <= end) {

			temp = ptr[start];
			ptr[start] = ptr[end];
			ptr[end] = temp;
			start++;
			end--;
		}
	} while (start <= end);

	if (left < end){
		QUICK_SORT(ptr, left, end);
	}
	if (start < right) {
		QUICK_SORT(ptr, start, right);
	}

	return 1;
}