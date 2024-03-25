
#include <iostream>
#include <fstream>
#include <string>
#include<cctype>
#include <iomanip>
#include<ctime>
#include<conio.h>
#include<string.h>
#include<cstdlib>
#include<vector>
#include <set>
#include<bits/stdc++.h>


#define ENTER 13
#define BACKSPACE 8


using namespace std;

void menu();
void GuardarDepartamentos();
bool buscarRegistro(int id, string nom);
void ConsultaDepartamentosporCod(int cod);
void GuardarActivos();
void ConsultaActivosPersona();
void ConsultaActivoDescripcion();
void ReporteGeneral();
bool LoginUsuario();



 //variables la parte de departamentos y codigos
int cod_dpto = 0;
string dsc_dpto;
int opc;
char op;
//variables para archivo activos
int cod_activo;
string dsc_activo;
string ubicacion;
double valor;
string asignado;

string personaBuscar;
string departamentoBuscar;

//variables para el login
string user= "";
int i = 0; //iterador para contar los espacios de la contrasena
int intentos = 0;





struct{

std::time_t t = std::time(nullptr);
std::tm* now = std::localtime(&t);
int dia = now->tm_mday;
int mes = (now->tm_mon +1 );
int anio = (now->tm_year+1900);

}fecha;




int main()
{


VOLVER:
    if(intentos == 3){
       cout<<"\nHa agotado la cantidad maxima de intentos para entrar al sistema, por favor ingrese de nuevo"<<endl;
       system("pause");
       exit(1);
    }else{


    if(LoginUsuario() == true){

     system("pause");

    } else{
    intentos++;
    goto VOLVER;

    }



    } // fin del else

Principal:
vuelve:
menu();


    do{



        switch(opc){

case 1:

     volver:
     cout<<"\n\t\tDigite A para el registro, B para la consulta o C para el menu principal."<<endl;
     cin>>op;

     switch(op){

 case 'A':

      GuardarDepartamentos();

    break;
 case 'B':

      cout<<"\n\tConsulta de Archivo.\nDigite el codigo a buscar"<<endl;
      cin>>cod_dpto;
      ConsultaDepartamentosporCod(cod_dpto);
      break;
 case 'C':
    goto Principal;

 default:
     cout<<"\tHa digitado una opcion invalida, vuelva a digitar la A o B"<<endl;
     goto volver;

    break;

     } // fin del segundo switch


    break;
case 2:
    vuelta:
    V:
cout<<"\n\tDigite A. para registrar, B. para consultar o C. para un reporte general o D para el menu principal."<<endl;
cin>>op;
switch(op){

case 'A':
    cout<<"\n\t\tRegistro"<<endl;
    GuardarActivos();

    break;
case 'B':

    cout<<"\nConsultar:\nDigite 1 para consultar por persona, 2 para consultar por descripcion"<<endl;
    cin>>opc;

    switch(opc){

case 1:

    ConsultaActivosPersona();
    goto V;

    break;
case 2:

    ConsultaActivoDescripcion();

    break;
default:
    cout<<"Ha digitado una opcion invalida, vuelva a digitar por favor"<<endl;
     system("pause");


    }
    break;

case 'C':
   //REPORTE GENERAL

ReporteGeneral();

    break;
case 'D':
    goto vuelve;

default:
    cout<<"Ha digitado una opcion invalida, vuelva a digitar por favor"<<endl;
     system("pause");
    goto vuelta;


}

    break;
case 3:

    cout<<"Ha finalizado el programa"<<endl;
    return 0; //finaliza el programa
    break;


default:
    cout<<"Usted ha digitado un numero fuera del rango, debe ser del 1 al 3"<<"\nVuelva a digitar la opcion"<<endl;
    cin>>opc;
    } // fin del switch

    }while(opc!=3);



    return 0;
}


void menu(){
cout<<setw(10)<<"\nMenu\t"<<endl;
cout<<" \n1.Departamentos."<<"\n\tA.Registrar"<<"\n\tB.Consultar"<<endl;
cout<<" \n2. Activos"<<"\n\tA.Registrar"<<"\n\tB.Consultar"<<"\n\t\tb.1 Por Persona"<<"\n\t\tb.2 Por Departamento"<<"\n\tC.Reporte General"<<endl;
cout<<" \n3.Salir"<<"\nDigite una opcion"<<endl;
cin>>opc;

}



bool LoginUsuario(){


user = "";
string  contrasena = "";
char caracter;
string p,k;



    ifstream UsuariosArchivos("acceso.txt", ios::in);

    if(!UsuariosArchivos){
         cout << "No se ha podido obtener el archivo acceso.txt" << endl;
            //Se sale del sistema
            exit(1);
    }else{


   cout<<"\n\t\t\tLogin de Usuario\n"<<endl;
   cout<<"\t\t\t-------------------\n"<<endl;
   cout<<"\n\t\tUsuario: "<<endl;
   cout<<"\t\t"; getline(cin,user);
   fflush(stdin);
   cout<<"\n\t\tClave: "<<endl;
    caracter = getch();

   cout<<"\n\t\t";while(caracter != ENTER){


   if(caracter != BACKSPACE){

    contrasena.push_back(caracter); // guarda cada caracter que se digite en el getch
    cout<<"*";
   }else{

       if(contrasena.length()>0){

        cout<<"\b \b";
        contrasena = contrasena.substr(0, contrasena.length() -1 ); //elimina lo escrito en contrasenha cada vez que borre

       }

   }

   caracter = getch();

   }


     while(UsuariosArchivos>>p>>k){


           if(p==user && k == contrasena){
           cout<<"\nUsuario encontrado\t\n\t\t\tBienvenido al sistema\n"<<endl;
           system("pause");
           return true;
           break;

           }else{
           cout<<"Usuario no encontrado, vuelva a digitarlo el usuario o usuario y clave no coinciden"<<endl;
           return false;
           system("pause");
           contrasena = " ";
           caracter='\0';


           }




   }
 } // fin del else
} // fin de la funcion


void GuardarDepartamentos()
{


  do
    {
    ofstream Departamentos("departamentos.txt", ios::app);

    if(!Departamentos){
        cout<<"No se ha podido abrir el archivo departamentos"<<endl;
        exit(1);
    }


    REGRESO:
    cout<<"\bDigite el codigo"<<endl;
    cin>>cod_dpto;
    fflush(stdin);
    cout<<"Digite el departamentos"<<endl;
    getline(cin,dsc_dpto);

 try
    {
    if(buscarRegistro(cod_dpto,dsc_dpto) == true)
        {

        throw "Ya se encuentra registrado el codigo o el nombre";

        }

         Departamentos << cod_dpto <<" "<< dsc_dpto<<endl;
    fflush(stdin);
       cout<<"Desea agregar un nuevo registro S/N"<<endl;
       cin>>op;




    }catch(const char * s)
    {


    cout<<"Identificacion o nombre ya esta registrado"<<endl;
    goto REGRESO;

    }




    }while(tolower(op) == 's');



}



bool buscarRegistro(int cod_dpto, string dsc_dpto){

int cod;
bool encontrado = false;

ifstream buscarArchivo("departamentos.txt", ios::in);

if (!buscarArchivo)//Valida si el archivo pudo abrirse, en caso contrario muestra un mensaje de advertencia
    {
        cout << "No existen registros, favor agregue un registro" << endl;
        return false;
    }else{
      while(!buscarArchivo.eof () && !encontrado){
            string nom="";

            buscarArchivo>>cod;
            buscarArchivo>>nom;

            if(cod == cod_dpto)//compara codigos
            {
                encontrado = true;
            }
            if (nom == dsc_dpto){
                encontrado = true;
            }
        }

        if(encontrado == true)
        {
           return true;
        }else{

        return false;
        }
        return false;


        buscarArchivo.close();


    }


}


void ConsultaDepartamentosporCod(int cod_dpto ){


ifstream buscarArchivo("departamentos.txt", ios::in);
int cod;
bool encontrado = false;


    if (!buscarArchivo)//Valida si el archivo pudo abrirse, en caso contrario muestra un mensaje de advertencia
    {
        cout << "No existen registros, favor agregue un registro" << endl;
    }else{
      while(!buscarArchivo.eof () && !encontrado){
            string nom="";

            buscarArchivo>>cod;
            buscarArchivo>>nom;

            if(cod == cod_dpto)//compara codigos
            {
                cout  << "Departamento" <<  endl;
                cout<< nom << endl;
                encontrado = true;

            }else{

            encontrado = false;
            }

        }
         if(!encontrado)
        {
            cout << "El departamento no existe" << endl;

        }

}
 buscarArchivo.close();

}



void GuardarActivos(){


do{
   ofstream Activos("activos.txt", ios::app);

      if (!Activos)//Valida si el archivo pudo abrirse, en caso contrario muestra un mensaje de advertencia
        {
            cout << "No se ha podido obtener el archivo activos.txt" << endl;
            //Se sale del sistema
            exit(1);
        }
        fflush(stdin);
        cout<<"Digite el codigo del activo"<<endl;
        cin>>cod_activo;
        fflush(stdin);
        cout<<"Digite la descripcion del activo"<<endl;
        getline(cin,dsc_activo);
        fflush(stdin);
        cout<<"Digite la ubicacion"<<endl;
        getline(cin,ubicacion);
        fflush(stdin);
        cout<<"Digite el valor"<<endl;
        cin>>valor;
        fflush(stdin);
        cout<<"Digite a quien esta asignado"<<endl;
        getline(cin,asignado);
        fflush(stdin);

        system("CLS");
        //guarda en el archivo los registros
        Activos<<cod_activo<<" "<<dsc_activo<<" "<<ubicacion<<" "<<fecha.dia<<"/"<<fecha.mes<<"/"<<fecha.anio<<" "<<valor<<" "<<asignado<<endl;
         fflush(stdin);

          do{
            cout << "Desea agregar un nuevo registro S/N" << endl;
            cin >> op;

         if((tolower(op) != 's') && (tolower(op) != 'n'))
            {
                cout << "Respuesta invalida" << endl;
                 system("pause");
                 system("CLS");
            }

            //Repite el proceso hasta que se agregue una respuesta valida
        }while(tolower(op) != 's' && tolower(op) != 'n');




}while(tolower(op) == 's');


}



void ConsultaActivosPersona(){




                fflush(stdin);
ifstream buscarPersonaActivo("activos.txt", ios::in);
bool encontrado = false;
string p="";
string k="";
string l="";
string m="";
string j="";
string s="";

     VOLVER:
    fflush(stdin);
    cout<<"Digite la persona a buscar:"<<endl;
    getline(cin,personaBuscar);

if (!buscarPersonaActivo)//Valida si el archivo pudo abrirse, en caso contrario muestra un mensaje de advertencia
    {
        cout << "No existen registros, favor agregue un registro" << endl;

    }else{

      while(buscarPersonaActivo>>p>>k>>l>>m>>j>>s){ // se usa getline para leer las cadenas con espacios vacios.

            if(s==personaBuscar)//compara personas
            {

                cout<< "Codigo" <<  setw(10) << "activo" << setw(13) << "Ubicacion" << setw(15)<< "Fecha "<<setw(14)<<"Valor" << setw(15) << "Asignado" <<endl;
                cout<<p<<setw(14)<<k<<setw(14)<<l<<setw(14)<<m<<setw(14)<<j<<setw(14)<<s<<endl;
                encontrado = true;
                break;

            }

            } // fin del while

        }
         if(!encontrado)
        {
            cout << "La persona  no existe" << endl;
        }

        buscarPersonaActivo.close();






}


void ConsultaActivoDescripcion(){

fflush(stdin);
ifstream buscarDescripcion("activos.txt", ios::in);
bool encontrado = false;

string description;
string p="";
string k="";
string l="";
string m="";
string j="";
string s="";


cout<<"Digite la descripcion"<<endl;
cin>>description;

if (!buscarDescripcion)//Valida si el archivo pudo abrirse, en caso contrario muestra un mensaje de advertencia
    {
        cout << "No existen registros, favor agregue un registro" << endl;

    }else{

      while(buscarDescripcion>>p>>k>>l>>m>>j>>s){ // se usa getline para leer las cadenas con espacios vacios.


                 if(k==description){
                cout<<"Codigo"<<setw(15)<<"activo"<<setw(15)<< "Ubicacion"<< setw(15)<<"Fecha"<<setw(15)<<"Valor"<<setw(15)<< "Asignado" <<endl;
                cout<<p<<setw(17)<<k<<setw(17)<<l<<setw(16)<<m<<setw(17)<<j<<setw(17)<<s<<endl;
                encontrado = true;
                break;


                 }



            } // fin del while

        }
         if(!encontrado)
        {
            cout << "La descripcion  no existe" << endl;
        }

        buscarDescripcion.close();


}


void ReporteGeneral(){



ifstream ArchivoOrdenado("activos.txt", ios::in);


multiset<string> palabras; //contenedor que ordena el archivo de menor a mayor


if(ifstream ArchivoOrdenado{"activos.txt"})
    {

    string linea;
    while(getline(ArchivoOrdenado,linea)) // guarda el archivo en la string linea
        palabras.insert(linea); // inserta la linea en el contenedor multiset para ordenarlo

    }else
    {
    exit(EXIT_FAILURE);

    }
    cout<<"\n\t\t\tARCHIVO DE ACTIVOS"<<endl;
    cout<< "Codigo" <<  setw(10) << "activo" << setw(13) << "Ubicacion" << setw(15)<< "Fecha "<<setw(14)<<"Valor" << setw(15) << "Asignado" <<endl;

    for(const auto &palabra : palabras){
       cout<< setw(10) <<palabra <<setw(10) <<endl;
    }


}














