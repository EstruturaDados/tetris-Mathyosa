#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Estrutura principal do jogo


// Cada peça tem um nome ('I','O','T','L') e um id único.
typedef struct {
    char nome;
    int id;
} Peca;

// Fila circular com tamanho fixo 5
#define TAM_FILA 5
Peca fila[TAM_FILA];
int inicio = 0, fim = 0, quantidade = 0;

// Pilha com capacidade 3
#define TAM_PILHA 3
Peca pilha[TAM_PILHA];
int topo = -1;

// Variável global para gerar ID único
int proximoID = 0;

// Tipos possíveis de peças
char tipos[] = {'I', 'O', 'T', 'L'};


// Funções para manipular fila e pilha


// Gera uma nova peça com nome aleatório e ID unico
Peca gerarPeca() {
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = proximoID++;
    return nova;
}

// Insere peça no fim da fila circular
void enqueue(Peca p) {
    if (quantidade == TAM_FILA) return;  // a fila sempre fica cheia
    fila[fim] = p;
    fim = (fim + 1) % TAM_FILA;
    quantidade++;
}

// Remove peça da frente da fila circular
Peca dequeue() {
    Peca removida = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    quantidade--;
    return removida;
}

// Empilha peça
int push(Peca p) {
    if (topo == TAM_PILHA - 1) return 0;  // pilha cheia
    pilha[++topo] = p;
    return 1;
}

// Desempilha peça
int pop(Peca *p) {
    if (topo == -1) return 0;  // pilha vazia
    *p = pilha[topo--];
    return 1;
}


// Exibe o estado atual da fila e da pilha

void exibirEstado() {
    printf("\n----------------------------------------------\n");
    printf("Estado atual:\n");

    // Fila
    printf("Fila de peças:\t");
    int i = inicio;
    for (int c = 0; c < quantidade; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");

    // Pilha
    printf("Pilha reserva (Topo -> Base): ");
    for (int j = topo; j >= 0; j--) {
        printf("[%c %d] ", pilha[j].nome, pilha[j].id);
    }
    printf("\n----------------------------------------------\n");
}

// -------------------------------
// AÇÕES DO JOGO
// -------------------------------

// Jogar peça (remove da fila de peças)
void jogarPeca() {
    if (quantidade == 0) {
        printf("A fila está vazia!\n");
        return;
    }

    Peca jogada = dequeue();
    printf("Peça jogada: [%c %d]\n", jogada.nome, jogada.id);

    // Repõe a peça automaticamente
    enqueue(gerarPeca());
}

// Reservar peça (vai da fila para pilha)
void reservarPeca() {
    if (quantidade == 0) {
        printf("A fila está vazia!\n");
        return;
    }
    if (topo == TAM_PILHA - 1) {
        printf("A pilha de reserva está cheia!\n");
        return;
    }

    Peca movida = dequeue();
    push(movida);

    printf("Peça [%c %d] movida para a pilha de reserva.\n", movida.nome, movida.id);

    // Repor peça automaticamente
    enqueue(gerarPeca());
}

// 3 Usar peça reservada (da pilha para o jogo)
void usarReservada() {
    Peca usada;
    if (!pop(&usada)) {
        printf("Nenhuma peça reservada para usar!\n");
        return;
    }

    printf("Peça reservada usada: [%c %d]\n", usada.nome, usada.id);
}

// Troca simples entre fila (frente) e pilha (topo)
void trocarSimples() {
    if (quantidade == 0 || topo == -1) {
        printf("Não é possível trocar (faltam peças).\n");
        return;
    }

    Peca temp = fila[inicio];
    fila[inicio] = pilha[topo];
    pilha[topo] = temp;

    printf("Troca simples entre fila e pilha realizada.\n");
}

// Troca múltipla (3 da fila por 3 da pilha)
void trocaMultipla() {
    if (quantidade < 3 || topo < 2) {
        printf("Não é possível trocar (é preciso ter 3 peças na fila e 3 na pilha).\n");
        return;
    }

    int posFila = inicio;

    for (int i = 0; i < 3; i++) {
        Peca temp = fila[posFila];
        fila[posFila] = pilha[topo - i];
        pilha[topo - i] = temp;

        posFila = (posFila + 1) % TAM_FILA;
    }

    printf("Troca múltipla (3 peças) realizada com sucesso!\n");
}


// Menu principal

void menu() {
    int opcao;

    do {
        exibirEstado();
        printf("\nOpções disponíveis:\n");
        printf("1 - Jogar peça da fila\n");
        printf("2 - Reservar peça na pilha\n");
        printf("3 - Usar peça reservada\n");
        printf("4 - Trocar peça da fila com topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com os 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: jogarPeca(); break;
            case 2: reservarPeca(); break;
            case 3: usarReservada(); break;
            case 4: trocarSimples(); break;
            case 5: trocaMultipla(); break;
            case 0: printf("Encerrando o programa...\n"); break;
            default: printf("Opção inválida!\n");
        }

    } while (opcao != 0);
}

// -------------------------------
// Estrutura basica do programa

int main() {
    srand(time(NULL));

    // Preencher a fila inicialmente
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(gerarPeca());
    }

    menu();
    return 0;
}
