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
				auxPointY, 
				auxPointX,
				amountQuadTree = 0,
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

tQuadrante refrashQuads(int amountQuads) {
	int width = (iWidth/(amountQuads/2));
	int height = (iHeight/(amountQuads/2));

	if (auxPointY >= auxPointX) {
		if (auxPointX >= width) {
			auxPointX = width/2;
		} else {
			auxPointX += (width/2) + auxPointX;
		}
		
		auxPointY += (auxPointY == 0) ? height/2:0;
	} else {
		if (auxPointY > height) {
			auxPointY = height/2;
		} else {
			auxPointY += (height/2) + auxPointY;
		}

		auxPointX += (auxPointX == 0) ? width/2:0;
	}

	printf("\n---- [ POINT_Y ] %d [ POINT_X ] %d ----\n", auxPointY, auxPointX);
	tPonto point = createPoint(auxPointX, auxPointY);
	
	return createQuad(point, width, height, amountQuads/4);
}

tTree * makeTree(tTree * tree, int level) {
	if (level <= 0) return NULL;

	int amountQuads = level*4;
	// printf("\n[ AMOUNT ] %d | [ LEVEL ] %d", amountQuads, level);

	if (tree == NULL) {
		tQuadrante quad = refrashQuads(amountQuads);
		tree = createTree(quad);
		makeTree(tree, level - 1);
		return tree;
	}

	refrashSettings(amountQuads, level);

	if (level == 1 && amountQuadTree > 0) {
		amountQuads = amountQuadTree;
	}
		printf("\n [ QUAD ] %d [ TREE ] %d\n", amountQuads, amountQuadTree);

	for (int j = 0; j < 4; j++) {

		tQuadrante quad = refrashQuads(amountQuads);
		tree->treeChield[j] = createTree(quad);

		// printf("\n[ AMOUNT ] %d | [ LEVEL ] %d", amountQuads, level);

		makeTree(tree->treeChield[j], level - 1);
	}

	return tree;
}

void refrashSettings(int amountQuads, int level) {
	if (level == 1) {
		printf("\n===== [ iHEIGHT ] %d [ iWIDTH ] %d =====\n", iHeight, iWidth);
		auxPointY = auxPointX = 0;
	}
	if (level == 2) {
		amountQuadTree += (amountQuads/2);
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
	
	printf("=========[ LEVEL ] %d=========", tree->quadtree.nivel);
	paintImage(tree->quadtree.pBase.x, tree->quadtree.pBase.y);

	if (tree->quadtree.nivel == 1) return;
	
	for (int j = 0; j < 4; j++) {
		imageTree(tree->treeChield[j]);
	}
	printf("\n");
}

void paintImage(int width, int height) {
	int halfColor = 0;
	printf("\n---- [ HEIGHT ] %d [ WIDTH ] %d ----\n", height, width);
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
	printf("\n [ SHOW TREE ] \n");
	showTree(_tree);
	// imageTree(_tree);
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
		case 'I'	: 	desenha = !desenha;
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