#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

//begin，call，const，do，end，if，odd，procedure，read，then，var，while，write
//+，-，*，/，=<,>,<,>=,<=,:=,=
// , . ; # ( )
// sym:单词类别 id：标识符值 num：用户定义的数

const int KN = 13; //关键字的个数
const int ON = 11; //操作符个数
const int JN = 5;  //界符个数
const int MAX = 10;

enum symbol
{
    nul,
    beginsym,
    callsym,
    constsym,
    dosym,
    endsym,
    ifsym,
    oddsym,
    procsym,
    readsym,
    thensym,
    varsym,
    whilesym,
    writesym,
    ident,  //标识符
    number, //数字
    pluss,   //+ - * /
    minuss,
    times,
    slash,
    eql,       //=
    neq,       //#
    lss,       //<
    leq,       //<=
    gtr,       //>
    geq,       //>=
    lparen,    //(
    rparen,    //)
    comma,     //,
    semicolon, //;
    period,    //.
    becomes    //:=
};

enum symbol sym; //传递单词种别
char id[MAX];    //传递标识符的名字
int num;         //传递无符号整数自身的值
char ch;         //从源文件得到的字符
enum symbol ssym[256];
FILE *fd, *fd2;
enum symbol key_word[KN] = {
    beginsym, callsym, constsym, dosym, endsym, ifsym, oddsym, procsym, thensym, varsym, whilesym, readsym, writesym};
char key[KN][10] = {"begin", "call", "const", "do", "end", "if", "odd", "proc", "then", "var", "while", "read", "write"};
void init(){
    for (int i = 0; i < 256;i++){
        ssym[i] = nul;
    }
    ssym['+'] = pluss;
    ssym['-'] = minuss;
    ssym['*'] = times;
    ssym['/'] = slash;
    ssym['('] = lparen;
    ssym[')'] = rparen;
    ssym['='] = eql;
    ssym[','] = comma;
    ssym['.'] = period;
    ssym['#'] = neq;
    ssym[';'] = semicolon;
}

bool isChar(char &ch)
    {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {
            if (ch >= 'A' && ch <= 'Z')
            {
                ch += 0x20;
            }
            return true;
        }
        return false;
    }
bool isDig(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    return false;
}
int isKey(char *str)
{
    for (int i = 0; i < KN; i++)
    {
        if (strcmp(str, key[i]) == 0)
        {
            sym = key_word[i];
            return i;
        }
    }
    sym = ident;
    return -1;
}
int getsym()
{
    ch = fgetc(fd); //调用从源文件中得到一个字符
    while (!feof(fd))
    {
        char temp[10]="";
        while (ch == ' ' || ch == 10 || ch == 13 || ch == 9)
        {
            ch = fgetc(fd);
        }
        if (isChar(ch))
        {
            strcat(temp, &ch);
            ch = fgetc(fd);
            while (isChar(ch) || isDig(ch))
            {
                strcat(temp, &ch);
                ch = fgetc(fd);
            }
            int i = isKey(temp);
            strcpy(id, temp);
            if (sym == ident)
            {
                fprintf(fd2, "(ident,%s)\n", id);
            }
            else
            {
                fprintf(fd2, "(%ssym,%s)\n", key[i], key[i]);
            }
        }
        else
        {
            if (isDig(ch))
            {
                num = ch - 0x30;
                ch = fgetc(fd);
                while (isDig(ch))
                {
                    num = num * 10 + ch - 0x30;
                    ch = fgetc(fd);
                }
                sym = number;
                fprintf(fd2, "(number,%d)\n", num);
            }
            else
            {
                if (ch == ':')
                {
                    ch = fgetc(fd);
                    if (ch == '=')
                    {
                        sym = becomes;
                        fprintf(fd2, "(becomes,:=)\n");
                        ch = fgetc(fd);
                    }
                    else
                    {
                        sym = nul;
                        printf("错误字符");
                    }
                }
                else
                {
                    if (ch == '<')
                    {
                        ch = fgetc(fd);
                        if (ch == '=')
                        {
                            sym = leq;
                            fprintf(fd2, "(leq,<=)\n");
                            ch = fgetc(fd);
                        }
                        else
                        {
                            sym = lss;
                            fprintf(fd2, "lss,<");
                        }
                    }
                    else if (ch == '>')
                    {
                        ch = fgetc(fd);
                        if (ch == '=')
                        {
                            sym = geq;
                            fprintf(fd2, "(geq,>=)\n");
                            ch = fgetc(fd);
                        }
                        else
                        {
                            sym = gtr;
                            fprintf(fd2, "gtr,>");
                        }
                    }
                    else{
                        sym = ssym[ch];
                        if(sym==eql){
                            fprintf(fd2, "(eql,=)\n");
                            ch = fgetc(fd);
                        }
                        else if (sym==neq)
                        {
                            fprintf(fd2, "(neq,#)\n");
                            ch = fgetc(fd);
                        }
                        else if (sym==pluss)
                        {
                            fprintf(fd2, "(plus,+)\n");
                            ch = fgetc(fd);
                        }
                        else if (sym == minuss)
                        {
                            fprintf(fd2, " minus,-)\n");
                            ch = fgetc(fd);
                        }
                        else if (sym==times)
                        {
                            fprintf(fd2, "(times,*)\n");
                            ch = fgetc(fd);
                        }
                        else if (sym==slash)
                        {
                            fprintf(fd2, "(slash,/)\n");
                            ch = fgetc(fd);
                        }
                        else if (sym==lparen)
                        {
                            fprintf(fd2, "(lparen,()\n");
                            ch = fgetc(fd);
                        }
                        else if (sym==rparen)
                        {
                            fprintf(fd2, "(rqaren,))\n");
                            ch = fgetc(fd);
                        }
                        else if (sym==comma)
                        {
                            fprintf(fd2, "(comma,,)\n");
                            ch = fgetc(fd);
                        }
                        else if (sym==period)
                        {
                            fprintf(fd2, "(period,.)\n");
                            ch = fgetc(fd);
                        }
                        else if (sym==semicolon)
                        {
                            fprintf(fd2, "(semicolon,;)\n");
                            ch = fgetc(fd);
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int main()
{
    init();
    fd = fopen("/home/lz/vscode/cpp/PL/input.txt", "r");
    fd2 = fopen("/home/lz/vscode/cpp/PL/output2.txt", "w");
    if (!fd)
    {
        printf("打开文件不成功");
    }
    getsym();
    fclose(fd);
    fclose(fd2);
    return 0;
}