#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CSVParser.h"
 
#define READ_BUF_SIZE 8192

typedef struct _Dados Dados;
struct _Dados {
    int numCasos;
    int numMortes;
};
 
void callback(char** cols, int ncols, void* userData) {
    Dados* dados = (Dados*) userData;
 
    if(strcmp(cols[1], "South America")==0){
        dados->numCasos += atoi(cols[5]); // casos
        dados->numMortes += atoi(cols[8]); ///mortes
    }
}
// DESAFIO: numero total de casos e mortes na america do sul
// colunas do ARQ=> 1-regiao, 5-caso, 8-morte
// compilar: gcc Teste2.c CSVParser.c
int main(int argc, char** argv) {    
    int qt;
    Dados dados = {0, 0};
    unsigned int total = 0;
    char* buf = (char*) malloc(READ_BUF_SIZE);

    // Verifica argumento
    if (argc < 1) {
        fprintf(stderr, "USO: %s\n", argv[0]);
        return 1;
    }

    CSVParser csv;
    CSVParser_init(&csv);
    FILE *f = fopen("../dados/owid-covid-data.csv","rb");
    if(f) {
        qt = fread(buf, 1, READ_BUF_SIZE, f);
        while(qt > 0) {
           
            total += qt;
            CSVParser_processLines(&csv, buf, qt, callback, &dados);
            qt = fread(buf, 1, READ_BUF_SIZE, f);
        }
        fclose(f);
        CSVParser_processLines(&csv, "\n", 1, callback, &dados);
        printf("Numero total de casos e mortes na America do Sul\n");
        printf("Casos: %d \nMortes: %d", dados.numCasos, dados.numMortes);
    }
    free(buf);
    return 0;
}
 