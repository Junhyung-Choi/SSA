// 스마트 센서와 액츄에이터 3조
// 조원: 최준형 / 김교원 / 정운 / 지훈 / 김윤식
#define INF 123456789

void showMatrix(int a[5][5])
{
    for(int i=0;i<5;i++)
    {
        if (a[i][4] == -INF)
        {
            displayBigTextLine(3*i+1, "%d %d %d %d",a[i][0],a[i][1],a[i][2],a[i][3]);
        }
        else if(i<4)
        {
            displayBigTextLine(3*i+1, "%d %d %d %d %d",a[i][0],a[i][1],a[i][2],a[i][3],a[i][4]);
        }
    }
}
