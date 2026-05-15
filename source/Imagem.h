#ifndef IMAGEM_H
#define IMAGEM_H

#include <iostream>
#include <vector>
#include <string>
#include "Cor.h"
#include <fstream>
using value_type = int;

class Imagem{

    private:
    value_type altura{0};
    value_type largura{0};
    std::vector<Cor> pixels;

    public:
    Imagem();
    Imagem(value_type altura, value_type largura);
   ~Imagem();

    Cor consultar_pixel(value_type i, value_type j);
    void set_cor(value_type i, value_type j, Cor cor);
    void salvar_imagem(const std::string &nome_arquivo);

    value_type get_largura();
    value_type get_altura();
};

#endif