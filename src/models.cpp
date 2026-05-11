#include "../include/models.h"
#include <sstream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <iostream>

struct DadosComplexidade {
    std::string nome;
    double (*f_teorica)(int);
};

double f_n(int n) { return static_cast<double>(n); }
double f_n_log_n(int n) { return n * std::log2(n > 0 ? n : 1); }
double f_n_quadrado(int n) { return std::pow(n, 2); }

std::string complexidade() {
    std::map<int, double> lista_medias; 
    const int REPETICOES = 20;  

    for (int n = 10; n <= 1000000; n *= 10) {
        std::vector<long long> tempos;

        for (int r = 0; r < REPETICOES; r++) {
            auto start = std::chrono::high_resolution_clock::now();
            codigo_analisado(n);
            auto end = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            tempos.push_back(duration.count());
        }

        double soma = std::accumulate(tempos.begin(), tempos.end(), 0.0);
        lista_medias[n] = soma / REPETICOES;
    }

    std::vector<DadosComplexidade> modelos = {
        {"O(n)", f_n},
        {"O(n log n)", f_n_log_n},
        {"O(n^2)", f_n_quadrado}
    };

    std::string melhor_ajuste = "";
    double menor_cv = 1e18; 

    for (auto& modelo : modelos) {
        std::vector<double> razoes;
        for (auto const& [n, tempo] : lista_medias) {
            double valor_teorico = modelo.f_teorica(n);
            if (valor_teorico > 0) razoes.push_back(tempo / valor_teorico);
        }

        double soma_r = std::accumulate(razoes.begin(), razoes.end(), 0.0);
        double media_r = soma_r / razoes.size();
        double var = 0;
        for (double r : razoes) var += std::pow(r - media_r, 2);
        double desvio = std::sqrt(var / razoes.size());
        double cv = desvio / media_r;

        if (cv < menor_cv) {
            menor_cv = cv;
            melhor_ajuste = modelo.nome;
        }
    }

    std::ostringstream resultado;
    resultado << "--- Resultados da Analise Empirica ---\n";
    for (const auto& [n, tempo] : lista_medias) {
        resultado << "n = " << n << ": " << tempo << " ns (media)\n";
    }
    resultado << "\nComplexidade identificada: " << melhor_ajuste << "\n";
    
    return resultado.str();
}

void codigo_analisado(int n) {
    std::vector<int> vetor = {10, 50, 30, 70, 80, 20, 90, 40};
    int chave = 20;

    for (int i = 0; i < vetor.size(); ++i) {
        if (vetor[i] == chave) {
            break;
        }
    }
}