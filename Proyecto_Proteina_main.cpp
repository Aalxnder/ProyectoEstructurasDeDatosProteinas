#include "ListaDoble.h"
#include "Aminoacido.h"
#include "Proteina.h"
#include "Interfaz.h"
#include <iostream>
using namespace std;

/*
 *  The giant monke is protected (#)
 *              ',
            .-`-,\__
              ."`   `,
            .'_.  ._  `;.
        __ / `      `  `.\ .--.
       /--,| 0)   0)     )`_.-,)
      |    ;.-----.__ _-');   /
       '--./         `.`/  `"`
          :   '`      |.
          | \     /  //
           \ '---'  /'
            `------' \
           _/       `--...
 *
 * No tenemos distinciones, cada quien trabajara en lo que tenga mayor conocimiento
 * y nos apoyaremos mutuamente porque nos queremos mucho.
 * Disclaimer: la verdad todos estamos haciendo de t o d o
 * Nombre del equipo: Temerarios (el respaldo) volumen 2 el imperio contrataca
 * Levi Alexander Perez Elizondo
 * Diego Medina Magaña
 * Hector Manuel Curiel Segura
 * Carlos Fernando Rivas Jimenez
 */

//===================PROTOTIPOS DE LAS FUNCIONES=====================//
void Menu(Interfaz &Menu, lista_d<Aminoacido> &AminoacidoList, lista_d<Proteina> &lista);
int Opcion(Interfaz &Menu);
void OpcionElegida(int opcionMenu,Interfaz &menuanahdir, lista_d<Aminoacido> &AminoacidoList,lista_d<Proteina> &lista);
void opcionElegidaAnhadir(int opcionMenuAnahdir,Interfaz &menuanahdir, lista_d<Aminoacido> &AminoacidoList,lista_d<Proteina> &lista);
void anhadirProteinaBack(Interfaz &menu, lista_d<Aminoacido> AminoacidoList, lista_d<Proteina> &lista);
void anhadirProteinaFront(Interfaz &menu, lista_d<Aminoacido> AminoacidoList, lista_d<Proteina> &lista);
void MostrarLista(Interfaz& pantalla,lista_d<Aminoacido>amino,lista_d<Proteina>& Lista);
void anhadirProteinaPos(Interfaz &menu, lista_d<Aminoacido> AminoacidoList, lista_d<Proteina> &lista);
void EliminarProteina(Interfaz &menu,lista_d<Aminoacido>Aminoacido, lista_d<Proteina> &lista);
void editarAminoacidoProteinas(Interfaz &menu,lista_d<Aminoacido>&AminoacidoList, lista_d<Proteina> &lista);
void buscarProteina(Interfaz& menuanahdir,lista_d<Aminoacido>& Aminoacidolist,lista_d<Proteina> &lista);
void QuickSortProteina(Interfaz& menuanahdir, lista_d<Aminoacido>& Aminoacidolist, lista_d<Proteina> &lista);
//===================FUNCION MAIN=====================//
int main()
{
    system("color 0A");
    //INSTANCIAS DE LAS LISTAS
    Interfaz pantalla;
    lista_d<Aminoacido> AminoacidoList;
    lista_d<Proteina> lista;
    //------------------

    //PROTEINAS DE PRUEBA
//    lista_d<Aminoacido> ListaAminoacido_1;
//    lista_d<Aminoacido> ListaAminoacido_2;
//    lista_d<Aminoacido> ListaAminoacido_3;
//    ListaAminoacido_1.push_f('C');
//    ListaAminoacido_1.push_f('A');
//    ListaAminoacido_1.push_f('N');
//
//    ListaAminoacido_2.push_f('Y');
//    ListaAminoacido_2.push_f('R');
//    ListaAminoacido_2.push_f('K');
//
//    ListaAminoacido_3.push_f('M');
//    ListaAminoacido_3.push_f('P');
//    ListaAminoacido_3.push_f('A');
//
//    Proteina Proteina_1{"Proteina 1",ListaAminoacido_1,1};
//    Proteina Proteina_2{"Proteina 2",ListaAminoacido_2,2};
//    Proteina Proteina_3{"Proteina 3",ListaAminoacido_3,3};
//    lista.push_f(Proteina_1);
//    lista.push_f(Proteina_2);
//    lista.push_f(Proteina_3);

    //------------------

    do
    {
        Menu(pantalla,AminoacidoList,lista); //Menu que cuenta con las opciones del programa
        pantalla.limpiar_pantalla(); //Se hace una limpieza de la pantalla
    } while (true);
}

//=================================== FUNCIONES DEL MENU ============================================//

//=================== MENU --> MOSTRAR OPCIONES =====================//
void Menu(Interfaz &Menu,lista_d<Aminoacido> &AminoacidoList, lista_d<Proteina> &lista)
{
    Menu.limpiarMenu(); //Se limpia la pantalla
    //=======OPCIONES QUE SE DESPLEGARAN EN EL MENU =======//
    //añadir opciones al menu
    Menu.setTitulo("||==Proteinas==||\n\n");
    Menu.anhadirOpcion("[1]. Anhadir Proteina.");
    Menu.anhadirOpcion("[2]. Eliminar Proteina.");
    Menu.anhadirOpcion("[3]. Editar Proteina.");
    Menu.anhadirOpcion("[4]. Buscar proteina.");
    Menu.anhadirOpcion("[5]. Ordenar lista de proteinas.");
    Menu.anhadirOpcion("[6]. Mostrar .");
    Menu.anhadirOpcion("[7]. Salir del programa.");
    Menu.Mostrar(); //Muestra de las opciones agregadas
    int Opc = Opcion(Menu); //Valor de entrada del usuario
    OpcionElegida(Opc,Menu,AminoacidoList,lista); //Se dirige a una funcion
}

//=================== MENU --> PASO DE UNA OPCION =====================//
int Opcion(Interfaz &Menu)
{
    //=== DECLARACION DE VARIABLES E INSTANCIAS ===//
    int opcionMenu = 0;
    bool inputValido = false;
    string input;
    //=============================================//

    while(!inputValido) //VALIDACION DE VALOR DE ENTRADA
    {
        getline(cin, input);
        try
        {
            opcionMenu = stoi(input);
            inputValido = true;
            Menu.setOpcion(opcionMenu);
            while (Menu.getOpcion() < 1 || Menu.getOpcion() > Menu.getSizeOpciones())
            {
                inputValido = false;
                Menu.SystemOutPrintln("Error, Ingresa una opcion valida.\n");
                getline(cin, input);
                opcionMenu = stoi(input);
                Menu.setOpcion(opcionMenu);
            }
            inputValido = true;
        }
        catch(invalid_argument& e)
        {
            Menu.SystemOutPrintln("Valor invalido, ingresa un campo valido\n");
        }

    }
    return opcionMenu; //RETORNO UNA VEZ VALIDADO QUE ES PARTE DE LAS OPCIONES
}

//=================== MENU --> OPCION --> DIRECCION A LA OPCION =====================//

void OpcionElegida(int opcionMenu,Interfaz &menuanahdir, lista_d<Aminoacido> &AminoacidoList,lista_d<Proteina> &lista)
{
    //=== DECLARACION DE VARIABLES E INSTANCIAS ===//
    int opcionMenuAnahdir = 0;
    //=============================================//
    switch (opcionMenu)
    {
        case 1: //AÑADIR PROTEINA
        {
            menuanahdir.limpiarMenu();
            menuanahdir.limpiar_pantalla();
            menuanahdir.setTitulo("AGREGAR PROTEINA\n\n");
            menuanahdir.anhadirOpcion("[1]. Anhadir al inicio.");
            menuanahdir.anhadirOpcion("[2]. Anhadir al final.");
            menuanahdir.anhadirOpcion("[3]. Anhadir en posicion especifica.");
            menuanahdir.anhadirOpcion("[4]. Regresar.\n");
            menuanahdir.Mostrar();
            opcionMenuAnahdir = Opcion(menuanahdir);
            opcionElegidaAnhadir(opcionMenuAnahdir, menuanahdir, AminoacidoList, lista);

            break;
        }
        case 2: //ELIMINAR PROTEINA
        {
            menuanahdir.limpiar_pantalla();
            EliminarProteina(menuanahdir, AminoacidoList, lista);
            break;
        }
        case 3: //EDITAR PROTEINA
        {
            menuanahdir.limpiar_pantalla();
            editarAminoacidoProteinas(menuanahdir, AminoacidoList, lista);
            break;
        }
        case 4: //BUSCAR PROTEINA (POR FOLIO)
        {
            menuanahdir.limpiar_pantalla();
            buscarProteina(menuanahdir,AminoacidoList,lista);
            menuanahdir.Pausar();
            break;
        }
        case 5: //ORDENAR LISTA DE PROTEINAS
        {
            menuanahdir.limpiar_pantalla();
            QuickSortProteina(menuanahdir,AminoacidoList,lista);
            menuanahdir.Pausar();
            break;
        }
        case 6: //MOSTRAR LISTA DE PROTEINAS
        {
            menuanahdir.limpiar_pantalla();
            MostrarLista(menuanahdir,AminoacidoList, lista);
            menuanahdir.Pausar();

            break;
        }
        case 7: //SALIR DEL PROGRAMA
        {
            menuanahdir.limpiar_pantalla();
            menuanahdir.SystemOutPrintln("Gracias por usar este programa. Hasta luego!\n");
            menuanahdir.Pausar();
            exit(0);
            break;
        }
    }
}

//=================== MENU --> OPCION --> ELECCION DE OPCIONES DE "AÑADIR PROTEINA" =====================//
void opcionElegidaAnhadir(int opcionMenuAnahdir,Interfaz &menuanahdir, lista_d<Aminoacido> &AminoacidoList,lista_d<Proteina> &lista)
{
    switch (opcionMenuAnahdir)
    {
        case 1:
            anhadirProteinaFront(menuanahdir,AminoacidoList,lista);
            break;
        case 2:
            anhadirProteinaBack(menuanahdir,AminoacidoList,lista);
            break;
        case 3:
            anhadirProteinaPos(menuanahdir,AminoacidoList,lista);
            break;
        case 4:
        {
            //PROBAR: 22 MAY 1:34PM
            menuanahdir.SystemOutPrintln("Regresando...");
            system("pause");
            menuanahdir.limpiar_pantalla();
            Menu(menuanahdir, AminoacidoList, lista);
            break;
        }
    }
}

//=================== MENU --> OPCION --> AÑADIR PROTEINA EN FRONT =====================//
void anhadirProteinaFront(Interfaz &menu, lista_d<Aminoacido> AminoacidoList, lista_d<Proteina> &lista)
{
    //=== DECLARACION DE VARIABLES E INSTANCIAS ===//
    int folio;
    string nombreProteina;
    lista_d<Aminoacido> NuevaSecuencia;
    string folioS;
    Proteina proteina;
    Aminoacido aminoacido;
    bool folioBool = false;
    bool folio_repetido = true; //folio_repetido_validar

    while(!folioBool || folio_repetido) //VALIDACION DE VALOR DE ENTRADA
    {
        menu.limpiar_pantalla();
        menu.SystemOutPrintln("AGREGAR PROTEINA AL FRENTE\n\n");
        menu.SystemOutPrintln("Inserta el folio de la proteina: ");
        getline(cin, folioS);

        try
        {
                folio = stoi(folioS);
                folioBool = true;
                //implementacion de busqueda binaria para evitar folios repetidos
                if(!lista.vacia())
                {
                    folio_repetido = lista.BusquedaBinariaBool(folio);
                }
                else
                {
                    folio_repetido=false;
                }

                menu.limpiar_pantalla();
                menu.SystemOutPrintln("AGREGAR PROTEINA AL FRENTE\n\n");

                    while (folio <= 0 || folio_repetido) //Valida que el folio no sea menor ni esté repetido
                    {
                        folioBool = false;
                        if (folio_repetido) {
                            menu.SystemOutPrintln("El folio esta duplicado, ingresa otro. ");
                        }
                        else if (!folioBool)
                        {
                            menu.SystemOutPrintln("El folio es menor que 0, ingresa otro. ");
                        }

                        getline(cin, folioS);
                        folio = stoi(folioS);
                        if(!lista.vacia())
                        {
                            folio_repetido = lista.BusquedaBinariaBool(folio);
                        }
                        else
                        {
                            folio_repetido=false;
                        }
                    }
                    folioBool = true;

        }
        catch (invalid_argument &e) //En caso que sea
        {
            menu.SystemOutPrintln("Ingresa un valor valido.\n");
            menu.Pausar();
        }
    }


    proteina.setfolio(folio);
    menu.limpiar_pantalla();
    menu.SystemOutPrintln("AGREGAR PROTEINA AL FRENTE\n\n");
    cout<<"Folio: "<<proteina.getfolio()<<endl;
    menu.SystemOutPrintln("Inserta el nombre de la proteina: ");
    getline(cin, nombreProteina);
    proteina.setNombre(nombreProteina);


    int opcion;
    int aminoacidoIngresado;

    string aminoIngresado;
    do {
        menu.limpiar_pantalla();
        menu.SystemOutPrintln("AGREGAR PROTEINA AL FRENTE\n\n");
        cout<<"Folio: "<<proteina.getfolio()<<endl;
        cout<<"Nombre: "<<proteina.getNombre()<<endl;
        char* unaLetra=aminoacido.getUnaLetra();
        string* nombre_amino = aminoacido.getNombreAmino();
        for (int i=0; i < 20; i++)
        {
            menu.SystemOutPrintln(i+1,unaLetra,i,nombre_amino,i,8,4);
        }
        cout<<"Secuencia Primaria: "<<proteina.getSecuencia()<<endl;
        bool aminoIngresadoBool = false;
        while(!aminoIngresadoBool)
        {
            menu.SystemOutPrintln("Inserta un aminoacido: ");
            getline(cin,aminoIngresado);
            try
            {
                aminoacidoIngresado=stoi(aminoIngresado);
                aminoIngresadoBool=true;

                while (aminoacidoIngresado < 1 || aminoacidoIngresado > 20)
                {
                    aminoIngresadoBool = false;
                    menu.SystemOutPrintln("Ingresa un valor valido: ");
                    getline(cin,aminoIngresado);
                    aminoacidoIngresado = stoi(aminoIngresado);
                }
                aminoIngresadoBool=true;
            }
            catch(invalid_argument &e)
            {
                menu.SystemOutPrintln("Ingresa un valor numerico...\n");
            }
        }

        aminoacido.setAmino(unaLetra[aminoacidoIngresado-1]);
        anhadirAminoacidoBack(aminoacido.getAmino(),NuevaSecuencia);
        menu.SystemOutPrintln("Aminoacido agregado correctamente.\n");
        proteina.setSecuencia(NuevaSecuencia);

        string OtroAmino;
        bool otroAminoBool=false;
        while(!otroAminoBool)
        {
            menu.SystemOutPrintln("Deseas agregar otro aminoacido? 1. Si 2. No: ");
            getline(cin,OtroAmino);
            try
            {
                opcion = stoi(OtroAmino);
                otroAminoBool=true;
                while (opcion < 1 || opcion > 2)
                {
                    otroAminoBool=false;
                    menu.SystemOutPrintln("Ingresa una opcion valida:\n");
                    menu.SystemOutPrintln("Deseas agregar otro aminoacido? 1. Si 2. No: ");
                    getline(cin,OtroAmino);
                    opcion = stoi(OtroAmino);
                }
                otroAminoBool=true;
            }
            catch(invalid_argument &e)
            {
                menu.SystemOutPrintln("Ingresa un valor numerico...\n");
            }
        }

        menu.limpiar_pantalla();
    } while (opcion == 1);
    anhadirProteinasFront(nombreProteina, NuevaSecuencia,lista,folio);
    menu.SystemOutPrintln("AGREGAR PROTEINA AL FRENTE\n\n");
    menu.SystemOutPrintln("Proteina agregada correctamente.\n");
    cout<<proteina;
    menu.Pausar();
    menu.limpiar_pantalla();
    Menu(menu,AminoacidoList,lista);
}

//=================== MENU --> OPCION --> AÑADIR PROTEINA EN BACK =====================//
void anhadirProteinaBack(Interfaz &menu, lista_d<Aminoacido> AminoacidoList, lista_d<Proteina> &lista)
{
    Proteina proteina;
    Aminoacido aminoacido;
    lista_d<Aminoacido> NuevaSecuencia;
    string nombreProteina;
    int folio;
    string folioS;
    bool folioBool = false;
    bool folio_repetido = true; //folio_repetido_validar
    while(!folioBool)
    {
        menu.limpiar_pantalla();
        menu.SystemOutPrintln("AGREGAR PROTEINA POR DETRAS\n\n");
        menu.SystemOutPrintln("Inserta el folio de la proteina: ");
        getline(cin,folioS);
        try
        {
            folio= stoi(folioS);
            folioBool=true;
            if(!lista.vacia())
            {
                folio_repetido = lista.BusquedaBinariaBool(folio);
            }
            else
            {
                folio_repetido=false;
            }
            while(folio<= 0 || folio_repetido)
            {
                folioBool = false;
                if (folio_repetido)
                {
                    menu.SystemOutPrintln("El folio esta duplicado, ingresa otro. ");
                }
                else if (!folioBool)
                {
                    menu.SystemOutPrintln("El folio es menor que 0, ingresa otro. ");
                }
                getline(cin,folioS);
                folio= stoi(folioS);
                if(!lista.vacia())
                {
                    folio_repetido = lista.BusquedaBinariaBool(folio);
                }
                else
                {
                    folio_repetido=false;
                }
            }
            folioBool = true;

        }
        catch(invalid_argument &e)
        {
            menu.SystemOutPrintln("Ingrese un valor valido.\n");
        }
    }
    proteina.setfolio(folio);
    cout<<"Folio: "<<proteina.getfolio()<<endl;
    menu.SystemOutPrintln("Inserta el nombre de la proteina: ");
    getline(cin, nombreProteina);
    proteina.setNombre(nombreProteina);
    menu.limpiar_pantalla();
    menu.SystemOutPrintln("AGREGAR PROTEINA POR DETRAS\n\n");

    int opcion;
    int aminoacidoIngresado;
    string aminoString;

    do
    {
        cout<<"Folio: "<<proteina.getfolio()<<endl;
        cout<<"Nombre: "<<proteina.getNombre()<<endl;
        char* unaLetra=aminoacido.getUnaLetra();
        string* nombre_amino = aminoacido.getNombreAmino();
        for (int i=0; i < 20; i++)
        {
            menu.SystemOutPrintln(i+1,unaLetra,i,nombre_amino,i,8,4);
        }
        cout<<"Secuencia Primaria: "<<proteina.getSecuencia()<<endl;
        bool AminoIngresadoBool = false;
        while(!AminoIngresadoBool)
        {
            menu.SystemOutPrintln("Inserta un aminoacido: ");
            getline(cin,aminoString);
            try
            {
                aminoacidoIngresado=stoi(aminoString);
                AminoIngresadoBool = true;
                while (aminoacidoIngresado < 1 || aminoacidoIngresado > 20)
                {
                    AminoIngresadoBool = false;
                    menu.SystemOutPrintln("Ingresa un valor valido: ");
                    getline(cin,aminoString);
                    aminoacidoIngresado = stoi(aminoString);
                }
                AminoIngresadoBool = true;
            }
            catch(invalid_argument &e)
            {
                menu.SystemOutPrintln("Ingrese un valor numerico...\n");
            }
        }

        aminoacido.setAmino(unaLetra[aminoacidoIngresado-1]);
        anhadirAminoacidoBack(aminoacido.getAmino(),NuevaSecuencia);
        menu.SystemOutPrintln("Aminoacido agregado correctamente\n");
        proteina.setSecuencia(NuevaSecuencia);

        string opcString;
        bool opcStringBool=false;
        while(!opcStringBool)
        {
            menu.SystemOutPrintln("Deseas agregar otro aminoacido? 1. Si 2. No: ");
            getline(cin,opcString);
            try
            {
                opcion=stoi(opcString);
                opcStringBool=true;
                while (opcion < 1 || opcion > 2) {
                    opcStringBool = false;
                    menu.SystemOutPrintln("Ingresa una opcion valida: ");
                    menu.SystemOutPrintln("Deseas agregar otro aminoacido? 1. Si 2. No: ");
                    getline(cin,opcString);
                    opcion= stoi(opcString);
                }
                opcStringBool=true;
            }
            catch(invalid_argument &e)
            {
                menu.SystemOutPrintln("Ingresa un valor numerico...\n");
            }
        }

        menu.limpiar_pantalla();
    } while (opcion == 1);

    anhadirProteinaBack(nombreProteina, NuevaSecuencia,lista,folio);
    menu.SystemOutPrintln("AGREGAR PROTEINA POR DETRAS\n\n");
    menu.SystemOutPrintln("Proteina agregada correctamente\n");
    cout<<proteina;
    menu.Pausar();
    menu.limpiar_pantalla();
    Menu(menu,AminoacidoList,lista);
}

//=================== MENU --> OPCION --> AÑADIR PROTEINA EN POSICION =====================//
void anhadirProteinaPos(Interfaz &menu, lista_d<Aminoacido> AminoacidoList, lista_d<Proteina> &lista)
{
    Proteina proteina;
    Aminoacido aminoacido;
    lista_d<Aminoacido> NuevaSecuencia;
    string nombreProteina;
    string pos;
    int posNum;
    string posNumero;
    bool posNumeroBool = false;
    while(!posNumeroBool)
    {
        menu.limpiar_pantalla();
        menu.SystemOutPrintln("AGREGAR PROTEINA POR POSICION\n\n");
        menu.SystemOutPrintln("Ingresa la posicion donde quieres ingresar la proteina: ");
        getline(cin, pos);
        try
        {
            posNum = stoi(pos);
            posNumeroBool = true;
            while((posNum<0)||posNum>lista.getTamanio()+1)
            {
                posNumeroBool = false;
                menu.SystemOutPrintln("Ingresa una posicion valida: ");
                getline(cin, pos);
                posNum = stoi(pos);
            }
            posNumeroBool = true;

        }
        catch(invalid_argument &e)
        {
            menu.SystemOutPrintln("Ingresa un valor numerico...\n");
        }
    }
    menu.limpiar_pantalla();
    menu.SystemOutPrintln("AGREGAR PROTEINA POR POSICION\n\n");
    cout<<"Posicion: "<<posNum<<endl;

    int folio;
    string folioS;
    bool boolFolio = false;
    bool folio_repetido = true; //folio_repetido_validar
    while(!boolFolio)
    {

        menu.SystemOutPrintln("Inserta el folio de la proteina: ");
        getline(cin,folioS);
        try
        {
            folio= stoi(folioS);
            boolFolio = true;
            if(!lista.vacia())
            {
                folio_repetido = lista.BusquedaBinariaBool(folio);
            }
            else
            {
                folio_repetido=false;
            }

            while(folio<= 0 || folio_repetido)
            {
                boolFolio = false;
                if (folio_repetido)
                {
                    menu.SystemOutPrintln("El folio esta duplicado, ingresa otro. ");
                }
                else if (!boolFolio)
                {
                    menu.SystemOutPrintln("El folio es menor que 0, ingresa otro. ");
                }
                getline(cin,folioS);
                folio= stoi(folioS);
                if(!lista.vacia())
                {
                    folio_repetido = lista.BusquedaBinariaBool(folio);
                }else{
                    folio_repetido=false;
                }
            }
            boolFolio = true;

        }
        catch(invalid_argument &e)
        {
            menu.SystemOutPrintln("Ingresa un valor numerico...\n");
        }
    }

    proteina.setfolio(folio);
    menu.limpiar_pantalla();
    menu.SystemOutPrintln("AGREGAR PROTEINA POR POSICION \n\n");
    cout<<"Posicion: "<<posNum<<endl;
    cout<<"Folio: "<<proteina.getfolio()<<endl;
    menu.SystemOutPrintln("Inserta el nombre de la proteina: ");
    getline(cin, nombreProteina);
    proteina.setNombre(nombreProteina);

    int opcion;
    int aminoacidoIngresado;
    //char* array = aminoacido.getUnaLetra();
    do {
        menu.limpiar_pantalla();
        menu.SystemOutPrintln("AGREGAR PROTEINA POR POSICION\n\n");
        cout<<"Posicion: "<<posNum<<endl;
        cout<<"Folio: "<<proteina.getfolio()<<endl;
        cout<<"Nombre: "<<proteina.getNombre()<<endl;
        char* unaLetra=aminoacido.getUnaLetra();
        string* nombre_amino = aminoacido.getNombreAmino();
        for (int i=0; i < 20; i++)
        {
            menu.SystemOutPrintln(i+1,unaLetra,i,nombre_amino,i,8,4);
        }
        cout<<"Secuencia Primaria: "<<proteina.getSecuencia()<<endl;
        bool boolAmino=false;
        string aminoString;
        while(!boolAmino)
        {
            menu.SystemOutPrintln("Inserta un aminoacido: ");
            getline(cin,aminoString);
            try
            {
                aminoacidoIngresado = stoi(aminoString);
                boolAmino = true;
                while (aminoacidoIngresado < 1 || aminoacidoIngresado > 20)
                {
                    boolAmino = false;
                    menu.SystemOutPrintln("Ingresa un valor valido: ");
                    getline(cin,aminoString);
                    aminoacidoIngresado = stoi(aminoString);
                }
                boolAmino = true;
            }
            catch(invalid_argument &e)
            {
                menu.SystemOutPrintln("Ingresa un valor numerico...\n");
            }
        }

        aminoacido.setAmino(unaLetra[aminoacidoIngresado-1]);
        anhadirAminoacidoBack(aminoacido.getAmino(),NuevaSecuencia);


        menu.SystemOutPrintln("Aminoacido agregado correctamente: ");

        proteina.setSecuencia(NuevaSecuencia);

        string opcString;
        bool opcStringBool=false;
        while(!opcStringBool)
        {
            menu.SystemOutPrintln("Deseas agregar otro aminoacido? 1. Si 2. No: ");
            getline(cin,opcString);
            try
            {
                opcion=stoi(opcString);
                opcStringBool=true;
                while (opcion < 1 || opcion > 2)
                {
                    opcStringBool = false;
                    menu.SystemOutPrintln("Ingresa una opcion valida: ");
                    menu.SystemOutPrintln("Deseas agregar otro aminoacido? 1. Si 2. No: ");
                    getline(cin,opcString);
                    opcion= stoi(opcString);
                }
                opcStringBool = true;
            }
            catch(invalid_argument &e)
            {
                menu.SystemOutPrintln("Ingresa un valor numerico...\n");
            }
        }
        menu.limpiar_pantalla();
    } while (opcion == 1);

    anhadirProteinasPos(nombreProteina, NuevaSecuencia,posNum-1,lista,folio);
    menu.SystemOutPrintln("AGREGAR PROTEINA POR POSICION \n\n");
    menu.SystemOutPrintln("Proteina agregada correctamente");
    //imprimir la proteina
    cout<<proteina;
    menu.Pausar();
    menu.limpiar_pantalla();
    Menu(menu,AminoacidoList,lista);
}


//===================MOSTRAR PROTEINAS======================//
void MostrarLista(Interfaz& pantalla,lista_d<Aminoacido>amino,lista_d<Proteina>& Lista)
{
    if (Lista.vacia())
    {
        pantalla.SystemOutPrintln("La lista esta vacia\n");
        pantalla.Pausar();
        pantalla.limpiar_pantalla();
        Menu(pantalla,amino,Lista);
    }
    else
    {
        string elemento;
        int opc;
        bool opcIngresada = false;
        pantalla.limpiar_pantalla();
        pantalla.SystemOutPrintln("MOSTRAR PROTEINAS\n\n");
        pantalla.limpiarMenu();
        pantalla.setTitulo("");
        pantalla.anhadirOpcion("[1]. Mostrar toda lista.");
        pantalla.anhadirOpcion("[2]. Mostrar un elemento de la lista.");
        pantalla.anhadirOpcion("[3]. Regresar.");
        pantalla.Mostrar();

        while(!opcIngresada)
        {
            getline(cin,elemento);
            try
            {
                opc = stoi(elemento);
                opcIngresada = true;
                pantalla.setOpcion(opc);
                while (pantalla.getOpcion() < 1 || pantalla.getOpcion() > pantalla.getSizeOpciones()) //Validar para alfanumérico
                {
                    opcIngresada = false;
                    pantalla.SystemOutPrintln("Error, Ingresa una opcion valida.\n");
                    getline(cin, elemento);
                    opc = stoi(elemento); // Usar la variable existente
                    pantalla.setOpcion(opc);
                }
                opcIngresada = true;
            }
            catch(invalid_argument &e)
            {
                pantalla.SystemOutPrintln("Ingresa un valor numerico...");
            }
        }



        switch(opc)
        {
            case 1:
            {
                Lista.imprimir_lista(cout);
                break;
            }
            case 2:
            {
                int folio;
                string indiceString;
                bool indiceBuscadoBool= false;
                bool FolioEncontrado=true;
                while(!indiceBuscadoBool || FolioEncontrado)
                {
                    pantalla.SystemOutPrintln("Ingresa el folio del elemento a mostrar: ");
                    getline(cin,indiceString);
                    try
                    {
                        folio = stoi(indiceString);
                        FolioEncontrado = Lista.BusquedaBinariaBool(folio);
                        indiceBuscadoBool = true;

                        while((folio<0))
                        {
                            indiceBuscadoBool = false;
                            pantalla.SystemOutPrintln("Ingresa un indice valido: ");
                            getline(cin,indiceString);
                            folio = stoi(indiceString);
                        }
                        if(FolioEncontrado)
                        {
                            cout<<"\nProteina: \n"<<Lista.BusquedaBinaria(folio)<<endl;
                            FolioEncontrado = false;
                        }
                        else
                        {

                            pantalla.SystemOutPrintln("Elemento no encontrado...");
                        }
                        indiceBuscadoBool = true;
                    }
                    catch(invalid_argument &e)
                    {
                        pantalla.SystemOutPrintln("Ingresa un valor numerico...\n");
                    }
                }

                break;
            }
            case 3:
                pantalla.SystemOutPrintln("Regresando...\n");
                pantalla.Pausar();
                pantalla.limpiar_pantalla();
                Menu(pantalla,amino, Lista);
                break;
            default:
            {
                break;
            }
        }
    }


}


//=====================ELIMINAR PROTEINA DE LA LISTA========================//
void EliminarProteina(Interfaz &menu,lista_d<Aminoacido>Aminoacidos, lista_d<Proteina> &lista)
{
    //verificar si la lista esta vacia
    if(lista.vacia()){
        menu.SystemOutPrintln("La lista esta vacia.\n");
        menu.Pausar();
        menu.limpiar_pantalla();
        Menu(menu,Aminoacidos,lista);
    }
    else
    {
        int opc=0;
        string stringOpc="";
        int posEliminar=0;
        bool eliminar = false;
        string stringEliminar="";

        menu.SystemOutPrintln("ELIMINAR PROTEINAS\n\n");
        menu.SystemOutPrintln("Lista de Proteinas\n\n");
        lista.imprimir_lista(cout);
        menu.SystemOutPrintln("\nElige una opcion para eliminar una proteina:\n");
        menu.limpiarMenu();
        menu.setTitulo("");
        menu.anhadirOpcion("[1]. Eliminar al principio.");
        menu.anhadirOpcion("[2]. Eliminar en una posicion.");
        menu.anhadirOpcion("[3]. Eliminar al final.");
        menu.anhadirOpcion("[4]. Regresar.");
        menu.Mostrar();

        opc = Opcion(menu); //Valor de entrada del usuario

        menu.limpiar_pantalla();
        lista.imprimir_lista(cout);

        switch (opc)
        {
            case 1:
            {
                //implementacion de eliminar en el inicio de la lista
                menu.limpiar_pantalla();
                menu.SystemOutPrintln("ELIMINAR PROTEINAS AL PRINCIPIO\n\n");
                lista.pop_f();
                lista.imprimir_lista(cout) ;
                menu.SystemOutPrintln("Proteina eliminada al principio de la lista.\n");
                menu.Pausar();

                break;
            }
            case 2:
            {
                try {
                    //validacion y implementacion de funcion eliminar en una posicion
                    bool eliminaBool = false;

                    menu.limpiar_pantalla();
                    menu.SystemOutPrintln("ELIMINAR PROTEINAS POR POSICION\n\n");
                    lista.imprimir_lista(cout);

                    while (!eliminaBool) {
                        menu.SystemOutPrintln("Escribe la posicion que deseas eliminar: \n");
                        getline(cin, stringEliminar);
                        try {
                            posEliminar = stoi(stringEliminar);
                            posEliminar = posEliminar - 1;
                            eliminaBool = true;

                            while ((posEliminar < -1) || (posEliminar > lista.getTamanio()))
                            {
                                eliminaBool = false;
                                menu.SystemOutPrintln("La posicion indicada no es valida, ingresa otro valor: ");
                                getline(cin, stringEliminar);
                                posEliminar = stoi(stringEliminar);
                                posEliminar = posEliminar - 1;

                            }
                            eliminaBool = true;

                        }
                        catch (invalid_argument &e) {
                            menu.SystemOutPrintln("Ingresa un valor numerico...");
                        }
                    }
                    menu.limpiar_pantalla();
                    menu.SystemOutPrintln("ELIMINAR PROTEINAS POR POSICION\n\n");
                    lista.pop_p(posEliminar);
                    lista.imprimir_lista(cout);
                    menu.SystemOutPrintln("Proteina eliminada en la posicion indicada.\n");
                    menu.Pausar();
                }
                catch (const exception &e) {
                    menu.SystemOutPrintln("No hay elementos validos\n");
                    menu.limpiar_pantalla();
                    Menu(menu, Aminoacidos, lista);

                }

                break;
            }
                //implementacion de la funcion eliminar al final
            case 3:
            {
                menu.limpiar_pantalla();
                menu.SystemOutPrintln("ELIMINAR PROTEINAS AL FINAL\n\n");
                lista.pop_b();
                lista.imprimir_lista(cout);
                menu.SystemOutPrintln("Proteina eliminada al final de la lista. \n");
                menu.Pausar();
                break;
            }
            case 4:
            {
                menu.SystemOutPrintln("Regresando...\n");
                menu.Pausar();
                menu.limpiar_pantalla();
                Menu(menu, Aminoacidos, lista);
                break;
            }
        }
    }
}

//Esta funcion agrega aminoacidos a la proteina escogida por el usuario.
void agregarAminoacido (Interfaz &menu, lista_d<Aminoacido>& AminoacidoList, lista_d<Proteina> &lista)
{
    int folio_proteina1=1;
    int pos_aminoacido1=0;
    int aminoacidoIngresado1=0;
    int opcInt=1;
    string aminoacidoIngresado="";
    string folio_proteina="";
    string pos_aminoacido="";
    Aminoacido aminoacido;
    string opc="";

    menu.limpiar_pantalla();
    menu.SystemOutPrintln("AGREGAR AMINOACIADO A PROTEINA\n\n");
    menu.SystemOutPrintln("Proteinas existentes:\n\n");
    lista.imprimir_lista(cout);
    bool proteModBool = false;
    bool folio_existente = true; //folio_existente_validar
    while(!proteModBool)
    {
        menu.SystemOutPrintln("\nEscoge que proteina agregarle un aminoacido (FOLIO):");
        getline(cin, folio_proteina);
        try
        {
            folio_proteina1 = stoi(folio_proteina);
            if(!lista.vacia())
            {
                folio_existente = lista.BusquedaBinariaBool(folio_proteina1);
            }else{
                folio_existente=false;
            }
            proteModBool = true;
            while((folio_proteina1 < 0) || !folio_existente) {
                proteModBool = false;
                if (folio_proteina1 < 0)
                {
                    menu.SystemOutPrintln("El folio indicado no es valido, ingresa otro valor: ");
                }
                else if (!folio_existente)
                {
                    menu.SystemOutPrintln("El folio indicado no existe, ingresa otro valor: ");
                }
                getline(cin, folio_proteina);
                folio_proteina1 = stoi(folio_proteina);
                if(!lista.vacia())
                {
                    folio_existente = lista.BusquedaBinariaBool(folio_proteina1);
                }else{
                    folio_existente=false;
                }
            }
            proteModBool = true;
        }
        catch(invalid_argument &e)
        {
            menu.SystemOutPrintln("Ingresa un valor numerico...");
        }
    }

do {

    lista_d<Aminoacido> &secuencia = lista.BusquedaBinaria(folio_proteina1).getSecuencia();
    bool posAminoBool = false;
    while (!posAminoBool) {
        menu.limpiar_pantalla();
        menu.SystemOutPrintln("AGREGAR AMINOACIADO A PROTEINA\n\n");
        cout<<"Proteina:"<<lista.BusquedaBinaria(folio_proteina1)<<endl;
        menu.SystemOutPrintln("\nEscoge en que posicion quieres agregar el aminoacido:");

        getline(cin, pos_aminoacido);
        try {

            pos_aminoacido1 = stoi(pos_aminoacido);
            pos_aminoacido1 = pos_aminoacido1 - 1;
            posAminoBool = true;
            while ((pos_aminoacido1 < 0) || (pos_aminoacido1 >= secuencia.getTamanio() + 1)) {
                posAminoBool = false;
                menu.SystemOutPrintln("La posicion indicada no es valida, ingresa otro valor: ");
                getline(cin, pos_aminoacido);
                pos_aminoacido1 = stoi(pos_aminoacido);
                pos_aminoacido1 = pos_aminoacido1 - 1;

            }
            posAminoBool = true;
        }
        catch (invalid_argument &e) {
            menu.SystemOutPrintln("Ingresa un valor numerico...");
        }
    }

    //tomar el valor del array
    menu.limpiar_pantalla();
    menu.SystemOutPrintln("AGREGAR AMINOACIADO A PROTEINA\n\n");
    cout<<"Proteina:\n"<<lista.BusquedaBinaria(folio_proteina1)<<endl;
    cout<<"Posicion del aminoacido:"<<pos_aminoacido1+1<<endl;

    char *unaLetra = aminoacido.getUnaLetra();
    string *nombre_amino = aminoacido.getNombreAmino();
    for (int i = 0; i < 20; i++) {
        menu.SystemOutPrintln(i + 1, unaLetra, i, nombre_amino, i, 8, 4);
    }
    bool aminoBool = false;
    while (!aminoBool) {
        menu.SystemOutPrintln("Inserta un aminoacido: ");
        getline(cin, aminoacidoIngresado);
        try {
            aminoacidoIngresado1 = stoi(aminoacidoIngresado);
            aminoacidoIngresado1 = aminoacidoIngresado1 - 1;

            aminoBool = true;
            while (aminoacidoIngresado1 < 0 || aminoacidoIngresado1 >= 19) {
                aminoBool = false;
                menu.SystemOutPrintln("Ingresa un valor valido: ");
                getline(cin, aminoacidoIngresado);
                aminoacidoIngresado1 = stoi(aminoacidoIngresado);
                aminoacidoIngresado1 = aminoacidoIngresado1 - 1;
            }
            aminoBool = true;
        }
        catch (invalid_argument &e) {
            menu.SystemOutPrintln("Ingresa un valor numerico...");
        }
    }

    aminoacido.setAmino(unaLetra[aminoacidoIngresado1]);

    try {
        anhadirProAminoacido(folio_proteina1, pos_aminoacido1, aminoacido, lista);
        menu.SystemOutPrintln("Aminoacido agregado.\n\n");
    } catch (const exception &e) {
        menu.SystemOutPrintln("No se pudo agregar el aminoacido: " + string(e.what()) + "\n");
        menu.limpiar_pantalla();
        Menu(menu, AminoacidoList, lista);
    }

    menu.limpiar_pantalla();
    menu.SystemOutPrintln("AGREGAR AMINOACIADO A PROTEINA\n\n");
    if(!lista.vacia())
    {
        cout<<"Proteina: \n"<< lista.BusquedaBinaria(folio_proteina1)<<endl;
    }
    bool otroAminoBool = false;
    while(!otroAminoBool)
    {
        menu.SystemOutPrintln("Deseas agregar otro aminoacido a la proteina? 1. Si  2. No: ");
        getline(cin,opc);
        try
        {
                opcInt=stoi(opc);
                otroAminoBool=true;
                while (opcInt < 1 || opcInt > 2) {
                    otroAminoBool = false;
                    menu.SystemOutPrintln("Ingresa una opcion valida. ");
                    menu.SystemOutPrintln("Deseas agregar otro aminoacido a la proteina? 1. Si 2. No: ");
                    getline(cin,opc);
                    opcInt= stoi(opc);
                }
                otroAminoBool = true;
        }
        catch(invalid_argument &e)
        {
            menu.SystemOutPrintln("Ingresa un valor numerico...");\
            menu.Pausar();
        }
    }

}while(opcInt == 1);
    menu.Pausar();
}

//Esta funcion elimina aminoacidos de la proteina escogida.
void eliminarAminoacido(Interfaz &menu, lista_d<Aminoacido> & AminoacidoList, lista_d<Proteina> &lista)
{
    int opc1=0;
    int folio_proteina1=0;
    int pos_aminoacido1=0;
    string folio_proteina="";
    string pos_aminoacido="";
    bool proteModBool = false;
    int opcInt=0;
    string opc="";
    bool folio_existente = false; //folio_existente_validar

    menu.limpiar_pantalla();
    menu.SystemOutPrintln("ELIMINAR AMINOACIDO A PROTEINA\n\n");
    menu.SystemOutPrintln("Proteinas existentes:\n\n");
    lista.imprimir_lista(cout);

    while(!proteModBool)
    {
        menu.SystemOutPrintln("\nEscoge que proteina eliminar un aminoacido (FOLIO):");
        getline(cin, folio_proteina);
        try
        {
            folio_proteina1 = stoi(folio_proteina);
            proteModBool= true;
            if(!lista.vacia())
            {
                folio_existente = lista.BusquedaBinariaBool(folio_proteina1);
            }else{
                folio_existente = true;
            }
            while ((folio_proteina1 < 0) || !folio_existente)
            {
                if (folio_proteina1 < 0)
                {
                    menu.SystemOutPrintln("El folio indicado no es valido, ingresa otro valor: ");
                }
                else if (folio_existente)
                {
                    menu.SystemOutPrintln("El folio indicado no existe, ingresa otro valor: ");
                }
                proteModBool = false;
                getline(cin, folio_proteina);
                folio_proteina1 = stoi(folio_proteina);
                if(!lista.vacia())
                {
                    folio_existente = lista.BusquedaBinariaBool(folio_proteina1);
                }else{
                    folio_existente = true;
                }
            }
            proteModBool = true;
        }
        catch(invalid_argument &e)
        {
            menu.SystemOutPrintln("Ingresa un valor numerico...");
        }
    }

    do {

        lista_d<Aminoacido> &secuencia = lista.BusquedaBinaria(folio_proteina1).getSecuencia();
        if (secuencia.getTamanio() <= 1) {
            menu.SystemOutPrintln("\nNo se puede eliminar un aminoacido de una proteina con un solo aminoacido. \n");
            menu.Pausar();
            menu.limpiar_pantalla();
            Menu(menu, AminoacidoList, lista);
        }

        bool posElimBool = false;

        while (!posElimBool) {
            menu.limpiar_pantalla();
            menu.SystemOutPrintln("ELIMINAR AMINOACIADO A PROTEINA\n\n");
            cout<<"Proteina:\n"<<lista.BusquedaBinaria(folio_proteina1)<<endl;
            menu.SystemOutPrintln("\nEscoge en que posicion quieres eliminar el aminoacido:");
            getline(cin, pos_aminoacido);
            try {
                pos_aminoacido1 = stoi(pos_aminoacido);
                pos_aminoacido1 = pos_aminoacido1 - 1;
                posElimBool = true;
                while ((pos_aminoacido1 < 0) || (pos_aminoacido1 >= secuencia.getTamanio())) {
                    posElimBool = false;
                    menu.SystemOutPrintln("La posicion indicada no es valida, ingresa otro valor: ");
                    getline(cin, pos_aminoacido);
                    pos_aminoacido1 = stoi(pos_aminoacido);
                    pos_aminoacido1 = pos_aminoacido1 - 1;

                }
                posElimBool = true;
            }
            catch (invalid_argument &e) {
                menu.SystemOutPrintln("ingrese un valor numerico...");
            }
        }


        try {
            eliminarProAminoacido(folio_proteina1, pos_aminoacido1, lista);
        } catch (const exception &e) {
            menu.SystemOutPrintln("No se pudo eliminar el aminoacido: " + string(e.what()) + "\n");
        }
        if(!lista.vacia())
        {
            menu.limpiar_pantalla();
            menu.SystemOutPrintln("ELIMINAR AMINOACIADO A PROTEINA\n\n");
            menu.SystemOutPrintln("Aminoacido eliminado.\n");
            cout<<"Proteina:\n"<<lista.BusquedaBinaria(folio_proteina1)<<endl;
        }

        bool otroAminoBool = false;
        while(!otroAminoBool)
        {
            menu.SystemOutPrintln("Deseas eliminar otro aminoacido a la proteina? 1. Si  2. No: ");
            getline(cin,opc);
            try
            {
                opcInt=stoi(opc);
                otroAminoBool=true;
                while (opcInt < 1 || opcInt > 2) {
                    otroAminoBool = false;
                    menu.SystemOutPrintln("Ingresa una opcion valida: ");
                    menu.SystemOutPrintln("Deseas eliminar otro aminoacido? 1. Si 2. No: ");
                    getline(cin,opc);
                    opcInt= stoi(opc);
                }
                otroAminoBool = true;
            }
            catch(invalid_argument &e)
            {
                menu.SystemOutPrintln("Ingresa un valor numerico...\n");
            }
        }


    }while(opcInt==1);
    menu.Pausar();

}

//Esta funcion cambia el nombre de la proteina escogida.
void cambiarNombreProteina(Interfaz &menu,lista_d<Aminoacido>amino, lista_d<Proteina> &lista)
{
    int opc1=0;
    int folio_proteina1=0;
    string folio_proteina="";
    string nuevo_nombre="";
    bool modNombreBool=false;


    bool folio_existente = false; //folio_existente_validar

    menu.limpiar_pantalla();
    menu.SystemOutPrintln("CAMBIAR NOMBRE A PROTEINA\n\n");
    menu.SystemOutPrintln("Proteinas existentes:\n\n");
    lista.imprimir_lista(cout);
    while(!modNombreBool)
    {
        menu.SystemOutPrintln("\nEscoge que proteina cambiarle el nombre (FOLIO): ");
        getline(cin, folio_proteina);
        try
        {
            folio_proteina1=stoi(folio_proteina);
            modNombreBool=true;
            if(!lista.vacia())
            {
                folio_existente = lista.BusquedaBinariaBool(folio_proteina1);
            }else{
                folio_existente = true;
            }
            while ((folio_proteina1 < 0) || !folio_existente)
            {
                if (folio_proteina1 < 0)
                {
                    menu.SystemOutPrintln("El folio indicado no es valido, ingresa otro valor: ");
                }
                else if (!folio_existente)
                {
                    menu.SystemOutPrintln("El folio indicado no existe, ingresa otro valor: ");
                }
                modNombreBool = false;
                getline(cin, folio_proteina);
                folio_proteina1 = stoi(folio_proteina);
                if(!lista.vacia())
                {
                    folio_existente = lista.BusquedaBinariaBool(folio_proteina1);
                }else{
                    folio_existente = true;
                }
            }
            modNombreBool = true;
        }
        catch (invalid_argument &e)
        {
            menu.SystemOutPrintln("Ingresa un valor numerico...");
        }
    }

    menu.limpiar_pantalla();
    menu.SystemOutPrintln("CAMBIAR NOMBRE A PROTEINA\n\n");
    cout<<"Proteina:\n"<<lista.BusquedaBinaria(folio_proteina1)<<endl;
    menu.SystemOutPrintln("\nIngresa el nuevo nombre para la proteina: ");
    getline(cin, nuevo_nombre);
    lista.BusquedaBinaria(folio_proteina1).setNombre(nuevo_nombre);

    menu.limpiar_pantalla();
    menu.SystemOutPrintln("CAMBIAR NOMBRE A PROTEINA\n\n");
    menu.SystemOutPrintln("\nNombre de la proteina cambiado correctamente.\n");
    cout<<"Proteina:\n"<<lista.BusquedaBinaria(folio_proteina1)<<endl;

    menu.Pausar();
}

//Esta funcion cambia el folio de la proteina escogida.
void cambiarFolioProteina(Interfaz &menu,lista_d<Aminoacido>amino, lista_d<Proteina> &lista)
{
    cin.clear();
    int folio_proteina1=0;
    string folio_proteina="";
    int nuevo_folio1=0;
    string nuevo_folio="";
    bool posModBool=false;
    bool folio_existente = false;

    menu.limpiar_pantalla();
    menu.SystemOutPrintln("CAMBIAR FOLIO A PROTEINA\n\n");
    menu.SystemOutPrintln("Proteinas existentes:\n\n");
    lista.imprimir_lista(cout);

    while(!posModBool)
    {
        menu.SystemOutPrintln("\nEscoge que proteina cambiarle el folio (FOLIO): ");
        getline(cin, folio_proteina);

        try {
            folio_proteina1 = stoi(folio_proteina);
            posModBool = true;

            if(!lista.vacia())
            {
                folio_existente = lista.BusquedaBinariaBool(folio_proteina1);
            }else{
                folio_existente = true;
            }

            while ((folio_proteina1 < 0) || !folio_existente) {
                if (folio_proteina1 < 0) {
                    menu.SystemOutPrintln("El folio indicado no es valido, ingresa otro valor: ");
                } else if (folio_existente) {
                    menu.SystemOutPrintln("El folio indicado no existe, ingresa otro valor: ");
                }
                posModBool = false;
                getline(cin, folio_proteina);
                folio_proteina1 = stoi(folio_proteina);
                if (!lista.vacia()) {
                    folio_existente = lista.BusquedaBinariaBool(folio_proteina1);
                } else {
                    folio_existente = true;
                }
                posModBool = true;
            }
        }
        catch(invalid_argument &e)
        {
            menu.SystemOutPrintln("Ingresa un valor numerico...");
        }
    }


    bool newFolioBool = false;
    bool folio_repetido = true; //folio_repetido_validar

    menu.limpiar_pantalla();
    menu.SystemOutPrintln("CAMBIAR FOLIO A PROTEINA\n\n");
    cout<<"Proteina:\n"<<lista.BusquedaBinaria(folio_proteina1)<<endl;
    while(!newFolioBool)
    {
        menu.SystemOutPrintln("\nIngresa el nuevo folio para la proteina: ");
        getline(cin, nuevo_folio);
        try
        {
            nuevo_folio1 = stoi(nuevo_folio);
            newFolioBool = true;
            if(!lista.vacia())
            {
                folio_repetido = lista.BusquedaBinariaBool(nuevo_folio1);
            }else{
                folio_repetido=false;
            }
            while(nuevo_folio1<=0 || folio_repetido)
            {
                newFolioBool = false;
                if (folio_repetido)
                {
                    menu.SystemOutPrintln("El folio esta duplicado, ingresa otro: ");
                }
                else if (!newFolioBool)
                {
                    menu.SystemOutPrintln("El folio es menor que 0, ingresa otro: ");
                }
                getline(cin,nuevo_folio);
                nuevo_folio1= stoi(nuevo_folio);
                if(!lista.vacia())
                {
                    folio_repetido = lista.BusquedaBinariaBool(nuevo_folio1);
                }else{
                    folio_repetido=false;
                }
            }
            newFolioBool = true;
        }
        catch(invalid_argument &e)
        {
            menu.SystemOutPrintln("Ingresa un valor numerico...");
        }
    }

    lista.BusquedaBinaria(folio_proteina1).setfolio(nuevo_folio1);

    menu.limpiar_pantalla();
    menu.SystemOutPrintln("CAMBIAR FOLIO A PROTEINA\n\n");
    menu.SystemOutPrintln("\nFolio de la proteina cambiado correctamente.\n");
    cout<<"Proteina:\n"<<lista.BusquedaBinaria(nuevo_folio1)<<endl;

    menu.Pausar();
}

//======================EDITAR PROTEINAS DE LA LISTA ========================//
void editarAminoacidoProteinas(Interfaz &menu,lista_d<Aminoacido>&AminoacidoList, lista_d<Proteina> &lista)
{
     int opc1=0;

     if(lista.vacia())
     {
         menu.SystemOutPrintln("EDITAR PROTEINAS \n\n");
         menu.SystemOutPrintln("\nLa lista de proteinas esta vacia. \n");
         menu.Pausar();
         menu.limpiar_pantalla();
         Menu(menu,AminoacidoList,lista);

     }

     else
     {
         menu.SystemOutPrintln("EDITAR PROTEINAS \n\n");
         menu.SystemOutPrintln("Elige que hacer con una proteina: \n");
         menu.limpiarMenu();
         menu.setTitulo("");
         menu.anhadirOpcion("[1]. Agregar un aminoacido a la secuencia.");
         menu.anhadirOpcion("[2]. Eliminar un aminoacido de la secuencia.");
         menu.anhadirOpcion("[3]. Cambiar nombre de una proteina.");
         menu.anhadirOpcion("[4]. Cambiar numero de folio de una proteina.");
         menu.anhadirOpcion("[5]. Regresar.");
         menu.Mostrar();
         opc1=Opcion(menu);

         switch(opc1)
         {
             case 1:
             {
                 agregarAminoacido(menu, AminoacidoList, lista);
                 break;
             }
             case 2: {
                 eliminarAminoacido(menu, AminoacidoList, lista);
                 break;
             }
             case 3:
             {
                 cambiarNombreProteina(menu,AminoacidoList, lista);
                 break;
             }
             case 4:
             {
                 cin.clear();
                 cambiarFolioProteina(menu,AminoacidoList, lista);

                 break;
             }

             case 5:
             {
                 menu.SystemOutPrintln("Regresando...");
                 menu.Pausar();

                 menu.limpiar_pantalla();
                 Menu(menu,AminoacidoList,lista);
                 break;
             }
         }
     }
}

void buscarProteina(Interfaz& menuanahdir,lista_d<Aminoacido>&AminoacidoList,lista_d<Proteina>&lista)
{
    if(lista.vacia())
    {
        menuanahdir.SystemOutPrintln("BUSCAR PROTEINAS\n\n");
        menuanahdir.SystemOutPrintln("La lista de proteinas esta vacia. \n");
        menuanahdir.Pausar();
        menuanahdir.limpiar_pantalla();
        Menu(menuanahdir,AminoacidoList,lista);

    }
    bool opcIngresada = false;
    string FolioBusqueda;
    int folio;
    bool encontrado = true;

    menuanahdir.SystemOutPrintln("BUSCAR PROTEINAS\n\n");
    while(!opcIngresada || encontrado)
    {

        menuanahdir.SystemOutPrintln("Ingresa el folio de la proteina a buscar: ");
        getline(cin, FolioBusqueda);

        try
        {
            folio = stoi(FolioBusqueda);
            encontrado = lista.BusquedaBinariaBool(folio);
            opcIngresada=true;
            if(encontrado)
            {
                cout<<"\nProteina: \n"<<lista.BusquedaBinaria(folio)<<endl;

                encontrado = false;
            }
            else
            {
                menuanahdir.SystemOutPrintln("Elemento no encontrado saliendo al menu...");
            }
        }
        catch (invalid_argument& e)
        {
            menuanahdir.SystemOutPrintln("Ingresa un valor valido.\n");
        }
    }

}

void QuickSortProteina(Interfaz& menuanahdir,lista_d<Aminoacido>&Aminoacidolist,lista_d<Proteina>&lista)
{
    if(lista.vacia())
    {
        menuanahdir.limpiar_pantalla();
        menuanahdir.SystemOutPrintln("ORDERNAR LISTA DE PROTEINAS\n\n");
        menuanahdir.SystemOutPrintln("La lista de proteinas esta vacia. \n");
        menuanahdir.Pausar();
        menuanahdir.limpiar_pantalla();
        Menu(menuanahdir,Aminoacidolist,lista);
    }
    else
    {
        menuanahdir.limpiar_pantalla();
        menuanahdir.SystemOutPrintln("ORDERNAR LISTA DE PROTEINAS\n\n");
        lista.quicksortporFolio(lista.getHead());
        menuanahdir.SystemOutPrintln("Lista Ordenada correctamente!\n");
    }

}
