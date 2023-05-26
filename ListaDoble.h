#pragma once
#include <iostream>

using namespace std;

template <typename objeto>
class lista_d
{
private:
    struct nodo
    {
//      Proteina<objeto> proteina;
        objeto dato;
        nodo* next;
        nodo* prev;
        nodo(const objeto& d = objeto{}, nodo* n = nullptr, nodo* p = nullptr) : dato{ d }, next{ n }, prev{ p } {}
        nodo(objeto&& d = objeto{}, nodo* n = nullptr, nodo* p = nullptr) : dato{ move(d) }, next{ move(n) }, prev{ move(p) } {}
    };

    nodo* head;
    nodo* tail;
    int tamanio;
    int capacidad;
    class iterador_const
    {
    public:
        iterador_const() :actual{ nullptr }
        {}
        const objeto& operator*()const
        {
            return recuperar();
        }

        iterador_const& operator++()
        {
            actual = actual->next;
            return *this;
        }

        iterador_const& operator++(int)
        {
            iterador_const viejo = *this;
            ++(*this);
            return viejo;
        }

        bool operator== (const iterador_const& rhs)const
        {
            return actual == rhs.actual;
        }

        bool operator!=(const iterador_const& rhs)const
        {
            return !(*this == rhs);
        }

        iterador_const& operator --()
        {
            actual = actual->prev;
            return *this;
        }

    protected:
        nodo* actual;
        objeto& recuperar() const
        {
            return actual->dato;
        }

        iterador_const(nodo* p) :actual{ p }
        {
        }
        friend class lista_d <objeto>;
    };
    class iterador :public iterador_const
    {
    public:
        iterador()
        {
        }
        objeto& operator*()
        {
            return iterador_const::recuperar();
        }
        const objeto& operator*()const
        {
            return iterador_const::operator*();
        }
        iterador& operator++()
        {
            this->actual = this->actual->next;
            return *this;
        }
        iterador operator++(int)
        {
            iterador viejo = *this;
            ++(*this);
            return viejo;
        }

    protected:
        friend class lista_d <objeto>;
    };

public:
	lista_d(const lista_d <objeto>& rhs);
	~lista_d();
	lista_d(lista_d <objeto>&& rhs);
	lista_d();
	lista_d<objeto>& operator=(const lista_d <objeto>& rhs);
    lista_d<objeto>& operator=(lista_d<objeto>&& rhs);
    //metodos de lista
	void iniciar();
    void limpiar();
	bool llena();
	void push_b(const objeto& x);
	void push_b(objeto&& x);
	bool vacia();
	void push_f(const objeto& x);
	void push_f(objeto&& x);
	void push_p(const objeto& x, int po);
	void push_p(objeto&& x, int po);
    void pop_p(int po);
    void pop_f();
    void pop_b();
    ostream& imprimir_lista(ostream& os)const;

    nodo* getHead()
    {
        if (vacia()) {
            throw std::out_of_range("La lista está vacía (funcion getHead).");
        }
        return head;
    }
    template<typename T>
    friend ostream & operator<<(ostream& os, const lista_d<T>& listatmp);

    int getTamanio()
    {
        return tamanio;
    }

    //funcion para ver lista
	objeto& peekLista(int indice);
    objeto& BusquedaBinariaRecursiva(int valor, int inicio, int fin);
    objeto& BusquedaBinaria(int valor);

    //BUSQUEDA BINARIA BOOL
    bool BusquedaBinariaBool(int valor);
    bool BusquedaBinariaRecursivaBool(int valor, int inicio, int fin);


    //Metodos de quicksort
    nodo* particionar(nodo* I, nodo* H);
    void intercambiar(objeto* nodo1, objeto* nodo2);
    nodo* UltimoNodo(lista_d::nodo *root);
    void _quickSort(nodo*I,nodo*H);
    void quicksortporFolio(nodo* head);

};

template <typename objeto>
lista_d <objeto>::lista_d(const lista_d <objeto>& rhs)
{
    head = tail = nullptr;
    tamanio = 0;
    capacidad = 10000;
    for (nodo* p = rhs.head; p != nullptr; p = p->next) {
        push_b(p->dato); // Agregar un nuevo nodo con el mismo dato en la lista
    }
}
template <typename objeto>
lista_d <objeto>::lista_d(lista_d <objeto>&& rhs) :head{ rhs.head }, tail{ rhs.tail }, tamanio{ rhs.tamanio }, capacidad{ rhs.capacidad }
{
	rhs.head = nullptr;
	rhs.tail = nullptr;
	rhs.tamanio = 0;
	rhs.capacidad = 10000;
}
template <typename objeto>
void lista_d<objeto>::limpiar()
{
    while (head != nullptr)
    {
        nodo* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    tamanio = 0;
}
template <typename objeto>
lista_d <objeto>::~lista_d()
{
	limpiar();

}
template <typename objeto>
lista_d <objeto>::lista_d()
{
	iniciar();
}
template <typename objeto>
lista_d<objeto>& lista_d<objeto>::operator=(const lista_d<objeto>& rhs)
{
    if (this == &rhs) return *this; // Manejar la asignación a sí mismo

    // Limpiar la lista actual
    limpiar();

    // Copiar los elementos de rhs a la lista actual
    for (nodo* p = rhs.head; p != nullptr; p = p->next) {
        push_b(p->dato); // Agregar un nuevo nodo con el mismo dato en la lista
    }

    return *this;
}
template <typename objeto>
lista_d<objeto>& lista_d<objeto>::operator=(lista_d<objeto>&& rhs)
{
    if (this != &rhs)
    {
        limpiar();
        head = rhs.head;
        tail = rhs.tail;
        tamanio = rhs.tamanio;
        capacidad = rhs.capacidad;
        rhs.head = nullptr;
        rhs.tail = nullptr;
        rhs.tamanio = 0;
        rhs.capacidad = 0;
    }
    return *this;
}


template <typename objeto>
void lista_d <objeto>::iniciar()
{
	head = nullptr;
	tail = nullptr;
	tamanio = 0;
	capacidad = 10000;
}

template <typename objeto>
bool lista_d <objeto>::llena()
{
	if (tamanio == capacidad)
		return true;
	else
		return false;
}

template <typename objeto>
bool lista_d <objeto>::vacia()
{
	if (head == nullptr)
		return true;
	else
		return false;
}

template <typename objeto>
ostream& lista_d <objeto>::imprimir_lista(ostream& os)const
{
    nodo* tmp;
    tmp = head;
    for (int i = 0; i < tamanio; i++)
    {
        os <<"["<<i+1<<"]"<< tmp->dato<<endl;
        if (i != tamanio - 1) {
            os << "";
        }
        else os << endl;
        tmp = tmp->next;

    }
    return os;
}


template <typename objeto>
void lista_d<objeto>::push_b(const objeto& x)
{
    nodo* p = new nodo{ x, nullptr, tail };
    if (vacia()) {
        head = tail = p;
    } else {
        tail->next = p;
        tail = p;
    }
    ++tamanio;
}

template <typename objeto>
void lista_d<objeto>::push_b(objeto&& x)
{
    nodo* p = new nodo{ std::move(x), nullptr, tail };
    if (vacia()) {
        head = tail = p;
    } else {
        tail->next = p;
        tail = p;
    }
    ++tamanio;
}

template <typename objeto>
void lista_d<objeto>::push_f(const objeto& x)
{
    nodo* p = new nodo{ x, head, nullptr };
    if (vacia()) {
        head = tail = p;
    } else {
        head->prev = p;
        head = p;
    }
    ++tamanio;
}

template <typename objeto>
void lista_d<objeto>::push_f(objeto&& x)
{
    nodo* p = new nodo{ std::move(x), head, nullptr };
    if (vacia()) {
        head = tail = p;
    } else {
        head->prev = p;
        head = p;
    }
    ++tamanio;
}

template <typename objeto>
void lista_d<objeto>::push_p(const objeto& x, int po)
{
    if (vacia() || po == 0)  // Si la lista está vacía o la posición es 1
        push_f(x);  // Insertar al principio de la lista
    else if (po >= tamanio)  // Si la posición es mayor al tamaño de la lista
        push_b(x);  // Insertar al final de la lista
    else
    {
        nodo* pre = head;
        for (int k = 0; k < po - 1; k++)  // Iterar hasta po - 1
        {
            pre = pre->next;
        }
        nodo* aft = pre->next;
        nodo* p = new nodo{ x, nullptr , nullptr};
        p->next = aft;
        aft->prev = p;  // Actualizar el puntero previo del nodo siguiente
        pre->next = p;
        p->prev = pre;  // Actualizar el puntero previo del nuevo nodo
        tamanio++;
    }
}

template <typename objeto>
void lista_d <objeto>::push_p(objeto&& x, int po)
{
    if (vacia() || po == 0)  // Si la lista está vacía o la posición es 1
        push_f(x);  // Insertar al principio de la lista
    else if (po >= tamanio)  // Si la posición es mayor al tamaño de la lista
        push_b(x);  // Insertar al final de la lista
    else
    {
        nodo* pre = head;
        for (int k = 0; k < po - 1; k++)  // Iterar hasta po - 1
        {
            pre = pre->next;
        }
        nodo* aft = pre->next;
        nodo* p = new nodo{move(x), nullptr , nullptr};
        p->next = aft;
        aft->prev = p;  // Actualizar el puntero previo del nodo siguiente
        pre->next = p;
        p->prev = pre;  // Actualizar el puntero previo del nuevo nodo
        tamanio++;
    }
}

template <typename objeto>
objeto& lista_d <objeto>::peekLista(int po)
{
    if (po < 0 || po >= tamanio)
    {
        throw std::out_of_range("El índice está fuera del rango de la lista");
    }
    nodo* p = head;
    for (int i = 0; i < po; i++)
    {
        p = p->next;
    }
    return p->dato;
}


template<typename objeto>
void lista_d<objeto>::pop_f()
{
    if (tamanio == 0){
        throw out_of_range("La lista esta vacia.");
    } else {
        nodo* temp = head;
        head = head -> next;
        if (head != nullptr){
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }

        delete temp;
        tamanio--;
    }
}


template<typename objeto>
void lista_d<objeto>::pop_b()
{
    if (tamanio == 0) {
        throw out_of_range("La lista esta vacia.");
    }
    nodo* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
    tamanio--;
}

template <typename objeto>
void lista_d<objeto>::pop_p(int po)
{
    if (po < 0 || po >= tamanio ) {
        throw std::out_of_range("Posicion no existente.");
    } else if (po == 0){
        pop_f();
    } else if (po == tamanio - 1){
        pop_b();
    } else {
        nodo* actual = head;
        for (int i = 0; i < po; i++){
            actual =  actual -> next;
        }
        actual -> prev -> next = actual -> next;
        actual -> next -> prev = actual -> prev;
        delete actual;
        tamanio--;
    }
}

//sobrecarga de operador <<
template <typename objeto>
ostream& operator<<(ostream& os, const lista_d<objeto>& listatmp)
{
    typename lista_d<objeto>::nodo* tmp;
    tmp = listatmp.head;
    for (int i = 0; i < listatmp.tamanio; i++)
    {
        os << tmp->dato;
        if (i != listatmp.tamanio - 1) {
            os << "-";
        }
        else os << endl;
        tmp = tmp->next;
    }
    return os;
}

//-----Busqueda Binaria------//

//Esta Busqueda Binaria retorna un valor booleano
//Si el valor es encontrado retorna true, de otra manera retorna false
template<typename objeto>
bool lista_d<objeto>::BusquedaBinariaRecursivaBool(int valor, int inicio, int fin)
{
    if (inicio > fin)
    {
        return false;
    }

    int medio = (inicio + fin) / 2;
    objeto& datoMedio = peekLista(medio);

    if (datoMedio.getfolio() == valor)
    {
        return true;
    }
    else if (datoMedio.getfolio() < valor)
    {
        return BusquedaBinariaRecursivaBool(valor, medio + 1, fin);
    }
    else
    {
        return BusquedaBinariaRecursivaBool(valor, inicio, medio - 1);
    }
}

template<typename objeto>
bool lista_d<objeto>::BusquedaBinariaBool(int valor)
{
    quicksortporFolio(getHead()); // Ordenar la lista por el nombre antes de realizar la búsqueda

    int inicio = 0;
    int fin = tamanio - 1;

    return BusquedaBinariaRecursivaBool(valor, inicio, fin);
}

//busqueda binaria que retorna un objeto y con ella mostramos los valores de la proteina
template<typename objeto>
objeto& lista_d<objeto>::BusquedaBinariaRecursiva(int valor, int inicio, int fin)
{

    if (inicio > fin)
    {
        // Si no se encuentra el valor, puedes lanzar una excepción o devolver un valor predeterminado
        throw std::runtime_error("Valor no encontrado");

    }

    int medio = (inicio + fin) / 2;
    objeto& datoMedio = peekLista(medio);

    if (datoMedio.getfolio() == valor)
    {
        return datoMedio;
    }
    else if (datoMedio.getfolio() < valor)
    {
        return BusquedaBinariaRecursiva(valor, medio + 1, fin);
    }
    else
    {
        return BusquedaBinariaRecursiva(valor, inicio, medio - 1);
    }
}


template<typename objeto>
objeto& lista_d<objeto>::BusquedaBinaria(int valor)
{
    quicksortporFolio(getHead()); // Ordenar la lista por el nombre antes de realizar la búsqueda

    int inicio = 0;
    int fin = tamanio - 1;

    return BusquedaBinariaRecursiva(valor, inicio, fin);
}

//================Quicksort==================//
template <typename objeto>
void lista_d<objeto>::intercambiar(objeto *nodo1, objeto *nodo2)
{
    objeto tmp = *nodo1;
    *nodo1 = *nodo2;
    *nodo2=tmp;
}

//tomar ultimo nodo
template <typename objeto>
typename lista_d<objeto>::nodo* lista_d<objeto>::UltimoNodo(lista_d::nodo *root)
{
    while(root && root->next)
        root=root->next;
    return root;
}

template <typename objeto>
typename lista_d<objeto>::nodo*lista_d<objeto>::particionar(lista_d::nodo *I,lista_d::nodo *H)
{
    int x = H->dato.getfolio();

    nodo *i = I->prev;

    for(nodo* j = I; j !=H; j=j->next)
    {
        if (j->dato.getfolio() <= x)
        {
            i = (i== nullptr)? I:i->next;
            intercambiar(&(i->dato),&(j->dato));
        }
    }
    i=(i== nullptr)? I : i->next;
    intercambiar(&(i->dato), &(H->dato));
    return i;
}

template <typename objeto>
void lista_d<objeto>::_quickSort(nodo*I,nodo*H)
{
    if (H != nullptr && I != H && I != H->next)
    {
        nodo *p = particionar(I,H);
        _quickSort(I,p->prev);
        _quickSort(p->next,H);
    }
}

template <typename objeto>
void lista_d<objeto>::quicksortporFolio(nodo* head)
{
    nodo *h = UltimoNodo(head);
    _quickSort(head, h);
}

