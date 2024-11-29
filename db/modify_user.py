import sqlite3
import sys
import returns

conn = sqlite3.connect('./db/database.db')
db = conn.cursor()

if len(sys.argv) < 4:
    returns.values({
        'ok': 'false',
        'msg': 'Não foram passados todos os dados para modificar usuário'
    })
    sys.exit(1)

column = sys.argv[1]
value = sys.argv[2]
id_usuario = sys.argv[3]

try:
    db.execute(f'''
        UPDATE Usuario
        SET {column} = ?
        WHERE ID_USUARIO = ?
    ''', (value, id_usuario))
    conn.commit()

    returns.values({
        'ok': 'true',
        'msg': f'Campo {column} do usuário alterado com sucesso'
    })
except sqlite3.Error as e:
    returns.values({
        'ok': 'false',
        'msg': f'Erro ao modificar dados do usuário {id_usuario}: {e}'
    })

conn.close()