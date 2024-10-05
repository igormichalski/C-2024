#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 256 //Tamanho tabela ascii (0 a 255)

//Foi utilizado esse curso para aprender os algortimos e como armazenar em arquivo utilizando os bits corretamente
//Referencia: https://www.youtube.com/watch?v=o8UPZ_KDWdU&list=PLqJK4Oyr5WShtxF1Ch3Vq4b1Dzzb-WxbP

typedef struct no {
    unsigned char caracter;
    int frequencia;
    struct no *esq, *dir, *proximo;
} No;

typedef struct {
    No *inicio;
    int tam;
} Lista;

void inicializaTabelaComZero(unsigned int tab[]) {
    for (int i = 0; i < TAM; i++) {
        tab[i] = 0;
    }
}

void preencheTabFrequencia(unsigned char data[], size_t size, unsigned int tab[]) {
    for (size_t i = 0; i < size; i++) {
        tab[data[i]]++;
    }
}

void criarLista(Lista *lista) {
    lista->inicio = NULL;
    lista->tam = 0;
}

void inserirListaOrdenado(Lista *lista, No *no) {
    if (lista->inicio == NULL) {
        lista->inicio = no;
    } else if (no->frequencia < lista->inicio->frequencia) {
        no->proximo = lista->inicio;
        lista->inicio = no;
    } else {
        No *aux = lista->inicio;
        while (aux->proximo != NULL && aux->proximo->frequencia <= no->frequencia) {
            aux = aux->proximo;
        }
        no->proximo = aux->proximo;
        aux->proximo = no;
    }
    lista->tam++;
}

void preencherLista(unsigned int tab[], Lista *lista) {
    No *novo;
    for (int i = 0; i < TAM; i++) {
        if (tab[i] > 0) {
            novo = malloc(sizeof(No));
            if (novo) {
                novo->caracter = i;
                novo->frequencia = tab[i];
                novo->dir = NULL;
                novo->esq = NULL;
                novo->proximo = NULL;
                inserirListaOrdenado(lista, novo);
            } else {
                printf("Erro preencherLista");
                return;
            }
        }
    }
}

No *removeNoInicio(Lista *lista) {
    No *aux = NULL;
    if (lista->inicio != NULL) {
        aux = lista->inicio;
        lista->inicio = lista->inicio->proximo;
        aux->proximo = NULL;
        lista->tam--;
    }
    return aux;
}

No *montarArvore(Lista *lista) {
    No *primeiro, *segundo, *novo;
    while (lista->tam > 1) {
        primeiro = removeNoInicio(lista);
        segundo = removeNoInicio(lista);
        novo = malloc(sizeof(No));
        if (novo) {
            novo->caracter = '=';
            novo->frequencia = primeiro->frequencia + segundo->frequencia;
            novo->esq = primeiro;
            novo->dir = segundo;
            novo->proximo = NULL;
            inserirListaOrdenado(lista, novo);
        } else {
            printf("Erro montarArvore\n");
            exit(1);
        }
    }
    return lista->inicio;
}

int alturaArvore(No *raiz) {
    int esq, dir;

    if (raiz == NULL) {
        return -1;
    } else {
        esq = alturaArvore(raiz->esq) + 1;
        dir = alturaArvore(raiz->dir) + 1;
        if (esq > dir)
            return esq;
        else
            return dir;
    }
}

char **alocaDicionario(int colunas) {
    char **dicionario;

    dicionario = malloc(TAM * sizeof(char *));
    for (int i = 0; i < TAM; i++)
        dicionario[i] = calloc(colunas, sizeof(char));

    return dicionario;
}

void gerarDicionario(char **dicionario, No *raiz, char *caminho, int colunas) {
    char esquerda[colunas], direita[colunas];
    if (raiz->esq == NULL && raiz->dir == NULL) {
        strcpy(dicionario[raiz->caracter], caminho);
    } else {
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        strcat(esquerda, "0");
        strcat(direita, "1");

        gerarDicionario(dicionario, raiz->esq, esquerda, colunas);
        gerarDicionario(dicionario, raiz->dir, direita, colunas);
    }
}

int getSerializedTreeSize(No *node) {
    if (node->esq == NULL && node->dir == NULL) {
        return 2; // '1' + character
    } else {
        return 1 + getSerializedTreeSize(node->esq) + getSerializedTreeSize(node->dir); // '0' + left + right
    }
}

void serializeTree(No *node, FILE *file) {
    if (node->esq == NULL && node->dir == NULL) {
        fputc('1', file);
        fputc(node->caracter, file);
    } else {
        fputc('0', file);
        serializeTree(node->esq, file);
        serializeTree(node->dir, file);
    }
}

No *deserializeTree(FILE *file) {
    int c = fgetc(file);
    if (c == EOF) {
        printf("Erro ao deserializar a árvore.\n");
        exit(1);
    }
    if (c == '1') {
        int ch = fgetc(file);
        if (ch == EOF) {
            printf("Erro ao deserializar a árvore.\n");
            exit(1);
        }
        No *node = malloc(sizeof(No));
        node->caracter = ch;
        node->esq = NULL;
        node->dir = NULL;
        node->proximo = NULL;
        return node;
    } else if (c == '0') {
        No *node = malloc(sizeof(No));
        node->caracter = 0;
        node->proximo = NULL;
        node->esq = deserializeTree(file);
        node->dir = deserializeTree(file);
        return node;
    } else {
        printf("Erro ao deserializar a árvore.\n");
        exit(1);
    }
}

char *codificarData(char **dicionario, unsigned char *data, size_t dataSize, int *totalBits) {
    size_t i;
    size_t tam = 0;
    for (i = 0; i < dataSize; i++) {
        tam += strlen(dicionario[data[i]]);
    }

    char *codigo = calloc(tam + 1, sizeof(char));
    if (!codigo) {
        printf("Erro de alocação de memória\n");
        exit(1);
    }

    codigo[0] = '\0';
    for (i = 0; i < dataSize; i++) {
        strcat(codigo, dicionario[data[i]]);
    }

    *totalBits = tam;
    return codigo;
}

void writeCompressedData(char *codigo, FILE *outputFile) {
    unsigned char byte = 0, mascara;
    int i = 0, bitPos = 7;
    int codigoLen = strlen(codigo);

    while (i < codigoLen) {
        mascara = 1;
        if (codigo[i] == '1') {
            mascara = mascara << bitPos;
            byte = byte | mascara;
        }
        bitPos--;

        if (bitPos < 0) {
            fwrite(&byte, sizeof(unsigned char), 1, outputFile);
            byte = 0;
            bitPos = 7;
        }
        i++;
    }

    if (bitPos != 7) {
        fwrite(&byte, sizeof(unsigned char), 1, outputFile);
    }
}

unsigned int bitUm(unsigned char byte, int i) {
    unsigned char mascara = (1 << i);
    return byte & mascara;
}

unsigned char *decodeData(unsigned char *compressedData, int totalBits, No *arvore, size_t *decodedDataSize) {
    int bitsRead = 0;
    No *aux = arvore;
    unsigned char *decodedData = (unsigned char *)malloc(totalBits);
    size_t decodedIndex = 0;
    size_t byteIndex = 0;
    unsigned char currentByte = compressedData[byteIndex];

    while (bitsRead < totalBits) {
        int bitPos = 7 - (bitsRead % 8);
        if (bitUm(currentByte, bitPos))
            aux = aux->dir;
        else
            aux = aux->esq;

        if (aux->esq == NULL && aux->dir == NULL) {
            decodedData[decodedIndex++] = aux->caracter;
            aux = arvore;
        }

        bitsRead++;
        if (bitsRead % 8 == 0 && bitsRead < totalBits) {
            byteIndex++;
            currentByte = compressedData[byteIndex];
        }
    }

    *decodedDataSize = decodedIndex;
    return decodedData;
}

unsigned char *readFile(const char *filename, size_t *size) {
    FILE *file = fopen(filename, "rb");
    unsigned char *buffer;
    size_t fileSize;

    if (!file) {
        printf("Não foi possível abrir o arquivo %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    rewind(file);

    buffer = (unsigned char *)malloc(fileSize * sizeof(unsigned char));
    if (!buffer) {
        printf("Erro de memória\n");
        fclose(file);
        return NULL;
    }

    fread(buffer, sizeof(unsigned char), fileSize, file);

    fclose(file);

    *size = fileSize;
    return buffer;
}

void compressFile(char *filename) {
    unsigned char *data;
    size_t dataSize;
    unsigned int tabela_frequencia[TAM];
    Lista lista;
    No *arvore;
    int colunas;
    char **dicionario, *codificado;
    char inputFilename[256], outputFilename[256];
    FILE *outputFile;
    int treeSize, totalBits;

    //Adicionar ".txt" ao nome do arquivo de entrada
    snprintf(inputFilename, sizeof(inputFilename), "%s.txt", filename);

    data = readFile(inputFilename, &dataSize);
    if (!data) {
        printf("Falha ao ler o arquivo de entrada.\n");
        return;
    }

    inicializaTabelaComZero(tabela_frequencia);
    preencheTabFrequencia(data, dataSize, tabela_frequencia);

    criarLista(&lista);
    preencherLista(tabela_frequencia, &lista);
    arvore = montarArvore(&lista);

    colunas = alturaArvore(arvore) + 1;
    dicionario = alocaDicionario(colunas);
    gerarDicionario(dicionario, arvore, "", colunas);

    codificado = codificarData(dicionario, data, dataSize, &totalBits);

    //Definir o nome do arquivo de saída com ".cmp"
    snprintf(outputFilename, sizeof(outputFilename), "%s.cmp", filename);
    outputFile = fopen(outputFilename, "wb");
    if (!outputFile) {
        printf("Falha ao abrir o arquivo de saída.\n");
        return;
    }

    treeSize = getSerializedTreeSize(arvore);

    fwrite(&treeSize, sizeof(int), 1, outputFile);

    serializeTree(arvore, outputFile);

    fwrite(&totalBits, sizeof(int), 1, outputFile);

    writeCompressedData(codificado, outputFile);

    fclose(outputFile);

    free(data);
    free(codificado);
    for (int i = 0; i < TAM; i++) {
        free(dicionario[i]);
    }
    free(dicionario);
}

void decompressFile(char *filename) {
    char inputFilename[256];
    char outputFilename[256];
    FILE *inputFile, *outputFile;
    int treeSize, totalBits;
    No *arvore;
    unsigned char *compressedData;
    size_t compressedDataSize;
    unsigned char *decodedData;
    size_t decodedDataSize;

    //Adicionar ".cmp" ao nome do arquivo de entrada
    snprintf(inputFilename, sizeof(inputFilename), "%s.cmp", filename);
    //Definir o nome do arquivo de saída com ".dcmp"
    snprintf(outputFilename, sizeof(outputFilename), "%s.dcmp", filename);

    inputFile = fopen(inputFilename, "rb");
    if (!inputFile) {
        printf("Falha ao abrir o arquivo de entrada.\n");
        return;
    }

    fread(&treeSize, sizeof(int), 1, inputFile);

    arvore = deserializeTree(inputFile);

    fread(&totalBits, sizeof(int), 1, inputFile);

    compressedDataSize = ((totalBits + 7) / 8);
    compressedData = (unsigned char *)malloc(compressedDataSize);
    if (!compressedData) {
        printf("Erro de alocação de memória\n");
        fclose(inputFile);
        return;
    }

    fread(compressedData, sizeof(unsigned char), compressedDataSize, inputFile);

    fclose(inputFile);

    decodedData = decodeData(compressedData, totalBits, arvore, &decodedDataSize);

    outputFile = fopen(outputFilename, "wb");
    if (!outputFile) {
        printf("Falha ao abrir o arquivo de saída.\n");
        free(compressedData);
        free(decodedData);
        return;
    }

    fwrite(decodedData, sizeof(unsigned char), decodedDataSize, outputFile);
    fclose(outputFile);

    free(compressedData);
    free(decodedData);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s [c|d] nome_do_arquivo_sem_extensao\n", argv[0]);
        return 1;
    }

    char option = argv[1][0];
    char *filename = argv[2];

    if (option == 'c') {
        compressFile(filename);
    } else if (option == 'd') {
        decompressFile(filename);
    } else {
        printf("Opção inválida. Use 'c' para compactar ou 'd' para descompactar.\n");
        return 1;
    }

    return 0;
}
