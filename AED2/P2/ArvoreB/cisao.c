função cindirPagina(arvoreB, x, i)
    z ← novo NóB()
    y ← x.filhos[i]
    z.folha ← y.folha
    z.n ← d - 1

    para j de 1 até d - 1
        z.chaves[j] ← y.chaves[j + d]

    se não y.folha
        para j de 1 até d
            z.filhos[j] ← y.filhos[j + d]

    y.n ← d - 1

    para j de x.n + 1 até i + 1, passo -1
        x.filhos[j + 1] ← x.filhos[j]

    x.filhos[i + 1] ← z

    para j de x.n até i, passo -1
        x.chaves[j + 1] ← x.chaves[j]

    x.chaves[i] ← y.chaves[d]
    x.n ← x.n + 1
