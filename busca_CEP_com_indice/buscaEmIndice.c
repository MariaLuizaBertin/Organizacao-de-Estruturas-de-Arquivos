#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do arquivo original
typedef struct {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
} Endereco;

// Estrutura do índice
typedef struct {
    char cep[8];
    unsigned int posicao;
} indiceEndereco;

int main(int argc, char **argv) {

    FILE *fi;

    // Verifica argumento
    if (argc < 2) {
        printf("Uso: %s CEP\n", argv[0]);
        return 1;
    }

    // Abre arquivo de índice
    fi = fopen("indice.dat", "rb");
    if (fi == NULL) {
        printf("Erro ao abrir indice.dat\n");
        return 1;
    }

    // Descobre quantidade de registros
    fseek(fi, 0, SEEK_END);
    long tamanhoBytes = ftell(fi);
    long qtd = tamanhoBytes / sizeof(indiceEndereco);
    rewind(fi);

    // CEP buscado (8 bytes)
    char cepBuscado[8];
    memcpy(cepBuscado, argv[1], 8);

    // Busca binária no índice
    int esquerda = 0;
    int direita = qtd - 1;
    int meio;
    int achou = 0;

    indiceEndereco ind;

    while (esquerda <= direita) {
        meio = (esquerda + direita) / 2;

        // Vai direto ao elemento do meio
        fseek(fi, meio * sizeof(indiceEndereco), SEEK_SET);
        fread(&ind, sizeof(indiceEndereco), 1, fi);

        int cmp = strncmp(cepBuscado, ind.cep, 8);

        if (cmp == 0) {
            achou = 1;
            break;
        } else if (cmp < 0) {
            direita = meio - 1;
        } else {
            esquerda = meio + 1;
        }
    }

    fclose(fi);

    // Se não encontrou
    if (!achou) {
        printf("CEP nao encontrado\n");
        return 0;
    }

    // Acesso direto ao arquivo original
    FILE *fd = fopen("../dados/cep_rj.dat", "rb");
    if (fd == NULL) {
        printf("Erro ao abrir cep.dat\n");
        return 1;
    }

    // Vai direto na posição encontrada
    fseek(fd, ind.posicao * sizeof(Endereco), SEEK_SET);

    Endereco e;
    fread(&e, sizeof(Endereco), 1, fd);

    fclose(fd);

    // Imprimi os dados do endereco
    printf("O endereco eh: \n");
    printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);

    return 0;
}