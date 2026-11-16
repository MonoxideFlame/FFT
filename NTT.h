#include <stdio.h>

#include <stdint.h>
typedef uint64_t U64;
typedef uint32_t U32;

void NTT_evaluate(U64* arr, U64 size);
void NTT_interpolate(U64* arr, U64 size);

U64 multiply_goldilocks(U64 a, U64 b);

void NTT_convolve(U64* result, U64* a, U64* b, U64 size);


