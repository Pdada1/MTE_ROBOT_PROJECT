void handrailAlgo(); //pain
void searchEnds(int &startCellX, int &startCellY, int &goalCellX, int &goalCellY);
void readMaze(); //this is fairly straightforward
void moveToCell(int currentCellX, int currentCellY, int moveToCellX, int moveToCellY); //this is fairly straightforward, use controlXMotors()
void controlXMotors(); //this is trivial
void initialize(); //not easy

/*
void depthFirstSolve();
void breadthFirstSolve();
*/


const int MAZE_R = 41, MAZE_C = 41, MOTOR_POWER = 30, CELL_TO_ENCODER = 1;
int mazeMap[MAZE_R][MAZE_C];
task main()
{
	initialize();
/*

*/
}
/*
X-axis is motorA + motorB, Y-axis is motorC, pen is motorD

void handrailAlgo()
{
	//Define solution as a modification of the mazeMap, all 0/1
	//Solution will be realized by sequence of movements from point to point

	//Solve Maze while recording movements
	int currentCellX = 0, currentCellY = 0, startCellX = 0, startCellY = 0, goalCellX = 0, goalCellY = 0;

	//search mazeMap for start and end points
	searchEnds(startCellX, startCellY, goalCellX, goalCellY);

	int facing = 0;
	char directions[4] = {E, N, W, S};
	/*
	E is [row][col-1]
	N is [row-1][col]
	W is [row][col+1]
	S is [row+1][col]

	*check to make sure entries are valid (between 0 and 40)*
	*/

	//pick a start and end (doesnt matter tbh)
	while (currentCellX != goalCellX || currentCellY != goalCellY)
	{

		//add current position to array of solution points (append?)

		//turn left, check forward
		//(else turn right, check forward)x3
		//step forward if forward is valid, else error

		//update current position after each move (in the move functions)

	}

	simpleSolArray = simplify(solArray);
	//this function will look through solArray, and cut sequences where the robot ends up back at the same point

	return simpleSolArray;

	or alternately copy the map array and modify?
}


void cellToMotor(int currentCellX, int currentCellY, int goalCellX, int goalCellY)
{
	int iEncodeX = nmotorEncoder[motorA]
	int iEncodeY = nmotorEncoder[motorA]
	int dEncodeX = (goalCellX - currentCellX) * 1 //this needs to be a constant
}
*/


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
