#include "Terreno.h"

    Terreno::Terreno(value_type n = 0){
        if(n < 0) throw std::out_of_range("N deve ser um valor positivo maior que zero.");
        this->altura = pow(2,n) + 1;
        this->largura = pow(2,n) + 1;
        altitudes.resize(altura*largura);

        srand(time(nullptr));   
    }
    Terreno::~Terreno(){}

    value_type Terreno::get_altitude(value_type i, value_type j){
        return this->altitudes[this->largura*i + j];
    };
    void Terreno::set_altitude(value_type i, value_type j, value_type valor){
        altitudes[i * this->largura + j] = valor;
    };
    value_type Terreno::get_linhas(){
        return this->altura;
    };
    value_type Terreno::get_colunas(){
        return this->largura;
    };

    void Terreno::diamond(value_type &x, value_type &y, value_type step, double &rugosidade){

    };
    void Terreno::square(value_type &x, value_type &y, value_type halfStep, double &rugosidade){

    };
    void Terreno::gerar_mapa(value_type n, double rugosidade){
        if(n < 0) throw std::out_of_range("N deve ser um valor positivo maior que zero.");
        this->altura = pow(2,n) + 1;
        this->largura = pow(2,n) + 1;
        altitudes.resize(altura*largura);

        //Iniciando os cantos
        set_altitude(0, 0, 0);
        set_altitude(0, largura-1, 0);
        set_altitude(altura-1, 0, 0);
        set_altitude(altura-1, largura-1, 0);

        value_type step = largura - 1;
        double deslocamento = rugosidade;
    
        while(step > 1) {
            value_type halfStep = step / 2;

            // Diamond step
            for(value_type x = 0; x < largura-1; x += step) {
                for(value_type y = 0; y < altura-1; y += step) {
                    diamond(x, y, step, deslocamento);
                }
            }
            // Square step
            for(value_type x = 0; x < largura; x += halfStep) {
                for(value_type y = (x + halfStep) % step; y < altura; y += step) {
                    square(x, y, halfStep, deslocamento);
                }
            }

            // Reduzindo a rugosidade
            deslocamento /= 2.0;
            step /= 2;
        }

    };