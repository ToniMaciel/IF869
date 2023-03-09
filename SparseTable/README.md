O Objetivo deste exercício é implementar uma SparseTable com as operações de range query e update. Conforme visto em aula, uma SparseTable sobre uma sequência de tamanho N pode ser usada para realizar consultas de intervalo (range queries) em tempo O(lg N) para funções combináveis em geral, ou em tempo constante para funções combináveis idempotentes.

Neste exercício, usaremos um gerador congruente linear de números pseudoaleatórios para gerar valores inteiros sem sinal de 32 bits. Esses números são gerados numa sequência X[0], X[1], X[2], ... onde

- O primeiro elemento X[0]= S, chamado semente, é dado
- Para k > 0, temos X[k+1] = (A * X[k] + C) % R, onde A, C e R são parâmetros fixos do gerador, que aqui definimos como R=2^32, A=1664525, C=1013904223.

Seja RNG o gerador usado no exercício e denotemos por RNG.next() a operação que gera e retorna o próximo número pseudoaleatório (inteiro sem sinal de 32 bits) da sequência. Na primeira chamada, essa função deve retornar X[0]=S.

## Input Specification

A entrada é constituída de várias linhas, cada uma correspondendo a um caso de teste (numerados 0,1,2...) na forma

```S N F O Q U```

Onde:

- S é a semente do gerador pseudo-aleatório
- N é o tamanho da sequência de valores (largura da SparseTable)
- F = MIN, MAX ou SUM indica a função a ser computada pela SparseTable
- O é o número total de operações a serem simuladas (range queries ou updates)
- Q é um inteiro não-negativo que representa a frequência relativa de operações do tipo range query
- U é um inteiro não-negativo que representa a frequência relativa de operações do tipo update

ou seja, uma operação arbitrária terá probabilidade Pq = Q/(Q+U) de ser uma query e Pu = 1-Pq = U/(Q+U) de ser do tipo update.

Após ler a entrada correspondente a cada caso, o programa deve inicializar um RNG com semente S e uma SparseTable T com a função F sobre os valores Y[0] = X[0]%M, ..., Y[N-1] = X[N-1] % M, onde X[0]=S, X[1], X[2], ... , X[N-1] são os N primeiros valores gerados pelo gerador acima descrito, e M = 4*N.

Em seguida, o programa deve simular O operações da maneira descrita a seguir:

1. Gera X := RNG.next()
2. Defina o tipo da operação "QRY" (query) ou "UPD" (update) como OP := "QRY" if X % (Q + U) < Q else "UPD"
3. Se OP == "QRY":
    1. Gera o limite à esquerda do intervalo L := RNG.next() % N
    2. Gera o limite à direita do intervalo R := L + 1 + (RNG.next() % (N-L))
    3. Executa a range query T.range_query(L,R) = F(Y[L:R])

4. Se OP == "UPD":
    1. Gera a posição I := RNG.next() % N
    2. Gera o valor V := RNG.next() % M (onde M=4*N)
    3. Executa o update T.update(I, V) para atualizar o valor de índice I para V 3 provocar a reconstrução parcial da SparseTable

## Output Specification

Para cada caso de teste 0,1,... da entrada, o programa deve produzir uma saída na forma

```
caso <#caso>
Z[0]
Z[1]
...
Z[O-1]
<linha em branco>
```

onde as linhas Z[i], i=0..O-1 correspondem aos resultados da operações simuladas da seguinte forma:

- Se a operação foi do tipo T.range_query(L,R), imprime o resultado da range query sobre o intervalo [L:R]
-  Se a operação foi do tipo T.upd(I, V), imprime o resultado da range query sobre o intervalo [I:N] após a atualização.