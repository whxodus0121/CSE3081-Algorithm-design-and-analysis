#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my_types.h"




int INSERTION_SORT(ELEMENT data[], int left, int right) {
	// must return 1 if the function finishes normally or return 0 otherwise
	//	return 0;

	ELEMENT *ptr = data;
	unsigned int temp;
	int i,j;
	ELEMENT te;
	double s, e;
	

	for(i=1;i<right+1;i++){
		temp = ptr[i].key;
		te = ptr[i];
		for(j=i-1;j>=0 && ptr[j].key>temp; j--) {
		

			ptr[j+1]=ptr[j];
			
		}
		
		ptr[j+1]= te;
		
	}

	
	

	return 1;
} 