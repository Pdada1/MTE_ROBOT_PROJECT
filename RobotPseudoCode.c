/* Code convetions
Motors for x direction: A,B
Motors for y direction: C
Motors for pen: D
Color Sensor Port: S1
Touch Sensor Port: S2
Passage=0
Wall=-1
Traversed Passage =1
if we double traverse set back to -1
Using left hand rule for the algo
*/


void handrailLAlgo(int startCellX, int startCellY); //pain
void moveToCell(int &currentCellX, int &currentCellY, int nextCellX, int nextCellY); //(Ximena)
bool isValidMove(int currentCellX, int currentCellY, int facingDir); //returns false if given move would go into wall(Ash, done)
void makeNextMove(int &currentCellX, int &currentCellY, int facingDir); //make next move and update mazeMap (char)
void readMaze(); //iterates over maze cells and stores as array,
void initialize(); //initializes robot
int findNextMove(int currentCellX, int currentCellY, int facingDir); //(done)
void modifyMazeMap(int currentCellX, int currentCellY);

void swapToPen(); //Moves pen to colour sensor pos
void swapToCSensor(); //Moves colour sensor to pen pos
void drawMaze(int const &currentCellX, int const &currentCellY, int facingDir, int const &startCellX,
	int const &startCellY, int const &goalCellX, int const &goalCellY);
void checkBlank();
/*
void depthFirstSolve(); //genuine suffering (but also semi-redundant so that makes it worse)
void breadthFirstSolve(); //genuine suffering
*/


const int MAZE_R = 9, MAZE_C = 9, MOTOR_POWER = 10,	MOTOR_POWER_Y = 100, CELL_TO_ENCODER = 180/(PI*2.75), WALL = -1, PASSAGE = 1;
int mazeMap[MAZE_R][MAZE_C];
string penDirection[MAZE_R*MAZE_C];

//start is [1][0], end is [MAZE_R - 1][MAZE_C]

task main()
{
    int currentCellX = 0, currentCellY = 0, startCellX = 0, startCellY = 0;
	//order of function initializations
	initialize();
	//moveToCell(x,y,8,8);
	//searchEnds();
	time1[T1]=0;
	readMaze();
	eraseDisplay();
	for(int i=2; i<MAZE_R+2;i++)
	{
		displayString(i, "%d %d %d %d %d %d %d %d %d", mazeMap[i-2][0],mazeMap[i-2][1],mazeMap[i-2][2],mazeMap[i-2][3],mazeMap[i-2][4],mazeMap[i-2][5],mazeMap[i-2][6],mazeMap[i-2][7],mazeMap[i-2][8]);
	}
	wait1Msec(5000);
	int maze_time=time1[T1];
	//start timer
	//handrailLAlgo();
	int algo_time=time1[T1]-maze_time;
	//draw maze
	int total_time=time1[T1];
	int draw_time=total_time-maze_time-algo_time;
}

bool searchEnds() //changed so that it checks the array and not moving the actual track and whatnot
{
	return (mazeMap[0][1]==0);
}

void readMaze()
{		const int LIGHT_THRESHOLD=25;
		eraseDisplay();
    int end_col = 0;
    for (int row = 0; row < MAZE_R;)
    {
        //scans from the left to the right at even rows
        if(row % 2 == 0)
        {
            for (int col = 0; col < MAZE_C;)
            {
                //assume colour sensor is S3; if colour == white
                if(SensorValue[S1] >LIGHT_THRESHOLD)
                {
                    mazeMap[row][col] = 0;
                }
                    //the colour is black
                else
                {
                    mazeMap[row][col] = -1;
                }

                displayString(col+2, "%d ",SensorValue[S1]);
                //move one cell to the right
           			if(col!=MAZE_C-1)
            			moveToCell(col, row, col + 1, row);
            		else
            		{
            			col++;
            		}
            		wait1Msec(300);
            }
            end_col = MAZE_C - 1;
        }
        //scans from the right to the left at even rows

        else
        {
            for (int col = MAZE_C - 1; col >=0 ;)
            {
                if(SensorValue[S1] > LIGHT_THRESHOLD)
                {
                    mazeMap[row][col] = 0;
                }
                else
                {
                    mazeMap[row][col] = -1;
                }
                displayString(col+2, "%d ",SensorValue[S1]);
                if(col!=0)
                	moveToCell(col, row, col - 1, row);
               	else
               	{
               		col--;
               	}
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
    //move the x distance
    if (currentCellX > nextCellX)
    {
    	motor[motorA] = motor[motorB] = MOTOR_POWER; //test to make sure directions are right
        while(nMotorEncoder[motorA] > nextCellX*3.54*CELL_TO_ENCODER)
        {}
    }
    else if (currentCellX < nextCellX)
    {
    	motor[motorA] = motor[motorB] = -MOTOR_POWER;
        while(nMotorEncoder[motorA] < nextCellX*3.54*CELL_TO_ENCODER)
        {}
    }
    motor[motorA] = motor[motorB]=0;
    //move the y distance
    if (currentCellY > nextCellY)
    {
    	motor[motorC] = MOTOR_POWER_Y;
        while(nMotorEncoder[motorA] > nextCellX*137*CELL_TO_ENCODER)
        {}
    }
    else if (currentCellY < nextCellY)
    {
    	motor[motorC] = -MOTOR_POWER_Y;
        while(nMotorEncoder[motorA] < nextCellX*137*CELL_TO_ENCODER)
        {}
    }
    motor[motorC] = 0;
    //update the current cell coordinate
    currentCellX = nextCellX;
    currentCellY = nextCellY;
    return;
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
	int cursorCellX = currentCellX, cursorCellY = currentCellY;

	while (cursorCellX != goalCellX || cursorCellY != goalCellY)
	{
		makeNextMove(cursorCellX, cursorCellY, findNextMove(cursorCellX, cursorCellY, facingDir));
		modifyMazeMap(cursorCellX, cursorCellY);

		//update current position after each move (in the move functions)
	}
}

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
	if(facingDir == 0 && mazeMap[currentCellY - count][currentCellX] != WALL)
	{
		return true;
	}
	else if(facingDir == 1 && mazeMap[currentCellY][currentCellX + count] != WALL)
	{
		return true;
	}
	else if(facingDir == 2 && mazeMap[currentCellY + count][currentCellX] != WALL)
	{
		return true;
	}
	else if(facingDir == 3 && mazeMap[currentCellY][currentCellX - count] != WALL)
	{
		return true;
	}
	return false;
}

int findNextMove(int cursorCellX, int cursorCellY, int facingDir)
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

void makeNextMove(int &currentCellX, int &currentCellY, int facingDir)
{
	//dir 0 is up, 1 is right, 2 is down, 3 is left
	int nextDir = findNextMove(currentCellX, currentCellY, facingDir);
	if (nextDir == 0) //if we need to go up
	{
		modifyMazeMap(currentCellX, currentCellY);
		currentCellY -= 1;

	}
	else if (nextDir == 1) //if we need to go right
	{
		modifyMazeMap(currentCellX, currentCellY);
		currentCellX += 1;
	}
	else if (nextDir == 2) //if we need to go down
	{
		modifyMazeMap(currentCellX, currentCellY);
		currentCellY += 1;
	}
	else if (nextDir == 3) //if we need to go left
	{
		modifyMazeMap(currentCellX, currentCellY);
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

void swapToPen()
{
	int const MoveX=4700;
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

void swapToCSensor()
{
	int const MoveX = 4700;
	int const MoveY = 0;
	int currentX = nMotorEncoder[motorC];
	int currentY = nMotorEncoder[motorA];
	motor[motorA] = motor[motorB] = motor[motorC]=0;
	motor[motorA] = motor[motorB] = 10;
	eraseDisplay();
	while(abs(nMotorEncoder[motorA] - currentY) < MoveY)
	{}
	motor[motorA] = motor[motorB] = 0;
		motor[motorC] = 100;
	while(abs(nMotorEncoder[motorC] - currentX) < MoveX)
	{}
	motor[motorC] = 0;
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

void drawMaze(int &currentCellX, int &currentCellY, int facingDir, int &startCellX,
	int &startCellY, int &goalCellX, int &goalCellY)
{
	moveToCell(currentCellX, currentCellY, startCellX, startCellY);
	while (currentCellX != goalCellX || currentCellY != goalCellY)
	{
		int dX = 0, dY = 0, nextMoveDir = findNextMove(currentCellX, currentCellY, facingDir);

		if (nextMoveDir == 0)
		{
			dY = 1;
		}
		else if (nextMoveDir == 1)
		{
			dX = 1;
		}
		else if (nextMoveDir == 2)
		{
			dY = -1;
		}
		else if (nextMoveDir == 3)
		{
			dY = -1;
		}
		moveToCell(currentCellX, currentCellY, currentCellX + dX, currentCellY + dY);
	}
}
