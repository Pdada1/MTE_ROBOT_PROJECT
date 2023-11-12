void handrailAlgo(); //pain
<<<<<<< Updated upstream
void searchEnds(int &startCellX, int &startCellY, int &goalCellX, int &goalCellY); //find start/end of maze (Charlene)
void readMaze(); //this is fairly straightforward, use moveToCell (Ximena)
void moveToCell(int &currentCellX, int &currentCellY, int nextCellX, int nextCellY); //move from current to goal cell, update current position(Ximena)
//void controlXMotors(int cells); //this is trivial, use moveToCell
void initialize(); //fairly straightforward
bool isValidMove(int currentCellX, int currentCellY, int facingDir); //DONE (Ash)
int findNextMove(int currentCellX, int currentCellY, int facingDir); //DONE (Ash)
void makeNextMove(int currentCellX, int currentCellY, int facingDir); //make next move and update mazeMap

=======
void searchEnds(int &startCellX, int &startCellY, int &goalCellX, int &goalCellY);
void readMaze(); //this is fairly straightforward, use moveToCell, white = 6, black = -1
void moveToCell(int currentCellX, int currentCellY, int moveToCellX, int moveToCellY); //this is fairly straightforward, use controlXMotors()
//update currentCell, move robot
void controlXMotors(int cells); //this is trivial, use moveToCell
void initialize(); //not easy
bool isValidMove(int currentCellX, int currentCellY, int facingDir); //complete
int findNextMove(int currentCellX, int currentCellY, int facingDir, char directions); //complete
void storeNextMove(int currentCellX, int currentCellY, int facingDir);
>>>>>>> Stashed changes
/*
void depthFirstSolve(); //genuine suffering (but also semi-redundant so that makes it worse)
void breadthFirstSolve(); //genuine suffering
*/


const int MAZE_R = 41, MAZE_C = 41, MOTOR_POWER = 30, CELL_TO_ENCODER = 1, VALID_CELL = -1;
int mazeMap[MAZE_R][MAZE_C];

task main()
{
	//initialize();
/*

*/
}

void readMaze()
{
    for (int row = 0; row < MAZE_R; row++)
    {
        for (int col = 0; col < MAZE_C; col++)
        {
            //assume colour sensor is S3; if colour == black
            if(SensorValue[S3] == -1)
            {
                mazeMap[row][col] = -1;
            }
            //the colour is white
            else
            {
                mazeMap[row][col] = 0;
            }

        }
    }
    return;
}

//X-axis is motorA + motorB, Y-axis is motorC, pen is motorD
void moveToCell(int currentCellX, int currentCellY, int nextCellX, int nextCellY)
{
    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorB] = 0; //not sure if this line is necessary
    nMotorEncoder[motorC] = 0;
    int dEncodeX = (nextCellX - currentCellX) * CELL_TO_ENCODER;
    int dEncodeY = (nextCellY - currentCellY) * CELL_TO_ENCODER;
    //put pen down
    motor[motorD] = 100;
    //move the x distance
    motor[motorA] = motor[motorB] = MOTOR_POWER;
    while(nMotorEncoder[motorA] < dEncodeX)
    {}
    motor[motorA] = motor[motorB] 0;
    //move the y distance
    motor[motorC] = MOTOR_POWER;
    while(nMotorEncoder[motorC] < dEncodeY)
    {}
    motor[motorC] = 0;
    //lift the pen
    motor[motorD] = 0;
    //update the current cell coordinate
    currentCellX = nextCellX;
    currentCellY = nextCellY;
    return;
}

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

		//update current position after each move (in the move functions)

	}
}


<<<<<<< Updated upstream
/*
void cellToMotor(int currentCellX, int currentCellY, int nextCellX, int next CellY)
{
	int iEncodeX1 = nMotorEncoder[motorA];
	int iEncodeX2 = nMotorEncoder[motorB];
	int iEncodeY = nMotorEncoder[motorD];
	int dEncodeX = (goalCellX - currentCellX) * CELL_TO_ENCODER;
	int dEncodeY = (goalCellY - currentCellY) * CELL_TO_ENCODER;
}
*/

=======
>>>>>>> Stashed changes

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
	facingDir = (3 + facingDir )%4; //equivalent to (facingDir - 1) %4?
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
	int count = 1;//because constants don't work here??
	if(facingDir == 0 && currentCellY - 1 > 0 && mazeMap[currentCellY - count][currentCellX] == VALID_CELL)
	{
		return true;
	}
	else if(facingDir == 1 && currentCellX + 1 < MAZE_C - 1 && mazeMap[currentCellY][currentCellX + count] == VALID_CELL)
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
