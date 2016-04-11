#include<iostream>
#define INF 99
using namespace std;

class tsp{
public:
int visited[10],cost[10],n,l;
int tsp1[10][10];
int node_no;
int row_min(int m[][10],int r);
int col_min(int m[][10],int c);
int min(int temp[][2],int q);
int reduce(int m[][10]);
void bnbreduction();
void display();
bool check(int);
void input();
tsp()
{
	l=0,node_no=1;
	for (int i = 0; i < 10; i++)
		visited[i]=-1;
}
};
void tsp:: input(){
	cout<<"\nEnter no. of cities :";
	cin>>n;
	cout<<"\nEnter matrix :";
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>tsp1[i][j];

}
int tsp:: row_min(int m[][10],int r){
	int min=INF;
	for(int j=0;j<n;j++){
		if(min>m[r][j])
			min=m[r][j];
	}
	if(min==INF)
		min=0;
	return min;
}
int tsp:: col_min(int m[][10],int c){
	int min=INF;
	for(int i=0;i<n;i++){
		if(min>m[i][c])
			min=m[i][c];
	}
	if(min==INF)
		min=0;
	return min;
}	
int tsp:: min(int temp[][2],int q){
	int p,min=INF;	
	for(int i=0;i<q;i++)
		if(min>temp[i][1]){
			min=temp[i][1];
			p=i;
		}
	return p;
}
int tsp:: reduce(int m[][10]){
	int min,sum=0;
	for(int i=0;i<n;i++){
		min=row_min(m,i);
		sum+=min;
		for(int j=0;j<n;j++)
			if(m[i][j]!=INF)
				m[i][j]-=min;
		}
	for(int i=0;i<n;i++){
		min=col_min(m,i);
		sum+=min;
		for(int j=0;j<n;j++)
			if(m[j][i]!=INF)
				m[j][i]-=min;
		}
	cout << "\nREDUCED MATRIX FOR NODE " << node_no++ << " : \n";
	for(int i = 0;i < n;i++) {
		for(int j = 0;j < n;j++)
			cout << m[i][j]<<"\t";
		cout << "\n";
	}
	cout<<sum;
	return sum;
}
void tsp:: display(){
	int sum=0;
	cout<<"\nThe Path is :";
	for(int i=0;i<l;i++)
		cout<<visited[i]+1<<"->";
	cout<<"1\n";
	cout<<"\nTotal cost :"<<cost[l-1];
}

bool tsp:: check(int k){
	for(int i=0;i<l;i++){
		if(visited[i]==k)
			return false;
	}
	return true; 
}
void tsp:: bnbreduction(){
int temp[10][2],m[10][10],q,i,p,k,j,sum=0;
while(l<n)
{
	q=0;
	//cout<<q<<"hi";
	for(i=0;i<n;i++)
	{
	//	cout<<i<<"\t";
		if(check(i))
			temp[q++][0]=i;
	}
	for(k=0;k<q;k++)
	{
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				m[i][j]=tsp1[i][j];
		for(i=0;i<l;i++)
			for(j=0;j<n;j++)
				m[visited[i]][j]=INF;
		for(i=1;i<l;i++)
			for(j=0;j<n;j++)
				m[j][visited[i]]=INF;
		for(i=0;i<n;i++)
			m[i][temp[k][0]]=INF;
		for(i=1;i<l;i++)
			//if(visited[i+1]!=-1)
				m[visited[i]][0]=INF;
		m[temp[k][0]][0]=INF;
		sum=reduce(m);
		cout<<sum<<"\t"<<cost[l-1]<<"\t"<<tsp1[visited[l-1]][temp[k][0]];
		temp[k][1]=sum+cost[l-1]+tsp1[visited[l-1]][temp[k][0]];
		cout<<"\nCost of node "<<node_no-1<<" :"<<temp[k][1];
	}
	p=min(temp,q);
	visited[l]=temp[p][0];
	cost[l++]=temp[p][1];
	cout<<"\nMinimum cost city :"<<temp[p][0]<<"\tCost :"<<temp[p][1];	
}
}

int main(){
	tsp p;
	p.input();
	p.visited[p.l]=0;
	p.cost[p.l++]=p.reduce(p.tsp1);
	p.bnbreduction();
	p.display();
}
