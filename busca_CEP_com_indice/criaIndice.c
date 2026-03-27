#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura do arquivo original
typedef struct {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2]; // espaço + quebra de linha
} Endereco;

// Estrutura do índice
typedef struct {
    char cep[8];
    unsigned int posicao;
} indiceEndereco;


// Função de comparação (qsort)
int compara(const void *a, const void *b) {
    indiceEndereco *x = (indiceEndereco *)a;
    indiceEndereco *y = (indiceEndereco *)b;

    // Compara exatamente 8 bytes (CEP não é string)
    return strncmp(x->cep, y->cep, 8);
}

int main(int argc, char **argv) {

    FILE *f, *s;
    Endereco e;
    int qt;

    printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));

    // Abre arquivo de dados
    f = fopen("../dados/cep_rj.dat", "rb");
    if (f == NULL) {
        printf("Erro ao abrir cep_rj.dat\n");
        return 1;
    }

    // Descobre quantidade de registros
    fseek(f, 0, SEEK_END);
    long tamanhoBytes = ftell(f);
    long tamanhoRegistros = tamanhoBytes / sizeof(Endereco);

    // Aloca vetor de índice
    indiceEndereco *a = malloc(tamanhoRegistros * sizeof(indiceEndereco));
    if (a == NULL) {
        printf("Erro de alocacao\n");
        fclose(f);
        return 1;
    }

    rewind(f);

    // Leitura do arquivo e construção do índice
    int i = 0;
    qt = fread(&e, sizeof(Endereco), 1, f);

    while (qt > 0) {
        // Copia os 8 bytes do CEP (dados binários)
        memcpy(a[i].cep, e.cep, 8);

        // Guarda a posição lógica
        a[i].posicao = i;

        qt = fread(&e, sizeof(Endereco), 1, f);
        i++;
    }

    // Ordena o índice pelo CEP => ela já existe , não precisa criar do zero
    qsort(a, tamanhoRegistros, sizeof(indiceEndereco), compara);

    // Debug: imprime os 10 primeiros
    printf("Os 10 primeiros CEPs do indice.dat e suas posicoes em cep_rj.dat abaixo: \n\n");
    for (int j = 0; j < 10 && j < tamanhoRegistros; j++) {
        printf("%.8s | %d\n", a[j].cep, a[j].posicao);
    }
    printf("salva em indice.dat\n");
    // Salva o índice em arquivo
    s = fopen("indice.dat", "wb");
    if (s == NULL) {
        printf("Erro ao criar indice.dat\n");
        free(a);
        fclose(f);
        return 1;
    }

    fwrite(a, sizeof(indiceEndereco), tamanhoRegistros, s);

    printf("Total Lido: %d\n", i);

    // Liberação de recursos
    free(a);
    fclose(s);
    fclose(f);

    return 0;
}