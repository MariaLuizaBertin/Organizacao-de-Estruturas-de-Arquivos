#include "ArvoreB.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; 
};


int main(int argc, char** argv)
{
    ArvoreB* a = ArvoreB_Abre("arvore.dat");
    char chave[TAM_CHAVE+1];
    long posicao=0;
/*
    for(i=0; i<1000000; i++)
    {
        sprintf(chave,"%08d",i);
        posicao = i;
        ArvoreB_Insere(a, chave, posicao);
    }*/

    Endereco e;
    int qt;
    FILE * f = fopen("cep-1.dat", "rb");
    qt = fread(&e, sizeof(Endereco), 1, f);
    srand(time(NULL));
    
    printf("escrevendo na arvore");
    while (qt > 0){
     //   printf("%ld - %s \n", posicao,e.cep);
        ArvoreB_Insere(a, e.cep, posicao);
        qt = fread(&e, sizeof(Endereco), 1, f);
        posicao ++;

    }
    printf("Acabou!!!");
    fclose(f);

    ArvoreB_Fecha(a);
    return 0;
}
