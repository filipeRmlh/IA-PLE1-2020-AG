# Trabalho de IA - PLE1 - 2020 - Algoritmo Genético - Sudoku
**Aluno**: Filipe José Maciel Ramalho. **DRE**: 114032785

## O trabalho
O projeto consiste em um algoritmo genético que resolva o problema do Sudoku.

Seu funcionamento é configurável por parâmetros descritos no arquivo [readme.md](readme.md).

A função objetivo (`Fn`) configurada é definida como sendo o número de células mutáveis (ou seja, não fixas) corretas dentro das linhas, somado às corretas dentro das colunas, somado às corretas dentro dos blocos.
A definição de "correta" é dada como sendo: O valor da célula a ser testada não está se repetindo dentro do escopo em teste (linha, coluna ou bloco / região) em que ela se encontra.

>O máximo global da função `Fn` é o número de células mutáveis presentes no sudoku vezes 3.

Como `Fn` pode assumir o valor 0, é necessário aplicar uma translação em 1 unidade para suprimir este comportamento indesejado para o A.G. com a função `Gn` (Gn = Fn+1). 
Não é necessária nenhuma outra alteração na função objetivo, uma vez que ela já é de maximização.

### O formato do sudoku

Como a função de Fn precisa ter conhecimento dos blocos, colunas e linhas para ser executada, foi escolhido uma biblioteca que pudesse lidar bem com estes parâmetros de maneira abstrata, 
mantendo a caracteristica vetorial dos dados internamente (assim, um reshape fica bem barato), por isso escolhi a biblioteca Armadillo ([http://arma.sourceforge.net/](http://arma.sourceforge.net/)). 
(Poderia fazer estas abstrações, mas achei que uma biblioteca pouparia meu trabalho).

Alem desta abstração da biblioteca, resolvi encapsular os dados em uma classe que contivesse funções úteis para o sudoku, como o preenchimento aleatório ou o print com cores.
Então, minha população é constituída como sendo um vetor de elementos da classe `Sudoku`, que por sua vêz contém os conteúdos da matrizes.

## Resultados

Para o sudoku 9x9, em todos os testes, não houve alcance do máximo global, com e sem elitismo.
Para todas as execuções feitas, os links para os resultados são os seguintes:

- a) tamanho da população = 100, probabilidade de crossover = 80%, número 
     de pontos de crossover = 1, probabilidade de mutação = 3%, número de gerações =100
     
    * Sem elitismo: [Link para resultado](results/a-3x3-sem-elitismo.md)
    
    * Com elitismo: [Link para resultado](results/a-3x3-com-elitismo.md)
     
 - b) tamanho da população = 100, probabilidade de crossover = 80%, número de pontos de crossover = 3, probabilidade de mutação = 3%, número de gerações =100 
    
    * Sem elitismo: [Link para resultado](results/b-3x3-sem-elitismo.md)
        
    * Com elitismo: [Link para resultado](results/b-3x3-com-elitismo.md)
    
 - c) tamanho da população = 100, probabilidade de crossover = 80%, número de pontos de crossover = 3, probabilidade de mutação = 15%, número de gerações =100 
    
    * Sem elitismo: [Link para resultado](results/c-3x3-sem-elitismo.md)
    
    * Com elitismo: [Link para resultado](results/c-3x3-com-elitismo.md)

Para um tabuleiro 4x4, os links dos resultados são os seguintes (em alguns casos, alcançando o máximo global).
- a) tamanho da população = 100, probabilidade de crossover = 80%, número 
     de pontos de crossover = 1, probabilidade de mutação = 3%, número de gerações =100
     
    * Sem elitismo: [Link para resultado](results/a-2x2-sem-elitismo.md)
    
    * Com elitismo: [Link para resultado](results/a-2x2-com-elitismo.md)
     
 - b) tamanho da população = 100, probabilidade de crossover = 80%, número de pontos de crossover = 3, probabilidade de mutação = 3%, número de gerações =100 
    
    * Sem elitismo: [Link para resultado](results/b-2x2-sem-elitismo.md)
        
    * Com elitismo: [Link para resultado](results/b-2x2-com-elitismo.md)
    
 - c) tamanho da população = 100, probabilidade de crossover = 80%, número de pontos de crossover = 3, probabilidade de mutação = 15%, número de gerações =100 
    
    * Sem elitismo: [Link para resultado](results/c-2x2-sem-elitismo.md)
    
    * Com elitismo: [Link para resultado](results/c-2x2-com-elitismo.md)
    
## Conclusão

Podemos verificar, com os experimentos que o elitismo é muito importante para não perder resultados importantes ao longo da execução do algoritmo.
Um outro ponto a ser considerado é a média das populações finais e iniciais, que tem uma diferença bem pequena entre si, e as vezes,
a media final tem valor inferior à inicial. Os Tabuleiros 9x9 e 4x4 foram testados outras vezes com outras funções, como por exemplo:
* Fn = "número de células únicas simultaneamente na linha coluna e bloco";
* Fn = "para cada célula 'c', somatorio de: (número de elementos iguais a c na linha onde c está + número de elementos iguais a c na coluna onde c está + número de elementos iguais a c no bloco onde c está)";

Mas a melhor função realmente foi a função definida atualmente.
Com os exercícios a,b e c sem elitismo, também notei um aumento bem pequeno na instabilidade dos resultados no a e b em relação ao c, acho que para ter uma avaliação melhor dessa intuição, seria necessário o cálculo do desvio padrão,
que se mostra inviável devido ao volume de dados em processamento.

