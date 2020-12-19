#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grpwk20.h"
#define N 610000

int min(int a, int b, int c){
    if(a>b){
        if(b>c) return c;
        else return b;
    }
    else{
        if(a>c) return c;
        else return a;
    }
}

//編集距離を返す
int ed(char *str1, char *str2){
  int cost = 0, dist;
  int i, j;
  int lenstr1 = strlen(str1) + 1;
  int lenstr2 = strlen(str2) + 1;
  int **d = (int**)malloc(lenstr1*sizeof(int*));

  for(i=0;i<lenstr1;i++) d[i] = (int*)malloc(lenstr2*sizeof(int));

  for(i=0;i<lenstr1;i++) d[i][0] = i;
  for(j=0;j<lenstr2;j++) d[0][j] = j;

  for(i=1;i<lenstr1;i++){
    for(j=1;j<lenstr2;j++){
      if(str1[i-1]==str2[j-1]) cost = 0;
      else cost = 1;
      d[i][j] = min(d[i-1][j]+1, d[i][j-1]+1, d[i-1][j-1]+cost);
    }
  }
  dist = d[lenstr1-1][lenstr2-1];
  free(d);
  return dist;
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

  int i=1, j;
  char str[N];
  fgets(str, N, sfp);

  //連続部分の削除
  char pre;
  pre = str[0];
  while(str[i]!='\0'){
    if(str[i]==pre){
      j = i;
      while(str[j]!='\0'){
        str[j] = str[j+1];
        j++;
      }
    }
    pre = str[i];
    i++;
  }
  
  //見ている文字列の先頭 k
  //編集距離 d0,d1,d2,d3
  //見ている文字列 res
  int k=0, d0, d1, d2, d3;
  char res[7];
  char id0[]="AGTACT", id1[]="AGCATC", id2[]="GATGCT", id3[]="GACGTC";
  
  while(1){
    //6文字で比較
    strncpy(res, str+k, 6);
    if(strlen(res)<=2) break;
    res[6] = '\0';
    d0 = ed(id0, res);
    d1 = ed(id1, res);
    d2 = ed(id2, res);
    d3 = ed(id3, res);

    memset(res, '0', 7);

    if(d0==0) {fputs("00", dfp); k+=6;}
    else if(d1==0) {fputs("01", dfp); k+=6;}
    else if(d2==0) {fputs("10", dfp); k+=6;}
    else if(d3==0) {fputs("11", dfp); k+=6;}
    else {
      //6文字でうまくいかないときは5文字で比較
      strncpy(res, str+k, 5);
      res[5] = '\0';
      d0 = ed(id0, res);
      d1 = ed(id1, res);
      d2 = ed(id2, res);
      d3 = ed(id3, res);

      memset(res, '0', 7);

      if(d0==1) {fputs("00", dfp); k+=5;}
      else if(d1==1) {fputs("01", dfp); k+=5;}
      else if(d2==1) {fputs("10", dfp); k+=5;}
      else if(d3==1) {fputs("11", dfp); k+=5;}
      else {
        //5文字でうまくいかないときは4文字で比較
        strncpy(res, str+k, 4);
        res[4] = '\0';
        d0 = ed(id0, res);
        d1 = ed(id1, res);
        d2 = ed(id2, res);
        d3 = ed(id3, res);

        memset(res, '0', 7);

        if(d0==2) {fputs("00", dfp); k+=4;}
        else if(d1==2) {fputs("01", dfp); k+=4;}
        else if(d2==2) {fputs("10", dfp); k+=4;}
        else if(d3==2) {fputs("11", dfp); k+=4;}
        else {
          //4文字でうまくいかないときは3文字で比較
          strncpy(res, str+k, 3);
          res[3] = '\0';
          d0 = ed(id0, res);
          d1 = ed(id1, res);
          d2 = ed(id2, res);
          d3 = ed(id3, res);

          memset(res, '0', 7);

          //妥協込み
          if(d0<=d1 && d0<=d2 && d0<=d3) {fputs("00", dfp); k+=3;}
          else if(d1<=d0 && d1<=d2 && d1<=d3) {fputs("01", dfp); k+=3;}
          else if(d2<=d0 && d2<=d1 && d2<=d3) {fputs("10", dfp); k+=3;}
          else {fputs("11", dfp); k+=3;}
        }
      }
    }
  }
  fputc('\n', dfp);
    
  fclose(sfp);
  fclose(dfp);
  return(0);
}

int main(){
  dec();
  return(0);
}
