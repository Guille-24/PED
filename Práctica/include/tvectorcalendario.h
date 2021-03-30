//
//  TVectorCalendario.hpp
//  PED
//
//  Created by Guillermo Jiménez on 28/2/21.
//

#ifndef tvectorcalendario_hpp
#define tvectorcalendario_hpp

#include <stdio.h>
#include <string.h>
#include <iostream>
#include "tcalendario.h"
using namespace std;

class TVectorCalendario {
    private:
        TCalendario *c;
        int tamano;
        TCalendario error;
        void Copia(const TVectorCalendario &);

    public:
        // Constructor por defecto
        TVectorCalendario();
        // Constructor a partir de un tamaño
        TVectorCalendario(int);
        // Constructor de copia
        TVectorCalendario(const TVectorCalendario &);
        // Destructor
        ~TVectorCalendario();
        // Sobrecarga del operador asignación
        TVectorCalendario & operator=(const TVectorCalendario &);
        // Sobrecarga del operador igualdad
        bool operator==(const TVectorCalendario &);
        // Sobrecarga del operador desigualdad
        bool operator!=(const TVectorCalendario &);
        // Sobrecarga del operador corchete (parte IZQUIERDA)
        TCalendario & operator[](int);
        // Sobrecarga del operador corchete (parte DERECHA)
        TCalendario operator[](int) const;
        // Tamaño del vector (posiciones TOTALES)
        int Tamano();
        // Cantidad de posiciones OCUPADAS (no vacías) en el vector
        int Ocupadas();
        // Devuelve TRUE si existe el calendario en el vector
        bool ExisteCal(const TCalendario &);
        // Mostrar por pantalla mensajes de TCalendario en el vector, de fecha IGUAL O POSTERIOR a la pasada
        void MostrarMensajes(int,int,int);
        // REDIMENSIONAR el vectorde TCalendario
        bool Redimensionar(int);

        // Sobrecarga del operador salida
        friend ostream & operator<<(ostream &, const TVectorCalendario &);
};

#endif