#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ========================= INVENTÁRIO MOCHILA =========================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

Item mochila[10];
int totalItens = 0;

void inserirItem() {
    if (totalItens >= 10) {
        printf("A mochila está cheia!\n");
        return;
    }
    Item novo;
    printf("Digite o nome do item: ");
    scanf("%s", novo.nome);
    printf("Digite o tipo do item: ");
    scanf("%s", novo.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    mochila[totalItens++] = novo;
    printf("Item cadastrado!\n");
}

void removerItem() {
    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nomeRemover);
    int encontrado = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
        printf("Item não encontrado.\n");
    } else {
        for (int i = encontrado; i < totalItens - 1; i++) {
            mochila[i] = mochila[i+1];
        }
        totalItens--;
        printf("Item removido!\n");
    }
}

void listarItens() {
    if (totalItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    printf("\nItens na mochila:\n");
    for (int i = 0; i < totalItens; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

void buscarItem() {
    char nomeBusca[30];
    printf("Digite o nome do item: ");
    scanf("%s", nomeBusca);
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Encontrado: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("Item não encontrado.\n");
}

// ========================= TORRE DE FUGA =========================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

Componente torre[20];
int totalComp = 0;

int bubbleSortNome(Componente v[], int n) {
    int comp = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            comp++;
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {
                Componente tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
            }
        }
    }
    return comp;
}

int insertionSortTipo(Componente v[], int n) {
    int comp = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i-1;
        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comp++;
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = chave;
    }
    return comp;
}

int selectionSortPrioridade(Componente v[], int n) {
    int comp = 0;
    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++) {
            comp++;
            if (v[j].prioridade < v[min].prioridade) min = j;
        }
        if (min != i) {
            Componente tmp = v[i];
            v[i] = v[min];
            v[min] = tmp;
        }
    }
    return comp;
}

int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int ini = 0, fim = n-1, comp = 0;
    while (ini <= fim) {
        int meio = (ini+fim)/2;
        comp++;
        int cmp = strcmp(v[meio].nome, chave);
        if (cmp == 0) {
            printf("Componente encontrado: %s | Tipo: %s | Prioridade: %d\n",
                   v[meio].nome, v[meio].tipo, v[meio].prioridade);
            printf("Comparações: %d\n", comp);
            return meio;
        } else if (cmp < 0) ini = meio+1;
        else fim = meio-1;
    }
    printf("Componente não encontrado. Comparações: %d\n", comp);
    return -1;
}

void medirTempo(int (*alg)(Componente[], int), Componente v[], int n) {
    clock_t ini = clock();
    int comp = alg(v, n);
    clock_t fim = clock();
    double tempo = (double)(fim-ini)/CLOCKS_PER_SEC;
    printf("Comparações: %d | Tempo: %.6f segundos\n", comp, tempo);
}

void mostrarComponentes(Componente v[], int n) {
    if (n == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }
    printf("\n--- Componentes ---\n");
    for (int i = 0; i < n; i++) {
        printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
               v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

//========================= MAIN =========================
int main() {
    int escolha;
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Sistema da Mochila\n");
        printf("2 - Torre de Fuga\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        if (escolha == 1) {
            int op;
            do {
                printf("\n--- Mochila ---\n");
                printf("1 - Inserir item\n2 - Remover item\n3 - Listar itens\n4 - Buscar item\n0 - Voltar\n");
                scanf("%d", &op);
                switch(op) {
                    case 1: inserirItem(); listarItens(); break;
                    case 2: removerItem(); listarItens(); break;
                    case 3: listarItens(); break;
                    case 4: buscarItem(); break;
                }
            } while(op != 0);
        } else if (escolha == 2) {
            int op;
            char chave[30];
            do {
                printf("\n--- Torre de Fuga ---\n");
                printf("1 - Inserir componente\n2 - Ordenar por nome (Bubble)\n3 - Ordenar por tipo (Insertion)\n4 - Ordenar por prioridade (Selection)\n5 - Buscar componente-chave (Binária)\n6 - Listar componentes\n0 - Voltar\n");
                scanf("%d", &op);
                getchar(); // limpar buffer
                switch(op) {
                    case 1:
                        if (totalComp < 20) {
                            printf("Nome: ");
                            fgets(torre[totalComp].nome, 30, stdin);
                            torre[totalComp].nome[strcspn(torre[totalComp].nome, "\n")] = 0;
                            printf("Tipo: ");
                            fgets(torre[totalComp].tipo, 20, stdin);
                            torre[totalComp].tipo[strcspn(torre[totalComp].tipo, "\n")] = 0;
                            printf("Prioridade (1-10): ");
                            scanf("%d", &torre[totalComp].prioridade);
                            getchar();
                            totalComp++;
                        } else printf("Limite atingido!\n");
                        break;
                    case 2: medirTempo(bubbleSortNome, torre, totalComp); mostrarComponentes(torre, totalComp); break;
                    case 3: medirTempo(insertionSortTipo, torre, totalComp); mostrarComponentes(torre, totalComp); break;
                    case 4: medirTempo(selectionSortPrioridade, torre, totalComp); mostrarComponentes(torre, totalComp); break;
                    case 5:
                        printf("Digite o nome do componente-chave: ");
                        fgets(chave, 30, stdin);
                        chave[strcspn(chave, "\n")] = 0;
                        buscaBinariaPorNome(torre, totalComp, chave);
                        break;
                    case 6: mostrarComponentes(torre, totalComp); break;
                }
            } while(op != 0);
        }
    } while(escolha != 0);

    return 0;
}
