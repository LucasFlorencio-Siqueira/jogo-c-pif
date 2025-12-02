#include <stdio.h>
#include "rnd.h"
#include "io.h"
#include "game.h"

int main() {
    iniciarAleatorio();
    
    int tamBoard = 10;
    char modo = 'A';
    char nome1[32] = "Alice";
    char nome2[32] = "Bob";
    int sair = 0;

    while (!sair) {
        int opcao = menuPrincipal();
        
        if (opcao == 1) {
            limparTela();
            pedirNomes(nome1, nome2);
            
            Game* jogo = criarJogo(tamBoard, tamBoard, nome1, nome2);
            
            if (modo == 'A') {
                posicionarFrotaAuto(&jogo->p1);
                posicionarFrotaAuto(&jogo->p2);
            }
            
            while (!jogo->game_over) {
                limparTela();
                Player* atual = (jogo->current_player == 1) ? &jogo->p1 : &jogo->p2;
                Player* inimigo = (jogo->current_player == 1) ? &jogo->p2 : &jogo->p1;
                
                mostrarTelaJogo(atual, inimigo);
                
                int r, c;
                while (!pedirTiro(&r, &c, tamBoard));
                
                CellState res = processarTiro(atual, inimigo, r, c);
                
                char* nomeNavio = NULL;
                if (res == CELL_HIT) {
                    Cell* cel = pegarCelula(&inimigo->board, r, c);
                    if (cel) {
                        nomeNavio = inimigo->fleet.ships[cel->ship_id].name;
                    }
                }
                mostrarMensagemTiro(res, nomeNavio);
                
                if (verificarFrotaDestruida(&inimigo->fleet)) {
                    jogo->game_over = 1;
                    mostrarVencedor(atual);
                } else {
                    alternarTurno(jogo);
                }
            }
            destruirJogo(jogo);
            
        } else if (opcao == 2) {
            configurarJogo(&tamBoard, &modo);
        } else if (opcao == 3) {
            sair = 1;
        }
    }
    
    return 0;
}
