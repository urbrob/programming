def set_base():
    import sqlite3

    # Połączenie z bazą danych
    conn = sqlite3.connect('database.db')

    # Cursor który umożliwi nam tworzenie zapytań do baz danych
    c = conn.cursor()

    c.execute("""CREATE TABLE IF NOT EXISTS patients (
              'pesel' 			VARCHAR(11) PRIMARY KEY,
              'first_name'    		VARCHAR(30),
              'last_name'     		VARCHAR(30),
              'address'       		VARCHAR(50),
              'index_number'  		integer);
              """)
    conn.commit()

    c.execute("""CREATE TABLE IF NOT EXISTS sequences (
              'ID'                  INTEGER PRIMARY KEY AUTOINCREMENT,
              'name'                VARCHAR(30),
              'description'         TEXT);
              """)
    conn.commit()

    c.execute("""CREATE TABLE IF NOT EXISTS sequences_connections (
              'from_id'                  INTEGER ,
              'to_id'                    INTEGER,
              FOREIGN KEY(from_id) REFERENCES sequences(ID),
              FOREIGN KEY(to_id) REFERENCES sequences(ID));
              """)
    conn.commit()

    c.execute("""CREATE TABLE IF NOT EXISTS patient_sequences (
              'patient_id'                     INTEGER ,
              'sequence_id'                    INTEGER,
              FOREIGN KEY(patient_id) REFERENCES patients(pesel),
              FOREIGN KEY(sequence_id) REFERENCES sequences(ID));
              """)
    conn.commit()


    c.execute("""CREATE TABLE IF NOT EXISTS symptoms (
              'ID'                       INTEGER PRIMARY KEY AUTOINCREMENT,
              'name'                     VARCHAR(30),
              'description'              TEXT);
              """)
    conn.commit()


    c.execute("""CREATE TABLE IF NOT EXISTS sequences_symptoms (
              'sequence_id'                     INTEGER ,
              'symptom_id'                      INTEGER,
              'chance'                          REAL,
              FOREIGN KEY(sequence_id) REFERENCES sequences(ID),
              FOREIGN KEY(symptom_id) REFERENCES symptoms(ID));
              """)
    conn.commit()

    conn.close()
