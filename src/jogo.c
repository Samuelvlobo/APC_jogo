#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

// Definir um comando para limpar a tela, dependendo do sistema operacional
#ifdef _WIN32
    #define clear() system("cls")
#else
    #define clear() system("clear")
#endif

void inicializarMatriz(char matriz[10][10][2]) {
    // Inicializa todas as posições da matriz com "-"
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            strcpy(matriz[i][j], "-");
        }
    }

    // Adiciona os identificadores das linhas e colunas
    char str = 'A';
    char str1 = '0';
    for (int i = 1; i < 10; i++) {
        matriz[i][0][0] = str;
        str++;
        matriz[0][i][0] = str1;
        str1++;
    }
}

void posicaoNavio(char *index) {
    int aux = 0;
    printf("Escolha a posicao digitando a coluna e a linha (Ex: A1):\n\n");
    printf("ATENCAO!\n");
    printf("Fique atento a margem, seus navios possuem 4 unidades de tamanho\n");
    printf("se for alocado em um espaco insuficiente, sera realocada para caber:\n");

    do {
        scanf("%2s", index);  // Lê até 2 caracteres
        index[0] = toupper(index[0]);
        int num = index[1] - '0';  // Converte caractere numérico para inteiro
        if (index[0] >= 'A' && index[0] <= 'I' && num >= 0 && num <= 9) {
            aux = 1;
        } else {
            printf("Posicao digitada errada, por favor digite uma letra entre A e I e um número entre 0 e 9:\n");
        }
    } while (aux != 1);
}

void imprimirMatriz(char matriz[10][10][2], const char* titulo) {
    printf("\n  %s:  \n", titulo);
    printf("-------------------\n");
    for (int i = 0; i < 10; i++) { // imprimindo a matriz
        for (int j = 0; j < 10; j++) {
            printf("%c ", matriz[i][j][0]);
        }
        printf("\n");
    }
    printf("\n");
}

int verifica(char matriz[10][10][2]) {
    for (int i = 1; i < 10; i++) { // pega as posições de onde deseja atacar
        for (int j = 1; j < 10; j++) {
            if (matriz[i][j][0] == 'o') {
                return 1; // encontrou um navio, interrompe a busca
            }
        }
    }
    return 0; // nenhum navio encontrado
}

void ataqueJogador(char *posicao) {
    int aux = 0;
    printf("\nEscolha onde deseja atacar (Ex: A0):\n");

    do {
        scanf("%2s", posicao);
        posicao[0] = toupper(posicao[0]);
        int num = posicao[1] - '0';  // Converte caractere numérico para inteiro
        if (posicao[0] >= 'A' && posicao[0] <= 'I' && num >= 0 && num <= 9) {
            aux = 1;
        } else {
            printf("Posicao digitada errada, por favor digite uma letra entre A e I e um número entre 0 e 9:\n");
        }
    } while (aux != 1);
}

void ataqueMaquina(char *posicao) {
    // Gera um número aleatório entre 0 e 9
    posicao[0] = 'A' + (rand() % 9);
    posicao[1] = '0' + (rand() % 9);
}

void obterCoordenadas(char *posicao, int *coord) {
    coord[0] = posicao[0] - 'A' + 1;
    coord[1] = posicao[1] - '0' + 1;
}

void posicionarNavios(char campoJogador[10][10][2], char campoMaquina[10][10][2]) {
    for (int i = 0; i < 4; i++) {
        char posicao[3];
        int aux[2];

        printf("\n----------- Posicione seus navios:-----------\n\n");
        posicaoNavio(posicao);
        obterCoordenadas(posicao, aux);

        for (int j = 0; j < 4; j++) { // Adiciona navios no campoJogador
            if (aux[0] > 6) {
                strcpy(campoJogador[aux[0] - j][aux[1]], "o");
            } else {
                strcpy(campoJogador[aux[0] + j][aux[1]], "o");
            }
        }

        for (int j = 0; j < 4; j++) { // Adiciona navios no campoMaquina
            if (aux[1] > 6) {
                strcpy(campoMaquina[aux[0]][aux[1] - j], "o");
            } else {
                strcpy(campoMaquina[aux[0]][aux[1] + j], "o");
            }
        }

        printf("\n");
        imprimirMatriz(campoJogador, "SEU CAMPO");
    }
}

int main() {
    // Criando os campos
    char campoJogador[10][10][2];
    char campoMaquina[10][10][2];
    char campoEspelhoMaquina[10][10][2];

    inicializarMatriz(campoJogador);
    inicializarMatriz(campoMaquina);
    inicializarMatriz(campoEspelhoMaquina);

    imprimirMatriz(campoJogador, "CAMPO JOGADOR");

    // Parte que adiciona os navios nos mapas
    posicionarNavios(campoJogador, campoMaquina);
    sleep(1);

    // Inicializa o gerador de números aleatórios uma única vez
    srand(time(NULL));

    // Parte dos ataques
    printf("\n-----VAMOS PARA A BATALHA!------\n");

     int vitoria = 0;
     int resultado = 0;
    while (resultado == 0) { // ataques do jogador e da máquina
        char posicao[3];
        int aux[2];

        clear();

        imprimirMatriz(campoJogador, "CAMPO JOGADOR");
        printf("\nSelecione a linha e a coluna onde deseja atacar:\n");
        imprimirMatriz(campoEspelhoMaquina, "CAMPO INIMIGO");
        ataqueJogador(posicao);
        obterCoordenadas(posicao, aux);

        if (campoMaquina[aux[0]][aux[1]][0] == 'o') {
            campoMaquina[aux[0]][aux[1]][0] = 'x';
            campoEspelhoMaquina[aux[0]][aux[1]][0] = 'x';
        } else if (campoMaquina[aux[0]][aux[1]][0] == '-') {
            campoMaquina[aux[0]][aux[1]][0] = 'E';
            campoEspelhoMaquina[aux[0]][aux[1]][0] = 'E';
        }

        ataqueMaquina(posicao);
        obterCoordenadas(posicao, aux);

        if (campoJogador[aux[0]][aux[1]][0] == 'o') {
            campoJogador[aux[0]][aux[1]][0] = 'x';
        } else if (campoJogador[aux[0]][aux[1]][0] == '-') {
            campoJogador[aux[0]][aux[1]][0] = 'E';
        }

        if(verifica(campoMaquina) == 0){//verifica se ja teve algum campo ja foi derrotado todos os navios
            resultado = 1;
            vitoria = 1;
        }else if(verifica(campoJogador) == 0){
            resultado = 1;
            vitoria = 2;
        }

    }

    if(vitoria == 1){//verifica quem ganhou o jogo
        clear();
        printf("\nVoce derrotou todos os navios do inimigo!!\n\n");
        imprimirMatriz(campoEspelhoMaquina, "CAMPO INIMIGO");
        printf("\nPARABENS!! VOCE GANHOU!!\n");
    }else if(vitoria == 2){
        clear();
        printf("\nTodos os seus navios foram derrotados...\n");
        imprimirMatriz(campoJogador, "CAMPO JOGADOR");
        printf("GAME OVER!");
    }

    return 0;
}
