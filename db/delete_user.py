import sqlite3
import sys
import returns

conn = sqlite3.connect('./db/database.db')
db = conn.cursor()

if len(sys.argv) < 2:
    returns.values({
        'ok': 'false',
        'msg': 'Não foram passados todos os dados para deletar usuário'
    })
    sys.exit(1)

id_usuario = sys.argv[1]

try:
    db.execute(f'''
        DELETE FROM Usuario
        WHERE ID_USUARIO = ?
    ''', (id_usuario, ))
    conn.commit()

    returns.values({
        'ok': 'true',
        'msg': f'Usuário {id_usuario} deletado com sucesso'
    })
except sqlite3.Error as e:
    returns.values({
        'ok': 'false',
        'msg': f'Erro ao deletear usuário {id_usuario}: {e}'
    })

conn.close()