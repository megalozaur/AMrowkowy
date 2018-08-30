#include "graf.h"
using namespace std;

void Tgraf::zeroj_f(double f0){
    for(int j=0;j<W;j++)
        for(int i=j+1;i<W;i++) g[i][j]=f0;
}

double Tgraf::max_f(){
    double max=f(0,1);
    for(int j=0;j<W;j++)
        for(int i=0;i<j;i++) if(f(i,j)>max) max=f(i,j);
    return max;
}

int Tgraf::max_f(int i, double &fmax){
    double max=f(i,0);
    int jmax=0;
    for(int j=0;j<W;j++)
        if(f(i,j)>max) {jmax=j; fmax=f(i,j);}
    return jmax;
}

int Tgraf::max_f(int i, int j0, double &fmax){
    fmax=0.0;
    int jmax=-1;
    for(int j=0;j<W;j++)if(d(i,j)){
        //cout << f(i,j)<< "  ";
        if(f(i,j)>fmax && j!=j0) {jmax=j; fmax=f(i,j);}

       }

    /*cout << "i="<<i<<endl;
    cout << "j0="<<j0<<endl;
    cout << "fmax="<<fmax<<endl;
    cout << "jmax="<<jmax<<endl<<endl;*/

    return jmax;
}

void Tgraf::zeroj_s(){
    for(int i=0;i<W;i++)
        g[i][i]=0;
}




double Tgraf::d(int i, int j){
    if(i==j) return 0;
    if(i<j)	return g[i][j];
    return g[j][i];
}

double Tgraf::f(int i, int j){
    if(i==j) return 0;
    if(i<j)	return g[j][i];
    return g[i][j];
}

double Tgraf::s(int i){
    return g[i][i];
}



void Tgraf::set_d(int i, int j, double x){
    if(i==j) return;
    //if( d(i,j)==0 ) {g[i][i]++; g[j][j]++;}	// Suma niepustych pól
    if(i<j)	g[i][j]=x;
    else g[j][i]=x;
}

void Tgraf::set_f(int i, int j, double x){
    if(i==j) return;
    set_s(i,0);
    set_s(j,0);
    if(i>j)	g[i][j]=x;
    else g[j][i]=x;
}

void Tgraf::set_s(int i, double x){
    g[i][i]=x;
}
