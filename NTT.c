#include "NTT.h"

#define NTT_MODULUS 0xFFFFFFFF00000001ULL

// Principal 2^m-th roots of unity modulo p = 2^64 - 2^32 + 1
// Index (m - 1) corresponds to stage size 2^m (m = 1 .. 32)
U64 principalRootsForward[32] = {
    0xFFFFFFFF00000000ULL, // N = 2^1  (2)
    0x0001000000000000ULL, // N = 2^2  (4)
    0xFFFFFFFEFF000001ULL, // N = 2^3  (8)
    0xEFFFFFFF00000001ULL, // N = 2^4  (16)
    0x00003FFFFFFFC000ULL, // N = 2^5  (32)
    0x0000008000000000ULL, // N = 2^6  (64)
    0xF80007FF08000001ULL, // N = 2^7  (128)
    0xBF79143CE60CA966ULL, // N = 2^8  (256)
    0x1905D02A5C411F4EULL, // N = 2^9  (512)
    0x9D8F2AD78BFED972ULL, // N = 2^10 (1,024)
    0x0653B4801DA1C8CFULL, // N = 2^11 (2,048)
    0xF2C35199959DFCB6ULL, // N = 2^12 (4,096)
    0x1544EF2335D17997ULL, // N = 2^13 (8,192)
    0xE0EE099310BBA1E2ULL, // N = 2^14 (16,384)
    0xF6B2CFFE2306BAACULL, // N = 2^15 (32,768)
    0x54DF9630BF79450EULL, // N = 2^16 (65,536)
    0xABD0A6E8AA3D8A0EULL, // N = 2^17 (131,072)
    0x81281A7B05F9BEACULL, // N = 2^18 (262,144)
    0xFBD41C6B8CAA3302ULL, // N = 2^19 (524,288)
    0x30BA2ECD5E93E76DULL, // N = 2^20 (1,048,576)
    0xF502AEF532322654ULL, // N = 2^21 (2,097,152)
    0x4B2A18ADE67246B5ULL, // N = 2^22 (4,194,304)
    0xEA9D5A1336FBC98BULL, // N = 2^23 (8,388,608)
    0x86CDCC31C307E171ULL, // N = 2^24 (16,777,216)
    0x4BBAF5976ECFEFD8ULL, // N = 2^25 (33,554,432)
    0xED41D05B78D6E286ULL, // N = 2^26 (67,108,864)
    0x10D78DD8915A171DULL, // N = 2^27 (134,217,728)
    0x59049500004A4485ULL, // N = 2^28 (268,435,456)
    0xDFA8C93BA46D2666ULL, // N = 2^29 (536,870,912)
    0x7E9BD009B86A0845ULL, // N = 2^30 (1,073,741,824)
    0x400A7F755588E659ULL, // N = 2^31 (2,147,483,648)
    0x185629DCDA58878CULL  // N = 2^32 (4,294,967,296)
};
// Principal inverse 2^m-th roots of unity modulo p = 2^64 - 2^32 + 1
// Used for FFT_interpolate / inverse transform stages
U64 principalRootsReverse[32] = {
    0xFFFFFFFF00000000ULL, // N = 2^1  (2)
    0xFFFEFFFF00000001ULL, // N = 2^2  (4)
    0x000000FFFFFFFF00ULL, // N = 2^3  (8)
    0x0000001000000000ULL, // N = 2^4  (16)
    0xFFFFFFFEFFFC0001ULL, // N = 2^5  (32)
    0xFDFFFFFF00000001ULL, // N = 2^6  (64)
    0xFFEFFFFF00000011ULL, // N = 2^7  (128)
    0x1D62E30FA4A4EEB0ULL, // N = 2^8  (256)
    0x3DE19C67CF496A74ULL, // N = 2^9  (512)
    0x3B9AE9D1D8D87589ULL, // N = 2^10 (1,024)
    0x76A40E0866A8E50DULL, // N = 2^11 (2,048)
    0x9AF01E431FBD6EA0ULL, // N = 2^12 (4,096)
    0x3712791D9EB0314AULL, // N = 2^13 (8,192)
    0x409730A1895ADFB6ULL, // N = 2^14 (16,384)
    0x158EE068C8241329ULL, // N = 2^15 (32,768)
    0x6D341B1C9A04ED19ULL, // N = 2^16 (65,536)
    0xCC9E5A57B8343B3FULL, // N = 2^17 (131,072)
    0x22E1FBF03F8B95D6ULL, // N = 2^18 (262,144)
    0x46A23C48234C7DF9ULL, // N = 2^19 (524,288)
    0xEF8856969FE6ED7BULL, // N = 2^20 (1,048,576)
    0xA52008AC564A2368ULL, // N = 2^21 (2,097,152)
    0xD46E5A4C36458C11ULL, // N = 2^22 (4,194,304)
    0x4BB9AEE372CF655EULL, // N = 2^23 (8,388,608)
    0x10EB845263814DB7ULL, // N = 2^24 (16,777,216)
    0xC01F93FC71BB0B9BULL, // N = 2^25 (33,554,432)
    0xEA52F593BB20759AULL, // N = 2^26 (67,108,864)
    0x91F3853F38E675D9ULL, // N = 2^27 (134,217,728)
    0x3EA7EAB8D8857184ULL, // N = 2^28 (268,435,456)
    0xE4D14A114454645DULL, // N = 2^29 (536,870,912)
    0xE2434909EEC4F00BULL, // N = 2^30 (1,073,741,824)
    0x95C0EC9A7AB50701ULL, // N = 2^31 (2,147,483,648)
    0x76B6B635B6FC8719ULL  // N = 2^32 (4,294,967,296)
};

static U32 bitReverse(U32 a){
	a = ((a & 0xaaaaaaaa) >> 1) | ((a & 0x55555555) << 1);
	a = ((a & 0xcccccccc) >> 2) | ((a & 0x33333333) << 2);
	a = ((a & 0xf0f0f0f0) >> 4) | ((a & 0x0f0f0f0f) << 4);
	a = ((a & 0xff00ff00) >> 8) | ((a & 0x00ff00ff) << 8);
	a = ((a & 0xffff0000) >> 16) | ((a & 0x0000ffff) << 16);
	return a;
}

U64 multiply_goldilocks(U64 a, U64 b) {
    U32 a0 = (U32)a, a1 = (U32)(a >> 32);
    U32 b0 = (U32)b, b1 = (U32)(b >> 32);

    U64 z0 = (U64)a0 * b0; // Coefficient for 2^0
    U64 z1 = (U64)a0 * b1; // Coefficient for 2^32
    U64 z2 = (U64)a1 * b0; // Coefficient for 2^32
    U64 z3 = (U64)a1 * b1; // Coefficient for 2^64

    // 3. Accumulate middle terms with carry handling across 64-bit boundary
    U64 mid = z1 + z2;
    U64 carry_mid = (mid < z1) ? 1ULL : 0ULL; // Detect 64-bit overflow on addition

    // Assemble low and high 64-bit words
    U64 lo = z0 + (mid << 32);
    U64 carry_lo = (lo < z0) ? 1ULL : 0ULL;

    U64 hi = z3 + (mid >> 32) + (carry_mid << 32) + carry_lo;

    // 4. reduce prime (2^64 = 2^32 - 1)
    const U64 P = 0xFFFFFFFF00000001ULL;
    U64 hi_lo = hi & 0xFFFFFFFFULL;
    U64 hi_hi = hi >> 32;

    // Subtract hi_hi (since 2^96 ≡ -1 mod P)
    U64 res = lo - hi_hi;
    if (lo < hi_hi) {
        res += P;
    }

    // Add hi_lo * (2^32 - 1) = (hi_lo << 32) - hi_lo
    U64 term = (hi_lo << 32) - hi_lo;
    res += term;
    if (res < term || res >= P) {
        res -= P;
    }

    return res;
}


static void transform(U64* arr, U32 n, char t){
	U64 m = n - 1;
	U64 leadingZeroes = 32;
	while(m != 0){
		m >>= 1;
		leadingZeroes--;
	}
	for(U32 i = 0; i < n; i++){
		U32 j = bitReverse(i) >> leadingZeroes;
		if( i < j){
			U64 temp;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	U64* roots;
	if(t){
		roots = principalRootsReverse;
	}
	else{
		roots = principalRootsForward;
	}
	U32 count = 0;
	for(U64 halfRun = 1; halfRun < n; halfRun *= 2){
		U64 wm = roots[count++];
		for(U64 j = 0; j < n; j += (halfRun * 2)){
			U64 acc = 1;
			for(U32 k = 0; k < halfRun; k++){
				//butterfly	
				U64 even = arr[k + j];
				U64 odd  = multiply_goldilocks(acc, arr[k + j + halfRun]);

				U64 sum = even + odd;

				if(sum >= NTT_MODULUS){
					sum -= NTT_MODULUS;//standard reduction
				} else if (sum < even){
					//we overflowed the integer across the 2^64 boundary. So the value in sum is:
					//
					//q = (a + b) - 2^64 
					//
					//actual result we want:
					//
					//r = (a + b) - 2^64 + 2^32 - 1 = q + 2^32 - 1
					//
					//The maximum q can be is 2*(2^64 - 2^32) - 2^64 = 2^64 - 2^32 - 2^32, since it comes from our ring. 
					// so r will never overflow.

					sum = sum + ((1ULL << 32) - 1);
				}

				U64 diff = even - odd;

				if(even < odd)
					diff += NTT_MODULUS;

				arr[k + j] = sum;
				arr[k + j + halfRun] = diff;	

				//acc = (acc * wm) % NTT_MODULUS;
				acc = multiply_goldilocks(acc, wm);
			}
		}
	}
}


void NTT_evaluate(U64* arr, U64 size){
	transform(arr, size, 0);
}
void NTT_interpolate(U64* arr, U64 size){
	//log size:
	U64 k = 0;
	U64 m = size;
	while(m != 1){
		m >>= 1;
		k++;
	}
	
	// the right hand side is always negative for any nonnegative value of k. 
	U64 inv_size = (NTT_MODULUS + (1ULL << (32 - k))) - (1ULL << (64 - k));

	transform(arr, size, 1);
	for(U64 i = 0; i < size; i++){
		arr[i] = multiply_goldilocks(arr[i], inv_size);
	}
}

void NTT_convolve(U64* result, U64* a, U64* b, U64 size){
	
	NTT_evaluate(a, size);
	NTT_evaluate(b, size);

	for(U64 i = 0; i < size; i++){
		result[i] = multiply_goldilocks(a[i], b[i]);
	}
		
	NTT_interpolate(result, size);	

}
