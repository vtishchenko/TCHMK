#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Big_integer.h"
using std::cout;

using namespace std;
void printmenu()
{
	cout << "Long_ariph <A filelame> <operation> <B filelame> <result filename> [-b] [<mod filename>]" << endl << endl;
	cout << "Ariph operations: + , -, * , / ,^, %"<<endl;
	cout << "mod and binary key isn't required "<<endl;
}

bool procoperation(Big_integer A, Big_integer B, Big_integer mod, char operation, Big_integer& res)
{
	if (mod < (int)0)
	{
		cout << "Negative mod!" << endl;
		return false;
	}

	if (operation == '^')
	{
		res = Pow(A, B, mod);
		return true;
	}

	if (mod > (int)0)
	{
		A = A % mod;
		B = B % mod;
	}

	switch (operation)
	{
	case '+':
		res = A + B;
		break;

	case '-':
		res = A - B;
		break;

	case '*':
		res = A * B;
		break;

	case '/':
		try
		{
			res = A / B;
		}
		catch (int err)
		{
			cout << "Division by zero" << endl;
			return false;
		}
		break;

	case '%':
		try
		{
			res = A % B;
		}
		catch (int err)
		{
			cout << "Division by zero" << endl;
			return false;
		}
		break;

	default:
		cout << "Wrong operation." << endl;
		printmenu();
		return false;
	}

	if (mod > (int)0)
	{
		res = res % mod;
		while (res < (int)0)
			res = res + mod;
	}

	return true;
}

int main(int argc, char* argv[])
{
	if (argc < 5)
	{
		cout << "Don't enough arguments" << endl;
		printmenu();
		return -1;
	}

	/*if (argc > 7)
	{
		cout << "So many arguments" << endl;
		printmenu();
		return -2;
	}*/

	if (strlen(argv[2]) > 1)
	{
		cout << "unknown operation" << endl;
		printmenu();
		return -3;
	}

	char* fileA = argv[1];
	char operation = argv[2][0];
	char* fileB = argv[3];
	char* fileRes = argv[4];
	bool binary = false;
	char* fileMod = NULL;

	if (argc == 6)
	{
		if (!strcmp(argv[5], "-b"))
			binary = true;
		else
			fileMod = argv[5];
	}

	if (argc == 7)
	{
		binary = true;
		fileMod = argv[6];
	}

	Big_integer A, B, mod = (int)0;

	if (binary)
	{
		A.ReadFromBin(fileA);
		B.ReadFromBin(fileB);
		if (fileMod)
			mod.ReadFromBin(fileMod);
	}
	else
	{
		A.ReadFromTextFile(fileA);
		if(A.ReadFromTextFile(fileA)==false)
		{
			printf("\nFirst input file contains not only numbers\n");
		}
		B.ReadFromTextFile(fileB);
		if(B.ReadFromTextFile(fileB)==false)
		{
			printf("\nSecond file contains not only numbers\n");
		}
		if(A.ReadFromTextFile(fileA)==false || B.ReadFromTextFile(fileB)==false)
			return 0;
		if (fileMod)
			mod.ReadFromTextFile(fileMod);
	}

	Big_integer res;
	if (!procoperation(A, B, mod, operation, res))
		return -1;

	if (binary)
		res.WriteToBin(fileRes);
	else
		res.WriteToTextFile(fileRes);

	return 0;
}
