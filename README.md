
# Blackjack no Arduino

Simulação de uma jogatina de Blackjack (ou 21) no arduino, com possibilidade de jogar em Jogador contra Máquina ou Jogador contra Jogador.

## Como jogar

Na tela inicial, aperte o Botão A para iniciar uma partida Jogador contra Maquina, ou o Botão B para Jogador contra Jogador.

Independente do modo de jogo, quando for a vez dos respectivos jogadores (exeto a Maquina), aperte o Botão A para comprar uma carta ou Botão B para passar a vez.

A vez de cada jogador vai alternando até um deles atingir exatamente 21, ganhando a partida, ou ultrapassando 21, perdendo a partida. Casos os dois jogadores passem a vez consecutivamente, o jogo se encerra e vence quem chegou mais perto de 21. Ambos resultados retornam à tela inicial.

Os jogadores podem depositar, a qualquer momento, suas apostas (fichas) na caixa de arrecadação, as quais no fim da partida serão liberadas e direcionadas ao jogador vencedor.

## Como montar

Para reproduzir a versão despida do projeto, basta seguir o esquemático presente no arquivo "Blackjack no Arduino.png".
Posicione o Servo dispensador de fichas de maneira que empurre sem esforços suas fichas de aposta.

## Materiais
- Arduino Uno
- Protoboard (para auxílio)
- 2 Micro Servo 9g
- LCD 16x2
- 2 botões push
- Fonte de alimentação
- Fichas de aposta (qualquer disquinho serve)
