/*
X-axis is motorA, Y-axis is motorD

array handrailAlgo(array mazeMap)
{
	//Define solution array as an array of points in reference frame of maze cells (ex. 1-20 for a 20 cell maze)
	//Solution will be realized by sequence of movements from point to point
	//Solve Maze while recording movements
	int currentCellX = 0, currentCellY = 0, goalCellX = 0, goalCellY = 0;

	//search mazeMap for start and end points
	int facing = 1;
	array directions[4] = [N, E, S, W];

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
task main()
{
/*

*/
}
