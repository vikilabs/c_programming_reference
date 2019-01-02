/* Sample code to simulate Class in c using structure.
 *
 *	Author:
 *		Viki (a) Vignesh Natarajan
 *		viki@vikilabs.org	
 *
 *  This code is free to use and experiment. Have Fun ;-)
 */

#include <stdio.h>

typedef void (*tFpGeneric) (void *, void *, void *); 

typedef struct{
	tFpGeneric func;
}tClass;

void testInt(void *self, void *input, void *output)
{
	if(input){
		printf("Test Function Input = %d\n", *((int*) input));

		if(output != NULL){
			*((int *) output) = *((int *)input);
		}

	}else{
		printf("Test Function Input = 0\n");

		if(output != NULL){
			*((int *)output) = 0;
		}

	}
	return;
}

int main()
{
	int input = 2, output = 0;
	tClass obj;
	obj.func=testInt;
	obj.func(&obj, &input, &output);
	printf("Test Function Output = %d\n", output);
	return 0;
}
