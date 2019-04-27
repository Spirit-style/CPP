#include <iostream>
#include <stdio.h>
using namespace std;
const int N = 3;     //进程数
const int SIZE = 10; //资源总数

int option;             //“=0"选用防止死锁算法； ”=1“不选用防止死锁算法
int vpmaxclaim[N + 1];  //第I进程对资源的最大需求量
int vallocation[N + 1]; //第I进程已分配到资源管理数
int vpstatus[N + 1];    //第I进程完成请求标志，为1时表示完成各次请求
int vcount[N + 1];      //第I进程请求次数计时器，表示该进程第几次请求
int total;              //已分配的资源总数
int remainder;          //剩余的系统资源总数
int inquiry;            //当前运行进程号
int ap[N + 1][SIZE];    //资源请求矢量
bool advance;

//初始化过程,装入所有初始数据,为各有关变量置初值,检查每个进程请求的资源总数是否超过系统所能提供的资源数。
void front()
{
    for (int i = 1; i <= N; ++i)
    {
        printf("CLASS OFPROCESS %d IS:", i);
        int j = 1;
        do
        {
            scanf("%d", &a[i][j]);
        } while (a[i][j++] != 0);
    }
    for (int i = 1; i <= N; ++i)
    {
        printf("MAXCLAIM OFPROCESS %d IS:", i);
        scanf("%d", &vpmaxclaim[i]);
        vallocation[i] = 0;
        vpstatus[i] = 0;
        vcount[i] = 0;
        total = 0;
        remainder = SIZE;
    }
    //判断最大需求量是否大于总需求量
    int temp = vpmaxclaim[1];
    for (int i = 2; i <= N; ++i)
        if (temp < vpmaxclaim[i])
            temp = vpmaxclaim[i];
    if (temp > SIZE)
    {
        printf("进程的最大资源需求量大于系统的总的需求量，出错！");
        return;
    }
}

//输出一次分配结果
void print()
{
}

//当测得资源不够分配或分配后可能产生死锁,回收已假定分配了的资源。
void retrieve()
{
}

//检查每个进程时候都已完成或者发生死锁。如果进程全部完成或发生死锁,则将全局变量 ADVANCE 置成 true,不然置成 false。
void term_ination(int i)
{
    int j = 0;
    while (j != N && vpstatus[++j])
    {
    }
    if (j == N)
        advance = true;
    else
        advance = false;
}

//为检查进程的分配资源数是否超过了它的最大申请量,或是释放的资源数是否超过占有数,这里是检查例外情况。
void r2()
{
}

//为各进程设置能执行完标志 T,对于还不能完成的进程将它的标志 T 置 1,能完成的进程标志 T 置 0.
void r4()
{
}

//测试在当前分配状态下,会不会产生死锁,若不会,死锁函数值返回 true,否则返回 false。
bool safe()
{
}

//按申请想当前进程分配或收回资源。
void allocate()
{
}

//收回当前进程的全部资源,并将此进程的 VPSTATUS 置 1。
void _return(int i)
{
    total -= vallocation[i];
    remainder += vallocation[i];
    vallocation[i] = 0;
    vpstatus[i] = 1;
}
void prevent_deadlock()
{
    //初始化
    front();
    int i;
    while (!advance)
    {
        i = 0;
        while (vpstatus[++i])
        {
        }
        inquiry = i;
        if (!ap[i][++vcount[i]])
        {
            //现行进程已经完成所有请求
            _return(i);
            term_ination(i);
        }
    }
}

int main()
{
    printf("INPUT:\n");
    printf("OPTION=");
    scanf("%d", &option);

    if (option == 0)
    {
        prevent_deadlock();
    }
    else if (option == 1)
    {
    }

    return 0;
}