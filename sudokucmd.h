#ifndef SUDOKUCMD_H // Include guard - Verifica se NOME_DO_HEADER_H ainda não foi definido
#define SUDOKUCMD_H // Define NOME_DO_HEADER_H para prevenir inclusão futura

    // Definição de Macros para as cores das fontes
    #define FORTE 15 // BRANCO CLARO
    #define FRACA 8 // CINZA
    #define NORMAL 7 // BRANCO
    #define ERRO 12 // VERMELHO CLARO

    #define PRETO 0
    #define AZUL 1
    #define VERDE 2
    #define AQUA 3
    #define VERMELHO 4
    #define ROXO 5
    #define AMARELO 6
    #define AZUL_CLARO 9
    #define VERDE_CLARO 10
    #define AQUA_CLARO 11
    #define ROXO_CLARO 13
    #define AMARELO_CLARO 14

    typedef struct entities_sudoku SUDOKU;

    void headerold(int color);
    void header1(int color);
    void header2(int color);
    void header3(int color);


    void show_board2(int c[9][9], char opcao_borda);
    void show_board(int c[9][9], char opcao_borda);
    void clear_board(int cells[9][9]);
    void show_menu(int color);

    void imprimir_campos(int campos[9][9]);
    void converter_entrada(char player_entrada[2], int coluna, int linha);
    void setColor(int color);



#endif // SUDOKUCMD_H // Fecha a guarda de inclusão

