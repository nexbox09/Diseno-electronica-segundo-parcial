# Calculadora con 6 Displays Dobles de Siete Segmentos y Teclado Matricial


Este proyecto es una calculadora implementada usando una placa STM32L053R8, la cual se conecta a displays dobles de siete segmentos y un teclado matricial 4x4. Esta configuración permite realizar operaciones básicas de calculadora de manera eficiente y efectiva

Esta va ser la guía de cómo conectar y probar la calculadora utilizando el STM32L053R8, displays dobles de siete segmentos y un teclado matricial.

# Conexiones
![image](https://github.com/nexbox09/Diseno-electronica-segundo-parcial/assets/68700670/3eba5963-3636-4be2-8b1b-3f4b29091847)

## Características

- **Hardware Utilizado**: Placa STM32L053R8, displays de siete segmentos y teclado matricial 4x4.
- **Funcionalidades**: Soporta operaciones matemáticas básicas como suma, resta, multiplicación y división.
- **Interfaz Intuitiva**: Displays de fácil lectura y teclado matricial para la interacción del usuario.

## Estructura del Código

El proyecto está estructurado en varios archivos, los cuales contienen las definiciones y funciones clave para la operación de la calculadora:

- `main.c`: Contiene la lógica principal del programa, maneja la inicialización del hardware y el bucle principal de operación.
- `decoders.h`: Incluye funciones para la actualización de los displays y la decodificación de los valores a mostrar, así como la lógica para el manejo de las operaciones matemáticas.
- `stm32lm053xx.h`: Define estructuras y constantes para el manejo directo de los registros de la placa STM32L053R8, facilitando la configuración y el control de los periféricos utilizados.

## Funciones Clave

### `actualizar_valores`

- Esta función se encarga de actualizar los displays en base a los dígitos almacenados en las variables `primero_digito`, `segundo_digito`, etc.
- Utiliza la función `descodificar` para convertir los valores numéricos a los correspondientes códigos de los segmentos del display.

### `descodificar`

- Convierte un valor numérico en el código de segmentos correspondiente para su visualización, utilizando el array `mostrar_tecla` que mapea los números y letras a sus representaciones en el display.

### `delay_ms`

- Proporciona un retardo en milisegundos, esencial para la temporización entre la activación de los diferentes dígitos y la estabilización de los valores mostrados.

## Compilación y Carga con STM32CubeIDE

Para compilar y cargar tu proyecto en un dispositivo STM32 utilizando STM32CubeIDE, sigue estos pasos:

1. **Instalación**: Asegúrate de tener STM32CubeIDE instalado en tu computadora.
2. **Creación del Proyecto**: Abre STM32CubeIDE y crea un nuevo proyecto seleccionando el microcontrolador STM32L053R8.
3. **Configuración del Proyecto**: Configura los pines y periféricos necesarios en la vista Pinout & Configuration.
4. **Agregar Código Fuente**: Incorpora tus archivos de código (`main.c`, `decoders.h`, etc.) al proyecto.
5. **Compilación**: Utiliza el botón "Build" para compilar el proyecto y asegurarte de que no haya errores.
6. **Carga en el Dispositivo**: Conecta tu placa a la computadora y utiliza las opciones "Debug" o "Run" para cargar el programa.
7. **Depuración y Prueba**: Utiliza las herramientas de depuración de STM32CubeIDE para probar y depurar tu aplicación.

## Instrucciones de Uso

1. **Montaje**: Ensambler la placa STM32L053R8 con los displays y el teclado matricial según el diagrama de conexión proporcionado.
2. **Programación**: Cargar el código fuente en la placa usando un IDE compatible y herramientas de desarrollo para STM32.
3. **Operación**: Encender la calculadora y utilizar el teclado matricial para introducir operaciones y visualizar los resultados en los displays.
