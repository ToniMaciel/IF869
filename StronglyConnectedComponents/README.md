O objetivo deste exercício é implementar o Algoritmo de Kosaraju, visto em aula, para calcular as componentes fortemente conexas (CFC) de um grafo dirigido.

## Input Specification

entrada inicia com uma linha com um inteiro

```
C
```
correspondente ao número de casos de teste. Após uma linha em branco, segue-se a descrição de C grafos, cada um correspondendo a um caso de teste. Cada grafo está descrito como listas de adjacências na forma

```
N
0 D[0]: W[0,0] W[0,1] ... W[0, D[0]-1]
1 D[1]: W[1,0] W[1,1] ... W[1,D[1]-1]
...
N-1 D[N-1]: W[N-1,0] W[N-1,1] ... W[N-1,D[N-1]-1]
```

onde

- N é o número de vértices do grafo, numerados 0..N-1
- D[I] é o grau de saída do vértice I, para I=0..N-1
- W[I,0]...W[I,D[I]-1] são os sucessores do vértice I, ou seja, o grafo contém arestas I-->W[I,J] para J=0..D[I]-1
Após cada caso, temos uma linha em branco.

## Output Specification

Para cada caso de teste no formato acima descrito, o programa deve imprimir a saída correspondente na forma

```
K
V[0,0] V[0,1] ... V[0,M[0]-1]
V[1,0] V[1,1] ... V[1,M[1]-1]
...
V[K-1,0] V[K-1,1] ... V[1,M[K-1]-1]
```

onde K corresponde ao número de CFC do grafo correspondente, e cada uma delas é dada numa das linhas V[J,0] V[J,1] ... V[J,M[J]-1], que contém os seus M[J] vértices ordenados e separados por espaço, ou seja, V[J,0] < V[J,1] < ... < V[J,M[J]-1]. As CFC também devem ser impressas em ordem lexicográfica, ou seja, V[0,0] < V[1,0] < ... < V[K-1,0]. Após cada caso, deve ser impressa uma linha em branco.