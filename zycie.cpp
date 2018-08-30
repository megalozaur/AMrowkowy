#include "zycie.h"
using namespace std;

Tzycie::Tzycie(int W,int M,int K_sr, int K_max, int start,int meta) : Tgraf(W,K_sr,K_max){
    t=0;
    this->start=start;
    this->meta=meta;
    if (start>=W || meta>=W) {cout<<"ERROR!   Start lub meta poza grafem\n"; ok=0;}
    zamrowianie(M);
    }


Tzycie::Tzycie(int W,int M, int start,int meta) : Tgraf(W){
    t=0;
    this->start=start;
    this->meta=meta;
    if (start>=W || meta>=W) {cout<<"ERROR!   Start lub meta poza grafem\n"; ok=0;}
    zamrowianie(M);
    }

Tzycie::Tzycie(string fn, int M, int start,int meta) : Tgraf(fn){
    t=0;
    this->start=start;
    this->meta=meta;
    if (start>=W || meta>=W) {cout<<"ERROR!   Start lub meta poza grafem\n"; ok=0;}
    zamrowianie(M);
    }

void Tzycie::zamrowianie(int M){
    // Stworzenie populacji M mrówek
    cout << "Stworzono populację "<<M<<" mrówek"<<endl;
    this->M=M;
    mr=new Tmrowka*[M];
    for (int m=0;m<M;m++)
        mr[m]=new Tmrowka(W,start);

    m0=new Tmrowka(W,start);
    }

Tzycie::~Tzycie() {
    if(mr!=NULL){
        cout << "Skasowano populację "<<M<<" mrówek"<<endl;
        for (int m=0;m<M;m++)
            delete mr[m];
        delete mr;
        }
    delete m0;

}



double Tzycie::P(int i, int j){
    //return d(i,j);
    return pow(f(i,j),A) / pow(d(i,j),B);
}



double Tzycie::SP(int i){
    // wersja niezależna od dotychczasowej trasy mrówki
    if (s(i)) return s(i);
    double S=0;
    for(int k=0;k<W;k++) if (d(i,k)) S+=P(i,k); // niejednoznaczne to 0
    set_s(i,S); //zachowanie do następnego zostawienia feromonu
    return S;
}

//suma feromonu wyłączając drogę, którą się do i-tego węzła doszło - j
double Tzycie::Sf(int i, int j0){
    double S=0;
    //int p=0;
    for(int k=0;k<W;k++) if (d(i,k) && k!=j0) {/*p++;*/S+=f(i,k);} // niejednoznaczne to 0
    /*cout <<"Sf="<<S<<endl;
    cout <<"p="<<p<<endl;
    if (p==1) return -1.0;*/
    return S;
}


double Tzycie::SPm(Tmrowka *m, int i){
    // liczy prawdop. dla już odwiedzonych przez mrówkę m sąsiadów
    double S=0;
    for(int k=0;k<m->K;k++) {
        int j=m->trasa[k];
        if (d(i,j)) S+=P(i,j);
        }
    return S;
}



int Tzycie::losuj_skok(Tmrowka *m){
    int i=m->gdzie();
    double S=SP(i)-SPm(m,i);
    //cout <<"S="<<S;
        if (S<=0) return start;
    S=S*rand()/double(RAND_MAX);
    //cout <<"SP="<<SP(i)<<"  S="<<S<<endl;
    int k;for(k=0;k<W && S>=0;k++) if (d(i,k) && !m->czy_bylas_w(k)) S-=P(i,k);
    k--;
    //Może jednak nie było gdzie skakać, błędy zaokrągleń dały S>0
    if(S>0) k=start;
    return k;
}




void Tzycie::idz(Tmrowka *m){
    if (m->K>=m->Wm-1) {m->idz_na_start();return;}  // zaplątana i nie ma siły iść

    int j=losuj_skok(m);
    if (j==start) {m->idz_na_start(); return;}

    int i=m->gdzie();
    m->idz_do(j,d(i,j));

    if(j==meta) {
        i=start;
        for(int k=1;k<=m->K;k++){
               int j=m->trasa[k];
               //cout <<"->"<<j;
                set_f(i,j,f(i,j)+1/(m->L));
               i=j;
               }
        //cout <<endl;
        m->idz_na_start();
        }
    }


void Tzycie::idzcie(){
    for(int z=0;z<M;z++)
        idz(mr[z]);
    }



/*void Tzycie::zyjcie_podzialka(int T){
    cerr <<"   Życie mrówek przez "<<T<<" kroków"<<endl;
    podzialka();

    int dt=0;for (int c=1;c<74;c++){
        cerr <<"#";
        for(;dt<T && dt<(c*T)/73;dt++){
            idzcie();
            odparuj();
            }
        }
    cerr << endl<< endl;
    t+=dt;
    }

*/
int Tzycie::zyjcie(double kontrast_min, int dt){
       for(int t1=0;t1<dt;t1++){
            idzcie();
            odparuj();
            }
    t+=dt;
    return (trasa()>kontrast_min);
    }


int Tzycie::znajdzcie(double kontrast_min, int dt, int T){
    cerr <<"   Życie mrówek do momentu znalezienia trasy o odp. kontraście, ale max."<<T<<"kroków, spr. co"<<dt<<"kroków."<<endl;

    while (zyjcie(kontrast_min,dt) && t<T) cerr <<"#";
    cerr << endl<< endl;

    if (dt>=T) return 1; // jeśli jeszcze nie osiągnięto odp. kontrastu
    return 0;
    }

int Tzycie::znajdzcie_zapiszcie(string fn,double kontrast_min, int dt, int T){
    cerr <<"   Życie mrówek do momentu znalezienia trasy o odp. kontraście, ale max."<<T<<"kroków, spr. co"<<dt<<"kroków. Z zapisywaniem."<<endl;
    char buffer[100];
    while (zyjcie(kontrast_min,dt) && t<T){
        sprintf(buffer,"%s%04d.dot",fn.c_str(),t);
        zapiszDOT(string(buffer));
        }
    cerr << endl<< endl;

    if (dt>=T) return 1; // jeśli jeszcze nie osiągnięto odp. kontrastu
    return 0;
    }


void Tzycie::odparuj(){
    for(int i=0;i<W;i++)
        for(int j=0;i<j;j++) set_f(i,j,f(i,j)*R);
}

////////////////////////////////////////////////////////////////////////////
double Tzycie::trasa(){
    double fmax,rozmycie,rozmycie_max=0;
    int i=start;
    int j0=start; //ścieżka powrotna wykluczona z rozważań
    int j;
    m0->idz_na_start();
    ////////////
    //if(t==0) return 1.0;
    ////////////
    while(i!=meta && (j=max_f(i,j0,fmax))>=0 && m0->idz_do(   j   ,   d(i,j)   )){
        //kontrast*=1-fmax/Sf(i);
        if (Sf(i,j0)>0) rozmycie=1-fmax/Sf(i,j0); else rozmycie=-1.0;
        //cout<<"rozmycie:="<<rozmycie<<" <=>"<<i<<"--"<<j<<endl;
        if(rozmycie>0 && rozmycie_max<rozmycie) rozmycie_max=rozmycie;
        j0=i;
        i=j;
        }
    if(i!=meta) {cout << "KLOPS!   Nie ma trasy! (Przynajmniej na razie.)"<<endl; return 1.0;}
    cout <<"Znaleziona przez m0 trasa; o dł. "<<m0->L<<", złożona "<<m0->K<<" kawałków, rozmycie feromonu to "<<rozmycie_max<<endl;
    return rozmycie_max;
    }
//Dot. mrówki próbnej

void Tzycie::zaznacz_trase(Tmrowka *m){
    if (m==NULL) m=m0;
    zeroj_f(0.0);
    //set_f(0,1,10);
    int i=m->trasa[0];
    for(int k=1;k<=m->K;k++){
        int j=m->trasa[k];
        set_f(i,j,10);
        //cout <<k<<")"<<i<<" "<<j<<" => f="<<f(i,j)<<endl;
        i=j;
        }
    }

void Tzycie::zapisz_trase(string fn,Tmrowka *m){
    cout << "Zapisywanie trasy\n";
    if (m==NULL) m=m0;
    m->zapisz(fn);
    }
////////////////////////////////////////////////////////////////////////////
//Obsługa
void Tzycie::par(){
    cout << "Parametry symulacji"<<endl;
    cout << "-------------------"<<endl;

    cout << "Krok czasowy  t="<<t<<endl;
    cout << "Liczba mrówek M="<<M<<endl;
    cout << "Liczba węzłów W="<<W<<endl<<endl;

    cout << "start="<<start << "    ----->     meta="<<meta<<endl<<endl;

    cout << "wykładnik odpowiadający feromonowi  A="<<A<<endl;
    cout << "wykładnik odpowiadający odległości  B="<<B<<endl;
    cout << "współczynnik odparowania            R="<<R<<endl<<endl;
    }

