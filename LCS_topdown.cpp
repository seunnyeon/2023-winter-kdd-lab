#include <iostream>
using namespace std;

int LCS1_AUX(string a[],string b[],int*** C[],int p, int q, int r, int s){
    if(C[p][q][r][s]>=0) return C[p][q][r][s];
    if(p==q && r==s){
        if(a[p]==b[r]) { 
            C[p][q][r][s]=1;
            return 1;
        }
        else {
            C[p][q][r][s]=0;
            return 0;
        }
    }
    int c=0;
    if(p==q){
        for(int j=r; j<s;j++){
            int k=LCS1_AUX(a,b,C,p,p,r,j)+LCS1_AUX(a,b,C,q,q,j+1,s);
            if(c<k) c=k;
        }
    }
    else if(r==s){
        for(int i=p; i<q;i++){
            int k=LCS1_AUX(a,b,C,p,i,r,r)+LCS1_AUX(a,b,C,i+1,q,s,s);
            if(c<k) c=k;
        }
    }
    for(int i=p; i<q;i++){
        for(int j=r; j<s;j++){
            int k=LCS1_AUX(a,b,C,p,i,r,j)+LCS1_AUX(a,b,C,i+1,q,j+1,s);
            if(c<k) c=k;
        }
    }
    C[p][q][r][s]=c;
    return c;
}

int LCS1(string a[],string b[],int m,int n){
    int ****C=new int***[m+1];
    for(int i=0;i<=m;i++){
        C[i]=new int**[m+1];
        for(int j=0;j<=m;j++){
            C[i][j]=new int*[n+1];
            for(int k=0;k<=n;k++){
                C[i][j][k]=new int[n+1];
                for(int l=0;l<=n;l++){
                  C[i][j][k][l]=-1;
                }
            }
        }
    }
    return LCS1_AUX(a,b,C,1,m,1,n);
}

int main(){
    int m; int n; int ans;
    string X[10]={"A","B","C","B","D","A","B"};
    string Y[10]={"B","D","C","A","B","A"};
    cin>>m;
    cin>>n;
    ans=LCS1(X,Y,m,n);
    cout<<"야호 정답은? "<<ans<<endl;
    return 0;
}