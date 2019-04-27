#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
using namespace std;

const int n = 10;       //n个用户，此时为10个用户
const int openum = 5;   //用户一次运行可打开5个文件
const int filenum = 10; //用户最多可保存10个文件
struct mfd
{
    char username[10];
    struct ufd *filecata; //文件目录指针
    int count = 0;        //用户以保存文件数目
};
struct ufd
{
    char filename[10]; //文件名
    char prodot[4];    //保护码
    int codelength;    //文件长度
    struct ufd *next = NULL;
};
struct afd
{
    int ofnum;      //打开文件号
    char opdot[4];  //打开保护码
    struct ufd *rw; //读写指针？
    struct afd *next = NULL;
};
struct afd *head = new struct afd;
struct mfd userfile[n];
int point = 0; //指向userfile空的位置
void init()
{ //初始化用户文件系统
    struct ufd *p;
    head->ofnum = 0;
    //filename="YOUJIN"
    strcpy(userfile[point].username, "YOUJIN");
    p = new struct ufd;
    userfile[point].filecata = p;
    strcpy(p->filename, "XUMAN");
    p->codelength = 9999;
    strcpy(p->prodot, "111");
    userfile[point].count++;
    p->next = new struct ufd;
    p = p->next;
    strcpy(p->filename, "F1");
    p->codelength = 0;
    strcpy(p->prodot, "111");
    userfile[point].count++;
    p->next = new struct ufd;
    p = p->next;
    strcpy(p->filename, "YOUJING");
    p->codelength = 100;
    strcpy(p->prodot, "111");
    userfile[point].count++;
    point++;
    // p->next = new struct ufd;
    // p = p->next;
}
void showit(struct ufd *it, int count)
{
    printf("YOUR FILE DIRECTORY\n");
    printf("FILE NAME\t\tPROTECTION\t\tCODELENGTH\n");
    struct ufd *p = it;
    for (int i = 0; i < count; ++i)
    {
        printf("%s\t\t\t%s\t\t\t%d\n", p->filename, p->prodot, p->codelength);
        p = p->next;
    }
}

void _create(struct ufd *it)
{
    printf("THE NEW FILES NAME(LESS THAN 9 CHARS)?\t");
    char name[10];
    scanf("%s", name);
    //getchar();
    //  printf("%s\n", name);

    printf("THE NEW FILE'S PROTECTION CODE?\t");
    char code[4];
    scanf("%s", code);
    //getchar();
    struct ufd *p;
    for (p = it; p->next; p = p->next)
        ;
    p->next = new struct ufd;
    p = p->next;
    p->codelength = 0;

    strcpy(p->filename, name);
    strcpy(p->prodot, code);
    printf("THE NEW FILE IS CREATED.\n");
    printf("ENTER THE OPEN MODE?\t");
    scanf("%s", code);
    struct afd *q;
    int i = 0;
    for (q = head; q->next; q = q->next)
    {
        ++i;
    }
    if (i < 5)
    {
        q->next = new struct afd;
        q = q->next;
        strcpy(q->opdot, code);
        q->ofnum = ++i;
        q->rw = p;
        head->ofnum = i;
        printf("THIS FILE IS OPENED, ITS OPEN NUMBER IS\t %d\n", q->ofnum);
    }
    else
    {
        printf("THIS FILE IS FAILED TO OPEN! ITS OPEN NUMBER ABOUT %d \n", openum);
    }
}

struct ufd *_delete(struct ufd *it)
{
    printf("THE DELETE FILE NAME? ");
    char name[10];
    scanf("%s", name);
    struct ufd *p, *q = NULL;
    for (p = it; p; p = p->next)
    {
        if (strcmp(p->filename, name) == 0)
            break;
        q = p;
    }
    struct afd *pp, *qq;
    for (pp = head->next, qq = head; pp; pp = pp->next)
    {
        if (pp->rw == p)
        {
            qq->next = pp->next;
            delete pp;
            pp = qq->next;
            for (; pp; pp = pp->next)
            {
                pp->ofnum--;
            }
            head->ofnum--;
        }
        qq = pp;
    }
    if (q == NULL)
    {
        q = p->next;
        delete p;
        return q;
    }
    q->next = p->next;
    delete p;
    return it;
}
void _read()
{
    printf("OPEN FILE NUMBER? ");
    char k;
    getchar();
    scanf("%c", &k);
    int ki = k - 0x30;
    if ((ki > head->ofnum) || (ki < 1))
    {
        printf("ERROR MESSAGE: IT IS NOT ALLOWED TO READ THIS FILE !!!\n");
        return;
    }
    struct afd *q;
    for (q = head->next; q; q = q->next)
    {
        if (q->ofnum == ki)
        {
            break;
        }
    }
    if (q->rw->prodot[0] == '0' || q->opdot[0] == '0')
    {
        printf("ERROR MESSAGE: IT IS NOT ALLOWED TO READ THIS FILE !!!\n");
        return;
    }
    printf("BE READING!\n");
}

void _write()
{
    printf("OPEN FILE NUMBER? ");
    char k;
    getchar();
    scanf("%c", &k);
    int ki = k - 0x30;
    if ((ki > head->ofnum) || (ki < 1))
    {
        printf("%d", ki);
        printf("ERROR MESSAGE: IT IS NOT ALLOWED TO WRITE THIS FILE !!!\n");
        return;
    }
    struct afd *q;
    for (q = head->next; q; q = q->next)
    {
        if (q->ofnum == ki)
        {
            break;
        }
    }
    if (q->opdot[1] == '0' || q->rw->prodot[1] == '0')
    {
        printf("ERROR MESSAGE: IT IS NOT ALLOWED TO WRITE THIS FILE !!!\n");
        return;
    }
    printf("HOW MANY CHARACTERS TO BE WRITTEN INTO THAT FILE? ");
    int count;
    scanf("%d", &count);
    q->rw->codelength = count;
}

void _open(struct ufd *it)
{
    printf("FILE NAME TO BE OPENED? ");
    char name[10];
    char code[4];
    scanf("%s", name);
    struct ufd *p;
    struct afd *q;
    for (p = it; p; p = p->next)
    {
        if (strcmp(p->filename, name) == 0)
        {
            printf("ENTER THE OPEN MODE? ");
            scanf("%s", code);
            int i = 0;
            for (q = head; q->next; q = q->next)
            {
                ++i;
            }
            if (i < openum)
            {
                q->next = new struct afd;
                q = q->next;
                strcpy(q->opdot, code);
                q->ofnum = ++i;
                q->rw = p;
                head->ofnum = i;
                printf("THIS FILE IS OPENED, ITS OPEN NUMBER IS\t %d\n", q->ofnum);
            }
            else
            {
                printf("THIS FILE IS FAILED TO OPEN! ITS OPEN NUMBER ABOUT %d \n", openum);
            }
            return;
        }
    }
    printf("NOT FOUND THE FILE %s\n", name);
}

void _close()
{
    printf("THE OPENED FILE NUMBER TO BE CLOSED? ");
    int k;
    scanf("%d", &k);
    if (k < 1 || k > head->ofnum)
    {
        printf("THE OPENED NUMBER IS FALSE.\n");
        return;
    }
    struct afd *p, *q;
    for (p = head->next, q = head; p; p = p->next)
    {
        if (p->ofnum == k)
            break;
        q = p;
    }
    q->next = p->next;
    delete p;
    p = q->next;
    for (; p; p = p->next)
    {
        p->ofnum--;
    }
    head->ofnum--;
    printf("THIS FIEL IS CLOSED.\n");
}

void _bye(struct ufd *it, int count)
{
    printf("NOW YOUR FILE DIRECTORY IS FOLLOWING: \n");
    struct ufd *p = it;
    for (int i = 0; i < count; ++i)
    {
        printf("%s\t\t\t%s\t\t\t%d\n", p->filename, p->prodot, p->codelength);
        p = p->next;
    }
    printf("GOOD BXE.\n");
}

void drop()
{
    for (struct afd *p = head->next; p; p = p->next)
    {
        head->next = p->next;
        delete p;
    }
    delete head;
    for (int i = 0; i < n; ++i)
    {
        struct ufd *p = userfile[i].filecata, *q;
        while (p)
        {
            q = p;
            p = p->next;
            delete q;
        }
    }
}
int main()
{
    init();
    printf("RUN\n");
    char name[10];
    bool flag = true;
    int i;
    while (flag)
    {
        printf("YOUR NAME? ");
        scanf("%s", name);
        for (i = 0; i < point; ++i)
        {
            if (strcmp(userfile[i].username, name) == 0)
            {
                flag = false;
                break;
            }
        }
        if (flag)
            printf("YOUR NAME IS NOT IN THE USER NAME TABLE,TRY AGAIN.\n");
    }
    flag = true;
    showit(userfile[i].filecata, userfile[i].count);
    char command[10];
    char allcommand[7][10] = {"CREATE", "DELETE", "OPEN", "CLOSE", "READ", "WRITE", "BYE"};
    int j = 0;
    while (j != 6)
    {
        while (flag)
        {
            printf("COMMAND NAME? ");
            scanf("%s", command);
            for (j = 0; j < 7; ++j)
            {
                if (strcmp(allcommand[j], command) == 0)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                printf("COMMAND NAME GIVED IS WRONG!\n");
                printf("IT SHOULD BE ONE OF FOLLOWING: CREATE,DELETE,OPEN,CLOSE,READ,WRITE,BYE. TRY AGAIN\n");
            }
        }
        flag = true;
        switch (j)
        {
        case 0:
            if (userfile[i].count <= filenum)
            {
                _create(userfile[i].filecata);
                userfile[i].count++;
            }
            else
            {
                printf("创建失败，每个用户最多只能创建%d个文件！", filenum);
            }
            break;
        case 1:
            if (userfile[i].count == 0)
            {
                printf("无文件可删除！");
            }
            else
            {
                showit(userfile[i].filecata, userfile[i].count);
                userfile[i].filecata = _delete(userfile[i].filecata);
                userfile[i].count--;
            }
            break;
        case 2:
            _open(userfile[i].filecata);
            break;
        case 3:
            _close();
            break;
        case 4:
            _read();
            break;
        case 5:
            _write();
            break;
        case 6:
            _bye(userfile[i].filecata, userfile[i].count);
            break;
        default:
            break;
        }
    }
    drop();
    return 0;
}
