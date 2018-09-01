# AMrowkowy
Implementation of Ant Colony Algorithm for finding optimal path in graph

## Zasada działania programu
Program służy do wyszukiwania najkrótszej drogi w nieskierowanym grafie.
Przeszukiwanie grafu przebiega losowo, przez wiele niezależnych agentów -mrówek.

## Algorytm mrówkowy
```
stworzenie albo wczytanie grafu o W wierzchołkach
stworzenie populacji M mrówek
*DOPÓKI* rozmycie < ROZMYCIE_MAX *I* czas symulacji < T_MAX:
	*NIECH KAŻDA* mrówka:
    	*JEŚLI* ilość krawędzi w jej trasie przekracza W:
			idzie na start
		wybierze losowo kolejny węzeł
		skoczy tam
		obliczy długość swojej trasy
		*JEŚLI* jest na starcie:
			wyczyści pamięć
		*JEŚLI* jest na mecie:
			doda feromon na trasie (**)
			wraca na start
	odparowanie feromonu (*)
	znalezienie optymalnej trasy i obliczenie rozmycia
zapisanie optymalnej trasy
```

## Tworzenie grafu
Program zawiera moduł odpowiedzialny za stworzenie spójnego grafu o zadanej liczbie wierzchołków, średnią i maksymalną liczbą krawędzi przypadających na wierzchołek. Tworzenie takiego grafu przebiega dwuetapowo. Najpierw łączone są ze sobą wszystkie
elementy, tak by zapewnić spójność. Następnie dodawane są połączenia pomiędzy losowymi wierzchołkami, które mają mniej niż maksymalna możliwa ilość połączeń. Dzieje się to dopóki nie zostanie osiągnięta zadana średnia liczba połączeń na wierzchołek. Wylosowane grafy stanowią dane testowe dla programu.

## Zapis i odczyt grafu 
Program wczytuje i zapisuje graf do plików tekstowych o następującej strukturze:
1. Pierwsza linia zawiera liczbę wierzchołków
2. Każda kolejna składa się z trójki liczb oddzielonych znakami tabulacji lub spacjami.
Pierwsze dwie to numery wierzchołków, w numeracji od zera; muszą być mniejsze niż liczba w pierwszej linii. Trzecia zmiennoprzecinkowa liczba określa długość krawędzi.

## Zapisywanie trasy do pliku
Wynik działania programu zapisywany jest jako plik tekstowy, którego pierwsza linia zawiera długość trasy, a kolejne numery węzłów ją definiujących.
Obsługa programu
Program umożliwia ustawienie parametrów symulacji, opisanych w pierwszej części instrukcji, wczytanie lub wygenerowanie grafu, określenie początkowego i końcowego węzła.Obsługa programu przebiega z poziomu linii poleceń. Po wywołaniu z argumentem *--help*,
program wyświetla następujące informacje:
```
AMrowkowy -- Adam Brodacki
Program szuka najkrótszej ścieżki w grafie, pomiędzy dwoma węzłami.
Dostępne opcje:
--help wyświetla tę informację
Parametry symulacji:
--start arg (=1)
--meta arg (=2) nr węzła startowego
nr węzła końcowego
--m arg (=50) liczba mrówek
--A arg (=4)
--B arg (=1)
--R arg (=0.875) wykładnik odpowiadający feromonowi
wykładnik odpowiadający odległości
współczynnik odparowania
--dt arg (=5) co tyle kroków sprawdza warunek zakończenia i zapisuje
stan grafu
maksymalna liczba kroków symulacji
maksymalna wartość ,,rozmycia feromonu'' między
ścieżkami (warunek zakończenia symulacji)
--t arg (=10000)
--thre arg (=0.25)
Wczytywanie, tworzenie i zapisywanie grafu:
--if arg
wejściowy plik tekstowy z grafem (użycie tej
spowoduje pominięcie losowania nowego grafu)
Plik zawiera w pierwszej linii liczbę wierzchołków
grafu, następne linie zawierają trójki liczb, dwie
pierwsze reprezentują nry wierzchołków w numeracji
od zera, trzecia odległość tych wierzchołków.
--of arg wyjściowy plik tekstowy z grafem (format pliku j.w.)
--wg arg (=15)
--kga arg (=5)
--kgm arg (=10) liczba wierzchołków grafu do wylosowania
średnia liczba krawędzi
maksymalna liczba krawędzi
Dane wyjściowe:
--p-trasa arg
--g-trasa arg
--g-feromon arg
--g-dt arg
zapisuje listę wierzchołków trasy do pliku
tekstowego o podanej nazwie (kolejne linie zawierają
kolejne wierzchołki, z pominięciem startu i mety)
zapisuje graf z wyznaczoną trasą w formacie dot
zapisuje graf z końcowym stanem feromonu w formacie
dot
szkielet nazwy pliku na stany pośrednie, zapisywane co
dt kroków, formacie dot
```
