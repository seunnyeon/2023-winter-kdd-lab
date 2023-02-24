#include <iostream>
using namespace std;

int size(int*p){
    int num=0;
    while(p[num]>0){
        if(p[++num]<=0) break;
    }
    return num;
}

pair<int**, int**> matrix_chain_order(int* p){
    int q;
    int n=size(p);
    int **m=new int*[n];
    int **s=new int*[n];
    for(int i=1; i<=n;i++){
        m[i]=new int[n];
        s[i]=new int[n];
        m[i][i]=0;
    }
    for(int l=2; l<=n;l++){
        for(int i=1; i<=n-l+1;i++){
            int j=i+l-1;
            m[i][j]=0;
            for(int k=i; k<=j-1; k++){
                q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if(m[i][j]==0) {m[i][j]=q; s[i][j]=k;}
                else if(q<m[i][j]) {
                    m[i][j]=q;
                    s[i][j]=k;
                }
            }
        }
    }
    return make_pair(m, s);
}

void print_optimal(int** s, int i, int j){
    if(i==j) cout<<"A_"<<i;
    else{
        cout<<"(";
        print_optimal(s,i,s[i][j]);
        print_optimal(s,s[i][j]+1,j);
        cout<<")";
    }
}

int main(){
   int* p=new int[7];
   p[0]=30; p[1]=35; p[2]=15; p[3]=5; p[4]=10; p[5]=20; p[6]=25;
   int** m=new int*[7]; int** s=new int*[7];
   for(int i=0;i<7;i++) {
    m[i]=new int[7];
    s[i]=new int[7];
   }
   pair<int**, int**> l= matrix_chain_order(p);
   m=l.first; s=l.second;
   for(int i=1;i<7;i++) {
    for(int j=i;j<7;j++){
      cout<<i<<", "<<j<<"번째: "<<m[i][j]<<", "<< s[i][j]<<endl;
    }    
   }
   print_optimal(s,1,6);
   cout<<endl;

   return 0;
}