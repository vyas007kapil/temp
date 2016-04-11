//============================================================================
// Name        : hamiltonian.cpp
// Author      : KAPIL
// Version     :
// Copyright   : TE 10
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
class hamiltonian{
	int **a,n,*path;
public:
	hamiltonian(int no){
		n=no;
		a=new int*[n];
		path=new int[n];
		for(int i=0;i<n;i++){
			path[i]=-1;
			a[i]=new int[n];
		}
	}
	void input();
	void hampath();
	int findnext(int);
	bool issafe(int,int);
	void display();
	void printsolution(int*);
};
void hamiltonian::display(){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<a[i][j]<<"\t";
		}
		cout<<"\n";
	}
}
void hamiltonian:: input(){
	int s,d;
	cout<<"Enter source,destination!!!";

	while(true){
		cin>>s>>d;
	if(s>n || d>n){
		cout<<"wrong vertex...";
		break;
	}
	if(s==-1 || d==-1)
		break;
	a[s][d]=1;
	a[d][s]=1;
	}
}
bool hamiltonian::issafe(int v,int pos){
	if(pos==0)
		return true;
	if(a[path[pos-1]][v]==0)
		return false;
	for(int i=0;i<pos;i++){
		if(path[i]==v)
			return false;
	}
	return true;
}
int hamiltonian::findnext(int pos){
	int i;
	if(pos==0){
		if(path[pos]==-1)
			return 0;
		else if(path[pos]<n-1)
			return path[pos]+1;
		else return -1;
	}
	if(pos>=n)
		return -1;
	else{
		i=path[pos]+1;
		while(i<n){
			if(issafe(i,pos))
				return i;
			i++;
		}
	}
	return -1;
}

void hamiltonian::hampath(){
	int pos=0,v;

	while(true){
		v=findnext(pos);
		if(v==-1){
			path[pos--]=-1;
			if(pos==-1)
				return;
		}
		else{
			path[pos++]=v;
			if(pos==n){
				printsolution(path);
				path[--pos]=-1;
				pos--;
			}
		}
	}
}
void hamiltonian::printsolution(int *path){
	int i;
	for(i=0;i<n;i++)
		cout<<path[i]<<"->";
		if(a[path[i-1]][path[0]])
			cout<<path[0]<<endl;
		cout<<endl;
}
int main() {
	int n;
	cout<<"Enter vertices";
	cin>>n;
	hamiltonian h(n);
	h.input();
	h.display();
	h.hampath();
	cout << "WELCOME" << endl; // prints WELCOME
	return 0;
}

