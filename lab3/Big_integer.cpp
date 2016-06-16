#include "Big_integer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using std::ifstream;
using std::ofstream;
int Ok=0;
#define DIV_BY_ZERO 1

Big_integer::Big_integer()
{//Конструктор по умолчанию
	this->size = 1;
	this->sign = 0;
	this->digs = new unsigned char[1];
	this->digs[0] = 0;
}

Big_integer::Big_integer(const char* inputstr)
{
	//Конструктор от входной строки
	
	int sLen = strlen(inputstr);
	int sSign = 0;
	if (inputstr[0] == '-')
	{
		sSign = 1;
		sLen--;
	}
	Big_integer res;
	//printf("Inputstr=%s",inputstr);
	Big_integer pow_of_ten = 1;  // Для того,чтобы преобразовать char в число по основанию 256 необходимо каждый 
								//Каждый символ превести к int значению и далее умножить на 10 в степени i, где i номер разряда.

	for (int i = sLen + sSign - 1; i >= sSign; i--)
	{
		int razryad = inputstr[i] - '0';
		res = res + pow_of_ten * razryad;
		pow_of_ten = pow_of_ten * 10;
	}
	res.sign = sSign;

	this->size = 0;
	*this = res;
	char alf[]="abcdefghijklmnopqrstuvwxyz!@#$%^&*()+=_'";
	for(int i=0; i<strlen(alf); i++)
		for(int j=0; j<strlen(inputstr); j++)
		if(inputstr[j] == alf[i])
			Ok++;
	//printf("Ok=%d",Ok);
}

Big_integer::Big_integer(const Big_integer &RValue)
{	//конструктор от Big_integer
	this->size = RValue.size;
	this->digs = new unsigned char[this->size];
	this->sign = RValue.sign;
	memcpy(digs, RValue.digs, this->size * sizeof(unsigned char));
	return;
}

Big_integer::Big_integer(int value)
{   
	//Конструктор от int-ового значения

	this->digs = new unsigned char[11]();
	this->size = 0;
	this->sign = 0;
	if (value < 0)
	{
		this->sign = 1;
		value = -value;
	}
	do
	{
		this->size++;
		this->digs[this->size - 1] = value % 256;
		value = value / 256;
	} while (value > 0);

	this->RemoveForwardZero();
}

Big_integer::~Big_integer()
{// Деструктор
	delete[] digs;
}

char* Big_integer::GetString()
{
	//Фукция получения строки в 10-й записи
	
	Big_integer temp = *this; 
	temp.sign = 0;
	
	std::vector<char> tempStr; // Вектор для хранения строки


	while (temp != (int)0)
	{
		Big_integer rem;
		temp = Div(temp, 10, rem); 
		char ost = rem[0] + '0'; 
		tempStr.push_back(ost);
	}

	
	if (this->sign)
		tempStr.push_back('-');


	int sSize = tempStr.size();
	char* string = new char[sSize + 1]();

	for (int i = 0; i < tempStr.size(); i++)
	{
		string[sSize - i - 1] = tempStr[i];
	}

	return string;
}


bool Big_integer::ReadFromTextFile(const char* filename)
{
	ifstream fp(filename);
	if (fp.fail())
		return false;
	fp.seekg(0, std::ios::end);
	int File_size = fp.tellg();
	fp.seekg(0, std::ios::beg);

	char* string = new char[File_size + 1]();
	fp >> string;
	fp.close();
	*this = Big_integer(string);
	delete[] string;
	if(Ok!=0)
	{
		return false;
	}
	else
		return true;
}

bool Big_integer::WriteToTextFile(const char* filename)
{
	ofstream fp_r(filename);
	if (fp_r.fail())
		return false;

	char* string = this->GetString();
	fp_r << string;
	delete[] string;
	fp_r.close();

	return true;
}

bool Big_integer::WriteToBin(const char* filename)
{

	ofstream fp_ob(filename, std::ios::binary);
	if (fp_ob.fail())
		return false;

	fp_ob.write((char*) this->digs, this->size); 

	fp_ob.close();
	return true;
}

bool Big_integer::ReadFromBin(const char* filename)
{
	ifstream fp_ib(filename, std::ios::binary);
	if (fp_ib.fail())
		return false;

	fp_ib.seekg(0, std::ios::end);
	int File_size = fp_ib.tellg();
	fp_ib.seekg(0, std::ios::beg);

	delete[] this->digs;
	this->digs = new unsigned char[File_size];
	this->size = File_size;
	this->sign = 0;

	fp_ib.read((char*)this->digs, File_size);
	fp_ib.close();

	return true;
}


void Big_integer::Set_size(int newSize)
{	
	if (this->size)
		delete[] this->digs;
	this->size = newSize;
	this->sign = 0;
	this->digs = new unsigned char[this->size]();
}

void Big_integer::RemoveForwardZero()
{
	while ((size - 1)&& digs[size - 1] == 0)
		this->size--;

	if (this->size == 1 && digs[0] == 0)
		this->sign = 0;
}

int Big_integer::cmp(const Big_integer& Y)
{

	int SignFlag = 1;
	if (this->sign == 1)
		SignFlag = -1;

	if (this->sign != Y.sign)
		return SignFlag;

	if (this->size > Y.size)
		return SignFlag;

	if (this->size < Y.size)
		return -SignFlag;

	int i = this->size - 1;

	while (this->digs[i] == Y[i] && i > 0)
	{
		i--;
	}
	return ( (int) this->digs[i] - (int) Y[i]) * SignFlag;
}

void Big_integer::Shift(int s)
{

	unsigned char* newdigs = new unsigned char[this->size + s]();
	for (int i = 0; i < this->size; i++)
	{
		newdigs[i + s] = this->digs[i];
	}

	delete[] this->digs;
	this->digs = newdigs;
	this->size += s;
	this->RemoveForwardZero();
}


Big_integer Big_integer::SummOrSub(const Big_integer& LValue, const Big_integer& RValue) const
{
	Big_integer A = LValue, B = RValue; 
	A.sign = 0;
	B.sign = 0;
	if (A > B)
	{
		A.sign = LValue.sign;
		B.sign = RValue.sign;
	}
	else
	{
		A = RValue;
		B = LValue;
	}

	if (A.sign == B.sign)
	{

		Big_integer res;
		res.Set_size(A.size + 1);

		int cf = 0;

		for (int i = 0; i < A.size; i++)
		{
			int tmp = A[i] + cf;
			if (i < B.size)
				tmp += B[i];

			res[i] = tmp % 256;
			cf = tmp / 256;
		}

		res[A.size] = cf;
		res.sign = A.sign;
		res.RemoveForwardZero();
		return res;
	}
	else
	{
		Big_integer res;
		res.Set_size(A.size);

		int cf = 0;
		for (int i = 0; i < A.size; i++)
		{
			int tmp = A[i] - cf;
			if (i < B.size)
				tmp -= B[i];

			cf = 0;
			if (tmp < 0)
			{
				cf = 1;
				tmp += 256;
			}
			res[i] = tmp;
		}

		res.sign = A.sign;
		res.RemoveForwardZero();
		return res;
	}
}

Big_integer Big_integer::Mul(const Big_integer X, const Big_integer Y) const
{
	Big_integer res;
	res.Set_size(X.size + Y.size);
	int cf = 0;
	for (int i = 0; i < Y.size; i++)
	{
		cf = 0;
		for (int j = 0; j < X.size; j++)
		{
			int tmp = (int) Y[i] * (int) X[j] + (int) cf + (int) res[i + j];
			cf = tmp / 256;
			res[i + j] = tmp % 256;
		}
		res[i + X.size] = cf;
	}

	res.sign = (X.sign != Y.sign);
	res.RemoveForwardZero();
	return res;
}

Big_integer Big_integer::Div(const Big_integer& X, const Big_integer& Y, Big_integer &rem) const
{
	rem = X;
	rem.sign = 0;

	Big_integer divider = Y;
	divider.sign = 0;

	if (divider == Big_integer((int)0))
	{
		throw DIV_BY_ZERO;
	}

	if (rem < divider)
	{
		rem = X;
		return Big_integer((int)0);
	}

	Big_integer res;
	res.Set_size(X.size - Y.size + 1);

	for (int i = X.size - Y.size + 1; i; i--)
	{
		int search_limit_max = 256;
		int search_limit_min = 0;
		int Value = search_limit_max;


		while (search_limit_max - search_limit_min > 1)
		{
			Value = (search_limit_max + search_limit_min) / 2;

			//tmp = Value * divider * 256^i;
			Big_integer tmp = divider * Value;
			tmp.Shift(i - 1);	// умножение на 256^(i - 1)
			
			if (tmp > rem)
				search_limit_max = Value;
			else
				search_limit_min = Value;
		}
		Big_integer tmp = divider * search_limit_min;
		tmp.Shift(i - 1); // умножение на 256 ^ (i - 1)
		rem = rem - tmp;
		res[i - 1] = search_limit_min;
	}

	res.sign = (X.sign != Y.sign);
	rem.sign = (X.sign != Y.sign);
	rem.RemoveForwardZero();
	res.RemoveForwardZero();

	return res;
}


Big_integer Pow(const Big_integer& X, const Big_integer& Y, Big_integer& mod)
{
	if (mod <= (int)0)
		return X ^ Y;
	Big_integer qw=0;
	std::vector <Big_integer> i;
	Big_integer q =Y;
	while(q>0)
	{
		Big_integer t = q % 2;
		i.push_back(t);
		q = q /2;
	}
	std::vector <Big_integer> i_new;
	for(int j=i.size()-1; j>=0; j--)
	{
		i_new.push_back(i[j]);
	}
	for(int j=0; j<i.size(); j++)
		qw = qw*10+i_new[j];
	std:: vector <Big_integer> ostatok;
	ostatok.push_back(X);
	for(int j = 1; j<i_new.size(); j++)
	{
		if(i_new[j]==0)
		{
			ostatok.push_back((ostatok[j-1]*ostatok[j-1]) % mod);
		}
		if(i_new[j]==1)
		{
			ostatok.push_back((ostatok[j-1]*ostatok[j-1]*ostatok[0]) % mod);
		}
	}
	Big_integer res = ostatok[ostatok.size()-1];
	return res;
}

unsigned char & Big_integer::operator[](int i)
{
	if (i < 0)
		return this->digs[this->size + i];
	return this->digs[i];
}

unsigned char Big_integer::operator[](int i) const
{
	if (i < 0)
		return this->digs[this->size + i];
	return this->digs[i];
}


Big_integer& Big_integer::operator=(const Big_integer& RValue)
{
	if (this->size)
		delete[] this->digs;

	this->size = RValue.size;
	this->digs = new unsigned char[size];
	this->sign = RValue.sign;
	memcpy(digs, RValue.digs, size);
	return *this;
}

Big_integer Big_integer::operator-() const
{
	Big_integer res = *this;
	res.sign = !res.sign;
	return res;
}

Big_integer Big_integer::operator^(const Big_integer& RValue) const
{
	Big_integer res = 1;
	Big_integer base = *this;
	for (Big_integer i = RValue; i > (int)0; i = i - 1)
		res = res * base;
	return res;
}

Big_integer Big_integer::operator+(const Big_integer& RValue) const
{
	return SummOrSub(*this, RValue);
}

Big_integer Big_integer::operator-(const Big_integer& RValue) const
{
	return *this + (-RValue);
}

Big_integer Big_integer::operator*(const Big_integer& RValue) const
{
	return Mul(*this, RValue);
}

Big_integer Big_integer::operator/(const Big_integer& RValue) const
{
	Big_integer rem;
	return Div(*this, RValue, rem);
}

Big_integer Big_integer::operator%(const Big_integer& RValue) const
{
	Big_integer rem;
	Div(*this, RValue, rem);
	return rem;
}

bool Big_integer::operator>(const Big_integer& Y)
{
	return this->cmp(Y) > 0;
}

bool Big_integer::operator>=(const Big_integer& Y)
{
	return this->cmp(Y) >= 0;
}

bool Big_integer::operator<(const Big_integer& Y)
{
	return this->cmp(Y) < 0;
}

bool Big_integer::operator<=(const Big_integer& Y)
{
	return this->cmp(Y) <= 0;
}

bool Big_integer::operator==(const Big_integer& Y)
{
	return this->cmp(Y) == 0;
}

bool Big_integer::operator!=(const Big_integer& Y)
{
	return this->cmp(Y) != 0;
}

Big_integer Big_integer::operator++()
{
Big_integer value = *this;
*this = *this + 1;
return value;
}

Big_integer Big_integer::operator++(int)
{
*this = *this + 1;
return *this;
}
Big_integer Big_integer::operator--()
{
Big_integer value = *this;
*this = *this - 1;
return value;
}

Big_integer Big_integer::operator--(int)
{
*this = *this - 1;
return *this;
}