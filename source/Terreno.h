#ifndef TERRENO_H
#define TERRENO_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib> 
#include <ctime>
using value_type = int;

class Terreno{

    private:
    value_type altura{0};
    value_type largura{0};
    std::vector<value_type> altitudes;

    public:
    Terreno(value_type n = 0);
   ~Terreno();

    private:
    void diamond(value_type &x, value_type &y, value_type step, double &rugosidade);
    void square(value_type &x, value_type &y, value_type halfStep, double &rugosidade);

    public:
    void gerar_mapa(value_type n, double rugosidade);
    void salvar_matriz(const std::string &nome_arquivo);
    void ler_matriz(const std::string &nome_arquivo);

    value_type get_altitude(value_type i, value_type j);
    void set_altitude(value_type i, value_type j, value_type valor);

    value_type get_linhas();
    value_type get_colunas();

};



#endif