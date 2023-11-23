void handrailAlgo(); //pain
void searchEnds(int &startCellX, int &startCellY, int &goalCellX, int &goalCellY); //find start/end of maze (Charlene)
void readMaze(); //this is fairly straightforward, use moveToCell (Ximena)
void moveToCell(int &currentCellX, int &currentCellY, int nextCellX, int nextCellY); //move from current to goal cell, update current position(Ximena)
//void controlXMotors(int cells); //this is trivial, use moveToCell
void initialize(); //fairly straightforward
bool isValidMove(int currentCellX, int currentCellY, int facingDir); //DONE (Ash)
int findNextMove(int currentCellX, int currentCellY, int facingDir); //DONE (Ash)
void makeNextMove(int currentCellX, int currentCellY, int facingDir); //make next move and update mazeMap

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

//X-axis is motorA + motorB, Y-axis is motorC, pen is motorD

void moveToCell(int &currentCellX, int &currentCellY, int nextCellX, int nextCellY) //needs to be checked
{
    int iEncodeXA = nMotorEncoder[motorA];
    int iEncodeXB = nMotorEncoder[motorB]; //not sure if this line is necessary
    int iEncodeY = nMotorEncoder[motorC];
    int dEncodeX = (nextCellX - currentCellX) * CELL_TO_ENCODER * 3.54//1.55;constants for first size of maze
    int dEncodeY = (nextCellY - currentCellY) * CELL_TO_ENCODER * 137//61;
    //move the x distance
    if (currentCellX > nextCellX)
    {
    	motor[motorA] = motor[motorB] = MOTOR_POWER; //test to make sure directions are right
        while(nMotorEncoder[motorA] > nextCllX*3.54*CELL_TO_ENCODER)
        {}
    }
    else if (currentCellX < nextCellX)
    {
    	motor[motorA] = motor[motorB] = -MOTOR_POWER;
        while(nMotorEncoder[motorA] < nextCllX*3.54*CELL_TO_ENCODER)
        {}
    }
    motor[motorA] = motor[motorB]=0;
    //move the y distance
    if (currentCellY > nextCellY)
    {
    	motor[motorC] = MOTOR_POWER_Y;
        while(nMotorEncoder[motorA] > nextCllX*137*CELL_TO_ENCODER)
        {}
    }
    else if (currentCellY < nextCellY)
    {
    	motor[motorC] = -MOTOR_POWER_Y;
        while(nMotorEncoder[motorA] < nextCllX*137*CELL_TO_ENCODER)
        {}
    }
// call correct encoder
    motor[motorC] = 0;
    //update the current cell coordinate
    currentCellX = nextCellX;
    currentCellY = nextCellY;
    return;
}


void correctEncoder()
{

}

void handrailAlgo()
{
	//Define solution as a modification of the mazeMap, all 0/1
	//Solution will be realized by sequence of movements from point to point

	//Solve Maze while recording movements
	int currentCellX = 0, currentCellY = 0, startCellX = 0, startCellY = 0, goalCellX = 0, goalCellY = 0;


	//search mazeMap for start and end points
	//searchEnds(startCellX, startCellY, goalCellX, goalCellY);

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
            mazeMap[row][0]= -1;
            mazeMap[row][MAZE_C-1]= -1;
        }
    }

    //search mazeMap for start and end points
	bool top_left = searchEnds();
	if(top_left)
	{
		startCellX=0;
		startCellY=1;
        mazeMap[startCellY][startCellX] = 0;
		goalCellX=MAZE_R-1;
		goalCellY=MAZE_C-2;
        mazeMap[goalCellY][goalCellX]=0;

	}
	else
	{
		startCellX=MAZE_R-2;
		startCellY=0;
        mazeMap[startCellY][startCellX] = 0;
		goalCellX=1;
		goalCellY=MAZE_C-1;
        mazeMap[goalCellY][goalCellX]=0;
	}

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

	{ //assuming this is using left hand rule
	facingDir = (3 + facingDir )%4; //equivalent to (facingDir - 1) %4?
}
	for (int attempts = 0; attempts < 4; attempts++)//only 3 checks needed since otherwise go back

	{
		if(isValidMove(currentCellX, currentCellY, facingDir))
		{
			return facingDir;
		}
		facingDir = (facingDir + 1) % 4;
	}
	return -1;
}

bool isValidMove(int currentCellX, int currentCellY, int facingDir) {
    int count = 1;//because constants don't work here??
    if (facingDir == 0 && currentCellY - 1 > 0 && mazeMap[currentCellY - count][currentCellX] == VALID_CELL)
}

int goalCellValue (int currentCellX, int currentCellY, int facingDir)
{
		int count=1;
    if (facingDir == 0) //check the north cell
    {
        return mazeMap[currentCellY-count][currentCellX];
    }
    else if (facingDir == 1) //check the east cell
    {
        return mazeMap[currentCellY][currentCellX+count];
    }
    else if (facingDir == 2) //check the south cell
    {
        return mazeMap[currentCellY+count][currentCellX];
    }
    else // if (nextDir == 3) check the west cell
    {
        return mazeMap[currentCellY][currentCellX-count];
    }
}

void makeNextMove(int currentCellX, int currentCellY, int facingDir)
{
	//dir 0 is up, 1 is right, 2 is down, 3 is left
	int count = 1;
	int nextDir = findNextMove(currentCellX, currentCellY, facingDir);
	if (nextDir == 0) //if we need to go up
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
