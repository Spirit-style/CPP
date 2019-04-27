// #include <cctype>
// #include <fstream>
// #include <iostream>
// #include <stdio.h>
// #include <string>
// #include <vector>
// using namespace std;

// int main()
// {
//     ifstream in; //从硬盘调到内存
//     in.open("/home/lz/vscode/cpp/PL/ex1/input.txt");
//     if (!in)
//     {
//         printf("打开文件错");
//         return -1;
//     }
//     string s,temp="";
//     vector<string> words;
//     while (getline(in, s))
//     {
//         //       cout << s << endl;
//         for (int i = 0; i < s.length; i++)
//         {
//             if(isalpha(s[i])){
//                 s[i] += 32;
//                 temp += s[i];
                
//             }
//         }
//     }
//     in.close();
//     return 0;
// }
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
 
using namespace std;
 
int splitword(vector<string>  &words)   //分词
{
    ifstream in;
    in.open("PL/input.txt");
    if(!in){
        cout << "打开文件出错！" <<endl;
        return -1;
    }
	string s;
	string temp;
    while(getline(in,s))//逐行读入
    {
		int i=0;
		int flag=0;
		while(s[i] != 0){
			if(isalpha(s[i])){
				if(s[i] >= 'A' && s[i] <= 'Z' )  s[i] -= -32;
				if(flag != 1 && flag != 2) 	{	
					words.push_back(temp);
					temp = "";
				}
				temp += s[i];
				flag = 1;
			}
			else if(isdigit(s[i])){
				if(flag != 1 && flag != 2){	
					words.push_back(temp);
					temp = "";
				}
				temp += s[i];
				flag = 2;
			}
			else if(s[i] == ' ' || s[i] == '\t'){
				flag = 0;
			}
			else {
				if(flag != 3 || s[i] != '='){	
					words.push_back(temp);
					temp = "";
				}
				temp += s[i];
				flag = 3;
			}
			i++;
		}
    }
	in.close();
	return 0;
}
 
int main()
{
	vector<string> reserved_word;  //初始化保留字
	reserved_word.push_back("begin");
	reserved_word.push_back("call");
	reserved_word.push_back("const");
	reserved_word.push_back("do");
	reserved_word.push_back("end");
	reserved_word.push_back("if");
	reserved_word.push_back("odd");
	reserved_word.push_back("procedure");
	reserved_word.push_back("read");
	reserved_word.push_back("then");
	reserved_word.push_back("var");
	reserved_word.push_back("while");
	reserved_word.push_back("write");
 
	vector<string> words;
	splitword(words);  
 
	vector<string> result_word;   //提取标识符&出现次数
	vector<int> times;
	int n=0,i,j,k;
	for(i=1;i<words.size();i++){
		if(isalpha(words[i][0])){  //如果words是字母串
			for(k=0;k<13;k++){//判断是否是保留字
				if( words[i] == reserved_word[k] ) 	break;  
			}
			if(k==13){
				if(n==0){//判断是否已经记录过
					result_word.push_back(words[i]);
					times.push_back(1);
					n++;
				}
				else{
					for(j=n-1;j>=0;j--){
						if(words[i] == result_word[j]) {
							times[j] ++;
							break;
						}
					}
					if(j<0){
						result_word.push_back(words[i]);
						times.push_back(1);
						n++;
					}
				}
			}
		}
	}
 
 
	ofstream out;  //存结果
	out.open("PL/result.txt");
	for(i=0;i<result_word.size();i++){
		out << "(" << result_word[i] << ":"<<"\t"<<times[i]<<")"<<endl;
	}
	out.close();
	cout << "结果已存入result.txt"<<endl;
 
	system("pause");
	return 0;
}



