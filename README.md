================= QuadTree em c, manipulando imagem =================

Forma usadas as bibliotecas: Math, OpenGL, GLUT e SOIL (Simple OpenGL Image Library).

O projeto consiste na criação de uma árvore, onde cada nó terá quatro filhos, para que através dela possamos manipular a imagem.

[EXECUÇÃO]

Para executar o código (em ambiente linux-ubuntu) basta baixar as bibliotecas, executar o arquivo "Makefile" uma vez e depois o comando:

        [gcc arvore.c EstruturasDeDados.c winGL.c -o arvore -lGL -lGLU -lglut -lSOIL -lm]

para gerar o arquivo "arvore" e depois basta rodar o comando:

        [./arvore]

[CÓDIGO]

As lógicas de criação da árvore e manipulação da imagem estão concentradas no arquivo "arvore.c", mas seus TAD (Tipo Abstrato de Dados) são encontrados no arquivo "EstruturasDeDados.h" e seus inicializadores em  "EstruturasDeDados.c".

É importante ressaltar que alguns logs que foram considerados importantes para observação do código estão comentados e os pontos mais relevantes do código estão marcados com um "TODO:"