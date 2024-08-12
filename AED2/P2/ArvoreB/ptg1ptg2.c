// Função que verifica se é possível redistribuir chaves entre duas páginas
boolean Verifica(Pagina* ptpag1, Pagina* ptpag2) {
    // Verifica se ptpag1 e ptpag2 têm o mesmo pai
    if (ptpag1->pai != ptpag2->pai) {
        return false;
    }

    // Obtém o número de chaves em cada página
    int numChaves1 = ptpag1->numChaves;
    int numChaves2 = ptpag2->numChaves;

    // Calcula o número mínimo de chaves necessárias em cada página após redistribuição
    int minChaves = d - 1;

    // Verifica se a soma das chaves nas duas páginas é suficiente
    if ((numChaves1 + numChaves2) >= 2 * minChaves + 1) {
        return true;
    } else {
        return false;
    }
}
