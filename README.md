# Gerenciador de Usuários

Este projeto é um sistema simples para gerenciar usuários e suas informações. Ele utiliza C++ para a lógica central e scripts Python para interagir com um banco de dados. É necessário notar que o projeto possui algumas funcionalidades que têm como intuito facilitar a demonstração do funcionamento principal, as quais não seriam aplicadas em uso real.

## Dependências

O projeto depende dos seguintes componentes:

1. **C++11 ou superior**: Para compilar o código C++.
2. **Python 3**: Para rodar os scripts Python, que são usados para interagir com o banco de dados.
3. **Pacote faker**: Utilizado no script Python para gerar usuários aleatórios. Ele pode ser instalado globalmente ou num ambiente virtual dentro do projeto com o seguinte comando: **pip3 install faker**

## Compilação, execução e limpeza

1. Para compilar o código C++, basta executar o comando: **make**. Isso irá gerar o executável `app` a partir dos arquivos fonte.
2. Após compilar o projeto, execute o programa com: **./app**.
3. Quando terminar, você pode executar o comando: **make clean**. Isso vai deletar os arquivos gerados pela compilação do projeto.

## Como utilizar

### 1. Login:

Ao executar o programa, é necessário fazer login. É apresentada uma simples verificação de usuário e senha, que estão ambos definidos no código do arquivo `main.cpp` como **admin**.

### 2. Menu:

Após entrar no menu, o programa irá apresentar opções de funcionalidade (números), confirmações (sim ou não) e informações de usuário/pesquisa, que devem ser fornecidos no console.

## Funcionalidades

-   **Listar usuários**: Exibe todos os usuários cadastrados no banco de dados.
-   **Buscar usuários**: Permite buscar usuários por nome.
-   **Adicionar usuários**: Cria um novo usuário no banco de dados.
-   **Editar usuários**: Modifica os dados de um usuário existente.
-   **Deletar usuários**: Remove um usuário do banco de dados.
-   **Gerar usuários aleatórios**: Cria n usuários com informações aleatórias.
-   **Resetar banco de dados**: Apaga todos os dados do banco.

## Scripts Python

Os scripts Python no diretório `db/` são responsáveis por realizar as operações no banco de dados. Eles são chamados pelo código C++ para:

-   **`init_db.py`**: Inicializa o banco de dados caso ele não exista.
-   **`list_users.py`**: Lista todos os usuários do banco.
-   **`get_users_by_name.py`**: Busca usuários por nome.
-   **`add_user.py`**: Adiciona um novo usuário.
-   **`modify_user.py`**: Modifica um usuário existente.
-   **`delete_user.py`**: Deleta um usuário.
-   **`erase_data.py`**: Reinicia o banco de dados apagando a tabela existente e criando uma nova.
-   **`generate_users.py`**: Gera usuários aleatórios utilizando o pacote `faker`.
