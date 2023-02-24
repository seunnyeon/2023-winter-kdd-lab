#include <iostream>
using namespace std;

int** SED(string X, string Y){
    int m = X.length(); int n = Y.length();
    int** C=new int*[m+1];
    for(int i=0; i<=m; i++) C[i]=new int[n+1];
    for(int i=1; i<=m; i++) C[i][0]=i;
    for(int i=1; i<=n; i++) C[0][i]=0;
    C[0][0]=0;
     for(int i=1; i<=m; i++){
        for(int j=1; j<=n; j++){
            int min=C[i-1][j-1];
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


int main(){
    string X;
    string Y;
    cin>>X;
    cin>>Y;
    int m = X.length(); int n = Y.length(); int min_ed=10000;
    int** C = new int*[m+1];
    for(int i=0; i<=m; i++){
        C[i]=new int[n+1];
    }
    C=SED(X,Y);
     for(int i=0;i<=m;i++){
        for(int j=0; j<=n;j++){
            cout<<C[i][j]<<" ";
            if(i==m) if(C[m][j]<min_ed) min_ed=C[m][j];
        }
        cout<<endl;
    }
    cout<<X<<endl;
    cout<<"min_edit_distance: "<<min_ed<<endl;
    delete[] C; 
    return 0;
}