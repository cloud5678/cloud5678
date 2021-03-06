#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in2,    poten,          sensorPotentiometer)
#pragma config(Sensor, in3,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  launSole1,      sensorDigitalOut)
#pragma config(Sensor, dgtl2,  wingSole1,      sensorDigitalOut)
#pragma config(Sensor, dgtl3,  lockSole1,      sensorDigitalOut)
#pragma config(Sensor, dgtl11, wingSole2,      sensorDigitalOut)
#pragma config(Sensor, dgtl12, launSole2,      sensorDigitalOut)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           intakeRight,   tmotorVex393, openLoop)
#pragma config(Motor,  port2,           armLeft,       tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           armLeft2,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           frontLeft,     tmotorVex393, openLoop)
#pragma config(Motor,  port5,           backLeft,      tmotorVex393, openLoop, encoder, encoderPort, I2C_1, 1233528)
#pragma config(Motor,  port6,           armRight,      tmotorVex393, openLoop)
#pragma config(Motor,  port7,           backRight,     tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_2, 1233528)
#pragma config(Motor,  port8,           armRight2,     tmotorVex393, openLoop)
#pragma config(Motor,  port9,           frontRight,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          intakeLeft,    tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Note armRight and arLeft are the top motors
//orientation of left and right is from the front of the robot
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(125)

#include "Main.c"
#include "PIDController.c"
#include "Sound.c"

PIDController armPID;
PIDController turnPID;

const int ARMAX = 1800;
const int ARMIN = 0;

void robotShutdown() {
	motor[port1] = 0;
	motor[port2] = 0;
	motor[port3] = 0;
	motor[port4] = 0;
	motor[port5] = 0;
	motor[port6] = 0;
	motor[port7] = 0;
	motor[port8] = 0;
	motor[port9] = 0;
	motor[port10] = 0;
	SensorValue[wingSole1] = 0;
	SensorValue[wingSole2] = 0;
	SensorValue[lockSole1] = 1;
}

int getPotenValue() {
	return 4100 - SensorValue[poten];
}

void driveArcade(int y, int x) {
	motor[frontLeft] = motor[backLeft] = y + x;
	motor[frontRight] = motor[backRight] = y - x;
}
void driveTank(int l, int r) {
	motor[frontLeft] = motor[backLeft] = l;
	motor[frontRight] = motor[backRight] = r;
}
void setArmSpeed(int z) {
	motor[armRight] = motor[armLeft] = motor[armLeft2] = motor[armRight2] = z;
}
void setIntakeSpeed(int speed) {
	motor[intakeLeft] = motor[intakeRight] = speed;
}
void resetEncoders() {
	nMotorEncoder[backRight] = nMotorEncoder[backLeft] = 0;
}
void setLauncher(int a) {
	SensorValue[launSole1] = SensorValue[launSole2] = a;
}
void setWings(int a) {
	SensorValue[wingSole1] = SensorValue[wingSole2] = a;
}
void setArmLock(int a) {
	SensorValue[lockSole1] = a;
}

///////////////////////////////////////////////////////////
// Robot Tasks
///////////////////////////////////////////////////////////

void robotInit() {
	// Initialize PID
	init(armPID, 0.564444, 0.009, 0);
	setThresholds(armPID, 128, -127);
	init(turnPID, -0.267368, 0, 0);
	setThresholds(turnPID, 128, -127);

	// Initalize Gyroscope
	SensorType[gyro] = sensorNone;
	wait1Msec(1000);
	SensorType[gyro] = sensorGyro;
	wait1Msec(2000);
	SensorValue[gyro]=0;
	SensorFullCount[gyro]=3600;
}

#include "Autonomous.c"

task robotAutonomous() {
	setArmLock(false);
	wait1Msec(100);

	bool blue = lcd_autonColor;

	if (lcd_autonMode == lcd_autonModeMID) {
		auton_middle(blue);
	} else if (lcd_autonMode == lcd_autonModeMID2) {
		auton_middle_2_pid(blue);
	} else if (lcd_autonMode == lcd_autonModeHANG) {
		auton_hanging_pid(blue);
	}

	robotShutdown();
}

bool pidOverride = false;
int prevArmLockPress = false;
bool armLockPos = true;
task robotTeleop() {
	// User control initialization
	//setSetpoint(turnPID, 0);
	setSetpoint(armPID, getPotenValue());

	while (true) { // User control loop
	  	int driveX = vexRT[Ch4];
	  	int driveY = vexRT[Ch3] ;
	  	int armSpeed = vexRT[Ch2];
	  	int intakeSpeed = 127*((vexRT[Btn5U])-(vexRT[Btn5D]));

	 		if (vexRT[Btn8U]) {
	  		pidOverride = true;
	  	}
	  	if (vexRT[Btn7U]) {
	  		pidOverride = false;
	  	}

	  	//if (abs(driveX) < 16) {
			//	turnPID.enabled = true;
			//} else {
			//	turnPID.enabled = false;
			//	SensorValue[gyro] = 0;
			//}

			//if (vexRT[Btn7D]) {
			//	turnPID.enabled = false;
			//	SensorValue[gyro] = 0;
			//}

			if (armSpeed > 12) {
				armPID.enabled = false;
				setSetpoint(armPID, getPotenValue());
				if (armPID.setpoint > ARMAX) setSetpoint(armPID, ARMAX);
			} else if (armSpeed < -6) {
				armPID.enabled = false;
				setSetpoint(armPID, getPotenValue());
				if (armPID.setpoint < ARMIN) setSetpoint(armPID, ARMIN);
			} else if (armSpeed > -1) {
				armSpeed = 12;
			} else {
				if (!armPID.enabled) {
					setSetpoint(armPID, getPotenValue());
				}
				armSpeed = 0;
				armPID.enabled = true;
			}

			if (abs(driveY) < 8) driveY = 0; // Drive deadband
			if (abs(driveX) < 8) driveX = 0; // Drive deadband

			if (!pidOverride) {
	  		//driveX = turnPID.enabled ? calculate(turnPID, SensorValue[gyro]) : driveX;
				armSpeed = armPID.enabled ? calculate(armPID, getPotenValue()) : armSpeed;
			}

			setLauncher(vexRT[Btn6D]);
	  	setWings(vexRT[Btn6U]);
	  	if (vexRT[Btn7D] == true && vexRT[Btn7D] != prevArmLockPress) {
	  		setArmLock(!armLockPos);
	  		armLockPos = !armLockPos;
	  	}

	  	driveArcade(driveY * 100 / 128, driveX * 100 / 128);
	  	setArmSpeed(armSpeed);
	  	setIntakeSpeed(intakeSpeed);

	  	prevArmLockPress = vexRT[Btn7D];
	  	wait1Msec(20);
	}
}

void robotDisabled() {

}
