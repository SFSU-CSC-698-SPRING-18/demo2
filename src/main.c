#include <stdio.h> 
#include <emmintrin.h>

int main()
{
    double A[8] __attribute__ ((aligned (16))) = {0,1,2,3,4,5,6,7};
    double B[8] __attribute__ ((aligned (16))) = {0,1,2,3,4,5,6,7};
    double C[8] __attribute__ ((aligned (16)));
    double CC[8] __attribute__ ((aligned (16)));
    
    // Brute force, one multiply per array index
    for(int i = 0; i < 8; i++)
    {
        C[i] = A[i] * B[i];
    }
    
    
    __m128d vec1;
    __m128d vec2;
    __m128d vec3;
    
    // Unroll loop and add 2 items at a time
    for(int i = 0; i < 8; i+= 2)
    {
        vec1 = _mm_load_pd(&A[i]);
        vec2 = _mm_load_pd(&B[i]);
        vec3 = _mm_mul_pd(vec1, vec2);
        _mm_storeu_pd (&CC[i], vec3);
    }
    
    // Now print out
    for(int i = 0; i < 8; i++)
    {
        printf("Item %i : %f  %f\n", i, C[i], CC[i]);
    }
    return 0;
}
