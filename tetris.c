#include <stdio.h>
#include <stdlib.h>


//Criando jogo Tetris Stack

//Fila de peças

typedef struct Peça {
    int tipo;
    struct Peça *proxima;
} Peça;

Peça *fila = NULL;

//Nome das peças

const char *nomes_pecas[] = {
    "I", "J", "L", "O", "S", "T", "Z"
};


//Menu do jogo para inserir as peças e remover

void menu() {
    int escolha;
    do {
        printf("Menu do Tetris:\n");
        printf("1. Adicionar peça\n");
        printf("2. Remover peça\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        if (escolha == 1) {
            int tipo;
            printf("Digite o tipo da peça (0-6): ");
            scanf("%d", &tipo);
            Peça *nova_peca = (Peça *)malloc(sizeof(Peça));
            nova_peca->tipo = tipo;
            nova_peca->proxima = fila;
            fila = nova_peca;
            printf("Peça %s adicionada à fila.\n", nomes_pecas[tipo]);
        } else if (escolha == 2) {
            if (fila != NULL) {
                Peça *removida = fila;
                fila = fila->proxima;
                printf("Peça %s removida da fila.\n", nomes_pecas[removida->tipo]);
                free(removida);
            } else {
                printf("A fila está vazia.\n");
            }
        }
    } while (escolha != 3);
}


int main() {
    menu();
    return 0;
}