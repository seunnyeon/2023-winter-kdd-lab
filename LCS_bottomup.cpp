#include <iostream>
using namespace std;

pair<char**, int**> LCS_length(string X, string Y){
    int m = X.length(); int n = Y.length();
    char** b=new char*[m+1]; int** c = new int*[m+1];
    for(int i=0; i<=m; i++){
        b[i]=new char[n+1];
        c[i]=new int[n+1];
    }
    for(int i=1; i<=m; i++) c[i][0]=0;
    for(int i=0; i<=n; i++) c[0][i]=0;
    for(int i=1; i<=m; i++){
        for(int j=1; j<=n; j++){
            if(X[i-1]==Y[j-1]){
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]='D';//대각선
            }
            else if(c[i-1][j]>=c[i][j-1]){
                c[i][j]=c[i-1][j];
                b[i][j]='U';//up
            }
            else{
                c[i][j]=c[i][j-1];
                b[i][j]='L';//left
            }
        }
    }
    return make_pair(b,c);
}

void print_lcs(char** b, string X, int i, int j){
    if(i==0||j==0) return;
    if(b[i][j]=='D'){
        print_lcs(b, X, i-1, j-1);
        cout<<X[i-1];
    }
    else if(b[i][j]=='U')print_lcs(b, X, i-1, j);
    else print_lcs(b, X, i, j-1);
}

int main(){    
    string X="ABCBDAB";
    string Y="BDCABA";    
    int m = X.length(); int n = Y.length();
    char** B=new char*[m+1]; int** C = new int*[m+1];
    for(int i=0; i<=m; i++){
        B[i]=new char[n+1];
        C[i]=new int[n+1];
    }
    pair<char**, int**> l=LCS_length(X,Y);
    B=l.first;
    C=l.second;
    cout<<"B: "<<endl;
    for(int i=1;i<=m;i++){
        for(int j=1; j<=n;j++){
            cout<<B[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"C: "<<endl;
    for(int i=0;i<=m;i++){
        for(int j=0; j<=n;j++){
            cout<<C[i][j]<<" ";
        }
        cout<<endl;
    }
    print_lcs(B, X, m, n);
    cout<<endl;
    delete[] B;
    delete[] C;
    return 0;
}