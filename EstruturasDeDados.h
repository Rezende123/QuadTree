#ifndef __EstruturasDeDados__
#define __EstruturasDeDados__ 1

#define GRAU_ARVORE 2

typedef struct point 	{	int x;
							int y;
						} tPonto;
						
typedef struct	{ 	tPonto	pBase;
					int 	height,width;
					int 	nivel;
					int		cor;
					float	erro;
				} 	tQuadrante;
				
typedef struct tree {
	tQuadrante quadtree;

	struct tree * treeChield[4];
} tTree;

tTree * createTree(tQuadrante quad);
tPonto createPoint(int x, int y);
tQuadrante createQuad(tPonto point, int width, int height, int level);
								
#endif		// __EstruturasDeDados__
