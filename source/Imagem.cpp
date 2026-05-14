#include "Imagem.h"

    Imagem::Imagem(){
    }
    Imagem::Imagem(value_type largura, value_type altura){
        this->largura = largura;
        this->altura = altura;
        pixels.resize(largura*altura);
    }
    Imagem::~Imagem(){

    }

    Cor Imagem::consultar_pixel(value_type largura, value_type altura){
        
    }