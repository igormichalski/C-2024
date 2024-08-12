//Calcula o cambo de balanciamento de uma arvore AVL

calcularAlturaENivelar(ptraiz)
    se ptraiz é nulo
        retorne 0
    
    alturaEsq ← calcularAlturaENivelar(ptraiz.esq)
    alturaDir ← calcularAlturaENivelar(ptraiz.dir)
    
    ptraiz.bal ← alturaDir - alturaEsq
    
    retorne máximo(alturaEsq, alturaDir) + 1


máximo(a, b)
    se a > b
        retorne a
    senão
        retorne b


calcularAlturaENivelar(ptraiz)
