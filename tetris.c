#include <stdio.h>
#include <stdlib.h>


//Criando jogo Tetris Stack

//Fila de peças

typedef struct Peça {
    int tipo;
    struct Peça *proxima;
} Peça;

Peça *fila = NULL;

//Nome das peças e gerar aleatoriamente

const char *nomes_pecas[] = {
    "I", "O", "T", "S", "Z", "J", "L"
};



//Menu do jogo para inserir as peças e remover

void adicionar_peca(int tipo) {
    Peça *nova_peca = (Peça *)malloc(sizeof(Peça));
    nova_peca->tipo = tipo;
    nova_peca->proxima = NULL;

    if (fila == NULL) {
        fila = nova_peca;
    } else {
        Peça *temp = fila;
        while (temp->proxima != NULL) {
            temp = temp->proxima;
        }
        temp->proxima = nova_peca;
    }
    printf("Peça %s adicionada à fila.\n", nomes_pecas[tipo]);
}

void remover_peca(void) {
    if (fila == NULL) {
        printf("A fila está vazia. Nenhuma peça para remover.\n");
        return;
    }
    Peça *removida = fila;
    fila = fila->proxima;
    printf("Peça %s removida da fila.\n", nomes_pecas[removida->tipo]);
    free(removida);
}

void usar_peca_reservada(void) {
    if (fila == NULL) {
        printf("A fila está vazia. Nenhuma peça reservada para usar.\n");
        return;
    }
    Peça *usada = fila;
    fila = fila->proxima;
    printf("Peça reservada %s usada no jogo.\n", nomes_pecas[usada->tipo]);
    free(usada);
}

void menu(void) {
    int escolha;
    do {
        printf("Menu do Tetris:\n");
        printf("1. Adicionar peça\n");
        printf("2. Remover peça\n");
        printf("3. Usar peça reservada\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: {
                printf("Digite o tipo da peça (0-6): ");
                int tipo;
                scanf("%d", &tipo);
                adicionar_peca(tipo);
                break;
            }
            case 2:
                remover_peca();
                break;
            case 3:
                usar_peca_reservada();
                break;
            case 4:
                printf("Saindo do jogo. Obrigado por jogar!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 4);
}

int main() {
    menu();
    return 0;
}
