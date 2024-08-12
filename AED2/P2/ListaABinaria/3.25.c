//Determina o numero de nos de uma subarvore v

contarNosSubarvore(no)
    se no == NULL
        retorne 0
    conteEsq = conteDir = 0
    // Contar o próprio nó + nós das subárvores esquerda e direita
    conteEsq = contarNosSubarvore(no->esq)
    conteDir = contarNosSubarvore(no->dir)
    
    retorne 1 + conteEsq + conteDir
