#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> 
#include <errno.h>
#include <pwd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h> 
#define MAX_PROMPT 1024
#define MAXLINE 4096 //the length of all args is ARG_MAX
#define MAXARG 20

struct parse_info;
struct passwd *pwd;
char *buffer;

void type_prompt(char*);  //终端提示符
int read_command(char **,char **,char*);//从终端中读入参数
int builtin_command(char *,char **);//
int parsing(char **,int,struct parse_info *);
void proc(void);
void sig_handler(int sig);



#ifndef STRUCT_PARSE_INFO
#define STRUCT_PARSE_INFO
#define BACKGROUND 			1
#define IN_REDIRECT 		2
#define OUT_REDIRECT 		4
#define OUT_REDIRECT_APPEND	8
#define IS_PIPED 			16
struct parse_info 
{
    int flag;//表明使用了哪些功能的标志位
    char* in_file;//输入重定向的文件名
    char* out_file;//输出重定向的文件名
    char* command2;//命令2
	char** parameters2; //命令2的参数表
};
#endif
