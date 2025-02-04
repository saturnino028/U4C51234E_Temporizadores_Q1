#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

/********************* Defines *********************/
#define buz_B   21

#define LED_Y   9
#define LED_G   11
#define LED_R   13

#define temp_semaforo 3000

/********************* Variaveis Globais *********************/
extern uint8_t controle_leds;


/********************* Prototipo de Funções *********************/

void init_pins_gpio();
void led_amarelo();
bool semaforo(struct repeating_timer *t);
void sinal_loc();
void sinal_init_trav();
void sinal_trav();
void sinal_adv();
void som_buz(uint16_t freq, uint16_t duration_ms);
void entrar_modo_gravacao();

#endif //MAIN_H