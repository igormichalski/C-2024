
registro noArvore{
	int chave
	noArvore esq
	noArvore dir
}

registro noFila{
	noArovre ptNoArv
	noFila prox
}


inserirFila()
	

removerFila()


inicializarFila(ptFila, ptraiz)
	ptFila->ptNoArv = ptraiz
	ptFila->prox = NULL

imprimirNivel(ptraiz)
	alocar(ptFila)
	incializarFila(ptFila, ptraiz)
	enquanto(ptFila->ptNoArv != NULL){
		escreva(ptFila->ptNoArv->chave)
		
		se (ptFila->ptNoArv->esq != NULL){
			inserir(ptFila->ptNoArv->esq);
		}
		
		se (ptFila->ptNoArv->dir != NULL){
			inserir(ptFila->ptNoArv->dir);
		}
		
		remover(ptFila->ptNoArv);
	
	}
	
