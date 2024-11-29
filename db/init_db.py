import sqlite3
import returns

conn = sqlite3.connect('./db/database.db')
db = conn.cursor()

try:
    # Usuario(id_usuario, email, senha, nome, dataNasc, genero, cpf, cep, telefone)

    # CHECKS:
    # genero deve ser 'f' ou 'm'
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

    returns.values({
        'ok': 'true',
        'msg': f'Conectado ao banco de dados'
    })
except sqlite3.Error as e:
    returns.values({
        'ok': 'false',
        'msg': f'Erro ao inicializar o banco de dados: {e}'
    })


