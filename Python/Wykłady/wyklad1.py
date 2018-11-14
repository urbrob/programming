# Zmienne
a = 1
b = 'ABCD'
c = 'A'
d = 1.23

# Podmianka
print(b, a)
b, a = a, b
print(b, a)
a = 7
b = 9
a += b
b = a - b
a = a - b
print(a, b)

# Operatory arytmetyczne
liczba_1 = 5
liczba_2 = 3
print(liczba_1 + liczba_2)
print(liczba_1 - liczba_2)
print(liczba_1 * liczba_2)
print(liczba_1 / liczba_2)
print(liczba_1 % liczba_2)
print(liczba_1 ** 2)


# Dzialanie na słowach
slowo = 'Python jest'
slowo_formatowane = '{} prawda ?'.format(slowo)
print(slowo_formatowane)
slowo_dodawane = slowo + ' prawda ?'
print(slowo_dodawane)  # Bad practice
stara_szkola = 'Patrz na to : %s' % 'WOW' # Nigdy tego nie użyłem, jest dość mało czytelne
print(stara_szkola)
slowo = 'ałaizd oT'
odwrocone_slowo = odwrocone_slowo[::-1]
print(odwrocone_slowo)

# Lista (To samo co tablica)
lista = [1,2,3,4,5,6]
print(lista[3])
lista = [1, 2, 3, 4, 5]
print(lista.pop(), lista)
print(lista.append(6), lista)
print(lista[:2], lista[1:2], lista[-1], lista[:-2])
del lista[:2]
print(lista)

# Krotka(tuple)
krotka = (1, 2, 3, 4, 4)
print(dir(krotka))
print(krotka)
lista_z_krotki = list(krotka)

# Słownik
slownik = {'1': 'jeden', '2': 2, '3': 3.00}
print(slownik['1'])
del slownik['1']
# print(slownik['1'])
print(slownik.get('1'))
print(slownik.pop('2'))
print(slownik.get('2', 'LOL NIEMA'))

# Instrukcje warunkowe
test = True
if test:
    print('Test to prawda')

a = 5
if a > 7:
    print('Prawda')
else:
    print('Fałsz')

if a < 7 and a > 3 or a == 5:
    print('Prawda')
else:
    print('False')

# Pętle
i = 0
while i < 10:
    i += 1
    print (i)
    


