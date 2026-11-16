//
//  main.cpp
//  CPPProject
//
//  Created by Adith Talupuru on 11/30/22.
//

#include <stdio.h>
#include "NTT.h"


int main(int argc, const char** argv){
    U64 size = 32;
	U64 a[32] = {1,1,1,1,1,1,1,1,
		         1,1,1,1,1,1,1,1,
		         0,0,0,0,0,0,0,0,
		         0,0,0,0,0,0,0,0};

	U64 b[32] = {1,1,1,1,1,1,1,1,
		         1,1,1,1,1,1,1,1,
		         0,0,0,0,0,0,0,0,
		         0,0,0,0,0,0,0,0};

	U64 c[32];

	for (int i = 0; i < size; i++){
		printf("%llu, ", a[i]);
	}
	printf("\n ");


	for(int i = 0; i < 5; i++){
		NTT_convolve(c, a, b, size);	
		//decimate and quantize
		for(int j = 0; j < size/2; j++){
			a[j] = c[2*j] / (4 - 2*(i%2);
			b[j] = c[2*j] / (4 - 2*(i%2);
		}
		for(int j = size/2; j < size; j++){
			a[j] = 0;
			b[j] = 0;
		}
	}
	NTT_convolve(c, a, b, size);	


	for (int i = 0; i < size; i++){
		printf("%llu, ", c[i]);//looks gaussian
	}

	return 0;
}
