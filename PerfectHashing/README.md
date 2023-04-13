Uma família de funções de dispersão H={h:[U]->[M]} de um universo [U]=0..U-1 num intervalo [M]=0..M-1 é dita universal se para quaisquer X!=Yem [U], temos Prob[h(X)=h(Y)]<=1/M, sendo essa probabilidade definida sobre todas as possíveis escolhas de h em H. Para U e M dados, podemos definir uma família universal como H(U,M,P)={h(K)=((a*K + b) % P) % M; 0<a<P, 0<=b<P}, onde P>M é um número primo. Uma função em H(U,M,P) é portanto definida pelos seus parâmetros (a,b), que podem ser gerados aleatoriamente como a:=1 + rng.next()%(P-1) e b:=rng.next()%P, onde rng.next() é a operação que produz o próximo número numa sequência pseudoaleatória.

Neste exercício, usaremos sempre valores inteiros de 32 bits sem sinal e P=2^31 - 1. Para gerar os valores (pseudo)aleatórios, usaremos um gerador congruente linear rng. Esses números são gerados numa sequência X[0], X[1], X[2], ... onde

- O primeiro elemento X[0]=S, chamado semente, é dado
- Para k > 0, temos X[k+1] = (A * X[k] + C) % R, onde A, C e R são parâmetros fixos do gerador, que aqui definimos como R=2^32, A=1664525, C=1013904223.

A chamada a rng.next() gera e retorna o próximo número pseudoaleatório (inteiro sem sinal de 32 bits) da sequência. Na primeira chamada, essa função deve retornar X[0]=S.

Uma Hashtable aberta T com encadeamento é uma tabela com M posições, associada a uma função de dispersão hT:[U]->[M], em que cada posição T[i] é uma lista encadeada. Neste exercício, vamos escolher hT aleatoriamente na família universal H(U,M,P) como descrito acima. Para acrescentar uma chave K do universo [U] à tabela, temos a operação T.set(K) que calcula a posição i:=hT(K) e, em seguida, adiciona K ao final da lista T[i], desde que K ainda não esteja na tabela. Se T já contém K, a operação não provoca nenhuma mudança. Para consultar se a T contém K, temos a operação T.get(K), que calcula a posição i:=hT(K) da mesma forma, e em seguida procura K na lista T[i].

Para garantir o tempo constante esperado nas operações de busca e inserção, imediatamente antes de inserir uma nova chave K (ou seja, já depois de verificar que ela não está em T), devemos verificar se a tabela já tem muitos elementos, ou seja se 2*N>M, onde N é o número de chaves armazenadas em T e M o tamanho da tabela. Caso isso se verifique, deve ocorrer um rehashing: uma nova tabela T' de tamanho M':=2M+1 é inicializada, juntamente com uma nova função de dispersão hT':[U]->[M'], e todas as chaves de T (da primeira à última lista T[0]..T[M-1], da esquerda para a direita) são reinseridas com T'.set(), como descrito acima. Ao final, a antiga tabela é descartada e substituída pela nova. Só então a nova chave K é inserida.

Uma Hashtable perfeita T é uma estrutura hierárquica constituída por uma tabela de tamanho M = N = #chaves em T e uma função de dispersão hT escolhida numa família universal. Neste exercício usaremos a família H(U,M,P) descrita acima. Cada posição T[i] corresponde a uma Hashtable estática sem colisões com N[i] elementos, com capacidade M[i]=N[i]^2, e função de dispersão universal g[i]. Neste exercício, teremos cada g[i] escolhida aleatoriamente em H(U,M[i],P). Para consultar uma chave K em T, primeiro calculamos a posição do primeiro nível i:=hT(K), e em seguida comparamos a chave K com a posição j:=g[i](K) da tabela T[i].

Uma hashtable perfeita é uma estrutura estática construída a partir de uma coleção fixa de valores K[0]..K[N-1] num universo [U] da seguinte maneira:

Parte 1

1. Inicialize a tabela T com M=2*floor(N/2)+1 (=N+1 se N for par, ou N se for ímpar) posições vazias e gere aleatoriamente uma função de dispersão hT em H(U,M,P)
2. Mapeie K[0]..K[N-1] nas M posições com hT, como se fosse uma Hashtable aberta com encadeamento, porém sem o rehashing. Seja N[i] o número de chaves mapeados em cada posição i=0..M-1.
3. Se SOMA(N[i]^2; i=0..M-1) > 4*N volte ao passo 1. Caso contrário, continue para a Parte 2 a seguir.

Parte 2

1. Para cada posição i=0..M-1:
    1. Se N[i]==0 avance para o próximo i (as posições vazias da tabela são ignoradas)
    2. Defina M[i] := N[i]^2 + 1
    3. Inicialize uma tabela vazia T'[i] de capacidade M[i] e gere aleatoriamente uma função de dispersão g[i] em H(U,M[i],P)
    4. Insira as M[i] chaves mapeadas em T[i] na Parte 1 em T'[i] (na mesma ordem) usando a função de dispersão g[i], isto é T'[i][g[i](K)]:=K. Caso haja alguma colisão, retorne ao passo 3 anterior.
    5. Substitua T[i] pela nova tabela T'[i] (sem colisões).

Neste exercício, primeiro vamos criar uma Hashtable aberta com encadeamento T0, e depois vamos construir uma Hashtable perfeita T1 a partir dela.

## Input Specification

A entrada consiste em uma linha

```
S U M0 I Q Pi Pq
```

onde

- S é a semente do gerador pseudoaleatório congruente linear rng.
- U é o tamanho do universo das chaves, isto é o universo será [U]=0..U-1
- M0 é a capacidade inicial da Hashtable aberta T0
- I é o número de operações de inserção simuladas na Hashtable aberta T0
- Q é o número de operações de consulta simuladas na Hashtable perfeita T1
- Pi é a frequência de impressão dos resultados das operações de inserção em T0
- Pq é a frequência de impressão dos resultados das operações de consulta em T0

Após ler a entrada o programa deve executar os seguintes passos:

1. Inicialize o gerador aleatório rng com semente S, e demais parâmetros como descrito acima. IMPORTANTE: Este gerador será usado globalmente pelo programa como a única fonte de aleatoriedade. É imprescindível que as chamadas a rng.next() ocorram na quantidade e ordem exatas de acordo com as especificações do problema.
2. Inicialize uma Hashtable T0 com tamanho M0, usando hashing aberto por encadeamento e função de dispersão universal gerada aleatoriamente sobre H(U,M0,P) como descrito acima
3. Repita I vezes:
    1. Gere uma chave aleatória K:=rng.next()%U
    2. Insira a chave K em T0 via T0.set(K) como descrito acima (incluindo o rehashing)
4. Crie uma Hashtable perfeita T1 a partir das chaves em T0 (da primeira à última lista T0[0]...T0[M0=capacity(T0)-1], da esquerda para a direita), como descrito acima
5. Repita Q vezes:
    1. Gere uma chave aleatória K:=rng.next()%U
    2. Consulte a chave K em T1 via T1.get(K)

## Output Specification

Para cada uma da I inserções T0.set(K), numeradas t=0..I-1, caso t % Pi = 0, o programa deve imprimir

```
I K i j
```

onde

- K é o valor da chave,
- i é a posição/lista de T0 em que K foi inserida, e
- j é a posição na lista T0[i] na qual a chave K foi colocada (que corresponde ao número de chaves em T0[i] antes da inserção do K).

Caso K já esteja contida em T0, a inserção não tem efeito, e deve-se fazer i = j = -1

Em seguida, para cada uma da Q consultas T1.get(K), numeradas t=0..Q-1, caso t % Pq = 0, o programa deve imprimir

```
Q K i j
```

onde

- K é o valor da chave
- i é a posição do primeiro nível de T1 em que K foi encontrada, se houver. Caso K não esteja em T1 defina i=-1, e
- j é a posição na tabela do segundo nível T1[i] em que K foi encontrada, i.e. T1[i][j]=K, se houver. Caso K não esteja em T1, defina j=-1.