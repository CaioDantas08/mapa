#include "Terreno.h"

    Terreno::Terreno(value_type n){
        if(n < 0) throw std::out_of_range("N deve ser um valor positivo maior que zero.");
        this->altura = pow(2,n) + 1;
        this->largura = pow(2,n) + 1;
        altitudes.resize(altura*largura);

        srand(time(nullptr));   
    }
    Terreno::~Terreno(){}

    altitude_type Terreno::get_altitude(value_type i, value_type j){
        return this->altitudes[this->largura*i + j];
    };
    void Terreno::set_altitude(value_type i, value_type j, altitude_type valor){
        altitudes[i * this->largura + j] = valor;
    };
    value_type Terreno::get_linhas(){
        return this->altura;
    };
    value_type Terreno::get_colunas(){
        return this->largura;
    };

    void Terreno::diamond(value_type &x, value_type &y, value_type step, double &rugosidade){
        value_type halfStep = step / 2;

        // Cantos
        value_type topLeft     = get_altitude(x, y);
        value_type topRight    = get_altitude(x + step, y);
        value_type bottomLeft  = get_altitude(x, y + step);
        value_type bottomRight = get_altitude(x + step, y + step);

        // Média
        double media = (
            topLeft +
            topRight +
            bottomLeft +
            bottomRight
        ) / 4.0;

        // Deslocamento aleatório
        double deslocamento =
            ((rand() / (double)RAND_MAX) * 2.0 - 1.0)
            * rugosidade;

        // Centro
        set_altitude(
            x + halfStep,
            y + halfStep,
            media + deslocamento
        );
    };
    void Terreno::square(value_type &x, value_type &y, value_type halfStep, double &rugosidade){
        double soma{0.0};
        value_type contador{0};

        // Cima
        if(x - halfStep >= 0) {
            soma += get_altitude(x - halfStep, y);
            contador++;
        }

        // Baixo
        if(x + halfStep < largura) {
            soma += get_altitude(x + halfStep, y);
            contador++;
        }

        // Esquerda
        if(y - halfStep >= 0) {
            soma += get_altitude(x, y - halfStep);
            contador++;
        }

        // Direita
        if(y + halfStep < altura) {
            soma += get_altitude(x, y + halfStep);
            contador++;
        }

        double media = soma / contador;

        double deslocamento =
            ((rand() / (double)RAND_MAX) * 2.0 - 1.0)
            * rugosidade;

        set_altitude(
            x,
            y,
            media + deslocamento
        );
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
            deslocamento *= 0.7;
            step /= 2;
        }

    };

    void Terreno::salvar_matriz(const std::string &nome_arquivo){
        std::ofstream arquivo(nome_arquivo);

        arquivo << this->altura << " " << this->largura << "\n";

        for (int i = 0; i < this->altura; i++) {
            for (int j = 0; j < this->largura; j++) {
                value_type altitude = get_altitude(i, j);
                arquivo << altitude << " ";
            }
            arquivo << "\n";
        }
        arquivo.close();
    };
    
    void Terreno::ler_matriz(const std::string &nome_arquivo){
        std::ifstream arquivo(nome_arquivo);

        if(!arquivo.is_open()){
            throw std::runtime_error("Erro ao abrir arquivo.");
        }

        arquivo >> this->altura >> this->largura;

        altitudes.resize(this->altura * this->largura);

        for(int i = 0; i < this->altura; i++){
            for(int j = 0; j < this->largura; j++){
                value_type valor;
                arquivo >> valor;

                set_altitude(i, j, valor);
            }
        }
        arquivo.close();
    };


    Imagem Terreno::criar_mapa_altitude(Paleta &p, double rugosidade) {
        Imagem img(this->altura, this->largura);
        value_type n = static_cast<value_type>(std::log2(this->altura - 1));
        gerar_mapa(n, rugosidade);

        double min_alt = get_altitude(0, 0);
        double max_alt = get_altitude(0, 0);

        for (int i = 0; i < this->altura; i++) {
            for (int j = 0; j < this->largura; j++) {
                double alt = get_altitude(i, j);
                min_alt = std::min(min_alt, alt);
                max_alt = std::max(max_alt, alt);
            }
        }

        double limite_sombra = 0.267;

        for (value_type i = 0; i < this->altura; i++) {
            for (value_type j = 0; j < this->largura; j++) {
                altitude_type alt = get_altitude(i, j);
                double normalizado = (alt - min_alt) / (max_alt - min_alt);
                normalizado*=0.83;
                Cor cor_pixel = p.consultar_cor(normalizado);


                bool sombra = false;
                double maior_alt_diagonal = alt;
                int k = 1;
                while (i >= k && j >= k) {
                    double alt_vizinho = get_altitude(i - k, j - k);
                    if (alt_vizinho > maior_alt_diagonal) {
                        maior_alt_diagonal = alt_vizinho;
                    }
                    k++;
                }
                if (maior_alt_diagonal > alt + (max_alt - min_alt) * limite_sombra) {
                    sombra = true;
                }

                if (sombra) {
                    double diff = maior_alt_diagonal - alt;
                    double fator = 1.0 - std::min(0.18, diff * 0.01);
                    cor_pixel.R = static_cast<int>(cor_pixel.R * fator);
                    cor_pixel.G = static_cast<int>(cor_pixel.G * fator);
                    cor_pixel.B = static_cast<int>(cor_pixel.B * fator);
                }

                img.set_cor(i, j, cor_pixel);
            }
        }
        return img;
    }