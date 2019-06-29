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
				hasNextPointX,
				resetMeasures = true,
				iLevel = 0;

bool 			desenha = false;

tTree * _tree;

// ***********************************************
// ******                                   ******
// ***********************************************

void desenhaArvore() {

	if (_tree != NULL) {
		system("clear");
		imageTree(_tree);
	} else {
		printf(" NO HAVE TREE ");
	}
	
}
	
/// ***********************************************************************
/// ** 
/// ***********************************************************************

// DEFINIÇÃO DOS PONTOS DE UM QUADRANTE
tQuadrante refreshQuads(int amountQuads, int level, int idQuad) {
	int width = (iWidth/(amountQuads/2));
	int height = (iHeight/(amountQuads/2));

	if (hasNextPointX) {
		// printf(" [X] ");
		refreshCurrentVectors(width, idQuad);
		if (idQuad == 0 && auxPointY != 0) {
			auxPointY -= height;
		} 
		auxPointX = nextPoint(auxPointX, width, currentWidth);
	} else {
		// printf(" [Y] ");
		refreshCurrentVectors(height, idQuad);
		if (idQuad == 0 && auxPointX != 0) {
			auxPointX -= width;
		} 
		auxPointY = nextPoint(auxPointY, height, currentHeight);
	}

	// if (level == 1) printf("\n---- [ HEIGHT ] %d [ WIDTH ] %d ----\n", height, width);
	if (level == 1) printf("\n---- [ LIMIT_Y ] %d [ LIMIT_X ] %d ----\n", currentHeight, currentWidth);
	if (level == 1) printf("\n---- [ POINT_Y ] %d [ POINT_X ] %d ----\n", auxPointY, auxPointX);
	
	tPonto point = createPoint(auxPointX, auxPointY);
	
	return createQuad(point, width, height, level);
}

int nextPoint(int point, int vector, int currentLocation) {
	// printf("\t\t\t\t\t [POINT] %d [VECTOR] %d [CurrentLocation] %d", point, vector,currentLocation);
	point = currentLocation - vector;

	if (point < 0) {
		point = 0;
	}

	return point;
}

void refreshCurrentVectors(int vector, int idQuad) {
	if (idQuad == 3) {
		currentHeight /= 2;
		hasNextPointX = true; 
	} else
	if (hasNextPointX) {
		currentWidth += vector;
		hasNextPointX = false;
	} else {
		currentHeight += vector;
		hasNextPointX = true;
	}
}

tTree * makeTree(tTree * tree, int level) {
	if (level <= 0) return NULL;

	int amountQuads = pow(2,iLevel);
	// printf("\n[ AMOUNT ] %d | [ LEVEL ] %d", amountQuads, level);

	if (tree == NULL) {
		tQuadrante quad = refreshQuads(amountQuads, level, 0);
		tree = createTree(quad);
		makeTree(tree, level - 1);
		return tree;
	}

	refrashSettings(amountQuads, level, false);

	// printf("\n [ QUAD ] %d [ TREE ] %d\n", amountQuads, amountQuadTree);

	for (int j = 0; j < 4; j++) {
		printf("\n [%d]", j);
		tQuadrante quad = refreshQuads(amountQuads, level, j);
		tree->treeChield[j] = createTree(quad);

		makeTree(tree->treeChield[j], level - 1);
	}

	refrashSettings(amountQuads, level, true);

	return tree;
}

void refrashSettings(int amountQuads, int level, bool isLeft) {
	if (level == 1) {
		if (isLeft) {
			// printf(" [REINIT] ");	
			hasNextPointX = false;
		} else {
			printf("\n===== [ iHEIGHT ] %d [ iWIDTH ] %d =====\n", iHeight, iWidth);
			// printf("\n[ AMOUNT ] %d | [ LEVEL ] %d", amountQuads, level);
		}
	} else
	if (level == 2) {
		auxPointY = auxPointX = 0;
		if (resetMeasures) {
			// printf(" [INIT] ");
			currentHeight = currentWidth = 0;
			resetMeasures = false;
			hasNextPointX = false;
		}
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

// TODO: VISUALIZAÇÃO POR NÍVEL
void imageTree(tTree * tree) {
	if (tree == NULL) return;
	
	printf("\n========= [ PAINT LEVEL ] %d =========", tree->quadtree.nivel);
	paintImage(& tree->quadtree);

	if (tree->quadtree.nivel == 1) return;
	
	for (int j = 0; j < 4; j++) {
		imageTree(tree->treeChield[j]);
	}
	printf("\n");
}

// TODO: EXIBIÇÃO DO ERRO E DA COR DO QUADRANTE
void paintImage(tQuadrante * quad) {
	int p_x = quad->pBase.x;
	int p_y = quad->pBase.y;
	int width = quad->width;
	int height = quad->height;

	defineHalfColorAndError(quad);

	printf("\n--- [ HALF ] %d ----\n", quad->cor);
	printf("\n--- [ ERROR ] %f ----\n", quad->erro);

	tPonto point_1, point_2;

	point_1 = createPoint(p_x, p_y);
	point_2 = createPoint(p_x + width, p_y + height);

	desenhaQuadrante(point_1, point_2, quad->cor);
}

// TODO: CÁLCULO DA COR POR QUADRANTE
// TODO: CÁLCULO DO ERRO
void defineHalfColorAndError(tQuadrante * quad) {
	int p_x = quad->pBase.x;
	int p_y = quad->pBase.y;
	int width = quad->width;
	int height = quad->height;
	int halfColor = 0;
	float error = 0;

	printf("\n---- [ POINT_Y ] %d [ POINT_X ] %d ----\n", p_y, p_x);
	printf("\n---- [ HEIGHT ] %d [ WIDTH ] %d ----\n", height, width);

	for(int z = 0; z < 2; z++) {
		for(int i = p_x; i < width; i++) {
			for(int j = p_y; j < height; j++) {
				int color = image[j*height+i*width];

				if (z == 0) {
					halfColor += color;
				} else {
					error += abs(halfColor - color);
				}
			}
		}

		if (z == 0) {
			halfColor /= (width*height);
		} else {
			error /= (width*height);
		}
	}
	quad->cor = halfColor;
	quad->erro = error;
}

// TODO: DEFINIÇÃO DO NÍVEL DA ÁRVORE 
void changeTree(int orientation) {
	system("clear");
	switch(orientation) {
		case 0: --iLevel;
			break;
		case 1: ++iLevel;
			break;
	}

	if (iLevel < 0) {
		iLevel = 0;
	}
	
	printf("\n\t BOTTOM LEVEL %d\n", iLevel);
	
	resetMeasures = true;

	_tree = NULL;
	_tree = makeTree(_tree, iLevel);
	// printf("\n [ SHOW TREE ] \n");
	// showTree(_tree);
	// imageTree(_tree);
}

void montaArvore() {
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
		case 'Q'	: 	changeTree(0);
						break;				
		case 'i'	:
		case 'I'	: 	changeTree(1);
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
