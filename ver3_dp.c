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

int nMotorSpeedSetting=35, vertex=0, count =0, row=0, val, r, c, i, j, f, e;
int S[6][6], dt[6][6], d[6], J[6][6];

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
      vertex++;
   }
   if(getColorName(c2) == Blue)
   {
      if(row % 2 == 0) S[row][count] = -1;
      else S[row][4 - count] = -1;
      playTone(440, 20); sleep(100);
      vertex++;
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
      // check vertex slowly
      setMotorSpeed(lm, nMotorSpeedSetting * 5/10);
      setMotorSpeed(rm, nMotorSpeedSetting * 5/10);
      sleep(50);
      // if your c1 or c3 got yellow faster than c2 got red
      if(getColorName(c2) == Red)
      {
            if(row % 2 == 0) S[row][count] = 1;
            else S[row][4 - count] = 1;
            // get out on vertex
            setMotorSpeed(lm, nMotorSpeedSetting);
            setMotorSpeed(rm, nMotorSpeedSetting);
            sleep(400);
      }
      if(getColorName(c2) == Blue)
      {
         if(row % 2 == 0) S[row][count] = -1;
         else S[row][4 - count] = -1;
         playTone(440, 20); sleep(100);
         vertex++;
      }  
      vertex++;
   }
   // if c1 and c3 both didn't got yellow, it means you aren't on vertex
   // clear vertex
   else vertex = 0;
   // if c1 or c3 got vertex(it can be over 1, but logic only compare vertex with number 1), add count
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
   sleep(100);
}

void turnRight(){
   // To do Point Turn, move front slightly
   setMotorSpeed(lm,30);
   setMotorSpeed(rm,30);
   sleep(400);

   // Turn Right until c2(middle) get yellow
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
   // For getting back on track, it's good turn lower
   sleep(50);
   // Stop it
   setMotorSpeed(lm,0);
   setMotorSpeed(rm,0);
   sleep(100);
}

void completeSearch() {
   while(true) {
      // ends with count added or not
      go();
      // if count is 5(end of row)
      if(count == 5) {
         if(row == 4) return;
         // if you are on the end of even row
         if(row % 2 == 0) {
            // Junhyung: I commented this block because it's same action in turn right;
            // setMotorSpeed(lm,35);
            // setMotorSpeed(rm,30);
            // sleep(400);

            // uncomment this block if you need to check corner red
            // for (int i = 0; i < 4; i++)
            // {
            //    if(getColorName(c2) == Red)
            //    {
            //       if(row % 2 == 0) S[row][count] = 1;
            //       else S[row][4-count] = 1;
            //       playTone(440,20);
            //       sleep(80);
            //    }
            //    if(getColorName(c2) == Blue)
            //    {
            //       if(row % 2 == 0) S[row][count] = -1;
            //       else S[row][4 - count] = -1;
            //       playTone(440, 20); sleep(100);
            //       vertex++;
            //    }
            // }
            turnRight();
            while(getColorName(c3) == White) go();
            // setMotorSpeed(lm,35);
            // setMotorSpeed(rm,30);
            // sleep(400);
            turnRight();
         }
         // if you are on the end of odd row
         else {
            // setMotorSpeed(lm,30);
            // setMotorSpeed(rm,35);
            // sleep(400);

            // uncomment this block if you need to check corner red
            // for (int i = 0; i < 4; i++)
            // {
            //    if(getColorName(c2) == Red)
            //    {
            //       if(row % 2 == 0) S[row][count] = 1;
            //       else S[row][4-count] = 1;
            //       playTone(440,20);
            //       sleep(80);
            //    }
            //    if(getColorName(c2) == Blue)
            //    {
            //       if(row % 2 == 0) S[row][count] = -1;
            //       else S[row][4 - count] = -1;
            //       playTone(440, 20); sleep(100);
            //       vertex++;
            //    }
            // }
            turnLeft();
            while(getColorName(c1) == White) go();
            // setMotorSpeed(lm,30);
            // setMotorSpeed(rm,35);
            // sleep(400);
            turnLeft();
         }
         row++;
         count = 0;
         while(getColorName(c1) == White && getColorName(c3) == White) {
            setMotorSpeed(lm, -15);
            setMotorSpeed(rm, -15);
        }
        // to start on back, control this time
        sleep(600);
      }
   }
}

int max(int a, int b) {
   return a > b ? a : b;
}

void goUp() {
   // Since robot go up, row should become lower.
   // var row: to count row from bottom to top
   r--; row++;
   displayBigTextLine(4, "Going Up %d", r);
   // robot always goes on row direction, so robot should turn right;
   turnRight();
   // init count
   count = 0;
   while(true) {
      // move until robot count vertex
      go();
      if(count == 1) {
         // sleep(300);
         turnLeft();
         break;
      }
   }
}

void goLeft() {
   // c(variable for coordinate) should become lower.
   // var c: to count
   c--;
   displayBigTextLine(7, "Going Left %d", c);
   // init count
   count = 0;
   while(true) {
      go();
      if(count == 1) {
         // go ends on vertex'x start, so move slightly to be on node.
         setMotorSpeed(lm, 30);
         setMotorSpeed(rm, 30);
         sleep(400);
         break;
      }
   }
}

void goDown()
{
   r++; row--;
   turnLeft();
   count = 0;
   while(true)
   {
      go();
      if (count == 1)
      {
         sleep(300);
         turnRight();
         break;
      }
   }
}


task main()
{
   while(getButtonPress(1)==0) sleep(10);
   completeSearch();

   playTone(420, 20); sleep(50);

   setMotorSpeed(lm, 10);
   setMotorSpeed(rm, 10);
   sleep(1000);

   playTone(520, 20); sleep(50);

   while(getColorName(c3) == White) {
     setMotorSpeed(lm, 10);
     setMotorSpeed(rm, -10);
   }
   while(getColorName(c2) == White) {
     setMotorSpeed(lm, 10);
     setMotorSpeed(rm, -10);
   }
   sleep(100);

   setMotorSpeed(lm, -10);
   setMotorSpeed(rm, -10);
   sleep(1000);//YOONSIK

   stopMotor();
   sleep(1000);

   count = row = 0;
   for(f=4; f>=0; f--)
		for(e=4; e>=0; e--)
      {
			if( e==4 && f==4) dt[e][f] = S[e][f];
			else if(f == 4) dt[e][f] = dt[e+1][f] + S[e][f];
			else
			{
				dt[e][f] = -10;
				for(i=0; i<=4; i++)
            {
					d[i] = dt[i][f+1];
					if(i > e)
               {
						for(j=i; j>=e; j--)
						   d[i] += S[j][f];
					}
					else if(i == e)
               {
						d[i] += S[i][f];
					}
					else
               {
						for(j=i; i<=e; j++)
						   d[i]+=S[j][f];
					}
					if(dt[e][f]<d[i])
               {
						dt[e][f] = d[i];
						J[e][f] = i;
					}
				}
			}
		}
   row = 0; r = c = 4;
   d[0]=0;
   for(i=0; i<=4; i++)
   {
      d[i+1] = J[d[i]][i];
   }
   for(i=4; i>0; i--)
   {
      if(r > d[i])
      {
         while(r > d[i]) goUp();
         goLeft();
      }
      else if(r == d[i])
      {
         goLeft();
      }
      else
      {
         while(r < d[i]) goDown();
         goLeft();
      }
   }

   playTone(240, 20); sleep(200);
   stopMotor();
   while(getButtonPress(1) == 0) sleep(10);
}
