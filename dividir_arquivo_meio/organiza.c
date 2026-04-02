#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

void intercala(const void *arq1, const void *arq2,const void *arqS){
	FILE *a, *b, *s;
	Endereco ea, eb;

	a = fopen(arq1, "rb");
	b = fopen(arq2, "rb");
	s = fopen(arqS, "wb");

	if(a == NULL || b == NULL || s == NULL){
        printf("Erro ao abrir 1 ou mais arquivos.\n");
        return;
    }

	// leitura inicial
	fread(&ea,sizeof(Endereco),1,a);
	fread(&eb,sizeof(Endereco),1,b);

	// eof -> End Of File => diz que é fim do arquivo => dps de uma tentativa de leitura frustada (malsucedida ou parcial)
    // Não pode testar EOF antes de testar ler pelo menos 1 vez
	while(!feof(a) && !feof(b))
	{
		if(compara(&ea,&eb)<0) // ea < eb
		{
			fwrite(&ea,sizeof(Endereco),1,s);
			fread(&ea,sizeof(Endereco),1,a);
		}
		else // ea >= eb
		{
			fwrite(&eb,sizeof(Endereco),1,s);
			fread(&eb,sizeof(Endereco),1,b);
		}
	}
	// despeja o resto do arquivo A
	while(!feof(a))
	{
		fwrite(&ea,sizeof(Endereco),1,s);
		fread(&ea,sizeof(Endereco),1,a);		
	}
	// despeja o resto do arquivo B
	while(!feof(b))
	{
		fwrite(&eb,sizeof(Endereco),1,s);
		fread(&eb,sizeof(Endereco),1,b);		
	}

	fclose(a);
	fclose(b);
	fclose(s);
}

int main(int argc, char** argv)
{
    char nome1[80], nome2[80], saida[80];

	//arquivos da rodada atual
	sprintf(nome1, "b0.dat");
	sprintf(nome2, "b1.dat");
	// novo arquivo de saida
	sprintf(saida, "saida.dat");
	intercala(nome1,nome2,saida);


	printf("%s e %s criaram arquivo=>  %s\n",nome1,nome2, saida);
	printf("Arquivo final: %s\n", saida);
    return 0;

}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int main(int argc, char** argv)
{
	FILE *a, *b, *saida;
	Endereco ea, eb;

	a = fopen("cep_a.dat","rb");
	b = fopen("cep_b.dat","rb");
	saida = fopen("saida.dat","wb");

	fread(&ea,sizeof(Endereco),1,a);
	fread(&eb,sizeof(Endereco),1,b);

	// eof -> End Of File
	while(!feof(a) && !feof(b))
	{
		if(compara(&ea,&eb)<0) // ea < eb
		{
			fwrite(&ea,sizeof(Endereco),1,saida);
			fread(&ea,sizeof(Endereco),1,a);
		}
		else // ea >= eb
		{
			fwrite(&eb,sizeof(Endereco),1,saida);
			fread(&eb,sizeof(Endereco),1,b);
		}
	}

	while(!feof(a))
	{
		fwrite(&ea,sizeof(Endereco),1,saida);
		fread(&ea,sizeof(Endereco),1,a);		
	}
	
	while(!feof(b))
	{
		fwrite(&eb,sizeof(Endereco),1,saida);
		fread(&eb,sizeof(Endereco),1,b);		
	}

	fclose(a);
	fclose(b);
	fclose(saida);
}

*/