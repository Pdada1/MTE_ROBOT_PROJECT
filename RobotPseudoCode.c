void handrailAlgo();
void searchEnds(int &startCellX, int &startCellY, int &goalCellX, int &goalCellY);
void readMaze(); //this is fairly straightforward
void moveToCell(int currentCellX, int currentCellY, int moveToCellX, int moveToCellY); //this is fairly straightforward, use controlXMotors()
void controlXMotors(); //this is trivial


const int MAZE_R = 41, MAZE_C = 41, MOTOR_POWER = 30;
int mazeMap[MAZE_R][MAZE_C] = {0};
task main()
{
/*

*/
}
/*
X-axis is motorA + motorB, Y-axis is motorC

void handrailAlgo()
{
	//Define solution as a modification of the mazeMap, all 0/1
	//Solution will be realized by sequence of movements from point to point

	//Solve Maze while recording movements
	int currentCellX = 0, currentCellY = 0, startCellX = 0, startCellY = 0, goalCellX = 0, goalCellY = 0;

	//search mazeMap for start and end points
	searchEnds(startCellX, startCellY, goalCellX, goalCellY);

	int facing = 0;
	char directions[4] = {E, N, S, W};

	//pick a start and end (doesnt matter tbh)
	while (currentCellX != goalCellX || currentCellY != goalCellY)
	{

		//add current position to array of solution points (append?)

		//if left cell, turn left and step forward (facing = (facing - 1) % 4, where direction is directions[facing])
		//else if forward cell, step forward
		//else if right cell, turn right and step forward (facing = (facing + 1) % 4)
		//else, turn around (facing = (facing + 2) % 4)

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
