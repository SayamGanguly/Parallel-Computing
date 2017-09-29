#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Box.h"
using namespace std;


void getBoxes(Box* boxes){
	
	int i=0;
	int boxId;
	cin >> boxId;
	while(boxId!=-1){
		boxes[i].boxId = boxId;
		cin >> boxes[i].startY >> boxes[i].startX >> boxes[i].height >> boxes[i].width;
		for(int j=0;j<NUM_OF_NEIGHBORS;j++){
			boxes[i].neighborList[j].side = sides[j];
			int count=0;
			cin >> count;
			boxes[i].neighborList[j].count = count;
			if(count>0){
				int *p = (int*)calloc(count,sizeof(int));
				for(int k=0;k<count;k++){
					cin >> *(p+k);
				}
				boxes[i].neighborList[j].neighbors = p;
			}
		}
		cin >> boxes[i].dsv;
		i++;
		cin >> boxId;
	}
}

void printBoxes(Box* boxes, int numBoxes){
	int i=0;
	while(i<numBoxes){
		cout << boxes[i].boxId << boxes[i].startY << boxes[i].startX << boxes[i].height << boxes[i].width << endl;
		
		for(int j=0;j<NUM_OF_NEIGHBORS;j++){
			cout << boxes[i].neighborList[j].count;
			int *p = boxes[i].neighborList[j].neighbors;
			for(int k=0;k< boxes[i].neighborList[j].count;k++){
				cout << *(p+k);
			}
			cout << endl;
		}
		cout << boxes[i].dsv << endl;
		i++;
	}
}