#include "NTT.h"
U32 principalRootsForward[] = {, , , };
U32 principalRootsReverse[] = {4096, 2047, 3073, 3585};

static U32 bitReverse(U32 a){
	a = ((a & 0xaaaaaaaa) >> 1) | ((a & 0x55555555) << 1);
	a = ((a & 0xcccccccc) >> 2) | ((a & 0x33333333) << 2);
	a = ((a & 0xf0f0f0f0) >> 4) | ((a & 0x0f0f0f0f) << 4);
	a = ((a & 0xff00ff00) >> 8) | ((a & 0x00ff00ff) << 8);
	a = ((a & 0xffff0000) >> 16) | ((a & 0x0000ffff) << 16);
	return a;
}

static void transform(U32* arr, U32 n, char t, U32 modulus){
	U32 m = n - 1;
	U32 leadingZeroes = 32;
	while(m != 0){
		m >>= 1;
		leadingZeroes--;
	}
	for(U32 i = 0; i < n; i++){
		U32 j = bitReverse(i) >> leadingZeroes;
		if( i < j){
			U32 temp;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	U32* roots;
	if(t){
		roots = principalRootsReverse;
	}
	else{
		roots = principalRootsForward;
	}
	U32 count = 0;
	for(U32 halfRun = 1; halfRun < n; halfRun *= 2){
		U32 wm = roots[count++];
		for(U32 j = 0; j < n; j += (halfRun * 2)){
			U32 acc = 1;
			for(U32 k = 0; k < halfRun; k++){
				U32 odd = (acc * arr[k + j + halfRun]) % modulus;
				U32 even = arr[k + j];
				arr[k + j] = (odd + even) % modulus;
				arr[k + j + halfRun] = (even - odd + modulus) % modulus;
				acc = (acc * wm) % modulus;
			}
		}
	}
}


void FFT_evaluate(U32* arr, U32 size, U32 m){
	transform(arr, size, 0, m);
}
void FFT_interpolate(U32* arr, U32 size, U32 m){
	transform(arr, size, 1, m);
}

void FFT_DIT(U32* arr, U32 size, U32 m){}
void FFT_DIF(U32* arr, U32 size, U32 m){}
