#ifndef IMAGEM_H
#define IMAGEM_H

#include <iostream>
#include <vector>
#include <string>
#include "Cor.h"
using value_type = int;

class Imagem{

    private:
    value_type largura{0};
    value_type altura{0};
    std::vector<Cor> pixels;

    public:
    Imagem();
    Imagem(value_type largura, value_type altura);
   ~Imagem();

    Cor consultar_pixel(value_type largura, value_type altura);
};

#endif