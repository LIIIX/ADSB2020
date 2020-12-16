#include <stdio.h>
#include <stdlib.h>
#include "grpwk20.h"

char toc(int x) {
  if(x == 0)
    return 'A';
  else if(x == 1)
    return 'C';
  else if(x == 2)
    return 'G';
  else
    return 'T';
}

int enc() {
  FILE* ofp;
  if((ofp = fopen(ORGDATA, "r")) == NULL) {
    fprintf(stderr, "cannot open %s\n", ORGDATA);
    exit(1);
  }

  FILE* efp;
  if((efp = fopen(ENCDATA, "w")) == NULL) {
    fprintf(stderr, "cannot open %s\n", ENCDATA);
    exit(1);
  }

  unsigned char c1, c2, res;

  int cnt = 0;
  for(int i = 0; i < ORGDATA_LEN; ++i) {
    c1 = getc(ofp);
    if(c1 == '1') continue;
    int id = i;

    for(int j = 0; j < 10; ++j) {
      fputc(toc(id % 4), efp);
      id /= 4;
    }

    ++cnt;

    if((cnt & 1) == 0)
      for(int j = 0; j < 5; ++j) { fputc('A', efp); }
  }
  fputc('\n', efp);

  fclose(ofp);
  fclose(efp);
  return (0);
}

int main() {
  enc();
  return (0);
}
