O Objetivo deste exercício é construir uma Árvore de Busca Aleatorizada (Randomised Search Tree) com operações de busca, inserção e remoção, a ser implementada como uma Treap baseada em operações de merge e split como visto em aula. Conforme visto, essas operações podem ser realizadas em tempo esperado O(log N).

Usaremos aqui um gerador congruente linear de números pseudoaleatórios para gerar valores inteiros sem sinal de 32 bits. Esses números são gerados numa sequência X[0], X[1], X[2], ... onde

- O primeiro elemento X[0]= S, chamado semente, é dado
- Para k > 0, temos X[k+1] = (A * X[k] + C) % R, onde A, C e R são parâmetros fixos do gerador, que aqui definimos como R=2^32, A=1664525, C=1013904223.

Seja rng o gerador usado no exercício e denotemos por rng.next() a operação que gera e retorna o próximo número pseudoaleatório (inteiro sem sinal de 32 bits) da sequência. Na primeira chamada, essa função deve retornar X[0]=S.

## Input Specification

A entrada possui uma linha na forma

```
S U B N I D Q P 
```
onde

- S é a semente do gerador pseudo-aleatório
- U é o tamanho do universo das chaves, i.e. as chaves estão no intervalo [U]=0..U-1
- B é um número de inserções iniciais a serem realizada na Treap (burnin)
- N é o número de operações a serem simuladas
- I é a frequência relativa de operações de inserção
- D é a frequência relativa de operações de remoção
- Q é a frequência relativa de operações de consulta
- P é a frequência relativa de impressão dos resultados

ou seja, uma operação arbitrária terá probabilidade Pi = I/(I+D+Q) de ser uma inserção, e Pd=D/(I+D+Q) de ser uma remoção e Pq = Q/(I+D+Q) de ser uma consulta.

Após ler a entrada correspondente a cada caso, o programa deve inicializar um RNG com semente S e uma Treap vazia T.

Em seguida, o programa deve inserir B chaves K[0] = X[0]%U, ..., K[B-1] = X[B-1]%U, onde X[0]=S, X[1], X[2], ... , X[B-1] são os B primeiros valores gerados pelo gerador acima descrito.

Após isso, o programa deve simular N operações da maneira descrita a seguir:

1. Gera X := rng.next() % (I+D+Q)
2. Define o tipo da operação "INS" (inserção), "DEL" (remoção), ou "QRY" (consulta) como OP:="INS" se X < I, OP:="DEL" se I <= X < (I+D) ou OP:="QRY" se `X > (I+D);
3. Se OP == "INS":
    1. Gera uma chave aleatória K := rng.next() % U
    2. Executa a inserção T.insert(K)
4. Se OP == "DEL":
    1. Gera uma chave aleatória K := rng.next() % U
    2. Executa a inserção T.delete(K)
5. Se OP == "QRY":
    1. Gera uma chave aleatória K := rng.next() % U
    2. Executa a consulta T.query(K)

A operação de inserção T.insert(K) baseia-se no split. Primeiro deve-se criar um novo nó X com chave X.key:=K e prioridade aleatória X.prty:=rnd.next() (o mesmo gerador é usado em todo o código). Deve-se então descer na árvore a partir da raiz como uma BST até chegar num nó Y tal que X.prty > Y.prty. X deve ser então inserido no lugar de Y, dividindo-se a subárvore enraizada em Y com base X.key e colocando as duas "metades" como filhos de X. Se um tal nó Y não existir, X é inserido como uma nova folha. IMPORTANTE: Se a árvore já contiver a chave K, a operação não modifica a árvore. Apenas se T não contém a chave K é que o nó X deve ser criado, o que significa que a chamada a rnd.next() para atribuir uma prioridade aleatória ao nó só será executada nesse caso.

A operação T.delete(K) baseia-se no merge. Um nó X com chave X.key=K é localizado e substituído pela fusão dos seus dois filhos.

## Output Specification

Para cada operação simulada #0,1,... após o burnin, o programa deve imprimir a saída correspondente conforme descrito abaixo se #operação % P == 0

- Se a operação foi do tipo T.insert(K), o programa deve imprimir
```
I K L
``` 
onde K é a chave inserida e L é a profundidade do novo criado na árvore (a raiz tem profundidade 0, seus filhos profundidade 1, netos profundidade 2, etc.). Caso a árvore T já contenha a chave K, a operação não provoca qualquer mudança e fazemos L=-1.

- Se a operação foi do tipo T.delete(K), o programa deve imprimir
```
D K L
```
onde K é a chave removida e L é a profundidade onde ela foi encontrada, caso ela esteja na árvore. Caso a árvore T não contenha a chave K, a operação não provoca qualquer mudança e fazemos L=-1.

- Se a operação foi do tipo T.query(K), o programa deve imprimir
```
Q K L
```
onde K é a chave consultada e L é a profundidade onde ela foi encontrada, caso ela esteja na árvore. Caso a árvore T não contenha a chave K, a operação não provoca qualquer mudança e fazemos L=-1.