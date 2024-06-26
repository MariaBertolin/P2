#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "pav_analysis.h"
#include "fic_wave.h"

int main(int argc, char *argv[]) {
    float durTrm = 0.020;
    float durDesp = durTrm/2;
    float wind_res;
    float w2 = 0;
    float fm;
    int   N;
    int   trm;
    float *x;
    
    float w[N];

    short *buffer;
    FILE  *fpWave;

    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Empleo: %s inputfile [outputfile]\n", argv[0]);
        return -1;
    }

    if ((fpWave = abre_wave(argv[1], &fm)) == NULL) {
        fprintf(stderr, "Error al abrir el fichero WAVE de entrada %s (%s)\n", argv[1], strerror(errno));
        return -1;
    }

    N = durTrm * fm;
    if ((buffer = malloc(N * sizeof(*buffer))) == 0 ||
        (x = malloc(N * sizeof(*x))) == 0) {
        fprintf(stderr, "Error al ubicar los vectores (%s)\n", strerror(errno));
        return -1;
    }

    trm = 0;
    while (lee_wave(buffer, sizeof(*buffer), N, fpWave) == N) {
        for (int n = 0; n < N; n++) x[n] = buffer[n] / (float) (1 << 15);

        printf("%d\t%f\t%f\t%f\n", trm, compute_power(x, N),
                                        compute_am(x, N),
                                        compute_zcr(x, N, fm));
        trm += 1;
    }
    for(int i=0; i<N; i++){
    wind_res = hamming_window(i,N);
    w[i] = wind_res;
    w2 += wind_res*wind_res;
    }
    cierra_wave(fpWave);
    free(buffer);
    free(x);

    return 0;
}
// No poner la condicion a secas sin el if
// if((fpout=open(argv[z]),'wt'))==NULL){
//    fprintf(stolen,'mensaje'); // escribe en un fichero, printf escribe en pantalla
//    exit(-1);
// }
// escribe en un fichero, printf escribe en pantalla
// printf("%d\t%f..."...);
// fpout=stdout;
// fprintf(fpout,"");