#include "stack.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <windows.h>
#include <stdlib.h> 
#include <time.h>

using namespace std;

cell m[MAZESIZE][MAZESIZE]; // this is the maze
Stack s;
int p = 0;
//functions:
void print(cell m[][MAZESIZE]);
void generate(int x, int y, bool random);

int main(){
	//initializing walls of all cells
	for (int i = 0; i < MAZESIZE; i++){
		for (int j = 0; j < MAZESIZE; j++){
			m[i][j].down = m[i][j].up = m[i][j].left = m[i][j].right = true;
			m[i][j].visited = false;
		}
	}
	s.create(); //creating stack
	generate(-1, -1, true);

	return 0;
}

void print(cell m[][MAZESIZE]) {
	for (int i = 0; i < MAZESIZE; i++) {
		for (int j = 0; j < MAZESIZE; j++) {
			if (m[i][j].up)
				cout << "+-";
			else cout << "+ ";
		}
		cout << "+" << endl;
		cout << "|";
		for (int j = 0; j < MAZESIZE; j++) {
			if (m[i][j].right)
				cout << m[i][j].val << "|";
			else
				cout << m[i][j].val << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < MAZESIZE; i++)
	{
		if (m[MAZESIZE - 1][i].down)
			cout << "+-";
	}
	cout << "+" << endl;
}

void generate(int x, int y, bool random){
	bool f1 = false;
	if (x < 0 || y < 0) random = true;
	srand((unsigned)time(NULL));

	if (random){ //if we are selecting a new random cell
		while (true){
			x = rand() % MAZESIZE; y = rand() % MAZESIZE;
			if (s.counter == MAZESIZE*MAZESIZE) return;
			if (!m[y][x].visited) break;
		}
	}
	m[y][x].val = '0' + p; m[y][x].visited = true;

	system("cls");//print after the current cell marked
	print(m);


	//finding available neighbours
	int neighbour[4] = { 1, 1, 1, 1 }; //1 means not visited and selectable neighbour
	if (x <= 0 || m[y][x - 1].visited) neighbour[0] = 0; //0 means border or visited
	if (y <= 0 || m[y - 1][x].visited) neighbour[2] = 0;
	if (x >= MAZESIZE - 1 || m[y][x + 1].visited) neighbour[1] = 0;
	if (y >= MAZESIZE - 1 || m[y + 1][x].visited) neighbour[3] = 0;
	int z, k = 0;
	for (int i = 0; i < 4; i++)
		k += neighbour[i];

	Sleep(100);

	if (k > 0){ //at least 1 neighbour available
		while (true){
			z = (rand() % 4); //random 0 to 3
			if (neighbour[z] == 1) break;
		} //Choose randomly one of the unvisited neighbours

		DataType *pushc = new DataType; pushc->x = x; pushc->y = y;
		s.push(pushc); //Push the current cell to the stack

		switch (z){ //break the walls and call next function
		case 0:
			m[y][x].left = false;
			m[y][x - 1].right = false;
			generate(x - 1, y, false);
			break;
		case 1:
			m[y][x].right = false;
			m[y][x + 1].left = false;
			generate(x + 1, y, false);
			break;
		case 2:
			m[y][x].up = false;
			m[y - 1][x].down = false;
			generate(x, y - 1, false);
			break;
		case 3:
			m[y][x].down = false;
			m[y + 1][x].up = false;
			generate(x, y + 1, false);
			break;
		}
	}
	else{
		p++;
		if (!s.isempty()){
			DataType n = s.pop();
			while (true){
				int u = 4;
				if (n.x <= 0 || m[n.y][n.x - 1].visited) u--;
				if (n.y <= 0 || m[n.y - 1][n.x].visited) u--;
				if (n.x >= MAZESIZE - 1 || m[n.y][n.x + 1].visited) u--;
				if (n.y >= MAZESIZE - 1 || m[n.y + 1][n.x].visited) u--;
				if (u == 0){
					if (!s.isempty())
						n = s.pop();
					else{
						n.x = -1;
						break;
					}
				}
				else break; //if u >0
			}

			generate(n.x, n.y, false);
		}
		else{
			for (int i = 0; i < MAZESIZE; i++){ //checking if any unvisited cell left
				for (int j = 0; j < MAZESIZE; j++){
					if (m[i][j].visited = false){
						f1 = true; //f1 =true means there are still unvisited cells
						break;//
					} //end if
				} //end for2
			} //end for and checking unvisited cells

			//f1 ? generate(-1, -1, true) : return; //condition ? result_if_true : result_if_false
			if (f1) generate(-1, -1, true);
			else return;
		} //end of else(stack is empty select a random cell)

	} //end of else(no neighbours available case)
} //end of gen function
