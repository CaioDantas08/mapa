#ifndef PALETA_H
#define PALETA_H

#include <iostream>
#include "Cor.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using value_type = int;

class Paleta{

    private:
    value_type quantidade{0};
    std::vector<Cor> cores;
    std::vector<double> valores;

    public:
    Paleta();
    Paleta(value_type quantidade, std::vector<Cor> c, std::vector<double> v);
 
    void parse_line(std::string linha);
    void ler_arquivo(const std::string &nome);
    Cor consultar_cor(double valor);

    value_type get_quantidade();
    std::vector<Cor> get_cores();
    std::vector<double> get_valores();
    
    void set_quantidade(value_type quantidade);
    void set_cores(std::vector<Cor> cores);
    void set_valores(std::vector<double> valores);

};

#endif