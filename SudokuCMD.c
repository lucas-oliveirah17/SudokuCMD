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

/*###########################################################################*/
struct entities_sudoku{
    unsigned int cells[9][9];
    char type_border;
    char input_player[2];
};
/*###########################################################################*/

void headerold(int color) {
    setColor(color);
    wprintf(L"#########################################################\n");
    wprintf(L"####### SUDOKU CMD ######## By: Lucas S. Oliveira #######\n");
    wprintf(L"#########################################################\n");
    setColor(NORMAL);
}

void header1(int color) {
    // site do desenho https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20
    setColor(color); // Desenho Big / PARA MENU USAR O SMALL KEYBOARD
    wprintf(L"┌────────────────────────────────────────────────────────────┐\n");
    wprintf(L"│   _____           _       _           _____ __  __ _____   │\n");
    wprintf(L"│  / ____|         | |     | |         / ____|  \\/  |  __ \\  │\n");
    wprintf(L"│ | (___  _   _  __| | ___ | | ___   _| |    | \\  / | |  | | │\n");
    wprintf(L"│  \\___ \\| | | |/ _` |/ _ \\| |/ / | | | |    | |\\/| | |  | | │\n");
    wprintf(L"│  ____) | |_| | (_| | (_) |   <| |_| | |____| |  | | |__| | │\n");
    wprintf(L"│ |_____/ \\__,_|\\__,_|\\___/|_|\\_\\\\__,_|\\_____|_|  |_|_____/  │\n");
    wprintf(L"│                                                            │\n");
    wprintf(L"└────────────────────────────────────────────────────────────┘\n");
    setColor(NORMAL);
}
void header2(int color)  { // Desenho Small
    setColor(color);
    wprintf(L"  ┌──────────────────────────────────────────────┐\n");
    wprintf(L"  │  ___         _     _         ___ __  __ ___  │\n");
    wprintf(L"  │ / __|_  _ __| |___| |___  _ / __|  \\/  |   \\ │\n");
    wprintf(L"  │ \\__ \\ || / _` / _ \\ / / || | (__| |\\/| | |) |│\n");
    wprintf(L"  │ |___/\\_,_\\__,_\\___/_\\_\\\\_,_|\\___|_|  |_|___/ │\n");
    wprintf(L"  └──────────────────────────────────────────────┘\n");
    setColor(NORMAL);
}

void header3(int color) {
    setColor(color);
    wprintf(L"   ┌────────────────────────────────────────────────┐\n");
    wprintf(L"   │  __        __   __               __        __  │\n");
    wprintf(L"   │ /__` |  | |  \\ /  \\ |__/ |  |   /  ` |\\/| |  \\ │\n");
    wprintf(L"   │ .__/ \\__/ |__/ \\__/ |  \\ \\__/   \\__, |  | |__/ │\n");
    wprintf(L"   │                                                │\n");
    wprintf(L"   └────────────────────────────────────────────────┘\n");
    setColor(NORMAL);
}

//############################################################################

void show_menu(int color) {
    setColor(color);
    wprintf(L"\t            MENU\n");
    wprintf(L"\t┌────────┬────────┬────────┐\n");
    wprintf(L"\t│  ____  │  ____  │  ____  │\n");
    wprintf(L"\t│ ||S || │ ||D || │ ||Q || │ \n");
    wprintf(L"\t│ ||__|| │ ||__|| │ ||__|| │\n");
    wprintf(L"\t│ |/__\\| │ |/__\\| │ |/__\\| │\n");
    wprintf(L"\t│        │        │        │\n");
    wprintf(L"\t│ BORDAS │ BORDAS │  SAIR  │\n");
    wprintf(L"\t│SIMPLES │ DUPLAS │        │ \n");
    wprintf(L"\t└────────┴────────┴────────┘\n");
    setColor(NORMAL);

}

//############################################################################

void show_board(int c[9][9], char opcao_borda) {
    int linha = 0;

    // Definindo os caracteres da borda
    wchar_t b_h, b_v, b_hv,
            b_ce, b_cd, b_cs, b_ci,
            b_cse, b_csd, b_cie, b_cid;
    // Definindo os caracteres da borda simples
    wchar_t b_simples_h = L'─', b_simples_v = L'│', b_simples_hv = L'┼',
            b_simples_ce = L'├', b_simples_cd = L'┤', b_simples_cs = L'┬', b_simples_ci = L'┴',
            b_simples_cse = L'┌', b_simples_csd = L'┐', b_simples_cie = L'└', b_simples_cid = L'┘';
    // Definindo os caracteres da borda duplas
    wchar_t b_dupla_h = L'═', b_dupla_v = L'║', b_dupla_hv = L'╬',
            b_dupla_ce = L'╠', b_dupla_cd = L'╣', b_dupla_cs = L'╦', b_dupla_ci = L'╩',
            b_dupla_cse = L'╔', b_dupla_csd = L'╗', b_dupla_cie = L'╚', b_dupla_cid = L'╝';
    // Definindo borda de escolha
    if(opcao_borda == 'S' || opcao_borda == 's') {
        b_h = b_simples_h; b_v = b_simples_v; b_hv = b_simples_hv;
        b_ce = b_simples_ce; b_cd = b_simples_cd; b_cs = b_simples_cs; b_ci = b_simples_ci;
        b_cse = b_simples_cse; b_csd = b_simples_csd; b_cie = b_simples_cie; b_cid = b_simples_cid;
    }
    else if (opcao_borda == 'D' || opcao_borda == 'd') {
        b_h = b_dupla_h; b_v = b_dupla_v; b_hv = b_dupla_hv;
        b_ce = b_dupla_ce; b_cd = b_dupla_cd; b_cs = b_dupla_cs; b_ci = b_dupla_ci;
        b_cse = b_dupla_cse; b_csd = b_dupla_csd; b_cie = b_dupla_cie; b_cid = b_dupla_cid;
    }

    // Imprimindo o tabuleiro no formato UTF-16
    for(int i = 0; i < 19; i++){
        if(i == 0) { // Linha Superior
            setColor(FORTE);
            wprintf(L"\n\t  %lc", b_cse);
            for(int j = 0; j < 9; j++) {
                wprintf(L"%lc%lc%lc", b_h, b_h, b_h);
                if(j != 8) {
                    wprintf(L"%lc", b_cs);
                }
                else {
                    wprintf(L"%lc\n", b_csd);
                }
            }
            setColor(FRACA);
        }
        if(i == 18) { // Linha Inferior
            setColor(FORTE);
            wprintf(L"\t  %lc", b_cie);
            for(int j = 1; j <= 9; j++) {
                wprintf(L"%lc%lc%lc", b_h, b_h, b_h);
                if(j != 9) {
                    wprintf(L"%lc", b_ci);
                }
                else {
                    wprintf(L"%lc\n", b_cid);
                }
            }
        }
        if(i % 2) { // Linha com os campos
            setColor(NORMAL);
            wprintf(L"\t%ld ", 10 - (linha + 1));
            setColor(FORTE);
            wprintf(L"%lc", b_v);
            setColor(FRACA);
            for(int j = 0; j < 9; j++) {
                wprintf(L"%lc", ' ');
                setColor(FORTE);
                wprintf(L"%lc", c[linha][j] == 0 ? ' ' : c[linha][j] + '0');
                setColor(FRACA);
                wprintf(L"%lc", ' ');
                if(!((j + 1) % 3)) {
                    setColor(FORTE);
                    wprintf(L"%lc", b_v);
                    setColor(FRACA);
                }
                else {
                    wprintf(L"%lc", b_v);
                }
            }
            linha++;
            wprintf(L"\n");
        }

        if(!(i % 2) && i != 0 && i != 6 && i != 12 && i != 18) {
            setColor(FORTE);
            wprintf(L"\t  %lc", b_ce);
            setColor(FRACA);
            for(int j = 0; j < 9; j++) {
                if(!((j + 1) % 3) && !(i % 6)) {
                    setColor(FORTE);
                }
                else {
                    setColor(FRACA);
                }
                wprintf(L"%lc%lc%lc", b_h, b_h, b_h);
                if((j + 1) != 9) {
                    if(!((j + 1) % 3)) {
                        setColor(FORTE);
                    }
                    else {
                        setColor(FRACA);
                    }
                    wprintf(L"%lc", b_hv);
                }
                else {
                    setColor(FORTE);
                    wprintf(L"%lc\n", b_cd);
                    setColor(FRACA);
                }
            }
        }

        if(i == 6 || i == 12) {
            setColor(FORTE);
            wprintf(L"\t  %lc", b_ce);
            for(int j = 0; j < 9; j++) {
                wprintf(L"%lc%lc%lc", b_h, b_h, b_h);
                if(j != 8) {
                    wprintf(L"%lc", b_hv);
                }
                else {
                    wprintf(L"%lc\n", b_cd);
                }
            }
            setColor(FRACA);
        }
    }
    setColor(NORMAL);
    wprintf(L"\t    a   b   c   d   e   f   g   h   i \n");

}

void show_board2(int c[9][9], char opcao_borda) {
    int linha = 0;

    // Definindo os caracteres da borda
    wchar_t b_h, b_v, b_hv,
            b_ce, b_cd, b_cs, b_ci,
            b_cse, b_csd, b_cie, b_cid;
    // Definindo os caracteres da borda simples
    wchar_t b_simples_h = L'─', b_simples_v = L'│', b_simples_hv = L'┼',
            b_simples_ce = L'├', b_simples_cd = L'┤', b_simples_cs = L'┬', b_simples_ci = L'┴',
            b_simples_cse = L'┌', b_simples_csd = L'┐', b_simples_cie = L'└', b_simples_cid = L'┘';
    // Definindo os caracteres da borda duplas
    wchar_t b_dupla_h = L'═', b_dupla_v = L'║', b_dupla_hv = L'╬',
            b_dupla_ce = L'╠', b_dupla_cd = L'╣', b_dupla_cs = L'╦', b_dupla_ci = L'╩',
            b_dupla_cse = L'╔', b_dupla_csd = L'╗', b_dupla_cie = L'╚', b_dupla_cid = L'╝';
    // Definindo borda de escolha
    if(opcao_borda == 'S' || opcao_borda == 's') {
        b_h = b_simples_h; b_v = b_simples_v; b_hv = b_simples_hv;
        b_ce = b_simples_ce; b_cd = b_simples_cd; b_cs = b_simples_cs; b_ci = b_simples_ci;
        b_cse = b_simples_cse; b_csd = b_simples_csd; b_cie = b_simples_cie; b_cid = b_simples_cid;
    }
    else if (opcao_borda == 'D' || opcao_borda == 'd') {
        b_h = b_dupla_h; b_v = b_dupla_v; b_hv = b_dupla_hv;
        b_ce = b_dupla_ce; b_cd = b_dupla_cd; b_cs = b_dupla_cs; b_ci = b_dupla_ci;
        b_cse = b_dupla_cse; b_csd = b_dupla_csd; b_cie = b_dupla_cie; b_cid = b_dupla_cid;
    }
    //LINHA 1, PARTE SUPERIOR
    setColor(FORTE);
    wprintf(L"\n\t  %lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n",
        b_cse, b_h, b_h, b_h, b_cs, b_h, b_h, b_h, b_cs, b_h, b_h, b_h, b_cs, b_h, b_h, b_h, b_cs, b_h, b_h, b_h,
        b_cs, b_h, b_h, b_h, b_cs, b_h, b_h, b_h, b_cs, b_h, b_h, b_h, b_cs, b_h, b_h, b_h, b_csd);
    setColor(FRACA);

    wprintf(L"\t9 %lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc\n",
        b_v, ' ', c[0][0], ' ', b_v, ' ', c[0][1], ' ', b_v, ' ', c[0][2], ' ', b_v, ' ', c[0][3], ' ', b_v, ' ', c[0][4], ' ',
        b_v, ' ', c[0][5], ' ', b_v, ' ', c[0][6], ' ', b_v, ' ', c[0][7], ' ', b_v, ' ', c[0][8], ' ', b_v);

    //LINHA 2, PARTE SUPERIOR
    wprintf(L"\t  %lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n",
        b_ce, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h,
        b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_cd);

    wprintf(L"\t8 %lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc\n",
        b_v, ' ', c[1][0], ' ', b_v, ' ', c[1][1], ' ', b_v, ' ', c[1][2], ' ', b_v, ' ', c[1][3], ' ', b_v, ' ', c[1][4], ' ',
        b_v, ' ', c[1][5], ' ', b_v, ' ', c[1][6], ' ', b_v, ' ', c[1][7], ' ', b_v, ' ', c[1][8], ' ', b_v);

    //LINHA 3, PARTE SUPERIOR
    wprintf(L"\t  %lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n",
        b_ce, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h,
        b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_cd);

    wprintf(L"\t7 %lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc\n",
        b_v, ' ', c[2][0], ' ', b_v, ' ', c[2][1], ' ', b_v, ' ', c[2][2], ' ', b_v, ' ', c[2][3], ' ', b_v, ' ', c[2][4], ' ',
        b_v, ' ', c[2][5], ' ', b_v, ' ', c[2][6], ' ', b_v, ' ', c[2][7], ' ', b_v, ' ', c[2][8], ' ', b_v);

    //LINHA 4, PARTE SUPERIOR
    setColor(FORTE);
    wprintf(L"\t  %lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n",
        b_ce, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h,
        b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_cd);
    setColor(FRACA);

    wprintf(L"\t6 %lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc\n",
        b_v, ' ', c[3][0], ' ', b_v, ' ', c[3][1], ' ', b_v, ' ', c[3][2], ' ', b_v, ' ', c[3][3], ' ', b_v, ' ', c[3][4], ' ',
        b_v, ' ', c[3][5], ' ', b_v, ' ', c[3][6], ' ', b_v, ' ', c[3][7], ' ', b_v, ' ', c[3][8], ' ', b_v);

    //LINHA 5, PARTE SUPERIOR
    wprintf(L"\t  %lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n",
        b_ce, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h,
        b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_cd);

    wprintf(L"\t5 %lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc\n",
        b_v, ' ', c[4][0], ' ', b_v, ' ', c[4][1], ' ', b_v, ' ', c[4][2], ' ', b_v, ' ', c[4][3], ' ', b_v, ' ', c[4][4], ' ',
        b_v, ' ', c[4][5], ' ', b_v, ' ', c[4][6], ' ', b_v, ' ', c[4][7], ' ', b_v, ' ', c[4][8], ' ', b_v);

    //LINHA 6, PARTE SUPERIOR
    wprintf(L"\t  %lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n",
        b_ce, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h,
        b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_cd);

    wprintf(L"\t4 %lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc\n",
        b_v, ' ', c[5][0], ' ', b_v, ' ', c[5][1], ' ', b_v, ' ', c[5][2], ' ', b_v, ' ', c[5][3], ' ', b_v, ' ', c[5][4], ' ',
        b_v, ' ', c[5][5], ' ', b_v, ' ', c[5][6], ' ', b_v, ' ', c[5][7], ' ', b_v, ' ', c[5][8], ' ', b_v);

    //LINHA 7, PARTE SUPERIOR
    setColor(FORTE);
    wprintf(L"\t  %lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n",
        b_ce, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h,
        b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_cd);
    setColor(FRACA);

    wprintf(L"\t3 %lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc\n",
        b_v, ' ', c[6][0], ' ', b_v, ' ', c[6][1], ' ', b_v, ' ', c[6][2], ' ', b_v, ' ', c[6][3], ' ', b_v, ' ', c[6][4], ' ',
        b_v, ' ', c[6][5], ' ', b_v, ' ', c[6][6], ' ', b_v, ' ', c[6][7], ' ', b_v, ' ', c[6][8], ' ', b_v);

    //LINHA 8, PARTE SUPERIOR
    wprintf(L"\t  %lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n",
        b_ce, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h,
        b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_cd);

    wprintf(L"\t2 %lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc\n",
        b_v, ' ', c[7][0], ' ', b_v, ' ', c[7][1], ' ', b_v, ' ', c[7][2], ' ', b_v, ' ', c[7][3], ' ', b_v, ' ', c[7][4], ' ',
        b_v, ' ', c[7][5], ' ', b_v, ' ', c[7][6], ' ', b_v, ' ', c[7][7], ' ', b_v, ' ', c[7][8], ' ', b_v);

    //LINHA 9, PARTE SUPERIOR
    wprintf(L"\t  %lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n",
        b_ce, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h,
        b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_hv, b_h, b_h, b_h, b_cd);

    wprintf(L"\t1 %lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc%lc%ld%lc%lc\n",
        b_v, ' ', c[8][0], ' ', b_v, ' ', c[8][1], ' ', b_v, ' ', c[8][2], ' ', b_v, ' ', c[8][3], ' ', b_v, ' ', c[8][4], ' ',
        b_v, ' ', c[8][5], ' ', b_v, ' ', c[8][6], ' ', b_v, ' ', c[8][7], ' ', b_v, ' ', c[8][8], ' ', b_v);

    // LINHA INFERIOR
    setColor(FORTE);
    wprintf(L"\t  %lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n",
        b_cie, b_h, b_h, b_h, b_ci, b_h, b_h, b_h, b_ci, b_h, b_h, b_h, b_ci, b_h, b_h, b_h, b_ci, b_h, b_h, b_h,
        b_ci, b_h, b_h, b_h, b_ci, b_h, b_h, b_h, b_ci, b_h, b_h, b_h, b_ci, b_h, b_h, b_h, b_cid);
    wprintf(L"\t    a   b   c   d   e   f   g   h   i \n");
    setColor(NORMAL);
}

void imprimir_campos(int campos[9][9]) {
    wprintf(L"\n\t");
    for(int linha = 0; linha < 9; linha++) {
        for(int coluna = 0; coluna < 9; coluna++) {
            wprintf(L" %d ", campos[linha][coluna]);
        }
        wprintf(L"\n\t");
    }
}

void clear_board(int cells[9][9]) {
    int i, j;
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++) {
            cells[i][j] = 0;
        }
    }
}

void converter_entrada(char player_entrada[2], int coluna, int linha) {
    switch(toupper(player_entrada[0])) {
        case 'A':
            coluna = 0;
            break;
        case 'B':
            coluna = 1;
            break;
        case 'C':
            coluna = 2;
            break;
        case 'D':
            coluna = 3;
            break;
        case 'E':
            coluna = 4;
            break;
        case 'F':
            coluna = 5;
            break;
        case 'G':
            coluna = 6;
            break;
        case 'H':
            coluna = 7;
            break;
        case 'I':
            coluna = 8;
            break;
    }
    linha = 9 - player_entrada[1];
}

// Função para alterar a cor do texto no CMD
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // Obtém o manipulador da saída padrão (CMD)
    SetConsoleTextAttribute(hConsole, color);           // Define o atributo da cor
}
