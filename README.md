# Compilar


`cmake -B build`


`cmake --build build`

## Threads por caso de teste

| Argumento | Threads por coluna   | Threads por linha | Threads por quadrado | 
|-----------|----------------------|-------------------|----------------------|
| 1         |           1          |         1         |          9           |
| 2         |           9          |         9         |          9           | 
| 3         |           0          |         0         |          0           |

## Tempo gasto por caso em segundos

| Qt. instancias   |        Caso 1        |      Caso 2       |       Caso 3         | 
|------------------|----------------------|-------------------|----------------------|
| 10000            |       0.025168       |                   |      0.054220        |
| 500000           |       1.057103       |                   |      2.658658        | 
| 1000000          |       2.140401       |                   |      5.292253        |
