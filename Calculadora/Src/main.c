#include <stdint.h>
#include "stm32lm053xx.h"
#include "decoders.h"

int main(void)
{

    // Habilitar el reloj para los puertos GPIOC y GPIOB
    // Esto es necesario para poder configurar y utilizar los pines de estos puertos
    RCC->IOPENR |= (1 << 2) | (1 << 1) | (1 << 0);
    ///////////////////////
    //CATODOS DEL DISPLAY//
    ///////////////////////
    // Configurar los pines del puerto GPIOC como salida
   // Estos pines se utilizarán para controlar los dígitos de los displays
    uint32_t portC_masks = (0b01 << 8) | (0b01 << 10) | (0b01 << 12) | (0b01 << 14) | (0b01 << 16) | (0b01 << 18);
    GPIOC->MODER &= ~(0b11 << 8 | 0b11 << 10 | 0b11 << 12 | 0b11 << 14 | 0b11 << 16 | 0b11 << 18);
    GPIOC->MODER |= portC_masks;

    //////////////////////////////
    ////////// SEGMENTOS DEL DISPLAY /////
    //////////////////////////////
    // Configurar los pines del puerto GPIOB como salida
   // Estos pines se utilizarán para controlar los segmentos de los displays
    GPIOB->MODER &= ~(0xFFFF); // Limpiar los modos de los primeros 8 pines del puerto B(pines 0 a 7)
    uint32_t portB_display_masks = (0b01 << 0) | (0b01 << 2) | (0b01 << 4) | (0b01 << 6) |
                                   (0b01 << 8) | (0b01 << 10) | (0b01 << 12) | (0b01 << 14);
    GPIOB->MODER |= portB_display_masks; // Definir estos pines del display como salida
    //////////////////////
    //COLUMNAS DEL KEYPAD
    ////////////////////
   // Configurar los pines del puerto GPIOB como salida
   // Estos pines se utilizarán para controlar las columnas de la matriz del teclado
    GPIOB->MODER &= ~((0b11 << 24) | (0b11 << 26) | (0b11 << 28) | (0b11 << 30)); // Limpiar la configuración actual para los pines 12 a 15
    GPIOB->MODER |= ((0b01 << 24) | (0b01 << 26) | (0b01 << 28) | (0b01 << 30)); // Establecer los pines PB12 a PB15 como salidas

    ////////////////////////////////////////////////////
    /////////////////////////FILAS DEL KEYPAD//////////////
    // Configurar los pines del 16 al 22 de GPIOB con resistencias pull-up
    GPIOB->PUPDR &= ~((0b11 << 16) | (0b11 << 18) | (0b11 << 20) | (0b11 << 22)); // Limpiar configuración de pull-up/pull-down
    GPIOB->PUPDR |= ((0b01 << 16) | (0b01 << 18) | (0b01 << 20) | (0b01 << 22)); // Establecer pull-up para pines de entrada

    // Configurar los pines PB8 a PB11 como entrada (teclado matricial)
    GPIOB->MODER &= ~((0b11 << 16) | (0b11 << 18) | (0b11 << 20) | (0b11 << 22)); // Limpiar la configuración actual para los pines 8 a 11

while (1) {
    for (int col = 0; col < 4; col++) {
        GPIOB->ODR = (0xF << 12); // Desactiva todas las columnas
        GPIOB->ODR &= ~(1 << (12 + col)); // Activa solo la columna actual

        delay_ms(10); // Deja tiempo para la estabilización

        uint32_t filas = GPIOB->IDR & (0xF << 8); // Lee el estado de las filas

        for (int fila = 0; fila < 4; fila++) {
            if (!(filas & (1 << (fila + 8)))) { // Detecta si alguna fila está activa (presionada)
                uint32_t numero_tecla = col * 4 + fila; // Ajusta el cálculo de numero_tecla

                    // Procesamiento basado en el número de la tecla
                    if (numero_tecla == KEY_D_INDEX) {                    // Implementación para la tecla igual "="
                        int sumar_millares = 0;
                        int unidades = number_to_key(primero_digito);
                        int decenas = number_to_key(segundo_digito);
                        int centenas = number_to_key(tercer_digito);
                        uint32_t millares = number_to_key(cuarto_digito);
                        sumar_millares = unidades + (decenas * 10) + (centenas * 100) + (millares * 1000);
                        guardar_decenas = (uint32_t)(guardar_decenas + sumar_millares);
                        primero_digito = segundo_digito = tercer_digito = 0xff;
                    } else if (numero_tecla == KEY_A_INDEX) {                     // Implementación para la tecla de suma
                        if (guardar_decenas != 0) {
                            int sumar_millares = 0;
                            int unidades = number_to_key(primero_digito);
                            int decenas = number_to_key(segundo_digito);
                            int centenas = number_to_key(tercer_digito);
                            uint32_t millares = number_to_key(cuarto_digito);
                            sumar_millares = unidades + (decenas * 10) + (centenas * 100);
                            guardar_decenas = (uint32_t)(guardar_decenas + sumar_millares);
                            unidades = guardar_decenas % 10;
                            decenas = ((guardar_decenas - unidades) % 100) / 10;
                            centenas = ((guardar_decenas - decenas - unidades) % 1000) / 100;
                            millares = ((guardar_decenas - centenas - decenas - unidades) % 10000) / 1000;
                            primero_digito = index_to_key(unidades);
                            segundo_digito = index_to_key(decenas);
                            tercer_digito = index_to_key(centenas);
                            cuarto_digito = index_to_key(millares);
                            guardar_decenas = 0;
                        }
                    } else if (numero_tecla == KEY_B_INDEX) {                    // Implementación para la tecla de resta
                        if (guardar_decenas != 0) {
                            int sumar_millares = 0;
                            int unidades = number_to_key(primero_digito);
                            int decenas = number_to_key(segundo_digito);
                            int centenas = number_to_key(tercer_digito);
                            uint32_t millares = number_to_key(cuarto_digito);
                            sumar_millares = unidades + (decenas * 10) + (centenas * 100);
                            guardar_decenas = (uint32_t)(guardar_decenas - sumar_millares);
                            if (guardar_decenas > 999) guardar_decenas = 999;
                            unidades = guardar_decenas % 10;
                            decenas = ((guardar_decenas - unidades) % 100) / 10;
                            centenas = ((guardar_decenas - decenas - unidades) % 1000) / 100;
                            millares = ((guardar_decenas - centenas - decenas - unidades) % 10000) / 1000;
                            primero_digito = index_to_key(unidades);
                            segundo_digito = index_to_key(decenas);
                            tercer_digito = index_to_key(centenas);
                            cuarto_digito = index_to_key(millares);
                            guardar_decenas = 0;
                        }
                    } else if (numero_tecla == KEY_C_INDEX) {                    // Implementación para la tecla de multiplicación
                        if (guardar_decenas != 0) {
                            int sumar_millares = 0;
                            int unidades = number_to_key(primero_digito);
                            int decenas = number_to_key(segundo_digito);
                            int centenas = number_to_key(tercer_digito);
                            uint32_t millares = number_to_key(cuarto_digito);
                            sumar_millares = unidades + (decenas * 10) + (centenas * 100);
                            guardar_decenas = (uint32_t)(guardar_decenas * sumar_millares);
                            unidades = guardar_decenas % 10;
                            decenas = ((guardar_decenas - unidades) % 100) / 10;
                            centenas = ((guardar_decenas - decenas - unidades) % 1000) / 100;
                            millares = ((guardar_decenas - centenas - decenas - unidades) % 10000) / 1000;
                            primero_digito = index_to_key(unidades);
                            segundo_digito = index_to_key(decenas);
                            tercer_digito = index_to_key(centenas);
                            cuarto_digito = index_to_key(millares);
                            guardar_decenas = 0;
                        }
                    } else if (numero_tecla == KEY_F_INDEX) {                     // Implementación para la tecla de división
                        if (guardar_decenas != 0) {
                            int div_value = 0;
                            int unidades = number_to_key(primero_digito);
                            int decenas = number_to_key(segundo_digito);
                            int centenas = number_to_key(tercer_digito);
                            div_value = unidades + (decenas * 10) + (centenas * 100);
                            if (div_value != 0) {                                   // ELIMINAR o BORRAR
                                guardar_decenas = (uint32_t)(guardar_decenas / div_value);
                                unidades = guardar_decenas % 10;
                                decenas = (guardar_decenas / 10) % 10;
                                centenas = (guardar_decenas / 100) % 10;
                                primero_digito = index_to_key(unidades);
                                segundo_digito = index_to_key(decenas);
                                tercer_digito = index_to_key(centenas);
                            }
                            guardar_decenas = 0;
                        }
                    } else if (numero_tecla == 12) {
                        primero_digito = 0xFF;
                        segundo_digito = 0xFF;
                        tercer_digito = 0xFF;
                        cuarto_digito = 0xFF;
                        quinto_digito = 0xFF;
                        guardar_decenas = 0;
                    } else {
                        tercer_digito = segundo_digito;
                        segundo_digito = primero_digito;
                        primero_digito = numero_tecla;
                    }

                while (!(GPIOB->IDR & (1 << (fila + 8)))); // Espera a que la tecla se suelte

                break; // Sale del bucle de filas para evitar múltiples lecturas
                }
            }
            GPIOB->ODR |= (1 << (12 + col));
        }

        // Actualizar los valores de los displays
        actualizar_valores();
        guardar_decenas = guardar_decenas % 1000;
    }

}

void delay_ms(uint16_t n) {
    for (uint32_t i = 0; i < n * 10; i++) {
        __asm__("NOP");
    }
}




