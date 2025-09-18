/* Funcionalidades a serem implementadas na estrutura FILA
– Inserção, remoção, exibição dos elementos e suas respectivas posições
na fila, verificação se a fila está vazia, verificação se a fila está cheia,
localização de um elemento, retornando -1 se não estiver na fila e, a
posição do elemento caso esteja na FILA. */

#include <stdio.h>
#define MAX 5

typedef struct {
    int item[MAX]; // vetor que guarda os elementos da fila
    int inicio;    
    int fim;       
} Fila;

void inicializar(Fila *f){ 
    f->inicio = 0;  // o início começa no índice 0
    f->fim = -1;    // fim = -1 significa "sem elementos ainda"
}

int vazia(Fila *f){
    return f->inicio > f->fim; // se o início ultrapassar o fim, está vazia
}

int cheia(Fila *f){
    return f->fim == MAX - 1; // se o fim chegou na última posição do vetor
}

void inserir(Fila *f, int valor){
    if(!cheia(f)){ // só insere se não estiver cheia
        f->fim++;                 // move o fim para a próxima posição
        f->item[f->fim] = valor;  // coloca o valor na fila
        printf("Valor %d inserido na posicao %d\n", valor, f->fim);
    } else {
        printf("Fila cheia! Nao é possível inserir %d\n", valor);
    }
}

void remover(Fila *f){
    if(!vazia(f)){ // só remove se não estiver vazia
        printf("Removido: %d da posicao %d\n", f->item[f->inicio], f->inicio);
        f->inicio++; // anda com o início para frente
    } else {
        printf("Fila vazia! Nada para remover.\n");
    }
}

void exibir(Fila *f){
    if(!vazia(f)){
        printf("Elementos na fila:\n");
        for(int i = f->inicio; i <= f->fim; i++){
            printf("Posicao %d: %d\n", i, f->item[i]);
        }
    } else {
        printf("Fila vazia!\n");
    }
}

int localizar(Fila *f, int valor){
    for(int i = f->inicio; i <= f->fim; i++){
        if(f->item[i] == valor){
            return i; // retorna a posição encontrada
        }
    }
    return -1; // não encontrado
}

int main() {
    Fila f;
    inicializar(&f); // cria fila vazia

    inserir(&f, 80);
    inserir(&f, 16);
    inserir(&f, 30);

    exibir(&f);

    remover(&f);
    exibir(&f);

    int pos = localizar(&f, 30);
    if (pos != -1)
        printf("Elemento 30 encontrado na posicao %d\n", pos);
    else
        printf("Elemento 30 não encontrado\n");

    return 0;
}
