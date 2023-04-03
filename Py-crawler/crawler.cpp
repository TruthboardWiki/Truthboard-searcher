#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int main(int argc,char** argv){
	if(argc==1){
		cout<<"Failed! Pleaase run main.exe!"<<endl;
		return 0;
	}
  char cmd[2048]={'\0'};
	if(argc==2){
    sprintf(cmd,"curl \"%s\" --output ./a.html",argv[1]);
    system(cmd);
		return 0;
	}
	sprintf(cmd,"curl \"%s\" --output ./%s",argv[1],argv[2]);
  system(cmd);
	return 0;
}
