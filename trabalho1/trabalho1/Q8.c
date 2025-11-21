#include <stdio.h>

char tabuleiro[3][3];
int jogador = 1;

void inicializarTabuleiro() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

void exibirTabuleiro() {
    printf("\n   A   B   C\n");
    for (int i = 0; i < 3; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < 3; j++) {
            printf(" %c ", tabuleiro[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("  ---+---+---\n");
    }
    printf("\n");
}

int converterJogada(char col, int lin) {
    int colIndex = -1;
    if (col == 'A' || col == 'a') colIndex = 0;
    else if (col == 'B' || col == 'b') colIndex = 1;
    else if (col == 'C' || col == 'c') colIndex = 2;
    
    int linIndex = lin - 1;
    
    if (linIndex < 0 || linIndex > 2 || colIndex == -1) return 0;
    if (tabuleiro[linIndex][colIndex] != ' ') return 0;
    
    return 1;
}

void fazerJogada(char col, int lin) {
    int colIndex = -1;
    if (col == 'A' || col == 'a') colIndex = 0;
    else if (col == 'B' || col == 'b') colIndex = 1;
    else if (col == 'C' || col == 'c') colIndex = 2;
    
    int linIndex = lin - 1;
    
    tabuleiro[linIndex][colIndex] = (jogador == 1) ? 'X' : 'O';
}

int verificarVencedor() {
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] != ' ' && tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2])
            return 1;
    }
    for (int j = 0; j < 3; j++) {
        if (tabuleiro[0][j] != ' ' && tabuleiro[0][j] == tabuleiro[1][j] && tabuleiro[1][j] == tabuleiro[2][j])
            return 1;
    }
    if (tabuleiro[0][0] != ' ' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2])
        return 1;
    if (tabuleiro[0][2] != ' ' && tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0])
        return 1;
    
    return 0;
}

int tabuleiroCompleto() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == ' ') return 0;
        }
    }
    return 1;
}

int main() {
    inicializarTabuleiro();
    int vencedor = 0;
    int empate = 0;
    
    while (!vencedor && !empate) {
        exibirTabuleiro();
        printf("Jogador %d, informe sua jogada (ex: A1): ", jogador);
        
        char col;
        int lin;
        scanf(" %c%d", &col, &lin);
        
        if (converterJogada(col, lin)) {
            fazerJogada(col, lin);
            vencedor = verificarVencedor();
            if (!vencedor) {
                empate = tabuleiroCompleto();
                jogador = (jogador == 1) ? 2 : 1;
            }
        } else {
            printf("Jogada inválida! Tente novamente.\n");
        }
    }
    
    exibirTabuleiro();
    if (vencedor) {
        printf("Jogador %d venceu!\n", jogador);
    } else {
        printf("Empate!\n");
    }
    
    return 0;
}
