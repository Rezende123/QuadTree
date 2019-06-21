#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include <GL/glut.h>

#include "EstruturasDeDados.h"
#include "winGL.h"
#include "arvore.h"
		
unsigned char* 	image = NULL;	// image file
int 			iHeight, 
				iWidth,
				currentWidth = 0,
				currentHeight = 0,
				auxPointY, 
				auxPointX,
				maxPointY = 0, 
				maxPointX = 0,
				hasNextPointX = true,
				iLevel = 0;

bool 			desenha = false;

tTree * _tree;

// ***********************************************
// ******                                   ******
// ***********************************************

void desenhaArvore() {

	printf("Aqui eu vou desenhar a arvore\n");
	
	// rotina que deve ser implementada para visualizacao da arvore
	// utilize a rotina desenhaQuadrante(p0, p1, cor)
	// fornecendo os pontos inicial e final do quadrante e a sua cor
	// funcao do valor do pixel ou da regiao que voce quer desenhar
	
	changeTree(1);
	// tPonto p0, p1;
	 
	// p0.x = p0.y = 0;

	// p1.x = iWidth/2;
	// p1.y = iHeight/2;	
	// desenhaQuadrante(p0, p1, 64);

	// p0.x = iWidth;
	// p0.y = iHeight;
	// desenhaQuadrante(p0, p1, 222);

}
	
/// ***********************************************************************
/// ** 
/// ***********************************************************************

tQuadrante refrashQuads(int amountQuads, int level) {
	int width = (iWidth/(amountQuads/2));
	int height = (iHeight/(amountQuads/2));

	// if (level == 1) printf("\n||||| [ HEIGHT ] %d [ WIDTH ] %d |||||\n", height, width);

	if (hasNextPointX) {
		refrashCurrentVectors(hasNextPointX, width);
		auxPointX = nextPoint(auxPointX, width, currentWidth);

		auxPointY += (auxPointY == 0) ? currentHeight/2:0;
		
		hasNextPointX = false;
	} else {
		refrashCurrentVectors(hasNextPointX, height);
		auxPointY = nextPoint(auxPointY, height, currentHeight);

		auxPointX += (auxPointX == 0) ? currentWidth/2:0;
		
		hasNextPointX = true;
	}
	// refrashMeasures(width, height);

	// if (level == 1) printf("\n---- [ LIMIT_Y ] %d [ LIMIT_X ] %d ----\n", currentHeight, currentWidth);
	if (level == 1) printf("\n---- [ POINT_Y ] %d [ POINT_X ] %d ----\n", auxPointY, auxPointX);
	
	tPonto point = createPoint(auxPointX, auxPointY);
	
	return createQuad(point, width, height, level);
}

int nextPoint(int point, int vector, int limit) {
	int addition = limit/2;
	// printf("\t\t\t\t\t [POINT] %d [ADD] %d [LIMIT] %d", point, addition, limit);

	if (point == 0) {
		point = addition;
	} else if ((point + addition) > limit) {
		point = addition/2;
	} else {
		point += addition;
	}

	return point;
}


void refrashCurrentVectors(bool hasNextPointX, int vector) {
	if (currentWidth == (vector*2) && currentHeight == (vector*2)) {
		currentHeight /= 2;
	} else
	if (hasNextPointX) {
		currentWidth += vector;
	} else {
		currentHeight += vector;
	}
}

tTree * makeTree(tTree * tree, int level) {
	if (level <= 0) return NULL;

	int amountQuads = pow(2,iLevel);
	// printf("\n[ AMOUNT ] %d | [ LEVEL ] %d", amountQuads, level);

	if (tree == NULL) {
		tQuadrante quad = refrashQuads(amountQuads, level);
		tree = createTree(quad);
		makeTree(tree, level - 1);
		return tree;
	}

	refrashSettings(amountQuads, level);

	// printf("\n [ QUAD ] %d [ TREE ] %d\n", amountQuads, amountQuadTree);

	for (int j = 0; j < 4; j++) {
		printf("\n [%d]", j);
		tQuadrante quad = refrashQuads(amountQuads, level);
		tree->treeChield[j] = createTree(quad);

		makeTree(tree->treeChield[j], level - 1);
	}

	return tree;
}

void refrashSettings(int amountQuads, int level) {
	if (level == 1) {
		printf("\n===== [ iHEIGHT ] %d [ iWIDTH ] %d =====\n", iHeight, iWidth);
		// printf("\n[ AMOUNT ] %d | [ LEVEL ] %d", amountQuads, level);
	} else
	if (level == 2) {
		currentHeight = currentWidth = auxPointY = auxPointX = 0;
	}
}

void showTree(tTree * tree) {
	if (tree == NULL) return;
	
	printf("[ LEVEL ] %d", tree->quadtree.nivel);

	if (tree->quadtree.nivel == 1) return;
	
	for (int j = 0; j < 4; j++) {
		showTree(tree->treeChield[j]);
	}
	printf("\n");
}

void imageTree(tTree * tree) {
	if (tree == NULL) return;
	
	printf("\n=========[ PAINT LEVEL ] %d=========", tree->quadtree.nivel);
	paintImage(tree->quadtree.pBase.x, tree->quadtree.pBase.y);

	if (tree->quadtree.nivel == 1) return;
	
	for (int j = 0; j < 4; j++) {
		imageTree(tree->treeChield[j]);
	}
	printf("\n");
}

void paintImage(int width, int height) {
	int halfColor = 0;
	printf("\n---- [ POINT_Y ] %d [ POINT_X ] %d ----\n", height, width);
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			int color = image[j*height+i*width];

			halfColor += color;
		}
	}
	halfColor /= (width*height);
	printf("\n--- [ HALF ] %d ----\n", halfColor);

	tPonto point_1, point_2;

	point_1 = createPoint(iWidth - width, iHeight - height);
	point_2 = createPoint(iWidth - (2 * width), iHeight - (2 * height));

	desenhaQuadrante(point_1, point_2, halfColor);
}

void changeTree(int orientation) {
	if (orientation == 0) {
		--iLevel;
	} else {
		++iLevel;
	}

	if (iLevel < 0) {
		iLevel = 0;
	}
	
	printf("\n\t BOTTOM LEVEL %d\n", iLevel);
	
	_tree = NULL;
	_tree = makeTree(_tree, iLevel);
	// printf("\n [ SHOW TREE ] \n");
	// showTree(_tree);
	imageTree(_tree);
}

void montaArvore() {
	
	printf("Aqui eu vou montar a arvore\n");
	
	// codifique aqui a sua rotina de montagem da arvore 
	changeTree(0);
}
	
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void teclado(unsigned char key, int x, int y) {

	switch (key) {
		case 27		: 	exit(0);
						break;				
		case 'q'	:
		case 'Q'	: 	montaArvore();
						break;				
		case 'i'	:
		case 'I'	: 	changeTree(1);// desenha = !desenha;
						break;		
		case 'd'	:
		case 'D'	:	desenha = !desenha;
						break;
		}
	glutPostRedisplay();
}
		
/// ***********************************************************************
/// **
/// ***********************************************************************

void mouse(int button, int button_state, int x, int y ) {

	if 	(button_state == GLUT_DOWN ) {
		switch (button) {
			
			case GLUT_LEFT_BUTTON	: 	printf("botao esquerdo?\n");
										break;
	
			case GLUT_RIGHT_BUTTON	:	printf("botao direito?\n");
										break;
			}
		glutPostRedisplay();
		}
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void desenho(void) {

    glClear (GL_COLOR_BUFFER_BIT); 
    
    glColor3f (1.0, 1.0, 1.0);
    
    if (desenha)
    	desenhaArvore();
    else
    	glDrawPixels( iWidth, iHeight, GL_LUMINANCE, GL_UNSIGNED_BYTE, image );
   	
    glutSwapBuffers ();
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

int main(int argc, char** argv) {
	
	char* filename = "images/lena.png";

    if (argc > 1)
		filename = argv[1];

	image = leImagem(filename);
			
	criaJanela(argc, argv);

    initOpenGL();
    
    initEventos();
    
    return 0;   
}
