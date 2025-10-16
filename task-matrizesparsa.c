#include <stdio.h>
#include<malloc.h>
#include <stdbool.h>

typedef struct tempNo{
    float valor;
    int coluna;
    struct tempNo* prox;
}NO;

typedef NO* PONT;

typedef struct{
    PONT* A; //vetor de listas
    int nlinhas;
    int ncolunas;
}MATRIZ;

typedef struct {
    PONT* A; // vetor de listas (cada linha)
    int nlinhas;
    int ncolunas;
} MATRIZ;

void inicializarMatriz(MATRIZ* m, int nlinhas, int ncolunas) {
    m->nlinhas = nlinhas;
    m->ncolunas = ncolunas;
    m->A = (PONT*) malloc(nlinhas * sizeof(PONT));
    if (m->A == NULL) {
        printf("Erro ao alocar memória para as linhas.\n");
        return;
    }
    for (int i = 0; i < nlinhas; i++) {
        m->A[i] = NULL;
    }
}

bool atribuirValor(MATRIZ* m, int linha, int coluna, float valor) {
    if (linha < 0 || linha >= m->nlinhas || coluna < 0 || coluna >= m->ncolunas)
        return false;

    PONT ant = NULL;
    PONT atual = m->A[linha];

    // procurar posição correta (ordenado por coluna)
    while (atual != NULL && atual->coluna < coluna) {
        ant = atual;
        atual = atual->prox;
    }

    if (atual != NULL && atual->coluna == coluna) {
        if (valor == 0) {
            // remover elemento
            if (ant == NULL)
                m->A[linha] = atual->prox;
            else
                ant->prox = atual->prox;
            free(atual);
        } else {
            // atualizar valor
            atual->valor = valor;
        }
    } else {
        if (valor != 0) {
            // inserir novo elemento
            PONT novo = (PONT) malloc(sizeof(NO));
            if (novo == NULL) return false;
            novo->valor = valor;
            novo->coluna = coluna;
            novo->prox = atual;
            if (ant == NULL)
                m->A[linha] = novo;
            else
                ant->prox = novo;
        }
    }
    return true;
}

float acessarValor(MATRIZ* m, int linha, int coluna) {
    if (linha < 0 || linha >= m->nlinhas || coluna < 0 || coluna >= m->ncolunas)
        return 0;

    PONT atual = m->A[linha];
    while (atual != NULL && atual->coluna < coluna) {
        atual = atual->prox;
    }
    if (atual != NULL && atual->coluna == coluna) {
        return atual->valor;
    } else {
        return 0;
    }
}

int main() {
    MATRIZ m;
    inicializarMatriz(&m, 5, 5);
    atribuirValor(&m, 1, 2, 3.5);
    atribuirValor(&m, 3, 4, 7.2);

    printf("Valor na posicao (1,2): %.2f\n", acessarValor(&m, 1, 2));
    printf("Valor na posicao (3,4): %.2f\n", acessarValor(&m, 3, 4));
    printf("Valor na posicao (0,0): %.2f\n", acessarValor(&m, 0, 0));

    return 0;
}