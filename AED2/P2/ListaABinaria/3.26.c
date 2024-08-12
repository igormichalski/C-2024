//Buscar o pai de um no ou chave

buscarPai(x,pt)
	se pt=NULL entao
		"a raiz nao tem pai"
	senao
		se (pt->esq->chave = x) ou (pt->dir->chave = x) entao
			return pt

		//Esquerda
		pai = buscarPai(x, pt->esq)
    		se pai != NULL
        		retorne pai
    
    		//Direita
    		retorne buscarPai(x, pt->dir)
