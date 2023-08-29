#include "../headers/funciones.h"
#include<iostream>
#include<vector>
using namespace std;

int main(){
	cout<<"inicio\n\n";
	funciones funcion;
	void (funciones::*lista[4])() = {
			&funciones::nominaEmpleados,
			&funciones::ventas,
			&funciones::reportes,
			&funciones::sueldos
		};
	funciones objetoFuncion;
	for(int i =0; i<4;i++){

	(objetoFuncion.*lista[i])();
	}
	
	return 0;
}
