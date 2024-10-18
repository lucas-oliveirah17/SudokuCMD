#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <fcntl.h>  // Para _setmode() Usado para configurar a saída em UTF_16
#include <io.h>     //   ||     ||       ||   ||      ||    ||   ||    ||  ||
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include <wchar.h>
#include "sudokucmd.h"

int main()
{
    int cells[9][9];
    char option = 'd';
    wchar_t input[2] = {'0', '0'};
    // Definindo a localidade
    setlocale(LC_ALL, "");
    // Mudando o modo de saída para suportar UTF-8
    _setmode(_fileno(stdout), _O_U16TEXT);  // Habilita UTF-16 no Windows
    clear_board(cells); // Limpa o tabuleiro
    do {
        header3(VERDE_CLARO);
        show_board(cells, option);
        show_menu(AMARELO_CLARO);
        wprintf(L"Qual acao deseja realizar? ");
        wscanf(L"%2s", &input);
        system("cls");
       /*fgetws(input, sizeof(input) / sizeof(wchar_t),stdin);
        //system("cls");
        // Remove o caractere de nova linha se presente
        size_t len = wcslen(input);
        if (len > 0 && input[len - 1] == L'\n') {
            input[len - 1] = L'\0'; // Substitui o '\n' por '\0'
        }*/
    }
    while(input[0] != toupper('q'));
    system("PAUSE");
    return 0;
}



/*

    char opcao_borda = 'S';
    char player_entrada [2];
    // Definindo a localidade
    setlocale(LC_ALL, "");
    // Mudando o modo de saída para suportar UTF-8
    _setmode(_fileno(stdout), _O_U16TEXT);  // Habilita UTF-16 no Windows
    wprintf(L"#########################################################\n####### SUDOKU CMD ######## By: Lucas S. Oliveira #######\n#########################################################\n\n");
    // Define a borda
    do {
        wprintf(L"Qual tipo de borda deseja? Simples = [S] | Dupla = [D]: ");
        scanf(" %c", &opcao_borda);
        if(opcao_borda == 'S' || opcao_borda == 's' || opcao_borda == 'D' || opcao_borda == 'd') {
            break;
        }
        else {
            setColor(ERRO);
            wprintf(L"Entrada inválida! Tente novamente.\n");
            setColor(NORMAL);
        }
    } while(1);
    // Exibe o tabuleiro
    tabuleiro(campos, opcao_borda);
    wprintf(L"\nDeseja limpar o tabuleiro? Sim [S] | Não [N]: ");
    getchar();
    scanf("%s", &player_entrada);
    if (toupper(player_entrada[0]) == 'S') {
        limpar_tabuleiro(campos);
    }
    else if (toupper(player_entrada[0]) == 'N') {
        wprintf(L"Limpeza cancelada!\n");
    }
    else {
        setColor(ERRO);
        wprintf(L"Entrada inválida! Tente novamente.\n\n");
        setColor(NORMAL);
    }
    tabuleiro(campos, opcao_borda);
    wprintf(L"\n\n");
    // Fim do programa
*/


