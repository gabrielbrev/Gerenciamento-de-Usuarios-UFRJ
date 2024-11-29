import sqlite3
import returns

conn = sqlite3.connect('./db/database.db')
db = conn.cursor()

try:
    db.execute('''
        DROP TABLE Usuario
    ''')
    conn.commit()

    returns.values({
        'ok': 'true',
        'msg': 'Tabela de usuários deletada com sucesso',
    })
except sqlite3.Error as e:
    returns.values({
        'ok': 'false',
        'msg': 'Erro ao deletar tabela de usuários'
    })

conn.close()
