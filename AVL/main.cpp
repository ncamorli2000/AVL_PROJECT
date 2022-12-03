
// 
// 
// the included display function is not my work. It was
// borrowed from https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
//
#include "AVL.h"
#include <iostream>
using namespace std;


int main()
{

	//testing AVL tree implementation using RAND function
	// this encorporates all rotation scenarios

	AVL RandomAVL;

	srand((unsigned)time(0));
	int randomNumber;
	for (int index = 4; index < 20; index++) {
		randomNumber = (rand() % 60) + 1;
		RandomAVL.insert(randomNumber);
	}

	RandomAVL.display();

	if (RandomAVL.isBalanced())
		cout << " Great! Out AVL tree is balanced! " << endl;
	else {
		cout << " AVL tree is NOT balanced.... " << endl;
	}
	
	if (RandomAVL.isSorted())
		cout << " Great! Out AVL tree is sorted ! " << endl;
	else {
		cout << " AVL tree is NOT sorted.... " << endl;
	}

	cout << endl;

	RandomAVL.insert(0);
	RandomAVL.remove(0);
	RandomAVL.inOrder();



}

