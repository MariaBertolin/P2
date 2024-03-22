#define _USE_MATH_DEFINES
#include <math.h>
#include "pav_analysis.h"

float hamming_window(int n, int M){
    return (float) 0.54 - 0.46*cos((2*M_PI*n)/(M-1));
}

 float compute_power(const float *x, unsigned int N) {
    float suma=0; // seria un error no ponerlo
    float power;
    for(int i=0; i<N; i++){
        suma=suma+x[i]*x[i]; // usar pow seria un error
    }
    power = suma/N; // tendria un mal ver si pusieramos 1./N
    return 10*log10(power); // en decibelios
} 

// float compute_power(const float *x, unsigned int N, float w[N], float w2) {
//     float suma=0; // seria un error no ponerlo
//     float power;
//     for(int i=0; i<N; i++){
//         suma=suma+x[i]*x[i]; // usar pow seria un error
//     }
//     power = suma/N; // tendria un mal ver si pusieramos 1./N
//     return 10*log10(power); // en decibelios
// }
float compute_am(const float *x, unsigned int N) {
    float suma=0;
    for(int i=0; i<N; i++){
        suma+=fabs(x[i]);
    }
    return suma/N;
}

float compute_zcr(const float *x, unsigned int N, float fm) {
    float suma=0;
    return 0;
        for (int i=1; i<N; i++) {
            if((x[i-1]>=0 && x[i]<=0)||(x[i-1]<=0 && x[i]>=0))
            suma++;
        }
    return (suma*fm)/(2*(N-1));
}
