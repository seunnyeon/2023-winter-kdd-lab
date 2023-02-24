#include "polynomial.h"
#include <iostream>
#include <cstring>
using namespace std;

Polynomial::Polynomial() { poly = CircularList<Term>(); }
Polynomial::Polynomial(const Polynomial& a) {
	this->poly = a.poly;
}                             // (c) Copy constructor
Polynomial::~Polynomial() {
	ChainNode<Term>* temp = poly.last->GetLink();
	ChainNode<Term>* first = poly.last;
	ChainNode<Term>* next;
	while (temp != first) {
		next = temp->link;
		temp->~ChainNode();
		temp = next;
	}
	first->~ChainNode();
}
// (e) Destructor
Polynomial& Polynomial:: operator=(const Polynomial& a) {
	this->poly= Polynomial().poly; 
	ChainNode<Term>* temp = a.poly.GetLast()->GetLink();
	ChainNode<Term>* current = this->poly.GetLast();
	ChainNode<Term>* first = a.poly.GetLast();
	int co; int ex;
	int* num = new int[100];
	int i = 0;
	do {
		co = temp->GetData().coef;
		ex = temp->GetData().exp;
		num[i++] = co;
		num[i++] = ex;
		temp = temp->GetLink();
	} while (temp != first);

	for (int j = i - 1; j >= 0; j -= 2) {
		Term k = Term();
		k.Set(num[j - 1], num[j]);
		this->poly.InsertFront(k);
	}
	delete[] num;
	return *this;
}               // (d) Assign operator

float Polynomial::Evaluate(float x) const {
	float result = 0;
	ChainNode<Term>* first=this->poly.GetLast();
	ChainNode<Term>* temp = first->GetLink();
	while (temp != first) {
		int exp = temp->GetData().exp;
		if (exp == 0) result += temp->GetData().coef;
		else {
			float c = temp->GetData().coef;
			for (int i = 0; i < exp; i++) {
				c *= x;
			}
			result += c;
		}
		temp = temp->GetLink();
	}
	return result;
}               // (i) Evaluate polynomial
Polynomial Polynomial:: operator+(const Polynomial& b) const{
	int* list = new int[1000]; int i = 0;
	Polynomial c;
	ChainNode<Term>* first_a = this->poly.GetLast();
	ChainNode<Term>* first_b = b.poly.GetLast();
	ChainNode<Term>* temp_a = first_a->GetLink();
	ChainNode<Term>* temp_b = first_b->GetLink();
	while (first_a != temp_a && first_b != temp_b) {
		int exp_a = temp_a->GetData().exp;
		int exp_b = temp_b->GetData().exp;
		if (exp_a == exp_b) {
			int sum = temp_a->GetData().coef + temp_b->GetData().coef;
			if (sum) {
				list[i++] = sum; list[i++] = exp_a;
			}
			temp_a = temp_a->GetLink();
			temp_b = temp_b->GetLink();
		}
		else if (exp_a < exp_b) {
			list[i++] = temp_b->GetData().coef; list[i++] = exp_b;
			temp_b = temp_b->GetLink();
		}
		else {
			list[i++] = temp_a->GetData().coef; list[i++] = exp_a;
			temp_a = temp_a->GetLink();
		}
	}
	while (first_a != temp_a) {
		list[i++] = temp_a->GetData().coef; list[i++] = temp_a->GetData().exp;
		temp_a = temp_a->GetLink();
	}
	while (first_b != temp_b) {
		list[i++] = temp_b->GetData().coef; list[i++] = temp_b->GetData().exp;
		temp_b = temp_b->GetLink();
	}
	for (int j = i - 1; j >= 0; j -= 2) {
		Term k = Term();
		k.Set(list[j - 1], list[j]);
		c.poly.InsertFront(k);
	}
	delete[] list;
	return c;
}              // (f) Addition
Polynomial Polynomial:: operator-(const Polynomial& b) const{
	int* list = new int[1000]; int i = 0;
	Polynomial c;
	ChainNode<Term>* first_a = this->poly.GetLast();
	ChainNode<Term>* first_b = b.poly.GetLast();
	ChainNode<Term>* temp_a = first_a->GetLink();
	ChainNode<Term>* temp_b = first_b->GetLink();
	while (first_a != temp_a && first_b != temp_b) {
		int exp_a = temp_a->GetData().exp;
		int exp_b = temp_b->GetData().exp;
		if (exp_a == exp_b) {
			int sum = temp_a->GetData().coef - temp_b->GetData().coef;
			if (sum) {
				list[i++] = sum; list[i++] = exp_a;
			}
			temp_a = temp_a->GetLink();
			temp_b = temp_b->GetLink();
		}
		else if (exp_a < exp_b) {
			list[i++] = temp_b->GetData().coef*(-1); list[i++] = exp_b;
			temp_b = temp_b->GetLink();
		}
		else {
			list[i++] = temp_a->GetData().coef; list[i++] = exp_a;
			temp_a = temp_a->GetLink();
		}
	}
	while (first_a != temp_a) {
		list[i++] = temp_a->GetData().coef; list[i++] = temp_a->GetData().exp;
		temp_a = temp_a->GetLink();
	}
	while (first_b != temp_b) {
		list[i++] = temp_b->GetData().coef*(-1); list[i++] = temp_b->GetData().exp;
		temp_b = temp_b->GetLink();
	}
	for (int j = i - 1; j >= 0; j -= 2) {
		Term k = Term();
		k.Set(list[j - 1], list[j]);
		c.poly.InsertFront(k);
	}
	delete[] list;
	return c;
}               // (g) Substarction
Polynomial Polynomial:: operator*(const Polynomial& b) const{
	Polynomial c;
	int* list_a = new int[100]; int* list_b = new int[100];
	int* coef_a = new int[100]; int* coef_b = new int[100];
	int i = 0; int j = 0;
	ChainNode<Term>* first_a = this->poly.GetLast();
	ChainNode<Term>* first_b = b.poly.GetLast();
	ChainNode<Term>* temp_a = first_a->GetLink();
	ChainNode<Term>* temp_b = first_b->GetLink();
	while (first_a != temp_a) {
		list_a[i] = temp_a->GetData().exp;
		coef_a[i++] = temp_a->GetData().coef;
		temp_a = temp_a->GetLink();
	}
	while (first_b != temp_b) {
		list_b[j] = temp_b->GetData().exp;
		coef_b[j++] = temp_b->GetData().coef;
		temp_b = temp_b->GetLink();
	}
	
	int** exp_list = new int*[i];
	int** coef_list = new int* [i];
	for (int k = 0; k < i; k++) {
		exp_list[k] = new int[3*j];
		coef_list[k]= new int[3*j];
		for (int l = 0; l < j; l++) {
			exp_list[k][l] = list_a[k] + list_b[l];
			coef_list[k][l] = coef_a[k] * coef_b[l];
		}
	}
	int num = 1; int index = 2;
	int* result = new int[i * j];
	result[0] = coef_list[0][0];	result[1] = exp_list[0][0];
	/*for (int k = 0; k < i; k++) {
		for (int l = 0; l < j; l++) {
			cout<< coef_list[k][l]<<", "<< exp_list[k][l]<<endl;
		}
	}*/
	exp_list[0] += 1;	coef_list[0] += 1;
	for (int k = 0; k < i; k++) {
		for (int l = 0; l < j; l++) {
			cout<< coef_list[k][l]<<", "<< exp_list[k][l]<<endl;
		}
	}
	while (num <= i*j-1 ){
		int sum = 0;
		int max = 0;
		for (int k = 1; k < i; k++)
			if (max < exp_list[k][0]) max = exp_list[k][0];
		for (int k = 0; k < i; k++) {
			if (max == exp_list[k][0]) {
				sum += coef_list[k][0];
				exp_list[k] += 1;	coef_list[k] += 1;
				num++;
			}
		}
		cout<< "max: "<<max<<", sum : "<<sum<<endl;
		result[index++] = sum;	result[index++] = max;
	}
	for(int real=0; real<index;real++)cout<<result[real]<<", "; 
	cout<<endl;
	int real1 = index - 1; int real2 = index - 2;
	cout<<result[index-4]<<", "<<result[index-3]<<endl;
	cout<<result[10]<<", "<<result[11]<<endl;
	cout<<"IDon't know"<<endl;
	while(real1>=0){
		cout<<result[real2]<<", "<< result[real1]<<endl;
        Term k = Term();		
		k.Set(result[real2], result[real1]);
		c.poly.InsertFront(k);
		real1=real1-2; real2=real2-2;
	}
	cout<<"-----------------------------"<<endl;
	for(int real=0; real<index;real++)cout<<result[real]<<", "; 
	cout<<endl;
	delete[] list_a; delete[] list_b;
	delete[] coef_a; delete[] coef_b;
	/*for(int del=0;del<i;del++){
		delete[] *(coef_list+del);
		delete[] *(exp_list+del);
	}*/
	delete[] coef_list;
	delete[] exp_list;
	return c;
}               // (h) Multiplication
istream& operator>>(istream& is, Polynomial& x) {
	int n;
	is >> n;
	int* list = new int[2 * n]; 
	char str[100];
	is >> str;
	int i = 0;	int j = 0;	string c; int l = strlen(str);
	while (i < l) {
		if (str[i] != 44) {
			c += str[i];
		}
		else {
			if (c != "") list[j++] = stoi(c);
			c = "";
		}
		i++;
	}
	list[j++] = stoi(c);

	for (int i = j - 1; i >= 0; i -= 2) {
		Term k = Term();
		k.Set(list[i - 1], list[i]);
		x.poly.InsertFront(k);
	}
	delete[] list;
	return is;

}// (a) Read
ostream& operator<<(ostream& os, const Polynomial& x) {
	ChainNode<Term>* temp = x.poly.GetLast()->GetLink();
	ChainNode<Term>* first = x.poly.GetLast();
	int n = 0;
	while (temp != first) {
		n += 1;
		temp = temp->GetLink();
	}
	temp = temp->GetLink();
	os << n;
	for (int i = 0; i < n; i++) {
		os << "," << temp->GetData().coef << "," << temp->GetData().exp;
		temp = temp->GetLink();
	}
	os << endl;
	return os;
}//(b) External representaion