#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <time.h>
#include "Box.h"
#include "Dissipate.h"
using namespace std;

#define absolute(a) \
	((a)>0 ? (a) : -1 * (a))

const double NS_PER_US = 1000;

int numBoxes, numRows, numCols;

double affectRate;
double epsilon;

void getDimensions(){
	cin >> numBoxes;
	cin >> numRows;
	cin >> numCols;
}

int main(int argc, char* argv[]){
	double minVal = DBL_MAX, maxVal = DBL_MIN;
	time_t time_start, time_end;
	struct timespec start, end;
	double diff;
	
	affectRate = atof(argv[1]);
	epsilon = atof(argv[2]);

	getDimensions();

	Box* boxes = (Box*)calloc(numBoxes, sizeof(Box));	
		
	getBoxes(boxes);
	
	int i=0;
	
	clock_t clock_start = clock();
	time(&time_start);
	clock_gettime(CLOCK_REALTIME,& start);
	
	
	do{
		//cout << "Iteration " << i++ << endl;
		processDissipation(boxes, &maxVal, &minVal, numBoxes, affectRate);
		i++;
	}while(absolute(maxVal-minVal)>epsilon*maxVal);
	
	clock_t clock_end = clock();
	time(&time_end);
	clock_gettime(CLOCK_REALTIME,& end);
	diff = (double)( ((end.tv_sec - start.tv_sec)*CLOCKS_PER_SEC) + ((end.tv_nsec -start.tv_nsec)/NS_PER_US) );
	
	cout << "**********************************************************" << endl;
	printf("dissipation converged in %d iterations,\n\twith max DSV = %f and min DSV = %f \n\taffect rate = %f\t\tepsilon = %f\n",i,maxVal,minVal,affectRate,epsilon);
	cout << endl << endl << "elapsed convergence loop time	(clock) : " << clock_end - clock_start << endl;
	cout << "elapsed convergence loop time	(time) : " << difftime(time_end,time_start) << endl;
	cout << "elapsed convergence loop time	(chrono) : " << diff << endl;
	cout << "**********************************************************" << endl;
	
	//printBoxes(boxes, numBoxes);
}