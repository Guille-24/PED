#include "tvectorcalendario.h"

TVectorCalendario::TVectorCalendario(){
    c = NULL;
    tamano = 0;
    error = TCalendario();
}

TVectorCalendario::TVectorCalendario(int tam){
    if (tam < 0){
        tamano = 0;
        c = NULL;
    } else {
        tamano = tam;
        c = new TCalendario[tam];
    }
}

void TVectorCalendario::Copia(const TVectorCalendario &v){
    tamano = v.tamano;
    c = v.c;
    error = v.error;
}

TVectorCalendario::TVectorCalendario (const TVectorCalendario &v){
    Copia(v);
}

TVectorCalendario::~TVectorCalendario(){
    delete []c;
    c = NULL;
    tamano = 0;
}

//Comprobar si funciona así o habrá que recorrer el vector
TVectorCalendario &TVectorCalendario::operator= (const TVectorCalendario &v){
    if (this != &v){
        if (v.tamano > 0){
            this->~TVectorCalendario();
            tamano = v.tamano;
            c = new TCalendario[v.tamano];
            error = TCalendario();
            for (int i = 0; i < v.tamano; i++){
                c[i] = v.c[i];
            }
        } else {
            tamano = 0;
            c = NULL;
            error = TCalendario();
        }
    }
    return *this;
}

bool TVectorCalendario :: operator==(const TVectorCalendario &v){
    if (this->tamano == v.tamano){
        for (int i = 0; i < v.tamano; i++){
            (v.c[i] == c[i]);
        }
    } else{
        return false;
    }
}

bool TVectorCalendario::operator!=(const TVectorCalendario &v){
   return !(*this == v);
}

//Sobrecarga del operador corchete (izquierda)
TCalendario &TVectorCalendario :: operator[](int v){
    TCalendario *dato = NULL;
    if (v >= 1 && v <= tamano){
        dato = &c[v - 1];
    } else {
        dato = &error;
    }
    return *dato;
}

TCalendario TVectorCalendario::operator[](int v) const{
    if (v >= 1 && v <= tamano){
        return c[v - 1];
    } else {
        return error;
    }
}

int TVectorCalendario::Ocupadas(){
    int contador = 0;
    for (int i = 0; i < tamano; i++){
        if (!c[i].EsVacio()){
            contador++;
        }
    }
    return contador;
}

bool TVectorCalendario::ExisteCal(const TCalendario &c){
    for (int i = 0; i < tamano; i++){
        if (this->c[i] == c){
            return true;
        }
    }
    return false;
}

void TVectorCalendario::MostrarMensajes(int dia, int mes, int anyo){
    for (int i = 1; i < tamano; i++){
        if (c[i].Anyo() >= anyo){
            if (c[i].Mes() >= mes){
                if (c[i].Dia() >= dia){
                    cout << c[i].Mensaje() << ", ";
                }
            }
        }
    }
}

bool TVectorCalendario::Redimensionar(int n){
    if (n <= 0 || n == tamano){return false;}
    if (n > 0){
        TVectorCalendario aux(n);
        if (n > tamano){
            for (int i = 0; i < n; i++){
                if (i < tamano){
                    aux.c[i] = c[i];
                } else {   
                    aux.c[i] = TCalendario();
                }
            }
        } else {
            for (int i = 0; i < n; i++){
                aux.c[i] = c[i];
            }
        }
        *this = aux;
        return true; 
    }
    return false;
}

int TVectorCalendario::Tamano(){
    return tamano;
}

ostream & operator << (ostream &os, const TVectorCalendario &v){
    os << "[";
    for (int i = 1; i < v.tamano + 1; i++){
        os << "(" << i << ") " << v[i];
        if (i < v.tamano) os << ", ";
    }
    os << "]";
    return os;
}

