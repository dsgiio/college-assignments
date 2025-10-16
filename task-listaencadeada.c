#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int TIPOCHAVE; 

typedef struct {
    TIPOCHAVE chave;
} REGISTRO;

typedef struct aux {
    REGISTRO reg;        // dado armazenado no nó
    struct aux* prox;    // ponteiro para o próximo nó
} ELEMENTO;

typedef ELEMENTO* PONT;

// lista encadeada
typedef struct {
    PONT inicio;  
} LISTA;

void inicializarLista(LISTA* l) {
    l->inicio = NULL;
}

int tamanho(LISTA* l) {
    PONT end = l->inicio;
    int tam = 0;
    while (end != NULL) { // percorre até o final da lista
        tam++;
        end = end->prox;
    }
    return tam;
}

void exibirLista(LISTA* l) {
    PONT end = l->inicio;
    printf("Lista: \" ");
    while (end != NULL) {
        printf("%d ", end->reg.chave);
        end = end->prox;
    }
    printf("\"\n");
}

// Busca um elemento na lista pela chave
PONT buscaSequencial(LISTA* l, TIPOCHAVE ch) {
    PONT end = l->inicio;
    while (end != NULL) {
        if (end->reg.chave == ch) return end;
        end = end->prox;
    }
    return NULL;
}

bool inserirNoInicio(LISTA* l, REGISTRO reg) {
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    if (novo == NULL) return false; 

    novo->reg = reg;
    novo->prox = l->inicio;  // aponta para o antigo primeiro
    l->inicio = novo;        // novo elemento vira o primeiro
    return true;
}


bool inserirOrdenado(LISTA* l, REGISTRO reg) {
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    if (novo == NULL) return false;

    novo->reg = reg;
    PONT ant = NULL;
    PONT atual = l->inicio;

    // procurar posição correta (ordem crescente)
    while (atual != NULL && atual->reg.chave < reg.chave) {
        ant = atual;
        atual = atual->prox;
    }

    // caso chave já exista, não insere
    if (atual != NULL && atual->reg.chave == reg.chave) {
        free(novo);
        return false;
    }

    // inserção no início
    if (ant == NULL) {
        novo->prox = l->inicio;
        l->inicio = novo;
    } else { // inserção no meio ou fim
        novo->prox = ant->prox;
        ant->prox = novo;
    }
    return true;
}

bool excluirElemento(LISTA* l, TIPOCHAVE ch) {
    PONT ant = NULL;
    PONT atual = l->inicio;

    while (atual != NULL && atual->reg.chave < ch) {
        ant = atual;
        atual = atual->prox;
    }

    if (atual == NULL || atual->reg.chave != ch) return false; // não encontrado

    if (ant == NULL) { // remoção do primeiro elemento
        l->inicio = atual->prox;
    } else { // remoção do meio ou fim
        ant->prox = atual->prox;
    }

    free(atual); // libera memória
    return true;
}

void reinicializarLista(LISTA* l) {
    PONT end = l->inicio;
    while (end != NULL) {
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
    l->inicio = NULL;
}

int main() {
    LISTA l;
    REGISTRO reg;
    inicializarLista(&l);

    printf("Lista criada.\n");
    exibirLista(&l);

    // Inserções
    reg.chave = 10; inserirOrdenado(&l, reg);
    reg.chave = 5;  inserirOrdenado(&l, reg);
    reg.chave = 20; inserirOrdenado(&l, reg);
    reg.chave = 15; inserirOrdenado(&l, reg);

    printf("\nApós inserções ordenadas:\n");
    exibirLista(&l);
    printf("Tamanho: %d\n", tamanho(&l));

    // Busca
    TIPOCHAVE chaveBusca = 15;
    PONT encontrado = buscaSequencial(&l, chaveBusca);
    if (encontrado != NULL)
        printf("Elemento %d encontrado na lista!\n", chaveBusca);
    else
        printf("Elemento %d não encontrado.\n", chaveBusca);

    // Remoção
    printf("\nRemovendo elemento 10...\n");
    excluirElemento(&l, 10);
    exibirLista(&l);
    printf("Tamanho: %d\n", tamanho(&l));

    // Reinicialização
    printf("\nReinicializando lista...\n");
    reinicializarLista(&l);
    exibirLista(&l);
    printf("Tamanho: %d\n", tamanho(&l));

    return 0;
}
