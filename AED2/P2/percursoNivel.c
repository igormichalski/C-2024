
registro noArvore{
	int chave
	noArvore esq
	noArvore dir
}

registro noFila{
	noArovre ptNoArv
	noFila prox
}


inserirFila(fila, no)
	aux = fila
	
	alocar(novo)
	novo->ptNoArv = no
	novo->prox = NULL
	
	se (fila != NULL)
		enquanto(aux->prox != NULL)
			aux = aux->prox
		aux->prox = novo
	senao
		fila = novo

removerFila(fila)
	aux = fila
	fila = fila->prox
	desaloca(aux)

inicializarFila(ptFila, ptraiz)
	inserirFila(ptFila, ptraiz)

imprimirNivel(ptraiz)
	alocar(ptFila)
	inicializarFila(ptFila, ptraiz)
	enquanto(ptFila != NULL){
		escreva(ptFila->ptNoArv->chave)
		
		se (ptFila->ptNoArv->esq != NULL){
			inserir(ptFila, ptFila->ptNoArv->esq);
		}
		
		se (ptFila->ptNoArv->dir != NULL){
			inserir(ptFila, ptFila->ptNoArv->dir);
		}
		
		remover(ptFila);
	
	}
	
