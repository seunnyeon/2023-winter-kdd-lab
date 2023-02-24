#include <iostream>
using namespace std;

pair<double**,int**> Optimal_bst(double p[], double q[], int n){
    //e : expected cost
    double**e= new double*[n+2]; double** w=new double*[n+2]; int** root=new int*[n+1];
    for(int i=1; i<=n+1; i++){
        e[i]=new double[n+1];
        w[i]=new double[n+1];
        if(i<n+1)  root[i]=new int[n+1];
        e[i][i-1]=q[i-1];
        w[i][i-1]=q[i-1];
        }
    for(int l=1; l<=n; l++){
        for(int i=1; i<=n-l+1; i++){
            int j=i+l-1;
            e[i][j]=1000;
            w[i][j]=w[i][j-1]+p[j]+q[j];
            for(int r=i; r<=j; r++){
                double t=e[i][r-1]+e[r+1][j]+w[i][j];
                if(t<e[i][j]){
                    e[i][j]=t;
                    root[i][j]=r;
                }
            }
        }
    }
    cout<<"------------------w---------------"<<endl;
    for(int i=1; i<=n+1; i++){
        for(int j=0; j<=n; j++){
            cout<<w[i][j]<<"   ";
        }
        cout<<endl;
    }
    return make_pair(e,root);
}
int main(){
    int n=5; double**e= new double*[n+2]; int** root=new int*[n+2];
    for(int i=1; i<=n+1; i++){
        e[i]=new double[n+1];
        root[i]=new int[n+1];
    }
    double p[6]={0,0.15,0.10,0.05,0.10,0.20};
    double q[6]={0.05,0.10,0.05,0.05,0.05,0.10};
    pair<double**, int**> l=Optimal_bst(p,q,n);
    e=l.first;
    root=l.second;
    cout<<"------------------e---------------"<<endl;
    for(int i=1; i<=n+1; i++){
        for(int j=0; j<=n; j++){
            cout<<e[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"----------------root---------------"<<endl;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cout<<root[i][j]<<" ";
        }
        cout<<endl;
    }
    delete[] e;
    delete[] root;
    return 0;
}