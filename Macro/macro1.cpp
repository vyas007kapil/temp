//============================================================================
// Name        : macro.cpp
// Author      : KAPIL
// Version     :
// Copyright   : TE 10
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class mnt{
	string name;
	int mntpr;
	friend class macro;
};
class mdt{
	string macdef[50];
	int l_mdt;
	friend class macro;
};
class macro{
	string mdt1[50],pass1[50],pass2[50];
	mnt mntab[5];
	mdt mdtab[15];
	int mntp,mdtp,l1,l2,length;
public:
	macro(){
		mntp=mdtp=length=l1=l2=0;
	}
	void pass_I();
	void pass_II();
	void op_pass_I();
	void op_pass_II();
	int add_mnt(string);
	void display_mdt();
	void display_mnt();
	int search_mnt(string);
};

int macro::add_mnt(string token){
	mntab[mntp].mntpr=mdtp;
	mntab[mntp++].name=token;
	return mntp-1;
}
void macro::display_mdt(){
	for(int i=0;i<length;i++)
		cout<<mdt1[i]<<endl;
}
void macro::display_mnt(){
	cout<<"ID\tMACRO NAME\n";
	for(int i=0;i<mntp;i++)
		cout<<mntab[i].mntpr<<"\t"<<mntab[i].name<<endl;
	cout<<endl;
}
int macro::search_mnt(string s){
	for(int i=0;i<mntp;i++)
	if(s.compare(mntab[i].name)==0)
		return i;
	return -1;
}
void macro::pass_I(){
	string line,token;
	int pos=0;
	ifstream fp("/home/hp/minput.txt");
	ofstream op("/home/hp/int.txt");
	while(!fp.eof()){
		int i=0;
		getline(fp,line);
		if(line.compare("macro")==0){
			getline(fp,line);
			pos=search_mnt(line);
			if(pos==-1)
				add_mnt(line);
			//getline(fp,line,'\n');
			while(true){
				getline(fp,line);
				if(line.compare("mend")==0)
					break;
				mdtab[mdtp].macdef[i++]=line;
				mdt1[length++]=line;
			}
			mdtab[mdtp++].l_mdt=i;
			continue;
		}
		else{
			pass1[l1++]=line;
			op<<line<<endl;
		}
	}
}
void macro::pass_II(){
	string line,token;
	int pos,i;
	ifstream ip("/home/hp/int.txt");
	while(!ip.eof()){
		getline(ip,line,'\n');
		istringstream iss(line);
		iss>>token;
		pos=search_mnt(token);
		cout<<pos;
		if(pos==-1){
			pass2[l2++]=line;
			continue;
		}
		else{
			cout<<"hi";
			for(i=0;i<=mdtab[mntab[pos].mntpr].l_mdt;i++){
				cout<<"k ";
				ostringstream o2;
				o2<<"+ ";
				pass2[l2++]=o2.str()+mdtab[mntab[pos].mntpr].macdef[i];

			}

		}
	}
}

void macro::op_pass_I(){
	for(int i=0;i<l1;i++){
		cout<<pass1[i]<<endl;
	}
}
void macro::op_pass_II(){
	ofstream op("/home/hp/macout.txt");
	cout<<endl;
	for(int i=0;i<l2;i++){
		cout<<pass2[i]<<endl;
		op<<pass2[i]<<endl;
	}
}
int main() {
	macro m;
	m.pass_I();
	m.op_pass_I();
	cout<<"\nMDT :\n";
	m.display_mdt();
	cout<<"\nMNT :\n";
	m.display_mnt();
	m.pass_II();
	m.op_pass_II();

	return 0;
}

