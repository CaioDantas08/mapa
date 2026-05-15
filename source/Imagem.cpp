#include "Imagem.h"

    Imagem::Imagem(){
    }
    Imagem::Imagem(value_type altura, value_type largura){
        this->altura = altura;
        this->largura = largura;
        pixels.resize(altura*largura);
    }
    Imagem::~Imagem(){

    }   
    Cor Imagem::consultar_pixel(value_type i, value_type j){
        return pixels[this->largura*i + j];
    }
    void Imagem::set_cor(value_type i, value_type j, Cor cor){
        if(i >= altura || j >= largura){
            throw std::out_of_range("Pixel fora da imagem");
        }
        this->pixels[this->largura*i + j] = cor;
    };
    void Imagem::salvar_imagem(const std::string &nome_arquivo){
        std::ofstream arquivo(nome_arquivo + ".ppm");

        arquivo << "P3\n";
        arquivo << this->altura << " " << this->largura << "\n";
        arquivo << "255\n";

        for (int i = 0; i < altura; i++) {
            for (int j = 0; j < largura; j++) {
                Cor c = consultar_pixel(i, j);

                arquivo << c.R << " "
                        << c.G << " "
                        << c.B << " ";
            }
            arquivo << "\n";
        }
        arquivo.close();
    };
    value_type Imagem::get_largura(){
        return this->largura;
    };
    value_type Imagem::get_altura(){
        return this->altura;
    };