#include "headers/header.h"
#include <string>
#include <form.h>
#include "headers/managerDB.h"

using namespace std;
int main() {
    SQLiteManager manager("nuevaBase.db");
    manager.querryDataBase("CREATE TABLE 'hola'('valor' integer)");
    return 0;
}