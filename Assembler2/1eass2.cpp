//============================================================================
// Name        : 1eass2.cpp
// Author      : KAPIL
// Version     :
// Copyright   : TE 10
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>

using namespace std;

class opcode{
	string mnemonic,i_class;
	int code,no;
	friend class assembler;
};

class literal{
	string lit;
	int add;
	friend class assembler;
};

class res{
	int i,j;
	friend class assembler;
};
class assembler{
	opcode table[26][5];
	literal litab[10];
	int bucket[26],lt,pl,pb,l,l1,flag,pooltab[10];
	string pass1[50],pass2[50];
	public:
	assembler(){
		lt=l=l1=pb=flag=0,pl=1;
		for(int i=0;i<26;i++)
			bucket[i]=0;
	}
	void populate();
	res search_op(string);
	int search_lit(string,int);
	void addlit(string);
	int isreg(string);
	void pass_I();
	void pass_II();
	void op_pass_I();
	void op_pass_II();
	void print_lit();
	void print_pool();
	int get_index(int);
};
void assembler::populate(){
	string line,token;
	int num,i,j;
	ifstream fp("/home/hp/optab_lit.txt");
	if(fp.is_open()){
		cout<<"File opened,,,,reading!!!";
		while(!fp.eof()){
			getline(fp,line);
			j=(int)line[0]-97;
			if(j<0)	break;
			istringstream iss(line);
			iss>>token;
			table[j][bucket[j]].mnemonic=token;
			iss>>token;
			table[j][bucket[j]].i_class=token;
			iss>>num;
			table[j][bucket[j]].code=num;
			iss>>num;
			table[j][bucket[j]].no=num;
			bucket[j]++;
		}
fp.close();
	}
	else{
		cout<<"FILE ERROR!!!!";
	}

}

res assembler::search_op(string s){
	res r;
	r.i=(int)s[0]-97;
	for(int i=0;i<bucket[r.i];i++){
		if(s.compare(table[r.i][i].mnemonic)==0){
			r.j=i;
			return r;
		}
	}
	r.i=r.j=-1;
	return r;
}

int assembler::search_lit(string str,int b){
	for(int i=b;i<lt;i++){
		if(str.compare(litab[i].lit)==0){
			return i;
		}
	}
	return -1;
}

void assembler::addlit(string str){
	litab[lt++].lit=str;

}

int assembler::isreg(string s){
	if(s.compare("areg")==0)
		return 1;
	if(s.compare("breg")==0)
		return 2;
	if(s.compare("creg")==0)
		return 3;
	if(s.compare("dreg")==0)
		return 4;
	return -1;
}

void assembler::pass_I(){
	int lc=0,itoken,pos,pos1,pos2,reg;
	res r;
	string line,token1,token2,token3;
	ifstream fp("/home/hp/source_code_lit.txt");
	if(fp.is_open()){
		while(!fp.eof()){
			getline(fp,line,'\n');
			istringstream iss(line);
			iss>>token1;
			if(token1.compare("start")==0){	//start
				iss>>itoken;
				lc=itoken;
				ostringstream op;
				op<<itoken;
				pass1[l++]=op.str()+" ad , 1 0 c , "+op.str();
				continue;
			}
			if(token1.compare("end")==0){	//end
				ostringstream op;
				op<<lc<<" ad , 2";
				pass1[l++]=op.str();
				for(int k=pb;k<lt;k++)
					litab[k].add=lc++;

				break;
			}

			r=search_op(token1);
			if(r.i==-1){		//not mnemonic
				cout<<"Error!!!";
				exit(0);
			}
			else{				//mnemonic
				opcode p=table[r.i][r.j];
				ostringstream o1,o2,o3;
				o1<<lc<<" "<<p.i_class<<" , "<<p.code<<" ";
				pass1[l]=o1.str();
				if(p.i_class.compare("is")==0)
					lc++;
				iss>>token2;
				if(p.no==0){
					l++;
					if(p.mnemonic.compare("ltorg")==0){
						pooltab[0]=0;
						pooltab[pl++]=lt;
						for(int k=pb;k<lt;k++)
							litab[k].add=lc++;
						pb=lt;
					}
					continue;
				}
				if(p.no==2){
					reg=isreg(token2);
					if(reg!=-1)
						o2<<reg<<" ";
					else{
						cout<<"Invalid register!!";
						exit(0);
					}
					iss>>token3;
					iss>>token3;
					pos=search_lit(token3,pb);
					if(pos==-1){
						addlit(token3);
						pos=search_lit(token3,pb);
					}
					o3<<pos;
					pass1[l++]+=o2.str()+" l , "+o3.str();
				}
			}
		}
	}

}
void assembler::op_pass_I()
{	std::ofstream file("/home/hp/pass_1.txt");

	for(int i=0;i<l;i++)
	{	cout<<pass1[i]<<std::endl;
		file<<pass1[i]<<std::endl;
	}
	file.close();
}
void assembler::print_lit()
{	std::cout<<"\nNo.\tLiteral\tAddress\n";
	for(int i=0;i<lt;i++)
		std::cout<<i<<".\t"<<litab[i].lit<<"\t"<<litab[i].add<<"\n";
}
void assembler::print_pool()
{
	std::cout<<"\nNo.\tPool Start\n";
	for(int i=0;i<pl;i++)
		cout<<i<<".\t"<<pooltab[i]<<"\n";

}
int assembler::get_index(int a){
	for(int i=0;i<lt;i++){
		if(litab[i].add==a)
			return i;
	}
	return -1;
}
void assembler::pass_II(){
	int lc=0,c=0,itoken,add,i,itoken2;
	string line,token1,token2,token3;
	ifstream fp("/home/hp/pass_1.txt");
	if(fp.is_open()){
		cout<<"File opened,,,,reading!!!";
		while(!fp.eof()){
			getline(fp,line,'\n');
			istringstream iss(line);
			iss>>itoken;
			lc=itoken;
			iss>>token1;
			if(token1.compare("is")!=0){
				ostringstream o1;
				o1<<lc<<")  ";
				pass2[l1++]=o1.str();
				if(line.find("ad , 3")!=string::npos){
					{
						for(int k=pooltab[c];k<pooltab[c+1];k++){
							ostringstream o3;
							o3<<lc++<<") "<<litab[get_index(lc)].lit;
							pass2[l++]=o3.str();
						}
						c++;
					}
				}

				continue;
			}
			else{
				ostringstream o1;
				iss>>token2;
				iss>>itoken;
				iss>>itoken2;
				o1<<lc<<")  "<<itoken<<" "<<itoken2;
				iss>>token3;
				iss>>token3;
				iss>>i;
				add=litab[i].add;
				o1<<" "<<add;
				pass2[l1++]=o1.str();
				continue;
			}
		}
	}

}
void assembler::op_pass_II()
{	ofstream file1("/home/hp/pass_2.txt");

	for(int i=0;i<l1;i++)
	{	cout<<pass2[i]<<endl;
		file1<<pass2[i]<<endl;
	}
	file1.close();
}


int main() {
	assembler op;
	op.populate();
	op.pass_I();
	cout<<"\nOutput PassI:\n";
	op.op_pass_I();
	std::cout<<"\nLiteral Table:\n";
	op.print_lit();
	cout<<"\nPool Table:\n";
	op.print_pool();
	op.pass_II();
	cout<<"\nOutput PassII:\n";
	op.op_pass_II();
	return 0;
}

