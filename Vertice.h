//
// Created by daniele lubrano on 26/02/2020.
//

#ifndef PROGETTO_ASD_PROBLEMA_2_VERTICE_H
#define PROGETTO_ASD_PROBLEMA_2_VERTICE_H



//classe vertice V appartenente alla lista di adj grafo G
class Vertice {
private:
    int vertice;
    int peso;
    Vertice *next;
public:
    int get_vertice() {
        return this->vertice;
    }

    int get_peso() {
        return this->peso;
    }

    Vertice *get_next() {
        return this->next;
    }

    void set_vertice(int input) {
        this->vertice = input;
    }

    void set_peso(int input) {
        this->peso = input;
    }

    void set_next(Vertice *input) {
        this->next = input;
    }

    Vertice() {
        vertice = -1;
    }
    Vertice(int u, int w) {
        this->vertice = u;
        this->peso = w;
    }

};

#endif //PROGETTO_ASD_PROBLEMA_2_VERTICE_H
