/*Um deque é uma fila com duas pontas, onde você pode inserir e remover tanto no início quanto no fim.
Ele é implementado com uma lista duplamente encadeada circular — ou seja, cada nó aponta para o anterior e o próximo, e o último volta para o primeiro.*/
#include <stdio.h>
#include<malloc.h>
#include <stdbool.h>

typedef TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
}REGISTRO;

typedef struct auxElem{
    REGISTRO reg; //valor armazenado
    struct auxElem* ant; 
    struct auxElem* prox;
}ELEMENTO;
typedef ELEMENTO* PONT;

//deque
typedef struct {
    PONT cabeca;
}DEQUE;

//cria o nó cabeca e faz ele apontar para ele mesmo
void inicializarDeque(DEQUE* d){
    d -> cabeca = (PONT) malloc(sizeof(ELEMENTO));
    d -> cabeca -> prox = d -> cabeca;
    d -> cabeca -> ant = d -> cabeca;
}

int tamanho(DEQUE *d){
    PONT end= d->cabeca->prox;
    int tam =0;
    while(end != d->cabeca){
        tam++;
        end = end -> prox;
    }
    return tam;
}

void exibicao(DEQUE *d){
    PONT end = d->cabeca->ant;
    printf("Deque: \" ");
    while(end != d->cabeca){
        printf("%d ", end->reg.chave);
        end = end -> ant;
    }
    printf("\"\n");
}

//Insere um novo nó após a cabeça e atualiza os ponteiros.
bool inserir(DEQUE *d, REGISTRO reg){
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    novo -> reg = reg;
    novo -> prox = d -> cabeca;
    novo -> ant = d -> cabeca -> ant;
    d -> cabeca -> ant = novo;
    novo -> ant -> prox = novo;
    return true;
}

//Remove o primeiro nó e atualiza os ponteiros da cabeça.
bool remover(DEQUE *d, REGISTRO *reg){
    if(d->cabeca->prox == d->cabeca) return false;
    PONT apagar = d -> cabeca -> prox;
    *reg = apagar -> reg;
    d -> cabeca -> prox = apagar -> prox;
    apagar -> prox -> ant = d -> cabeca;
    free(apagar);
    return true;
}

void reinicializar(DEQUE *d){
    PONT end = d->cabeca->prox;
    while(end != d->cabeca){
        PONT apagar = end;
        end = end -> prox;
        free(apagar);
    }
    d -> cabeca -> prox = d -> cabeca;
    d -> cabeca -> ant = d -> cabeca;
}

int main(){
    DEQUE d;
    REGISTRO reg;
    inicializarDeque(&d);
    for(int i=1; i<=5; i++){
        reg.chave = i;
        inserir(&d, reg);
    }
    exibicao(&d);
    printf("Tamanho: %d\n", tamanho(&d));
    for(int i=1; i<=3; i++){
        remover(&d, &reg);
        printf("Removido: %d\n", reg.chave);
    }
    exibicao(&d);
    printf("Tamanho: %d\n", tamanho(&d));
    reinicializar(&d);
    exibicao(&d);
    printf("Tamanho: %d\n", tamanho(&d));
    return 0;
}

