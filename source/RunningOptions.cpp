#include "RunningOptions.h"

void RunningOptions(){

    std::string nome_paleta;
    std::cout << "Digite o nome do arquivo da paleta de cores a ser usada: \n";
    std::getline(std::cin, nome_paleta);

    Paleta P;
    P.ler_arquivo("../colors/" + nome_paleta);

    value_type n{0};
    std::cout << "Digite um valor N para criarmos as dimensões da imagem: \n";
    std::cin >>n;
    std::cin.ignore();
    Terreno T(n);

    std::string nome_arquivo;
    std::cout << "Para finalizar, digite o nome do arquivo a ser salvo em ppm: \n";
    std::getline(std::cin, nome_arquivo);

    Imagem img;
    img = T.criar_mapa_altitude(P, 10000.0);
    img.salvar_imagem(nome_arquivo);
};