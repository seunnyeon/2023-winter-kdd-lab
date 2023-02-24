#include <iostream>
using namespace std;
int memoized_cut_rod_aux(int* p, int n, int*r){
    int q;
    if (r[n]>=0) return r[n];
    if(n==0) q=0;
    else {
        q=-1;
        for(int i=1;i<=n;i++){
            int k=p[i]+memoized_cut_rod_aux(p, n-i, r);
            if(q<k) q=k;
        }
    }
    r[n]=q;
    return q;
}

int memoized_cut_rod(int* p, int n){
    int*r =new int[n+1];
    for (int i=0; i<n+1;i++){
        r[i]=-1;
    }
    return memoized_cut_rod_aux(p,n,r);
}

pair<int*,int*> bottom_up_cut_rod(int* p, int n){
    int q;
    int* r= new int[n+1];
    int* s= new int[n+1];
    r[0]=0;
    for (int j=1; j<=n; j++){
        q=-1;
        for(int i=1; i<=j;i++){
            if(q<p[i]+r[j-i]) {q=p[i]+r[j-i]; s[j]=i;}
        }          
        r[j]=q;
    }
    return make_pair(r, s);
}

void print(int* p, int n){
    int* r=new int[n+1]; int* s=new int[n+1];
    pair<int*, int*> l=bottom_up_cut_rod(p,n);
    r=l.first;
    s=l.second;
    cout<<"value: "<<r[n]<<endl;
    while(n>0){
        cout<<s[n]<<endl;
        n-=s[n];
    }
}



int main(){
    int n=9; int *p=new int[n+1]; 
    p[1]=1; p[2]=5; p[3]=8; p[4]=9; p[5]=10; p[6]=17; p[7]=17; p[8]=20; p[9]=24;
    cout<<"topdown : "<<memoized_cut_rod(p,n)<<endl;
    cout<<"botton_up: "<<endl;
    print(p,n);
    return 0;
}