# README - Atividade 1: Temporizador Periódico

## Descrição da Atividade

Utilizando o ambiente de simulação Wokwi e o Pico W, por meio deste projeto foi desenvolvido um semáforo onde cada sinal luminoso dura 3 ms.
Ainda foi desenvolvido um sistema para sinalização por áudio para pedestres com deficiência visual.

## Componentes Necessários

1. **Microcontrolador**: Raspberry Pi Pico W
2. **LEDs**: 03 LEDs (vermelho, amarelo e verde)
3. **Resistores**: 03 resistores de 330 Ω

## Fluxo de Funcionamento

O semáforo operará da seguinte maneira:

1. O LED **vermelho** acende por **3 segundos**, enquanto os outros permanecem apagados;
2. Sinal sonoro indica que a passagem está liberada para pedestres por **2 segundos**;
3. Sinal sonoro de advertência de encerramento de travessia **1 segundo**;
4. O LED **amarelo** acende por **3 segundos**, enquanto os outros permanecem apagados;
5. O LED **verde** acende por **3 segundos**, enquanto os outros permanecem apagados;
6. O ciclo se repete continuamente.

## Como Executar

Para utilizar o programa com o simulador Wokwi, o usuário deve:

1. Clonar este repositório: git clone https://github.com/saturnino028/U4C51234E_Temporizadores_Q1.git;
2. Usando a extensão Raspberry Pi Pico importar o projeto;
3. Compilar o código e clicar no arquivo diagram.json.

## Possíveis Melhorias
- Implementar botões para simular a presença de pedestres ou veículos.
- Utilizar PWM para controlar a intensidade dos LEDs e volume dos buzzer.
- Adicionar comunicação sem fio para controle remoto do semáforo.

---
Desenvolvido para a capacitação em Sistemas Embarcados oferecida pela CEPEDI utilizando o Raspberry Pi Pico W, o simulador Wokwi e o Pico SDK.
