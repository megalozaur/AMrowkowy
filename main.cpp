// d(i,j)=0 niejednoznaczne

#include "zycie.h"
#include <string>
#include <iostream>
#include <iterator>
#include <boost/program_options.hpp>
namespace po = boost::program_options;
using namespace std;

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 * http://www.boost.org/doc/libs/1_58_0/doc/html/program_options/tutorial.html#idp337653936
 * http://www.boost.org/doc/libs/1_62_0/libs/program_options/example/first.cpp
 * https://stackoverflow.com/questions/718447/adding-external-library-into-qt-creator-project
 */
int main(int argc, char* argv[]){
    double thre,A,B,R;
    int M,W,K_sr,K_max,T,start,meta,dt;
    Tzycie *mrowisko=NULL;

    po::options_description desc("AMrowkowy -- Adam Brodacki\n\n"
                                 "Program szuka najkrótszej ścieżki w grafie, pomiędzy dwoma węzłami.\n\nDostępne opcje");
    desc.add_options()
        ("help", "wyświetla tę informację");

    po::options_description symu_desc("Parametry symulacji");
    symu_desc.add_options()
        ("start", po::value<int>(&start)->default_value(1), "nr węzła startowego")
        ("meta", po::value<int>(&meta)->default_value(2), "nr węzła końcowego\n")
        ("m", po::value<int>(&M)->default_value(50), "liczba mrówek\n")
        ("A", po::value<double>(&A)->default_value(4), "wykładnik odpowiadający feromonowi")
        ("B", po::value<double>(&B)->default_value(1), "wykładnik odpowiadający odległości")
        ("R", po::value<double>(&R)->default_value(0.875), "współczynnik odparowania\n")
        ("dt", po::value<int>(&dt)->default_value(5), "co tyle kroków sprawdza warunek zakończenia i zapisuje stan grafu")
        ("t", po::value<int>(&T)->default_value(10000), "maksymalna liczba kroków symulacji")
        ("thre", po::value<double>(&thre)->default_value(0.25), "maksymalna wartość ,,rozmycia feromonu'' między ścieżkami (warunek zakończenia symulacji)");

    po::options_description graf_desc("Wczytywanie, tworzenie i zapisywanie grafu");
    graf_desc.add_options()
        ("if", po::value<string>(), "wejściowy plik tekstowy z grafem (użycie tej spowoduje pominięcie losowania nowego grafu)\n\nPlik zawiera w pierwszej linii liczbę wierzchołków grafu, następne linie zawierają trójki liczb, dwie pierwsze reprezentują nry wierzchołków w numeracji od zera, trzecia odległość tych wierzchołków.\n")
        ("of", po::value<string>(), "wyjściowy plik tekstowy z grafem (format pliku j.w.)\n\n")
        ("wg", po::value<int>(&W)->default_value(15), "liczba wierzchołków grafu do wylosowania")
        ("kga", po::value<int>(&K_sr)->default_value(5), "średnia liczba krawędzi")
        ("kgm", po::value<int>(&K_max)->default_value(10), "maksymalna liczba krawędzi");

    po::options_description outp_desc("Dane wyjściowe");
    outp_desc.add_options()
        ("p-trasa", po::value<string>(), "zapisuje listę wierzchołków trasy do pliku tekstowego o podanej nazwie (kolejne linie zawierają kolejne wierzchołki, z pominięciem startu i mety)")
        ("g-trasa", po::value<string>(), "zapisuje graf z wyznaczoną trasą w formacie dot")
        ("g-feromon", po::value<string>(), "zapisuje graf z końcowym stanem feromonu w formacie dot")
        ("g-dt", po::value<string>(), "szkielet nazwy pliku na stany pośrednie, zapisywane co dt kroków, formacie dot");



    po::variables_map vm;
    desc.add(symu_desc).add(graf_desc).add(outp_desc);
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        return 0;
        }

    if (vm.count("if")) {
        cout << "Wczytywanie grafu z pliku '" << vm["if"].as<string>() << "'.\n";
        mrowisko=new Tzycie(vm["if"].as<string>(),M,start,meta);
        //Tzycie *mrowisko=new Tzycie(3,10);
        //mrowisko->wczytaj("graf.txt");
        }
    else {
        cout << "Tworzenie grafu\n";
        mrowisko=new Tzycie(W,M,K_sr,K_max,start,meta);
        }

    if(!(mrowisko->ok)){
            cout << "Nie ma grafu\n";
            return 1;
        }

    mrowisko->A=A;
    mrowisko->B=B;
    mrowisko->R=R;

    if (vm.count("of")) mrowisko->zapiszTXT(vm["of"].as<string>());

    if (T){

    if (vm.count("g-dt")) mrowisko->znajdzcie_zapiszcie(vm["g-dt"].as<string>(),thre,dt,T);
    else mrowisko->znajdzcie(thre,dt,T);

    mrowisko->par();
    if (vm.count("g-feromon")) mrowisko->zapiszDOT(vm["g-feromon"].as<string>());

    mrowisko->trasa();
    mrowisko->zaznacz_trase();

    if (vm.count("g-trasa")) mrowisko->zapiszDOT(vm["g-trasa"].as<string>());
    if (vm.count("p-trasa")) mrowisko->zapisz_trase(vm["p-trasa"].as<string>());
    }

    delete mrowisko;
    return 0;
}


