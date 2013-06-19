agh.pr.wyszukiwarka
===================

Programowanie równoległe C++

opis: program zajmuje się generowaniem listy wyników wyszukiwania na podstawie otrzymanych ID plików, jest częścią systemu wyszukiwania.

Technologia: c++, MPI, openMP

dane wejściowe: plik tekstowy z liczbami (tabela 2wymiarowa)

dane wyjściowe: posortowany wynik wyszukiwania w postaci tabeli rekordów, np.
Object[] = {[id:4,ocena:4.82], [id:3,ocena:3.51]}

algorytm:
- konwertowanie linii w pliku tekstowym na tabele ID
- porównywanie tabel miedzy sobą aby wyciągnąć tylko powtarzające się ID
- zastąpienie każdego ID rekordem/obiektem w którym jest zmienna, według której następuje sortowanie wyników (np. id "12" to rekord w którym jest zmienna "ocena" = 4.83)
- sortowanie tabeli rekordów/obiektów wg wartości zmiennej
- zwrócenie wyniku
