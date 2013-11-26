#pragma config(Sensor, dgtl12, touchSensor,    sensorDigitalIn)
#pragma config(Motor,  port1,           leftFront,     tmotorVex393, openLoop)
#pragma config(Motor,  port2,           rightFront,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           leftIntake,    tmotorVex393, openLoop)
#pragma config(Motor,  port4,           rightIntake,   tmotorVex393, openLoop)
#pragma config(Motor,  port5,           leftArm,       tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port6,           rightArm,      tmotorVex393, openLoop)
#pragma config(Motor,  port7,           leftArm2,      tmotorVex393, openLoop)
#pragma config(Motor,  port8,           rightArm2,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           leftRear,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          rightRear,     tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  //if (SensorValue(touchSensor) == 0)
  //{
	//Hits first friendly large ball into goal zone. (Total time: 1 second)
bool outside=true;//set to false if behind bump,set to true if doing autonomous infront
	if(outside == true)
		{
		ClearTimer(T1);
	while(time1[T1] < 1000)
	{
  	motor[leftFront] = 80;
  	motor[leftRear] = 80;
  	motor[rightFront] = 80;
  	motor[rightRear] = 80;
  	motor[leftArm] = 70;
  	motor[rightArm] = 70;
  	motor[leftArm2] = 70;
  	motor[rightArm2] = 70;

	}
		motor[leftFront] = 0;
  	motor[leftRear] = 0;
  	motor[rightFront] = 0;
  	motor[rightRear] = 0;
		//If a ball is in the robot, outtake (you're intaking here, not outtaking) (Total time: 3 seconds)
	ClearTimer(T1);
	while(time1[T1] < 2000)
	{
		motor[leftIntake] = 127;
		motor[rightIntake] = 127;

	}
		//outtake (Total time: 5 seconds)
	ClearTimer(T1);
	while(time1[T1] < 2000)
	{
		motor[leftIntake] = -127;
		motor[rightIntake] = -127;
	}

	//5 point code. Confirmed to work for 5+, 10+ potential.
	//Go back with arm up. (Total time: 5.9 seconds)
	ClearTimer(T1);
	while(time1[T1] < 900)
	{
  	motor[leftFront] = -100;
  	motor[leftRear] = -100;
  	motor[rightFront] = -100;
  	motor[rightRear] = -100;
  	motor[leftArm] = 10;
  	motor[rightArm] = 10;
  	motor[leftArm2] = 10;
  	motor[rightArm2] = 10;
	}
	//Wait for three seconds and point robot in the direction of next ball. (Total time: 8.9 seconds)
	ClearTimer(T1);
	while(time1[T1] < 3000)
	{
  	motor[leftFront] = 0;
  	motor[leftRear] = 0;
		motor[rightFront] = 0;
		motor[rightRear] = 0;
		motor[leftArm] = 10;
		motor[rightArm] = 10;
		motor[leftArm2] = 10;
		motor[rightArm2] = 10;
		motor[leftIntake] = 0;
		motor[rightIntake] = 0;
	}
	//Lowers arm. (Total time: 9.1 seconds)
	ClearTimer(T1);
	while(time1[T1] < 200)
	{
		motor[leftArm] = -70;
  	motor[rightArm] = -70;
  	motor[leftArm2] = -70;
  	motor[rightArm2] = -70;
	}

	//Go forward for two seconds, and lifts arm. (Total time: 11.3 seconds)
		ClearTimer(T1);
	while(time1[T1] < 2200)
	{
		motor[leftArm] = 2;
  	motor[rightArm] = 2;
  	motor[leftArm2] = 2;
  	motor[rightArm2] = 2;
  motor[leftFront] = 80;
  motor[leftRear] = 80;
    motor[rightFront] = 80;
    motor[rightRear] = 80;
    motor[leftArm] = 30;
  motor[rightArm] = 30;
  motor[leftArm2] = 30;
  motor[rightArm2] = 30;
	}
	//Timeout
	motor[leftFront] = 0;
  motor[leftRear] = 0;
    motor[rightFront] = 0;
  motor[rightRear] = 0;
    motor[leftArm] = 0;
  motor[rightArm] = 0;
  motor[leftArm2] = 0;
  motor[rightArm2] = 0;
  motor[leftIntake] = 0;
		motor[rightIntake] = 0;

}




else //if behind bump (inside)
{
	//raise arm (Total time: 0.5 seconds)
		motor[leftArm] = 65;
		motor[rightArm] = 65;
  	motor[leftArm2] = 65;
  	motor[rightArm2] = 65;
	wait1Msec(500);
	//Intake to prepare for outtake. (Total time: 1.5 seconds)
		motor[leftIntake] = 127;
		motor[rightIntake] = 127;
	wait1Msec(1000);
	//Outtake. (Total time: 3.5 seconds)
		motor[leftIntake] = -127;
		motor[rightIntake] = -127;
	wait1Msec(2000);
	//Wait for two seconds (manually orient robot?) (Total time: 5.5 seconds)
		motor[leftIntake] = 0;
		motor[rightIntake] = 0;
		wait1Msec(2000);
	//move forward and hit 3 buckyballs (this lowers the arm?) (Total time: 6.3 seconds)
		motor[leftArm] = -22;
		motor[rightArm] = -22;
  	motor[leftArm2] = -22;
  	motor[rightArm2] = -22;
  wait1Msec(800);
  //Drive forwards and slightly lift arm. (Total time: 7.8 seconds)
  	motor[leftArm] = 9;
		motor[rightArm] = 9;
  	motor[leftArm2] = 9;
  	motor[rightArm2] = 9;
  	motor[leftFront] = 80;
 	  motor[leftRear] = 80;
    motor[rightFront] = 80;
 	  motor[rightRear] = 80;
	wait1Msec(1500);
	//Timeout
	  motor[leftArm] = 0;
		motor[rightArm] = 0;
  	motor[leftArm2] = 0;
  	motor[rightArm2] = 0;
		motor[leftFront] = 0;
 	  motor[leftRear] = 0;
    motor[rightFront] = 0;
 	  motor[rightRear] = 0;
 	  motor[leftIntake] = 0;
		motor[rightIntake] = 0;


}
/*  OLD CODE DO NOT USE UNDER ANY CIRCUMSTANCES (This is NOT old code! It's a blueprint for a 15+ scorer that needs testing to reach a workable state. It shouldn't be used as it stands, but if we get a chance to test it will be edited to an optimal state.)


	//15 point + enemy ball middle zone. Currently does not work, needs testing.
	//Keeps arm lifted, turns to the right 90 degrees. (Total time: 1.5 seconds)
	ClearTimer(T1);
	while(time1[T1] < 500)
	{
	motor[leftFront] = 127;
  motor[leftRear] = 127;
  motor[rightFront] = -127;
  motor[rightRear] = -127;
	}
	//Hits second friendly large ball into goal zone. (Total time: 2.5 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
  motor[leftFront] = 127;
  motor[leftRear] = 127;
  motor[rightFront] = 127;
  motor[rightRear] = 127;
	}
	//Lowers arm in prep for going under barrier, turns to the left 90 degrees. (Total time: 3 seconds)
	ClearTimer(T1);
	while(time1[T1] < 500)
	{
  motor[leftFront] = -127;
  motor[leftRear] = -127;
  motor[rightFront] = 127;
  motor[rightRear] = 127;
  motor[leftArm] = -60;
  motor[rightArm] = -60;
  motor[leftArm2] = -60;
  motor[rightArm2] = -60;
	}
	//Moves up to the goal. (Total time: 4 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
  motor[leftFront] = 127;
  motor[leftRear] = 127;
  motor[rightFront] = 127;
  motor[rightRear] = 127;
	}
	//Lifts arm. (Total time: 5 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
		motor[leftArm] = 60;
		motor[rightArm] = 60;
		motor[leftArm2]= 60;
		motor[rightArm2] = 60;
	}
	//Deposits preloads in goal. (Total time: 6.5 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1500)
	{
		motor[leftIntake] = 127;
		motor[rightIntake] = 127;
	}
	//Turns to the right 120 degrees and lowers arm slightly. (Total time: 7 1/6 seconds)
	ClearTimer(T1);
	while(time1[T1] < 667)
	{
		motor[leftFront] = 127;
		motor[leftRear] = 127;
		motor[rightFront] = -127;
		motor[rightRear] = -127;
				motor[leftArm] = -20;
		motor[rightArm] = -20;
		motor[leftArm2]= -20;
		motor[rightArm2] = -20;
	}
	//Hits enemy large ball into middle zone. (Total time: 8 2/3 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1500)
	{
		motor[leftFront] = 127;
		motor[leftRear] = 127;
		motor[rightFront] = 127;
		motor[rightRear] = 127;
	}
	//Turns to the left 60 degrees. (Total time: 9 seconds)
	ClearTimer(T1);
	while(time1[T1] < 333)
	{
		motor[leftFront] = -127;
		motor[leftRear] = -127;
		motor[rightFront] = 127;
		motor[rightRear] = 127;
	}
	//Hits other enemy large ball into middle zone. (Total time: 10 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
		motor[leftFront] = 127;
		motor[leftRear] = 127;
		motor[rightFront] = 127;
		motor[rightRear] = 127;
	}
	//Turns to the right 135 degrees and lowers arm. (Total time: 10.75 seconds)
	ClearTimer(T1);
	while(time1[T1] < 750)
	{
		motor[leftArm] = -60;
		motor[rightArm] = -60;
		motor[leftArm2] = -60;
		motor[rightArm2] = -60;
		motor[leftFront] = 127;
		motor[leftRear] = 127;
		motor[rightFront] = -127;
		motor[rightRear] = -127;
	}
	//Travels as far as possible southwest while attempting to pick up more buckyballs. (Time out)
	ClearTimer(T1);
	while(time1[T1] < 4125)
	{
		motor[leftIntake] = 127;
		motor[rightIntake] = 127;
		motor[leftFront] = 127;
		motor[leftRear] = 127;
		motor[rightFront] = 127;
		motor[rightRear] = 127;
	}
*/

}
/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop
	while (true)
	{
	  // This is the main execution loop for the user control program. Each time through the loop
	  // your program should update motor + servo values based on feedback from the joysticks.

	  // .....................................................................................
	  // Insert user code here. This is where you use the joystick values to update your motors, etc.
	  // .....................................................................................

	 //Arm
          //Use Left Stick
                motor[leftArm] = vexRT[Ch3];
                motor[rightArm] = vexRT[Ch3];
                motor[leftArm2] = vexRT[Ch3];
                motor[rightArm2] = vexRT[Ch3];

                //Intake
                //RB Upper is Intake, LB Upper is Output
                if (vexRT[Btn5U] == 1)
                {
                        motor[leftIntake] = -127;
                        motor[rightIntake] = -127;
                }
                else if (vexRT[Btn6U] == 1)
                {
                        motor[leftIntake] = 127;
                        motor[rightIntake] = 127;
                }
                else
                {
                        motor[leftIntake] = 0;
                        motor[rightIntake] = 0;
                }
                //Turning/Straight driving
                //Use Right-Stick
                if((vexRT[Ch1] > 20) || (vexRT[Ch1] < -20))
                {
                        motor[leftFront] = (vexRT[Ch2] + vexRT[Ch1]);
                        motor[leftRear] = (vexRT[Ch2] + vexRT[Ch1]);
                        motor[rightFront] = (vexRT[Ch2] - vexRT[Ch1]);
                        motor[rightRear] =  (vexRT[Ch2] - vexRT[Ch1]);
                }
                else
                {
                        motor[leftFront] = vexRT[Ch2];
                        motor[leftRear] = vexRT[Ch2];
                        motor[rightFront] = vexRT[Ch2];
                        motor[rightRear] = vexRT[Ch2];
                }
        }
}
