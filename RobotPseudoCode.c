void handrailAlgo(); //pain
//void searchEnds(int &startCellX, int &startCellY, int &goalCellX, int &goalCellY); //find start/end of maze (Charlene) * Surprise, we don't actually need this - sorry :(
void moveToCell(int &currentCellX, int &currentCellY, int nextCellX, int nextCellY); //move from current to goal cell, update current position(Ximena)
//void controlXMotors(int cells); //this is trivial, use moveToCell
bool isValidMove(int currentCellX, int currentCellY, int facingDir); //DONE (Ash) *
void makeNextMove(int &currentCellX, int &currentCellY, int facingDir); //make next move and update mazeMap (char)
void readMaze(); //this is fairly straightforward, use moveToCell, white == 6, black == -1
//update currentCell, move robot
void initialize(); //not easy
int findNextMove(int currentCellX, int currentCellY, int facingDir); //complete *
void storeNextMove(int currentCellX, int currentCellY, int facingDir); //(pranav)

void swapToPen(); //move pen tip to (0, 0) and then put pen down

void drawMaze();
/*
void depthFirstSolve(); //genuine suffering (but also semi-redundant so that makes it worse)
void breadthFirstSolve(); //genuine suffering
*/


const int MAZE_R = 41, MAZE_C = 41, MOTOR_POWER = 30, CELL_TO_ENCODER = 1, VALID_CELL = 1;
int mazeMap[MAZE_R][MAZE_C];

//start is [1][0], end is [MAZE_R - 1][MAZE_C]

task main()
{
	/*
	//order of function initializations
	initialize();
	moveToCell(); //need to differentiate between moving the pen and colour sensor
	searchEnds();
	readMaze();
	//start timer
	handrailAlgo();
	//end timer


	//draw maze
*/
}

void searchEnds(int &startCellX, int &startCellY, int &goalCellX, int &goalCellY, int &currentCellX, int &currentCellY) //i think we need to take a look at this
{
	//only scan the upper row from left to right
	//assume we start at the upper left corner and the colour sensor is already at the 1st tile

	nMotorEncoder[motorA] = 0;

	//move directly to the 2nd last colomn from the right
	moveToCell(currentCellX, currentCellY, 0, 1); //move one down from starting

	if(SensorValue[S1] == 6) //if we detect the white start tile
		{
			startCellX = 0; //in the 2nd last colomn from the left
			startCellY = 1; //in the 1st row from the top
			goalCellX = MAZE_C-1; //in the 1st column from the right
			goalCellY = MAZE_R-2; //in the 2nd row from the bottom
		}
	else
		{
			startCellX = MAZE_C-2; //in the 1st colomn from the left
			startCellY = 0; //in the 2nd row from the top
			goalCellX = 1; //in the 1st colomn from the right
			goalCellY = MAZE_R-1; //in the 2nd row fron the bottom
		}
	//returns back to the initial position
	moveToCell(currentCellX, currentCellY, 0, 0);
}

void readMaze()
{
	for (int col = 0; col < MAZE_C; col++)
    for (int row = 0; row < MAZE_R; row++)
    {
        //scans from the left to the right at even rows
        if(row % 2 == 0)
        {
            for (int col = 0; col < MAZE_C; col++)
            {
                //assume colour sensor is S3; if colour == black
                if(SensorValue[S1] == 6)
                {
                    mazeMap[row][col] = -1;
                }
                    //the colour is white
                else
                {
                    mazeMap[row][col] = 0;
                }
            }
            //move one cell to the right
            moveToCell(col, row, col + 1, row);
        }
        //scans from the right to the left at even rows
        else
        {
            for (int col = MAZE_C - 1; col >= 0 ; col--)
            {
                if(SensorValue[S1] == -1)
                {
                    mazeMap[row][col] = -1;
                }
                else
                {
                    mazeMap[row][col] = 0;
                }
            }
            moveToCell(col, row, col - 1, row);
        }
        moveToCell(col, row, col, row + 1);
    }
    return;
}

//X-axis is motorA + motorB, Y-axis is motorC, pen is motorD
void moveToCell(int &currentCellX, int &currentCellY, int nextCellX, int nextCellY) //needs to be checked
{
    int iEncodeXA = nMotorEncoder[motorA];
    int iEncodeXB = nMotorEncoder[motorB]; //not sure if this line is necessary
    int iEncodeY = nMotorEncoder[motorC];
    int dEncodeX = (nextCellX - currentCellX) * CELL_TO_ENCODER;
    int dEncodeY = (nextCellY - currentCellY) * CELL_TO_ENCODER;
    //move the x distance
    if (currentCellX > nextCellX)
    {
    	motor[motorA] = motor[motorB] = MOTOR_POWER; //test to make sure directions are right
    }
    else
    {
    	motor[motorA] = motor[motorB] = -MOTOR_POWER;
    }
    while(abs(nMotorEncoder[motorA] - iEncodeXA) < abs(dEncodeX))
    {}
    motor[motorA] = motor[motorB]=0;
    //move the y distance
    if (currentCellY > nextCellY)
    {
    	motor[motorC] = MOTOR_POWER;
    }
    else
    {
    	motor[motorC] = -MOTOR_POWER;
    }
    while(abs(nMotorEncoder[motorC] - iEncodeY < abs(dEncodeY))
    {}
    motor[motorC] = 0;
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


void initialize()
{
	//sensor and motor encoder initialization and reset
	const int MOTOR_CONFIG_PWR=10;
	SensorType[S1] = sensorEV3_Color;
	wait1Msec(10);
	SensorType[S2] = sensorEV3_Touch;
	wait1Msec(10);
	SensorMode[S1] = modeEV3Color_Color;
	wait1Msec(10);
	nMotorEncoder[motorA]=nMotorEncoder[motorB]=nMotorEncoder[motorC]=nMotorEncoder[motorD]=0;

	//fills out 2d bit array with default value of 0
	for (int row = 0; row < MAZE_R; row++)
	{
		for (int col = 0; col < MAZE_C; col++)
		{
			mazeMap[row][col] = 0;
		}
	}
	//displays configuration intstructions for user to position print head on first cell at 0,0
	displayString(2, "Use the buttons");
	displayString(3, "to align");
	displayString(4,"the print head");
	displayString(5, "with the top left");
	displayString(6,"cell in the maze");

	bool button_Pressed=false;
	//allows the user to move the print head by using the buttons
	while(!getButtonPress(buttonEnter))
	{
		displayString(8,"Clr Sensor Value = %d", SensorValue[S1]);
		while(getButtonPress(buttonUp))
		{
			button_Pressed=true;
			motor[motorD]=MOTOR_CONFIG_PWR;
			displayString(8,"Clr Sensor Value = %d", SensorValue[S1]);
		}
			while(getButtonPress(buttonDown))
		{
			button_Pressed=true;
			motor[motorD]=-MOTOR_CONFIG_PWR;
			displayString(8,"Clr Sensor Value = %d", SensorValue[S1]);
		}
			while(getButtonPress(buttonLeft))
		{
			button_Pressed=true;
			motor[motorA]=motor[motorC]=-MOTOR_CONFIG_PWR;
			displayString(8,"Clr Sensor Value = %d", SensorValue[S1]);
		}
			while(getButtonPress(buttonRight))
		{
			button_Pressed=true;
			motor[motorA]=motor[motorC]=MOTOR_CONFIG_PWR;
			displayString(8,"Clr Sensor Value = %d", SensorValue[S1]);
		}
		if(button_Pressed)
		{
			motor[motorA]=motor[motorB]=motor[motorC]=motor[motorD]=0;
			button_Pressed=false;
		}

	}
	return;
}

bool isValidMove(int currentCellX, int currentCellY, int facingDir)
{
	int count = 1;//because constants don't work here??
	if(facingDir == 0 && currentCellY - 1 > 0 && abs(mazeMap[currentCellY - count][currentCellX]) == VALID_CELL)
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

int findNextMove(int currentCellX, int currentCellY, int facingDir)
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

void makeNextMove(int currentCellX, int currentCellY, int facingDir)
{
	//dir 0 is up, 1 is right, 2 is down, 3 is left
	int count = 1;
	int nextDir = findNextMove(currentCellX, currentCellY, facingDir);
	if (nextDir == 0) //if we need to go up
	{
		mazeMap[currentCellY-count][currentCellX] = 0;
		currentCellY -= 1;
	}
	else if (nextDir == 1) //if we need to go right
	{
		mazeMap[currentCellY][currentCellX+count] = 0;
		currentCellX += 1;
	}
	else if (nextDir == 2) //if we need to go down
	{
		mazeMap[currentCellY+count][currentCellX] = 0;
		currentCellY += 1;
	}
	else if (nextDir == 3) //if we need to go left
	{
		mazeMap[currentCellY][currentCellX-count] = 0;
		currentCellX -= 1;
	}
}


void storeNextMove(int currentCellX, int currentCellY, int facingDir)
{



}
