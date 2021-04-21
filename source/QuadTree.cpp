#include <iostream>
#include <cmath>
using namespace std;

template<class U>
struct Punto{
    U x;
    U y;
    Punto() {
        x = 0;
        y = 0;
    }
    Punto(U x, U y){
        this->x = x;
        this->y = y;
    }
    
};

template<class T,class U>
struct Nodo{
    Punto<U> pos;
    T dato;
    Nodo() {
        dato = 0;
    }
    Nodo(Punto<U> pos, int dato){
        this->pos = pos;
        this->dato = dato;
    }  
};

template<class T,class U>
class QuadTree{
    Nodo<T,U>* n;
    Punto<U> limIzquierdo;
    Punto<U> limDerecho;
    QuadTree* divSupIzquierda;
    QuadTree* divSupDerecha;
    QuadTree* divInfIzquierda;
    QuadTree* divInfDerecha;

public:
    void insertar(Nodo<T,U>*);
    Nodo<T,U>* buscar(Punto<U>);
    bool verifica(Punto<U>);
    QuadTree(){
        limIzquierdo = Punto(0, 0);
        limDerecho = Punto(0, 0);
        n = NULL;
        divSupIzquierda = NULL;
        divSupDerecha = NULL;
        divInfIzquierda = NULL;
        divInfDerecha = NULL;
    }
    QuadTree(Punto<U> topL, Punto<U>  botR){
        n = NULL;
        divSupIzquierda = NULL;
        divSupDerecha = NULL;
        divInfIzquierda = NULL;
        divInfDerecha = NULL;
        limIzquierdo = topL;
        limDerecho = botR;
    }
};

template<class T,class U>
bool QuadTree<T,U>::verifica(Punto<U> p)
{
    return (p.x >= limIzquierdo.x &&
        p.x <= limDerecho.x &&
        p.y >= limIzquierdo.y &&
        p.y <= limDerecho.y);
}

template<class T,class U>
void QuadTree<T,U>::insertar(Nodo<T,U>* node){
    if (node == NULL)
        return;
    if (!verifica(node->pos))
        return;
    if (abs(limIzquierdo.x - limDerecho.x) <= 1 && abs(limIzquierdo.y - limDerecho.y) <= 1){
        if (n == NULL)
            n = node;
        return;
    }

    if ((limIzquierdo.x + limDerecho.x) / 2 >= node->pos.x){
        if ((limIzquierdo.y + limDerecho.y) / 2 >= node->pos.y){
            if (divSupIzquierda == NULL)
                divSupIzquierda = new QuadTree(
                    Punto<U>(limIzquierdo.x, limIzquierdo.y),
                    Punto<U>((limIzquierdo.x + limDerecho.x) / 2,
                        (limIzquierdo.y + limDerecho.y) / 2));
            divSupIzquierda->insertar(node);
        }

        else{
            if (divInfIzquierda == NULL)
                divInfIzquierda = new QuadTree(
                    Punto<U>(limIzquierdo.x,
                        (limIzquierdo.y + limDerecho.y) / 2),
                    Punto<U>((limIzquierdo.x + limDerecho.x) / 2,
                        limDerecho.y));
            divInfIzquierda->insertar(node);
        }
    }
    else{
        if ((limIzquierdo.y + limDerecho.y) / 2 >= node->pos.y){
            if (divSupDerecha == NULL)
                divSupDerecha = new QuadTree(
                    Punto<U>((limIzquierdo.x + limDerecho.x) / 2,
                        limIzquierdo.y),
                    Punto<U>(limDerecho.x,
                        (limIzquierdo.y + limDerecho.y) / 2));
            divSupDerecha->insertar(node);
        }

        else{
            if (divInfDerecha == NULL)
                divInfDerecha = new QuadTree(
                    Punto<U>((limIzquierdo.x + limDerecho.x) / 2,
                        (limIzquierdo.y + limDerecho.y) / 2),
                    Punto<U>(limDerecho.x, limDerecho.y));
            divInfDerecha->insertar(node);
        }
    }
}


template<class T,class U>
Nodo<T,U>* QuadTree<T,U>::buscar(Punto<U> p){
    if (!verifica(p))
        return NULL;

    if (n != NULL)
        return n;

    if ((limIzquierdo.x + limDerecho.x) / 2 >= p.x){
        if ((limIzquierdo.y + limDerecho.y) / 2 >= p.y){
            if (divSupIzquierda == NULL)
                return NULL;
            return divSupIzquierda->buscar(p);
        }

        else{
            if (divInfIzquierda == NULL)
                return NULL;
            return divInfIzquierda->buscar(p);
        }
    }
    else{
        if ((limIzquierdo.y + limDerecho.y) / 2 >= p.y){
            if (divSupDerecha == NULL)
                return NULL;
            return divSupDerecha->buscar(p);
        }

        else{
            if (divInfDerecha == NULL)
                return NULL;
            return divInfDerecha->buscar(p);
        }
    }
};



int main(){
    Punto<int> limiteIzquierdo(-16, -16);
    Punto<int> limiteDerecho(16, 16);
    QuadTree<int,int> quad(limiteIzquierdo, limiteDerecho);
    Nodo<int, int> nodo1(Punto<int>(-1, 1), 13);
    Nodo<int, int> nodo2(Punto<int>(2, 5), 49);
    Nodo<int, int> nodo3(Punto<int>(7, -6), 56);
    Nodo<int, int> nodo4(Punto<int>(3, -9), 23);
    Nodo<int, int> nodo5(Punto<int>(8, 8), 76);
    Nodo<int, int> nodo6(Punto<int>(1, 9), 12);
    quad.insertar(&nodo1);
    quad.insertar(&nodo2);
    quad.insertar(&nodo3);
    quad.insertar(&nodo4);
    quad.insertar(&nodo5);
    quad.insertar(&nodo6);
    cout <<quad.buscar(Punto<int>(-1, 1))->dato << endl;
    cout<<quad.buscar(Punto<int>(3, -9))->dato << endl;
    cout <<quad.buscar(Punto<int>(8, 8))->dato << endl;
    return 0;
}