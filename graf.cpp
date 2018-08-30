#include "graf.h"
using namespace std;

/**
 * @brief Tgraf::alokuj
 * @param W
 */
void Tgraf::alokuj(int W){
    this->W=W;
    g1D=new double[W*W];
    for (int w=0;w<W*W;w++) g1D[w]=0;
    g=new double*[W];
    for (int w=0;w<W;w++) g[w]=g1D+w*W;
    cout << "Stworzono graf o "<<W<<" wierzchołkach"<<endl;
    zeroj_f();
    }


Tgraf::Tgraf(int W){
    W++;
    alokuj(W);
    }

Tgraf::Tgraf(string fn){
    wczytaj(fn);
    }


Tgraf::Tgraf(int W, int K_sr, int K_max){
    alokuj(W);
    srand (time(0));

    //połączenie wszystkich węzłów -- wtedy graf spójny
    int i=rand()%W;
    cerr <<"   Łączenie wszystkich węzłów... "<<endl;
    podzialka();
    int k=0;for (int z=1;z<74;z++){
        cerr << "#";
    for (;k<W-1 && k<z*(W-1)/73;k++){
        //cout << k;
        //strzał w jeden z nieskomunikowanych węzłów i nie obecym (i-tym)
        int p=W-k-int(s(i));
        //cout << "p_max=" << p <<"\t";
        p=rand()%p;
      //  cout << " p=" << p << "\t";

        //znaleznienie ustrzelonego
        int j;for(j=0;j<W && p>=0;j++) if(s(j)==0 && i!=j) p--;
        j--;

    //    cout << "==> * -- " << j << endl;
        set_d(j,i,rand()/double(RAND_MAX));
        set_s(j,s(j)+1);set_s(i,s(i)+1);	//s-liczba krawedzi od danego węzła
        i=j;

        }
        }
    cout<<endl<<endl;
    cout<<"Ilości połączeń dla kolejnych węzłów (k="<<k<<"):"; przekatna(); cout<<endl<<endl;
    cerr <<"   Dodawanie połączeń, żeby osiągnąć zadaną średnią..."<<endl; podzialka();

    // dodanie każdego z połączeń poniżej K_max tak samo prawdopodobne
    int j;
    for (int z=1;z<74;z++){
        cerr << "#";

    while(2*k<W*K_sr && 2*k<W*K_sr*z/73){

        //strzał w parę nieskomunikowanych węzłów
        int p=0;for(i=0;i<W;i++)
            for(j=i+1;j<W;j++) if(!d(i,j)) p+=(K_max-s(j))*(K_max-s(i));

        if (p==0) break;
        p=p>1?rand()%p:0;

        //znaleznienie ustrzelonego
        for(i=0;i<W && p>=0;i++)
            for(j=i+1;j<W && p>=0;j++) if(!d(i,j)) p-=(K_max-s(j))*(K_max-s(i));
        j--;i--;

        set_d(j,i,rand()/double(RAND_MAX));
        set_s(j,s(j)+1);set_s(i,s(i)+1);	//s-liczba krawedzi od danego węzła
        k++;
        i=j;
        }

    }

cout<<endl<<endl;
cout<<"Ilości połączeń dla kolejnych węzłów: "; przekatna();
zeroj_s();
    ok=1;
    }

void Tgraf::przekatna(){
    double S=0;
    for (int l=0;l<W;l++) {cout << s(l) << "\t"; S+=s(l);}
    cout << "S="<<S<<endl;
    }



Tgraf::~Tgraf(){
    delete g;
    delete g1D;
    cout << "Skasowano graf o "<<W<<" wierzchołkach."<<endl;
    }


