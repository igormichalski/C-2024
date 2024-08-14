//Faça um algoritmo para imprimir em ordem crescente todas as chaves armazenadas em uma árvore B de ordem d apontada por ptraiz.

função imprimirEmOrdem(ptraiz)
    se ptraiz é nulo
        retorne

    para i de 1 até ptraiz.n
        // Percorrer a subárvore à esquerda do nó
        imprimirEmOrdem(ptraiz.filhos[i])
        
        // Imprimir a chave atual
        escreva(ptraiz.chaves[i])

    // Percorrer a subárvore à direita do último filho
    imprimirEmOrdem(ptraiz.filhos[ptraiz.n + 1])
fim função
