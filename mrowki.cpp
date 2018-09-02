#include "mrowki.h"
using namespace std;


Tmrowka::Tmrowka(int W, int start){
    K=0;
    Wm=W;
    trasa=new int[W];
    trasa[0]=start;
    //cout << "Stworzono mrówkę o zasięgu "<<Wm<<endl;
    }


Tmrowka::~Tmrowka(){
    delete trasa;
    //cout << "Skasowano mrówkę"<<endl;
    }

int Tmrowka::gdzie(){
    return trasa[K];
    }

bool Tmrowka::czy_bylas_w(int s){
    for(int k=0;k<K;k++)
        if(trasa[k]==s) return true;
    return false;
    }

void Tmrowka::idz_na_start(){   //int start
        K=0;
        L=0;
        //trasa[0]=start;
    }

int Tmrowka::idz_do(int j, double d){
    if (K>=Wm-1) {idz_na_start();return 0;}  // zaplątana i nie wie co zrobić
    //cout << "Mrówka idzie do "<< j <<endl;
    //int i=gdzie();
    K++;
    trasa[K]=j;
    L+=d;//L+=d(i,j);
    return 1;
    }

void Tmrowka::zapisz(string fn){
    ofstream out;
    cout << "Zapisywanie trasy mrówki do pliku "<<fn<<"..." << endl;
    out.open(fn.c_str(),ofstream::out);
    for (int k=1;k<K;k++)
        out<<trasa[k]<<"\n";
    out.close();
    }
