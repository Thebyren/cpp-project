#ifndef COLORES_H
#define COLORES_H

//la manera de implementar los colores es incluir la libreria primeramente
/*
#include<colores.h>

cout<<ROJO<<"texto rojo"<<RESET;

utilizamos los colores definidos, y luego reseteamos los colores de la terminal

*/
#define RESET "\033[0m"
#define NEGRO "\033[30m"
#define ROJO "\033[31m"
#define VERDE "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BLANCO "\033[37m"

// Estilos de texto
#define ESTILO_NORMAL "\033[0m"
#define ESTILO_NEGRITA "\033[1m"
#define ESTILO_SUBRAYADO "\033[4m"
#define ESTILO_INVERTIDO "\033[7m"

#endif // COLORES_H
