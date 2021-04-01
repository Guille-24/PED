//
//  TCalendario.hpp
//  PED
//
//  Created by Guillermo Jiménez on 11/2/21.
//

#ifndef tcalendario_hpp
#define tcalendario_hpp

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
class TCalendario {

    friend ostream & operator << (ostream &, const TCalendario &);
    
    private:
        int dia, mes, anyo;
        char* mensaje;
        
        // auxiliar de copia
        void Copia(const TCalendario &);
        
    
    public:
           // Constructor por defecto: inicializa dia, mes y anyo a 1/1/1900 y mensaje a NULL
           TCalendario ();
           // Constructor que inicializa calendario con parámetros pasados
           TCalendario(int dia, int mes, int anyo, char * mens);
           // Constructor copia
           TCalendario (const TCalendario &);
           // Destructor
           ~TCalendario();
           // Sobrecarga del operador asignación
           TCalendario & operator=(const TCalendario &);
           // Sobrecarga del operador: SUMA de fecha + un número de dias;
           TCalendario operator+(int);
           // Sobrecarga del operador: RESTA de fecha - un número de dias;
           TCalendario operator-(int);
           // Modifica la fecha incrementándola en un dia (con postincremento);
           TCalendario operator++(int);
           // Modifica la fecha incrementándola en un dia (con preincremento);
           TCalendario & operator++();
           // Modifica la fecha decrementándola en un dia (con postdecremento);
           TCalendario operator--(int);
           // Modifica la fecha decrementándola en un día (con predecremento);
           TCalendario & operator--();
           // Modifica la fecha
           bool ModFecha (int, int, int);
           // Modifica el mensaje
           bool ModMensaje(char *);
           // Sobrecarga del operador igualdad;
           bool operator ==(const TCalendario &);
           // Sobrecarga del operador desigualdad;
           bool operator !=(const TCalendario &);
           // Comprueba que las fechas estén correctas
           bool isUnderControl(int, int, int);
           // Sobrecarga del operador >; (ver ACLARACIÓN sobre ORDENACIÓN)
           bool operator>(const TCalendario &);
           // Sobrecarga del operador <; (ver ACLARACIÓN sobre ORDENACIÓN)
           bool operator<(const TCalendario &);
           // TCalendario vacío
           bool EsVacio();
           // Devuelve el día del calendario;
           int Dia();
           // Devuelve el mes del calendario;
           int Mes();
           // Devuelve el año del calendario;
           int Anyo();
           // Devuelve el mensaje del calendario;
           char *Mensaje();
           
};

#endif /* tcalendario_hpp */
