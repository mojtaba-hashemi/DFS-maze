// Project Name: 	DFS Maze
// Project Author:	Mojtaba Hashemi
// Modified Date:	Monday - 2023 25 September

#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <stack>
#include <fstream>

using namespace std;
#define SIZE 21

// CELL STRUCTURE
struct Cell {
	bool visited;
	bool top_wall;
	bool bot_wall;
	bool left_wall;
	bool right_wall;
	char display;
};

// FUNCTION DECLARATION
void Initialize(Cell Level[][SIZE]);
void ClearScreen();
void Redraw(Cell Level[][SIZE]);
void GenerateMaze(Cell Level[][SIZE], int &posX, int &posY, int &goalX, int goalY);
void Save(Cell Level[][SIZE]);


// MAIN
int main() {
	Cell Level[SIZE][SIZE];
	int posX, posY;
	int goalX, goalY;
	bool game_over = false;


	while(!game_over) {
		system("cls");
		Initialize(Level);
		Redraw(Level);
		GenerateMaze(Level, posX, posY, goalX, goalY);
		Save(Level);

		char input;
		cout << "Create a new maze? (Y)/(N): ";
		cin >> input;


		if((input != 'n') && (input != 'N') && (input != 'y') && (input != 'Y'))
			cout << "Invalid command, please try again" << endl;
		else if ((input == 'n') || (input == 'N')) {
			game_over=true;
			cout << "Good bye!" << endl;
		}
	}

	_getch();
	return 0;
}



// INITIALIZE MAZE
void Initialize(Cell Level[][SIZE]) {
	for(int i=0; i<SIZE; i++) {
		for(int j=0; j<SIZE; j++) {
			Level[i][j].display = '*';
			Level[i][j].visited = false;
			Level[i][j].top_wall = true;
			Level[i][j].bot_wall = true;
			Level[i][j].left_wall = true;
			Level[i][j].right_wall = true;
		}
	}

	for(int i=1; i<SIZE-1; i++) {
		for(int j=1; j<SIZE-1; j++) {
			Level[1][j].top_wall = false;
			Level[SIZE-2][j].bot_wall = false;
			Level[i][1].left_wall =false;
			Level[i][SIZE-2].right_wall = false;
		}
	}
}


// CLEAR SCREEN
void ClearScreen() {
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut,Position);
}




// REDRAW MAZE
void Redraw(Cell Level[][SIZE]) {
	for(int i=0; i<SIZE; i++) {
		cout << endl;
		for (int j=0; j<SIZE; j++) {
			cout << " " << Level[i][j].display;
		}
	}
}




// GENERATE MAZE
void GenerateMaze(Cell Level[][SIZE], int &posX, int &posY, int &goalX, int goalY) {
	srand((unsigned)time(NULL));
	int random;
	int randomX = ((2*rand()+1)%(SIZE-1));
	int randomY = ((2*rand()+1)%(SIZE-1));
	posX = randomX;
	posY = randomY;
	int visitedCells = 1;
	int totalCells = ((SIZE-1)/2)*((SIZE-1)/2);
	int percent;
	stack<int> back_trackX, back_trackY;

	Level[randomY][randomX].display = 'S';
	Level[randomY][randomX].visited = true;

	while(visitedCells < totalCells) {
		if(((Level[randomY-2][randomX].visited == false) && (Level[randomY][randomX].top_wall == true) && (Level[randomY-2][randomX].bot_wall == true)) ||
		        ((Level[randomY+2][randomX].visited == false) && (Level[randomY][randomX].bot_wall == true) && (Level[randomY+2][randomX].top_wall == true)) ||
		        ((Level[randomY][randomX-2].visited == false) && (Level[randomY][randomX].left_wall == true) && (Level[randomY][randomX-2].right_wall == true)) ||
		        ((Level[randomY][randomX+2].visited == false) && (Level[randomY][randomX].right_wall == true) && (Level[randomY][randomX+2].left_wall == true))) {
				
				random = (rand()%4)+1;
				// GO UP
				if((random == 1) && (randomY > 1))
				{
					if(Level[randomY-2][randomX].visited == false)
					{
						Level[randomY-1][randomX].display = ' ';
						Level[randomY-1][randomX].visited = true;
						Level[randomY][randomX].top_wall = false;
						
						back_trackX.push(randomX);
						back_trackY.push(randomY);
						
						randomY -= 2;
						Level[randomY][randomX].visited = true;
						Level[randomY][randomX].display = ' ';
						Level[randomY][randomX].bot_wall = false;
						visitedCells++;
					}
					else
					continue;
				}
				// GO DOWN
				else if ((random == 2) && (randomY < SIZE-2))
				{
					if(Level[randomY+2][randomX].visited == false)
					{
						Level[randomY+1][randomX].display = ' ';
						Level[randomY+1][randomX].visited = true;
						Level[randomY][randomX].bot_wall = false;
						
						back_trackX.push(randomX);
						back_trackY.push(randomY);
						
						randomY += 2;
						Level[randomY][randomX].visited = true;
						Level[randomY][randomX].display = ' ';
						Level[randomY][randomX].top_wall = false;
						visitedCells++;
						
					}
					else
					continue;
				}
				// GO LEFT
				else if ((random == 3) && (randomX >1))
				{
					if(Level[randomY][randomX-2].visited == false)
					{
						Level[randomY][randomX-1].display = ' ';
						Level[randomY][randomX-1].visited = true;
						Level[randomY][randomX].left_wall = false;
						
						back_trackX.push(randomX);
						back_trackY.push(randomY);
						
						randomX -= 2;
						Level[randomY][randomX].visited = true;
						Level[randomY][randomX].display = ' ';
						Level[randomY][randomX].right_wall = false;
						visitedCells++;
						
					}
					else
					continue;
				}
				// GO RIGHT
				else if ((random == 4) && (randomX < SIZE-2))
				{
					if(Level[randomY][randomX+2].visited == false)
					{
						Level[randomY][randomX+1].display = ' ';
						Level[randomY][randomX+1].visited = true;
						Level[randomY][randomX].right_wall = false;
						
						back_trackX.push(randomX);
						back_trackY.push(randomY);
						
						randomX += 2;
						Level[randomY][randomX].visited = true;
						Level[randomY][randomX].display = ' ';
						Level[randomY][randomX].left_wall = false;
						visitedCells++;
						
					}
					else
					continue;
				}
				percent = (visitedCells*100/totalCells*100)/100;
				cout << endl << "       Generating a random maze..." << percent << "%" << endl;	
		}
		else
		{
			randomX = back_trackX.top();
			back_trackX.pop();
			
			randomY = back_trackY.top();
			back_trackY.pop();
		}
		ClearScreen();
		Redraw(Level);
	}
	goalX = randomX;
	goalY = randomY;
	Level[goalY][goalX].display = 'E';
	system("cls");
	ClearScreen();
	Redraw(Level);
	cout << endl << "\a\t		Complete!" << endl;
}


// SAVE MAZE
void Save(Cell Level[][SIZE])
{
	ofstream output;
	char file[20];
	char input;
	cout << endl << "Save Maze? (Y)/(N): ";
	cin >> input;
	
	if ((input == 'y') || (input == 'Y'))
	{
		cout << endl << "Save as: ";
		cin >> file;
		output.open(file);
		for (int i=0; i<SIZE; i++)
		{
			output << endl;
			for(int j=0; j<SIZE; j++)
			{
				output << Level[i][j].display << " ";
			}
		}
		cout << "Maze has been saved to" << "\"" << endl;
		output.close();
	}
}




































































