# Projekt zaliczeniowy - Algorytmy i Struktury Danych II

Tytul: _Program rozwiazujacy problem otwarcia **n** skarbonek_

Autor: _Cezary924_

Jezyk: _C++_

Rok: _2021/2022_


## Opis programu

W poleceniu przedstawiony został problem otwarcia _n_ skarbonek 
przy pomocy odpowiadającym im kluczy. Każdą skarbonkę można 
otworzyć jej indywidualnym kluczem lub rozbić młotkiem. 
Poszczególne klucze powrzucane są do losowych skarbonek w losowej 
ilości. Celem zadania jest znalezienie minimalnej ilości skarbonek, 
które należy rozbić. 

Rozwiązać powyższe ćwiczenie można posługując się implementacją 
grafu przygotowaną podczas zajęć z _Algorytmów i struktur danych_. 
W tym przypadku mamy do czynienia z grafem skierowanym, którego 
węzłami są numery skarbonek. Krawędź występuje między węzłami, 
jeśli klucz pierwszej skarbonki znajduje się w drugiej.  

Przygotowana na ćwiczeniach implementacja grafu rozszerzona została 
o dodatkowe elementy. Klasa definiująca wierzchołki posiada dodatkową 
zmienną pomocniczą zdolną przechowywać liczbę całkowitą. Zmiany 
zaszły również w funkcji _main_, w której zastąpiono testy sprawdzające 
poprawne działanie implementacji grafu poprzez funkcje odpowiedzialne 
za konsolowy interfejs użytkownika oraz algorytm wyszukujący 
najmniejszą możliwą liczbę skarbonek do rozbicia.  

W algorytmie tym przemieszczamy się od wierzchołka poprzez jedyną 
wychodzącą z niego krawędź do następnego wierzchołka. Jeśli wierzchołek 
nie został jeszcze odwiedzony, zmieniona zostaje liczba przechowywana 
przez niego na numer początkowego wierzchołka. Operacje te wykonywane 
są dla kolejnych wierzchołków na trasie do momentu, w którym algorytm 
napotka wierzchołek, który w zmiennej pomocniczej przechowuje numer 
początkowego wierzchołka lub numer innego wierzchołka. W pierwszym 
przypadku oznacza to, że droga, którą algorytm podróżował, jest tą samą 
składową grafu (cyklem) – zwiększona zostaje wartość zmiennej przechowującej liczbę różnych składowych. Natomiast w sytuacji drugiej algorytm doszedł 
do analizowanej już wcześniej składowej – nie ma potrzeby zwiększania 
liczby składowych. Do przemieszczania się użyto iteratora po krawędziach 
wychodzących z danego wierzchołka. Algorytm wykonywany jest dla każdego wierzchołka grafu. Końcowa liczba składowych oznacza minimalną liczbę 
skarbonek, które należy rozbić, aby dostać się do wszystkich skarbonek. 


## Opis użytych struktur danych

Do realizacji użyto implementacji grafu przygotowanej 
na zajęciach. Składa się ona z klasy definiującej graf 
jako macierz, a także definiującej podstawowe operacje 
na grafie (_class GraphAsMatrix_) oraz klas, których 
instancje będą odpowiadać wierzchołkom/krawędziom (_class 
Vertex_/_class Edge_). Zaimplementowane zostały również klasy 
definiujące różne rodzaje iteratorów i wizytatorów, jednakże 
w tym projekcie używany jest jedynie iterator po krawędziach 
wychodzących z danego wierzchołka (_class EmanEdgesIter_). 


## Oszacowanie złożoności czasowej i pamięciowej

Złożoność czasowa głównego algorytmu: _O(n)_. 

Złożoność pamięciowa głównego algorytmu: _O(1)_.


## Dokumentacja użytkowa

Program znajduje się w katalogu _Program_Skarbonki_. Dzięki 
Makefile uruchomić program można jedną komendą: _make run_. 
Po uruchomieniu program czytelnie prosi użytkownika o wprowadzenie 
kolejnych danych – zgodnie z narzuconą w poleceniu ideologią 
wprowadzania danych. 
