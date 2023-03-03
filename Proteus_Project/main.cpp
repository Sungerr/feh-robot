
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>

#define counts_per_inch 16.6
#define counts_per_degree_right 1.056
#define counts_per_degree_left 1.078

//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P0_1);
DigitalEncoder left_encoder(FEHIO::P1_0);
AnalogInputPin cds(FEHIO::P3_0);
FEHMotor right_motor(FEHMotor::Motor0,9.0);
FEHMotor left_motor(FEHMotor::Motor3, 9.0);

void move_forward(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void turn_left(int percent, int counts) {
	//Reset encoder counts
	right_encoder.ResetCounts();
	left_encoder.ResetCounts();
	//Set both motors to desired percent
	right_motor.SetPercent(-percent);
	left_motor.SetPercent(percent);
	//While the average of the left and right encoder is less than counts,
	//keep running motors
	while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

	//Turn off motors
	right_motor.Stop();
	left_motor.Stop();
}

void turn_right(int percent, int counts) {
	//Reset encoder counts
	right_encoder.ResetCounts();
	left_encoder.ResetCounts();
	//Set both motors to desired percent
	left_motor.SetPercent(-percent);
	right_motor.SetPercent(percent);
	//While the average of the left and right encoder is less than counts,
	//keep running motors
	while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

	//Turn off motors
	right_motor.Stop();
	left_motor.Stop();
}

int main(void)
{
    int motor_percent = 30; //Input power level here
    float x, y; //for touch screen

    //Initialize the screen
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);
    while(cds.Value() > 1.5){ 
        LCD.WriteLine(cds.Value());
        Sleep(0.1);
    } //Wait for screen to be pressed

	Sleep(1.0);
	
	//turn_right(motor_percent, 95); //About 90 degrees
	//turn_left(motor_percent, 97); //About 90 degrees
    move_forward(motor_percent, 17*counts_per_inch); //see function
	Sleep(1.0);
	turn_left(motor_percent, 29*counts_per_degree_left);
    Sleep(1.0);
    move_forward(motor_percent, 8.8*counts_per_inch); //see function
	Sleep(1.0);
	turn_right(motor_percent, 88);
	Sleep(1.0);
	move_forward(motor_percent+10, 35*counts_per_inch);
	Sleep(1.0);
	turn_right(motor_percent, 37*counts_per_degree_right);
    //6 = 90 degree turn
	Sleep(1.0);
	move_forward(motor_percent, 25*counts_per_inch);
	Sleep(1.0);
	move_forward(-motor_percent, 5*counts_per_inch);
	Sleep(1.0);
    turn_right(motor_percent, 120*counts_per_degree_right);
	Sleep(1.0);
    move_forward(motor_percent, 35*counts_per_inch);
    Sleep(1.0);
    turn_right(motor_percent, 70*counts_per_degree_right);
    Sleep(1.0);
    move_forward(motor_percent, 30*counts_per_inch);
    Sleep(1.0);

    return 0;
}