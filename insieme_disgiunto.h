//
// Created by daniele lubrano on 25/02/2020.
//

#ifndef PROGETTO_ASD_PROBLEMA_2_INSIEME_DISGIUNTO_H
#define PROGETTO_ASD_PROBLEMA_2_INSIEME_DISGIUNTO_H


//class nodo dell'insieme disgiunto
template <typename I>
class Nodo{
private:
    int key;
    I* insieme;
    Nodo* next;
public:
    int get_key();
    Nodo* get_next();
    //ritorna il ptr alla radice
    I* get_insieme();
    void set_key(int input);
    void set_next(Nodo* input);
    void set_insieme(I* input);
    Nodo();
};

//funzioni dichiarate esternamente
template <typename I>
int Nodo<I>::get_key(){
    return this->key;
}

template <typename I>
Nodo<I>* Nodo<I>::get_next(){
    return this->next;
}

//ritorna il ptr alla radice
template <typename I>
I* Nodo<I>::get_insieme(){
    return this->insieme;
}

template <typename I>
void Nodo<I>::set_key(int input){
    this->key = input;
}

template <typename I>
void Nodo<I>::set_next(Nodo* input){
    this->next = input;
}

template <typename I>
void Nodo<I>::set_insieme(I* input){
    this->insieme = input;
}

template <typename I>
Nodo<I>::Nodo(){
    this->set_next(nullptr);
    this->set_insieme(nullptr);
    this->set_key(-999);
}

//----------------------------------------------------------------

//classe INSIEME
class Insieme{
private:
    Nodo <Insieme>* head;
    Nodo <Insieme>* tail;
    int rank;
public:

    Nodo<Insieme>* get_head();
    //ritorna il ptr alla radice
    Nodo<Insieme>* get_tail();
    void set_head(Nodo<Insieme>* input);
    void set_tail(Nodo<Insieme>* input);
    void set_rank(int input);
    int get_rank();
    Insieme(int key_in);
    Insieme();
};

//funzioni dichiarate esternamente
Nodo<Insieme>* Insieme::get_head(){
    return this->head;
}
//ritorna il ptr alla radice
Nodo<Insieme>* Insieme::get_tail(){
    return this->tail;
}
void Insieme::set_head(Nodo<Insieme>* input){
    this->head = input;
}
void Insieme::set_tail(Nodo<Insieme>* input){
    this->tail = input;
}
void Insieme::set_rank(int input){
    this->rank = input;
}
int Insieme::get_rank(){
    return this->rank;
}
//costruttore overloading
Insieme::Insieme(int key_in){
    this->set_head(new Nodo <Insieme>);
    this->set_tail(this->get_head());
    head->set_key(key_in);
    head->set_insieme(this);
    this->set_rank(0);
}

//costruttore
Insieme::Insieme(){
    this->set_head(new Nodo <Insieme>);
    this->set_tail(this->get_head());
    head->set_insieme(this);
    this->set_rank(0);
}


#endif //PROGETTO_ASD_PROBLEMA_2_INSIEME_DISGIUNTO_H
