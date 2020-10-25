# Trabalho de IA - PLE1 - 2020 - Algoritmo Genético - Sudoku
**Aluno**: Filipe José Maciel Ramalho. **DRE**: 114032785

## O trabalho
O projeto consiste em um algoritmo genético que resolva o problema do Sudoku.

Seu funcionamento é configurável por parâmetros descritos no arquivo [readme.md](readme.md).

A função objetivo (`Fn`) configurada é definida como sendo o número de células mutáveis (ou seja, não fixas) corretas dentro do sudoku.
A definição de "correta" é dada como sendo: O valor da célula a ser testada não está se repetindo nem na linha, nem na coluna e nem no bloco (ou região) em que ela se encontra.

>O máximo global da função `Fn` é o número de células mutáveis presentes no sudoku.

Como `Fn` pode assumir o valor 0, é necessário aplicar uma translação em 1 unidade para suprimir este comportamento indesejado para o A.G. com a função `Gn` (Gn = Fn+1). 
Não é necessária nenhuma outra alteração na função objetivo, uma vez que ela já é de maximização.

### O formato do sudoku

Como a função de Fn precisa ter conhecimento dos blocos, colunas e linhas para ser executada, foi escolhido uma biblioteca que pudesse lidar bem com estes parâmetros de maneira abstrata, 
mantendo a caracteristica vetorial dos dados internamente (assim, um reshape fica bem barato), por isso escolhi a biblioteca Armadillo ([http://arma.sourceforge.net/](http://arma.sourceforge.net/)). 
(Poderia fazer estas abstrações, mas achei que uma biblioteca pouparia meu trabalho).

Alem desta abstração da biblioteca, resolvi encapsular os dados em uma classe que contivesse funções úteis para o sudoku, como o preenchimento aleatório ou o print com cores.
Então, minha população é constituída como sendo um vetor de elementos da classe `Sudoku`, que por sua vêz contém os conteúdos da matrizes.

## Resultados

Os resultados infelizmente não foram muito animadores. 
Para o sudoku 9x9, em todos os testes não houve nenhuma melhora em nenhum ponto, com e sem elitismo.
Para todas as execuções (a, b e c) os resultados foram os seguintes:

* Gn Start: 1
* Gn End: 1
* Mean Start: 1
* Mean End: 1

Para um tabuleiro 4x4, no entanto, os resultados foram os seguintes.
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