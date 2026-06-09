#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ArvoreB.h"
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
    Endereco e;
    int qt;
    FILE * f = fopen("cep-2.dat", "rb");
    FILE *s = fopen("cep-intercepcao.dat", "wb");
    qt = fread(&e, sizeof(Endereco), 1, f);
    srand(time(NULL));
    ArvoreB* a = ArvoreB_Abre("arvore.dat");
    char chave[TAM_CHAVE+1];
    long posicao;

    while (qt > 0){
        posicao = ArvoreB_Busca(a, e.cep);

        if (posicao==-1){
            printf("nao eh igual");
        }  else {
            printf("%ld\n",posicao);
            fwrite(&e,sizeof(Endereco),1,s);

        }  
              
        qt = fread(&e, sizeof(Endereco), 1, f);
    }
    ArvoreB_Fecha(a);
    fclose(f);




    
    return 0;
}

