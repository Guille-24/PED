#include "tlistacalendario.h"
using namespace std;

TNodoCalendario::TNodoCalendario(){
    c = TCalendario();
    siguiente = NULL;
}

TNodoCalendario::TNodoCalendario(const TNodoCalendario &n){
    if (siguiente != NULL){
       delete siguiente;
    }
    c = n.c;
    siguiente = n.siguiente;
}

TNodoCalendario::~TNodoCalendario(){
    c = TCalendario();
    siguiente = NULL;
}

TNodoCalendario & TNodoCalendario::operator=(const TNodoCalendario &n){
    if (siguiente != NULL){
        delete siguiente;
    }
    if (this != NULL){
        c = n.c;
        siguiente = n.siguiente;
    }
    return *this;
}

//TListaPos ********************************************

TListaPos::TListaPos(){
    pos = NULL;
}

TListaPos::TListaPos(const TListaPos &p){
    if (pos != NULL){
        delete pos;
    } else {
        pos = p.pos;
    }
}

TListaPos::~TListaPos(){
    pos = NULL;
}

TListaPos & TListaPos::operator=(const TListaPos &p){
    if (this != &p){
        pos = p.pos;
    }
    return *this;
}

bool TListaPos::operator!=(const TListaPos &p){
    return !(this == &p);
}

bool TListaPos::operator==(const TListaPos &p){
    return (pos == p.pos);
}

TListaPos TListaPos::Siguiente() const {
    TListaPos aux;
    aux.pos = pos -> siguiente;
    return aux;
}

bool TListaPos::EsVacia() const {
    return (pos == NULL);
}



// TListaCalendario ******************************************************
TListaCalendario::TListaCalendario(){
    primero = NULL;
}

TListaCalendario::TListaCalendario(const TListaCalendario &lc){
    TNodoCalendario *aux = lc.primero;
    while (primero != NULL){
        primero = aux;
        aux = lc.primero -> siguiente;
    }
    aux = NULL;
}

TListaCalendario ::~TListaCalendario(){
    TNodoCalendario *aux;
    while (primero != NULL){
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
    aux = NULL;
}

TListaCalendario & TListaCalendario::operator=(const TListaCalendario &l){
    if (this != &l){
        this->~TListaCalendario();
        TNodoCalendario *aux = l.primero;
        while (primero != NULL){
            primero = aux;
            aux = l.primero -> siguiente;
        }
        aux = NULL;
    }
    return *this;
}

bool TListaCalendario::operator==(const TListaCalendario &l){
    bool equal = false;
    TNodoCalendario *aux = l.primero;
    
    while ((primero != NULL && aux != NULL) || equal == true){
        if (primero != aux){
            equal = false;
        } else {
            primero = primero->siguiente;
            aux = aux -> siguiente;
        }
    }
    return equal;
}

TListaPos TListaCalendario::Primera() const{
    TListaPos pos;
    pos.pos = primero;
    return pos;
    
}

int TListaCalendario::Longitud() const {
    int longitud = 0;
    TListaPos pos;
    pos = Primera();
    while (!pos.EsVacia()){
        pos = pos.Siguiente();
        longitud++;
    }
    return longitud;
}

TListaPos TListaCalendario::Ultima() const{
    TListaPos pos;
    pos = Primera();
    while (!pos.EsVacia()){
        pos = pos.Siguiente();
    }
    return pos;
}

TCalendario TListaCalendario::Obtener(const TListaPos &p) const {
    bool found = false;
    TListaPos aux(p);
    if (!p.EsVacia()){
        return p.pos->c;
    }
    TCalendario obtenido;
    return obtenido;
}



TListaCalendario TListaCalendario::operator+(const TListaCalendario &l){
    TListaCalendario resultante;
    TListaPos lizq(Primera());
    TListaPos lder(l.Primera());


}

