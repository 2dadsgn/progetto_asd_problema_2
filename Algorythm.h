//
// Created by daniele lubrano on 24/02/2020.
//

#ifndef PROGETTO_ASD_PROBLEMA_2_ALGORYTHM_H
#define PROGETTO_ASD_PROBLEMA_2_ALGORYTHM_H


#include <string>
#include <vector>
#include <iostream>
#include "Grafo.h"
#include "Lista.h"
#include "insieme_disgiunto.h"
#include <fstream>

using namespace std;

class Algorythm {
private:
    //file da cui leggere input
    string nome_file;
    int numero_isole;
    int numero_ponti;

    //struttura dati per conservare insiemi disgiunti
    Lista <Insieme> insiemi_disgiunti;

    //bridge to build
    vector <Edge*> BtB;
    int costo_totale_ricostruzione;

    // variabile  Grafo
    Grafo G;

    //funzione per leggere da file
    bool get_input();

    //kruskal
    void kruskal();

    //findset
    Cella <Insieme>* find_set(int u);

    //makeset
    Insieme* make_set(int key_in);
    //unione per rango
    void union_nodes(Cella <Insieme>* u, Cella <Insieme>* v);

public:

    //costruttore che esegue algoritmo
    Algorythm(string nome_file_in);

    //print dei ponti da ricostruire
    void risultato();



};



//-----------------------funzioni dichiarate esternamente--------------------



//costruttore
Algorythm::Algorythm(string nome_file_in){
    this->costo_totale_ricostruzione = 0;
    //dichiaro il nome del file
    try {
        this->nome_file ="../" + nome_file_in;
    }
     catch (...){
         cout<<"errore in setting file name";
     }

    //richiamo la funzione di cattura input
    try {
        this->get_input();
    }
    catch (...){
        cout<<"errore in ottenimento input";
    }


    //kruskal
    try {
        this->kruskal();
    }
    catch (...){
        cout<<"errore in kruskal";
    }


}

//funzione per leggere da file input e creare lista di adiacenza  e lista archi
bool Algorythm::get_input(){
    ifstream file;
    string linea;
    int a,b,u, v, w;

    file.open(this->nome_file);
    //controllo se il file esiste ed è aperto correttamente
    if(!file){
        return false;
    }
    //istruzioni per estrarre linee e inserirle in strutture dati apposite
    //ottengo dati prina linea
    getline(file,linea);
    a=linea.find(' ');
    this->numero_isole=stoi(linea.substr(0,a));
    this->numero_ponti=stoi(linea.substr(a));

    //inserisco vertici vuoti tanti quanti isole
    this->G.initialize(numero_isole);

    //passo alle linee successive
    while(getline(file,linea)){   //itera finchè ci sono linee di input
        //individuo gli spazi in modo tale da delimitare u,v,w
        a=linea.find(' ');
        b=linea.find_last_of(' ');

        //ottengo i valori
        u=stoi(linea.substr(0,a));
        v=stoi(linea.substr(a,b));
        w=stoi(linea.substr(b));

        //crea lista archi
        G.insert_edge(u,v,w);

        //passo alla funzione il ptr nella posizione u che corrisponde all'isola
        //numero u
        G.insert_vertice(u-1,v,w);


        //passo alla funzione il ptr nella posizione v che corrisponde all'isola
        //numero v
        G.insert_vertice(v-1,u,w);
    }
    file.close();
    return true;
}




//---------------------findset------------------------------
Cella <Insieme>* Algorythm::find_set(int u){
    Cella <Insieme>* cursore;
    Nodo <Insieme>* ptr_nodo;
    cursore = this->insiemi_disgiunti.get_head();

    while(cursore != nullptr){
        //ottengo il rappresentante chiamato head dell'insieme
        ptr_nodo = cursore->get_data()->get_head();
        while(ptr_nodo != nullptr){
            if(ptr_nodo->get_key() == u){
                //ritorna la cella in cui è memorizzato l'insieme
                return cursore;
            }
            ptr_nodo = ptr_nodo->get_next();
        }
        cursore = cursore->get_next();
    }
    return 0;
}





//----------makeset----------------------------------------

Insieme* Algorythm::make_set(int key_in){
    return new Insieme(key_in);
}




//unione per rango
void Algorythm::union_nodes(Cella <Insieme>* u, Cella <Insieme>* v){
    //ottengo gli insiemi disgiunti
    Insieme* s1 = u->get_data();
    Insieme* s2 = v->get_data();

    //setto i puntatori alle radici dei due disjoint set
    Nodo <Insieme>* ptr_1 = s1->get_head();
    Nodo <Insieme>* ptr_2 = s2->get_head();

    if(s1->get_rank()> s2->get_rank()){

        //allora unisci s2 ad s1, radice dell'albero unito sarà root di s1
        while(ptr_2 != nullptr){
            //tengo traccia dell'ultimo elemento con s1
            ptr_1 = ptr_2;

            ptr_2->set_insieme(s1);
            ptr_2 = ptr_2->get_next();
        }
        //tail di s1 diventa la root di s2
        s1->get_tail()->set_next(s2->get_head());
        s1->set_tail(ptr_1);
        ptr_1->set_next(nullptr);

        //elimino s2
        this->insiemi_disgiunti.delete_cella(s2);

        s1->set_rank(s1->get_rank()+s2->get_rank());
    }
    else{
        //allora unisci s1 ad s2, radice dell'albero unito sarà root di s2
        while(ptr_1 != nullptr){
            //tengo traccia dell'ultimo elemento con s1
            ptr_2 = ptr_1;
            ptr_1->set_insieme(s2);
            ptr_1 = ptr_1->get_next();
        }
        //tail di s1 diventa la root di s2
        s2->get_tail()->set_next(s1->get_head());
        s2->set_tail(ptr_2);
        ptr_2->set_next(nullptr);

        //aumento rank di s2
        s2->set_rank(s2->get_rank()+s1->get_rank());
        //elimino s1
        this->insiemi_disgiunti.delete_cella(s1);
    }


}


//algoritmo di kruskal oer calcolare albero ricoprente minimo
void Algorythm::kruskal(){
    int c=0;
    //cout<<c++<<endl;
    vector <Edge> insieme_archi_mst;
    vector <Edge>::iterator itr_archi;
    int costo_ricostruzione=0;

    //crea foresta di insiemi disgiunti
    Cella <Insieme>* cursore = this->insiemi_disgiunti.get_head();
    for (int i=1;i<=numero_isole;i++){
        this->insiemi_disgiunti.insert_cella(make_set(i));
    }

    //ordina archi in senso non decrescente
    G.quicksort(0,G.get_numero_archi()-1);

   //cout<<c++<<endl;


    for(int i=0;i<G.get_numero_archi();i++){

        //controlla se i due vertici dell'arco appartengono allo stesso insieme
        Cella <Insieme>* cella_s1 = find_set(G.get_edge(i)->get_u());
        Cella <Insieme>* cella_s2 = find_set(G.get_edge(i)->get_v());
        //cout<<cella_s1->get_data()->get_head()->get_key()<< " -- "<<cella_s2->get_data()->get_head()->get_key()<<endl;
        if(cella_s1->get_data()->get_head()->get_key() != cella_s2->get_data()->get_head()->get_key()){
            union_nodes(cella_s1, cella_s2);

            //cout<< "arco "<<archi.at(i).get_u()<<"-"<<archi.at(i).get_v()<<endl;

            //inserisco i ponti da ricostruire e calcolo costo minimo totale
            if(G.get_edge(i)->get_w()>0){
                costo_ricostruzione= costo_ricostruzione + G.get_edge(i)->get_w();
                //salvo gli archi da ricostruire
                this->BtB.push_back(G.get_edge(i));
                this->costo_totale_ricostruzione = this->costo_totale_ricostruzione + G.get_edge(i)->get_w();
            }
        }

    }
}


void Algorythm::risultato() {
    cout<<"I ponti da ricostruire sono i seguenti: "<< endl;
    for(auto x : this->BtB){
        cout<<x->get_u()<<" -> "<<x->get_v()<<" ( "<< x->get_w()<<" )"<<endl;
    }
    cout<<"Il costo totale dei lavori sarà: "<< endl<<this->costo_totale_ricostruzione;
}



#endif //PROGETTO_ASD_PROBLEMA_2_ALGORYTHM_H
