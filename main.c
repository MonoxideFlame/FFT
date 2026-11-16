//
//  main.cpp
//  CPPProject
//
//  Created by Adith Talupuru on 11/30/22.
//

#include <stdio.h>
#include "NTT.h"
int main(int argc, const char** argv){
    U32 size = 16;
	U32 a[16] = {0,1,1,1,
				   1,1,1,0,
				   0,0,0,0,
				   0,0,0,0}; 



	for (int i = 0; i < size; i++){
		printf("%d, ", a[i]);
	}
	printf("\n ");

	U32 m  = 65537;
	FFT_evaluate(a, size, m);

	for (int i = 0; i < size; i++){
		a[i] = (a[i] * a[i]) % m;
		printf("%d, ", a[i]);
	}
	printf("\n ");

	FFT_interpolate(a, size, m);

	for (int i = 0; i < size; i++){
		printf("%d, ", a[i]);
	}

	return 0;
}
