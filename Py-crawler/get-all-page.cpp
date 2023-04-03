#include<bits/stdc++.h>
#include<unistd.h>

using namespace std;
ofstream ferr ("err.log",ios::app);
string char_to_str(char ch[]){
	string s;
	for(int i=0;i<strlen(ch);i++){
		s.push_back(ch[i]);
	}
	return s;
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
void jihuo(){

}

int main(int argc,char** argv){
	char* path=getcwd(NULL,0);
	jihuo();
	chdir(path);
	ofstream fout ("a.html");
	fout.close();
	if(have_file("a.html"))
		system("rm a.html");
	char url[1024];
	if(argc==1){
		ferr<<"----------------------------"<<endl;
		ferr<<"ERR:get-all-pages.exe"<<endl;
		ferr<<"DO_NOT_RUN_MAIN_EXE"<<endl;
		exit(0);
	}else{
		sprintf(url,"%s",argv[1]);
	}
	//cout<<1;
	char cmd[1536];
	sprintf(cmd,"./crawler %s",url);
	int a=system(cmd);
	ifstream fin ("a.html");
	if(a==1){
		ferr<<"----------------------------"<<endl;
		ferr<<"ERR:get-all-pages.exe"<<endl;
		ferr<<"PAGE:"<<url<<endl;
		ferr<<"DO_NOT_FIND_CRAWLER_EXE"<<endl;
		exit(0);
	}else if(!fin.is_open()){
		ferr<<"----------------------------"<<endl;
		ferr<<"ERR:get-all-pages.exe"<<endl;
		ferr<<"PAGE:"<<url<<endl;
		ferr<<"DO_NOT_FIND_FILE_A_HTML"<<endl;
		exit(0);
	}
	string s;
	char of[1024]={'\0'};
	int i=strlen(url)-1;
	string num;
	for(;url[i]!='/';i--){
		num.push_back(url[i]);
	}
	s="lmth."+num+"segap"+"/lmth/.";
	for(int i=s.size()-1;i>=0;i--){
		of[s.size()-1-i]=s[i];
	}
	cout<<of<<endl;
	fout.open(of);
	while(getline(fin,s)){
		if(have_str("@import url(/admin:themes/code/1);",s)){
			fout<<"@import url("+char_to_str(url)+"admin:themes/code/1);"<<endl;
		}else{
			fout<<s<<endl;
		}
		if(have_str("<head>",s)){
			//fout<<"<base href=\"./\">"<<endl;
		}
		//cout<<1;
	}
	return 0;
}
//@import url(http://kcdfg.wdfiles.com/local--theme/silent-silver-patch/style.css);
