from tkinter import *
from sqllite import set_base
from tkinter import messagebox
import sqlite3


def makeform(root, fields):
    entries = []
    for field in fields:
        row = Frame(root)
        lab = Label(row, width=15, text=field, anchor='w')
        ent = Entry(row)
        row.pack(side=TOP, fill=X, padx=5, pady=5)
        lab.pack(side=LEFT)
        ent.pack(side=RIGHT, expand=YES, fill=X)
        entries.append((field, ent))
    return entries

def save_patient(form):
    values = [value[1].get() for value in form]
    values[0] = int(values[0])
    values[4] = int(values[4])
    query = "INSERT INTO patients VALUES (?, ?, ?, ?, ?);"
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute(query, values)
    conn.commit()
    print(f"USED QUERY: INSERT INTO patients(pesel, first_name, last_name, address, index_number) VALUES ({values[0]}, '{values[1]}', '{values[2]}', '{values[3]}', {values[4]})")
    conn.close()


def get_all_patient():
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    query = "SELECT * FROM patients;"
    c.execute(query)
    rows = c.fetchall()
    messagebox.showinfo("Patients", rows)
    for entry in rows:
        print(entry)
    print(f"USED QUERY: {query}")
    conn.close()


def make_patients():
    root = Tk()
    form = makeform(root, ['pesel', 'first_name', 'last_name', 'address', 'index_number'])
    b1 = Button(root, text='Create', command=lambda: save_patient(form))
    b1.pack(side=LEFT, padx=5, pady=5)
    b2 = Button(root, text='Getall', command=get_all_patient)
    b2.pack(side=LEFT, padx=5, pady=5)


if __name__ == '__main__':
    set_base()
    root = Tk()
    b1 = Button(root, text='Add patient',
                command=make_patients)
    b1.pack(side=LEFT, padx=5, pady=5)
    b2 = Button(root, text='Quit', command=root.quit)
    b2.pack(side=LEFT, padx=5, pady=5)
    root.mainloop()
