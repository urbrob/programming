lista = [1, 2, 3, 4]
krotka = (1, 2, 3, 4)
slownik = {
    '1': 1,
    '2': 2,
    '3': 3,
    '4': 4
}


def dodaj():
    a = 5
    a -= 3
    return 5 + 3


def potega(podstawa, wykladnik):
    return podstawa ** wykladnik


def sum_sr(lista):
    suma = 0
    for liczba in lista:
        suma += liczba
    return suma, suma / len(lista)


def extend_by(lista, liczba):
    for index, liczebka in enumerate(lista):
        lista[index] += liczba
    return lista


print(extend_by([1, 2, 3, 4], 5))


def dodaj_2(liczba):
    return liczba + 2


def exam(a, b, c, d, stala=0):
    return stala


def liczby_to_lista(a, *args):
    return args


def len_string_and_int(value):
    if type(value) is type(1):
        return len(str(value))
    else:
        return len(value)


def trudna_funkcja(lista, sumowanie, *args, **kwargs):
    if kwargs.get('is_admin'):
        for index, liczba in enumerate(lista):
            lista[index] += sumowanie
    return lista


# MASA FUNKCJI KTÓRA NAWZAJEM SIĘ WYWOŁUJE V

def nadpisana_trudna_funkcja(lista, sumowanie, *args, **kwargs):
    if kwargs.get('is_admin'):
        for index, liczba in enumerate(lista):
            if lista[index] < kwargs.get('is_from_africa'):
                lista[index] += sumowanie
    return lista


def convert(**kwargs):
    print(kwargs)


convert(robert='glupi', gold7='dzban', hw='blad', moja_srednia=3.0)


def dodaj_a_b(a, b):
    return a + b


def stworz_liste(a, b):
    return [a, b]


def przedstaw_sie(imie):
    return 'Cześć jestem {}'.format(imie)


def argumenty(*args):
    print(args)


def kwargs_print(**kwargs):
    print(kwargs)


args = [1, 2, 3, 4]

kwar = {
    'a': 5,
    'b': 7,
    'c': 8
}


def dodaj_do_liczb(a, b, c):
    a += c
    b += c
    return a, b


def main():
    a = 5
    b = 3
    a, b = dodaj_do_liczb(a, b, 7)
    return a, b
