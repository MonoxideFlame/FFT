#include "Stockham.h"
#include <stdio.h>



void printArray(Complex* a, int len){
	printf("[");
	if(len > 0){
		for(int i = 0; i < len - 1; i++){
			printf("(%.3f) + (%.3fi),", a[i].real, a[i].imag);
		}
		printf("(%.3f) + (%.3fi)]\n", a[len - 1].real, a[len - 1].imag);
	}
	else{
		printf("]");
	}
}


void printMagnitudesSquare(Complex* a, int len){
	printf("[");
	if(len > 0){
		for(int i = 0; i < len - 1; i++){
			printf("%.6f, ", a[i].real * a[i].real + a[i].imag * a[i].imag);
		}
		printf("%.6f]\n", a[len - 1].real * a[len - 1].real + a[len - 1].imag * a[len - 1].imag);
	}
	else{
		printf("]\n");
	}
}

int main(void){
	double samples[] = {5, 2, 6, 4, 5, 6, 7, 8};
	Complex signal[8];

	for(int i = 0; i < 8; i++){
		signal[i].real = samples[i];
		signal[i].imag = 0;
	}	



	printMagnitudesSquare(signal, 8);

	fft_DIF(signal, 8);

	printMagnitudesSquare(signal, 8);

	return 0;
}
