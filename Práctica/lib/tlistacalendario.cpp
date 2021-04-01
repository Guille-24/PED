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
    pos = p.pos;
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

TListaPos TListaPos::Siguiente() {
    TListaPos aux;
    aux.pos = pos -> siguiente;
    return aux;
}

bool TListaPos::EsVacia() {
    return (pos == NULL);
}



// TListaCalendario ******************************************************

TListaCalendario::TListaCalendario(){
    primero = NULL;
}


TListaCalendario :: TListaCalendario (const TListaCalendario& lc) 
{
	primero = lc.primero;
	TNodoCalendario * n1, *n2;

	if (lc.primero != NULL){
		int i = 1;
		while (i < lc.Longitud()){
			n1 = primero;
			while (n1 != NULL){
				n2 = n1 -> siguiente;
				primero -> c = lc.primero -> c;
                n1 = n2;
			}
			n1 = NULL;
			n2 = NULL;
			i++;
		}
	} else{
		primero = NULL;
	}
}

TListaCalendario::~TListaCalendario() {
	TListaPos lp;
	lp = Primera();
	if(primero != NULL){
		for(int i = 0; i < Longitud(); i++){
			lp = lp.Siguiente();
		}
		primero = lp.pos;
		primero = NULL;
	}
}

TListaCalendario & TListaCalendario::operator=(const TListaCalendario &l){
    if (this != &l){
        this->~TListaCalendario();
        if (l.primero != NULL){
            primero = l.primero;
        } else {
            primero = NULL;
        }
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
    TListaPos p;
    p.pos = primero;
    return p;
    
}

bool TListaCalendario::EsVacia(){
    return (primero == NULL);
}

int TListaCalendario::Longitud() const {
    int longitud = 0;
    TListaPos p;
    p = Primera();
    while (!p.EsVacia()){
        p = p.Siguiente();
        longitud++;
    }
    return longitud;
}

TListaPos TListaCalendario::Ultima() const{
    TListaPos p;
    p = Primera();
    while (!p.EsVacia()){
        p = p.Siguiente();
    }
    return p;
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

TListaCalendario TListaCalendario::operator - (const TListaCalendario& l) {
	TListaCalendario resultante;
	TListaPos lizq(Primera());
	TListaPos lder(l.Primera());
	for(int i = 0; i < Longitud(); i++){
		resultante.Insertar(lizq.pos -> c);
		lizq = lizq.Siguiente();
	}
	for(int i = 0; i < l.Longitud(); i++){
        resultante.Borrar(lder.pos -> c);
        lder = lder.Siguiente();
	}
	return resultante;
}

bool TListaCalendario::Buscar(const TCalendario &cal){
    
    bool founded = false;
    TListaPos aux;
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

bool TListaCalendario::Insertar(const TCalendario& c) {
	TListaPos actual;
	TListaPos anterior;
	TNodoCalendario* aux = new TNodoCalendario();
	actual = Primera();
	anterior = Primera();

	if(actual.EsVacia()){
		actual.pos = new TNodoCalendario();
		actual.pos -> c = c;
		primero =actual.pos;
		return true;
	}

	if(Buscar(c)){return false;}
	else{
		while(!actual.EsVacia()){
			if(actual.pos -> c > c){
				if(actual == Primera()){
					aux -> c = c;
					aux -> siguiente = actual.pos;
					primero = aux;
					return true;
				}
			} else {
				if(actual.Siguiente().EsVacia()){
					aux -> c = c;
					aux -> siguiente = actual.Siguiente().pos;
					actual.pos -> siguiente = aux;
					return true;
				}
				else if(actual.Siguiente().pos -> c > c){
					aux -> c= c;
					aux -> siguiente = actual.pos -> siguiente;
					anterior.pos -> siguiente = aux;
					return true;
				}
			}
			actual = actual.Siguiente();
		}
	}
	return true;
}


bool TListaCalendario::Borrar(int dia, int mes, int anyo){
    TListaPos aux(Primera());
    if (anyo < primero -> c.Anyo()){
        return false;
    } else {
        if (mes < primero -> c.Mes()){
            return false;
        } else {
            if (dia < primero -> c.Dia()){
                return false;
            } else {
                while (!aux.EsVacia()){
                    if ((aux.pos -> c.Anyo() == anyo && aux.pos -> c.Mes() < mes) ||
                        aux.pos -> c.Anyo() < anyo ||
                        (aux.pos -> c.Anyo() == anyo && aux.pos -> c.Mes() == mes && aux.pos -> c.Dia() < dia)){
                        Borrar(aux.pos -> c);
                        aux = Primera();
                    } else {
						aux = aux.Siguiente();
                    }
                }
                return true;
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

ostream & operator << (ostream &o, const TListaCalendario &lc)
{
	TListaPos l;
	l = lc.Primera();
	if (l.EsVacia()){
		o << "<>";
	}else{
		o << "<";
		int i = 0;
		while (i < lc.Longitud()){
			if (i == 0){
				o << lc.Obtener(l);
			}else{
				o << " " << lc.Obtener(l);
			}
			l = l.Siguiente();
			i++;
		}
		o << ">";
	}
	return o;
}

TListaCalendario TListaCalendario::ExtraerRango(int n1, int n2) {
	TListaCalendario resultante;
	TListaPos lis(Primera()), aux;
	
	if(n1<=0){n1 = 1;}
	if(n2>Longitud()){n2 = Longitud();}
	
	if(n1 <= n2){
		int i = 1;
		while (i <= n2){
			if (i >= n1){
				resultante.Insertar(lis.pos -> c);
				aux = lis.Siguiente();
				Borrar(lis.pos -> c);
				lis = aux;
			} else {
				lis = lis.Siguiente();
			}
			i++;
		}
	}
	return resultante;
}

TListaCalendario TListaCalendario::ExtraerRangoAux(int n1, int n2) {
	TListaCalendario resultante;
	TListaPos lis(Primera()), aux;
	
	if(n1 <= 0){n1 = 1;}
	if(n2 > Longitud()){n2 = Longitud();}
	//Aseguramos los límites
	
	if(n1 <= n2){
		int i = 1;
		while (i <= n2){
			if (i >= n1){
				resultante.Insertar(lis.pos -> c);
				aux = lis.Siguiente();
				lis = aux;
			} else {
				lis = lis.Siguiente();
			}
			i++;
		}
	}
	return resultante;
}


TListaCalendario TListaCalendario::SumarSubl(int I_L1, int F_L1, const TListaCalendario& L2, int I_L2, int F_L2) {
	TListaCalendario nL1;
	TListaCalendario nL2;
	TListaCalendario resultante;
	TListaCalendario aux(L2);
	if(I_L1 <= F_L1 && I_L2 <= F_L2){
		if(I_L1 <= 0 || I_L2 <= 0){
			if(I_L1 <= 0 && I_L2 <= 0){
				nL1 = ExtraerRangoAux(1, F_L1);
				nL2 = aux.ExtraerRangoAux(1, F_L2);
			} else if(I_L1 <= 0){
				nL1 = ExtraerRangoAux(1, F_L1);
				nL2 = aux.ExtraerRangoAux(I_L2, F_L2);
			} else if(I_L2 <= 0){
				nL1 = ExtraerRangoAux(I_L1, F_L1);
				nL2 = aux.ExtraerRangoAux(1, F_L2);
			}
		} else if(F_L1 > Longitud() || F_L2 > L2.Longitud()){
			if(F_L1 > Longitud() && F_L2 > L2.Longitud()){
					nL1 = ExtraerRangoAux(I_L1, Longitud());
					nL2 = aux.ExtraerRangoAux(I_L2, Longitud());
			} else if(F_L1 > Longitud()){
				nL1 = ExtraerRangoAux(I_L1, Longitud());
				nL2 = aux.ExtraerRangoAux(I_L2, F_L2);
			} else if(F_L2>aux.Longitud()){
				nL1 = ExtraerRangoAux(I_L1, F_L1);
				nL2 = aux.ExtraerRangoAux(I_L2, Longitud());
			}
		} else{
			nL1 = ExtraerRangoAux(I_L1, F_L1);
			nL2 = aux.ExtraerRangoAux(I_L2, F_L2);
		}
	} else{
		if(I_L1 > F_L1 && I_L2 > F_L2){
		} else if(I_L1 > F_L1){
			nL2 = aux.ExtraerRangoAux(I_L2, F_L2);
		} else if(I_L2 > F_L2){
			nL1 = ExtraerRangoAux(I_L1, F_L1);
		}
	}
	resultante = nL1 + nL2;
	return resultante;
}