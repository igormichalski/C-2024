//concatenação de duas páginas

função concatenarPaginas(arvoreB, x, i)
    y ← x.filhos[i]
    z ← x.filhos[i+1]
    y.chaves[d-1] ← x.chaves[i]
    
    para j de 0 até z.n-1 faça
        y.chaves[j+d] ← z.chaves[j]
    
    se não é folha(z) então
        para j de 0 até z.n faça
            y.filhos[j+d] ← z.filhos[j]
    
    y.n ← y.n + z.n + 1
    
    para j de i até x.n-1 faça
        x.chaves[j] ← x.chaves[j+1]
    
    para j de i+1 até x.n faça
        x.filhos[j] ← x.filhos[j+1]
    
    x.n ← x.n - 1
    liberar(z)
