#include <iostream>
#include "Paleta.cpp"

using value_type = int;

int main(){

    Paleta paleta;
    paleta.ler_arquivo("../colors/colors.cor");
    
    return 0;
}