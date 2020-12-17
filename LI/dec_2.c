#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grpwk20.h"
#define DATA_LEN 100000
#define TIME 20

char rslt[ORGDATA_LEN];
int rslt_addr[DATA_LEN][4];

int max_array(int* a){
    int M = 0;
    for(int i=1; i<4; i++){
        if(a[M] < a[i]) M = i;
    }
    return M;
}

int tonum(char c) {
    if(c == 'A')
        return 0;
    else if(c == 'C')
        return 1;
    else if(c == 'G')
        return 2;
    else
        return 3;
}

int dec(){
    FILE *sfp;
    if((sfp = fopen(SEQDATA, "r")) ==NULL){
        fprintf(stderr, "cannot open %s\n", SEQDATA);
        exit(1);
    }

    FILE *dfp;
    if((dfp = fopen(DECDATA, "w")) ==NULL){
        fprintf(stderr, "cannot open %s\n", DECDATA);
        exit(1);
    }

    unsigned char c;

    for(int i=0; i<DATA_LEN; i++){
        for(int j=0; j<4; j++){
            rslt_addr[i][j] = 0;
        }
    }

    for(int i=0; i<TIME; i++){
        for(int l=0; l<DATA_LEN; l++){
            //get the data(A,C,G,T)
            int data[4] = {0, 0, 0, 0};
            for(int j=0; j<7; j++){
                c = getc(sfp);
                data[tonum(c)]++;
            }
            int m = max_array(data);
            //get the address(2 times/group)
            for(int j=0; j<2; j++){
                int addr_res = 0;
                for(int k=0; k<9; k++){
                    c = getc(sfp);
                    addr_res += tonum(c)*pow(4, 8-k);
                }
                if(addr_res < DATA_LEN) rslt_addr[addr_res][m]++;
            }
        }
        c = getc(sfp);
    }

    //get final reslut
    for(int i=0; i<DATA_LEN; i++){
        int n = max_array(rslt_addr[i]);
        switch(n){
            case 0:
                rslt[i*2] = '0';
                rslt[i*2+1] = '0';
                break;
            case 1:
                rslt[i*2] = '0';
                rslt[i*2+1] = '1';
                break;
            case 2:
                rslt[i*2] = '1';
                rslt[i*2+1] = '0';
                break;
            case 3:
                rslt[i*2] = '1';
                rslt[i*2+1] = '1';
                break;
            default:
                break;
        }
    }

    //output
    for(int i=0; i<ORGDATA_LEN; i++){
        fputc(rslt[i],dfp);
    }
    c = '\n';
    fputc(c, dfp);

    fclose(sfp);
    fclose(dfp);
    return(0);
}

int main(){
    dec();
    return(0);
}
