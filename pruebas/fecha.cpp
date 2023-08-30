#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <ctime>
#endif

int ObtenerAnioActual() {
#ifdef _WIN32
    // Código para Windows
    SYSTEMTIME st;
    GetLocalTime(&st);

    return st.wYear;
#else
    // Código para Unix (Linux/macOS)
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* tiempoLocal = std::localtime(&tiempoActual);

    return tiempoLocal->tm_year + 1900;
#endif
}

int main() {
    int anioActual = ObtenerAnioActual();

    std::cout << "Año actual: " << anioActual << std::endl;

    return 0;
}
