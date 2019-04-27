#include <cstring>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int n = 5;
const int maxptime = 5;      //40;
const int maxtotaltime = 15; //10
struct PCB
{
    int id;           //进程标识数
    struct PCB *next; //链指针
    int ptime;        //优先数/轮转时间片数
    int runtime;      //占用cpu时间片数
    int totaltime;    //进程所需的时间片数
    char status;      //进程状态 W：就绪 R：运行 F：完成
    bool operator<(const PCB &a) const
    {
        return ptime < a.ptime;
    }
} *FIN = NULL, *HEAD = NULL, *TAIL = NULL, *RUN = NULL;

//生成并初始化各个进程
void born()
{
    struct PCB *p = new PCB;
    int i;
    HEAD = p;
    srand((unsigned int)time(NULL)); //伪随机发生器种子
    for (i = 1; i < n; ++i)
    {
        p->id = i;
        p->ptime = rand() % maxptime + 1;
        p->runtime = 0;
        p->status = 'W';
        p->totaltime = rand() % maxtotaltime + 1;
        p->next = new PCB;
        p = p->next;
    }
    p->id = i;
    p->ptime = rand() % maxptime + 1;
    p->runtime = 0;
    p->status = 'W';
    p->totaltime = rand() % maxtotaltime + 1;
    p->next = NULL;
    TAIL = p;
}
//调整
void adjust()
{
    priority_queue<struct PCB> q;
    for (struct PCB *p = HEAD; p != NULL; p = p->next)
    {
        q.push(*p);
    }
    for (struct PCB *p = HEAD; p != NULL; p = p->next)
    {
        p->id = q.top().id;
        p->ptime = q.top().ptime;
        p->runtime = q.top().runtime;
        p->status = q.top().status;
        p->totaltime = q.top().totaltime;
        q.pop();
    }
}
void showit()
{
    printf("\nOUTPUT OF PRIORITY\n");
    printf("========================================\n");
    printf("RUNNING PROC.           WAITING QUEUE\n");
    if (RUN)
        printf("   %4d               ", RUN->id);
    else
        printf("                      ");
    for (struct PCB *p = HEAD; p; p = p->next)
    {
        printf("%4d", p->id);
    }
    printf("\n========================================\n");
    printf("%-25s", "ID");
    for (struct PCB *p = FIN; p; p = p->next)
    {
        printf("%4d", p->id);
    }
    printf("\n%-25s", "PRIORITY");
    for (struct PCB *p = FIN; p; p = p->next)
    {
        printf("%4d", p->ptime);
    }
    printf("\n%-25s", "CPUTIME");
    for (struct PCB *p = FIN; p; p = p->next)
    {
        printf("%4d", p->runtime);
    }
    printf("\n%-25s", "ALLTIME");
    for (struct PCB *p = FIN; p; p = p->next)
    {
        printf("%4d", p->totaltime);
    }
    printf("\n%-25s", "STATE");
    for (struct PCB *p = FIN; p; p = p->next)
    {
        printf("%4c", p->status);
    }
    printf("\n%-25s", "NEXT");
    for (struct PCB *p = FIN; p; p = p->next)
    {
        if (!p->next)
            printf("%4d", p->next);
        else
            printf("%4d", p->next->id);
    }
}
//撤销各个进程的空间
void _pop()
{
    struct PCB *q, *p = NULL;
    while (p)
    {
        q = p;
        p = p->next;
        delete q;
    }
}

void priority()
{

    struct PCB *p = NULL;
    //生成进程
    born();
    //调整优先数
    adjust();
    FIN = HEAD;
    showit();
    RUN = HEAD;
    HEAD = HEAD->next;
    RUN->status = 'R';
    showit();
    while (RUN->next || RUN->status != 'F')
    {
        RUN->totaltime -= 1;
        RUN->runtime += 1;
        RUN->ptime -= 3;
        if (RUN->totaltime == 0)
        {
            RUN->status = 'F';
            p = RUN;
            if (HEAD)
            {
                RUN = HEAD;
                HEAD = HEAD->next;
                RUN->status = 'R';
            }
        }
        else if (HEAD && (RUN->ptime <= HEAD->ptime))
        {
            if (p != NULL)
            {
                p->next = HEAD;
            }
            else{
                FIN = HEAD;
            }
            TAIL->next = RUN;
            RUN->next = NULL;
            RUN->status = 'W';
            TAIL = RUN;
            RUN = HEAD;
            HEAD = HEAD->next;
            RUN->status = 'R';
        }
        //显示进程状态
        showit();
    }
    //释放空间
    _pop();
}
void round_robin()
{
    struct PCB *p = NULL;
    born();
    FIN = HEAD;
    showit();
    RUN = HEAD;
    HEAD = HEAD->next;
    RUN->status = 'R';
    showit();
    while (RUN->next || RUN->status != 'F')
    {
        RUN->totaltime -= 1;
        RUN->runtime += 1;
        if (RUN->totaltime == 0)
        {
            RUN->status = 'F';
            p = RUN;
            if (HEAD)
            {
                RUN = HEAD;
                HEAD = HEAD->next;
                RUN->status = 'R';
            }
        }
        else if (HEAD && RUN->runtime % RUN->ptime == 0)
        {
            if (p != NULL)
                p->next = HEAD;
            else
                FIN = HEAD;
            RUN->status = 'W';
            TAIL->next = RUN;
            TAIL = RUN;
            TAIL->next = NULL;
            RUN = HEAD;
            HEAD = HEAD->next;
            RUN->status = 'R';
        }
        showit();
    }
    _pop();
}
int main()
{
    char str[20];
    char a[] = "priority\n", b[] = "round robin\n";
    printf("TYPE THE ALGORTITHM(priority or round robin):");
    fgets(str, 20, stdin);
    if (strcmp(str, a) == 0)
    {
        priority();
    }
    else if (strcmp(str, b) == 0)
    {
        round_robin();
    }
    else
    {
        printf("输入的算法名称不合法！");
    }
    printf("\n结束！！！");
    return 0;
}