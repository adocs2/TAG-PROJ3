Trabalho 3 de grafos

Afonso Dias de Oliveira Conceição Silva - 140055771
Gabriel Nunes Rodrigues Fonseca - 160006597

Compilação: g++ -Wall main.cpp -o main
Executar: ./main

Obs:
Nome do arquivo de leitura está setado dentro do código. Caso queira mudar, mude no código fonte.

Considerações sobre o trabalho:
    Nosso trabalho tomou como foco a preferencia de cada professor, portando a primeira vez que preenchemos as vagas das escolas a gente ignora o que a escola deseja.
    Mas com o andar da execução do emparelhamento, a gente reavalia o preenchimento das vagas tomando como base o que a escola deseja, o que ela tem e o que foi ofertado.

    Esse trabalho foi bem desafiador, tivemos dificuldade no algoritmo de emparelhamento por causa do complexidade do arquivo. 
    (Escolas com uma ou mais vagas, manter a posição do vetor de cada professor pelas habilidades que ele está preenchendo, avaliar se o professor ofertado pode substituir alguém ou não)

    Essas dificuldades consistiam em analisar a quantidade de vagas de cada escola e avaliar se o professor oferecido era melhor ou não que aquele que já estava lá, 
        além de não ter um exemplo de emparelhamento correto para esse problema para fins de comparação da saída. Algumas escolas não conseguiram os professores com as habilidades que queriam, então elas
        acabaram ficando com os professores que a desejavam.

    Decisões do projeto que foram tomadas:
    1) Caso alguma escola ficou sem professor (Aconteceu com a escola 13), a preenchemos com os primeiros professores que estavam livres
    2) Caso a escola não tenha o professor que ela deseja e a oferecem um outro professor que possui a mesma habilidade que o professor que já está lá, 
        elá mantém o professor que já estava lá.