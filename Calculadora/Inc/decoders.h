/*
 * decoders.h
 *
 *  Created on: Apr 7, 2024
 *      Author: Andrés Ramos
 */

#ifndef DECODERS_H_
#define DECODERS_H_

#include "stm32lm053xx.h"  // Asegúrate de incluir el archivo correcto para el hardware específico

// Definición de las funciones
void delay_ms(uint16_t n);
void actualizar_valores(void);
uint32_t descodificar(uint32_t value_to_decode);
void descodificar_decimal(uint32_t value);

const uint32_t mostrar_tecla[] = {
    uno, dos, tres, A,
    cuatro, cinco, seis, B,
    siete, ocho, nueve, C,
    E, cero, F, D
};

// Variables para almacenar los dígitos y el valor acumulado
uint32_t primero_digito = 0xFF;
uint32_t segundo_digito = 0xFF;
uint32_t tercer_digito = 0xFF;
uint32_t cuarto_digito = 0xFF;
uint32_t quinto_digito = 0xFF;
uint32_t sexto_digito = 0xFF;
uint32_t guardar_decenas = 0;

// Actualizar los valores mostrados en los displays
void actualizar_valores(void) {
    // Apagar todos los dígitos y segmentos antes de actualizar
    GPIOC->BSRR = 0xFF00;
    GPIOB->BSRR = 0xFF00;

    if (cuarto_digito != 0xFF) {
        GPIOC->BSRR = 1 << 9;  // Enciende el cuarto dígito
        GPIOB->BSRR = descodificar(cuarto_digito);
        delay_ms(5);
    }

    if (tercer_digito != 0xFF) {
        GPIOC->BSRR = 1 << 8;  // Enciende el tercer dígito
        GPIOB->BSRR = descodificar(tercer_digito);
        delay_ms(5);
    }

    if (segundo_digito != 0xFF) {
        GPIOC->BSRR = 1 << 6;  // Enciende el segundo dígito
        GPIOB->BSRR = descodificar(segundo_digito);
        delay_ms(5);
    }

    if (primero_digito != 0xFF) {
        GPIOC->BSRR = 1 << 5;  // Enciende el primer dígito
        GPIOB->BSRR = descodificar(primero_digito);
        delay_ms(5);
    }
}

// Función para descodificar el número
uint32_t descodificar(uint32_t number) {
    if (number < sizeof(mostrar_tecla) / sizeof(mostrar_tecla[0])) {
        return mostrar_tecla[number];
    }
    return 13;  // Retorna un valor por defecto si el índice está fuera de rango
}

// Función para actualizar los dígitos basados en un nuevo valor decimal
void descodificar_decimal(uint32_t value) {
    if (value < 10) {
        cuarto_digito = tercer_digito;
        tercer_digito = segundo_digito;
        segundo_digito = primero_digito;
        primero_digito = value;
    }
}

#endif /* DECODERS_H_ */
