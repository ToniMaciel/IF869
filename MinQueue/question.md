Na última implementação de MinQueue vista em aula, usamos um array dinâmico V para armazenar os elementos da fila e outro array dinâmico M para armazenar os elementos da fila que ainda poderão ser mínimo, ou seja, que não são sucedidos na fila por um elemento menor.

Por exemplo, após enfileirar os valores 4, 20, 39, 7, 12, 10, teríamos:
```
V = [4, 20, 39, 7, 12, 10]
M = [4, 7, 10]
```
Após desenfileirar o 4 e o 20, teríamos:
```
V = [39, 7, 12, 10]
M = [7, 10]
```
e assim sucessivamente.

O objetivo deste exercício é implementar uma MinQueue para inteiros sem sinal de 32 bits (uint32_t).

Para tal, considere um gerador congruente linear de números pseudoaleatórios. Esses números são gerados numa sequência X[0], X[1], X[2], ... onde

O primeiro elemento X[0]= S, chamado semente, é dado
Para k > 0, temos X[k] = (A * X[k-1] + C) % R, onde A, C e R são parâmetros fixos do gerador.
Neste exercício usaremos R=2^32, A=1664525, C=1013904223.

### Input Specification

A entrada possui uma linha especificando um caso de teste na forma
```
S B N P
```
Onde

S é a semente do gerador da sequência aleatória que será usada
B é um inteiro que representa um burn in, ou seja, um número inicial de enfileiramentos na MinQueue. Inicialmente, o programa deve enfileirar os valores y gerados pelo gerador com a semente S e valores de A, C e R acima especificados.
N especifica o número total de operações a serem realizadas na MinQueue após o burn in (portanto, no total serão N+B operações).
P especifica a frequência relativa das operações push/pop.
Para cada uma das N operações após os B enfileiramentos de burn in, o algoritmo a ser executado é o seguinte:
```
1. Obtém o próximo número `X[i]` da sequência pseudo-aleatória
2. Caso `X[i] % 10 < P`:
        2.1  Obtém o próximo número `X[i+1]` e enfileira-o na MinQueue
   Caso `X[i] % 10 >= P:
        2.2. Desenfileira um elemento da MinQueue
```
### Output Specification

Para cada uma das N operações após o burn in o programa deve imprimir uma linha na forma
```
L I
```
onde

L indica o número de elementos que ainda podem ser mínimo (comprimento do array M)
I especifica a posição do elemento mínimo na fila (o primeiro elemento ainda na fila está na posição 0, o segundo na posição 1, e assim sucessivamente)

Sample Input #1
2671786989 10 10 6

Sample Output #1
2 9
3 9
3 8
3 7
2 7
2 6
2 5
2 4
3 4
3 4