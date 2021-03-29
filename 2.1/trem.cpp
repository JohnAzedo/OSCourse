#include "trem.h"
#include <QtCore>
#include<QDebug>

// Memória compartilhada
int local_1 = 0;
int local_2 = 0;
int local_3 = 0;
int local_4 = 1;
int local_5 = 0;
int local_6 = 1;
int local_7 = 0;


//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = 100;
}

void Trem::setVelocidade(int velocidade){
    int valor = 100 - velocidade;
    if(valor==100){
        this->terminate();
    }else{
        this->start();
    }
    this->velocidade = valor;
}


// Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 30 && x <330){

                if(x == 310){
                    // T1 está fora da zona de convergencia
                    // e quer verificar se local 1 ou local 3 estão ocupados
                    if(local_1 == 0 || local_3 == 0){
                       break;
                    }else{ // Caso não, acesse a região 1
                        start();
                    }
                    local_1--; // Avise que o local 1 tá ocupado
                }
                x+=10;

            }
            else if (x == 330 && y < 150){
                if(y == 130){
                    // T1 está dentro do local 1 e
                    //quer verificar se o local 3 está ocupada
                    if(local_3 == 0){
                        break;
                    }else{
                        start(); // Caso não, acesse a região 3
                    }
                    local_3--; // Avise que a o local 1 está ocupado
                }
                y+=10;
             }
            else if (x > 60 && y == 150){
                if(x == 310){
                    local_1++; // Avise que local 1 está desocupado
                }

                if(x == 170){
                    local_3++; // Avise que local 3 está desocupado
                }
                x-=10;
            }
            else{
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 30 && x <600){
                if(x == 350){
                    local_1++; // Avise que local 1 está desocupado
                }

                // T2 está fora da zona de convergencia
                // e quer verificar se local 1 ou local 3 ou local 5 ou local 2 estão ocupados
                if(x == 580){
                    if(local_2 == 0 || local_5 == 0 || local_4 == 0 || local_1 == 0){
                        break;
                    }else{
                        start(); // Caso não, acesse a região 2
                    }
                    local_2--; // Avise que o local 2 está ocupado
                }
                x+=10;
            }
            else if (x == 600 && y < 150){
                // T2 está no local 2
                // e quer verificar se o local 5 ou o local 4 ou o local 1 estão ocupados
                if(y ==130){
                    if(local_5==0 || local_4 == 0 || local_1 == 0){
                        break;
                    }else{
                        start(); // Caso não, acesse a região 5
                    }
                    local_5--;// Avise que o local 5 está ocupado
                }

                y+=10;
            }
            else if (x > 330 && y == 150){
                // T2 está no local 4
                // e quer verificar se o local 1 está ocupado
                if(x == 350){
                    if(local_1 == 0){
                        break;
                    }else{
                        start(); // Caso não, acesse a região 1
                    }
                    local_1--; // Avise que o local 1 está ocupado
                }

                // T2 está no local 5
                // e quer verificar se local 1 ou local 4 estão ocupados
                if(x == 480){
                    if(local_4 == 0 || local_1 == 0){
                        break;
                    }else{
                        start(); // Caso não, acesse a região 4
                    }
                    local_4--; // Avise que o local 4 está ocupado
                }

                if(x == 440){
                    local_5++; //Avise que o local 5 está desocupado
                }

                if(x == 580){
                    local_2++; // Avise que o local 2 está desocupado
                }
                x-=10;
            }
            else{
                if(y == 130){
                    local_4++; // Avise que o local 4 está desocupado
                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 30 && x <870){
                if(x == 620){
                    local_2++; // Avise que o local 2 está despcupado
                }
                x+=10;
            }
            else if (x == 870 && y < 150)
                y+=10;
            else if (x > 600 && y == 150){
                // T3 está no local 6
                // e quer verificar se o local 2 está ocupado
                if(x == 620){
                    if(local_2 == 0){
                        break;
                    }else{
                        start(); // Caso não, acesse a região 2
                    }
                    local_2--; // Avise que o local 2 está ocupado
                }

                // T3 está fora da zona de convergência
                // e quer verificar se o local 6 ou local 2 estão ocupado
                if(x == 750){
                    if(local_6 == 0 || local_2 == 0){
                        break;
                    }else{
                        start(); // Caso não, acesse a região 6
                    }
                    local_6--; // Avise que a região 6 está ocupada
                }
                x-=10;
            }
            else{
                if(y==130){
                    local_6++; // Avise que o local_6 está desocupado
                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 150 && x <460){
                if(x == 350){
                    local_3++; // Avise que o local 3 está desocupado
                }

                // T4 está no local 3
                // e que verificar se o local 4 ou local 7 está ocupado
                if(x == 310){
                    if(local_4 == 0 || local_7 == 0){
                        break;
                    }else{
                        start(); // Caso não, acesse a região 4
                    }
                    local_4--; // Avise que o local 4 está desocupado
                }

                // T4 está no local 4
                // e quer verificar se o local 7 está ocupado
                if(x == 440){
                    if(local_7 == 0){
                        break;
                    }else{
                        start(); // Caso não, acesse a região 7
                    }
                    local_7--; // Avise que o local 7 está desocupado
                }

                x+=10;

            }
            else if (x == 460 && y < 270){
                if(y==170){
                    local_4++; // Avise que o local 4 está desocupado
                }

                y+=10;
            }
            else if (x > 190 && y == 270){
                if(x == 440){
                    local_7++; // Avise que o local 7 está desocupado
                }
                x-=10;
            }
            else {
                // T4 está fora da zona de convergencia
                // e quer verificar se local 3 ou local 4 ou local 7 estão ocupados
                if(y==170){
                    if(local_3 == 0 || local_4 == 0 || local_7 == 0){
                        break;
                    }else{
                        start(); // Caso não, acesse a região 3
                    }
                    local_3--; // Avise que o local 3 está ocupado
                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 150 && x <730){
                if(x == 480){
                    local_7++; // Avise que o local 7 está desocupado
                }

                if(x==620){
                    local_5++; // Avise que o local 5 está despocupado
                }

                // T5 está no local 5
                // e quer verificar se local 6 está ocupado
                if(x == 580){
                    if(local_6 == 0){
                        break;
                    }else{
                        start(); // Caso não, acesse a região 6
                    }
                    local_6--; // Avise que o local 6 está desocupado
                }
                x+=10;
            }
            else if (x == 730 && y < 270){
                if(y==170){
                    local_6++; // Avise que o local_6 está desocupado
                }
                y+=10;
            }
            else if (x > 460 && y == 270){
                // T5 está fora da zona de convergencia
                // e quer verificar se local 7 ou local 5 ou local 6 estão ocupados
                if(x == 480){
                    if(local_7==0 || local_5 == 0 || local_6 == 0){
                        break;
                    }else{
                        start(); // Caso não, acesse a região 7
                    }
                    local_7--; // Avise que o local 7 está ocupado
                }
                x-=10;
            }
            else{
                // T5 está no local 7
                // e quer verificar se local 5 ou o local_6 está ocupado
                if(y == 170){
                    if(local_5 == 0 || local_6 == 0){
                        break;
                    }else{
                        start(); // Caso não, acesse a região
                    }
                    local_5--; // Avise que o local 5 está ocupado
                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}
