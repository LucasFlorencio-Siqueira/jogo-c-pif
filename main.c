#include <stdio.h>
#include "rnd.h"
#include "io.h"
#include "game.h"

int main() {
    iniciarAleatorio();
    
    int tamTabuleiro = 10;
    char modoPosicionamento = 'A';
    char nome1[30] = "Jogador 1";
    char nome2[30] = "Jogador 2";
    int sair = 0;

    while (!sair) {
        int opcao = menuPrincipal();
        
        if (opcao == 1) {
            limparTela();
            pedirNomes(nome1, nome2);
            
            Jogo* jogo = criarJogo(tamTabuleiro, nome1, nome2);
            
            if (modoPosicionamento == 'A') {
                posicionarFrotaAuto(&jogo->j1);
                posicionarFrotaAuto(&jogo->j2);
            }
            
            while (!jogo->fimDeJogo) {
                limparTela();
                Jogador* atual = (jogo->jogadorAtual == 1) ? &jogo->j1 : &jogo->j2;
                Jogador* inimigo = (jogo->jogadorAtual == 1) ? &jogo->j2 : &jogo->j1;
                
                mostrarTelaJogo(atual, inimigo);
                
                int l, c;
                while (!pedirTiro(&l, &c, tamTabuleiro));
                
                EstadoCelula res = processarTiro(atual, inimigo, l, c);
                
                char* nomeNavio = NULL;
                if (res == ACERTO) {
                    Celula* cel = pegarCelula(inimigo->meuTabuleiro, l, c);
                    if (cel) {
                        nomeNavio = inimigo->frota.listaNavios[cel->idNavio].nome;
                    }
                }
                mostrarMensagemTiro(res, nomeNavio);
                
                if (verificarFrotaDestruida(&inimigo->frota)) {
                    jogo->fimDeJogo = 1;
                    mostrarVencedor(atual);
                } else {
                    alternarTurno(jogo);
                }
            }
            destruirJogo(jogo);
            
        } else if (opcao == 2) {
            configurarJogo(&tamTabuleiro, &modoPosicionamento);
        } else if (opcao == 3) {
            sair = 1;
        }
    }
    
    return 0;
}
