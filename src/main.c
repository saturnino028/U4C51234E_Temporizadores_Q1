#include "main.h"

struct repeating_timer timer; //Crie estrutura do tipo timer
volatile uint32_t passado = 0, temp_p_loc = 0;
volatile uint8_t contador = 0;

int main()
{
    stdio_init_all();
    init_pins_gpio();

    gpio_put(LED_R, 1);

    add_repeating_timer_ms(temp_semaforo, semaforo, NULL, &timer); //Temporizador para LEDs Semaforo (SDK)

    while (true)
    {
        if(!controle_leds) //LED Vermelho acesso
        {
            // Obtém o tempo atual em microssegundos
            if(contador<1)
            {
                uint32_t agora = to_us_since_boot(get_absolute_time());
                // Verifica se passou tempo suficiente desde o último evento
                if (agora - passado > 1000000) // 1000 ms
                {   
                    switch (contador)
                    {
                        case 0:
                            sinal_init_trav(); //Sinaliza travessia liberada para pedestre
                            sleep_ms(50);
                            som_buz(2500, 160); //Sinal Sonoro de travessia - Tabela 4.7
                            sleep_ms(50);
                            break;
                        case 1:
                            som_buz(2500, 160); //Sinal Sonoro de travessia - Tabela 4.7
                            sleep_ms(50);
                            break;
                        default:
                            break;
                    }
                    contador++;
                    passado  = agora;
                }
            }
            else
            {
                sinal_adv();
                contador = 0;
                sleep_ms(500);
            }
        }
        
        uint32_t temp_a_loc = to_us_since_boot(get_absolute_time()); //Tempo agora localização
        // Verifica se passou tempo suficiente desde o último evento
        if (temp_a_loc - temp_p_loc > 2000000) // Ativa o sinal de localização a cada 2s
        {
            som_buz(950, 60); //Sinal sonoro de localização - Tabela 4.7
            temp_p_loc = temp_a_loc;
        }
    }
}
