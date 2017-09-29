#include "Dissipate.h"
#include "Box.h"
#include <float.h>
#include <string.h>
#include <stdlib.h>

double getContactDistance(double start1, double len1, double start2, double len2){
	double maxStart = start1 > start2 ? start1 :  start2;
	double minEnd = start1+len1 < start2+len2 ? start1+len1 : start2+len2;
	return minEnd - maxStart;
}

double dissipate(Box* boxes, Box* currentBox){
	double boxPerimeter = 2.0 * (currentBox->height + currentBox->width);
	double total = 0.0;
	for(int i=0;i<NUM_OF_NEIGHBORS;i++){
		char side = currentBox->neighborList[i].side;
		if(currentBox->neighborList[i].count == 0){
			
			if(side == sides[0] || side == sides[1])
				total += currentBox->width * currentBox->dsv;
			else
				total += currentBox->height * currentBox->dsv;
		}
		else{
			for(int j=0;j<currentBox->neighborList[i].count;j++){
				Box* currentNeighbor = &boxes[currentBox->neighborList[i].neighbors[j]];
				double contactDistance = 0;
				if(side == sides[0] || side == sides[1])
					contactDistance = getContactDistance(currentBox->startX, currentBox->width, currentNeighbor->startX, currentNeighbor->width);
				else
					contactDistance = getContactDistance(currentBox->startY, currentBox->height, currentNeighbor->startY, currentNeighbor->height);
				total += contactDistance * currentNeighbor->dsv;
			}
		}
	}
	total /= boxPerimeter;
	
	return total;
}

void commitupdates(Box* boxes, double *currentUpdates, int numBoxes){
	for(int i=0;i<numBoxes;i++){
		boxes[i].dsv = currentUpdates[i];
	}
}
void processDissipation(Box* boxes, double *maxVal, double *minVal, int numBoxes, double affectRate){
	double *currentUpdates = (double*)calloc(numBoxes, sizeof(double));
	*minVal = DBL_MAX;
	*maxVal = DBL_MIN;
	for(int i=0;i<numBoxes;i++){
			double total = dissipate(boxes,&boxes[i]);
			currentUpdates[i] = boxes[i].dsv + (total - boxes[i].dsv) * affectRate;
			*minVal = *minVal < currentUpdates[i] ? *minVal : currentUpdates[i];
			*maxVal = *maxVal > currentUpdates[i] ? *maxVal : currentUpdates[i];		
	}
	commitupdates(boxes, currentUpdates, numBoxes);
	free(currentUpdates);
}	