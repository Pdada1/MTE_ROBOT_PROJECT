void handrailAlgo(); //pain
void searchEnds(int &startCellX, int &startCellY, int &goalCellX, int &goalCellY);
void readMaze(); //this is fairly straightforward, use moveToCell
void moveToCell(int currentCellX, int currentCellY, int moveToCellX, int moveToCellY); //this is fairly straightforward, use controlXMotors()
void controlXMotors(); //this is trivial, use moveToCell
void initialize(); //not easy
bool isValidMove(int currentCellX, int currentCellY, int facingDir);
int findNextMove(int currentCellX, int currentCellY, int facingDir, char directions);

/*
void depthFirstSolve(); //genuine suffering (but also semi-redundant so that makes it workse)
void breadthFirstSolve(); //genuine suffering
*/


const int MAZE_R = 41, MAZE_C = 41, MOTOR_POWER = 30, CELL_TO_ENCODER = 1, VALID_CELL = 1;
int mazeMap[MAZE_R][MAZE_C];

task main()
{
	//initialize();
/*

*/
}

//X-axis is motorA + motorB, Y-axis is motorC, pen is motorD

void handrailAlgo()
{
	//Define solution as a modification of the mazeMap, all 0/1
	//Solution will be realized by sequence of movements from point to point

	//Solve Maze while recording movements
	int currentCellX = 0, currentCellY = 0, startCellX = 0, startCellY = 0, goalCellX = 0, goalCellY = 0;

	//search mazeMap for start and end points
	//searchEnds(startCellX, startCellY, goalCellX, goalCellY);
	char dir[4] = {'N', 'E', 'S', 'W'};
	/*
	E is [row][col-1]
	N is [row-1][col]
	W is [row][col+1]
	S is [row+1][col]

	*check to make sure entries are valid (between 0 and 40)*
	*/

	//pick a start and end (doesnt matter tbh)
	int facingDir = 0; //Tells us which direction we most recently went
	while (currentCellX != goalCellX || currentCellY != goalCellY)
	{
		//makeNextMove(findNextMove())

		//modify mazeMap

		//turn left, check forward
		//(else turn right, check forward)x3
		//step forward if forward is valid, else error

		//update current position after each move (in the move functions)

	}
}


void cellToMotor(int currentCellX, int currentCellY, int goalCellX, int goalCellY)
{
	int iEncodeX = nMotorEncoder[motorA];
	int iEncodeY = nMotorEncoder[motorA];
	int dEncodeX = (goalCellX - currentCellX) * CELL_TO_ENCODER;
	int dEncodeY = (goalCellY - currentCellY) * CELL_TO_ENCODER;
}



/*
Inputs: EV3 Buttons, Colour Sensor, Ultrasonic or Touch Sensor, Motor Encoders
Outputs: 3x motor (x-axis, z-axis, pen)
*/

void initialMaze()
{
	for (int row = 0; row < MAZE_R; row++)
	{
		for (int col = 0; col < MAZE_C; col++)
		{
			mazeMap[row][col] = 0;
		}
	}
	return;
}

int findNextMove(int currentCellX, int currentCellY, int facingDir, char directions)
{
	facingDir = (3 + facingDir )%4;
	for (int attempts = 0; attempts < 4; attempts++)
	{
		if(isValidMove(currentCellX, currentCellY, facingDir))
		{
			return facingDir;
		}
		facingDir = (facingDir + 1) % 4;
	}
	return -1;
}

bool isValidMove(int currentCellX, int currentCellY, int facingDir)
{
	int count=1;
	if(facingDir == 0 && currentCellY - 1 > 0 && mazeMap[currentCellY -count][currentCellX] == VALID_CELL)
	{
		return true;
	}
	else if(facingDir == 1 && currentCellX + 1 < MAZE_C - 1 && mazeMap[currentCellY][currentCellX + 1] == VALID_CELL)
	{
		return true;
	}
	else if(facingDir == 2 && currentCellY + 1 < MAZE_R - 1 && mazeMap[currentCellY + count][currentCellX] == VALID_CELL)
	{
		return true;
	}
	else if(facingDir == 3 && currentCellX - 1 > 0 && mazeMap[currentCellY][currentCellX - count] == VALID_CELL)
	{
		return true;
	}
	return false;
}
