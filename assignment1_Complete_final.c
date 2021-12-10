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

int nMotorSpeedSetting=25, vertex=0, count =0, row=0, val, r, c, c_suc=15, max_row = 4, max_count = 5, max_matrix = 5, search_init = 0, count_movingPoint = 0, back_row = 4, back_count = 4;
int S[6][6], dt[6][6];

void showMatrix()
{
    for(int i=0;i<5;i++)
    {
        displayBigTextLine(1, "%d", count);
        displayBigTextLine(3 + i*2,"%d %d %d %d %d",S[i][0],S[i][1],S[i][2],S[i][3],S[i][4]);
    }
}
void finalShowMatrix()
{
   // case 5x4
   if (max_row == 3)
   {
      char pS[4][5] = {
         {'+','+','+','+','+'},
         {'+','+','+','+','+'},
         {'+','+','+','+','+'},
         {'+','+','+','+','+'}
      };
      for (int i = 0; i < 4; i++)
      {
         for (int j =0; j<5; j++)
         {
            if(S[i][j] == 1)
               pS[i][j] = 'O';
            else if (S[i][j] == -1)
               pS[i][j] = 'X';
         }
      }
      eraseDisplay();
      for(int i=0;i<4;i++)
      {
         displayBigTextLine(2*i+1,"%c %c %c %c %c",pS[i][0],pS[i][1],pS[i][2],pS[i][3],pS[i][4]);
      }
   } else {
      char pS[5][4] = {
         {'+','+','+','+'},
         {'+','+','+','+'},
         {'+','+','+','+'},
         {'+','+','+','+'},
         {'+','+','+','+'}
      };
      for (int i = 0; i < 5; i++)
      {
         for (int j =0; j < 4; j++)
         {
            if(S[i][j] == 1)
               pS[i][j] = 'O';
            else if (S[i][j] == -1)
               pS[i][j] = 'X';
         }
      }
      eraseDisplay();
      for(int i=0;i<5;i++)
      {
         displayBigTextLine(2*i+1,"%c %c %c %c",pS[i][0],pS[i][1],pS[i][2],pS[i][3]);
      }
   }
}

void showScore(){
	eraseDisplay();
	if(max_row == 3) 	displayBigTextLine(1,"Score: %d",dt[3][4]);
	else displayBigTextLine(1,"Score: %d",dt[4][3]);
}

void stopMotor(){
   setMotorSpeed(lm,0);
   setMotorSpeed(rm,0);
}

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

   if(row % 2 == 1 || row == max_row){
   		if(getColorName(c1) == Yellow || getColorName(c3) == Yellow) {
        	setMotorSpeed(lm, 10);
        	setMotorSpeed(rm, 10);
        	sleep(200);
        	if(getColorName(c2) == Red) {
        		if(count == max_count) S[row][0] = 1;
        		if(row % 2 == 0) S[row][count] = 1;
         		else S[row][(max_count - 1) - count] = 1;
	        	showMatrix();
	        	playTone(440, 20); sleep(100);
	        	setMotorSpeed(lm, 10);
	        	setMotorSpeed(rm, 10);
	        	sleep(400);
	        }
	        if(getColorName(c2) == Blue) {
        		if(row % 2 == 0) S[row][count] = -1;
         		else S[row][(max_count - 1) - count] = -1;
	        	showMatrix();
	        	playTone(440, 20); sleep(100);
	        	setMotorSpeed(lm, 10);
	        	setMotorSpeed(rm, 10);
	        	sleep(200);
	        }
		vertex++;
    	}
    	else
		{
        	vertex = 0;
        	showMatrix();
   	 	}
    }
    else{
		if(getColorName(c3) == Yellow || getColorName(c1) == Yellow){
        	setMotorSpeed(lm, 10);
        	setMotorSpeed(rm, 10);
        	sleep(200);
        	if(getColorName(c2) == Red){
         		if(row % 2 == 0) S[row][count] = 1;
         		else S[row][(max_count - 1) - count] = 1;
         	showMatrix();
         	playTone(440, 20); sleep(100);
         	setMotorSpeed(lm, 10);
         	setMotorSpeed(rm, 10);
         	sleep(400);
            }
           else if(getColorName(c2) == Blue) {
        		if(row % 2 == 0) S[row][count] = -1;
         		else S[row][(max_count - 1) - count] = -1;
	        	showMatrix();
	        	playTone(440, 20); sleep(100);
	        	setMotorSpeed(lm, 10);
	        	setMotorSpeed(rm, 10);
	        	sleep(200);
	        	}
        	vertex++;
        }
      	else{
					vertex = 0;
        	showMatrix();
        }
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

void completeSearch() {
   while(true) {
      go();

      if(search_init == 0 && count == 4 && row == 0) {
				setMotorSpeed(lm, 20);
				setMotorSpeed(rm, 15);
				sleep(300);
				stopMotor();
				sleep(200);
				if(getColorName(c2) == White) {
					max_row = 4;
					max_count = 4;
					max_matrix = 4;
					back_row = 4;
					back_count = 3;
				}
				else {
					max_row = 3;
					max_count = 5;
					max_matrix = 5;
					back_row = 3;
					back_count = 4;
				}
				search_init++;
			}

      if(count == max_count) {
         if(row == max_row) return;
         if(row % 2 == 0) {
            setMotorSpeed(lm, 40);
            setMotorSpeed(rm, 35);
            for(int i = 0; i < 4; i++) {
               if(getColorName(c2) == Red) {
                  if(row % 2 == 0) S[row][count] = 1;
                  else S[row][max_count - count] = 1;
                  playTone(440, 20);
                  setMotorSpeed(lm, 10);
	        				setMotorSpeed(rm, 10);
	        				sleep(400);
               }
               else sleep(90);
            }
            turnRight();
         }
         else {
            for(int i = 0; i < 3; i++) {
               if(getColorName(c2) == Red) {
                  if(row % 2 == 0) S[row][count] = 1;
                  else S[row][(max_count - 1) - count] = 1;
                  playTone(440, 20);
                  setMotorSpeed(lm, 10);
	        				setMotorSpeed(rm, 10);
	        				sleep(400);
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
         while(getColorName(c1) == White && getColorName(c3) == White) {
            setMotorSpeed(lm, -10);
            setMotorSpeed(rm, -10);
         }
         setMotorSpeed(lm,-10);
         setMotorSpeed(rm,-10);
         sleep(300);

         stopMotor();
         sleep(500);
      }
   }
}

int max(int a, int b) {
   return a > b ? a : b;
}

void goUp() {
   r--; row++;
   displayBigTextLine(1, "%d", r);
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
   displayBigTextLine(4, "%d", c);
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

void go_MovingPoint() {
	while(count_movingPoint < 4) {
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

	   if(getColorName(c1) == Yellow) {
	    setMotorSpeed(lm, 10);
	    setMotorSpeed(rm, 10);
	    vertex++;
	   }
	   else
	   {
	     vertex=0;
	   }

	   if (vertex == 1)
	   {
	     count_movingPoint++;
	   }
	 }
	 stopMotor();
	 sleep(100);
}

task main(){
   while(getButtonPress(1)==0) sleep(10);

   completeSearch();

   stopMotor();
   sleep(2000);

   finalShowMatrix();

   if(max_row == 3) {
    setMotorSpeed(lm, 10);
   	setMotorSpeed(rm, 10);
   	sleep(500);

   	while(getColorName(c2) == White) {
    	setMotorSpeed(lm, -10);
     	setMotorSpeed(rm, 10);
     	sleep(20);
   	}
   	sleep(100);

   	go_MovingPoint();
   }



   playTone(420, 20);
   sleep(50);

   setMotorSpeed(lm, 10);
   setMotorSpeed(rm, 10);
   sleep(1000);

   playTone(420, 20);
   sleep(50);

   stopMotor();
   sleep(1000);


   playTone(420, 20);
   sleep(50);

   while(getColorName(c2) == White) {
     setMotorSpeed(lm, 10);
     setMotorSpeed(rm, -10);
     sleep(20);
   }
   sleep(100);

   stopMotor();
   sleep(1000);

   playSound(soundBeepBeep);
   sleep(1000);

   /*while(getColorName(c3) == White) {
     setMotorSpeed(lm, -10);
     setMotorSpeed(rm, -10);
   }
   sleep(400);//YOONSIK

   stopMotor(); */
   setMotorSpeed(lm, -10);
   setMotorSpeed(rm, -10);
   sleep(200);

   count = row = 0;

   //matrix_max -> 5
   for(int i = 0; i < 5; i++) {
      for(int j = 0; j < 5; j++) {
         if(i == 0 && j == 0) dt[i][j] = S[i][j];
         else if(i == 0) dt[i][j] = dt[i][j-1] + S[i][j];
         else if(j == 0) dt[i][j] = dt[i-1][j] + S[i][j];
         else dt[i][j] = max(dt[i-1][j], dt[i][j-1]) + S[i][j];
      }
   }
   row = 0; r = back_row; c = back_count;

	 while(r != 0 || c != 0) {
	    if(r == 0) goLeft();
	    else if(c == 0) goUp();
	    else if(dt[r-1][c] > dt[r][c-1]) {
	    	playTone(440, 20);
	      sleep(80);
	      goUp();
	    }
	    else {
	      playTone(440, 20);
	      sleep(80);
	      goLeft();
	    }
	    eraseDisplay();
	    //displayBigTextLine(1, "%d %d(%d)", r, c, row);
	 		showScore();
	 }

   playTone(240, 20); sleep(100);
   stopMotor();
   while(getButtonPress(1) == 0) sleep(10);
}
//Delete

/*if(row == 3){
	row = 4;
	while(count != 4)go();
}*/
