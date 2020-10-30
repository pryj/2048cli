#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
int score=0;

int addnum(){
    return rand()%5?2:4;
}

int check(int a[][4])
{
    int ret = 0; //기본은 밀수 없다고 생각
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            if (a[i][j] == a[i + 1][j]) //상하로 밀 수 있음(합쳐짐)
                ret = 1;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            if (a[i][j] == a[i][j + 1]) //좌우로 밀 수 있음(합쳐짐)
                ret = 1;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (a[i][j] == 0) //빈칸이 존재하여 어느 쪽으로든 밀 수 있음
                ret = 1;
    return ret;
}

int up(int a[][4])
{
    int ret = 0;
    int chk[4][4] = {
        0,
    };                          //2048에서 한 번 합쳐진 문자는 그 이동에서 더는 합쳐지지 않는다.
    for (int i = 1; i < 4; i++) //위에서부터 체크, i=0인 경우 따질 필요X
        for (int j = 0; j < 4; j++)
        {
            int k = i;
            while (k > 0 && a[k][j] != 0)
                if (a[k - 1][j] == 0)
                { //그냥 빈칸 따라 올라감
                    a[k - 1][j] = a[k][j];
                    a[k][j] = 0;
                    k--;
                    ret = 1;
                }
                else if (a[k - 1][j] == a[k][j] && !chk[k - 1][j])
                { //합침,합쳐진 적 있나 체크
                    a[k - 1][j] += a[k][j];
                    score+=a[k - 1][j];
                    a[k][j] = 0;
                    ret = 1;
                    chk[k - 1][j] = 1; //합쳐진 적 있음 표시
                    break;
                }
                else //행동불능
                {
                    break;
                }
        }
    return ret;
}

//회전 코-드
void turn(int a[][4])
{
    int tmp[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            tmp[i][j] = a[i][j];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            a[i][j] = tmp[j][3 - i];
}

//단순 출력 함수이다
void print(int a[][4], int chk)
{
    system("cls");
    
    printf("%30d\n\n",score);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            if (a[i][j])
                printf("%d\t", a[i][j]);
            else
                printf(" \t");
        if(i!=3) printf("\n\n");
    }
    //출력 안하는게 나은 경우
    if (!chk)
    {
        //printf("no\n");
    }
}

int main()
{
    //데이터 읽기
    FILE *fp = stdin;
    int a[4][4] = {
        0,
    };
    //c는 방향
    char c;
    int rnd1 = rand() % 16, rnd2 = rand() % 15;

    a[rnd1 / 4][rnd1 % 4] = addnum();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            rnd2--;
            if (rnd2 == 0)
                a[i][j] = addnum();
        }
    print(a, 1);
    // 함수호출하여 출력
    while (check(a))
    {
        c = getch();
        //printf("%d",c);
        int cnt;
        switch(c){
            case 72: case 119: cnt=0; break;
            case 75: case 97: cnt=3; break;
            case 77: case 100: cnt=1; break;
            case 80: case 115: cnt=2; break;
            case 27: cnt=-2; break;
            default: cnt=-1;
        }
        int k = 0;
        //k는 이동 있었나 검증
        if(cnt==-1)
            continue;
        if(cnt==-2)
            break;
        for(int i=0;i<cnt;i++)turn(a);
        k=up(a);
        for(int i=0;i<4-cnt;i++)turn(a);
        
        //이동이 있었다면 2를 추가 생성
        if (k)
        {
            //빈칸개수 세기
            int cnt = 0;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    if (a[i][j] == 0)
                        cnt++;
            if (cnt == 0)
                continue;
            //어디 넣을지(번째)
            int now = rand() % cnt;
            //now번째를 찾아감
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                {
                    if (a[i][j] == 0)
                    {
                        if (now == 0)
                            //now번째이므로 2투입
                            a[i][j] = addnum();
                        now--;
                    }
                }
        }
        //출력.
        print(a, k); 
    }
    printf("\nGAME OVER\nYOUR SCORE:%d\n",score);
}