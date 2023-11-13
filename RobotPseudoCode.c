void handrailAlgo(); //pain
void searchEnds(int &startCellX, int &startCellY, int &goalCellX, int &goalCellY); //find start/end of maze (Charlene)
void moveToCell(int &currentCellX, int &currentCellY, int nextCellX, int nextCellY); //move from current to goal cell, update current position(Ximena)
//void controlXMotors(int cells); //this is trivial, use moveToCell
bool isValidMove(int currentCellX, int currentCellY, int facingDir); //DONE (Ash)
void makeNextMove(int currentCellX, int currentCellY, int facingDir); //make next move and update mazeMap
void readMaze(); //this is fairly straightforward, use moveToCell, white = 6, black = -1
//update currentCell, move robot
void initialize(); //not easy
int findNextMove(int currentCellX, int currentCellY, int facingDir, char directions); //complete
void storeNextMove(int currentCellX, int currentCellY, int facingDir);
/*
void depthFirstSolve(); //genuine suffering (but also semi-redundant so that makes it worse)
void breadthFirstSolve(); //genuine suffering
*/


const int MAZE_R = 41, MAZE_C = 41, MOTOR_POWER = 30, CELL_TO_ENCODER = 1, VALID_CELL = -1;
int mazeMap[MAZE_R][MAZE_C];

task main()
{
	initialize();
	readMaze();
/*

*/
}


void searchEnds(int &startCellX, int &startCellY, int &goalCellX, int &goalCellY)
{
	//only scan the upper row from left to right
	//assume we start at the upper left corner and the colour sensor is already at the 1st tile (we can edit this if we need to)
	
	//while we move the robot to the right:
	nMotorEncoder[motorA] = 0; //is this needed?
	const int MOVE_TO_END = 40;
	
	motor[motorA] = motor[motorB] = MOTOR_POWER;
    	while(nMotorEncoder[motorA] < MOVE_TO_END*CELL_TO_ENCODER)
    		{
		if(SensorValue [S1] == 6) //if we detect the white start tile
			{
				startCellX = MAZE_C-2; //in the 2nd last colomn from the right
				startCellY = 0; //in the 1st row from the top
				goalCellX = 1; //in the 2nd colomn from the left
				goalCellY = MAZE_C-1; //in the 1st row from the bottom
			}
		else
			{
				startCellX = 0; //in the 1st colomn from the left
				startCellY = 1; //in the 2nd row from the top
				goalCellX = MAZE_C-1; //in the 1st colomn from the right
				goalCellY = MAZE_R-2; //in the 2nd last row fron the bottom
			}
		}
   	 motor[motorA] = motor[motorB]=0;

	//returns back to the initial position
	motor[motorA] = motor[motorB] = -1*MOTOR_POWER;
	while(nMotorEncoder[motorA] > 0)
	{}
	motor[motorA] = motor[motorB] = 0;
}



void readMaze()
{
    for (int row = 0; row < MAZE_R; row++)
    {
        for (int col = 0; col < MAZE_C; col++)
        {
            //assume colour sensor is S3; if colour == black
            if(SensorValue[S1] == -1)
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
    motor[motorA] = motor[motorB]=0;
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
	SensorType[S1]=sensorEV3_Color;
	SensorType[S2]=sensorEV3_Touch;
	SensorMode[S1]=modeEV3Color_Color;
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
	displayString(3, "to move the align");
	displayString(4,"the print head");
	displayString(4, "with the top left");
	displayString(5,"cell in the maze");

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
