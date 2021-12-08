#include <stdio.h>

#define INF 123456789
#define SIZE 25

int spMatrix[25][50];
int spMatrix_copy[25][50];
int tmp_path[50];
int answer[50];
int visited[25];
int visited_red[25];

int isSecond = 0;

int dx[4] = { 1,-1, 0, 0};
int dy[4] = { 0, 0, 1,-1};

int tmpx;
int tmpy;

int n_index = 1;
int dif_x, dif_y;

int nMotorSpeedSetting=25, vertex=0, count =0, row=0, val, r, c, c_suc=15, max_row = 4, max_count = 5, max_matrix = 5, search_init = 0, count_movingPoint = 0, back_row = 4, back_count = 4;
// int S[6][6], dt[6][6];
int dt[6][6];

int S[5][5] = {
    {0,1,0,1,0},
    {1,0,0,0,0},
    {0,1,0,1,0},
    {0,0,1,-1,0},
    {0,0,0,1,0}
};

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

// coordinate(?) to index
int ctoi(int x, int y)
{
    return 5 * x + y; 
}

// return values to tmpx,tmpy;
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
    // initList(visited_red,0);
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
    // initList(visited_red,0);
    initList_visited(0);
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
    // initList(visited_red,0);
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
    // initList(tmp_path,-1);
    initList_tmpPath(-1);
    // for(int i=0; i<5; i++)
    // {
    //     for(int j=0; j<5; j++)
    //     {
    //         printf("spMatrix[%d][%d]: ",i,j);
    //         for(int k=0; k<50; k++){
    //             printf(" %2d",spMatrix[ctoi(i,j)][k]);
    //         }
    //         printf("\n");
    //     }
    // }
    // printf("\n\n");
    // printf("x: %d y:%d\n",x,y);
    for (;spMatrix[ctoi(x,y)][i] != -1; i++)
    {
        // printf("spMatrix[%d][%d][%2d] : %d\n",x,y,i,spMatrix[ctoi(x,y)][i]);
        tmp_path[i] = spMatrix[ctoi(x,y)][i];
    }
    tmp_path[i] = value;
    // for (int i = 0; i < 50; i++)
    // {
    //     printf("%d ", tmp_path[i]);
    // }
    // printf("\n");
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

    int index = 0;
    // initList(tmp_path, -1);
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
    }

    printf("End's score is : %d\n", evalStack(end_x,end_y));
    printf("End's route is: %d ",spMatrix[ctoi(end_x,end_y)][0]);
    for (int i = 1; spMatrix[ctoi(end_x,end_y)][i] != -1; i++)
    {
        printf("->%d", spMatrix[ctoi(end_x,end_y)][i]);
    }
    printf("\n");
}

void calc_Shortcut(int choice) {

    if(max_row == 4) {
        calSP(23, 0, choice);
    }
    else {
        calSP(19, 0, choice);
    }

    isSecond += 1;
    // initList(visited, 0);
    initList_visited(0);

    for(int i = 0; i<25; i++)
    {
        for(int k = 0; k <50; k++)
        {
            spMatrix_copy[i][k] = spMatrix[i][k];
        }
    }

    printf("%s\n", "first end");

    if(max_row == 4) {
        calSP(23, 0, choice);
    }
    else {
        calSP(19, 0, choice);
    }

    printf("%s\n", "second end");

    if (evalStack_copy(0,0) > evalStack(0,0))
    {
        printf("copy : %d\n", evalStack_copy(0,0));
        for(int i = 0; i < 50; i++)
        {
            answer[i] = spMatrix_copy[0][i];
        }
    }
    else
    {
        printf("original : %d\n", evalStack(0,0));
        for(int i = 0; i < 50; i++)
        {
            answer[i] = spMatrix[0][i];
        }
    }

}


int main(){
//    while(getButtonPress(1)==0) sleep(10);

//    completeSearch();

//    stopMotor();
//    sleep(2000);
   
   //choice 0: 4x5
   //choice 1: 5x4
   int choice = 0;
   if (choice == 0){
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
    calc_Shortcut(choice);

    while (answer[n_index] != -1)
    {
        itoc(answer[n_index]);
        c = back_count;
        r = back_row;
        dif_x = tmpx - r;
        dif_y = tmpy - c;
        if (dif_x == 1 && dif_y == 0)
        {
            printf("%s\n", "goDown");   
        }
        else if (dif_x == -1 && dif_y == 0)
        {
            printf("%s\n", "goDown");
        }
        else if (dif_x == 0 && dif_y == -1)
        {
            printf("%s\n", "goDown");
        }
        else if (dif_x == 0 && dif_y == 1)
        {
            printf("%s\n", "goDown");
        }
        n_index += 1;
    }

//    finalShowMatrix();

//    if(max_row == 3) {
//     setMotorSpeed(lm, 10);
//       setMotorSpeed(rm, 10);
//       sleep(500);

//       while(getColorName(c2) == White) {
//        setMotorSpeed(lm, -10);
//         setMotorSpeed(rm, 10);
//         sleep(20);
//       }
//       sleep(100);

//       go_MovingPoint();
//    }



//    playTone(420, 20);
//    sleep(50);

//    setMotorSpeed(lm, 10);
//    setMotorSpeed(rm, 10);
//    sleep(1000);

//    playTone(420, 20);
//    sleep(50);

//    stopMotor();
//    sleep(1000);


//    playTone(420, 20);
//    sleep(50);

//    while(getColorName(c2) == White) {
//      setMotorSpeed(lm, 10);
//      setMotorSpeed(rm, -10);
//      sleep(20);
//    }
//    sleep(100);

//    stopMotor();
//    sleep(1000);

//    playSound(soundBeepBeep);
//    sleep(1000);

   /*while(getColorName(c3) == White) {
     setMotorSpeed(lm, -10);
     setMotorSpeed(rm, -10);
   }
   sleep(400);//YOONSIK
   stopMotor(); */
//    setMotorSpeed(lm, -10);
//    setMotorSpeed(rm, -10);
//    sleep(200);

//   count = row = 0;

//    while (answer[n_index] != -1)
//     {
//         itoc(answer[n_index]);
//         dif_x = tmpx - r;
//         dif_y = tmpy - c;
//         if (dif_x == 1 && dif_y == 0)
//         {
//             goDown();   
//         }
//         else if (dif_x == -1 && dif_y == 0)
//         {
//             goUp();
//         }
//         else if (dif_x == 0 && dif_y == -1)
//         {
//             goLeft();
//         }
//         else if (dif_x == 0 && dif_y == 1)
//         {
//             goRight();
//         }
//         n_index += 1;
//     }


//    //matrix_max -> 5
//    for(int i = 0; i < 5; i++) {
//       for(int j = 0; j < 5; j++) {
//          if(i == 0 && j == 0) dt[i][j] = S[i][j];
//          else if(i == 0) dt[i][j] = dt[i][j-1] + S[i][j];
//          else if(j == 0) dt[i][j] = dt[i-1][j] + S[i][j];
//          else dt[i][j] = max(dt[i-1][j], dt[i][j-1]) + S[i][j];
//       }
//    }
//    row = 0; r = back_row; c = back_count;

//     while(r != 0 || c != 0) {
//        if(r == 0) goLeft();
//        else if(c == 0) goUp();
//        else if(dt[r-1][c] > dt[r][c-1]) {
//           playTone(440, 20);
//          sleep(80);
//          goUp();
//        }
//        else {
//          playTone(440, 20);
//          sleep(80);
//          goLeft();
//        }
//        eraseDisplay();
//        //displayBigTextLine(1, "%d %d(%d)", r, c, row);
//           showScore();
//     }

//    playTone(240, 20); sleep(100);
//    stopMotor();
//    while(getButtonPress(1) == 0) sleep(10);
}
//Delete

/*if(row == 3){
   row = 4;
   while(count != 4)go();
}*/