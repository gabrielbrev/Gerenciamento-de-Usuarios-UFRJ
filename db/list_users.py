import sqlite3
import returns

conn = sqlite3.connect('./db/database.db')
db = conn.cursor()

try:
    db.execute('''
        SELECT * FROM Usuario
    ''')
    users = db.fetchall()

    returns.values({
        'ok': 'true',
        'msg': 'Retornados todos os usuários do banco de dados',
        'result': users
    })
except sqlite3.Error as e:
    returns.values({
        'ok': 'false',
        'msg': f'Erro ao consultar lista de usuários: {e}'
    })

conn.close()
