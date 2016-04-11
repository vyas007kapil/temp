# include <iostream>
using namespace std;

class nqueens{
	int *x,n,s;
	public :
	nqueens(int no){
		x = new int[no];
		n=no;
		s=1;
	}
	int ret(){
		return s;
	} 
	int abs(int x){
		if(x<0)
			return (-x);
		return x;
	}
	bool place(int k,int i){
		for(int j=1;j<k;j++)
			if( x[j]==i || abs(x[j]-i) == abs(j-k) )
				return false;
		return true;
	}
	void output(){
		cout<<"solution :"<<s++<<"\n";
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(x[i]==j)
					cout<<"|Q";
				else
					cout<<"|_";
			}
		cout<<"|\n";
		}
	}	
	void n_queens(int k){
		for(int i=1;i<=n;i++){
			if(place(k,i)){
				x[k]=i;
				if(k==n)
					output();
				else
					n_queens(k+1);
			}
		}
	}
};

int main(){
	int n;
	cout<<"Enter no. of queens :";
	cin>>n;
	nqueens nq(n);
	nq.n_queens(1);
	if(nq.ret()==1)
 		cout<<"No solution possible";
	return 0;
} 
