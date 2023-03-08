
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <FEHBattery.h>

#define counts_per_inch 16.6
#define counts_per_degree_right 1.056
#define counts_per_degree_left 1.078
#define red_threshold 0.2
#define blue_threshold 0.5
#define red_light 0
#define blue_light 1
#define light_x 9.9
#define light_y 62.2

//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P0_1);
DigitalEncoder left_encoder(FEHIO::P1_0);
AnalogInputPin cds(FEHIO::P3_0);
FEHMotor right_motor(FEHMotor::Motor0,9.0);
FEHMotor left_motor(FEHMotor::Motor3, 9.0);

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

void move_forward(int percent, int counts, int direction) //using encoders
{
	// while (RPS.Heading() > 0 && (RPS.Heading() < (direction - 1) || RPS.Heading() > (direction + 1))) {
	// 	if (RPS.Heading() > direction) {
	// 		if (RPS.Heading() - direction > 180) {
	// 			turn_left(10, 1);
	// 		} else {
	// 			turn_right(10, 1);
	// 		}
	// 	} else {
	// 		if (direction - RPS.Heading() > 180) {
	// 			turn_right(10, 1);
	// 		} else {
	// 			turn_left(10, 1);
	// 		}
	// 	}
	// 	LCD.WriteLine(RPS.Heading());
	// }
	//LCD.WriteLine(RPS.Heading());

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

void move_to_x(int x) {
	while (RPS.X() > 0 && (RPS.X() < (x - 2) || RPS.X() > (x + 2))) {
		if (RPS.X() > x) {
			move_forward(10, 1, 90);
		} else {
			move_forward(10, 1, 270);
		}
	}
}

void move_to_y(int y) {
	while (RPS.Y() > 0 && (RPS.Y() < (y - 2) || RPS.Y() > (y + 2))) {
		if (RPS.Y() > y) {
			move_forward(10, 1, 180);
		} else {
			move_forward(10, 1, 0);
		}
	}
}

int kiosk_light() {
	if (cds.Value() < red_threshold) {
		LCD.WriteLine("Red");
		return RED;
	} else if (cds.Value() < blue_threshold){
		LCD.WriteLine("Blue");
		return BLUE;
	} else {
		LCD.WriteLine("blue");
		return 1;
	}
}

int main(void)
{
	//RPS.InitializeTouchMenu();
    int motor_percent = 40; //Input power level here
    float x, y; //for touch screen

    //Initialize the screen
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);

	// while(true) {
	// 	LCD.WriteLine("X:");
	// 	LCD.WriteLine(RPS.X());
	// 	LCD.WriteLine("Y:");
	// 	LCD.WriteLine(RPS.Y());
	// 	Sleep(0.1);
	// }
		
    while(cds.Value() > 1.5){ 
        LCD.WriteLine(cds.Value());
        Sleep(0.1);
    } //Wait for screen to be pressed

	//No RPS
	move_forward(motor_percent, 15*counts_per_inch, 0); //see function
	Sleep(1.0);
	move_forward(-motor_percent-5, 1*counts_per_inch, 0); //see function
	Sleep(1.0);
	turn_left(motor_percent, 90*counts_per_degree_left);
	Sleep(1.0);
	move_forward(motor_percent, 30*counts_per_inch, 0); //see function
	Sleep(1.0);
	turn_left(motor_percent, 18.5*counts_per_degree_left);
	Sleep(1.0);
	move_forward(motor_percent, 23*counts_per_inch, 0); //see function
	Sleep(1.0);
	kiosk_light();
	Sleep(1.0);
	turn_right(motor_percent, 90*counts_per_degree_right);
	Sleep(1.0);
	move_forward(motor_percent, 10*counts_per_inch, 0); //see function
	Sleep(1.0);
	move_forward(-motor_percent, 20*counts_per_inch, 0); //see function
	Sleep(1.0);
	turn_right(motor_percent, 90*counts_per_degree_right);
	Sleep(1.0);
	move_forward(motor_percent, 14*counts_per_inch, 0); //see function
	Sleep(1.0);
	turn_right(motor_percent, 90*counts_per_degree_right);
	Sleep(1.0);
	move_forward(motor_percent, 20*counts_per_inch, 0); //see function






	//With RPS

    // move_forward(motor_percent, 12*counts_per_inch, 30); //see function
	// Sleep(1.0);
	// turn_left(motor_percent, 90*counts_per_degree_left);
    // Sleep(1.0);
    // move_forward(motor_percent, 18*counts_per_inch, 90); //see function
	// Sleep(1.0);
	// turn_right(motor_percent, 88);
	// Sleep(1.0);
	// move_forward(motor_percent+10, 35*counts_per_inch, 0);
	// Sleep(1.0);
	// // On ramp
	// turn_right(motor_percent, 90*counts_per_degree_right);
	// Sleep(1.0);
	// move_forward(motor_percent, 25*counts_per_inch, 315);
	// Sleep(1.0);
	// move_to_x(light_x);
	// Sleep(1.0);
	// move_to_y(light_y);
	// Sleep(1.0);
	// move_forward(-motor_percent, 5*counts_per_inch, 315);
	// Sleep(1.0);
    // turn_right(motor_percent, 120*counts_per_degree_right);
	// Sleep(1.0);
    // move_forward(motor_percent, 35*counts_per_inch,225);
    // Sleep(1.0);
    // turn_right(motor_percent, 70*counts_per_degree_right);
    // Sleep(1.0);
    // move_forward(motor_percent, 30*counts_per_inch, 180);
    // Sleep(1.0);

    return 0;
}