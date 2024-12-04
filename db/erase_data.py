import sqlite3
import returns

conn = sqlite3.connect('./db/database.db')
db = conn.cursor()

try:
    db.execute('''
        DROP TABLE Usuario
    ''')
    conn.commit()

    db.execute('''
        CREATE TABLE IF NOT EXISTS Usuario (
            id_usuario INTEGER PRIMARY KEY AUTOINCREMENT,
            email TEXT NOT NULL UNIQUE,
            senha TEXT NOT NULL,
            nome TEXT NOT NULL,
            dataNasc DATE NOT NULL,
            genero TEXT CHECK(genero IN ('F', 'M')) NOT NULL,
            cpf TEXT NOT NULL UNIQUE,
            cep TEXT NOT NULL,
            telefone TEXT
        );
    ''')
    conn.commit()

    returns.values({
        'ok': 'true',
        'msg': 'Dados resetados com sucesso',
    })
except sqlite3.Error as e:
    returns.values({
        'ok': 'false',
        'msg': 'Erro ao resetar dados'
    })

conn.close()
