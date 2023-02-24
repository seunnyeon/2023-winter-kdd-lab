#include <iostream>
using namespace std;

int LCS2_AUX(string X,  string Y, int i, int j, int* C[], int m, int n){//모든 케이스가 콜링이 되어야 하는디....
    if(C[i][j]!=-1) return C[i][j];
    for(int k=i; k<=m; k++){
        for(int l=j; l<=n; l++){
            if(X[k-1]==Y[l-1] && X[k-1]!=0){
                int a=1+LCS2_AUX(X,Y,k+1,l+1,C,m,n);
                if(C[k][l]<a) C[k][l]=a;
            }
            else{
                int b=LCS2_AUX(X,Y,k+1,l,C,m,n);
                int c=LCS2_AUX(X,Y,k,l+1,C,m,n);
                if(b>=c && C[k][l]<b) C[k][l]=b;
                else if(c>b && C[k][l]<c) C[k][l]=c;
            }
        }
    }
    if(i==1&& j==1){
        cout<<"C"<<endl;
        for(int q=1; q<=m+1;q++){
            for(int p=1;p<=n+1;p++){
                cout<<C[q][p]<<" ";
            }
            cout<<endl;
        }
    }
    return C[i][j];
}

int LCS2(string X,  string Y){
    int m=X.length(); int n=Y.length();
    int** C=new int*[m+2];
    for(int i=0; i<m+2; i++){
        C[i]=new int[n+2];
        for(int j=0; j<n+2;j++){
            if(j==n+1||i==m+1) C[i][j]=0;
            else C[i][j]=-1;
        }
    }
    int opt=LCS2_AUX(X,Y,1,1,C,m,n);
    return opt;
}

int main(){
    string X="ABCBDAB";
    string Y="BDCABA";
    int k=LCS2(X,Y);
    cout<<"LCS_result: "<<k<<endl;
    return 0;
}