#include <iostream>
#include <string>
using namespace std;

int longest(int* ne, int n, int big){
    if(big==n-1) return 1;
    int max=0;
    for(int i=big+1; i<n; i++){
        int num=1;
        if(ne[i]>ne[big]){
                int a=longest(ne, n, i);
                num+=a;
        }
        if(max<num)max=num;
        num=1;
    }
    return max;
}

int whole(int* ne, int n, int big){
    int max=0;
    while(big<n){
        int a = longest(ne,n,big);
        if(max<a) max=a;
        big++;
    }
    return max;
}

int main(){
    int n; string c;
    cin>>n;
    cin.ignore();
    getline(cin,c);
    int* num=new int[n]; string temp; int j=0; int length=c.length();
    for(int i=0; i<n; i++){
        while(c[j]!=32 && j<length){
            temp+=c[j++];
        }
        j++;
        num[i]=stoi(temp);        
        temp="";
    }
    cout<<whole(num,n,0);
    return 0;
}