#pragma config(Sensor,S1,c1,sensorEV3_Color,modeEV3Color_Color)
#pragma config(Sensor,S2,c2,sensorEV3_Color,modeEV3Color_Color)
#pragma config(Sensor,S3,c3,sensorEV3_Color,modeEV3Color_Color)
#pragma config(Motor,motorB,lm,tmotorEV3_Large,PIDControl,encoder)
#pragma config(Motor,motorC,rm,tmotorEV3_Large,PIDControl,encoder)

#define DIFF 10

int nMotorSpeedSetting=35,vertex=0,count =0,row=0,val,r=0,c=0,i,j,f,e;
int S[6][6],dt[6][6],d[6],J[6][6];

void go()
{
	val=7;
	if(getColorName(c2)==5) //5:red
	{
		if(row%2==0)S[row][count]=1;
		else S[row][4-count]=1;
		playTone(440,20); sleep(100);
	}
	else if(getColorName(c2)==2){
		if(row%2==0)S[row][count]=-1;
		else S[row][4-count]=-1;
		playTone(400,20);
		sleep(100);
	}
	if(getColorName(c2)==4) //4:yellow
	{
		setMotorSpeed(lm,nMotorSpeedSetting-val);
		setMotorSpeed(rm,nMotorSpeedSetting+val);

	}
	else{
		setMotorSpeed(lm,nMotorSpeedSetting-val);
		setMotorSpeed(rm,nMotorSpeedSetting+val);

	}
		if(getColorName(c1)==4 || getColorName(c3)==4)
		vertex++;
		else vertex =0;
	if(vertex==1) count++;
}
void turnLeft()
{
	setMotorSpeed(lm,20);
	setMotorSpeed(rm,35);
	sleep(300);
	while(getColorName(c1)>4){
		setMotorSpeed(lm,-nMotorSpeedSetting*6/10);
		setMotorSpeed(rm,nMotorSpeedSetting*6/10);
		sleep(10);
	}
	while(getColorName(c2)>4){
		setMotorSpeed(lm,-nMotorSpeedSetting*6/10);
		setMotorSpeed(rm,nMotorSpeedSetting*6/10);
		sleep(5);
	}
	setMotorSpeed(lm,0);
	setMotorSpeed(rm,0);
	sleep(100);
}

void turnRight(){
	setMotorSpeed(lm,30);
	setMotorSpeed(rm,30);
	sleep(100);
	while(getColorName(c3)>4){
		setMotorSpeed(lm,nMotorSpeedSetting*6/10);
		setMotorSpeed(rm,-nMotorSpeedSetting*6/10);
		sleep(10);
	}
	while(getColorName(c2)>4){
		setMotorSpeed(lm,nMotorSpeedSetting*6/10);
		setMotorSpeed(rm,-nMotorSpeedSetting*6/10);
		sleep(5);
	}
	sleep(200);
	setMotorSpeed(lm,0);
	setMotorSpeed(rm,0);
	sleep(100);
}

void stopMotor(){
	setMotorSpeed(lm,0);
	setMotorSpeed(rm,0);
}

void completeSearch(){
	while(true){
		go();
		if(count==4){
			if(row==4) return;
			if(row%2==0){
				setMotorSpeed(lm,40);
				setMotorSpeed(rm,35);
				for(int i=0; i<4; i++){
					if(getColorName(c2)==5){
						if(row%2==0) S[row][count]=1;
						else S[row][4-count]=1;
						playTone(440,20);
						sleep(80);
					}
					else if(getColorName(c2)==2){
						if(row%2==0) S[row][count]=-1;
						else S[row][4-count]=-1;
						playTone(400,20);
						sleep(80);
					}
					else sleep(90);
				}
				turnRight();
			}
			else{
				for(int i=0;i<3; i++){
					if(getColorName(c2)==5){
						if(row%2==0) S[row][count]=1;
						else S[row][4-count]=1;
						playTone(440,20);
						sleep(80);
					}
					else if(getColorName(c2)==2){
						if(row%2==0) S[row][count]=-1;
						else S[row][4-count]=-1;
						playTone(400,20);
						sleep(80);
					}
					else sleep(90);
				}
				turnLeft();
			}
			if(row%2==0){
				while(getColorName(c3)==6) go(); //6:white
				setMotorSpeed(lm,35);
				setMotorSpeed(rm,30);
				sleep(400);
				turnRight();
			}
			else{
				while(getColorName(c1)==6) go();
				setMotorSpeed(lm,30);
				setMotorSpeed(lm,35);
				sleep(400);
				turnRight();
			}
			row++;
			count=0;
			setMotorSpeed(lm,-30);
			setMotorSpeed(rm,-30);
			sleep(410);
		}
	}
}
void goUp(){
	r--; row++;
	turnRight();
	count=0;
	while(true){
		go();
		if(count==1){
			sleep(300);
			turnLeft();
			break;
		}
	}
}
void goDown(){
	r++; row--;
	turnLeft();
	count=0;
	while(true){
		go();
		if(count==1){
			sleep(300);
			turnRight();
			break;
		}
	}
}
void goLeft(){
	c--;
	count=0;
	while(true){
		go();
		if(count==1){
			setMotorSpeed(lm,30);
			setMotorSpeed(rm,30);
			sleep(400);
			break;
		}
	}
}
task main(){
	while(getButtonPress(1)==0) sleep(10);
	completeSearch();
	setMotorSpeed(lm,20);
	setMotorSpeed(lm,20);
	sleep(1000);
	setMotorSpeed(lm,20);
	setMotorSpeed(rm,-20);
	sleep(1650);

	count=row=0;
	for(f=4; f>=0; f--)
		for(e=4; e>=0; e--){
			if(e==4 &&f==4) dt[e][f]=S[e][f];
			else if(f==4) dt[e][f]=dt[e+1][f]+S[e][f];
			else
			{
				dt[e][f]=-10;
				for(i=0; i<=4; i++){
					d[i]=dt[i][f+1];
					if(i>e){
						for(j=i; j>=e; j--)
						d[i]+=S[j][f];
					}
					else if(i==e){
						d[i]+=S[i][f];
					}
					else{
						for(j=i; i<=e; j++)
						d[i]+=S[j][f];
					}
					if(dt[e][f]<d[i]){
						dt[e][f]=d[i];
						J[e][f]=i;
					}
				}
			}
		}
		row=0; r=c=4;
		d[0]=0;
		for(i=0; i<=4; i++){
			d[i+1] =J[d[i]][i];
		}
		for(i=4; i>0; i--){
			if(r>d[i])
			{
				while(r>d[i]) goUp();
				goLeft();
			}
			else if(r==d[i])
			{
				goLeft();
			}
			else{
				while(r<d[i]) goDown();
				goLeft();
			}
		}
		playTone(240,20); sleep(200);
		stopMotor();
		while(getButtonPress(1)==0) sleep(10);
}
