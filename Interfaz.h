#pragma once
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

class Interfaz
{
private:

    int opcion;
    string titulo;
    string instrucciones;
    vector <string> opciones;

public:

    Interfaz() : titulo{"Sin titulo"}, instrucciones{"Sin instrucciones"}
    {
        titulo = "PROTEINAS\n";
        instrucciones = "Ingresa una opcion: \n";
    }

    void anhadirOpcion(string opcion)
    {
        opciones.emplace_back(opcion);
    }

    void setTitulo(string titulo)
    {
        this->titulo = titulo;
    }

    void limpiarMenu()
    {
        opciones.clear();
    }

    void setInstrucciones(string instrucciones)
    {
        this->instrucciones = instrucciones;
    }

    int getOpcion() const
    {
        return opcion;
    }

    void setOpcion(int opcion)
    {
        this->opcion = opcion;
    }

    string getTitulo() const
    {
        return titulo;
    }

    string getInstrucciones() const
    {
        return instrucciones;
    }

    const vector <string> &getOpciones() const
    {
        return opciones;
    }

    void setOpciones(const vector <string> &opciones)
    {
        Interfaz::opciones = opciones;
    }

    void Mostrar()
    {
        SystemOutPrintln(getTitulo());
        Imprimir_Opciones(cout);
        SystemOutPrintln(getInstrucciones());
    }

    ostream &Imprimir_Opciones(ostream &os) const
    {
        for (int i = 0; i < opciones.size(); i++)
        {
            os << opciones[i] << endl;
        }
        return os;
    }

    void SystemOutPrintln(const string &str)
    {
        ostream &os = cout;
        os.write(str.c_str(), str.size());
    }

    void SystemOutPrintln(int num, const char* arr, int index, const string* arr2, int index2, int espacios, int lineas_salida)
    {
        ostream &os = cout;
        //HARD-CODE NO APTO PARA SENIORS
        if ( num == 1)
        {
            os <<endl;
        }
        if (num == 1 || num == 5 || num == 9)
        {
            os << ' ';
        }
        os << num << ". "<< arr[index] << " -> " << arr2[index2];

        int i = 0;
        if (num == 11 || num == 15)
        {
            i = -2;
        }
        if (num == 7 || num == 19)
        {
            i = -1;
        }
        if (num == 5 || num == 6)
        {
            i = 1;
        }
        if (num == 17)
        {
            i = 2;
        }
        if (num == 9 || num == 10 || num == 13 || num == 18)
        {
            i = 3;
        }
        if (num == 14)
        {
            i = 5;
        }
        if (num == 2 || num == 6 || num == 10 || num == 14 || num == 18)
        {
            i = i - 2;
        }
        if (num == 3 || num == 7 || num == 11 || num == 15 || num == 19)
        {
            i = i + 2;
        }
        for (i; i < espacios; i++)
        {
            os << ' ';
        }
        if (num%lineas_salida == 0)
        {
            os <<endl;
        }
        if (num == 20)
        {
            os <<endl;
        }
    }

    void Pausar()
    {
        SystemOutPrintln("Presiona Enter para continuar...\n");
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // Ignora cualquier caracter en el búfer de entrada.
    }

    int getSizeOpciones() const
    {
        return opciones.size();
    }

    void limpiar_pantalla()
    {
    #ifdef _WIN32
    #define CLEAR "cls"
    #elif defined(unix) || defined(_unix_) || defined(_APPLE_) || defined(_MACH_)
    #define CLEAR "clear"
    #else
    #error "SO no soportado para limpiar pantalla easter egg el rivas es el Macho alfa"
    #endif
        system(CLEAR);
    }

};

