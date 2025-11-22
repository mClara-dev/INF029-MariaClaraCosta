#include <stdio.h>

#define TAM 10
#define NUM_NAVIOS 5

typedef struct {
    int tamanho;
    int posicoes[TAM][2];
    int atingido[TAM];
} Navio;

typedef struct {
    char mapa[TAM][TAM];
    char mapa_adversario[TAM][TAM];
    Navio navios[NUM_NAVIOS];
    int navios_afundados;
} Jogador;

Jogador jogadores[2];
int jogador_atual = 0;

void inicializarMapas() {
    for (int p = 0; p < 2; p++) {
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                jogadores[p].mapa[i][j] = ' ';
                jogadores[p].mapa_adversario[i][j] = ' ';
            }
        }
        jogadores[p].navios_afundados = 0;
    }
}

void exibirMapa(Jogador j, int proprio) {
    printf("\n  ");
    for (char c = 'A'; c < 'A' + TAM; c++) {
        printf(" %c", c);
    }
    printf("\n");
    
    for (int i = 0; i < TAM; i++) {
        printf("%2d", i + 1);
        for (int j = 0; j < TAM; j++) {
            char celula;
            if (proprio) {
                celula = j.mapa[i][j];
            } else {
                celula = j.mapa_adversario[i][j];
            }
            printf(" %c", celula);
        }
        printf("\n");
    }
    printf("\n");
}

int posicionarNavio(int jogador_idx, int navio_idx, int tamanho, int linha, int coluna, int direcao) {
    if (direcao == 0) {
        if (coluna + tamanho > TAM) return 0;
    } else {
        if (linha + tamanho > TAM) return 0;
    }
    
    for (int i = 0; i < tamanho; i++) {
        int lin = linha + (direcao == 1 ? i : 0);
        int col = coluna + (direcao == 0 ? i : 0);
        
        if (jogadores[jogador_idx].mapa[lin][col] != ' ') {
            return 0;
        }
    }
    
    for (int i = 0; i < tamanho; i++) {
        int lin = linha + (direcao == 1 ? i : 0);
        int col = coluna + (direcao == 0 ? i : 0);
        
        jogadores[jogador_idx].mapa[lin][col] = 'N';
        
        jogadores[jogador_idx].navios[navio_idx].posicoes[i][0] = lin;
        jogadores[jogador_idx].navios[navio_idx].posicoes[i][1] = col;
        jogadores[jogador_idx].navios[navio_idx].atingido[i] = 0;
    }
    
    jogadores[jogador_idx].navios[navio_idx].tamanho = tamanho;
    
    return 1;
}

void posicionarNavios(int jogador_idx) {
    printf("Jogador %d, posicione seus navios:\n", jogador_idx + 1);
    
    printf("Navio tamanho 4:\n");
    int ok = 0;
    while (!ok) {
        printf("Informe linha (1-10), coluna (A-J) e direção (H/V): ");
        int linha;
        char coluna_char;
        char direcao;
        scanf("%d %c %c", &linha, &coluna_char, &direcao);
        
        int coluna = coluna_char - 'A';
        linha--;
        
        ok = posicionarNavio(jogador_idx, 0, 4, linha, coluna, (direcao == 'V' || direcao == 'v') ? 1 : 0);
        if (!ok) printf("Posição inválida! Tente novamente.\n");
    }
    
    printf("Navio tamanho 3:\n");
    ok = 0;
    while (!ok) {
        printf("Informe linha (1-10), coluna (A-J) e direção (H/V): ");
        int linha;
        char coluna_char;
        char direcao;
        scanf("%d %c %c", &linha, &coluna_char, &direcao);
        
        int coluna = coluna_char - 'A';
        linha--;
        
        ok = posicionarNavio(jogador_idx, 1, 3, linha, coluna, (direcao == 'V' || direcao == 'v') ? 1 : 0);
        if (!ok) printf("Posição inválida! Tente novamente.\n");
    }
    
    for (int i = 0; i < 3; i++) {
        printf("Navio tamanho 1 (%d/3):\n", i + 1);
        ok = 0;
        while (!ok) {
            printf("Informe linha (1-10) e coluna (A-J): ");
            int linha;
            char coluna_char;
            scanf("%d %c", &linha, &coluna_char);
            
            int coluna = coluna_char - 'A';
            linha--;
            
            ok = posicionarNavio(jogador_idx, 2 + i, 1, linha, coluna, 0);
            if (!ok) printf("Posição inválida! Tente novamente.\n");
        }
    }
}

int atirar(int atacante, int defensor, int linha, int coluna) {
    if (jogadores[atacante].mapa_adversario[linha][coluna] != ' ') {
        return -1;
    }
    
    if (jogadores[defensor].mapa[linha][coluna] == 'N') {
        jogadores[atacante].mapa_adversario[linha][coluna] = '0';
        jogadores[defensor].mapa[linha][coluna] = '0';
        
        for (int n = 0; n < NUM_NAVIOS; n++) {
            int afundou = 1;
            for (int p = 0; p < jogadores[defensor].navios[n].tamanho; p++) {
                int lin_navio = jogadores[defensor].navios[n].posicoes[p][0];
                int col_navio = jogadores[defensor].navios[n].posicoes[p][1];
                
                if (lin_navio == linha && col_navio == coluna) {
                    jogadores[defensor].navios[n].atingido[p] = 1;
                }
                
                if (!jogadores[defensor].navios[n].atingido[p]) {
                    afundou = 0;
                }
            }
            
            if (afundou) {
                jogadores[defensor].navios_afundados++;
                return 2;
            }
        }
        
        return 1;
    } else {
        jogadores[atacante].mapa_adversario[linha][coluna] = 'X';
        return 0;
    }
}

void jogar() {
    int vencedor = -1;
    
    while (vencedor == -1) {
        printf("\n=== Vez do Jogador %d ===\n", jogador_atual + 1);
        
        printf("Seu mapa:\n");
        exibirMapa(jogadores[jogador_atual], 1);
        
        printf("Mapa do adversário:\n");
        exibirMapa(jogadores[jogador_atual], 0);
        
        printf("Informe coordenada para atirar (ex: A1): ");
        int linha;
        char coluna_char;
        scanf("%d %c", &linha, &coluna_char);
        
        int coluna = coluna_char - 'A';
        linha--;
        
        if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM) {
            printf("Coordenada inválida!\n");
            continue;
        }
        
        int resultado = atirar(jogador_atual, 1 - jogador_atual, linha, coluna);
        
        if (resultado == -1) {
            printf("Você já atirou aqui!\n");
        } else if (resultado == 0) {
            printf("Água!\n");
            jogador_atual = 1 - jogador_atual;
        } else if (resultado == 1) {
            printf("Acertou!\n");
        } else if (resultado == 2) {
            printf("Afundou um navio!\n");
        }
        
        if (jogadores[1 - jogador_atual].navios_afundados == NUM_NAVIOS) {
            vencedor = jogador_atual;
        }
    }
    
    printf("\nJogador %d venceu!\n", vencedor + 1);
}

int main() {
    printf("=== BATALHA NAVAL ===\n");
    
    inicializarMapas();
    
    for (int i = 0; i < 2; i++) {
        printf("\nJogador %d - Posicionamento:\n", i + 1);
        posicionarNavios(i);
    }
    
    jogar();
    
    return 0;
}
