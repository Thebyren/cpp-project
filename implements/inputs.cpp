#include "inputs.h"
#include "managerDB.h"
void ingreso(){

    SQLiteManager dbManager("ruta_a_tu_base_de_datos.db");

    dataUser nuevoUsuario;
    nuevoUsuario.nombre = "John";
    nuevoUsuario.apellido = "Doe";
    nuevoUsuario.fechaNacimiento = "1990-01-01";
    nuevoUsuario.edad = 33;
    nuevoUsuario.antiguedadEmpresa = 5;
    nuevoUsuario.correo = "john@example.com";
    nuevoUsuario.codigoVenta = 123;
    nuevoUsuario.idPuesto = 2;  // ID correspondiente al puesto en la tabla de puestos

    std::string consulta = dbManager.newUser(nuevoUsuario);
    dbManager.querryDataBase(consulta);

}