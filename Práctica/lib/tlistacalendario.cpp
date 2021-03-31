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

// Constructor funciona mal, ARREGLAR
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
                aux1 = aux2;
			}
			aux1 = NULL;
			aux2 = NULL;
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

TListaCalendario TListaCalendario::operator -(const TListaCalendario& l) {
	TListaCalendario resultante;
	TListaPos lizq(Primera());
	TListaPos lder(l.Primera());
	for(int i=0; i<Longitud();i++){
		resultante.Insertar(lizq.pos->c);
		lizq = lizq.Siguiente();
	}
	for(int i=0; i<l.Longitud();i++){
        resultante.Borrar(lder.pos->c);
        lder = lder.Siguiente();
	}
	return resultante;
    /* PROBAR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    while (!lizq.EsVacia()){
        resultante.Insertar(lizq.pos -> c);
        lizq = lizq.Siguiente();
    }
    while (!lder.EsVacia()){
        resultante.Borrar(lder.pos -> c);
        lder = lder.Siguiente();
    }
    */
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

bool TListaCalendario::Insertar(const TCalendario& c) {//Funciona Bien
	TListaPos actual;
	TListaPos anterior;//Posicion anterior
	TNodoCalendario* aux=new TNodoCalendario();
	actual = Primera();
	anterior = Primera();

	if(actual.EsVacia()){
		actual.pos = new TNodoCalendario();
		actual.pos -> c = c;
		primero =actual.pos;
		return true;
	}

	if(Buscar(c)){//Si existe dentro de la lista no se incluye
		return false;
	}
	else{
		while(!actual.EsVacia()){//Si la lista no es vacía
			if(actual.pos->c>c){//Si la posicion es mayor
				if(actual == Primera()){
					aux -> c = c;
					aux -> siguiente = actual.pos;
					primero = aux;
					return true;
				}
			}
			else{//Si la posicion es menor
				if(actual.Siguiente().EsVacia()){//Es el último elemento
					aux -> c = c;
					aux -> siguiente = actual.Siguiente().pos;
					actual.pos -> siguiente = aux;
					return true;
				}
				else if(actual.Siguiente().pos -> c > c){//Esta en medio
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

ostream & operator << (ostream &o, const TListaCalendario &lc)
{
	TListaPos lp;
	lp = lc.Primera();
	if (lp.EsVacia())
	{
		o << "<>";
	}
	else
	{
		o << "<";
		int i = 0;
		while (i < lc.Longitud())
		{
			if (i == 0)
			{
				o << lc.Obtener(lp);
			}
			else
			{
				o << " " << lc.Obtener(lp);
			}
			lp = lp.Siguiente();
			i++;
		}
		o << ">";
	}
	return o;
}

TListaCalendario TListaCalendario::ExtraerRango(int n1, int n2) {
	TListaCalendario nueva;
	TListaPos lp, aux;
	lp=Primera();
	if(n2>Longitud()){
		n2=Longitud();
	}
	if(n1<=0){
		n1=1;
	}
	if(n1<=n2){
		for(int i=1;i<=n2;i++){
			if(i>=n1){
				nueva.Insertar(lp.pos->c);
				aux=lp.Siguiente();
				Borrar(lp.pos->c);
				lp=aux;
			}
			else{
				lp=lp.Siguiente();
			}
		}
	}
	return nueva;
}

TListaCalendario TListaCalendario::ExtraerRangoNM(int n1, int n2) {
	TListaCalendario nueva;
	TListaPos lp, aux;
	lp=Primera();
	if(n2>Longitud()){
		n2=Longitud();
	}
	if(n1<=0){
		n1=1;
	}
	if(n1<=n2){
		for(int i=1;i<=n2;i++){
			if(i>=n1){
				nueva.Insertar(lp.pos->c);
				aux=lp.Siguiente();
				lp=aux;
			}
			else{
				lp=lp.Siguiente();
			}
		}
	}
	return nueva;
}


TListaCalendario TListaCalendario::SumarSubl(int I_L1, int F_L1, const TListaCalendario& L2, int I_L2, int F_L2) {
	TListaCalendario nuevaL1;
	TListaCalendario nuevaL2;
	TListaCalendario auxL2(L2);
	if(I_L1<=F_L1 && I_L2<=F_L2){//Rango Coherente
		if(I_L1 <=0 || I_L2 <=0){
			if(I_L1<=0 && I_L2 <=0){//Si F_L1 y F_L2 son menores o iguales que 0
				nuevaL1=ExtraerRangoNM(1, F_L1);
				nuevaL2= auxL2.ExtraerRangoNM(1, F_L2);
			}
			else if(I_L1<=0){//Si I_L1 es menor o igual que 0
				nuevaL1=ExtraerRangoNM(1, F_L1);
				nuevaL2=auxL2.ExtraerRangoNM(I_L2, F_L2);
			}
			else if(I_L2<=0){//Si I_L2 es menor o igual que 0
				nuevaL1=ExtraerRangoNM(I_L1, F_L1);
				nuevaL2=auxL2.ExtraerRangoNM(1, F_L2);
			}
		}
		else if(F_L1>Longitud() || F_L2 > L2.Longitud()){
			if(F_L1>Longitud() && F_L2 > L2.Longitud()){//Si F_L1 y F_L2 son mayores que el tamaño de sus listas
					nuevaL1=ExtraerRangoNM(I_L1, Longitud());
					nuevaL2=auxL2.ExtraerRangoNM(I_L2, Longitud());
			}
			else if(F_L1>Longitud()){//Si F_L1 es mayor que el tamaño de la lista F1(*this)
				nuevaL1=ExtraerRangoNM(I_L1, Longitud());
				nuevaL2=auxL2.ExtraerRangoNM(I_L2, F_L2);
			}
			else if(F_L2>auxL2.Longitud()){//Si F_L2 es mayor que el tamaño de la lista F2
				nuevaL1=ExtraerRangoNM(I_L1, F_L1);
				nuevaL2=auxL2.ExtraerRangoNM(I_L2, Longitud());
			}
		}
		else{
			nuevaL1=ExtraerRangoNM(I_L1, F_L1);
			nuevaL2=auxL2.ExtraerRangoNM(I_L2, F_L2);
		}
	}
	else{
		if(I_L1>F_L1 && I_L2 > F_L2){//Si I_L1 y I_L2 son mayores que F_L1 Y F_L2
		}
		else if(I_L1>F_L1){//Si F_L1 es mayor que I_L1
			nuevaL2=auxL2.ExtraerRangoNM(I_L2, F_L2);
		}
		else if(I_L2>F_L2){//Si F_L2 es mayor que F_L2
			nuevaL1=ExtraerRangoNM(I_L1, F_L1);
		}
	}
	return nuevaL1+nuevaL2;
}