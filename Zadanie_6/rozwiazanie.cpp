/*

algorytm grahama / 
tangensy itd
otoczka wypukla
nie trzeba potegowac / pierwiastkowac jak w jednej linii

posortwac (amplituda, kat odleglosc) "jakos tak"
usuniecie wspolliniowych (pkt 4.)

algorytm:
    szukamy punktu min(y), min(x) (lewy dolny punkt, najpierw y jesli te same to x)
    wyrzucamy go z listy trzyammy gdzies indziej
    policz wspolrzedne polarne, alfa = f(A, O), (punkt z pkt 1. jest tak jakby na (0, 0))
    sortujemy liste po alfa pozniej po d
    usuwamy elementy o tym samym alfa
    2 struktury : lista, stos
    na stos: O, (2 kolejne z listy)
    na liscie: reszta
    liczymy wykladnik: 2 ostatnie elementy ze stosu i jeden z listy
    wykladnik <= 0 to ze stosu sciagam ostatni element i powtarzam
    jezeli > 0 element z listy na stos, a z listy usuwam
    do momentu az l jest puste
    policz obwod: ob + be + ex + ... + xo
    

*/