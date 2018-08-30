#ifndef MROWKI_H
#define MROWKI_H
using namespace std;

//! Definicja struktury przechowującej ścieżki mrówek

#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>

class Tmrowka {
public:
    int Wm;                         //!< Maksymalna liczba węzłów w trasie grafu
    int *trasa=NULL;                //!< Tablica z numerami pokonanych węzłów
    int K;                          //!< etap podróży, 0 oznacza punkt startowy (wpisany w 1. komórce tabeli trasa)
    double L;                       //!< dł. trasy
    int gdzie();                    //!< podaje aktualne położenie
    bool czy_bylas_w(int s);        //!< zwraca true, jeśli mrówka już była w węźle s
    void idz_na_start();            //!< wymazuje mrowce wspomnienia i przenosi do mrowiska - start wpisany konstruktorem
    int idz_do(int j, double d);    //!< mrówka pokonuje kolejny odcinek trasy, o dł. d, z obecnej poz. do j
    void zapisz(string fn);         //!< zapis listy wierzchołków pokonanych przez mrówkę
    Tmrowka(int Wm, int start);
    ~Tmrowka();
    };

#endif // MROWKI_H
