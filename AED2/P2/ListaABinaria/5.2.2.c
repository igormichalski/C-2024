//retorna o nível do nó na árvore.

encontrarNivel(raiz, no, nivelAtual)
    se raiz == NULL
        retorne -1 // Nó não encontrado ou árvore vazia
    
    se raiz == no
        retorne nivelAtual // Encontrou o nó, retornar o nível atual
    
    // Verificar subárvore esquerda
    nivelEsq = encontrarNivel(raiz->esq, no, nivelAtual + 1)
    se nivelEsq != -1
        retorne nivelEsq // Nó encontrado na subárvore esquerda
    
    // Verificar subárvore direita
    nivelDir = encontrarNivel(raiz->dir, no, nivelAtual + 1)
    retorne nivelDir // Retorna -1 se o nó não for encontrado na subárvore direita


nivel = encontrarNivel(raiz, no, 0)
