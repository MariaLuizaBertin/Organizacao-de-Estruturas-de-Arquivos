#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CSVParser.h"
 
// emcc Teste2.c CSVParser.c -lnoderawfs.js -lnodefs.js
 
#define READ_BUF_SIZE 8192
 
void callback(char** cols, int ncols, void* userData) {
    int* count = (int*) userData;
 
    if(strcmp(cols[1], "South America")==0){
        count[0] += atoi(cols[5]); // casos
        count[1] += atoi(cols[8]); ///mortes
    }
}
// DESAFIO: numero total de casos e mortes na america do sul
// colunas do ARQ=> 1-regiao, 5-caso, 8-morte
// compilar: gcc Teste2.c CSVParser.c
int main() {    
    int qt;
    int count[2]={0,0};
    unsigned int total = 0;
    char* buf = (char*) malloc(READ_BUF_SIZE);
    CSVParser csv;
    CSVParser_init(&csv);
    FILE *f = fopen("../dados/owid-covid-data-american-continente.csv","rb");
    if(f) {
        qt = fread(buf,1,READ_BUF_SIZE,f);
        while(qt > 0) {
           
            total += qt;
            CSVParser_processLines(&csv,buf,qt,callback,count);
            qt = fread(buf,1,READ_BUF_SIZE,f);
        }
        fclose(f);
        CSVParser_processLines(&csv,"\n",1,callback,count);
        printf("Numero total de casos e mortes na America do Sul\n");
        printf("Casos: %d \nMortes: %d", count[0],count[1]);
    }
    free(buf);
    return 0;
}
 