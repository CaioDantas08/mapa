#include "Paleta.h"

    Paleta::Paleta(){
    }
    Paleta::Paleta(value_type quantidade, std::vector<Cor> c, std::vector<double> v){
        this->quantidade = quantidade;
        this->cores = c;
        this->valores = v;

        //this->cores.resize(100);
        //this->valores.resize(100);
    }

    void Paleta::parse_line(std::string linha){
        std::stringstream ss(linha);

        double valor{0};
        value_type R{0}, G{0}, B{0};

        ss >> valor >> R >> G >> B;
        valores.push_back(valor);

        Cor c;
        c.R = R;
        c.G = G;
        c.B = B;
        cores.push_back(c);
    }
    void Paleta::ler_arquivo(const std::string &nome){
        std::ifstream arquivo(nome);
        if(arquivo.is_open()){
            std::string linha;
            std::getline(arquivo, linha);
            try{
                quantidade = std::stoi(linha);
            }catch(...){
                std::cerr << "Erro: quantidade de cores não lida." << std::endl;
            }
            while(getline(arquivo, linha)){
                parse_line(linha);
            }
            arquivo.close();    
        }else{
            std::cerr << "Erro: arquivo não lido.";
        }
    }

    Cor Paleta::consultar_cor(double valor){
        //Implementar upper bound ou lower bound depois
        value_type indice{0};
        for (value_type i = 0; i < valores.size(); i++){
           if(valores[i] > valor){indice = i - 1; break;}
           else if(i == valores.size() - 1 && valor >= valores[i]){
            indice = i;
           }
        }
        return cores[indice];
    }

    value_type Paleta::get_quantidade(){
        return quantidade;
    }   
    std::vector<Cor> Paleta::get_cores(){
        return cores;
    }
    std::vector<double> Paleta::get_valores(){
        return valores;
    }
    void Paleta::set_quantidade(value_type quantidade){
        this->quantidade = quantidade;
    }
    void Paleta::set_cores(std::vector<Cor> cores){
        this->cores = cores;
    }
    void Paleta::set_valores(std::vector<double> valores){
        this->valores = valores;
    }