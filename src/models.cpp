#include "../include/models.h"
#include <sstream>

std::string complexidade(){
    std::map<int, int> lista;

    for(int i = 1; i <= 1000000000; i *= 10){
        auto start = std::chrono::high_resolution_clock::now();

        codigo_analisado(i);

        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

        int tempo_int = static_cast<int>(duration.count());

        lista[i] = tempo_int;
    }

    std::ostringstream resultado;
    for (const auto& [n, tempo] : lista) {
        resultado << "n = " << n << ": " << tempo << " ms\n";
    }
    return resultado.str();
}

void codigo_analisado(int n){
    int a = 0;
    for(int i = 0; i < n; i++){
        a++;
    }
}