O Objetivo deste exercício é implementar uma Scapegoat Tree com as operações de inserção, e consulta. Conforme visto em aula, uma Scapegoat tree com N nós realiza essas operações em tempo amortizado O(log N).

Neste exercício, usaremos um gerador congruente linear de números pseudoaleatórios para gerar valores inteiros sem sinal de 32 bits. Esses números são gerados numa sequência X[0], X[1], X[2], ... onde

- O  primeiro elemento X[0]= S, chamado semente, é dado
- Para k > 0, temos X[k+1] = (A * X[k] + C) % R, onde A, C e R são parâmetros fixos do gerador, que aqui definimos como R=2^32, A=1664525, C=1013904223.

Seja rng o gerador usado no exercício e denotemos por rng.next() a operação que gera e retorna o próximo número pseudoaleatório (inteiro sem sinal de 32 bits) da sequência. Na primeira chamada, essa função deve retornar X[0]=S.

## Input Specification

A entrada possui uma linha na forma

```
S U A B N I Q P 
```
onde

- S é a semente do gerador pseudo-aleatório
- U é o tamanho do universo das chaves, i.e. as chaves estão no intervalo [U]=0..U-1
- A é o valor de α (alpha), ou seja um float no intervalo (0.5, 1.0)
- B é um número de inserções iniciais a serem realizada na Splay Tree (burnin)
- N é o número de operações a serem simuladas
- I é a frequência relativa de operações de inserção
- Q é a frequência relativa de operações de consulta
- P é a frequência relativa de impressão dos resultados
ou seja, uma operação arbitrária terá probabilidade Pi = I/(I+Q) de ser uma inserção, e Pq = Q/(I+Q) = 1-Pi de ser uma consulta.

Após ler a entrada correspondente a cada caso, o programa deve inicializar um RNG com semente S e uma Scapegoat Tree vazia T com parâmetro α=A.

Em seguida, o programa deve inserir B chaves K[0] = X[0]%U, ..., K[B-1] = X[B-1]%U, onde X[0]=S, X[1], X[2], ... , X[B-1] são os B primeiros valores gerados pelo gerador acima descrito.

Em seguida, o programa deve simular N operações da maneira descrita a seguir:

1. Gera X := rng.next() % (I+Q)
2. Define o tipo da operação "INS" (inserção) ou "QRY" (consulta) como OP:="INS" se X < I, ou OP:="QRY" caso contrário;
3. Se OP == "INS":
    1. Gera uma chave aleatória K := rng.next() % U
    2. Executa a inserção T.insert(K)
4. Se OP == "QRY":
    1. Gera uma chave aleatória K := rng.next() % U
    2. Executa a consulta T.query(K)

## Output Specification

Para cada operação simulada #0,1,... após o burnin, o programa deve imprimir a saída correspondente conforme descrito abaixo se #operação % P == 0

- Se a operação foi do tipo T.insert(K), o programa deve imprimir
```
I K Lo Lf
```
onde K é a chave inserida e Lo é a profundidade em que nova folha foi originalmente criada (a raiz tem profundidade 0, seus filhos profundidade 1, netos profundidade 2, etc.), e Lf a profundidade final na qual K termina após uma eventual reconstrução, caso a árvore tenha se tornado α-desbalanceada (em altura). Se não houve reconstrução, Lf=Lo. Caso a árvore T já contenha a chave K, a operação não provoca qualquer mudança e fazemos Lo=Lf=-1.

- Se a operação foi do tipo T.query(K), o programa deve imprimir
```
Q K L
```
onde K é a chave consultada e L é a profundidade onde ela foi encontrada, caso ela esteja na árvore. Caso a árvore T não contenha a chave K, a operação não provoca qualquer mudança e fazemos L=-1.