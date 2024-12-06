import sqlite3
import sys
import returns

try:
    from faker import Faker
except:
    print(" ")

conn = sqlite3.connect('./db/database.db')
db = conn.cursor()

if len(sys.argv) < 2:
    returns.values({
            'ok': 'false',
            'msg': 'Número de usuários desejados não informado'
        })
    sys.exit(1)

num_usuarios = int(sys.argv[1])

fake = Faker('pt_BR')    

max_iter = num_usuarios * 10
c = i = 0
while i < num_usuarios and c < max_iter:
    c += 1
    i += 1

    email = fake.email()
    senha = fake.password(length=8)
    nome = fake.name()
    data_nasc = fake.date_of_birth(minimum_age=18, maximum_age=80)
    genero = fake.random_element(elements=('M', 'F'))
    cpf = fake.cpf()
    cep = fake.postcode()
    telefone = fake.phone_number()

    try:
        db.execute('''
            INSERT INTO Usuario (email, senha, nome, dataNasc, genero, cpf, cep, telefone)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?);
        ''', (email, senha, nome, data_nasc, genero, cpf, cep, telefone))
        conn.commit()
    except sqlite3.Error as e:
        i -= 1
        

if c == max_iter:
    returns.values({
        'ok': 'false',
        'msg': f'Erro ao gerar {num_usuarios - i} usuários restantes'
    })
else:
    returns.values({
        'ok': 'true',
        'msg': 'Usuários gerados com sucesso'
    })

conn.close()