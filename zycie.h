#ifndef ZYCIE_H
#define ZYCIE_H

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "mrowki.h"
#include "graf.h"
#include "pomocnicze.h"

//! Definicja klasy głównej, zawierającej graf, populację mrówek i mechanikę algorytmu mrówkowego

class Tzycie : public Tgraf {

private:
    Tmrowka **mr=NULL;                      //!< Mrowiskowy spis powszechny
    int M;                                  //!< Liczba mrówek
    int start,meta;

    double P(int i, int j);                 //!< prawdopodobieństwo skoku i -> j = f(d,f)
    double SP(int i);                       //!< suma prawdopodobieństw wszystkich skoków z i == norma prawdopodobieństwa skoku z i
    double SPm(Tmrowka *m, int i);          //!< poprawka do normy ze wzgl. na odwiedzone przez m-tą  mrówkę węzły

    double Sf(int i, int j);                //!< suma feromonu w węzłach wych. z i

    int losuj_skok(Tmrowka *m);             //!< losuje węzeł, do którego skoczy dana mrówka

    void idz(Tmrowka *m);                   //!< Szukaj! - 1 krok.
    void idzcie();                          //!< Każda mrówka robi krok

public:
    int t;                                  //!<,,Czas"
    double A;                               //!< wykładnik odpowiadający feromonowi
    double B;                               //!< wykładnik odpowiadający odległości
    double R;                               //!< współczynnik odparowania

    Tzycie(int W, int M, int K_sr, int K_max, int start,int meta);  //!< Graf z W wierzchołkami, K_sr*W wierzch., K_max wierzch wych. z 1. węzła i M mrówek
    Tzycie(int W, int M, int start,int meta);                       //!< Pusty graf z W wierzchołkami i M mrówek
    Tzycie(string fn, int M, int start,int meta);                   //!< Graf wczytany z pliku o nazwie w fn i M mrówek
    void zamrowianie(int M);                //!< Stwirzenie populacji M mrówek
    ~Tzycie();

    void odparuj();                         //!< Proporcionalne do R zmniejszenie stężenia feromonu na każdym połączeniu

    int zyjcie(double kontrast_min=0.2,int dt=1);                   //!< Start symulacji na T kroków, zwraca true jeśli znaleziono trasę, co spr. raz w ostatnim kroku
    //void zyjcie_podzialka(int T=1);         //!< Dodatkowo wyświetla pasek postępu, a poza tym j.w.
    int znajdzcie(double kontrast_min=0.2, int dt=0, int T=10000000);    //!< Start symulacji do momentu znalezienia trasy o min kontr lub przekr. czasu, sprawdzanie warunku co dt
    int znajdzcie_zapiszcie(string fn,double kontrast_min=0.2, int dt=0, int T=10000000);//!< j.w. z zapisywaniem co dt. kroków do pliku o nazwie fn



    void par();                             //!< Wyświetla parametry symulacji

    Tmrowka *m0=NULL;                       //!< mrówka testowa do szukania trasy
    double trasa();                         //!< szuka trasy mrówką m0 i zwraca max z (1-max_f(i)/S(i))
    void zaznacz_trase(Tmrowka *m=NULL);    //!< zaznaczanie trasy pojedynczej mrówki na trasie feromonem, zerowany jest dotychczasowy jego stan
    void zapisz_trase(string fn, Tmrowka *m=NULL);  //!< zapisuje trasę mrówki m do pliku o nazwie w fn
};


#endif // ZYCIE_H
