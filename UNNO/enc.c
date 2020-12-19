#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grpwk20.h"

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

  unsigned char c1, c2;
  for(int i=0; i<ORGDATA_LEN; i+=2){
    c1 = getc(ofp);
    c2 = getc(ofp);
    
    switch( ( (c1 & 0x1) << 7) >> 6 | ( c2 & 0x1) ){
    case 0:
      fputs("AGTACT", efp);
      break;
    case 1:
      fputs("AGCATC", efp);      
      break;
    case 2:
      fputs("GATGCT", efp);     
      break;
    case 3:
      fputs("GACGTC", efp);     
      break;
    }
  }
  fputc('\n', efp);
  
  
  fclose(ofp);
  fclose(efp);
  return(0);
}

int main(){
  enc();
  return(0);
}
