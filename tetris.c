#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Definições e Constantes ---
#define TAMANHO_MAXIMO 5

// Estrutura para representar uma "Peça"
typedef struct {
    int id;
} Peca;

// Estrutura da Fila Circular
typedef struct {
    Peca itens[TAMANHO_MAXIMO];
    int frente; // Índice do primeiro elemento
    int tras;   // Índice onde o próximo elemento será inserido
    int contador; // Número atual de elementos na fila
} FilaCircular;

// --- Funções de Geração e Inicialização ---

/**
 * @brief Gera uma nova peça com um ID sequencial.
 * @return Uma nova Peca.
 */
Peca gerarPeca() {
    // Usamos um ID simples para simulação. Em um sistema real, seria mais complexo.
    static int proximo_id = 1;
    Peca nova_peca;
    nova_peca.id = proximo_id++;
    return nova_peca;
}

/**
 * @brief Inicializa a fila com 5 peças geradas automaticamente.
 * @param fila Ponteiro para a estrutura da fila.
 */
void inicializarFila(FilaCircular *fila) {
    fila->frente = 0;
    fila->tras = 0;
    fila->contador = 0;

    printf("Inicializando a fila com %d peças automaticamente...\n", TAMANHO_MAXIMO);
    for (int i = 0; i < TAMANHO_MAXIMO; i++) {
        // Enfileira imediatamente as 5 peças iniciais
        Peca p = gerarPeca();
        fila->itens[fila->tras] = p;
        fila->tras = (fila->tras + 1) % TAMANHO_MAXIMO;
        fila->contador++;
    }
    printf("Inicialização concluída. Estado inicial:\n");
    visualizarFila(fila);
}

// --- Funcionalidades da Fila ---

/**
 * @brief Verifica se a fila está cheia.
 */
int estaCheia(FilaCircular *fila) {
    return fila->contador == TAMANHO_MAXIMO;
}

/**
 * @brief Verifica se a fila está vazia.
 */
int estaVazia(FilaCircular *fila) {
    return fila->contador == 0;
}

/**
 * @brief Insere uma nova peça no final da fila (Enfileirar).
 * @param fila Ponteiro para a estrutura da fila.
 */
void inserirPeca(FilaCircular *fila) {
    if (estaCheia(fila)) {
        printf("\nERRO: A fila está cheia. Nenhuma peça pode ser inserida.\n");
        return;
    }

    Peca nova_peca = gerarPeca();
    printf("\nInserindo nova peça de ID: %d no final da fila...\n", nova_peca.id);

    fila->itens[fila->tras] = nova_peca;
    // Atualiza o índice 'tras' de forma circular
    fila->tras = (fila->tras + 1) % TAMANHO_MAXIMO;
    fila->contador++;

    printf("Inserção realizada com sucesso.\n");
    visualizarFila(fila);
}

/**
 * @brief Remove a peça da frente da fila (Desenfileirar/Jogar).
 * @param fila Ponteiro para a estrutura da fila.
 */
void jogarPeca(FilaCircular *fila) {
    if (estaVazia(fila)) {
        printf("\nERRO: A fila está vazia. Nenhuma peça para jogar (remover).\n");
        return;
    }

    Peca peca_removida = fila->itens[fila->frente];
    printf("\nJogando (removendo) a peça da frente. ID removido: %d\n", peca_removida.id);

    // Atualiza o índice 'frente' de forma circular
    fila->frente = (fila->frente + 1) % TAMANHO_MAXIMO;
    fila->contador--;

    printf("Peça jogada com sucesso.\n");
    visualizarFila(fila);
}

/**
 * @brief Visualiza o estado atual da fila.
 * @param fila Ponteiro para a estrutura da fila.
 */
void visualizarFila(FilaCircular *fila) {
    printf("\n--- ESTADO ATUAL DA FILA (Contador: %d) ---\n", fila->contador);

    if (estaVazia(fila)) {
        printf("| Fila VAZIA |\n");
        printf("--------------------------------------------\n");
        return;
    }

    printf("|");
    int i = fila->frente;
    for (int count = 0; count < fila->contador; count++) {
        printf(" [ID: %02d] ", fila->itens[i].id);
        i = (i + 1) % TAMANHO_MAXIMO;
    }
    printf("|\n");

    printf("Indices: Frente=%d, Tras=%d\n", fila->frente, fila->tras);
    printf("--------------------------------------------\n");
}

// --- Menu Principal ---

void exibirMenu() {
    printf("\n========================================\n");
    printf("   SIMULADOR DE FILA CIRCULAR (TAM: %d)   \n", TAMANHO_MAXIMO);
    printf("========================================\n");
    printf("1. Visualizar Fila Atual\n");
    printf("2. Jogar Peça (Remover da Frente)\n");
    printf("3. Inserir Nova Peça (No Final)\n");
    printf("4. Sair\n");
    printf("----------------------------------------\n");
    printf("Escolha uma opção: ");
}

int main() {
    // Inicializa a semente para geração de números aleatórios (não estritamente necessário aqui, mas boa prática)
    srand(time(NULL));

    FilaCircular minhaFila;
    int opcao = 0;

    // 1. Inicialização obrigatória do sistema
    inicializarFila(&minhaFila);

    do {
        exibirMenu();
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer de entrada em caso de erro (ex: digitar letra)
            while (getchar() != '\n');
            opcao = 0;
            printf("\nEntrada inválida. Por favor, digite um número de 1 a 4.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                visualizarFila(&minhaFila);
                break;
            case 2:
                jogarPeca(&minhaFila);
                break;
            case 3:
                inserirPeca(&minhaFila);
                break;
            case 4:
                printf("\nEncerrando a simulação. Até breve!\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}


