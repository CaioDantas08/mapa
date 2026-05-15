#include <iostream>
#include "Paleta.h"
#include "Imagem.h"
using value_type = int;

int main(){

    Paleta paleta;
    paleta.ler_arquivo("../colors/colors.cor");

    Imagem img(3,4);

    for (value_type i = 0; i < img.get_altura(); i++){
        for (value_type j = 0; j < img.get_largura(); j++){
            img.set_cor(i,j, {255,255,255});
            std::cout << img.consultar_pixel(i,j).R << " ";
            std::cout << img.consultar_pixel(i,j).G << " ";
            std::cout << img.consultar_pixel(i,j).B << "    ";
        }
        std::cout << " \n";
    }

    img.salvar_imagem("P3.ppm");

    return 0;
}