# Sudoku Solution Validator

## Opção 1: Executando a partir do código-fonte

### Compilar

`cmake -B build`


`cmake --build build`

### Executar

`./build/bin/sudoku nome_do_arquivo caso_teste`

## Opção 2: Executando através de um container docker

### Baixe a imagem

`docker pull lucassguedes/sudoku`

### Execute a imgem em modo interativo

`docker run -it lucassguedes/sudoku /bin/bash`

### Execute o programa dentro do container

Dentro da pasta `build`, execute o seguinte comando (substituindo <caso_de_teste> por 1, 2 ou 3):

`./bin/sudoku ../sudoku.csv <caso_de_teste>`

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


