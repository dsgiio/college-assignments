#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
}REGISTRO;

typedef struct aux{
    REGISTRO reg;
    struct aux* prox;
}ELEMENTO;

typedef ELEMENTO* PONT;

//fila
typedef struct {
    PONT inicio;
    PONT fim;
}FILA;

void inicializar(FILA* f){
    f ->inicio = NULL;
    f -> fim = NULL;
}

int tamanho(FILA *f){
    PONT end = f->inicio;
    int tam =0;
    while(end != NULL){
        tam++;
        end = end ->prox;
    }
    return tam;
}

void exibicao(FILA *f){
    PONT end = f->inicio;
    printf("Fila: \" ");
    while(end != NULL){
        printf("%d ", end->reg.chave);
        end = end -> prox;
    }
    printf("\"\n");
}

bool inserirNaFila(FILA *f, REGISTRO reg) {
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    if (novo == NULL) return false;  // check for malloc failure
    novo->reg = reg;
    novo->prox = NULL;
    if (f->inicio == NULL) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
    return true;
}

bool excluir(FILA *f, REGISTRO *reg) {
    if (f->inicio == NULL) return false;
    *reg = f->inicio->reg;
    PONT apagar = f->inicio;
    f->inicio = f->inicio->prox;
    free(apagar);
    if (f->inicio == NULL) f->fim = NULL;
    return true;
}

void reinicializar(FILA *f) {
    PONT end = f->inicio;
    while (end != NULL) {
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
    f->inicio = NULL;
    f->fim = NULL;
}

int main() {
    FILA fila;
    REGISTRO reg;
    inicializar(&fila);

    // Testando a fila
    for (int i = 1; i <= 5; i++) {
        reg.chave = i;
        inserirNaFila(&fila, reg);
        exibicao(&fila);
    }

    while (excluir(&fila, &reg)) {
        printf("Removido: %d\n", reg.chave);
        exibicao(&fila);
    }

    reinicializar(&fila);
    return 0;
}
