#include <stdio.h>
#include <stdlib.h>
#include "grpwk20.h"

void Addr_calc(char* addr, int count, int addr_len){
    if(count == 0) return;
    else if(count == 1){
      addr[addr_len-1] = '1';
      return;
    } else {
        int cnt=1;
        while(count > 0){
            int s = count%2;
            if(s==0) addr[addr_len-(cnt++)] = '0';
            else addr[addr_len-(cnt++)] = '1';
            count = count/2;
        }
        return;
    }
}

int enc(){
    FILE *ofp;
    if((ofp = fopen(ORGDATA, "r")) ==NULL){
        fprintf(stderr, "cannot open %s\n", ORGDATA);
        exit(1);
    }

    FILE *efp;
    if((efp = fopen(ENCDATA, "w")) ==NULL){
        fprintf(stderr, "cannot open %s\n", ENCDATA);
        exit(1);
    }

    unsigned char c1, c2, res;
    int count = 0;
    for(int i=0; i<ORGDATA_LEN; i+=2){
        c1 = getc(ofp);
        c2 = getc(ofp);
    
        switch( ( (c1 & 0x1) << 7) >> 6 | ( c2 & 0x1) ){
        case 0:
            res = BASE_A;
            break;
        case 1:
            res = BASE_C;      
            break;
        case 2:
            res = BASE_G;      
            break;
        case 3:
            res = BASE_T;      
            break;
        }
        for(int j=0; j<7; j++) { fputc(res, efp); }

        char res_addr[]="000000000000000000";
        Addr_calc(res_addr, count++, 18);
        char ca1, ca2;
        for(int j=0; j<2; j++){
            for(int k=0; k<18; k+=2){
                ca1 = res_addr[k];
                ca2 = res_addr[k+1];
                switch( ( (ca1 & 0x1) << 7) >> 6 | ( ca2 & 0x1) ){
                case 0:
                    res = BASE_A;
                    break;
                case 1:
                    res = BASE_C;      
                    break;
                case 2:
                    res = BASE_G;      
                    break;
                case 3:
                    res = BASE_T;      
                    break;
                }
                fputc(res, efp);
            }
        }
    }
    res = '\n';
    fputc(res, efp);

    fclose(ofp);
    fclose(efp);
    return(0);
}

int main(){
    enc();
    return(0);
}