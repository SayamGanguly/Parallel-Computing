#ifndef _Box_h
#define _Box_h

const int NUM_OF_NEIGHBORS = 4;
const char sides[] = {'T','B','L','R'};;

typedef struct {
	char side;
	int	count;
	int* neighbors;
}Neighbor;

typedef struct {
	double boxId, startY, startX, height, width;
	Neighbor neighborList[NUM_OF_NEIGHBORS];
	double dsv;
}Box;

void getBoxes(Box* boxes);
void printBoxes(Box* boxes, int numBoxes);
#endif