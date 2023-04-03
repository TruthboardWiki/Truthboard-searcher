#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
string char_to_str(const char* ch){
	string s;
	for(int i=0;i<strlen(ch);i++){
		s.push_back(ch[i]);
	}
	return s;
}
int char_to_int(const char* s){
	int i=0;
	for(int j=0;j<strlen(s);j++){
		i*=10;
		i+=s[j]-'0';
	}
	return i;
}

#define cls system("cls")
#define Utc 8
#define GT_YEA 0x000000
#define GT_MON 0x000001
#define GT_DAY 0x000002
#define GT_HOU 0x000003
#define GT_MIN 0x000004
#define GT_SEC 0x000005

ofstream ferr ("err.log"/*,ios::app*/);
int GetTimes(int lei){
	time_t now_time;
	now_time = time(NULL);
	tm* timer=gmtime(&now_time);
	if(lei==0){
		return 1900+timer->tm_year;
	}else if(lei==1){
		return 1+timer->tm_mon;
	}else if(lei==2){
		return timer->tm_mday;
	}else if(lei==3){
		return timer->tm_hour+Utc;
	}else if(lei==4){
		return timer->tm_min;
	}else if(lei==5){
		return timer->tm_sec;
	}else{
		return now_time;
	}
}
bool have_file(const char* name){
	ifstream fins (name);
	return fins.is_open();
}
bool have_floder(const char* name){
	bool b=chdir(name)==0;
	if(b) chdir("../");
	return b;
}
bool compare_2_html(const char* file1,const char* file2){
	ifstream fin1 (file1);
	ifstream fin2 (file2);
	string s1,s2;
	while(getline(fin1,s1)||getline(fin2,s2)){
		if(s1!=s2){
			return false;
		}
	}
	return true;
}
void jihuo(){
	
}
void crawler(const char* url,const char* thing,const char* filename){
	char url2[2048];
	sprintf(url2,"./other-page %s%s %s",url,thing,filename);
	system(url2);
}
bool have_str(string s,string s2){
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
int main(int argc,char** argv){
	char timedata[1000]={'\0'};
	sprintf(timedata,"%d/%02d/%02d %02d:%02d:%02d",GetTimes(GT_YEA),GetTimes(GT_MON),GetTimes(GT_DAY),GetTimes(GT_HOU),GetTimes(GT_MIN),GetTimes(GT_SEC));
	ferr<<"NOW:"<<timedata<<endl;
	char* path=getcwd(NULL,0);
	string lan;
	ifstream flan("lan");
	if(!flan.is_open()){
		cout<<"Welcome to use Py-Crawler ";
		cout<<"Professional";
		cout<<" Editon (TimeLine-Bookstore Inside Edition)"<<endl;
		cout<<"Use 5 threads."<<endl;
	}else{
		getline(flan,lan);
		cout<<lan<<endl;
	}
	jihuo();
	chdir(path);
	if(!have_floder("html"))
		system("mkdir html");// ./html/
	ofstream fout;
	if(have_file("a.html"))
		system("rm a.html");
	char url[1024];
	if(argc==1){
		cout<<"Choose:"<<endl;
		cout<<"[1] TB"<<endl;
		cout<<"[ANY KEY] Other website"<<endl<<"> ";
		char c;
		c=getchar();
		getchar();
		if(c=='1'){
			sprintf(url,"https://truthboard.wikidot.com/");
		}else{
			if(!flan.is_open()){
				cout<<"Example: https://truthboard.wikidot.com/"<<endl;
				cout<<"Input URL> ";
			}else{
				getline(flan,lan);
				cout<<lan<<endl;
				getline(flan,lan);
				cout<<lan;
			}
			fgets(url,1024,stdin);
		}
	}else{
		sprintf(url,"%s",argv[1]);
	}
	char cmd[1536];
	sprintf(cmd,"./crawler %s",url);
	cout<<cmd<<endl;
	int a=system(cmd);
	ifstream fin ("a.html");
	if(a==1){
		ferr<<"----------------------------"<<endl;
		ferr<<"ERR:main.exe"<<endl;
		ferr<<"PAGE:"<<url<<endl;
		ferr<<"DO_NOT_FIND_CRAWLER_EXE"<<endl;
		exit(0);
	}else if(!fin.is_open()){
		ferr<<"----------------------------"<<endl;
		ferr<<"ERR:main.exe"<<endl;
		ferr<<"PAGE:"<<url<<endl;
		ferr<<"DO_NOT_FIND_FILE_A_HTML"<<endl;
		exit(0);
	}
	string s;
	fin.close();
	char url2[2048];
	int n=1;
	int nu;
	if(argc<3){
		cout<<"Your pages of /system:list-all-pages> ";
		cin>>nu;
	}else{
		nu=char_to_int(argv[2]);
	}
	long long l=clock(),l2=0;
	while(n<=nu){
		sprintf(url2,"./get-all-page %ssystem:list-all-pages/p/%d",url,n);
		//cout<<url2<<endl;
		system(url2);
		n++;
	}
	system("./all");
	fin.open("allurls.log");
	string things,things2,things3,things4,things5;
	while(getline(fin,things)){
		char thing[512]={'\0'};
		for(int i=0;i<things.size();i++){
			thing[i]=things[i];
		}
    crawler(url,thing,"a.html");
		//cout<<url2<<endl;
	}
	fin.close();
	l2=clock();
	ferr<<"-----END-----"<<endl;
	ferr<<"Use Time:"<<(l2-l)/1000<<endl;
	//*/
  system("clear");
	return 0;
}
