O Objetivo deste exercício é implementar uma Árvore de van Emde Boas (vEBT) com as operações de inserção, remoção e sucessor. Conforme visto em aula, uma vEBT sobre o universo [U]=0..U-1 de tamanho U=2^(2^M) pode ser usada para realizar essas operações em tempo O(M=lglg U).

Neste exercício, usaremos um gerador congruente linear de números pseudoaleatórios para gerar valores inteiros sem sinal de 32 bits. Esses números são gerados numa sequência X[0], X[1], X[2], ... onde

- O primeiro elemento X[0]= S, chamado semente, é dado
- Para k > 0, temos X[k+1] = (A * X[k] + C) % R, onde A, C e R são parâmetros fixos do gerador, que aqui definimos como R=2^32, A=1664525, C=1013904223.

Seja RNG o gerador usado no exercício e denotemos por RNG.next() a operação que gera e retorna o próximo número pseudoaleatório (inteiro sem sinal de 32 bits) da sequência. Na primeira chamada, essa função deve retornar X[0]=S.

### Input Specification

A entrada é constituída de uma linha na forma

```
S M B N I F D P
```

onde

- S é a semente do gerador pseudo-aleatório
- M é o valor de lglg U ou seja, a vEBT armazena inteiros no universo 0..U-1, onde U=2^(2^M)
- B é o tamanho do burn-in, ou seja, uma quantidade inicial de inserções
- N é o número total de operações a serem simuladas (inserções, remoções e sucessor).
- I é um inteiro não-negativo que representa a frequência relativa de operações do tipo inserção
- F é um inteiro não-negativo que representa a frequência relativa de operações do tipo sucessor
- D é um inteiro não-negativo que representa a frequência relativa de operações do tipo remoção
- P é um inteiro não-negativo que indica a frequência de impressão dos resultados. O programa deverá imprimir a resposta de uma a cada P operações como descrito abaixo.

ou seja, uma operação arbitrária terá probabilidade Pi = I/(I+F+D) de ser uma inserção, Pf = F/(I+F+D) de ser um sucessor, Pd = D/(I+F+D) de ser uma remoção.

Após ler a entrada, o programa deve inicializar um RNG com semente S, e uma vEBT T sobre o universo U=[2^(2^M)]=0..2^(2^M)-1, inicialmente vazia.

Após isso, o programa deve inicialmente inserir os valores Y[0] = X[0] % U, ..., Y[B-1] = X[B-1] % U, onde X[0]=S, X[1], X[2], ... , X[B-1] são os B primeiros valores gerados pelo gerador acima descrito.

Em seguida, o programa deve simular N operações da maneira descrita a seguir:

1. Gera X := RNG.next() % (I+F+D)
2. Defina o tipo da operação "INS" (inserção) ou "SUC" ou "DEL" (remoção) como OP := "INS" se X < I; "SUC" se I <= X < I+F ou "DEL" se I + F <= X
3. Se OP == "INS":
    1. Gera um valor a inserir X := RNG.next() % U
    2. Executa a inserção T.insert(X)
4. Se OP == "SUC":
    1. Gera um valor a consultar X := RNG.next() % U
    2. Executa a operação de consulta do sucessor T.successor(X)
5. Se OP == "DEL":
    1. Gera um valor Y := RNG.next() % U
    2. Faz X := T.sucessor(Y) se Y tem sucessor ou X := Y caso contrário.
    3. Executa a remoção T.delete(X)

### Output Specification

O programa deve produzir uma saída com na forma

```
Z[0]
Z[1]
...
Z[O-1]
```

onde as linhas Z[J], J=0..O-1 correspondem aos resultados das operações de número J*P, contadas a partir do 0 após o burn-in (i.e. O=floor(N/P), da seguinte forma:

- Se a operação foi do tipo T.insert(X), imprime uma linha
```
I L
```

onde L é o número de "níveis" da vEBT acessados para a inserção. Ao realizarmos a chamada inicial, acessamos o primeiro nível com universo de tamanho U. Se essa chamada realiza uma chamada recursiva para inserir num dos clusters de tamanho sqrt(U) então o segundo nível será acessado, e assim sucessivamente até, no máximo, chegar a uma "folha" com universo de tamanho 2, acessando, nesse caso, M-1 níveis. IMPORTANTE: Caso a vEBT T já contenha o valor X antes dessa operação, consideramos L=0.

- Se a operação foi do tipo T.successor(X), imprime uma linha
```
S X'
```
onde X' é o sucessor de X em T. Caso X não tenha sucessor em T, então X'=U.

- Se a operação foi do tipo T.delete(X), imprime uma linha
```
D L
```
onde L é o número de "níveis" da vEBT acessados para a remoção, como explicado acima para a inserção. 

IMPORTANTE: Caso a vEBT T não contenha o valor X antes dessa operação, consideramos L=0.
