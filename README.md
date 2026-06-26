# Organização de Estrutura de Arquivos

Projeto desenvolvido para a disciplina **Organização de Estrutura de Arquivos**.

## 📂 Estrutura de Pastas

1. **Busca Binária - Arquivo CEP**
2. **Índice Ordenado CEP**
3. **Ordenação Externa - Diversos Blocos**
4. **Processamento de CSV / Covid**
5. **CEP indexado com Árvore B - ISAM**
6. **Pasta de dados**

## 📊 Arquivos de Dados Originais

Os arquivos utilizados neste projeto são grandes e não podem ser enviados diretamente para o GitHub.  
Eles devem ser colocados na pasta *dados* após o download.

📥 [Baixar pasta completa de dados](https://1drv.ms/f/c/4e3f140390335b22/IgCmw160OfjaSqiqhbeQM0F9AWTXGiy2EDoYxYabqkyrjug?e=wCGc5S)

### Arquivos principais
- cep.dat  
- cep-ordenado.dat  
- owid-covid-data.csv  

### Arquivos extras (versões reduzidas)
1. cep_rj.dat (Apenas os CEPs do estado do Rio de Janeiro)  
2. cep_rj_ordenado.dat (CEPs do RJ ordenados)  
3. owid-covid-data-american-continent.csv (Dados apenas do continente americano)

## 🚀 Como usar

1. Clone este repositório:
```bash
   git clone https://github.com/MariaLuizaBertin/Organizacao-de-Estruturas-de-Arquivos.git
```
### Busca Binária 
Implementa busca binária diretamente sobre um arquivo ordenado.
```bash
cd busca_binaria_Cep
```
Compile:
```bash
gcc -o busca busca.c
```
Execute:
```bash
./busca 01001000
```
### Busca CEP com Índice Ordenado
Cria um arquivo de índice ordenado e realiza buscas através dele.
```bash
cd busca_Cep_com_indice
```
Compile:
```bash
gcc -o criaIndice criaIndice.c
gcc -o buscaEmIndice buscaEmIndice.c
```
Execute:
```bash
./criaIndice
./buscaEmIndice 01001000
```
### Ordenação Externa
Divide um arquivo grande em blocos ordenados e realiza intercalação.
Entre na pasta:
```bash
cd intercala
```
Compile:
```bash
gcc -o divideArquivo divideArquivo.c
gcc -o intercala intercala.c
```
Execute:
```bash
./divideArquivo
./intercala
```

### Processamento CSV
Mostra o total de casos e mortes de Covid-19 na América do Sul.
Entre na pasta:
```bash
cd processamento_de_CSV_Covid
```
Compile:
```bash
gcc -o ProcessaCSV ProcessaCSV.c
```
Execute:
```bash
./ProcessaCSV
```
### Árvore B (ISAM)
Constrói um índice utilizando Árvore B para acelerar buscas por CEP.
Entre na pasta:
```bash
cd indexado_arvoreb
```
Compile:
```bash
gcc -o aleatorizaCep aleatorizaCep.c ArvoreB.c
gcc -o criaArvoreB criaArvoreB.c ArvoreB.c
gcc -o joinArvoreBcomCep joinArvoreBcomCep.c ArvoreB.c
```
Execute:
```bash
./aleatorizaCep
./criaArvoreB
./joinArvoreBcomCep
```
## 👩‍💻 Autoria

Projeto desenvolvido por:

- MariaLuizaBertin

Alguns módulos foram desenvolvidos em grupo durante a disciplina, conforme indicado na tabela abaixo.

| Módulo | Participantes |
|--------|---------------|
| Busca Binária - Arquivo CEP | Maria Luiza Bertin |
| Índice Ordenado CEP | Maria Luiza Bertin |
| Ordenação Externa - Diversos Blocos | Maria Luiza Bertin |
| Processamento de CSV / Covid | Maria Luiza Bertin, Rafael Barrionuevo de Souza, Leticia Mendonca dos Santos, Erick Ricardo Baiao Batista Pereira, Gustavo Andrade de Souza, Matheus Alexandre Ferreira Leite |
| CEP Indexado com Árvore B - ISAM | Maria Luiza Bertin, Rafael Barrionuevo de Souza, Leticia Mendonca dos Santos, Erick Ricardo Baiao Batista Pereira, Gustavo Andrade de Souza, Matheus Alexandre Ferreira Leite |
