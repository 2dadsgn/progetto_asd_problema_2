//
// Created by daniele lubrano on 26/02/2020.
//

#ifndef PROGETTO_ASD_PROBLEMA_2_EDGE_H
#define PROGETTO_ASD_PROBLEMA_2_EDGE_H

//classe arco facente parte del Grafo E appartente a G
class Edge {
private:
    int u;
    int v;
    int w;
public:

    //imposta i due vertici e il peso
    void set_edge(int uin, int vin, int win);

    int get_v();

    int get_u() ;

    int get_w() ;

    //costruttore
    Edge();

    //ovreloading costruttore
    Edge(int uin, int vin, int win) ;
};



//funzioni dichiarate esternamente

//imposta i due vertici e il peso
void Edge::set_edge(int uin, int vin, int win) {
    this->u = uin;
    this->v = vin;
    this->w = win;
}

//ritorna valore v
int Edge::get_v() {
    return this->v;
}

//ritorna valore u
int Edge::get_u() {
    return this->u;
}

//ritorna valore w
int Edge::get_w() {
    return this->w;
}

Edge::Edge() {
    v = -1;
    u = -1;
    w = 2000;
}

Edge::Edge(int uin, int vin, int win) {
    this->v = vin;
    this->u = uin;
    this->w = win;
}

#endif //PROGETTO_ASD_PROBLEMA_2_EDGE_H
