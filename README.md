# 🚢 Batalha Naval — Implementação Modular em C

Trabalho desenvolvido para a disciplina **Programação de Inovação e Fundamentos de Sistemas de Informação**, na **CESAR School**.

---

## 📘 Visão Geral do Projeto

Este repositório contém uma implementação robusta do jogo **Batalha Naval** via linha de comando. O foco do projeto foi a aplicação de **programação estruturada**, **gerenciamento manual de memória** e **modularização** do código para facilitar a manutenção e escalabilidade.

O sistema permite partidas contra o computador (ou entre jogadores), com funcionalidades como posicionamento automático de frotas e tabuleiros de tamanho dinâmico.

---

## 🔧 Recursos Implementados

* **Tabuleiro Dinâmico:** O tamanho do grid é definido pelo usuário e alocado em tempo de execução.
* **Posicionamento Inteligente:** Algoritmo que distribui navios aleatoriamente sem sobreposição (`rnd` + `game`).
* **Tradutor de Coordenadas:** Sistema que converte inputs humanos (ex: "B5") para índices de matriz (ex: `1, 4`) via tabela ASCII.
* **Feedback Visual:** Interface que oculta navios inimigos (Fog of War) e revela apenas tiros e acertos.

---

## 🏗 Arquitetura e Módulos

O código foi organizado em módulos com responsabilidades únicas ("Separation of Concerns"):

### 1. `rnd` (O Dado)
Responsável pela estocasticidade do jogo.
* **Funcionamento:** Utiliza `srand(time(NULL))` para garantir sementes únicas a cada execução.
* **Função:** `gerarNumero(min, max)` garante integridade matemática nos sorteios de coordenadas.

### 2. `board` (O Tabuleiro)
Gerencia a estrutura de dados do grid.
* **Estruturas:** Utiliza `enum CellState` (WATER, SHIP, HIT, MISS) para legibilidade.
* **Destaque Técnico:** Em vez de uma matriz estática, utiliza **Vetor Único (1D)** com aritmética de ponteiros `(linha * largura + coluna)`. Isso permite alocar tabuleiros de qualquer tamanho usando `malloc`.

### 3. `fleet` (A Frota)
Gerencia as entidades (navios) do jogo.
* **Controle de Dano:** Cada `Ship` possui contadores de `hits`. A função `verificarFrotaDestruida` itera sobre a frota para determinar o fim do jogo (Game Over).

### 4. `game` (O Cérebro)
Centraliza as regras de negócio e o estado da partida.
* **Validação:** Impede tiros duplicados e posicionamentos inválidos (fora do mapa ou colisão).
* **Mecânica de Tiro:** Processa o ataque, atualiza o estado da célula (`HIT`/`MISS`) e notifica o jogador.

### 5. `io` (A Interface)
Camada de abstração para Entrada/Saída.
* **Parsing:** Converte caracteres para inteiros (ex: `'A'` torna-se `0` através de `'B' - 'A' = 1`).
* **Renderização:** Exibe o tabuleiro condicionalmente (escondendo navios não atingidos do adversário).

### 6. `main` (O Maestro)
Orquestrador do ciclo de vida do software.
* Inicializa sementes e estruturas.
* Executa o *Game Loop*.
* Garante a limpeza de memória (`free`) ao encerramento.

---

## 👥 Equipe

| Aluno | Email |
| :--- | :--- |
| **Lucas Henrique Florencio Siqueira** | [lhfs@cesar.school](mailto:lhfs@cesar.school) |
| **Guilherme Henrique Leite Nóbrega** | [ghln@cesar.school](mailto:ghln@cesar.school) |

---

## 💻 Conceitos de C Aplicados

Para garantir a eficiência e a robustez do sistema, foram aplicados os seguintes conceitos avançados da linguagem:

* **Alocação Dinâmica (`malloc`/`free`):** O tabuleiro não tem tamanho fixo. A memória é solicitada ao sistema operacional conforme a configuração da partida e devolvida estritamente ao final, prevenindo *Memory Leaks*.
* **Ponteiros:** Utilizados extensivamente para passar referências de grandes estruturas (`Board`, `Game`) entre funções sem a necessidade de cópias custosas de dados.
* **Structs e Enums:** Agrupamento lógico de dados (ex: `Ship` contém nome, tamanho e vida) e substituição de "números mágicos" por nomes legíveis (`CELL_WATER` vs `0`).

---

## 🚀 Compilação e Execução

### Pré-requisitos
* Compilador **GCC**
* **Make** (Opcional, mas recomendado)

### Como rodar

1.  Clone o repositório.
2.  No terminal, execute:

```bash
gcc -o batalha_naval src/*.c -I src
./batalha_naval
