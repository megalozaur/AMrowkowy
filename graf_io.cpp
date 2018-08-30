#include "graf.h"
using namespace std;

void Tgraf::wczytaj(string fn){
    int i,j;
    double d;
    int iW;
    ifstream in;
    cout << "Wczytywanie grafu z pliku "<<fn<<"..." << endl;
    in.open(fn.c_str(),ofstream::in);
    if(!in.is_open()) {cout <<"Nie można otworzyć "<<fn<<endl; return;}
    in >> iW;
    cout << "Ma mieć "<< iW << " węzłów"<<endl;
    if (!W) alokuj(iW);

    while(!in.eof()) {
        in >>i>>j>>d;
        //cout << i<<"\t"<<j<<"\t"<<d<<endl;
        if(i<W && j<W) set_d(i,j,d);
        else cout << "WARNING! Numer węzła przekracza zadeklarowany"<<endl;
    }

    if (iW>W) {cout << "Nie można dopisać do obecnego grafu!"<<endl; return;}
    in.close();
    ok=1;
    }







/*void Tgraf::zapisz(string fn){
    ofstream out;
    cout << "Zapisywanie grafu do pliku "<<fn<<"..." << endl;
    out.open(fn.c_str(),ofstream::out);
    piszTXT(out);
    out.close();
    }*/



void Tgraf::zapiszTXT(string fn){
    zapiszTak(fn,&Tgraf::piszTXT);
}

void Tgraf::zapiszDOT(string fn){
    zapiszTak(fn,&Tgraf::piszDOT);
}


void Tgraf::zapiszTak(string fn, void (Tgraf::*foo)(ofstream &out) ){
    ofstream out;
    cout << "Zapisywanie grafu do pliku "<<fn<<"..." << endl;
    out.open(fn.c_str(),ofstream::out);
    (this->*foo)(out);
    out.close();
    }



void Tgraf::piszTXT(ofstream &out){
    out << W << endl;
    for (int j=0;j<W;j++)
        for(int i=j+1;i<W;i++)
            if (d(i,j)) out << i <<"\t"<< j <<"\t"<< d(i,j) << endl;
    out << endl;
    }


void Tgraf::piszDOT(ofstream &out){
    out << "graph G {" << endl;
    for (int j=0;j<W;j++)
        for(int i=j+1;i<W;i++)
            if (d(i,j)!=0){
                out << i <<"--" << j << "[label=" << int(d(i,j)*100)/100.0;

                if (10*f(i,j)<  max_f()) out << ",penwidth=0.1,color=red";
                else out << ",penwidth=" << int(f(j,i)/max_f()*1000.0)/100.0;
                out << "]"<< endl;
                }
    out << "}" << endl;
    }
