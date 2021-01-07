#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <stdio.h>
#include <stdlib.h>
#include "grpwk20.h"

short tonum(char c) {
  if(c == 'A')
    return 0;
  else if(c == 'C')
    return 1;
  else if(c == 'G')
    return 2;
  else
    return 3;
}

int dec() {
  FILE* sfp;
  if((sfp = fopen(SEQDATA, "r")) == NULL) {
    fprintf(stderr, "cannot open %s\n", SEQDATA);
    exit(1);
  }

  FILE* dfp;
  if((dfp = fopen(DECDATA, "w")) == NULL) {
    fprintf(stderr, "cannot open %s\n", DECDATA);
    exit(1);
  }

  unsigned char c, res;
  int cnt = 0;
  short m;
  c = getc(sfp);
  while(c != '\n') {
    //前から奇数個の場合デコード
    res = c;
    if(!(cnt & 1)) {
      m = tonum(res);
      fputc((m >> 1) + '0', dfp);
      fputc((m & 0x1) + '0', dfp);
    }
    while(1) {
      c = getc(sfp);
      if(c != res) break;
    }
    cnt++;
  }

  res = '\n';
  fputc(res, dfp);

  fclose(sfp);
  fclose(dfp);
  return (0);
}

int main() {
  dec();
  return (0);
}