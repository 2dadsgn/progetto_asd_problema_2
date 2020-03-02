#ifndef LINKEDLIST
#define LINKEDLIST


template<class T>
class Cella {
private:
    T *data;
    Cella *next;
    Cella *prev;

public:
    void set_data(T *datain);

    void set_next(Cella<T> *listain);

    void set_prev(Cella<T> *listain);

    T *get_data();

    Cella<T> *get_next();

    Cella<T> *get_prev();

    Cella(T *data_in, Cella<T> *previn);

};

template<class T>
void Cella<T>::set_data(T *datain) {
    this->data = datain;
}

template<class T>
void Cella<T>::set_next(Cella<T> *listain) {
    this->next = listain;
}

template<class T>
void Cella<T>::set_prev(Cella<T> *listain) {
    this->prev = listain;
}

template<class T>
T *Cella<T>::get_data() {
    return this->data;
}

template<class T>
Cella<T> *Cella<T>::get_next() {
    return this->next;
}

template<class T>
Cella<T> *Cella<T>::get_prev() {
    return this->prev;
}

template<class T>
Cella<T>::Cella(T *data_in, Cella<T> *previn) {
    this->set_data(data_in);
    this->set_next(nullptr);
    this->set_prev(previn);
}


//classe lista che gestisce le istanze di cella immagazzinate in essa---------------

template<class T>
class Lista {
private:
    Cella<T> *head;
    Cella<T> *tail;

public:
    Cella<T> *get_head();

    Cella<T> *get_tail();

    //funzione per cancellare un dato insieme
    int delete_cella(T* insieme);

    void insert_cella(T* insieme);

    Lista();

    //inizializzazione linked list con un cella che punta ad un insieme
    Lista(T *insieme);
};



//funzioni esterne alla classe
template<class T>
Cella<T>* Lista<T>::get_head() {
    return this->head;
}

template<class T>
Cella<T> *Lista<T>::get_tail() {
    return this->tail;
}

//funzione per cancellare un dato insieme
template<class T>
int Lista<T>::delete_cella(T* insieme) {
    Cella<T> *cursore = this->head;
    Cella<T> *next;
    Cella<T> *prev;
    while (cursore != nullptr) {
        if (cursore->get_data() == insieme) {
            if (cursore == this->head) {
                //elimino oggetto
                this->head = this->head->get_next();
                this->head->set_prev(nullptr);
                return 1;
            } else if (cursore->get_next() == nullptr) {
                //ultimo elemento
                this->tail = cursore->get_prev();
                this->tail->set_next(nullptr);
                return 1;
            } else {
                prev = cursore->get_prev();
                next = cursore->get_next();
                prev->set_next(next);
                next->set_prev(prev);
                return 1;
            }
        }
        cursore = cursore->get_next();

    }
    return 0;
};

//funzione per inserimento nella lista
template <class T>
void Lista<T>::insert_cella(T* insieme) {

    //se lista vuota inserisce in testa
    if (this->head == nullptr) {
        this->head = new Cella<T>(insieme, nullptr);
        this->tail = this->head;
    } else {
        //la vecchia tail diventa penultimo e next di vecchia tail diventa nuovo
        this->tail->set_next(new Cella<T>(insieme, this->tail));
        //nuovo diventa la nuova tail
        this->tail = this->tail->get_next();
    }

}

template<class T>
Lista<T>::Lista() {
    this->head = nullptr;
    this->tail = nullptr;
}

//inizializzazione linked list con un cella che punta ad un insieme
template<class T>
Lista<T>::Lista(T *insieme) {
    this->head = new Cella<T>(insieme, nullptr);
    this->tail = this->head;
}

#endif