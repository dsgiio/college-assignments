#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
}REGISTRO;

typedef struct aux{
    REGISTRO reg;
    struct aux *prox;
}ELEMENTO;

typedef ELEMENTO* PONT;

//pilha 
typedef struct {
    PONT topo;
}PILHA;

void inicializarPilha(PILHA* p){
    p -> topo = NULL;
}

int tamanhoPilha(PILHA* p){
    PONT end = p->topo;
    int tam =0;
    while(end != NULL){
        tam++;
        end = end -> prox;
    }
    return tam;
}

bool pilhaVazia(PILHA *p){
    if(p->topo == NULL) return true;
    else return false;
}

void exibicao(PILHA *p){
    PONT end = p->topo;
    printf("Pilha: \" ");
    while(end != NULL){
        printf("%d ", end->reg.chave);
        end = end -> prox;
    }
    printf("\"\n");
}

bool inserir(PILHA *p, REGISTRO reg){
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    novo -> reg = reg;
    novo -> prox = p ->topo;
    p -> topo = novo;
    return true;
}

bool remover(PILHA *p, REGISTRO *reg){
    if (p->topo == NULL) return false;
    *reg = p->topo->reg;
    PONT apagar = p->topo;
    p->topo = p->topo->prox;
    free(apagar);
    return true;
}

void reinicializar(PILHA *p){
    PONT apagar;
    PONT posicao = p->topo;
    while(posicao != NULL){
        apagar = posicao;
        posicao = posicao -> prox;
        free(apagar);
    }
    p->topo = NULL;
}

int main(){
    PILHA p;
    REGISTRO reg;
    inicializarPilha(&p);
    printf("Tamanho: %d\n", tamanhoPilha(&p));
    exibicao(&p);
    printf("Pilha vazia: %s\n", pilhaVazia(&p) ? "sim" : "nao");

    reg.chave = 10;
    inserir(&p, reg);
    reg.chave = 20;
    inserir(&p, reg);
    reg.chave = 30;
    inserir(&p, reg);
    printf("Tamanho: %d\n", tamanhoPilha(&p));
    exibicao(&p);
    printf("Pilha vazia: %s\n", pilhaVazia(&p) ? "sim" : "nao");

    if(remover(&p, &reg)){
        printf("Removido: %d\n", reg.chave);
    } else {
        printf("Erro ao remover!\n");
    }
    printf("Tamanho: %d\n", tamanhoPilha(&p));
    exibicao(&p);

    reinicializar(&p);
    printf("Tamanho: %d\n", tamanhoPilha(&p));
    exibicao(&p);
    printf("Pilha vazia: %s\n", pilhaVazia(&p) ? "sim" : "nao");

    return 0;
}