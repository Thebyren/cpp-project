# proyecto en c++

## es un proyecto de administracion interna escrito en c++ utilizando ncurses y sus librerias adjuntas

para facilidad de los datos, utilizamos sqlite para administrar los datos de usuarios, asi como los registros de informacion general como las localizaciones, gestiones de los usuarios y todo lo demas.

puede descargar el ejecutable [aqui](./main.cpp)

y puede descargar el codigo fuente [aqui](./main.cpp)

```mermaid
graph TD;
    inicio-->menu;//inicia
    menu-->seleccion;
    seleccion-->opt1;
    opt1-->menu-opt1;
    menu-opt1-->seleccion-opt1;
    seleccion-->opt2;
    opt2-->menu-opt2;
    seleccion-opt2-->database;
    menu-opt2-->seleccion-opt2;
    seleccion-opt1-->database;
    seleccion-->opt3;
    opt3-->menu-opt3;
    menu-opt3-->seleccion-opt3-1;
    menu-opt3-->seleccion-opt3-2;
    seleccion-opt3-1-->database;
    seleccion-opt3-2-->datastructure;
```
