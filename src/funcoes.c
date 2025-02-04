#include "main.h"

uint8_t controle_leds = 0; //Variavel de controle de LEDs

/**
 * @brief inicia os pinos de GPIO
 */
void init_pins_gpio()
{
    //Configuração do buzzer B
    gpio_init(buz_B);
    gpio_set_dir(buz_B, GPIO_OUT);

    //Configuração do LED vermelho
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);

    //Configuração do Led Amarelo
    gpio_init(LED_Y);
    gpio_set_dir(LED_Y, GPIO_OUT);

    //Configuração do LED verde
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);

}

/**
 * @brief Combina as cores verde e vermelho para criar LED amarelo,
 *        acende LED amarelo conectado na GPIO 9 (apenas no Wokwi)
 */
void led_amarelo()
{
    gpio_put(LED_G, 1);
    gpio_put(LED_R, 1);
    gpio_put(LED_Y, 1);
}

/**
 * @brief Controla os leds a intervalos regulares definido na função add_repeating_timer_ms
 * @param t recebe ponteiro para a estrutura de dados do temporizador que chamou a função
 * @return retorna true para continuar com o timer ou false para parar
 */
bool semaforo(struct repeating_timer *t)
{
    if(controle_leds < 2)
        controle_leds++;
    else
        controle_leds = 0;

    printf("%d\n", controle_leds);

    switch (controle_leds)
    {
        case 0:
            gpio_put(LED_Y, 0);
            gpio_put(LED_G, 0);
            gpio_put(LED_R, 1);
            printf("Vermelho: %d ms\n", to_ms_since_boot(get_absolute_time()));
            break;
        case 1:
            gpio_put(LED_G, 0);
            gpio_put(LED_R, 0);
            gpio_put(LED_Y, 1);
            printf("Amarelo: %d ms\n", to_ms_since_boot(get_absolute_time()));
            break;
        case 2:
            gpio_put(LED_Y, 0);
            gpio_put(LED_R, 0);
            gpio_put(LED_G, 1);
            printf("Verde: %d ms\n", to_ms_since_boot(get_absolute_time()));
            break;
        default:
            break;
    }
}

/**
 * @brief coloca o PICO no modo de gravação
 */
void entrar_modo_gravacao() 
{
    printf("Entrando no modo de gravação...\n");
    reset_usb_boot(0, 0); 
}

/*** Funções Inclusão Pedestres Com Deficiência Visual ***/
/**
 * @brief as funções a seguir visam garantir autonomia e acesibilidade a deficientes visuais
 * e estão de acordo com a consulta pública disponível em: 
 * 
 * <https://www.gov.br/participamaisbrasil/inclusao-padroes-criterios-para-sinalizacao-semaforica>
 */

/**
 * @brief reproduz um tom puro
 * @param freq é a frequência do sinal
 * @param duration_ms é a duração do sinal em milisegundos
 */
void som_buz(uint16_t freq, uint16_t duration_ms)
{
    uint period = 1000000 / freq;  // Período do sinal em microssegundos
    uint cycles = (duration_ms * 1000) / period;  // Número de ciclos a gerar

    for (uint i = 0; i < cycles; i++) 
    {
        gpio_put(buz_B, 1);  // Liga o buzzer
        sleep_us(period / 2);  // Espera metade do período
        gpio_put(buz_B, 0);  // Desliga o buzzer
        sleep_us(period / 2);  // Espera metade do período
    }
}

/**
 * @brief Sinal sonoro de inicio do tempo de travessia - Tabela 4.7
 */
void sinal_init_trav()
{
    int steps = 15; // Número de passos para distribuir os 150 ms
    float f_init = 2000;
    float f_final = 500;
    float step_size = (f_init - f_final) / steps; // Quantidade de Hz por passo

    som_buz(f_init, 10);

    for(int i = 0; i < steps; i++)
    {
        float freq = f_init - (i * step_size);
        som_buz(freq, 10); // Cada tom dura 10 ms
    }
}

/**
 * @brief Sinal sonoro de advertência de encerramento de travessia
 */
void sinal_adv()
{
    som_buz(2500, 160); //Sinal Sonoro de travessia - Tabela 4.7
    sleep_ms(500);
    som_buz(2500, 160); //Sinal Sonoro de travessia - Tabela 4.7
}