import sqlite3
import sys
import re
import returns

conn = sqlite3.connect('./db/database.db')
db = conn.cursor()

if len(sys.argv) < 2:
    returns.values({
        'ok': 'false',
        'msg': 'Não foram passados todos os dados para buscar usuário'
    })
    sys.exit(1)

nome = sys.argv[1]
nome_query = (f'{re.sub(r'[^a-zA-Z0-9 ]', '_', nome)}%').replace(' ', '%')
# Substitui os caracteres especiais por "_" e adiciona "%" no final e no lugar dos espacos

try:
    db.execute(f'''
        SELECT *
        FROM Usuario
        WHERE nome LIKE ?
    ''', (nome_query, ))
    users = db.fetchall()

    returns.values({
        'ok': 'true',
        'msg': f'Retornados os usuários contendo "{nome}" no nome',
        'result': users
    })
except sqlite3.Error as e:
    returns.values({
        'ok': 'false',
        'msg': f'Erro ao consultar usuários de nome {nome}: {e}'
    })

conn.close()