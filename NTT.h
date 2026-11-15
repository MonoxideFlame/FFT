#include <stdio.h>
typedef unsigned int U32;//should be fine, not serious code

void FFT_evaluate(U32* arr, U32 size, U32 m);
void FFT_interpolate(U32* arr, U32 size, U32 m);

void FFT_DIT(U32* arr, U32 size, U32 m);
void FFT_DIF(U32* arr, U32 size, U32 m);

