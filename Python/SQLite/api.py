from tkinter import *
from sqllite import set_base
from tkinter import messagebox
import sqlite3

# Funkcja do formularza
def makeform(root, fields):
    entries = []
    # Dodaj pola do wpisania
    for field in fields:
        row = Frame(root)
        lab = Label(row, width=15, text=field, anchor='w')
        ent = Entry(row)
        row.pack(side=TOP, fill=X, padx=5, pady=5)
        lab.pack(side=LEFT)
        ent.pack(side=RIGHT, expand=YES, fill=X)
        entries.append((field, ent))
    return entries

# Funkcja kt�ra wyci�ga z formularza dane i zapisuje u�ytkownika
def save_patient(form):
    values = [value[1].get() for value in form]
    # Warto�ci z formularza zawsze s� zwracane w formie STRING musimy je zamieni� na INT
    values[0] = int(values[0])
    values[4] = int(values[4])
    # To zapytanie oznacza DODAJ DO TABELI pacjenci WARTO�CI (Kt�re b�d� p�niej dodane)
    query = "INSERT INTO patients VALUES (?, ?, ?, ?, ?);"
    # Po��cz z baz�
    conn = sqlite3.connect('database.db')
    # Stw�rz kursor
    c = conn.cursor()
    # Odpal zapytanie i przeka� dane do tych znak�w zapytania (values)
    c.execute(query, values)
    # Zaakceptuj zmian� do bazy danych
    conn.commit()
    print(f"USED QUERY: INSERT INTO patients(pesel, first_name, last_name, address, index_number) VALUES ({values[0]}, '{values[1]}', '{values[2]}', '{values[3]}', {values[4]})")
    conn.close()


# Funkcja pobiera wszystkich pacjent�w z bazy
def get_all_patient():
    # Po��czenie z baz� danych.
    conn = sqlite3.connect('database.db')
    # Stworzenie kursora, kt�ry b�dzie wysy�a� zapytania do bazy danych
    c = conn.cursor()
    # To zapytania oznacza "WE� wszystkie pola Z TABELI patients"
    query = "SELECT * FROM patients;"
    # Wy�lij zapytanie do bazy danych
    c.execute(query)
    # Wyci�gnij wynik z zapytania 
    rows = c.fetchall()
    # Wypisz dane pobrane z bazy
    messagebox.showinfo("Patients", rows)
    for entry in rows:
        print(entry)
    print(f"USED QUERY: {query}")
    # ZAWSZE zamykamy po��czenie z baz� danych
    conn.close()


# Funkcja tworzy nowe okienko z formularzem (funkcja makeform) i dodaje przyciski do zapisania pacjenta i wczytania go
def make_patients():
    root = Tk()
    form = makeform(root, ['pesel', 'first_name', 'last_name', 'address', 'index_number'])
    b1 = Button(root, text='Create', command=lambda: save_patient(form))
    b1.pack(side=LEFT, padx=5, pady=5)
    b2 = Button(root, text='Getall', command=get_all_patient)
    b2.pack(side=LEFT, padx=5, pady=5)


# To jest funkcja kt�ra si� odpala gdy w��czymy skrypt
if __name__ == '__main__':
    # Ustawiamy baz� danych
    set_base()
    # Odpalamy nasz� aplikacje do dodawania, dodajemy przyciski i zap�tlamy wykonywanie
    root = Tk()
    b1 = Button(root, text='Add patient',
                command=make_patients)
    b1.pack(side=LEFT, padx=5, pady=5)
    # Aby komenda dzia�a�a musisz j� poda� bez () inaczej nie zadzia�a. Musi to by� wska�nik do funkcji
    b2 = Button(root, text='Quit', command=root.quit)
    b2.pack(side=LEFT, padx=5, pady=5)
    root.mainloop()
