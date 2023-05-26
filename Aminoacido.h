#pragma once
#include "ListaDoble.h"
using namespace std;
 //????????????????????????????????????????????????
class Aminoacido
{
    private:

		char unaLetra[20] = { 'A','R','N', 'D','C','Q','E','G','H','I','L','K','M','F','P','S','T','W','Y','V' };
        string tresLetras[20] = { "Ala", "Arg","Asn", "Asp", "Cys", "Gln", "Glu", "Gly", "His", "Ile", "Leu", "Lys", "Met", "Phe", "Pro", "Ser", "Thr", "Trp", "Tyr","Val"};
		string nombre_amino[20] = { "Alanina","Arginina","Asparagina", "Aspartato","Cisteina","Glutamina","Glutamico","Glicina","Histidina","Isoleucina","Leucina","Lisina", "Metionina", "Fenilalanina", "Prolina", "Serina", "Treonina", "Triptofano", "Tirosina", "Valina"};
		char Amino;

	public:
       friend ostream& operator<<(ostream& os, const Aminoacido& aminoacid);
        Aminoacido() = default;
        Aminoacido(char amino) : Amino(amino) {}
        Aminoacido& operator=(const Aminoacido& other);

        char *getUnaLetra()
        {
            return unaLetra;
        }

        string *getTresLetras()
        {
            return tresLetras;
        }

        string *getNombreAmino()
        {
            return nombre_amino;
        }

        char getAmino() const
        {
            return Amino;
        }

        void setAmino(char aminoacido)
        {
            Amino = aminoacido;
        }


};
    ostream& operator<<(ostream& os, const Aminoacido& aminoacid)
    {
        os<<aminoacid.Amino;
        return os;
    }

    Aminoacido& Aminoacido::operator=(const Aminoacido& other)
    {
        if (this != &other) {
            Amino = other.Amino;
        }
        return *this;
    }

    void anhadirAminoacidoBack( char &x, lista_d<Aminoacido>& Aminoacidos)
    {
        Aminoacidos.push_b(x);
    }

    void anhadirAminoacidoBack(char&& x,lista_d<Aminoacido>& Aminoacidos)
    {
        Aminoacidos.push_b(x);
    }

    void anhadirAminoacidoFront(const char&& x,lista_d<Aminoacido>& Aminoacidos)
    {
        Aminoacidos.push_f(x);
    }

    void anhadirAminoacidoFront(char &&x,lista_d<Aminoacido>& Aminoacidos)
    {
        Aminoacidos.push_f(x);
    }

    void anhadirAminoacidoPos(const char &x, int pos,lista_d<Aminoacido>& Aminoacidos)
    {
        Aminoacidos.push_p(x,pos);
    }

    void anhadirAminoacidoPos(char &&x, int pos,lista_d<Aminoacido>& Aminoacidos)
    {
        Aminoacidos.push_p(x,pos);
    }


    void EliminarAminoacidosFront(lista_d<Aminoacido>& Aminoacidos)
    {
        Aminoacidos.pop_f();
    }

    void EliminarAminoacidosBack(lista_d<Aminoacido>& Aminoacidos)
    {
        Aminoacidos.pop_b();
    }

    void EliminarAminoacidosPos(int po,lista_d<Aminoacido>& Aminoacidos)
    {
        Aminoacidos.pop_p(po);
    }




//    void MostrarAminoacidos(lista_d<Aminoacido>& Aminoacidos)
//    {
//        Aminoacidos.imprimir_lista(cout);
//    }
//faltan las demas versiones (back, front y pos)
