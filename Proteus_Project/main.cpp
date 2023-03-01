#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>

#define counts_per_inch 15.4

//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P0_1);
DigitalEncoder left_encoder(FEHIO::P1_0);
FEHMotor right_motor(FEHMotor::Motor0,9.0);
FEHMotor left_motor(FEHMotor::Motor1,9.0);

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
    int motor_percent = 40; //Input power level here
    
	int turn_counts = 206;
	int ten_counts = 405;
	int four_counts = 162;

    float x, y; //for touch screen

    //Initialize the screen
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);

    LCD.WriteLine("Shaft Encoder Exploration Test");
    LCD.WriteLine("Touch the screen");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed

    move_forward(motor_percent, 23*counts_per_inch); //see function
	Sleep(1.0);
	turn_right(motor_percent, 70);
	Sleep(1.0);
	move_forward(motor_percent, 33*counts_per_inch);
	Sleep(1.0);
	turn_right(motor_percent, 40);
    //test
	Sleep(1.0);
	move_forward(motor_percent, 16*counts_per_inch);
	Sleep(1.0);
    turn_right(motor_percent, 40);
	Sleep(1.0);
    move_forward(motor_percent, 24*counts_per_inch);
	Sleep(1.0);
    turn_right(motor_percent, 60);
	Sleep(1.0);
    move_forward(motor_percent, 32*counts_per_inch);
	Sleep(1.0);

    return 0;
}

