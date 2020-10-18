#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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

void print(int a[][4], int chk)
{
    if (chk)
    {
        printf("\n\n");
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                if (a[i][j])
                    printf("%d\t", a[i][j]);
                else
                    printf(" \t");
            printf("\n\n");
        }
    }
    else
    {
        printf("no\n");
    }
}

int main()
{
    int a[4][4]={
        0,
    };
    srand(time(0));
    a[rand()%4][rand()%4]=2;
    print(a,1);
    // 함수호출하여 출력
    while (check(a))
    {
        char c;
        scanf("%c", &c);
        int k = 0;
        if (c == 'W' || c == 'w')
        {
            k = up(a);
        }
        else if (c == 'A' || c == 'a')
        {
            turn(a);
            turn(a);
            turn(a);
            k = up(a);
            turn(a);
        }
        else if (c == 'S' || c == 's')
        {
            turn(a);
            turn(a);
            k = up(a);
            turn(a);
            turn(a);
        }
        else if (c == 'D' || c == 'd')
        {
            turn(a);
            k = up(a);
            turn(a);
            turn(a);
            turn(a);
        }
        else
        {
            continue;
        }
        if (k)
        {
            int cnt = 0;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    if (a[i][j] == 0)
                        cnt++;
            if (cnt == 0)
                continue;
            int now = rand() % cnt;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                {
                    if (a[i][j] == 0)
                    {
                        if (now == 0)
                            a[i][j] = (rand()%5>3)*2+2;
                        now--;
                    }
                }
        }
        print(a, k);
    }
    printf("GAME OVER\n");
}