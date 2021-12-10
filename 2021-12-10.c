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

#define INF 123456789
#define SIZE 20

int nMotorSpeedSetting=25, vertex=0, count =0, row=0, val, r, c, c_suc=15, max_row = 4, max_count = 5, max_matrix = 5, search_init = 0, count_movingPoint = 0, back_row = 4, back_count = 4;
int S[6][6], dt[6][6];
int choice = 0, isSecond = 0, final_score;

short spMatrix[25][50];
short spMatrix_copy[25][50];
int tmp_path[50];
int answer[50];
int visited[25];
int visited_red[25];

int dx[4] = { 1,-1, 0, 0};
int dy[4] = { 0, 0, 1,-1};

int tmpx;
int tmpy;

int n_index = 1;
int dif_x, dif_y;

/* void initList(int* list,int value)
{
    for(int i=0;i<25;i++)
    {
        list[i] = value;
    }
} */

void initList_visited(int value)
{
    for(int i=0;i<25;i++)
    {
        visited[i] = value;
    }
}

void initList_tmpPath(int value)
{
    for(int i=0;i<25;i++)
    {
        tmp_path[i] = value;
    }
}

void initList_visitedRed(int value)
{
    for(int i=0;i<25;i++)
    {
        visited_red[i] = value;
    }
}

int ctoi(int x, int y)
{
    return 5 * x + y;
}

void itoc(int index)
{
    tmpx = index / 5;
    tmpy = index % 5;
}

int evalStack(int start_x, int start_y)
{
    int index = ctoi(start_x, start_y);
    if (spMatrix[ctoi(start_x,start_y)][0] == -1) return -INF;
    itoc(spMatrix[ctoi(start_x,start_y)][0]);
    int sx = tmpx, sy = tmpy;
    int score = 0;
    //initList(visited_red,0);
    initList_visitedRed(0);
    if (S[sx][sy] == 1)
    {
        score += 5;
        int r_index = spMatrix[index][0];
        visited_red[r_index] = 1;
    }
    else if (S[sx][sy] == -1) score -= 5;

    int x,y;
    for(int i = 1; spMatrix[index][i] != -1; i++)
    {
        score -= 1;
        itoc(spMatrix[ctoi(start_x,start_y)][i]);
        x=tmpx;
        y=tmpy;
        if(S[x][y] == 1)
        {
            int r_index = spMatrix[index][i];
            if (visited_red[r_index] == 1)
                score -= 5;
            else
            {
                  int r_index = spMatrix[index][i];
                visited_red[r_index] = 1;
                score += 5;
            }
        }
        else if (S[x][y] == -1) score -= 5;
    }
    return score;
}

int evalStack_copy(int start_x, int start_y)
{
    int index = ctoi(start_x, start_y);
    if (spMatrix_copy[ctoi(start_x,start_y)][0] == -1) return -INF;
    itoc(spMatrix_copy[ctoi(start_x,start_y)][0]);
    int sx = tmpx, sy = tmpy;
    int score = 0;
    //initList(visited_red,0);
    initList_visitedRed(0);
    if (S[sx][sy] == 1)
    {
        score += 5;
        int r_index = spMatrix_copy[index][0];
        visited_red[r_index] = 1;
    }
    else if (S[sx][sy] == -1) score -= 5;

    int x,y;
    for(int i = 1; spMatrix_copy[index][i] != -1; i++)
    {
        score -= 1;
        itoc(spMatrix_copy[ctoi(start_x,start_y)][i]);
        x=tmpx;
        y=tmpy;
        if(S[x][y] == 1)
        {
            int r_index = spMatrix_copy[index][i];
            if (visited_red[r_index] == 1)
                score -= 5;
            else
            {
                  int r_index = spMatrix_copy[index][i];
                visited_red[r_index] = 1;
                score += 5;
            }
        }
        else if (S[x][y] == -1) score -= 5;
    }
    return score;
}

int evalStack_tmp()
{
    if (tmp_path[0] == -1) return -INF;
    itoc(tmp_path[0]);
    int sx = tmpx, sy = tmpy;
    int score = 0;
    //initList(visited_red,0);
    initList_visitedRed(0);
    if (S[sx][sy] == 1)
    {
        score += 5;
        visited_red[tmp_path[0]] = 1;
    }
    else if (S[sx][sy] == -1) score -= 5;

    int x,y;
    for(int i = 1; tmp_path[i] != -1; i++)
    {
        score -= 1;
        itoc(tmp_path[i]);
        x=tmpx;
        y=tmpy;
        if(S[x][y] == 1)
        {
            if (visited_red[tmp_path[i]] == 1)
                score -= 5;
            else
            {
                visited_red[tmp_path[i]] = 1;
                score += 5;
            }
        }
        else if (S[x][y] == -1) score -= 5;
    }
    return score;
}

void setPath(int x, int y, int value)
{
    int i = 0;
    //initList(tmp_path,-1);
    initList_tmpPath(-1);

    for (;spMatrix[ctoi(x,y)][i] != -1; i++)
    {
        tmp_path[i] = spMatrix[ctoi(x,y)][i];
    }
    tmp_path[i] = value;
}

void copyPath(int x, int y)
{
    int i=0;
    for(int j=0;j<50;j++)
    {
        spMatrix[ctoi(x,y)][j] = -1;
    }
    for (;tmp_path[i] != -1; i++)
    {
        spMatrix[ctoi(x,y)][i] = tmp_path[i];
    }
}

int reroll(int origin)
{
    itoc(origin);
    int origin_x = tmpx;
    int origin_y = tmpy;
    int ret = 0;
    for(int i=0; i<4; i++)
    {
        int near_x = origin_x + dx[i];
        int near_y = origin_y + dy[i];
        if (0 <= near_x && near_x <= 4 && 0 <= near_y && near_y <= 4)
        {

            setPath(origin_x,origin_y,ctoi(near_x,near_y));
            if (evalStack(near_x,near_y) <= evalStack_tmp())
            {
                copyPath(near_x,near_y);
                if(visited[ctoi(near_x,near_y)])
                {
                    ret = 1;
                    visited[ctoi(near_x,near_y)] = 0;
                }
            }
        }
    }
    visited[origin] = 1;
    return ret;
}

void calSP(int start_loc, int end, int choice)
{
    itoc(start_loc);
    int start_x = tmpx;
    int start_y = tmpy;
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            for(int k=0; k<50; k++){
                spMatrix[ctoi(i,j)][k] = -1;
            }
        }
    }
    playTone(440, 20); sleep(50);
    spMatrix[ctoi(start_x,start_y)][0] = start_loc;
    itoc(end);
    int end_x = tmpx;
    int end_y = tmpy;
    int order[20];
    if(choice == 0){
        if (isSecond == 0){
            int order_tmp[20] = {23,22,18,21,17,13,20,16,12,8,15,11,7,3,10,6,2,5,1,0};
            for(int i=0;i<20;i++) order[i] = order_tmp[i];
        }
        else
        {
            int order_tmp[20] = {23,18,22,13,17,21,8,12,16,20,3,7,11,15,2,6,10,1,5,0};
            for(int i=0;i<20;i++) order[i] = order_tmp[i];
        }
    }
    else
    {
         if(isSecond == 0)
        {
            int order_tmp[20] = {19,14,18,9,13,17,4,8,12,16,3,7,11,15,2,6,10,1,5,0};
            for(int i=0;i<20;i++) order[i] = order_tmp[i];
        }
        else
        {
            int order_tmp[20] = {19,18,14,17,13,9,16,12,8,4,15,11,7,3,10,6,2,5,1,0};
            for(int i=0;i<20;i++) order[i] = order_tmp[i];
        }
    }
    playTone(600, 20); sleep(50);

    int index = 0;
    //initList(tmp_path, -1);
    initList_tmpPath(-1);

    while (index < SIZE)
    {
        itoc(order[index]);
        if (visited[order[index]]) index += 1;
        else
        {
            int next_check = reroll(order[index]);
            if (next_check == 1)
            {
                index = 0;
            }
        }
        //playTone(440, 20); sleep(500);
    }
}

void calc_Shortcut(int choice) {

    if(max_row == 4) {
        for(int i = 0; i < 5; i++) S[i][4] = -1;
        calSP(23, 0,choice);
    }
    else {
        for(int i = 0; i < 5; i++) S[4][i] = -1;
        calSP(19, 0,choice);
    }

    isSecond += 1;
    //initList(visited, 0);
    initList_visited(0);

    for(int i = 0; i<25; i++)
    {
        for(int k = 0; k <50; k++)
        {
            spMatrix_copy[i][k] = spMatrix[i][k];
        }
    }

    if(max_row == 4) {
        for(int i = 0; i < 5; i++) S[i][4] = -1;
        calSP(23, 0,choice);
    }
    else {
        for(int i = 0; i < 5; i++) S[4][i] = -1;
        calSP(19, 0,choice);
    }
    if (evalStack_copy(0,0) > evalStack(0,0))
    {
    		final_score = evalStack_copy(0,0);
        for(int i = 0; i < 50; i++)
        {
            answer[i] = spMatrix_copy[0][i];
        }
    }
    else
    {
    		final_score = evalStack(0,0);
        for(int i = 0; i < 50; i++)
        {
            answer[i] = spMatrix[0][i];
        }
    }
}

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
   if(max_row == 3)    displayBigTextLine(1,"Score: %d",dt[3][4]);
   else displayBigTextLine(1,"Score: %d",dt[4][3]);
}

void stopMotor(){
   setMotorSpeed(lm,0);
   setMotorSpeed(rm,0);
}

void go()
{
    val = 5;
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
            sleep(300);

            if(getColorName(c2) == Red) {
                if(count == max_count) S[row][0] = 1;
                if(row % 2 == 0) S[row][count] = 1;
                else S[row][(max_count - 1) - count] = 1;
                showMatrix();
                playTone(440, 20); sleep(100);
                setMotorSpeed(lm, 15);
                setMotorSpeed(rm, 15);
                sleep(400);
                playTone(700, 20); sleep(100);
            }
            else if(getColorName(c2) == Blue) {
                if(row % 2 == 0) S[row][count] = -1;
                else S[row][(max_count - 1) - count] = -1;
                showMatrix();
                playTone(440, 20); sleep(100);
                setMotorSpeed(lm, 15);
                setMotorSpeed(rm, 15);
                sleep(400);
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
            sleep(100);
            if(getColorName(c2) == Red){
                if(row % 2 == 0) S[row][count] = 1;
                else S[row][(max_count - 1) - count] = 1;
                showMatrix();
                playTone(440, 20); sleep(100);
                setMotorSpeed(lm, 15);
                setMotorSpeed(rm, 15);
                sleep(400);
                playTone(700, 20); sleep(100);
            }
            else if(getColorName(c2) == Blue) {
                if(row % 2 == 0) S[row][count] = -1;
                else S[row][(max_count - 1) - count] = -1;
                showMatrix();
                playTone(440, 20); sleep(100);
                setMotorSpeed(lm, 15);
                setMotorSpeed(rm, 15);
                sleep(400);
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
	//sleep(150) - 2021-12-10-14:35
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
	//sleep(50)
    sleep(50);
    setMotorSpeed(lm,0);
    setMotorSpeed(rm,0);
    sleep(100);
}

void go_2()
{
    val = 5;
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
            sleep(100);
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
            sleep(100);
            vertex++;
        }
        else
        {
            vertex = 0;
            showMatrix();
        }
    }
   if(vertex == 1) count++;
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
                choice = 0;
            }
            else {
                max_row = 3;
                max_count = 5;
                max_matrix = 5;
                back_row = 3;
                back_count = 4;
                choice = 1;
            }
            search_init++;
        }

        if(count == max_count) {
            if(row == max_row) return;
            if(row % 2 == 0) {
                setMotorSpeed(lm, 40);
                setMotorSpeed(rm, 35);
                sleep(300);
                for(int i = 0; i < 4; i++) {
                    if(getColorName(c2) == Red) {
                        if(row % 2 == 0) S[row][count-1] = 1;
                        else S[row][(max_count - count)] = 1;
                	    playTone(440, 20);
                	    setMotorSpeed(lm, 10);
                	    setMotorSpeed(rm, 10);
                	    sleep(200);
            		}
         		}
            turnRight();
            }
            else {
                setMotorSpeed(lm, 40);
            	setMotorSpeed(rm, 35);
            	sleep(300);
                for(int i = 0; i < 3; i++) {
                    if(getColorName(c2) == Red) {
                        if(row % 2 == 0) S[row][count-1] = 1;
                        else S[row][(max_count - count)] = 1;
                        playTone(440, 20);
                        setMotorSpeed(lm, 10);
                        setMotorSpeed(rm, 10);
                        sleep(200);
                    }
                }
            turnLeft();
         }
         if(row % 2 == 0) {
            while(getColorName(c3) == White) go_2();
            setMotorSpeed(lm, 35);
            setMotorSpeed(rm, 30);
            sleep(400);
            turnRight();
         }
         else {
            while(getColorName(c1) == White) go_2();
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
         sleep(700);

         stopMotor();
         sleep(700);
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
         setMotorSpeed(lm, 40);
        setMotorSpeed(rm, 35);
        sleep(200);
         turnLeft();
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
        if(count == 1)
        {   setMotorSpeed(lm, 40);
            setMotorSpeed(rm, 35);
            sleep(400);
            turnRight();
            break;
        }
    }
}

void goRight()
{
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
   sleep(150);

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

   sleep(150);
   setMotorSpeed(lm,0);
   setMotorSpeed(rm,0);
   sleep(100);
    c++;
    count = 0;

    while(true)
    {
        go();
        if(count == 1)
        {
            setMotorSpeed(lm, 35);
            setMotorSpeed(rm, 40);
            sleep(200);
            turnLeft();
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
            setMotorSpeed(lm, 35);
            setMotorSpeed(rm, 35);
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
        sleep(300);
        while(getColorName(c2) == White) {
            //changed direction - 12/10 15:00
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
    sleep(1500);

    stopMotor();
    sleep(1000);

    while(getColorName(c2) != Yellow) {
        setMotorSpeed(lm, 10);
        setMotorSpeed(rm, -10);
        sleep(20);
    }
    sleep(100);

    stopMotor();
    sleep(1000);

    playSound(soundBeepBeep);
    sleep(1000);

    calc_Shortcut(choice);

    eraseDisplay();
    displayBigTextLine(1, "exit");
    sleep(5000);
    playTone(700,20); sleep(100);

    r = back_row;
    c = back_count;
    row = 0; count = 0;

    while (answer[n_index] != -1)
    {
        itoc(answer[n_index]);
        dif_x = tmpx - r;
        dif_y = tmpy - c;
        if (dif_x == 1 && dif_y == 0)
        {
            goDown();
        }
        else if (dif_x == -1 && dif_y == 0)
        {
            goUp();
        }
        else if (dif_x == 0 && dif_y == -1)
        {
            goLeft();
        }
        else if (dif_x == 0 && dif_y == 1)
        {
            goRight();
        }
        n_index += 1;
    }

    playTone(240, 20); sleep(100);
    stopMotor();
    eraseDisplay();
    displayBigTextLine(1,"Score : %d", final_score);
    while(getButtonPress(1) == 0) sleep(10);
}
