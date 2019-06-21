#ifndef __ARVORE__
#define __ARVORE__ 1
		
void teclado(unsigned char key, int x, int y);

void mouse(int button, int button_state, int x, int y );

void desenho(void);

void bottomLevel();

tQuadrante refrashQuads(int amountQuads, int level);
int nextPoint(int point, int vector, int limit);
int nextLimitPoint(int vector, int point);
void setMaxPoint (int point, int * maxPoint);
void refrashMeasures(int width, int height);
tTree * makeTree(tTree * tree, int level);
void showTree(tTree * tree);
void changeTree(int orientation);
void paintImage(int width, int height);
void refrashSettings(int amountQuads, int level);

#endif	// __ARVORE__

