#include <stdio.h>
#include <ctype.h>

#define TAM 10
#define TAM_NAVIO 3
#define NAVIO 3
#define AGUA 0

// Inicializa o tabuleiro com zeros (água)
void inicializarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = AGUA;
}

// Converte letra para índice de coluna
int letraParaColuna(char letra) {
    letra = toupper(letra);
    if (letra >= 'A' && letra <= 'J') return letra - 'A';
    return -1;
}

// Verifica se o navio pode ser posicionado sem sair ou sobrepor
int podePosicionar(int tab[TAM][TAM], int lin, int col, int orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int r = lin, c = col;
        if (orientacao == 0) c += i;            // horizontal
        else if (orientacao == 1) r += i;       // vertical
        else if (orientacao == 2) { r += i; c += i; }  // diagonal ↘
        else if (orientacao == 3) { r += i; c -= i; }  // diagonal ↙

        if (r < 0 || r >= TAM || c < 0 || c >= TAM) return 0;
        if (tab[r][c] != AGUA) return 0;
    }
    return 1;
}

// Posiciona o navio no tabuleiro
void posicionarNavio(int tab[TAM][TAM], int lin, int col, int orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int r = lin, c = col;
        if (orientacao == 0) c += i;            // horizontal
        else if (orientacao == 1) r += i;       // vertical
        else if (orientacao == 2) { r += i; c += i; }  // diagonal ↘
        else if (orientacao == 3) { r += i; c -= i; }  // diagonal ↙

        tab[r][c] = NAVIO;
    }
}

// Exibe o tabuleiro com letras nas colunas
void exibirTabuleiro(int tab[TAM][TAM]) {
    printf("   ");
    for (int j = 0; j < TAM; j++)
        printf("%c ", 'A' + j);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Navio 1 - Horizontal (linha 1, coluna D)
    int lin1 = 1;
    char colLetra1 = 'D';
    int col1 = letraParaColuna(colLetra1);
    if (podePosicionar(tabuleiro, lin1, col1, 0))
        posicionarNavio(tabuleiro, lin1, col1, 0);

    // Navio 2 - Vertical (linha 5, coluna G)
    int lin2 = 5;
    char colLetra2 = 'G';
    int col2 = letraParaColuna(colLetra2);
    if (podePosicionar(tabuleiro, lin2, col2, 1))
        posicionarNavio(tabuleiro, lin2, col2, 1);

    // Navio 3 - Diagonal ↘ (linha 0, coluna A)
    int lin3 = 0;
    char colLetra3 = 'A';
    int col3 = letraParaColuna(colLetra3);
    if (podePosicionar(tabuleiro, lin3, col3, 2))
        posicionarNavio(tabuleiro, lin3, col3, 2);

    // Navio 4 - Diagonal ↙ (linha 0, coluna I)
    int lin4 = 0;
    char colLetra4 = 'I';
    int col4 = letraParaColuna(colLetra4);
    if (podePosicionar(tabuleiro, lin4, col4, 3))
        posicionarNavio(tabuleiro, lin4, col4, 3);

    // Exibir tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}