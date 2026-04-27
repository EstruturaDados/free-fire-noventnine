#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct Item
// Representa cada objeto coletado pelo jogador
typedef struct {
    char nome[30];     // Nome do item
    char tipo[20];     // Tipo do item (arma, munição, cura, etc.)
    int quantidade;    // Quantidade do item
} Item;

// Vetor global para armazenar até 10 itens
Item mochila[10];
int totalItens = 0; // Controla quantos itens estão cadastrados

// Função para inserir um novo item na mochila
void inserirItem() {
    if (totalItens >= 10) {
        printf("A mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("Digite o nome do item: ");
    scanf("%s", novo.nome);

    printf("Digite o tipo do item (arma, municao, cura, etc.): ");
    scanf("%s", novo.tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[totalItens] = novo;
    totalItens++;

    printf("Item cadastrado com sucesso!\n");
}

// Função para remover um item da mochila pelo nome
void removerItem() {
    char nomeRemover[30];
    printf("Digite o nome do item que deseja remover: ");
    scanf("%s", nomeRemover);

    int encontrado = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Item não encontrado na mochila.\n");
    } else {
        // Desloca os itens para preencher o espaço removido
        for (int i = encontrado; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        printf("Item removido com sucesso!\n");
    }
}

// Função para listar todos os itens da mochila
void listarItens() {
    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    printf("\nItens na mochila:\n");
    for (int i = 0; i < totalItens; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("\n");
}

// Função para buscar um item pelo nome (busca sequencial)
void buscarItem() {
    char nomeBusca[30];
    printf("Digite o nome do item que deseja buscar: ");
    scanf("%s", nomeBusca);

    int encontrado = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Item não encontrado.\n");
    } else {
        printf("Item encontrado: Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[encontrado].nome, mochila[encontrado].tipo, mochila[encontrado].quantidade);
    }
}

// Função principal com menu interativo
int main() {
    int opcao;

    do {
        printf("=== Sistema de Inventário Mochila ===\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
