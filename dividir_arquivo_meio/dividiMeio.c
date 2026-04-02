#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2]; // espaço + quebra de linha
} Endereco;

int compara(const void *e1, const void *e2) {
    return strncmp(((Endereco*)e1)->cep, ((Endereco*)e2)->cep, 8);
}

int main(){
    FILE *f,*saida;
    Endereco ea,eb, *buffer;
    char nomeArq[80];
    long tamBytes, tam, qtBloco, sobra;
    
    f = fopen("../dados/cep_rj.dat","rb");
    if(f == NULL){
        printf("Erro ao abrir arquivo cep_rj.dat.\n");
        return 1;
    }

    fseek(f,0, SEEK_END);
    tamBytes = ftell(f);
    tam = tamBytes / sizeof(Endereco);
    rewind(f);
    printf("Quantidade total de Registro: %d\n",tam);

    qtBloco = tam/2;
    sobra = tam % 2;
    buffer = malloc((qtBloco+1)*sizeof(Endereco));
    
    // arquivo original em 2 menores 
    for(int i=0;i<2 ; i++) {
        long qtdB = (i<sobra? qtBloco+1: qtBloco);

        fread(buffer,sizeof(Endereco),qtdB,f); 
        qsort(buffer, qtdB, sizeof(Endereco), compara);

        sprintf(nomeArq, "b%d.dat",i);
        saida = fopen(nomeArq, "wb");
        fwrite(buffer,sizeof(Endereco),qtdB,saida);
        printf("o arquivo b%d.dat tem %ld registros\n",i, qtdB);
        fclose(saida);
    }
    free(buffer);
    fclose(f);

    printf("O arquivo cep-rj.dat foi dividido ao meio");
    return 0;
}