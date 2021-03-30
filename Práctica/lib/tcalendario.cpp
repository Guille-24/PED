//
//  TCoordenada.cpp
//  PED
//
//  Created by Guillermo Jiménez on 11/2/21.
//

#include "tcalendario.h"
TCalendario::TCalendario(){
    dia = 1;
    mes = 1;
    anyo = 1900;
    mensaje = NULL;
}

bool TCalendario :: isUnderControl(int dia, int mes, int anyo){
    bool es = false;

    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || anyo < 1900){
        es = false;
    }
    else{
        if (mes == 4 || mes == 6 || mes == 9 || mes == 11){
            if (dia <= 30){
                es = true;
            }
        }
        else if (mes == 2){
            if ((anyo % 4 == 0) && ((anyo % 100 != 0) || (anyo % 400 == 0))){
                if (dia <= 29){
                    es = true;
                }
            }
            else{
                if (dia <= 28){
                    es = true;
                }
                else{
                    es = false;
                }
            }
        }
        else if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
            if (dia <= 31){
                es = true;
            }
        }
    }
    return es;
}

// Constructor que inicializa calendario con parámetros pasados
TCalendario :: TCalendario (int dia, int mes, int anyo, char * mens){
    bool prueba;

    if (isUnderControl(dia, mes, anyo) == true){
        this->dia = dia;
        this->mes = mes;
        this->anyo = anyo;

        if (mens == NULL){
            mensaje = NULL;
        } else{
            mensaje = new char[strlen(mens) + 1];
            strcpy(mensaje, mens);
        }
    } else{
        this->dia = 1;
        this->mes = 1;
        this->anyo = 1900;
        mensaje = NULL;
    }
}

TCalendario::TCalendario(const TCalendario &c){
    Copia(c);
}

void TCalendario::Copia(const TCalendario &c){
    dia = c.dia;
    mes = c.mes;
    anyo = c.anyo;
    if (c.mensaje != NULL){
        mensaje = new char[strlen(c.mensaje) + 1];
        strcpy(mensaje, c.mensaje);
    } else{
        mensaje = NULL;
    }
}

TCalendario::~TCalendario(){
    dia = 1;
    mes = 1;
    anyo = 1900;
    mensaje = NULL;
}

TCalendario &TCalendario::operator=(const TCalendario &c){
    if (this != &c){
        (*this).~TCalendario();
        Copia(c);
    }
    return *this;
}

//Sobrecarga del operador SUMA de fecha + un número de días
TCalendario TCalendario :: operator + (const int d){
    if (d >= 0){
        TCalendario s(*this);
        s.dia = dia + d;
        while (!isUnderControl(s.dia, s.mes, s.anyo)){
            if (s.mes == 12){
                s.dia -= 30;
                s.mes = 1;
                s.anyo++;
            }
            else if (s.mes == 2){
                if ((s.anyo % 4 == 0) && (s.anyo % 400 == 0) || (s.anyo % 100 != 0)){
                    s.dia = s.dia - 29;
                    s.mes++;
                } else {
                    s.dia = s.dia - 28;
                    s.mes++;
                }
            } else if (s.mes == 4 || s.mes == 6 || s.mes == 9 || s.mes == 11){
                s.dia = s.dia - 30;
                s.mes++;
            } else if (s.mes == 1 || s.mes == 3 || s.mes == 5 || s.mes == 7 || s.mes == 8 || s.mes == 10){
                s.dia = s.dia - 31;
                s.mes++;
            }
        }
    return s;
    }
}

// incrementa la fecha en un día (con postincremento)
TCalendario TCalendario:: operator++(int t)
{
	TCalendario tc(*this); // OBJETO TEMPORAL

	*this = *this + 1;
	return tc;
}

// incrementa la fecha en un dia (con preincremento);
TCalendario& TCalendario:: operator++(void)
{
	*this  = *this + 1;
	return *this;
}


TCalendario TCalendario :: operator- (const int d){
    bool es = false;
    TCalendario r(*this);

    r.dia = dia - d;

    while (!isUnderControl(r.dia, r.mes, r.anyo) && es == false){
        if (r.anyo < 1900){
            r.dia = 1;
            r.mes = 1;
            r.anyo = 1900;
            r.mensaje = NULL;
            es = true;
        } else if (r.mes == 1){
            r.dia = r.dia + 31;
            r.mes = 12;
            r.anyo--;
        } else if (r.mes == 2){
            if ((r.anyo % 4 == 0) && (r.anyo % 400 == 0) || (r.anyo % 100 != 0)){
                r.dia = r.dia + 29;
                r.mes--;
            } else{
                r.dia = r.dia + 28;
                r.mes--;
            }
        } else if (r.mes == 4 || r.mes == 6 || r.mes == 9 || r.mes == 11){
            r.dia = r.dia + 30;
            r.mes--;
        }else if (r.mes == 1 || r.mes == 3 || r.mes == 5 || r.mes == 7 || r.mes == 8 || r.mes == 10 || r.mes == 12){
            r.dia = r.dia + 31;
            r.mes--;
        }
    }
    return r;
}

TCalendario TCalendario :: operator-- (const int d){
    TCalendario tc(*this);
    *this = *this - 1;
    return tc;
}

TCalendario& TCalendario::operator-- (void){
    *this = *this - 1;
    return (*this);
}

bool TCalendario::ModFecha(int dia, int mes, int anyo){
    bool modificado = true;
    if (isUnderControl(dia, mes, anyo)){
        this -> dia = dia;
        this -> mes = mes;
        this -> anyo = anyo;
    } else {
        modificado = false;
    }
    return modificado;
}

bool TCalendario::ModMensaje(char *mens){
    bool modificado = true;
    if (mens == NULL){
        mensaje = NULL;
        modificado = false;
    } else{
        mensaje = new char[strlen(mens) + 1];
        strcpy(mensaje, mens);
    }
    return modificado;
}

bool TCalendario::operator==(const TCalendario &c){ 
    return (dia == c.dia && anyo == c.anyo && mes == c.mes &&
    (strcmp(mensaje, c.mensaje) == 0)) ? true : false;
}

bool TCalendario::operator!=(const TCalendario &c){
    return !(*this == c);
}

bool TCalendario::operator>(const TCalendario &c){
    bool mayor = false;
    if (anyo > c.anyo){
        mayor = true;
    } else if (anyo == c.anyo){
        if (mes > c.mes){
            mayor = true;
        } else if (mes == c.mes){
            if (dia > c.dia){
                mayor = true;
            } else if (dia == c.dia){
                if (mensaje != NULL && c.mensaje != NULL){
                    if (strcmp(mensaje, c.mensaje) > 0){
                        mayor = true;
                    }
                } else if ((strcmp(mensaje, "") == 0) && c.mensaje == NULL){
                    mayor = true;
                } else if ((strcmp(mensaje, " ") == 0) && c.mensaje == NULL){
                    mayor = true;
                } else if ((strcmp(mensaje, " ") == 0) && (strcmp(c.mensaje, "") == 0)){
                    mayor = true;
                }
            }
        }
    }
    return mayor;
}

bool TCalendario::operator<(const TCalendario &c){
    return (*this != c && !(*this > c));
}

int TCalendario :: Dia(){
    return dia;
}
int TCalendario :: Mes(){
    return mes;
}
int TCalendario :: Anyo(){
    return anyo;
}
char * TCalendario :: Mensaje(){
    return mensaje;
}
bool TCalendario :: EsVacio(){
    bool es = false;

    if (dia == 1 && mes == 1 && anyo == 1900 && mensaje == NULL){
        es = true;
    }
    return es;
}

ostream & operator << (ostream &os, const TCalendario &c){
    if (c.dia <= 9){
        if (c.mes <= 9){
            if (c.mensaje == NULL){
                os << 0 << c.dia << "/" << 0 << c.mes << "/" << c.anyo << " " << "\"" << "\"";
            } else {
                os << 0 << c.dia << "/" << 0 << c.mes << "/" << c.anyo << " " << "\"" << c.mensaje << "\"";
            }
        } else {
            if (c.mensaje == NULL) {
                os << 0 << c.dia << "/" << c.mes << "/" << c.anyo << " " << "\"" << "\"";
            } else {
                os << 0 << c.dia << "/" << c.mes << "/" << c.anyo << " " << "\"" << c.mensaje << "\"";
            }
        }
    } else if (c.mes <= 9){
        if (c.dia <= 9){
            if (c.mensaje == NULL){
                os << 0 << c.dia << "/" << 0 << c.mes << "/" << c.anyo << " " << "\"" << "\"";	
            } else {
                os << 0 << c.dia << "/" << c.mes << "/" << c.anyo << " " << "\"" << c.mensaje << "\"";	
            }
        } else {
            if (c.mensaje == NULL){
                os << c.dia << "/" << 0 << c.mes << "/" << c.anyo << " " << "\"" << "\"";	
            } else {
                os << c.dia << "/" << 0 << c.mes << "/" << c.anyo << " " << "\"" << c.mensaje << "\"";	
            }
        }
    } else {
        if (c.mensaje == NULL) {
            os << c.dia << "/" << c.mes << "/" << c.anyo << " " << "\"" << "\"";
        } else {
            os << c.dia << "/" << c.mes << "/" << c.anyo << " " << "\"" << c.mensaje << "\"";
        }
    }
	return os;
}
