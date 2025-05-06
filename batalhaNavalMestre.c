#include <stdio.h>
#include <ctype.h>

#define TAM 10
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5

// Inicializa o tabuleiro com água
void inicializarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = AGUA;
}

// Posiciona navios simples no tabuleiro (exemplo fixo)
void posicionarNavios(int tab[TAM][TAM]) {
    // Horizontal
    tab[2][2] = tab[2][3] = tab[2][4] = NAVIO;
    // Vertical
    tab[4][6] = tab[5][6] = tab[6][6] = NAVIO;
    // Diagonal ↘
    tab[0][0] = tab[1][1] = tab[2][2] = NAVIO;
    // Diagonal ↙
    tab[0][9] = tab[1][8] = tab[2][7] = NAVIO;
}

// Aplica uma matriz de habilidade (5x5 ou 7x7) no tabuleiro, com centro em (centroLin, centroCol)
void aplicarHabilidade(int tab[TAM][TAM], int habilidade[][5], int tamHab, int centroLin, int centroCol, int tipo) {
    int offset = tamHab / 2;
    for (int i = 0; i < tamHab; i++) {
        for (int j = 0; j < tamHab; j++) {
            int lin = centroLin - offset + i;
            int col = centroCol - offset + j;

            if (lin >= 0 && lin < TAM && col >= 0 && col < TAM) {
                if (habilidade[i][j] == 1)
                    tab[lin][col] = tipo; // Aplica tipo da habilidade (valores negativos)
            }
        }
    }
}

// Exibe o tabuleiro
void exibirTabuleiro(int tab[TAM][TAM]) {
    printf("   ");
    for (int j = 0; j < TAM; j++)
        printf("%c ", 'A' + j);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++) {
            switch (tab[i][j]) {
                case 0: printf(". "); break;      // Água
                case 3: printf("N "); break;      // Navio
                case -1: printf("C "); break;     // Cone
                case -2: printf("X "); break;     // Cruz
                case -3: printf("O "); break;     // Octaedro
                default: printf("? "); break;
            }
        }
        printf("\n");
    }
}

// Cria a matriz de habilidade CONE 5x5 (expande para baixo)
void criarCone(int matriz[5][5]) {
    for (int i = 0; i < 5; i++) {           // linhas
        for (int j = 0; j < 5; j++) {       // colunas
            if (i == 0 && j == 2) matriz[i][j] = 1; // topo
            else if (i == 1 && (j >= 1 && j <= 3)) matriz[i][j] = 1;
            else if (i == 2 && (j >= 0 && j <= 4)) matriz[i][j] = 1;
            else matriz[i][j] = 0;
        }
    }
}

// Cria a matriz de habilidade CRUZ 5x5
void criarCruz(int matriz[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 2 || j == 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria a matriz de habilidade OCTAEDRO 5x5
void criarOctaedro(int matriz[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);

    // Matrizes de habilidade
    int cone[5][5], cruz[5][5], octaedro[5][5];
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplicar habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 5, 3, 3, -1);       // Cone = C
    aplicarHabilidade(tabuleiro, cruz, 5, 5, 5, -2);       // Cruz = X
    aplicarHabilidade(tabuleiro, octaedro, 5, 7, 7, -3);   // Octaedro = O

    // Mostrar resultado
    printf("Tabuleiro com navios e habilidades:\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}