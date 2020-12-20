#include <stdio.h>
#include <stdlib.h>
#include "grpwk20.h"
//4回繰り返す場合にコスト80、1%くらいの確率でerror、error発生しない場合hd=0
//5回繰り返す場合にコスト100、hd＝0
#define TIMES 4

unsigned char tochar(unsigned char c1, unsigned char c2){
  unsigned char res;
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
  return res;
}

int tonum(unsigned char c) {
  if(c == 'A')
    return 0;
  else if(c == 'C')
    return 1;
  else if(c == 'G')
    return 2;
  else
    return 3;
}

unsigned char numtochar(int a){
  if(a == 0) return BASE_A;
  else if(a == 1) return BASE_C;
  else if(a == 2) return BASE_G;
  else return BASE_T;
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

/*e.g.: ACGT -> AAAAAGGGGGCCCCCAAAAAGGGGGAAAAATTTTT*/
  unsigned char c1, c2, c3, c4, base1, base2;
  int num1, num2, res;
  c1 = getc(ofp);
  c2 = getc(ofp);
  for(int i=0; i<ORGDATA_LEN; i+=2){
    if((c3 = getc(ofp)) != '\n'){
      c4 = getc(ofp);
      base1 = tochar(c1, c2); num1 = tonum(base1);
      base2 = tochar(c3, c4); num2 = tonum(base2);
      for(res = 0; (res==num1) || (res==num2); res++);
      for(int i=0; i<TIMES; i++) fputc(base1, efp);
      for(int i=0; i<TIMES; i++) fputc(numtochar(res), efp);
      c1 = c3; c2 = c4;
    } else {
      base1 = tochar(c1, c2);
      for(int i=0; i<5; i++) fputc(base1, efp);
    }
  }
  base1 = '\n';
  fputc(base1, efp);

  fclose(ofp);
  fclose(efp);
  return(0);
}

int main(){
  enc();
  return(0);
}
