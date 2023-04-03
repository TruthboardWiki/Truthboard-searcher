#include<bits/stdc++.h>
#include<unistd.h>

using namespace std;
ofstream ferr ("err.log",ios::app);
void jihuo(){

}
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
int main(int argc,char** argv){
	char* path=getcwd(NULL,0);
	jihuo();
	chdir(path);
	ofstream fout;
	char url[1024];
	if(argc==1){
		ferr<<"----------------------------"<<endl;
		ferr<<"ERR:other-page.exe"<<endl;
		ferr<<"DO_NOT_RUN_MAIN_EXE"<<endl;
		exit(0);
	}else if(argc==2){
		sprintf(argv[2],"a.html");
	}else{
		sprintf(url,"%s",argv[1]);
	}
	if(have_file(argv[2])){
		char cmd1[1024];
		sprintf(cmd1,"rm %s",argv[2]);
		system(cmd1);
	}
	//cout<<1;
	char cmd[1536];
	sprintf(cmd,"./crawler %s %s",url,argv[2]);
	int a=system(cmd);
	ifstream fin (argv[2]);
	if(a==1){
		ferr<<"----------------------------"<<endl;
		ferr<<"ERR:other-page.exe"<<endl;
		ferr<<"PAGE:"<<url<<endl;
		ferr<<"DO_NOT_FIND_CRAWLER_EXE"<<endl;
		exit(0);
	}else if(!fin.is_open()){
		ferr<<"----------------------------"<<endl;
		ferr<<"ERR:other-page.exe"<<endl;
		ferr<<"PAGE:"<<url<<endl;
		ferr<<"DO_NOT_FIND_FILE_A_HTML"<<endl;
		exit(0);
	}
	string s;
	char of[1024]={'\0'};
	char floder[1024]={'\0'};
	string floder2;
	bool bl=0;
	for(int i=strlen(url)-1;url[i]!='/';i--){
		if(bl){
			floder2.push_back(url[i]);
		}
		if(url[i]==':'){
			s.push_back('/');
			bl=1;
		}else
			s.push_back(url[i]);
		
	}
	if(floder2!="\0"){
		string fl2;
		vector<string> var_flo;
		floder2+=" ";
		for(int i=0;i<floder2.size();i++){// delete/char/page
			if(floder2[i]=='/'||floder2[i]==':'||i==floder2.size()-1){
				var_flo.push_back(fl2);
				fl2="";
			}else{
				fl2.push_back(floder2[i]);
			}
		}
		chdir("html");
		for(int j=var_flo.size()-1;j>=0;j--){
			string tmps=var_flo[j]+" ridkm";
			for(int i=0;i<1024;i++){
				floder[i]='\0';
			}
			for(int i=tmps.size()-1;i>=0;i--){
				floder[tmps.size()-1-i]=tmps[i];
			}
			system(floder);
			for(int i=0;i<1024;i++){
				floder[i]='\0';
			}
			for(int i=var_flo[j].size()-1;i>=0;i--){
				floder[var_flo[j].size()-1-i]=var_flo[j][i];
			}
			chdir(floder);
		}
		for(int j=var_flo.size();j>=0;j--){
			chdir("../");
		}
	}
	s="lmth."+s+"/lmth/.";
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
	fin.close();
	return 0;
}
//@import url(http://kcdfg.wdfiles.com/local--theme/silent-silver-patch/style.css);
