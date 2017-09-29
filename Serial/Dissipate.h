#include "Box.h"

#ifndef _Dissipate_h
#define _Dissipate_h

double getContactDistance(double start1, double len1, double start2, double len2);
double dissipate(Box* boxes, Box* currentBox);
void commitupdates(Box* boxes, double *currentUpdates, int numBoxes);
void processDissipation(Box* boxes, double *maxVal, double *minVal, int numBoxes, double affectRate);

#endif