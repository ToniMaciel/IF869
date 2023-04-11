O Objetivo deste exercício é implementar uma Skip List (SL) com as operações de busca, inserção e remoção. Conforme visto em aula, uma SL de pode ser usada para realizar essas operações em tempo esperado O(lg N).

A figura abaixo ilustra uma SL para os valores (2, 4, 6, 8, 10, 12, 14, 16, 18) com altura 3. Uma busca pela chave X=18 começaria no head pelo nível 2, passaria para os nós de valor 6 e depois 10 ainda no nível 2, depois desceria para o nível 1 ainda no nó 10, passaria então para o nó 16 no nível 1, e desceria então para o nível 0 ainda no nó 16, onde a busca se encerraria com o cursor posicionado sobre esse precursor. Esse caminho está indicado na figura pelos numerais romanos. Repare que, neste exemplo, a busca passou por 4 nós distintos (head,6,10,16), ao invés dos oito que seriam necessários numa busca sequencial. Caso quisésssemos remover esse valor da lista, seguiríamos o mesmo caminho, e o mesmo também ocorreria caso quiséssemos inserir o valor 17. Caso o valor procurado não pertença à SL, a busca encerraria no último nó e no nível 0.

<div class="overflow-table">
  +----+                            +----+                +----+                                                  +----+
  |    |                            |    |                |    |                                                  |    |
2 | I  ---------------------------->| II ---------------->|III -------------------------------------------------->|    |
  |    |                            |    |                |    |                                                  |    |
  |    |                 +----+     |    |                |    |                           +----+                 |    |
1 |  ------------------->|   ------>|  ------------------>|III'--------------------------->| IV ----------------->|    |
  |    |     +----+      |    |     |    |     +----+     |    |     +----+     +----+     |    |      +----+     |    |
  |    |     |    |      |    |     |    |     |    |     |    |     |    |     |    |     |    |      |    |     |    |
0 |  ------->|  -------->|   ------>|  ------->|   ------>|   ------>|   ------>|   ------>| IV' ----->|   ------>|    |
  |    |     |    |      |    |     |    |     |    |     |    |     |    |     |    |     |    |      |    |     |    |
  +====+     +====+      +====+     +====+     +====+     +====+     +====+     +====+     +====+      +====+     +====+
  |    |     |    |      |    |     |    |     |    |     |    |     |    |     |    |     |    |      |    |     |    |
  | \  |     |  2 |      | 4  |     |  6 |     | 8  |     | 10 |     | 12 |     | 14 |     | 16 |      | 18 |     | NIL|
  +----+     +----+      +----+     +----+     +----+     +----+     +----+     +----+     +----+      +----+     +----+      
  head
</div>

Neste exercício, usaremos um gerador congruente linear de números pseudoaleatórios para gerar valores inteiros sem sinal de 32 bits. Esses números são gerados numa sequência X[0], X[1], X[2], ... onde

O primeiro elemento X[0]= S, chamado semente, é dado
Para k > 0, temos X[k+1] = (A * X[k] + C) % R, onde A, C e R são parâmetros fixos do gerador, que aqui definimos como R=2^32, A=1664525, C=1013904223.
Seja RNG o gerador usado no exercício e denotemos por RNG.next() a operação que gera e retorna o próximo número pseudoaleatório (inteiro sem sinal de 32 bits) da sequência. Na primeira chamada, essa função deve retornar X[0]=S.

### Input Specification

A entrada é constituída de uma linha na forma
```
S U B N F J D P
```
onde

- S é a semente do gerador pseudo-aleatório
- U é o tamanho do universo, ou seja, a SL armazena valores no intervalo 0..U-1
- B é o tamanho do burn-in, ou seja, uma quantidade inicial de inserções
- N é o número total de operações a serem simuladas (buscas, inserções, remoções).
- F é um inteiro não-negativo que representa a frequência relativa de operações do tipo busca
- J é um inteiro não-negativo que representa a frequência relativa de operações do tipo inserção
- D é um inteiro não-negativo que representa a frequência relativa de operações do tipo remoção
- P é um inteiro não-negativo que indica a frequência de impressão dos resultados. O programa deverá imprimir a resposta de uma a cada P operações como descrito abaixo.
ou seja, uma operação arbitrária terá probabilidade Pf = F/(F+I+D) de ser uma busca, Pi = I/(F+I+D) de ser uma inserção, e Pd = D/(F+I+D) de ser uma remoção.

Após ler a entrada, o programa deve inicializar um RNG com semente S, e uma SL L inicialmente vazia.

Após isso, o programa deve inicialmente inserir os valores Y[0] = X[0] % U, ..., Y[B-1] = X[B-1] % U, onde X[0]=S, X[1], X[2], ... , X[B-1] são os B primeiros valores gerados pelo gerador acima descrito.

Em seguida, o programa deve simular N operações da maneira descrita a seguir:

1. Gera X := RNG.next() % (F+I+D)
2. Defina o tipo da operação "FND" (busca) ou "INS" (inserção) ou "DEL" (remoção) como OP := "FND" se X < F; "INS" se F <= X < F+I ou "DEL" se F + I <= X
3. Se OP == "FND":
    1. Gera um valor a consultar X := RNG.next() % U
    2. Executa a operação de busca L.find(X)
3. Se OP == "INS":
    1. Gera um valor a inserir X := RNG.next() % U
    2. Executa a inserção L.insert(X)
4. Se OP == "DEL":
    1. Gera um valor a remover X := RNG.next() % U
    2. Executa a remoção L.delete(X)

Durante a inserção, o programa deverá sortear uma altura H para o novo nó a ser inserido de acordo com o seguinte Algoritmo:

1. Inicializa H := 1
2. Defina a altura máxima MAX_H := L.height + 1
3. Enquanto (RNG.next() % 100) < 50 e H < MAX_H:
    1. H := H+1
4. Retorna H

IMPORTANTE: Em todas os passos do algoritmo o mesmo gerador pseudo-aleatório deve ser utilizado.

### Output Specification

O programa deve produzir uma saída com na forma

```
Z[0]
Z[1]
...
Z[O-1]
```
onde as linhas Z[J], J=0..O-1 correspondem aos resultados das operações de número J*P, contadas a partir do 0 após o burn-in (i.e. O=floor(N/P), da seguinte forma:

- Se a operação foi do tipo L.find(X), imprime uma linha
```
F D H
```
onde D é quantidade de nós difentes visitados no caminho de busca, incluindo e head e terminando no precursor de X, e H é a altura do nó X. No exemplo da busca pelo valor 18 acima, o programa deveria imprimir.

```
F 4 1
```

Caso o valor não pertença a L devemos fazer H=0. Por exemplo, se buscássemos o valor 11, o programa deveria imprimir
```
F 3 0
```

Se a operação foi do tipo T.insert(X), imprime uma linha
```
I R
```

onde R é o resultado da operação: 1 se o valor foi inserido com sucesso, ou 0 se o X já pertencia à SL.

Se a operação foi do tipo T.delete(X), imprime uma linha
```
D R
```

onde R é o resultado da operação: 1 se o valor foi removido com sucesso, ou 0 se o X não pertencia à SL.
