# Trabalho de IA-PLE1-2020 - Algoritmo Genético
Aluno: Filipe José Maciel Ramalho DRE: 14032785

Projeto construído com Jetbrains CLION

> O relatório se encontra no arquivo [relatório.md](relatorio.md)

Já existe uma versão pré-compilada no projeto, que funciona em computadores linux, para executá-la, siga as instruções na seção "[Como executar](#como-executar)", porém se houver alguma dificuldade, siga o guia abaixo na seção "[Como compilar](#como-compilar)".

> Supõe se que o diretório corrente no terminal é o diretório raiz do projeto.

## Como compilar
* Instale o g++ (testado com gcc versão 8.3.0). (Testado em "c++ standard 14")

* Instale o CMake (testado com versão 3.17)

* Instale Lapack e Blas no seu computador (testado com versão 3.8.0-2).  
    Para S.O.'s baseados em Debian/Ubuntu. basta rodar o comando abaixo.
    ```bash
    apt install liblapack-dev && apt install libblas-dev
    ``` 
  Para outros Linux use o gerenciador de pacotes padrão ou o synaptics.
  
* Execute o comando abaixo para compilar:
    ```bash
    cmake --build ./cmake-build-debug --target all -- -j 9
    ```
    
## Como executar
* Entre na pasta onde o executável se encontra
    ```
    cd cmake-build-debug
    ```
 
* Execute o executável gerado
    ```
    ./IA_AG_PLE1_2020 <lotes> <gerações> <tambloco> <tampop> <ncuts> <nmuts> <mutprob> <crossprob> <elitismo> <debug>
    ```

Onde:
* lotes = número de experimentos a serem feitos;
* gerações = número de gerações por experimento;
* tambloco = tamanho de uma região/bloco do tabuleiro escrito como uma string "nxm".  
    Exemplo: "3x3";
* tampop = tamanho da população;
* ncuts = número de cortes para crossover;
* nmuts = número de células a sofrerem mutação;
* mutprob = probabilidade de mutação (entre 0 e 1);
* crossprob = probabilidade de crossover (entre 0 e 1);
* elitismo = com elitismo (*y*) ou não (*n*);
* debug = mostrar sudokus (*y*) ou não (*n*);

Caso não seja passado nenhum argumento, os default serão usados. Caso sejam passados um número incorreto de argumentos, o programa lançará uma exceção.

Exemplo a:
```
./IA_AG_PLE1_2020 10 100 "2x2" 100 3 7 0.03 0.80 y n
```

Exemplo b:
```
./IA_AG_PLE1_2020 10 100 "2x2" 100 3 7 0.03 0.80 y y
```

Exemplo do output de um dos experimentos de uma execução com debug ativado.

![Output com debug ativado](./assets/Exemplo%20Output.png)

## Teste Individual das funções do AG
Para testar cada uma das funções individualmente, edite o arquivo `Tester.h` entre os comentários 
`Code Here. Replace the code below as you wish.` e `End`. Já existe um código de exemplo nele, que pode ser substituído sem problemas.

As funções estão no arquivo AG.h que já está incluído no arquivo de teste.
Cada uma das funções de AG.h estão descritas através de comentários descritivos.

Após finalizar o código no arquivo de teste, compile o projeto novamente e rode o comando abaixo.

```
./IA_AG_PLE1_2020 test
```