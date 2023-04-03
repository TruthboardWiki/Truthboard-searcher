#include<bits/stdc++.h>
#include<unistd.h>

using namespace std;
bool is_pages(string s){
	if(s[0]=='p'&&s[1]=='a'&&s[2]=='g'&&s[3]=='e'&&s[4]=='s'){
		return 1;
	}else if(s[0]=='s'&&s[1]=='y'&&s[2]=='s'&&s[3]=='t'&&s[4]=='e'&&s[5]=='m'&&s[6]==':'&&s[7]=='l'&&s[8]=='i'&&s[9]=='s'&&s[10]=='t'&&s[11]=='-'&&s[12]=='a'&&s[13]=='l'&&s[14]=='l'&&s[15]=='-'&&s[16]=='p'&&s[17]=='a'&&s[18]=='g'&&s[19]=='e'&&s[20]=='s'){
		return 1;
	}
	return 0;
}
void jihuo(){

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
int main(){
	char* path=getcwd(NULL,0);jihuo();
	chdir(path);
	ifstream fin ("./html/pages1.html");
	ofstream fout ("allurls.log");
	map<string,bool> t_page;
	int n=1;
	while(fin.is_open()){
		//cout<<n;
		string s;
		bool b=false;
		while(getline(fin,s)){
			if(have_str("<div id=\"main-content\">",s)){
				b=true;
			}
			if(!b){continue;}
			for(int i=0;i<s.size();i++){
				if(s[i]=='<'&&s[i+1]=='a'&&s[i+2]==' '){
					i+=10;
					if(s[i-1]!='/'){
						continue;
					}
					string url;
					while(s[i]!='"'){
						url.push_back(s[i]);
						i++;
					}
					if(url[0]!='\0'&&(!is_pages(url))&&!t_page[url]){
						fout<<url<<endl;
						t_page[url]=true;
					}
				}
			}
			
		}
		n++;
		fin.close();
		char fn[1248];
		sprintf(fn,"./html/pages%d.html",n);
		fin.open(fn);
	}
	//system("pause");
	return 0;
}
