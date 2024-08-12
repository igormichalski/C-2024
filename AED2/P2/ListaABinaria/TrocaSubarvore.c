No* EncontrarNo(No* raiz, int chave) {
    if (raiz == NULL) {
        return NULL;
    }
    if (raiz->data == chave) {
        return raiz;
    } else if (chave < raiz->data) {
        return EncontrarNo(raiz->esquerda, chave);
    } else {
        return EncontrarNo(raiz->direita, chave);
    }
}

// Função auxiliar para trocar dados e subárvores de dois nós
void TrocaDadosENos(No* no1, No* no2) {
    if (no1 != NULL && no2 != NULL) {
		int tempData = no1->data;
		No *tempEsquerda = no1->esquerda;
		No *tempDireita = no1->direita;

		no1->data = no2->data;
		no1->esquerda = no2->esquerda;
		no1->direita = no2->direita;

		no2->data = tempData;
		no2->esquerda = tempEsquerda;
		no2->direita = tempDireita;
	}
}

// Função para trocar subárvores
void TrocaSubarvores(No* ptraiz, int x, int y) {
    No *noX, *noY;

    noX = EncontrarNo(ptraiz, x);
    noY = EncontrarNo(ptraiz, y);

    TrocaDadosENos(noX, noY);
    
}
