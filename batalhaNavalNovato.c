#include <stdio.h>
#include <ctype.h>  // Para toupper()

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_NAVIO 3
#define VALOR_AGUA 0

// Função para inicializar o tabuleiro com zeros (água)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
        }
    }
}

// Converte uma letra (A-J ou a-j) para índice da coluna (0-9)
int letraParaColuna(char letra) {
    letra = toupper(letra);
    if (letra >= 'A' && letra <= 'J') {
        return letra - 'A';
    }
    return -1;  // Inválido
}

// Verifica se pode posicionar navio sem ultrapassar limites ou sobreposição
int podePosicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                        int linhaInicial, int colunaInicial,
                        int orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linhaInicial + (orientacao == 1 ? i : 0);
        int coluna = colunaInicial + (orientacao == 0 ? i : 0);

        if (linha >= TAMANHO_TABULEIRO || coluna >= TAMANHO_TABULEIRO) {
            return 0;
        }

        if (tabuleiro[linha][coluna] != VALOR_AGUA) {
            return 0;
        }
    }
    return 1;
}

// Posiciona o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                     int linhaInicial, int colunaInicial,
                     int orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linhaInicial + (orientacao == 1 ? i : 0);
        int coluna = colunaInicial + (orientacao == 0 ? i : 0);
        tabuleiro[linha][coluna] = VALOR_NAVIO;
    }
}

// Exibe o tabuleiro com letras nas colunas
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%c ", 'A' + j);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Coordenadas dos navios usando letra para coluna
    int linhaH = 2;
    char colunaHLetra = 'E';  // coluna 4
    int linhaV = 5;
    char colunaVLetra = 'H';  // coluna 7

    // Converte letras para índices
    int colunaH = letraParaColuna(colunaHLetra);
    int colunaV = letraParaColuna(colunaVLetra);

    if (colunaH == -1 || colunaV == -1) {
        printf("Erro: Coluna inválida.\n");
        return 1;
    }

    // Verifica e posiciona navio horizontal
    if (podePosicionarNavio(tabuleiro, linhaH, colunaH, 0)) {
        posicionarNavio(tabuleiro, linhaH, colunaH, 0);
    } else {
        printf("Erro: Não foi possível posicionar o navio horizontal.\n");
    }

    // Verifica e posiciona navio vertical
    if (podePosicionarNavio(tabuleiro, linhaV, colunaV, 1)) {
        posicionarNavio(tabuleiro, linhaV, colunaV, 1);
    } else {
        printf("Erro: Não foi possível posicionar o navio vertical.\n");
    }

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}