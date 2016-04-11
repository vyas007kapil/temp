//============================================================================
// Name        : 1eass.cpp
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

class sym{
	string symbol;
	int add;
	bool used,defined;
	friend class assembler;
};

class res{
	int i,j;
	friend class assembler;
};

class assembler{
	opcode table[26][5];
	sym symtab[10];
	int bucket[26],s,l,l1;
	string pass1[50],pass2[50];
	public:
	assembler(){
		s=l=l1=0;
		for(int i=0;i<26;i++)
			bucket[i]=0;
	}
	void populate();
	res search_op(string);
	int search_sym(string);
	void addsym(string);
	int isreg(string);
	void pass_I();
	void pass_II();
	void op_pass_I();
	void op_pass_II();
	void print_sym();
};
void assembler::populate(){
	string line,token;
	int num,i,j;
	ifstream fp("/home/hp/optab.txt");
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

int assembler::search_sym(string str){
	for(int i=0;i<s;i++){
		if(str.compare(symtab[i].symbol)==0){
			return i;
		}
	}
	return -1;
}

void assembler::addsym(string str){
	symtab[s].defined=true;
	symtab[s++].symbol=str;

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
	if(s.compare("gt")==0)
		return 5;
	if(s.compare("gte")==0)
		return 6;
	if(s.compare("lt")==0)
		return 7;
	if(s.compare("le")==0)
		return 8;
	return -1;
}

void assembler::pass_I(){
	int lc=0,itoken,pos,pos1,pos2,reg;
	res r;
	string line,token1,token2,token3;
	ifstream fp("/home/hp/source_code.txt");
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
				break;
			}
			r=search_op(token1);
			if(r.i==-1){			//not mnemonic
				pos=search_sym(token1);
				if(pos==-1){
					addsym(token1);
					symtab[pos].used=true;
				}
				pos=search_sym(token1);
				iss>>token2;
				if(token2.compare("equ")==0){
					iss>>token3;
					pos1=search_sym(token1);
					pos2=search_sym(token3);
					symtab[pos1].add=symtab[pos2].add;
					symtab[pos1].defined=true;
					/*ostringstream o1;
					o1<<" ";
					pass1[l++]=o1.str();
				*/	continue;
				}
				r=search_op(token2);
				opcode p=table[r.i][r.j];
				if(p.i_class.compare("dl")==0){
					iss>>itoken;
					symtab[pos].add=lc;
					ostringstream o1;
					o1<<lc<<" "<<p.i_class<<" , "<<p.code<<" c , "<<itoken;
					if(p.mnemonic.compare("ds")==0)
						lc+=itoken;
					else	lc++;
					pass1[l++]=o1.str();
					continue;
					}
				else{
					symtab[pos].add=lc;
					ostringstream o1;
					o1<<lc<<" "<<p.i_class<<" , "<<p.code<<" ";
					iss>>token3;
					reg=isreg(token3);
					o1<<reg;
					iss>>token3;
					iss>>token3;
					pos2=search_sym(token3);
					if(pos2==-1){
						addsym(token3);
					}
					pos2=search_sym(token3);
					o1<<" s , "<<pos2;
					lc++;
					pass1[l++]=o1.str();
					continue;

				}
			}
			else{
				opcode p=table[r.i][r.j];
				iss>>token2;
				reg=isreg(token2);
				if(reg!=-1){
					ostringstream o1;
					o1<<lc<<" "<<p.i_class<<" , "<<p.code<<" "<<reg;
					iss>>token3;
					iss>>token3;
					pos2=search_sym(token3);
					if(pos2==-1){
						addsym(token3);
					}
					pos2=search_sym(token3);
					o1<<" s , "<<pos2;
					lc++;
					pass1[l++]=o1.str();
					continue;
				}
				else{
					ostringstream o1;
					o1<<lc<<" "<<p.i_class<<" , "<<p.code;
					pos2=search_sym(token2);
					if(pos2==-1){
						addsym(token2);
					}
					pos2=search_sym(token2);
					o1<<" 0 s , "<<pos2;
					lc++;
					pass1[l++]=o1.str();
					continue;
				}
			}
		}
	}

}
void assembler::op_pass_I(){
	ofstream file("/home/hp/pass_1.txt");
	for(int i=0;i<l;i++){
		cout<<pass1[i]<<endl;
		file<<pass1[i]<<endl;
	}
}
void assembler::print_sym()
{	cout<<"\nNo.\tSymbol\tAddress\n";
	for(int i=0;i<s;i++)
		cout<<i<<".\t"<<symtab[i].symbol<<"\t"<<symtab[i].add<<"\n";
}
void assembler::pass_II(){
	int lc=0,itoken,add,i,itoken2;
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
				if(token1.compare("0")==0)
					break;

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
				add=symtab[i].add;
				o1<<" "<<add;
				pass2[l1++]=o1.str();
				continue;
			}
		}
	}
}
void assembler::op_pass_II()
{	ofstream file1("/home/hp/pass_2.txt");

	for(int i=0;i<l1-1;i++)
	{	cout<<pass2[i]<<endl;
		file1<<pass2[i]<<endl;
	}
	file1.close();
}
int main(){
	assembler op;
	op.populate();
	op.pass_I();
	cout<<"\nOutput PassI:\n";
	op.op_pass_I();
	std::cout<<"\nSymbol Table:\n";
	op.print_sym();
	op.pass_II();
	cout<<"\nOutput PassII:\n";
	op.op_pass_II();
	return 0;
}

