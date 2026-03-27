#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nPartes 4

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

    qtBloco = tam/nPartes;
    sobra = tam % nPartes;
    buffer = malloc((qtBloco+1)*sizeof(Endereco));
    
    // arquivos menores sendo ordenados 
    for(int i=0;i<nPartes ; i++) {
        long qtdB = (i<sobra? qtBloco+1: qtBloco);
        //(i<sobra? qtBloco+1: qtBloco) é o mesmo que : if(qtBloco < sobra) { qtBloco += 1; } else {qtBloco;}

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

    printf("O arquivo cep-rj.dat foi dividido em %d arquivos menores",nPartes);
    return 0;
}