#include <stdio.h>
#define INF 123456789
#define SIZE 25

int graph[5][5] = {
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,-1,0},
    {0,0,-1,1,0},
    {0,0,0,-1,0}
};

int spMatrix[5][5][50];
int tmp_path[50];
int red_list[25];
int visited[25];
int visited_red[25];

int dx[4] = { 1,-1, 0, 0};
int dy[4] = { 0, 0, 1,-1};

int tmpx;
int tmpy;


void initList(int list[25],int value)
{
    for(int i=0;i<25;i++)
    {
        list[i] = value;
    }
}

// coordinate(좌표) to index
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
    if (spMatrix[start_x][start_y][0] == -1) return -INF;
    itoc(spMatrix[start_x][start_y][0]);
    int sx = tmpx, sy = tmpy;
    int score = 0;
    initList(visited_red,0);
    if (graph[sx][sy] == 1)
    {
        score += 5;
        visited_red[spMatrix[start_x][start_y][0]] = 1;
    } 
    else if (graph[sx][sy] == -1) score -= 5;

    int x,y;
    for(int i = 1; spMatrix[start_x][start_y][i] != -1; i++)
    {
        score -= 1;
        itoc(spMatrix[start_x][start_y][i]);
        x=tmpx;
        y=tmpy;
        if(graph[x][y] == 1)
        {
            if (visited_red[spMatrix[start_x][start_y][i]] == 1)
                score -= 5;
            else
            {
                visited_red[spMatrix[start_x][start_y][i]] = 1;
                score += 5;
            }
        }
        else if (graph[x][y] == -1) score -= 5;
    }
    return score;
}

int evalStack_tmp()
{
    printf("abc\n");
    if (tmp_path[0] == -1) return -INF;
    printf("pass INF\n");
    itoc(tmp_path[0]);
    int sx = tmpx, sy = tmpy;
    int score = 0;
    initList(visited_red,0);
    printf("pass visited_red\n");
    if (graph[sx][sy] == 1)
    {
        score += 5;
        visited_red[tmp_path[0]] = 1;
    } 
    else if (graph[sx][sy] == -1) score -= 5;

    int x,y;
    for(int i = 1; tmp_path[i] != -1; i++)
    {
        score -= 1;
        itoc(tmp_path[i]);
        x=tmpx;
        y=tmpy;
        if(graph[x][y] == 1)
        {
            if (visited_red[tmp_path[i]] == 1)
                score -= 5;
            else
            {
                visited_red[tmp_path[i]] = 1;
                score += 5;
            }
        }
        else if (graph[x][y] == -1) score -= 5;
    }
    return score;
}

void setPath(int x, int y, int value)
{
    printf("setPath\n");
    int i = 0;
    initList(tmp_path,-1);
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            printf("spMatrix[%d][%d]: ",i,j);
            for(int k=0; k<50; k++){
                printf(" %2d",spMatrix[i][j][k]);
            }
            printf("\n");
        }
    }
    printf("x: %d y:%d\n",x,y);
    for (;spMatrix[x][y][i] != -1; i++)
    {
        printf("spMatrix[%d][%d][%2d] : %d\n",x,y,i,spMatrix[x][y][i]);
        tmp_path[i] = spMatrix[x][y][i];
    }
    tmp_path[i] = value;
    for (int i = 0; i < 50; i++)
    {
        printf("%d ", tmp_path[i]);
    }
    printf("\n");
}

void copyPath(int x, int y)
{
    int i=0;
    for(int j=0;j<50;j++)
    {
        spMatrix[x][y][j] = -1;
    }
    for (;tmp_path[i] != -1; i++)
    {
        spMatrix[x][y][i] = tmp_path[i];
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
                printf("near_x : %d, near_y: %d, ctoi: %d\n", near_x, near_y, ctoi(near_x,near_y));
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

void calSP(int start, int end)
{
    itoc(start);
    int start_x = tmpx;
    int start_y = tmpy;
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            for(int k=0; k<50; k++){
                spMatrix[i][j][k] = -1;
                printf("spMatrix[%d][%d][%2d] : %d\n",i,j,k,spMatrix[i][j][k]);
            }
        }
    }
    spMatrix[start_x][start_y][0] = start;
    itoc(end);
    int end_x = tmpx;
    int end_y = tmpy;
    int order[25] = {24,23,19,22,18,14,21,17,13,9,20,16,12,8,4,15,11,7,3,10,6,2,5,1,0};
    int index = 0;

    initList(tmp_path,-1);
    while (index < SIZE)
    {
        itoc(order[index]);
        if (visited[order[index]]) index += 1;
        else
        {
            printf("hello\n");
            int next_check = reroll(order[index]);
            if (next_check == 1)
            {
                index = 0;
            }
        }   
    }
    printf("End's score is : %d\n", evalStack(end_x,end_y));
    printf("End's route is: %d ",spMatrix[end_x][end_y][0]);
    for (int i = 1; spMatrix[end_x][end_y][i] != -1; i++)
    {
        printf("->%d", spMatrix[end_x][end_y][i]);
    }
    printf("\n");
}

int main(void)
{
    calSP(24,0);
}