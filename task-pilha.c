/* 
Funcionalidades a serem implementadas na estrutura PILHA
– Inserção (push), remoção (pop), exibição do topo (peek),
verificação se a pilha está vazia, verificação se a pilha está cheia.
*/

#include <stdio.h>
#define MAX 5 // tamanho máximo da pilha

// Definição da Pilha
typedef struct {
    int item[MAX]; // vetor que guarda os elementos
    int topo;      // índice do elemento do topo
} Pilha;

// Inicializa a pilha (vazia)
void inicializar(Pilha *p) {
    p->topo = -1; // topo = -1 significa "sem elementos"
}

// Verifica se está vazia
int vazia(Pilha *p) {
    return p->topo == -1;
}

// Verifica se está cheia
int cheia(Pilha *p) {
    return p->topo == MAX - 1;
}

// Inserir (push) → coloca um elemento no topo
void push(Pilha *p, int valor) {
    if(!cheia(p)) {
        p->topo++;               // anda para a próxima posição
        p->item[p->topo] = valor; // coloca o valor
        printf("Valor %d inserido na pilha!\n", valor);
    } else {
        printf("Pilha cheia! Nao é possível inserir %d\n", valor);
    }
}

// Remover (pop) → retira o elemento do topo
void pop(Pilha *p) {
    if(!vazia(p)) {
        printf("Removido: %d do topo\n", p->item[p->topo]);
        p->topo--; // volta uma posição
    } else {
        printf("Pilha vazia! Nada para remover.\n");
    }
}

// Topo (peek) → mostra o valor do topo, sem remover
void peek(Pilha *p) {
    if(!vazia(p)) {
        printf("Topo da pilha: %d\n", p->item[p->topo]);
    } else {
        printf("Pilha vazia!\n");
    }
}

// Exibir todos os elementos
void exibir(Pilha *p) {
    if(!vazia(p)) {
        printf("Elementos na pilha:\n");
        for(int i = p->topo; i >= 0; i--) {
            printf("Posicao %d: %d\n", i, p->item[i]);
        }
    } else {
        printf("Pilha vazia!\n");
    }
}

// Programa principal
int main() {
    Pilha p;
    inicializar(&p);

    push(&p, 10);
    push(&p, 20);
    push(&p, 30);

    exibir(&p);

    peek(&p); // mostra o topo

    pop(&p);
    exibir(&p);

    return 0;
}
