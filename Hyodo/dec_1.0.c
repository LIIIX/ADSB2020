#include <stdio.h>
#include <stdlib.h>
#include "grpwk20.h"

char s[2000010];
int pac[2000010];

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

int min(int a, int b) { return a < b ? a : b; }

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

  int repeat = 30;
  while(repeat--) {
    int n = 0;
    while((c = getc(sfp)) != '\n') {
      s[n] = c;
      ++n;
    }
    //printf("DE%d\n", n);

    for(int i = 0; i < n; i += 25) {
      int id = 0;
      for(int j = 9; 0 <= j; --j) {
        id *= 4;
        id += tonum(s[i + j]);
      }
      ++pac[id];

      id = 0;
      for(int j = 19; 10 <= j; --j) {
        id *= 4;
        id += tonum(s[i + j]);
      }
      ++pac[id];
    }
  }

  int lim = 13;
  for(int i = 0; i < ORGDATA_LEN; ++i) {
    if(pac[i] >= lim)
      fputc('0', dfp);
    else
      fputc('1', dfp);

    //if(i < 100) printf("%d,%d\n", i, pac[i]);
  }
  fputc('\n', dfp);

  fclose(sfp);
  fclose(dfp);
  return (0);
}

int main() {
  dec();
  return (0);
}
