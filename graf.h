#ifndef GRAF_H
#define GRAF_H
using namespace std;

//! Definicja klasy zawierającej graf i ślad feromonowy
/*! Definicja klasy zawierającej graf, ślad feromonowy, metody do manipulacji i odczytywania tych danych, losowanie, wczytywanie, zapisywanie grafu

<pre>
 j/i: 0   1   2   3 . . . . . W
 .. +---+---+---+---+---+---+---+
 0  | S | D | D | D | D | D | D |
    +---+---+---+---+---+---+---+
 1  | f | S | D | D | D | D | D |
    +---+---+---+---+---+---+---+
 2  | f | f | S | D | D | D | D |
    +---+---+---+---+---+---+---+
 3  | f | f | f | S | D | D | D |
 .  +---+---+---+---+---+---+---+
 .  | f | f | f | f | S | D | D |
 .  +---+---+---+---+---+---+---+
 .  | f | f | f | f | f | S | D |
 .  +---+---+---+---+---+---+---+
 W  | f | f | f | f | f | f | S |
    +---+---+---+---+---+---+---+

    S(w,w) - suma prawdopodobieństw dla wierzchołka w odp. kol. w=i=j
    D(i,j),i>j - odległość dwu węzłów i i j.
    f(i,j),j>i - ilość feromonu na trasie między j i i
    W - ilość węzłów</pre>
*/

#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "pomocnicze.h"


class Tgraf {

protected:
    int W=0;		//!< Liczba węzłów grafu

private:
    double *g1D=NULL;	//!< tablica W*W g[i,j]=g1D[i+j*W]
    double **g=NULL;
    void alokuj(int W);

    void zeroj_s();


public:
    Tgraf(int W);                       //!< stworzenie pustego grafu
    Tgraf(string fn);                   //!< stworzenie grafu na podstawie pliku
    Tgraf(int W, int K_sr, int K_max);	//!< stworzenie i losowanie grafu o K krawędziach
    ~Tgraf();
    double d(int i, int j);             //!< odczyt odległości
    double f(int i, int j);         	//!< odczyt poziomu feromonu
    double s(int i);                    //!< odczyt sumy dla i-tego wierzchołka
    void set_d(int i, int j, double x);	//!< wpisanie krawędzi
    void set_f(int i, int j, double x);	//!< aktualizacja poziomu feromonu
    void zeroj_f(double f0=1.5);        //!< wpisanie stałej wartości jako f(i,j)
    double max_f();                     //!< wyznacza max f(i,j)
    int max_f(int i,double &fmax);         //!< najpowabniejszy skok z i
    int max_f(int i,int j0,double &fmax);  //!< najpowabniejszy skok z i z pominięciem j0 - czyli powrotnego

    void set_s(int i, double x);		//!< zapis sumy dla i-tego wierzchołka

    void piszDOT(ofstream &out);        //!< funkcja wypisująca do strumienia dane w formacie DOT
    void piszTXT(ofstream &out);        //!< funkcja wypisująca do strumienia dane w formacie TXT
    void zapiszTak(string fn, void (Tgraf::*foo)(ofstream &out) );  //!< otwarcie pliku i zapisanie go przy pomocy funkcji foo
    void zapiszDOT(string fn);          //!< zapis grafu do pliku DOT o nazwie w fn
    void zapiszTXT(string fn);          //!< zapis grafu do pliku DOT o nazwie w fn
    void wczytaj(string fn);            //!< wczytanie grafu z pliku
    void przekatna();                   //!< wypisanie przekątnej - s
    int ok=0;       //!< 1-graf istnieje można działać
    };

#endif // GRAF_H
