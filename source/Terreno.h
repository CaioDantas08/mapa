#ifndef TERRENO_H
#define TERRENO_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib> 
#include <ctime>
#include <fstream>
#include "Paleta.h"
#include "Imagem.h"

using altitude_type = double;
using value_type = int;

class Terreno{

    private:
    value_type altura{0};
    value_type largura{0};
    std::vector<altitude_type> altitudes;

    public:
    Terreno(value_type n = 0);
   ~Terreno();

    private:
    void diamond(value_type &x, value_type &y, value_type step, altitude_type &rugosidade);
    void square(value_type &x, value_type &y, value_type halfStep, altitude_type &rugosidade);

    public:
    void gerar_mapa(value_type n, double rugosidade);
    void salvar_matriz(const std::string &nome_arquivo);
    void ler_matriz(const std::string &nome_arquivo);

    altitude_type get_altitude(value_type i, value_type j);
    void set_altitude(value_type i, value_type j, altitude_type valor);

    value_type get_linhas();
    value_type get_colunas();

    Imagem criar_mapa_altitude(Paleta &p, double rugosidade);

};



#endif