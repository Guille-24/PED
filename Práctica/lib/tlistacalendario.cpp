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

TListaCalendario :: TListaCalendario (const TListaCalendario& lc) 
{
	primero = lc.primero;
	TNodoCalendario * aux1, *aux2;

	if (lc.primero != NULL){
		int i = 1;
		while (i < lc.Longitud()){
			aux1 = primero;
			while (aux1 != NULL){
				aux2 = aux1 -> siguiente;
				primero -> c = lc.primero -> c;
			}
			aux1 = NULL;
			aux2 = NULL;
			i++;
		}
	} else{
		primero = NULL;
	}
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
    TListaPos aux(p);
    if (!aux.EsVacia()){
        return p.pos->c;
    }
    TCalendario obtenido;
    return obtenido;
}



TListaCalendario TListaCalendario::operator+(const TListaCalendario &l){
    TListaCalendario resultante;
    TListaPos lizq(Primera());
    TListaPos lder(l.Primera());

    while (!lizq.EsVacia()){
        resultante.Insertar(lizq.pos -> c);
        lizq = lizq.Siguiente();
    }
    while (!lder.EsVacia()){
        resultante.Insertar(lder.pos -> c);
        lder = lder.Siguiente();
    }
    return resultante;
}

bool TListaCalendario::Buscar(const TCalendario &cal){
    
    bool founded = false;
    TListaPos aux;
    cout << "Entro en el buscar" << endl;
    TListaCalendario laux(*this);
    aux.pos = laux.primero;
    int i = 0;
    while (i < laux.Longitud()){
        if (aux.pos -> c == cal){founded = true;}
        aux = aux.Siguiente();
        i++;
    }
    return founded;
}

bool TListaCalendario::Insertar(const TCalendario &cal){
    cout << "entro en el insertar" << endl;
    bool founded = false;
    TListaPos actual;
    TListaPos anterior;
    TNodoCalendario *n = new TNodoCalendario();
    cout << "Creo las variables" << endl;
    if (Buscar(cal)){founded = true;}
    cout << "No fallo en el buscar" << endl;
    if (primero == NULL){
        cout << "Entro en el primer caso" << endl;
        primero = n;
        n -> c = cal;
        founded = true;
    } else {
        actual = Primera();
        while (!founded && !actual.EsVacia()){
            if (Obtener(actual) > cal){
                founded = true;
            } else {
                anterior = actual;
                actual = actual.Siguiente();
            }
        }
        if (founded || anterior == Ultima()){
            if (anterior.EsVacia()){
                n -> c = cal;
                n -> siguiente = actual.pos;
                primero = n;
            } else if (anterior == Ultima()){
                n -> c = cal;
                n -> siguiente = NULL;
                anterior.pos -> siguiente = n;
            } else {
                n -> c = cal;
                n -> siguiente = actual.pos;
                anterior.pos -> siguiente = n;
            }
        }
    }
    return founded;
}


bool TListaCalendario::Borrar(int dia, int mes, int anyo){
    TListaPos aux(Primera());
    if (anyo > primero -> c.Anyo()){
        return true;
    } else {
        if (mes > primero -> c.Mes()){
            return true;
        } else {
            if (dia > primero -> c.Dia()){
                return true;
            } else {
                while (!aux.EsVacia()){
                    if ((aux.pos -> c.Anyo() == anyo && aux.pos -> c.Mes() > mes) ||
                        aux.pos -> c.Anyo() > anyo ||
                        (aux.pos -> c.Dia() > dia && aux.pos -> c.Mes() == mes && aux.pos -> c.Anyo() == anyo)){
                            aux = aux.Siguiente();
                    } else {
                        Borrar(aux.pos -> c);
                        aux = Primera();
                    }
                }
                return false;
            }
        }
    }
}

bool TListaCalendario::Borrar(const TCalendario &cal){
    bool founded = false;
    TListaPos actual(Primera());
    TListaPos anterior(Primera());
    if (primero == NULL){return false;}
    else {
        if (!Buscar(cal)){return false;}
        else {
            if (Obtener(actual) == cal){
                founded = true;
                primero = primero->siguiente;
                delete actual.pos;
            } else {
                actual = actual.Siguiente();
                while (actual.pos != NULL && !founded){
                    if (Obtener(actual) == cal){
                        founded = true;
                        anterior.pos -> siguiente = actual.pos -> siguiente;
                        delete actual.pos;
                    } else {
                        anterior = actual;
                        actual = actual.Siguiente();
                    }
                }
            }
        }
    }
    return founded;
}

bool TListaCalendario::Borrar(const TListaPos &l){return Borrar(Obtener(l));}

ostream & operator<<(ostream &o, const TListaCalendario &l){
    TListaPos aux;
    aux = l.Primera();
    if (aux.EsVacia()){
        o << "<>";
    } else {
        o << "<";
        int i = 0;
        while (i < l.Longitud()){
            if (i == 0){
                o << l.Obtener(aux);
                cout << "Dentro del while del operator << " << endl;
            } else {
                o << " " << l.Obtener(aux);
            }
            aux = aux.Siguiente();
            i++;
        }
        o << ">";
        o << ">";
    }
    return o;
}

