#include <cstring>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
const int vmsize = 32;
const int length = 256; //被调试的指令地址流长度,可作为一个常量设定。
const int MAX = vmsize * 1024;
struct node
{
    int ye = -1;
    int num = -1; //上一次或下一次调用的位置
};
int called = -1;       //当前请求的页面号。
bool pagefault = true; //页面失效标志,如当前请求页 called 已在页表内,则置 pagefault=false,否则为 true。
int table[vmsize];     //页表。table[i]=j,表示虚存的第 j 页在实存的第 i 页中。
int used = 0;          //当前被占用的实存页面数,可用来判断当前实存中是否有空闲页。
int a[length];
struct node pageno[length];

// 在【0，319】的指令地址之间随机选取一起点m。
// 顺序执行一条指令，即执行地址为m+1的指令。
// 在前地址【0,m+1】中随机选取一条指令并执行，该指令的地址为m’。
// 顺序执行一条指令，其地址为m’+1。
// 在后地址【m’+2,319】中随机选取一条指令并执行。
// 重复步骤（1）-（5），直到320次指令
void init()
{ //产生指令地址流
    srand((unsigned int)time(NULL));
    int m,txx, i = 0;
    //while (i < length)
    // {
    //     m = rand() % MAX; //虚拟存储器32k
    //     a[i++] = m;
    //     a[i++] = m + 1;
    //     a[i++] = rand() % (m);
    //     a[i++] = m + 2 + rand() % (MAX - (m + 2) + 1);
    // }
    txx = MAX / 2;
    while (i < length)
    {
        m = rand() % MAX; //虚拟存储器32k
        a[i++] = m;
        a[i++] = m + 1;
        a[i++] = rand() % (txx);
        a[i++] = txx+1 + rand() % (MAX-txx-1);
    }

    printf("THE VIRTUAL ADDRESS STREAM AS FOLLOWS:\n");
    for (i = 0; i < length; ++i)
    {
        printf("a[%d]=%d \t", i, a[i]);
        if (i % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n===============================================\n");
    // for (int i = 0,int j=0; i < length/4;++i){
    //     j = i * 4;  //分成四部分
    //     a[j] = m;//50%的指令顺序执行
    //     a[j + 1] = m + 1;
    //     a[j + 2] = a[j] * rand() / MAX;//25%均匀分布在前地址部分。
    //     a[j + 3] = a[j + 2] + 1;
    //     m = a[j + 3] + (MAX - a[j + 3]) * rand() / MAX;
    // }
}
//Optimal
void opt(int assigned)
{
    for (int i = 0; i < vmsize; ++i)
    {
        for (int j = i + 1; j < vmsize; ++j)
        {
            if (pageno[i].ye == pageno[j].ye)
            {
                pageno[i].num = j; //计算下一次调用在什么时候，为-1表示不再调用
                break;
            }
        }
    }
    struct node *plan = new struct node[assigned]; //申请物理块，一共可容纳页assigned个
    int count = 0;                                 //计算页面中断数
    for (int i = 0; i < vmsize; ++i)
    {
        // if (i < assigned)
        // {
        //     for (int j = i + 1; j<)
        //         plan[i].ye = -1; //初始化物理块
        // }
        table[i] = -1; //初始化页表，没有页在内存中
    }
    used = 0;
    for (int i = 0; i < length; ++i)
    {
        called = pageno[i].ye;
        for (int j = 0; j < assigned; ++j)
        {
            if (called == plan[j].ye)
            { //页面在物理块
                pagefault = false;
            }
        }
        if (pagefault && used < assigned)
        {
            for (int j = 0; j < assigned; ++j)
            {
                if (plan[j].ye == -1)
                {
                    plan[j].ye = pageno[i].ye; //将虚存页号a[i]放入物理块号j处
                    plan[j].num = pageno[i].num;
                    table[pageno[i].ye] = j;
                    ++count;
                    ++used;
                    break;
                }
            }
        }
        else
        {
            // for (int j = 0; j < assigned; ++j)
            // {
            //     if (called == plan[j].ye)
            //     { //页面在物理块
            //         pagefault = false;
            //     }
            // }
            if (pagefault == true)
            { //访问页面不在物理块内
                int temp = plan[0].num, k = 0;
                if (temp != -1)
                {
                    for (int j = 1; j < assigned; ++j)
                    {
                        if (plan[j].num == -1)
                        {
                            k = j;
                            break;
                        }
                        else if (temp < plan[j].num)
                        {
                            temp = plan[j].num;
                            k = j;
                        }
                    }
                }
                //替换k块
                table[plan[k].ye] = -1;
                plan[k].ye = called;
                plan[k].num = pageno[i].num;
                table[called] = k;
                ++count;
            }
        }
        pagefault = true;
    }
    double s = 1 - (double)count / length;
    printf("%d\t\t\t\t%f\n", assigned, s);
    delete[] plan;
}
void lru(int assigned)
{
    struct node *plan = new struct node[assigned]; //申请物理块，一共可容纳页assigned个
    int count = 0;                                 //计算页面中断数
    for (int i = 0; i < vmsize; ++i)
    {
        table[i] = -1; //初始化页表，没有页在内存中
    }
    used = 0;
    for (int i = 0; i < length; ++i)
    {
        called = pageno[i].ye;
        for (int j = 0; j < assigned; ++j)
        {
            if (called == plan[j].ye)
            { //页面在物理块
                pagefault = false;
                plan[j].num = -2;
            }
        }
        if (pagefault && used < assigned)
        {
            for (int j = 0; j < assigned; ++j)
            {
                if (plan[j].ye == -1)
                {
                    plan[j].ye = pageno[i].ye; //将虚存页号pageno[i]放入物理块号j处
                    plan[j].num = -2;
                    table[pageno[i].ye] = j;
                    ++count;
                    ++used;
                    break;
                }
            }
        }
        else
        {
            if (pagefault == true)
            { //访问页面不在物理块内
                int temp = plan[0].num, k = 0;
                for (int j = 1; j < assigned; ++j)
                {
                    if (plan[j].num > temp)
                    {
                        temp = plan[j].num;
                        k = j;
                    }
                }
                table[plan[k].ye] = -1;
                plan[k].num = -2;
                plan[k].ye = called;
                table[called] = k;
                ++count;
            }
        }
        for (int k = 0; k < assigned; ++k)
        {
            if (plan[k].ye != -1)
            {
                plan[k].num++;
            }
        }
        pagefault = true;
    }
    double s = 1 - (double)count / length;
    printf("%d\t\t\t\t%f\n", assigned, s);
    delete[] plan;
}

void fifo(int assigned){
    struct node *plan = new struct node[assigned]; //申请物理块，一共可容纳页assigned个
    int count = 0;                                 //计算页面中断数
    for (int i = 0; i < vmsize; ++i)
    {
        table[i] = -1; //初始化页表，没有页在内存中
    }
    used = 0;
    for (int i = 0; i < length; ++i)
    {
        called = pageno[i].ye;
        for (int j = 0; j < assigned; ++j)
        {
            if (called == plan[j].ye)
            { //页面在物理块
                pagefault = false;
            }
        }
        if (pagefault && used < assigned)
        {
            for (int j = 0; j < assigned; ++j)
            {
                if (plan[j].ye == -1)
                {
                    plan[j].ye = pageno[i].ye; //将虚存页号pageno[i]放入物理块号j处
                    plan[j].num = -1;
                    table[pageno[i].ye] = j;
                    ++count;
                    ++used;
                    break;
                }
            }
        }
        else
        {
            if (pagefault == true)
            { //访问页面不在物理块内
                int temp = plan[0].num, k = 0;
                for (int j = 1; j < assigned; ++j)
                {
                    if (plan[j].num > temp)
                    {
                        temp = plan[j].num;
                        k = j;
                    }
                }
                table[plan[k].ye] = -1;
                plan[k].num = -1;
                plan[k].ye = called;
                table[called] = k;
                ++count;
            }
        }
        for (int k = 0; k < assigned; ++k)
        {
            if (plan[k].ye != -1)
            {
                plan[k].num++;
            }
        }
        pagefault = true;
    }
    double s = 1 - (double)count / length;
    printf("%d\t\t\t\t%f\n", assigned, s);
    delete[] plan;
}





void page(int pagesize)
{ //页面地址流
    printf("PAGE NUMBER WITH SIZE %dk FOR EACH ADDRESS IS:\n", pagesize);
    int m = pagesize * 1024;
    for (int i = 0; i < length; ++i)
    {
        pageno[i].ye = a[i] / m;
        printf("pageno[%d]=%d \t", i, pageno[i].ye);
        if (i % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\nvmsize=%dk\tpagesize=%dk\n", vmsize, pagesize);
    printf("====================================================\n");
}

int main()
{
    int pagesize = 1;
    int assigned = 4;
    int keep=1;
    init(); //生成指令流
    char strs[10];
    char alg1[] = "opt\n", alg2[] = "lru\n", alg3[] = "fifo\n";
    while (keep)
    {
        pagesize = 1;
        printf("The algorithm is(opt or lru or fifo):");
        fgets(strs, 10, stdin);
        while (pagesize <= 8)
        {
            page(pagesize);
            printf("page assigned\t\tpages_in/totalreferences\n");
            if (strcmp(strs, alg1) == 0)
            {
                for (assigned = 4; assigned <= vmsize/pagesize; assigned += 2)
                {
                    opt(assigned); //最佳
                }
            //    printf("End the result for opt\n\n");
            }
            else if (strcmp(strs, alg2) == 0)
            {
                for (assigned = 4; assigned <= vmsize/pagesize; assigned += 2)
                {
                    lru(assigned); //最佳
                }
            //    printf("End the result for lru\n\n");
            }
            else if (strcmp(strs, alg3) == 0)
            {
                for (assigned = 4; assigned <= vmsize/pagesize; assigned += 2)
                {
                    fifo(assigned); 
                }
            //    printf("End the result for fifo\n\n");
            }
            else
            {
                printf("输入的算法名称不符合!");
            }
            pagesize *= 2;
        }
        printf("输入'0'结束:");
        scanf("%d", &keep);
    }
    return 0;
}