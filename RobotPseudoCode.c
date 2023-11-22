/* Code convetions
Motors for x direction: A,B
Motors for y direction: C
Motors for pen: D
Color Sensor Port: S1
Touch Sensor Port: S2
Passage=0
Wall=-1
Traversed Passage =1
if we double traverse set back to 0
Using left hand rule for the algo

*/


void handrailAlgo(); //pain
//void searchEnds(int &startCellX, int &startCellY, int &goalCellX, int &goalCellY); //find start/end of maze (Charlene)
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


const int MAZE_R = 9, MAZE_C = 9, MOTOR_POWER = 10,	MOTOR_POWER_Y = 100, CELL_TO_ENCODER = 180/(PI*2.75), VALID_CELL = 0;
int mazeMap[MAZE_R][MAZE_C];
string penDirection[MAZE_R*MAZE_C];

//start is [1][0], end is [MAZE_R - 1][MAZE_C]

task main()
{

	//order of function initializations
	initialize();
	int x=0, y=0;
	//moveToCell(x,y,8,8);
	//searchEnds();
	//readMaze();
	//start timer
	//handrailAlgo();
	//end timer
	swapToPen();

	//draw maze

}

bool searchEnds() //changed so that it checks the array and not moving the actual track and whatnot
{
	return (mazeMap[1][0]==0);
}

void readMaze()
{
    int end_col = 0;
    for (int row = 0; row < MAZE_R;)
    {
        //scans from the left to the right at even rows
        if(row % 2 == 0)
        {
            for (int col = 0; col < MAZE_C-1;)
            {
                //assume colour sensor is S3; if colour == white
                if(SensorValue[S1] == 6)
                {
                    mazeMap[row][col] = 0;
                }
                    //the colour is black
                else
                {
                    mazeMap[row][col] = -1;
                }

                displayString(col, "%d ",SensorValue[S1]);
                //move one cell to the right
            		moveToCell(col, row, col + 1, row);
            		wait1Msec(300);
            }
            end_col = MAZE_C - 1;
        }
        //scans from the right to the left at even rows

        else
        {
            for (int col = MAZE_C - 1; col > 0 ;)
            {
                if(SensorValue[S1] > 15 /*== 6*/)
                {
                    mazeMap[row][col] = 0;
                }
                else
                {
                    mazeMap[row][col] = -1;
                }
                displayString(col, "%d ",SensorValue[S1]);
                moveToCell(col, row, col - 1, row);
               	wait1Msec(300);
            }
            end_col = 0;
        }

        if(row != MAZE_C - 1)
        {
        	moveToCell(end_col, row, end_col, row + 1);
        }
        else
        {
            row++;
        }
        wait1Msec(500);
    }
    return;
}

//X-axis is motorA + motorB, Y-axis is motorC, pen is motorD
void moveToCell(int &currentCellX, int &currentCellY, int nextCellX, int nextCellY) //needs to be checked
{
    int iEncodeXA = nMotorEncoder[motorA];
    int iEncodeXB = nMotorEncoder[motorB]; //not sure if this line is necessary
    int iEncodeY = nMotorEncoder[motorC];
    int dEncodeX = (nextCellX - currentCellX) * CELL_TO_ENCODER*3.55//1.55;constants for first size of maze
    int dEncodeY = (nextCellY - currentCellY) * CELL_TO_ENCODER*140//61;
    //move the x distance
    if (currentCellX > nextCellX)
    {
    	motor[motorA] = motor[motorB] = MOTOR_POWER; //test to make sure directions are right
    }
    else if (currentCellX < nextCellX)
    {
    	motor[motorA] = motor[motorB] = -MOTOR_POWER;
    }
    while(abs(nMotorEncoder[motorA] - iEncodeXA) < abs(dEncodeX))
    {}
    motor[motorA] = motor[motorB]=0;
    //move the y distance
    if (currentCellY > nextCellY)
    {
    	motor[motorC] = MOTOR_POWER_Y;
    }
    else if (currentCellY < nextCellY)
    {
    	motor[motorC] = -MOTOR_POWER_Y;
    }
    while(abs(nMotorEncoder[motorC] - iEncodeY) < abs(dEncodeY))
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
	bool top_left = searchEnds();
	if(top_left)
	{
		startCellX=1;
		startCellY=0;
		goalCellX=MAZE_R-2;
		goalCellY=MAZE_C-1;
	}
	else
	{
		startCellX=MAZE_R-1;
		startCellY=1;
		goalCellX=0;
		goalCellY=MAZE_C-2;
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
	//int facingDir = 0; //Tells us which direction we most recently went//might not need
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
	SensorMode[S1] = modeEV3Color_Reflected;
	wait1Msec(10);
	const int MTR_ENC_LIMIT_MAG=650;
	const int XMOTOR_CONFIG_PWR=10;
	const int YMOTOR_CONFIG_PWR=100;
	SensorType[S1]=sensorEV3_Color;
	SensorType[S2]=sensorEV3_Touch;
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
		displayString(9, "Motor Encoder value =%d", nMotorEncoder[motorA]);
		while(getButtonPress(buttonUp))
		{
			button_Pressed=true;
			motor[motorC]=YMOTOR_CONFIG_PWR;
			displayString(8,"Clr Sensor Value = %d", SensorValue[S1]);
			displayString(9, "Motor Encoder value =%d", nMotorEncoder[motorA]);
		}
			while(getButtonPress(buttonDown))
		{
			button_Pressed=true;
			motor[motorC]=-YMOTOR_CONFIG_PWR;
			displayString(8,"Clr Sensor Value = %d", SensorValue[S1]);
			displayString(9, "Motor Encoder value =%d", nMotorEncoder[motorA]);
		}
			while(getButtonPress(buttonLeft))
		{
			button_Pressed=true;
			motor[motorA]=motor[motorB]=-XMOTOR_CONFIG_PWR;
			displayString(8,"Clr Sensor Value = %d", SensorValue[S1]);
		}
			while(getButtonPress(buttonRight))
		{
			button_Pressed=true;
			motor[motorA]=motor[motorB]=XMOTOR_CONFIG_PWR;
			displayString(8,"Clr Sensor Value = %d", SensorValue[S1]);
		}
		if(button_Pressed)
		{
			motor[motorA]=motor[motorB]=motor[motorC]=motor[motorD]=0;
			button_Pressed=false;
		}

	}
	nMotorEncoder[motorA]=nMotorEncoder[motorB]=nMotorEncoder[motorC]=nMotorEncoder[motorD]=0;
	return;
}


bool isValidMove(int currentCellX, int currentCellY, int facingDir)//need to flip params
{
	int count = 1;//because constants don't work here??
	if(facingDir == 0 && /*currentCellY - 1 >= 0*/ abs(mazeMap[currentCellY - count][currentCellX]) == VALID_CELL)
	{
		return true;
	}
	else if(facingDir == 1 && /*currentCellX + 1 < MAZE_C - 1 &&*/ mazeMap[currentCellY][currentCellX + count] == VALID_CELL)
	{
		return true;
	}
	else if(facingDir == 2 && /*currentCellY + 1 < MAZE_R - 1*/  mazeMap[currentCellY + count][currentCellX] == VALID_CELL)
	{
		return true;
	}
	else if(facingDir == 3 && /*currentCellX - 1 > 0 &&*/ mazeMap[currentCellY][currentCellX - count] == VALID_CELL)
	{
		return true;
	}
	return false;
}

int findNextMove(int currentCellX, int currentCellY, int facingDir)
{
	facingDir = (3 + facingDir )%4; //equivalent to (facingDir - 1) %4?
	for (int attempts = 0; attempts < 4; attempts++)
	{//assuming this is using left hand rule
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

int goalCellValue (int &currentCellX, int &currentCellY, int facingDir)
{
		int count=1;
    if (facingDir == 0) //check the north cell
    {
        currentCellY -= 1;
        return mazeMap[currentCellY-count][currentCellX];
    }
    else if (facingDir == 1) //check the east cell
    {
        currentCellX += 1;
        return mazeMap[currentCellY][currentCellX+count];
    }
    else if (facingDir == 2) //check the south cell
    {
        currentCellY -= 1;
        return mazeMap[currentCellY+count][currentCellX];
    }
    else // if (nextDir == 3) check the west cell
    {
        currentCellX -= 1;
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
		mazeMap[currentCellY-count][currentCellX] = 1;
		currentCellY -= 1;

	}
	else if (nextDir == 1) //if we need to go right
	{
		mazeMap[currentCellY][currentCellX+count] = 1;
		currentCellX += 1;
	}
	else if (nextDir == 2) //if we need to go down
	{
		mazeMap[currentCellY+count][currentCellX] = 1;
		currentCellY += 1;
	}
	else if (nextDir == 3) //if we need to go left
	{
		mazeMap[currentCellY][currentCellX-count] = 1;
		currentCellX -= 1;
	}
}

// y is the rows, x is the cols
bool junctionCheck(int currentCellX, int currentCellY, int facingDir)
{
    int frontCellX = currentCellX;
    int frontCellY = currentCellY;

    // check if the gird in the front is 1
    // dir 0 is up, 1 is right, 2 is down, 3 is left
    bool frontIs1;
    if(goalCellValue(frontCellX, frontCellY, facingDir) == 1)
    {
        frontIs1 = true;
    }
    // now the current x and current y is the one in the front
    bool zero;
    // check if there's an empty direction with 0 beside current x and y
    for(int i = 0; i < 4; i++)
    {
        // not checking the back cell
        if(i != 2)
        {
            // check left, front, and right
            if(goalCellValue(frontCellX, frontCellY, (facingDir + i) % 4 ) == 0)
            {
                zero = true;
            }
        }
    }
    // check front left and front right
    // move one to the front again
    makeNextMove(frontCellX, frontCellY, facingDir);
    if(goalCellValue(frontCellX, frontCellY, (facingDir + 1) % 4 ) == 0
       || goalCellValue(frontCellX, frontCellY, (facingDir + 3) % 4 ) == 0)
    {
        zero = true;
    }

    // check if both conditions are true
    if(frontIs1 && zero)
    {
        return true;
    }
    return false;
}

void swapToPen()
{
	int const MoveX=3700;
	int const MoveY=0;
	int const currentX=nMotorEncoder[motorC];
	int const currentY=nMotorEncoder[motorA];
	motor[motorA]=motor[motorB]=motor[motorC]=0;
	motor[motorA]=motor[motorB]=-10;
	eraseDisplay();
	while(abs(nMotorEncoder[motorA]-currentY)<MoveY)
	{}
	motor[motorA]=motor[motorB]=0;
		motor[motorC]=-100;
	while(abs(nMotorEncoder[motorC]-currentX)<MoveX)
	{}
	motor[motorC]=0;
}


void movePen(int startCellX, int startCellY, int goalCellX, int goalCellY)
{
    //sets the current cell to the start cell
    int currentCellX = startCellX;
    int currentCellY = startCellY;
    while (currentCellX != goalCellX && currentCellY != goalCellY)
    {
        if (mazeMap[currentCellX][currentCellY+1] == 1) //if the top cell is white
        {
            moveToCell(currentCellX, currentCellY, currentCellX, currentCellY+1);
        }
        else if (mazeMap[currentCellX+1][currentCellY] == 1) //if the right cell is white
        {
            moveToCell(currentCellX, currentCellY, currentCellX+1, currentCellY);
        }
        else if (mazeMap[currentCellX][currentCellY-1] == 1) //if the bottom cell is white
        {
            moveToCell(currentCellX, currentCellY, currentCellX, currentCellY-1);
        }
        else if (mazeMap[currentCellX-1][currentCellY] == 1) //if the left cell is white
        {
            moveToCell(currentCellX, currentCellY, currentCellX-1, currentCellY);
        }
    }
    //since move to cell moves AND updates the current cell, the loop will keep on running until
    //the current cell has reached the goal cells


}
