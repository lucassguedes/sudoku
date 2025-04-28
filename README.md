# Sudoku Solution Validator

Projeto focado na implementação e análise da verificação de jogos sudoku com múltiplas threads. O programa lê um arquivo `.csv`e verifica a validez de cada uma das instâncias do sudoku.  Foi realizada a implementação com três casos diferentes, com mais ou menos threads, que pode ser vista em detalhes mais a diante.

## Opção 1: Executando a partir do código-fonte

### Compilar

`cmake -B build`


`cmake --build build`

### Executar

`./build/bin/sudoku nome_do_arquivo <caso_teste> <numero_de_instancias>`

## Opção 2: Executando através de um container docker

### Baixe a imagem

`docker pull lucassguedes/sudoku`

### Execute a imgem em modo interativo

`docker run -it lucassguedes/sudoku /bin/bash`

### Execute o programa dentro do container

Dentro da pasta `build`, execute o seguinte comando (substituindo <caso_de_teste> por 1, 2 ou 3):

`./bin/sudoku ../sudoku.csv <caso_de_teste> <numero_de_instancias>`

## Threads por caso de teste

| Qt. Threads            | Caso 1               | Caso 2            | Caso 3               | 
|------------------------|----------------------|-------------------|----------------------|
| Threads para linhas    |           1          |         9         |          0           |
| Threads para colunas   |           1          |         9         |          0           | 
| Threads para quadrados |           9          |         9         |          0           |

## Tempo gasto por caso

A Tabela apresenta os valores médios de tempo (em segundos) de resolução de uma quantidade definida de instâncias em cada caso após 10 execuções, em um 11th Gen Intel® Core™ i5-11320H × 8.

| Qt. instâncias   |        Caso 1        |      Caso 2       |       Caso 3         | 
|------------------|----------------------|-------------------|----------------------|
| 1                |       0.000700       |     0.001569      |      0.000031        |
| 10000            |       0.049772       |     0.028268      |      0.092676        |
| 500000           |       1.857274       |     1.036911      |      4.579158        | 
| 1000000          |       3.695505       |     1.925958      |      9.108666        |


## Quem fez o que?
O projeto foi feito de forma bem conjunta e complementar, então é um pouco difícil fazer a separação.
O processo de verificação do sudoku foi feito em conjunto.
A criação de diferentes casos foi feita por Ana Cecília.
A criação do leitor de arquivo foi feita por Lucas.

Acho que mais detalhes da separação pode ser melhor observado pelo histórico de commits.