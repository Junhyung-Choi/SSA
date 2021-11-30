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
int S[6][6], dt[6][6];

void go()
{
	val = 7;
	if(getColorName(c2) == Red) {
		if(row % 2 == 0) S[row][count] = 1;
		else S[row][4 - count] = 1;
		playTone(440, 20); sleep(100);
	}
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

void completeSearch() {
	while(true) {
		go();

		if(count == 4) {
			if(row == 4) return;
			if(row % 2 == 0) {
				setMotorSpeed(lm, 40);
				setMotorSpeed(rm, 35	);
				for(int i = 0; i < 4; i++) {
					if(getColorName(c2) == Red) {
						if(row % 2 == 0) S[row][count] = 1;
						else S[row][4 - count] = 1;
						playTone(440, 20);
						sleep(80);
					}
					else sleep(90);
				}
				turnRight();
			}
			else {
				for(int i = 0; i < 3; i++) {
					if(getColorName(c2) == Red) {
						if(row % 2 == 0) S[row][count] = 1;
						else S[row][count] = 1;
						playTone(440, 20);
						sleep(80);
					}
					else sleep(90);
				}
				turnLeft();
			}
			if(row % 2 == 0) {
				while(getColorName(c3) == White) go();
				setMotorSpeed(lm, 35);
				setMotorSpeed(rm, 30);
				sleep(400);
				turnRight();
			}
			else {
				while(getColorName(c1) == White) go();
				setMotorSpeed(lm, 30);
				setMotorSpeed(rm, 35);
				sleep(400);
				turnLeft();
			}
			row++;
			count = 0;
			setMotorSpeed(lm, -30);
			setMotorSpeed(rm, 30);
			sleep(410);
		}
	}
}

int max(int a, int b) {
	return a > b ? a : b;
}

void goUp() {
	r--; row++;
	turnRight();
	count = 0;

	while(true) {
		go();
		if(count == 1) {
			sleep(300);
			turnLeft();
			break;
		}
	}
}

void goLeft() {
	c--;
	count = 0;
	while(true) {
		go();
		if(count == 1) {
			setMotorSpeed(lm, 30);
			setMotorSpeed(rm, 30);
			sleep(400);
			break;
		}
	}
}



task main(){
	while(getButtonPress(1)==0) sleep(10);

	completeSearch();
	setMotorSpeed(lm, 20);
	setMotorSpeed(rm, -20);
	sleep(1000);
	setMotorSpeed(lm, -20);
	setMotorSpeed(rm, 20);
	sleep(1650);

	count = row = 0;

	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			if(i == 0 && j == 0) dt[i][j] = S[i][j];
			else if(i == 0) dt[i][j] = dt[i][j-1] + S[i][j];
			else if(j == 0) dt[i][j] = dt[i-1][j] + S[i][j];
			else dt[i][j] = max(dt[i-1][j], dt[i][j-1] + S[i][j]);
		}
	}

	int x = 0;
	int y = 100;

	for(int i = 0; i < 5; i++) {
		y = y - 10;
		x = 0;

		for(int j = 0; j < 5; j++) {
			displayStringAt(x, y, "%d[%d]", S[i][j], dt[i][j]);
			x = x + 25;
		}
	}

	row = 0; r = c = 4;

	while(r != 0 || c != 0) {
		if(r == 0) goLeft();
		else if(c == 0) goUp();
		else if(dt[r-1][c] > dt[r][c-1]) goUp();
		else goLeft();
		eraseDisplay();
		displayBigTextLine(1, "%d %d(%d)", r, c, row);
	}

	playTone(240, 20); sleep(200);
	stopMotor();
	while(getButtonPress(1) == 0) sleep(10);
}
