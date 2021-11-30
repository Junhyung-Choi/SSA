#pragma config(Sensor,S1,c1,sensorEV3_Color,modeEV3Color_Color)
#pragma config(Sensor,S2,c2,sensorEV3_Color,modeEV3Color_Color)
#pragma config(Sensor,S3,c3,sensorEV3_Color,modeEV3Color_Color)
#pragma config(Motor,motorB,lm,tmotorEV3_Large,PIDControl,encoder)
#pragma config(Motor,motorC,rm,tmotorEV3_Large,PIDControl,encoder)

#define DIFF 10
#define Black 1
#define Blue 2
#define Green 3
#define Yellow 4
#define Red 5
#define White 6
#define Brown 7

int nMotorSpeedSetting=35, vertex=0, count =0, row=0, val, r, c;

void go()
{
	val = 7;
	if(getColorName(c2) == Yellow)
	{
		setMotorSpeed(lm, nMotorSpeedSetting - val);
		setMotorSpeed(rm, nMotorSpeedSetting + val);
	}
	else {
		setMotorSpeed(lm, nMotorSpeedSetting + val);
		setMotorSpeed(rm, nMotorSpeedSetting - val);
	}
	if(row % 2 == 1 || row == 4){
		if(getColorName(c1) == Yellow) vertex++;
		else vertex = 0;
	}
	else {
		if(getColorName(c3) == Yellow) vertex++;
		else vertex = 0;
	}
	if(vertex == 1) count++;
}

void turnLeft()
{
	setMotorSpeed(lm,40);
	setMotorSpeed(rm,40);
	sleep(150);

	while(getColorName(c1) > Yellow){
		setMotorSpeed(lm, -nMotorSpeedSetting * 6/10);
		setMotorSpeed(rm, nMotorSpeedSetting * 6/10);
		sleep(20);
	}

	while(getColorName(c2) > Yellow){
		setMotorSpeed(lm,-nMotorSpeedSetting * 6/10);
		setMotorSpeed(rm,nMotorSpeedSetting * 6/10);
		sleep(20);
	}

	sleep(150);
	setMotorSpeed(lm,0);
	setMotorSpeed(rm,0);
	sleep(100);
}

void turnRight(){
	setMotorSpeed(lm,40);
	setMotorSpeed(rm,40);
	sleep(100);

	while(getColorName(c3) > Yellow){
		setMotorSpeed(lm, nMotorSpeedSetting * 6/10);
		setMotorSpeed(rm, -nMotorSpeedSetting * 6/10);
		sleep(20);
	}

	while(getColorName(c2) > Yellow){
		setMotorSpeed(lm, nMotorSpeedSetting * 6/10);
		setMotorSpeed(rm, -nMotorSpeedSetting * 6/10);
		sleep(20);
	}

	sleep(50);
	setMotorSpeed(lm,0);
	setMotorSpeed(rm,0);
	sleep(100);
}

void stopMotor(){
	setMotorSpeed(lm,0);
	setMotorSpeed(rm,0);
}

int max(int a, int b) {
	return a > b ? a : b;
}

void showMatrix()
{
    for(int i=0;i<6;i++)
    {
        displayBigTextLine(i*2+1,"%d %d %d %d %d %d",S[i][0],S[i][1],S[i][2],S[i][3],S[i][4],S[i][5]);
    }
}

task main(){
	while(getButtonPress(1)==0) sleep(10);
	while(true)
	{
		showMatrix(s);
		go();
		if(count == 4)
		{
				if(row == 3) break;
				if(row %2 == 0)
				{
					setMotorSpeed(lm,35);
					setMotorSpeed(lm,30);
					sleep(400);
					turnRight();
				}
				else
				{
					sleep(300);
					turnLeft();
				}
				if(row % 2 == 0)
				{
					while( getColorName(c3) == White) go();
					setMotorSpeed(lm,35);
					setMotorSpeed(rm,30);
					sleep(400);
					turnRight();
				}
				else
				{
					while( getColorName(c1) == White) go();
					setMotorSpeed(lm,30);
					setMotorSpeed(rm,35);
					sleep(400);
					turnLeft();
				}
				row++;
				count = 0;
			}
		}
		playTone(240,20); sleep(200);
		stopMotor();
		while(getButtonPress(1) == 0) sleep(10);
}
