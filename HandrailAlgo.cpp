#include <iostream>
#include <cstdlib>

using namespace std;
void handrailAlgo(int &startCellX, int &startCellY); //pain
void moveToCell(int &currentCellX, int &currentCellY, int nextCellX, int nextCellY); //(Ximena)
bool isValidMove(int currentCellX, int currentCellY, int facingDir); //returns false if given move would go into wall(Ash, done)
void makeNextMove(int &currentCellX, int &currentCellY, int facingDir); //make next move and update mazeMap (char)
void readMaze(); //iterates over maze cells and stores as array,
void initialize(); //initializes robot
int findNextMove(int currentCellX, int currentCellY, int &facingDir); //(done)
void storeNextMove(int currentCellX, int currentCellY, int facingDir); //(pranav)
void modifyMazeMap(int currentCellX, int currentCellY);
bool searchEnds();

const int MAZE_R = 9;
int MAZE_C = 9;
int WALL = -1;
int mazeMap[9][9] = {
        {-1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, 0, 0, 0, 0, 0, 0, 0, 0},
        {-1, 0, -1, -1, -1, -1, -1, 0, -1},
        {-1, 0, 0, 0, -1, 0, -1, 0, -1},
        {-1, 0, -1, -1, -1, 0, 1, 0, -1},
        {-1, 0, -1, 0, 0, 0, -1, 0, -1},
        {-1, 0, -1, 0, 1, 1, -1, 0, -1},
        {0, 0, -1, 0, 0, 0, 0, 0, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1}
};

int main() {

    int startCellX = 0;
    int startCellY = 0;
    handrailAlgo(startCellX, startCellY);

    for(int r = 0; r < MAZE_R; r++)
    {
        for(int c = 0; c < MAZE_C; c++) {
            cout << mazeMap[r][c] << "\t";
        }
        cout << endl;
    }

}

void handrailAlgo(int &startCellX, int &startCellY)
{
	//Define solution as a modification of the mazeMap, all 0/1
	//Solution will be realized by sequence of movements from point to point

	//Solve Maze while recording movements
	int goalCellX = 0, goalCellY = 0, facingDir = 0;
    int cursorCellX = 0, cursorCellY = 0;

	//set ends to black
    for (int row = 0; row < MAZE_R; row++)
    {
        if (row == 0 || row == MAZE_R-1)
        {
            for (int col = 0; col < MAZE_C; col++)
            {
                mazeMap[row][col] = -1;
            }
        }
        else
        {
            mazeMap[row][0] = -1;
            mazeMap[row][MAZE_C-1] = -1;
        }
    }

    //search mazeMap for start and end points
	bool top_left = searchEnds();
	if(top_left)
	{
		startCellX = 1;
		startCellY = 0;
        mazeMap[startCellY][startCellX] = 1;
		goalCellX = MAZE_C-2;
		goalCellY = MAZE_R-1;
        mazeMap[goalCellY][goalCellX]=0;

	}
	else
	{
		startCellX= 0;
		startCellY=MAZE_R-2;
        mazeMap[startCellY][startCellX] = 1;
		goalCellX=MAZE_C-1;
		goalCellY=1;
        mazeMap[goalCellY][goalCellX]=0;
	}

    cout << "start cell: [" <<  startCellY << ", " << startCellX << "]" << endl;
    cout << "goal cell: [" << goalCellY << ", " << goalCellX << "]" << endl;

    cursorCellX = startCellX;
    cursorCellY = startCellY;

	while (cursorCellX != goalCellX || cursorCellY != goalCellY)
	{
		makeNextMove(cursorCellX, cursorCellY, findNextMove(cursorCellX, cursorCellY, facingDir));
        // cout << cursorCellX << "\t" << cursorCellY << endl;
		modifyMazeMap(cursorCellX, cursorCellY);

		//update current position after each move (in the move functions)
	}
}

bool searchEnds() //changed so that it checks the array and not moving the actual track and whatnot
{
    return (mazeMap[0][1] == 0);
}
bool isValidMove(int currentCellX, int currentCellY, int facingDir)//need to flip params
{
    int count = 1;//because constants don't work here??
    if(facingDir == 0 && currentCellY - count >= 0 && mazeMap[currentCellY - count][currentCellX] != WALL)
    {
        return true;
    }
    else if(facingDir == 1 && currentCellX + count <= MAZE_C && mazeMap[currentCellY][currentCellX + count] != WALL)
    {
        return true;
    }
    else if(facingDir == 2 && currentCellY - count <= MAZE_R && mazeMap[currentCellY + count][currentCellX] != WALL)
    {
        return true;
    }
    else if(facingDir == 3 && currentCellX - count >= 0 && mazeMap[currentCellY][currentCellX - count] != WALL)
    {
        return true;
    }
    return false;
}

int findNextMove(int cursorCellX, int cursorCellY, int &facingDir)
{
    facingDir = (3 + facingDir )%4; //equivalent to (facingDir - 1) %4?

    for (int attempts = 0; attempts < 4; attempts++)//only 3 checks needed since otherwise go back
    {
        if(isValidMove(cursorCellX, cursorCellY, facingDir))
        {
            return facingDir;
        }
        facingDir = (facingDir + 1) % 4;
    }
    return -1;
}

void makeNextMove(int &currentCellX, int &currentCellY, int facingDir)
{
    //dir 0 is up, 1 is right, 2 is down, 3 is left
    // int nextDir = findNextMove(currentCellX, currentCellY, &facingDir);
    if (facingDir == 0) //if we need to go up
    {
        // modifyMazeMap(currentCellX, currentCellY);
        currentCellY -= 1;
        // when are we calling move to cell

    }
    else if (facingDir == 1) //if we need to go right
    {
        // modifyMazeMap(currentCellX, currentCellY);
        currentCellX += 1;
    }
    else if (facingDir == 2) //if we need to go down
    {
        // modifyMazeMap(currentCellX, currentCellY);
        currentCellY += 1;
    }
    else if (facingDir == 3) //if we need to go left
    {
        // modifyMazeMap(currentCellX, currentCellY);
        currentCellX -= 1;
    }
}

// y is the rows, x is the cols
bool junctionCheck(int currentCellX, int currentCellY)
{
    int validCells = 0;
    // check if the four girds beside current cell have more than one valid cell
    for(int direction = 0; direction < 4; direction++)
    {
        if(isValidMove(currentCellX, currentCellY, direction % 4 ))
        {
            validCells++;
        }
    }
    if(validCells > 2)
    {
        return true;
    }
    return false;
}

bool checkBlank()
{
    return (mazeMap[0][1]==mazeMap[1][0]);
}

void modifyMazeMap(int currentCellX, int currentCellY)
{
    if (mazeMap[currentCellY][currentCellX] == 0 || junctionCheck(currentCellX, currentCellY))
    {
        mazeMap[currentCellY][currentCellX] = 1;
    }
    else
    {
        mazeMap[currentCellY][currentCellX] = -1;
    }
}