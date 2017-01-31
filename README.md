## Implementacja
Program w c++ sprawdzający izomorfizm dwóch grafów rozdzielnych z możliwymi pętlami. Algorytm sprawdzający użyty do tego celu jest częściową implementacją algorytmu VF2. Jeżeli chodzi o szybkość działania to dla większości grafów do 150 wierzchołków, o ile nie są niezwykle złośliwe czas szukania izomorfizmu to nie więcej niż 30s. Dodatkowo w repozytorium znajduje się parę skryptów w pythonie pomagających w testowaniu i wizualizacji wyniku działania programu. Krótki opis posługiwania się nimi:
**GraphIsomorphism** - główny program w C++. Jako dwa argumenty należy podać pliki tekstowe w których w odpowiednim formacie(opisane poniżej w instrukcji) podane są dwa grafy które należy sprawdzić.
**graph.py** - pobiera pliki tekstowe zawierające grafy, a także plik tworzony przez główny program zawierający mapowanie grafów. Następnie rysuje oba grafy i koloruje ich wierzchołki zgodnie z podanym mapowaniem (czyli wierzchołki odpowiadające sobie są w tym samym kolorze). Wykorzystuje bibliotekę IGraph.
**check_isomorphism.py** - ładuje dwa grafy i sprawdza ich izomorfizm. Jako argumenty należy podać nazwy plików tekstowych.
**gen.py** - generuje dwa izomorficzne grafy o zpermutowanych wierzchołkach i zapisuje je do plików tekstowych. Jako argumenty programu należy podać ich nazwy.
**skrypt.sh** - skrypt testowy wywołujący generowanie grafów i sprawdzanie ich izomorfizmu 10 razy.



## AISDI - projekt z algorytmów (grafowych)

Graf G jest *izomorficzny* z grafem H, jeśli istnieje wzajemnie jednoznaczna funkcja (bijekcja) odwzorująca wierzchołki grafu G w wierzchołki grafu H w ten sposób, że jeśli dwa wierzchołki w grafie G są połączone krawędzią, to odpowiadające im wierzchołki w grafie H są również połączone krawędzią.

Proszę napisać program, który:

1. Wczyta dwa grafy nieskierowane z plików o nazwach przekazanych jako argumenty jego wywołania.
2. Sprawdzi, czy wczytane grafy są izomorficzne i jeśli tak, wyświetli odpowiednią funkcję odwzorującą wierzchołki.

**Uwaga:** krawędzie grafu mogą być tylko jednokrotne, ale grafy mogą nie być spójne, a wierzchołki mogą być połączone krawędzią również same ze sobą.

## Sposób uruchomienia programu

    >./program plik_z_opisem_grafu_1 plik_z_opisem_grafu_2

## Format pliku z opisem grafu

W pierwszej linii znajduje się dodatnia liczba całkowita oznaczająca liczbę wszystkich wierzchołków w grafie. Poniżej, dla każdej krawędzi w grafie, znajduje się linia z dwoma nieujemnymi liczbami całkowitymi, oznaczającymi numery wierzchołków połączonych tą krawędzią. Numeracja wierzchołków zaczyna się od 0. Liczby w jednej linii oddzielone są znakiem spacji.

## Wynik działania programu

Wynikiem działania programu powinno być wyświetlenie na ekranie napisu `Izomorficzne` w przypadku gdy dwa wejściowe grafy są izomorficzne, lub `Nieizomorficzne` w przypadku przeciwnym. Kolejne linie poniżej napisu `Izomorficzne` powinny zawierać odwzorowania numerów wierzchołków z grafu pierwszego (w kolejności rosnącej) w odpowiednie numery wierzchołków w grafie drugim: `numer_wierzchołka --> numer_wierzchołka`.

**Uwaga:** w przypadku, gdy istnieje więcej niż jedna funkcja odwzorująca wierzchołki, program powinien wyświetlić dowolną z nich.

## Przykład 1

graf1.txt:

    3

graf2.txt:

    3

wynik:

    >./program graf1.txt graf2.txt
    Izomorficzne
    0 --> 0
    1 --> 1
    2 --> 2

## Przykład 2

graf1.txt:

    4
    0 1
    1 2
    2 3
    3 0
    3 1

graf2.txt:

    4
    1 3
    3 2
    2 0
    0 1
    1 2

wynik:

    >./program graf1.txt graf2.txt
    Izomorficzne
    0 --> 3
    1 --> 2
    2 --> 0
    3 --> 1

