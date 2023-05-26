#pragma once
#include "Aminoacido.h"
#include "ListaDoble.h"
#include "Interfaz.h"
#include "iostream"


class Proteina {
private:

    int folio;
    lista_d<Aminoacido> secuencia;
    string nombre;

public:

    friend ostream& operator<<(ostream& os, const Proteina& prote);
    //constructores añadi constructores
    //  Proteina() = default;
        Proteina():nombre{"No hay nombre"},secuencia{lista_d<Aminoacido>()},folio{0}{}
        Proteina(string nom, lista_d<Aminoacido>  sec,int fol) : nombre{nom}, secuencia{sec},folio{fol} {}
        Proteina(string &&nombre, lista_d<Aminoacido> &&secuencia,int&& folio) : nombre{move(nombre)}, secuencia{move(secuencia)}, folio{move(folio)} {}
	//setters y getters

        int getfolio() const;
        void setfolio(int folio);
        Proteina& operator=(const Proteina& otra);

        void setNombre(string nombre)
		{
			this->nombre = nombre;
		}

		string getNombre()const
		{
			return nombre;
		}

        void setSecuencia(lista_d<Aminoacido> &secuencia)
        {
            this->secuencia = secuencia;
        }

        lista_d<Aminoacido>& getSecuencia()
        {
            return secuencia;
        }

        bool operator<=(const Proteina& otra)const{
            return folio<=otra.folio;
        }

};

  ostream& operator<<(ostream& os, const Proteina& prote)
{
    os <<"Folio: "<<prote.folio<< '\n'<<"Nombre: "<< prote.nombre << '\n'<<"Secuencia: "<< prote.secuencia;
    return os;
}

int Proteina::getfolio() const
{
    return folio;
}

void Proteina::setfolio(int folio)
{
   this->folio = folio;
}

Proteina& Proteina::operator=(const Proteina& otra)
{
    if (this != &otra) {
        nombre = otra.nombre;
        secuencia = otra.secuencia;
        folio = otra.folio;
    }
    return *this;
}

void anhadirProteinaBack(string &x, lista_d<Aminoacido> &aminoacido,lista_d<Proteina>& lista,int &folio)
{
    Proteina proteina{x, aminoacido,folio};
    lista.push_b(proteina);
}

void anhadirProteinaBack(string &&x, lista_d<Aminoacido> &&aminoacido,lista_d<Proteina>& lista,int &&folio)
{
    Proteina proteina{x, aminoacido,folio};
    lista.push_b(proteina);
}

void anhadirProteinasFront(const string &x, lista_d<Aminoacido> &aminoacido,lista_d<Proteina>& lista,int &folio)
{
    Proteina proteina{x, aminoacido,folio};
    lista.push_f(proteina);
}

void anhadirProteinasFront(string &&x, lista_d<Aminoacido>  &&aminoacido,lista_d<Proteina>& lista,int &&folio)
{
    Proteina proteina{x, aminoacido,folio};
    lista.push_f(proteina);
}

void anhadirProteinasPos(const string &x, lista_d<Aminoacido>  &aminoacido, int pos,lista_d<Proteina>& lista,int &folio)
{
    Proteina proteina{x, aminoacido,folio};
    lista.push_p(proteina, pos);
}

void anhadirProteinasPos(string &&x, lista_d<Aminoacido> &&aminoacido, int pos,lista_d<Proteina>& lista,int &&folio)
{
    Proteina proteina{x, aminoacido,folio};
    lista.push_p(proteina, pos);
}


void anhadirProAminoacido(int folio_proteina, int pos_aminoacido, const Aminoacido& aminoacido,lista_d<Proteina>& listaproteicas)
{
    Interfaz temporal;
    Proteina& proteina = listaproteicas.BusquedaBinaria(folio_proteina);
    lista_d<Aminoacido>& secuencia = proteina.getSecuencia();
    secuencia.push_p(aminoacido, pos_aminoacido);
}

void eliminarProAminoacido(int folio_proteina, int pos_aminoacido, lista_d<Proteina>& listaproteicas)
{
    Proteina& proteina = listaproteicas.BusquedaBinaria(folio_proteina);
    lista_d<Aminoacido>& secuencia = proteina.getSecuencia();
    secuencia.pop_p(pos_aminoacido);
}

//funny moment =)