# ASA 24/25 - Projeto 2
**Filipe Oliveira**  
**Número de estudante**: ist1110633

## 📌 Descrição do Projeto  

Este projeto permite analisar o **índice de conectividade de uma rede de metro**, avaliando o **número mínimo de mudanças de linha** necessárias para viajar entre quaisquer duas estações.  

A medida utilizada é o **índice de conectividade do metro** (**mc**), definido como:  
mc = max{ML(e1, e2) | e1, e2 ∈ Metro}
onde **ML(e1, e2)** representa o número mínimo de trocas de linha entre as estações **e1** e **e2**.  

---

## 🎯 Definição do Problema  

A rede de metro é representada como um **multigrafo não-dirigido**, onde:  
- **Cada vértice** representa uma estação.  
- **Cada aresta** representa uma ligação direta entre duas estações numa determinada linha.  

### 📌 **Entrada**  
O programa recebe um ficheiro com:  
1. **Uma linha com três inteiros**:  
   - `n` → Número de estações (`n ≥ 2`).  
   - `m` → Número de ligações (`m ≥ 0`).  
   - `l` → Número de linhas de metro (`l ≥ 0`).  
2. **`m` linhas**, cada uma contendo três inteiros `x, y, l`:  
   - `x` e `y` representam duas estações conectadas diretamente.  
   - `l` indica a linha de metro que as liga.  

### 📌 **Saída**  
O programa imprime um único número inteiro **`s`**, que representa o **índice de conectividade da rede**.  
- Se **não for necessária nenhuma troca de linha**, imprime **`0`**.  
- Se existir **pelo menos um par de estações sem ligação**, imprime **`-1`**.  

---

## 📄 Relatório  

O ficheiro [relatorio-ASA2425P2.pdf](./relatorio-ASA2425P2.pdf) contém informações detalhadas sobre este projeto, incluindo:  
- **Descrição da solução**: raciocínio utilizado  
- **Análise teórica da solução**: complexidade de cada etapa da solução e complexidade total  
- **Avaliação experimental dos resultados**: gráfico do tempo em função da complexidade teórica prevista  

---

📄 **Nota:** Para mais exemplos e explicações detalhadas, consultar [enunciado-ASA2425P2.pdf](./enunciado-ASA2425P2.pdf)
