#ifndef __ARVORE__
#define __ARVORE__ 1
		
void teclado(unsigned char key, int x, int y);

void mouse(int button, int button_state, int x, int y );

void desenho(void);

void bottomLevel();

tQuadrante refrashQuads(int amountQuads, int level, int idQuad);
int nextPoint(int point, int vector, int limit);
int nextLimitPoint(int vector, int point);
void setMaxPoint (int point, int * maxPoint);
void refreshMeasures(int width, int height);
void refreshCurrentVectors(int vector, int idQuad);
tTree * makeTree(tTree * tree, int level);
void showTree(tTree * tree);
void changeTree(int orientation);
void imageTree(tTree * tree);
void paintImage(int p_x, int p_y, int width, int height);
void refrashSettings(int amountQuads, int level, bool isLeft);

#endif	// __ARVORE__

