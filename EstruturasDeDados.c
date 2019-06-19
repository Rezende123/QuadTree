#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "EstruturasDeDados.h"

tTree * createTree(tQuadrante quad) {
    tTree * tree = malloc(sizeof (tTree));

    tree->quadtree = quad;

    return tree;
}

tPonto createPoint(int x, int y) {
    tPonto * point = malloc(sizeof (tPonto));
    
    point->x = x;
    point->y = y;

    return *point;
}

tQuadrante createQuad(tPonto point, int width, int height, int level) {
    tQuadrante * quad = malloc(sizeof (tQuadrante));

    quad->pBase = point;
    quad->width = width;
    quad->height = height;
    quad->nivel = level;

    return *quad;
}