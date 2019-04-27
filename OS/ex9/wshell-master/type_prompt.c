//#include <sys/utsname.h>
#include "wshell.h"
const int max_name_len = 256;
const int max_path_len = 1024;

void type_prompt(char *prompt)
{
    extern struct passwd *pwd; //extern可以置于变量或者函数前，以标示变量或者函数的定义在别的文件中，提示编译器遇到此变量和函数时在其他模块中寻找其定义。此外extern也可用来进行链接指定。
    char hostname[max_name_len];
    char pathname[max_path_len];
    int length;
    pwd = getpwuid(getuid()); //根据用户id获取当前用户的信息，包括：用户名、密码、用户id、组id、真实用户名、主目录路径等。
    getcwd(pathname, max_path_len);//将当前工作目录的绝对路径放置在pathname中。
    if (gethostname(hostname, max_name_len) == 0)//获取主机名
        sprintf(prompt, "[LZshell]%s@%s:", pwd->pw_name, hostname);//将用户名和主机名格式化之后放入prompt缓存
    else
        sprintf(prompt, "[LZshell]%s@unknown:", pwd->pw_name);//获取主机名失败后的处理
    //printf("pathname: %s,length:%d\npw_dir:%s,length:%d\n",
    //pathname,strlen(pathname),pwd->pw_dir,strlen(pwd->pw_dir));
    length = strlen(prompt);
    if (strlen(pathname) < strlen(pwd->pw_dir) ||
        strncmp(pathname, pwd->pw_dir, strlen(pwd->pw_dir)) != 0)
        sprintf(prompt + length, "%s", pathname);
    else
        sprintf(prompt + length, "~%s", pathname + strlen(pwd->pw_dir));
    length = strlen(prompt);
    if (getuid() == 0)//geteuid()用来取得执行目前进程有效的用户识别码
        sprintf(prompt + length, "#");
    else
        sprintf(prompt + length, "$");
    return;
}

// int main()
// {
//     char prompt[100];
//     type_prompt(prompt);
//     printf("%s", prompt);
//     return 0;
// }
