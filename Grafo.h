//
// Created by daniele lubrano on 24/02/2020.
//

#ifndef PROGETTO_ASD_PROBLEMA_2_GRAFO_H
#define PROGETTO_ASD_PROBLEMA_2_GRAFO_H

#include "Vertice.h"
#include "Edge.h"
#include "Lista.h"
#include <vector>
#include <iostream>

using namespace std;



class Grafo {
private:
    vector <Lista <Vertice> > lista_adiacenza;
    vector <Edge *> lista_archi;
    int partition( int p, int r);
    int c=0;

public:
    vector <Edge *>* get_archi();
    int get_numero_archi();
    void initialize(int size);
    Grafo();
    void insert_vertice(int index, int u, int w);
    void insert_edge(int u, int v ,int w);
    void quicksort(int p , int r);
    Edge* get_edge(int index);
    Vertice* get_vertice(int index);


};

//funzioni grafo dichiarate esternamente----------------------------------------


//funzione partition
int Grafo::partition( int p, int r){

    int q = r;
    int x = this->lista_archi.at(q)->get_w();
    int k=p-1;
    int i=0;
    for(i =p;i<r;i++){
        if(this->lista_archi.at(i)->get_w()<=x){
            k++;
            swap(this->lista_archi.at(i),this->lista_archi.at(k));
        }
    }
    swap(this->lista_archi.at(k+1),this->lista_archi.at(q));
    return k+1;

}

//funzione di quicksort usata per riorganizzare gli archi
void Grafo::quicksort(int p , int r){

    if(p<r){
        int q =partition(p,r);
        quicksort(p,q-1);
        quicksort(q+1,r);
    }

}

//inserimento archi in vettore archi
void Grafo::insert_edge(int u, int v ,int w){
    this->lista_archi.push_back(new Edge(u,v,w));
    //verificato inserisce correttamente tutti gli archi

}

//funzione di insert, inserisce una nuoca cella con vertice al suo interno nell'elelemnto
//lista nella posizione del vettore selezionata
void Grafo::insert_vertice(int index, int u, int w) {
    this->lista_adiacenza.at(index).insert_cella(new Vertice(u,w));
}

//costruttore per inizializzare i due vettori
Grafo::Grafo() {

}


//inizializza il grafo con tanti oggetti vuoti quanto size
void Grafo::initialize(int size) {
    for (int i = 0; i < size; i++) {
        lista_adiacenza.push_back(nullptr);
    }
}


//funzione per creare lista adiacenza
void crea_lista_adiacenza(Vertice *ptr_in, int vertice_in, int peso_in) {

    if (ptr_in->get_vertice() == -1) {
        //la lista di adj è vuota
        ptr_in->set_peso(peso_in);
        ptr_in->set_vertice(vertice_in);
        ptr_in->set_next(nullptr);

    } else {
        //altrimenti ptr a vertice esiste
        //itero ptr finchè trovo l'ultimo elemento
        while (ptr_in->get_next() != nullptr) {
            ptr_in = ptr_in->get_next();
        }
        //crea vertice successivo e assegna valori

        ptr_in->set_next(new Vertice);

        ptr_in = ptr_in->get_next();
        ptr_in->set_vertice(vertice_in);
        ptr_in->set_peso(peso_in);
        ptr_in->set_next(nullptr);
    }
}


vector <Edge *>* Grafo::get_archi() {
    return &lista_archi;
}

int Grafo::get_numero_archi() {
    return lista_archi.size();
}

//funzione per ritornare arco
Edge* Grafo::get_edge(int index){
    return this->lista_archi.at(index);

}

//funzione per ritornare vertice
Vertice* Grafo::get_vertice(int index) {
    return this->lista_adiacenza.at(index).get_head()->get_data();

}


#endif //PROGETTO_ASD_PROBLEMA_2_GRAFO_H
