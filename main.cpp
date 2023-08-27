#include "headers/header.h"
#include <string>
#include <form.h>
#include "headers/managerDB.h"

using namespace std;
int main() {
    SQLiteManager manager("base.db");
    
    //manager.querryDataBase(" CREATE TABLE usuarios (id INTEGER PRIMARY KEY AUTOINCREMENT,nombres TEXT NOT NULL,apellidos TEXT NOT NULL,puesto TEXT NOT NULL,telefonos INTEGER NOT NULL,    fechaNacimiento DATE NOT NULL,    edad INTEGER NOT NULL,    antiguedadEmpresa INTEGER NOT NULL,    correoElectronico TEXT NOT NULL,    codigoVenta INTEGER,    FOREIGN KEY(codigoVenta) REFERENCES ventas(idVendedor),    FOREIGN KEY(puesto) REFERENCES puestos(nombre))");
    cout<<"nombres, apellidos, puesto, telefonos, fechanacimiento, edad, antiguedadEmpresa, correo, codigo venta, puesto, ";

    dataUser nuevoRegistro;

    cout<<"ingrese los datos del usuario\n";
    cout<<"ingrese nombre: ";
    cin>>nuevoRegistro.nombre;
    cout<<"ingrese apellido: ";
    cin>>nuevoRegistro.apellido;
    cout<<"ingrese edad: ";
    cin>>nuevoRegistro.edad;
    cout<<"ingrese correo: ";
    cin>>nuevoRegistro.correo;
    cout<<"ingrese puesto: ";
    cin>>nuevoRegistro.idPuesto;
    cout<<"ingrese ubicacion: ";
    cin>>nuevoRegistro.ubicacion;
    cout<<"ingrese antiguedad en la empresa: ";
    cin>>nuevoRegistro.antiguedadEmpresa;
    cout<<"ingrese codigoVenta: ";
    cin>>nuevoRegistro.codigoVenta;
    

    
    manager.querryDataBase(manager.newUser(nuevoRegistro));
    
    vector <dataUser> registro = manager.obtenerRegistrosUsuarios();

    cout<<"\n\ndatos en el registro\n\n";
    for(const dataUser& usuario:registro){
        cout<<"nombre "<<usuario.nombre<<endl;
        cout<<"apellido "<<usuario.apellido<<endl;
        cout<<"correo "<<usuario.correo<<endl;
        cout<<"puesto "<<usuario.idPuesto<<endl;
        cout<<"edad "<<usuario.edad<<endl;
    }
    return 0;
}