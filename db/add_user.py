import sqlite3
import sys
import returns

conn = sqlite3.connect('./db/database.db')
db = conn.cursor()

if len(sys.argv) < 9:
    returns.values({
        'ok': 'false',
        'msg': 'Não foram passados todos os dados do novo usuário'
    })
    sys.exit(1)

values = sys.argv[1:]

try:
    db.execute(f'''
        INSERT INTO Usuario (email, senha, nome, dataNasc, genero, cpf, cep, telefone)
        VALUES ({', '.join(['?'] * len(values))});
    ''', values)
    conn.commit()

    returns.values({
        'ok': 'true',
        'msg': 'Usuário cadastrado com sucesso'
    })
except sqlite3.Error as e:
    returns.values({
        'ok': 'false',
        'msg': f'Erro ao cadastrar o usuário: {e}'
    })

conn.close()
