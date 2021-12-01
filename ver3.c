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

int nMotorSpeedSetting=30, vertex=0, count =0, row=0, val, r, c, c_suc=15;
int S[6][6], dt[6][6];

// Showing Matrix
void showMatrix()
{
   for(int i=0;i<5;i++)
   {
      displayBigTextLine(1, "%d", count);
      displayBigTextLine(3 + i*2,"%d %d %d %d %d",S[i][0],S[i][1],S[i][2],S[i][3],S[i][4]);
   }
}

// Stopping Matrix
void stopMotor(){
   setMotorSpeed(lm,0);
   setMotorSpeed(rm,0);
}

// Going Front
void go()
{
   // val: value for one sensor tracing
   val = 4;
   // if c2(middle) got red, set S
   // pass and add count
   if(getColorName(c2) == Red)
   {
      if(row % 2 == 0) S[row][count] = 1;
      else S[row][4 - count] = 1;
      playTone(440, 20); sleep(100);
      // get out on vertex
      setMotorSpeed(lm, 35);
      setMotorSpeed(rm, 35);
      sleep(400);
      count++;
   }
   // if c2(middle) got yellow or white, do one sensor tracing
   if(getColorName(c2) == Yellow)
   {
      setMotorSpeed(lm, nMotorSpeedSetting - val);
      setMotorSpeed(rm, nMotorSpeedSetting + val);
   }
   else {
      setMotorSpeed(lm, nMotorSpeedSetting + val);
      setMotorSpeed(rm, nMotorSpeedSetting - val);
   }

   //if c1(left) or c3(right) got yellow, it means you are on vertex
   if (getColorName(c1) == Yellow || getColorName(c3) == Yellow)
   {
     sleep(50);
     // if your c1 or c3 got yellow faster than c2 got red
     if(getColorName(c2) == Red)
     {
         if(row % 2 == 0) S[row][count] = 1;
         else S[row][4 - count] = 1;
         // get out on vertex
         setMotorSpeed(lm, 35);
         setMotorSpeed(rm, 35);
         sleep(200);
     }
     vertex++;
   }
   // if c1 and c3 both didn't got yellow, it means you aren't on vertex
   // clear vertex
   else vertex = 0;
   // if c1 or c3 got vertex, add count
   if(vertex == 1)
   {
      count++;
   }
}


void turnLeft()
{
    // To do Point Turn, move front slightly
   setMotorSpeed(lm,30);
   setMotorSpeed(rm,30);
   sleep(400);

   // Turn Left until c2(middle) get yellow
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
   //to prevent stop turning exactly when c2 got yellow, do sleep
   sleep(50);
   // Stop it
   setMotorSpeed(lm,0);
   setMotorSpeed(rm,0);
   sleep(1000);
}

void turnRight(){
   // To do Point Turn, move front slightly
   setMotorSpeed(lm,30);
   setMotorSpeed(rm,30);
   sleep(400);

   // Turn left until c2(middle) get yellow
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
    // to prevent stop turning exactly when c2(middle) got yellow, do sleep
   sleep(50);
   // Stop it
   setMotorSpeed(lm,0);
   setMotorSpeed(rm,0);
   sleep(1000);
}

void completeSearch() {
   while(true) {
      // ends with count added or not
      go();
      // if count is 5(end of row)
      if(count == 5) {
         if(row == 4) return;
         if(row % 2 == 0) {
            turnRight();
         }
         else {
            turnLeft();
         }
         if(row % 2 == 0) {
            while(getColorName(c3) == White) go();
            turnRight();
         }
         else {
            while(getColorName(c1) == White) go();
            turnLeft();
         }
         row++;
         count = 0;
         while(getColorName(c1) == White && getColorName(c3) == White) {
            setMotorSpeed(lm, -15);
            setMotorSpeed(rm, -15);
        }
        sleep(600);
      }
   }
}

int max(int a, int b) {
   return a > b ? a : b;
}

void goUp() {
   r--; row++;
   displayBigTextLine(4, "Going Up %d", r);
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
   displayBigTextLine(7, "Going Left %d", c);
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

   while(getColorName(c3) == White) {
     setMotorSpeed(lm, 10);
     setMotorSpeed(rm, -10);
     sleep(20);
   }
   sleep(100);

   stopMotor();
   sleep(1000);

   playSound(soundBeepBeep);
   sleep(1000);

   setMotorSpeed(lm, -15);
   setMotorSpeed(rm, -10);
   sleep(2000);//YOONSIK

   stopMotor();
   sleep(1000);

   count = row = 0;

   for(int i = 0; i < 5; i++) {
      for(int j = 0; j < 5; j++) {
         if(i == 0 && j == 0) dt[i][j] = S[i][j];
         else if(i == 0) dt[i][j] = dt[i][j-1] + S[i][j];
         else if(j == 0) dt[i][j] = dt[i-1][j] + S[i][j];
         else dt[i][j] = max(dt[i-1][j], dt[i][j-1]) + S[i][j];
      }
   }

   row = 0; r = c = 4;

   while(r != 0 || c != 0) {
      displayBigTextLine(1, "%d %d(%d)", r, c, row);
      if(r == 0) goLeft();
      else if(c == 0) goUp();
      else if(dt[r-1][c] > dt[r][c-1]) goUp();
      else goLeft();
   }

   playTone(240, 20); sleep(200);
   stopMotor();
   while(getButtonPress(1) == 0) sleep(10);
}
