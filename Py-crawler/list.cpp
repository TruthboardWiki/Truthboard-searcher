#include<bits/stdc++.h>
#include<dirent.h>
#include<unistd.h>
#include <sys/stat.h>
#define SITEURL "https://truthboard.wikidot.com/"
using namespace std;

map<string,bool> pu;
string search_value="";

ofstream fout("result.txt");
/*功能函数*/
extern string bts(string str){
	int a,len=str.size();
	for(a=0;a<len;a++){
		if(str[a]>='A'&&str[a]<='Z'){
			str[a]=str[a]+32;
		}
	}
	return str;
}
extern bool have_str(string s,string s2){
	if(s.size()>s2.size()) return 0;
	for(int i=0;i<s2.size();i++){
		bool b=1;
		for(int j=0;j<s.size();j++){
			if(s[j]!=s2[i+j]){
				b=0;
				break;
			}
		}
		if(b){
			return 1;
		}
	}
	return 0;
}
extern string char_to_str(const char* ch){
	string s;
	for(int i=0;i<strlen(ch);i++){
		s.push_back(ch[i]);
	}
	return s;
}
extern bool have_file(const char* f2){
	ifstream fin (f2);
	bool b=fin.is_open();
	fin.close();
	return b;
}
/*end.*/
string HTMLToText(string html){
	bool show=true;
	string text="";
	for(int i=0;i<html.size();i++){
		if(html[i]=='<'){
			show=false;
		}
		if(show){
			text.push_back(html[i]);
		}
		if(html[i]=='>'){
			show=true;
		}
	}
	return text;
}
int CountHTML(string s){
	int j=0;
	for(int i=0;i<s.size();i++){
		if(s[i]=='<'){
			j++;
		}
		if(s[i+1]=='/'){
			j-=2;
		}
	}
	return j;
}
extern string file_to_url(string fn){
	string tmp="";
	string url="";
	int cnt=0;
	for(int i=fn.size()-6;i>=0;i--){
		if(fn[i]=='/'){
			if(cnt==0){
				url+=tmp;
			}else if(tmp=="lmth"){
				break;
			}else{
				url+=":"+tmp;
			}
			tmp.clear();
			cnt++;
		}else{
			tmp.push_back(fn[i]);
		}
	}
	reverse(url.begin(),url.end());
	return SITEURL+url;
}
extern void readfile(const char* fn){
	ifstream fin(fn);
	string s,sval="";
	int diver=0;
	bool show11=false;
	string title="";
	string tmp="";
	while(getline(fin,s)){
		if(have_str("title",s)){
			bool b=false,show=false;
			string sss;
			for(int i=0;i<s.size();i++){
				if(s[i]=='<'){
					b=true;
				}else if(s[i]=='>'){
					b=false;
					if(sss=="title"){
						show=true;
					}else if(sss=="/title"){
						show=false;
					}
				}else if(b){
					sss.push_back(s[i]);
				}else if(show){
					title.push_back(s[i]);
				}
			}
		}else if(have_str("main-content",s)){
			show11=true;
		}else if(have_str("page-info-break",s)){
			show11=false;
		}
		sval=HTMLToText(s);
		tmp=char_to_str(getcwd(NULL,0))+"/"+char_to_str(fn);
		string sturl=file_to_url(tmp.c_str());
		if(have_str(search_value,sval)&&pu[sturl]==0&&show11){
			fout<<sturl<<endl<<title<<endl<<sval<<endl;
			pu[sturl]=1;
			break;
		}
	}
}
extern int ls(string floder){
	struct stat buf;
	if(floder=="-h"||floder=="--help"){
		cout<<"usage: ls [floder]"<<endl;
	}
	char argv[256]={'\0'};
	for(int i=0;i<floder.size();i++){
		argv[i]=floder[i];
	}
	DIR *dp;
	struct dirent *dirp;
	if(strlen(argv)==0){
		printf("Usage:dir directory_name\n");
		return 1;
	}
	if((dp=opendir(argv))==NULL){
		printf("Cannot open%s.\n",argv);
		printf("Try to use sudo.\n");
		return 1;
	}
	while((dirp=readdir(dp))!=NULL){
		stat(dirp->d_name, &buf);
		if(S_IFREG & buf.st_mode){
			readfile(dirp->d_name);
		}
	}
	closedir(dp);
	return 0;
}
extern vector<string> lsfloder(string floder){
	vector<string> strlf;
	struct stat buf;
	char argv[256]={'\0'};
	for(int i=0;i<floder.size();i++){
		argv[i]=floder[i];
	}
	DIR *dp;
	struct dirent *dirp;
	if(strlen(argv)==0){
		printf("Usage:dir directory_name\n");
		return strlf;
	}
	if((dp=opendir(argv))==NULL){
		printf("Cannot open%s.\n",argv);
		printf("Try to use sudo.\n");
		return strlf;
	}
	while((dirp=readdir(dp))!=NULL){
		stat(dirp->d_name, &buf);
		if(/*!have_file(dirp->d_name)*/S_IFDIR & buf.st_mode){
			if(char_to_str(dirp->d_name)=="."||char_to_str(dirp->d_name)==".."){continue;}
			strlf.push_back(char_to_str(dirp->d_name));
		}
	}
	closedir(dp);
	return strlf;
}
void dfs(){
	//深度优先搜索，遍历html文件夹。
	//html文件夹可以看作数据库
	//搜索到的相关内容将输出到../result.txt内，由php读取搜索内容。
	vector<string> strlf=lsfloder(getcwd(NULL,0));
	ls(char_to_str(getcwd(NULL,0)));
	for(int i=0;i<strlf.size();i++){
		chdir(strlf[i].c_str());
		dfs();
		chdir("..");
	}
}
int main(int argc,char** argv){
	chdir("html");
	if(argc==1){
		fout.close();
		return 0;
	}
	search_value=char_to_str(argv[1]);
	dfs();
	fout.close();
	return 0;
}
