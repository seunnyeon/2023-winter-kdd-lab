#include <iostream>
using namespace std;

int** ED(string X, string Y){
    int m = X.length(); int n = Y.length();
    int** C=new int*[m+1];
    for(int i=0; i<=m; i++) C[i]=new int[n+1];
    for(int i=1; i<=m; i++) {C[i][0]=i;}
    for(int i=1; i<=n; i++) {C[0][i]=i;}
    C[0][0]=0;
     for(int i=1; i<=m; i++){
        for(int j=1; j<=n; j++){
            int min;
                min=C[i-1][j-1];
                if(C[i-1][j]>=0 && min>C[i-1][j]) min=C[i-1][j];
                if(C[i][j-1]>=0 && min>C[i][j-1]) min=C[i][j-1];       
            if(X[i-1]==Y[j-1]) {
                C[i][j]=min;
            }
            else C[i][j]=min+1;
        }
    }
    return C;
}

void print_ED(int** C, string X, string Y,int m, int n){
    int i=m; int j=n; int min; string dir;
    //cout<< i<<", "<<j<<"번째 - 실행"<<endl;
    if(i==0 || j==0);
    else{
        if(i==1 && j==1){
            if(X[i-1]==Y[j]) {dir="U"; min=C[i][j-1];}
            else if(X[i]==Y[j-1]) {dir="L"; min=C[i-1][j];}
            else {dir="D"; min=C[i-1][j-1];}
        }
        else if(i==1) {min=C[i][j-1]; dir="U";}
        else if(j==1) {min=C[i-1][j]; dir="L";}
        else{
            min=C[i-1][j-1];
            dir="D";
            if(C[i-1][j]<min && C[i-1][j]>=0) {min=C[i-1][j];  dir="L";}
            if(C[i][j-1]<min && C[i][j-1]>=0){min=C[i][j-1];  dir="U";}
        }
        if(dir=="D") {
            print_ED(C,X,Y,i-1,j-1);
            if(min<C[i][j]) {
                cout<<i<<", "<<j<<"번째 : substitute --> ";
                for(int k=0; k<=j-1; k++) cout<<Y[k];
                for(int k=i; k<X.length(); k++) cout<<X[k];
                cout<<endl;
            }
        }
        else if(dir=="L") {
            print_ED(C,X,Y,i-1,j);
            if(min<C[i][j]){
                cout<<i<<", "<<j<<"번째 : delete --> ";
                for(int k=0; k<=j-1; k++) cout<<Y[k];
                if(i>1 && i<X.length()) {for(int k=i; k<X.length(); k++) cout<<X[k];}
                else{for(int k=i+1; k<X.length(); k++) cout<<X[k];}
                cout<<endl;
            }            
        }
        else {
            print_ED(C,X,Y,i,j-1);
            if(min<C[i][j]){
                cout<<i<<", "<<j<<"번째 : insert --> ";
                for(int k=0; k<=j-1; k++) cout<<Y[k];
                if(min==-1) {for(int k=i-1; k<X.length(); k++) cout<<X[k];}
                else {for(int k=i; k<X.length(); k++) cout<<X[k];}
                cout<<endl;
            }
        }
    }
}


int main(){
    string X;
    string Y;
    cin>>X;
    cin>>Y;
    int m = X.length(); int n = Y.length();
    int** C = new int*[m+1];
    for(int i=0; i<=m; i++){
        C[i]=new int[n+1];
    }
    C=ED(X,Y);
     for(int i=1;i<=m;i++){
        for(int j=1; j<=n;j++){
            cout<<C[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"total cost: "<<C[m][n]<<endl;
    cout<<X<<endl;
    print_ED(C,X,Y,m,n);
    delete[] C; 
    return 0;
}