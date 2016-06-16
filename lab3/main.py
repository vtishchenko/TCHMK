#!/usr/bin/python3.4m

import Big_integer
import sys
import argparse
 
def getFromFiles (fileA, fileB, fileMod, binary):
	A = Big_integer.Big_integer()
	B = Big_integer.Big_integer()
	modulus = Big_integer.Big_integer()
	if (binary):
		if not A.ReadFromBin(fileA):
			print("Can't get number from:", fileA) 
			return False, A, B, modulus
		if not B.ReadFromBin(fileB):
			print("Can't get number from:", fileB)
			return False, A, B, modulus
		if fileMod:
			if not modulus.ReadFromBin(fileMod):
				print("Can't get number from:", fileMod)
				return False, A, B, modulus
	else:
		if not A.ReadFromTextFile(fileA):
			print("Can't get number from:", fileA)
			return False, A, B, modulus
		if not B.ReadFromTextFile(fileB):
			print("Can't get number from:", fileB)
			return False, A, B, modulus
		if fileMod:
			if not modulus.ReadFromTextFile(fileMod):
				print("Can't get number from:", fileMod)
				return False, A, B, modulus
	return True, A, B, modulus
	
def process(A, B, modulus, operation):
	zero = Big_integer.Big_integer("0")
	res = zero
	
	if (modulus < zero):
		print("Negative modulus!")
		return False, res
		
	if operation == '^':
		res = Big_integer.Pow(A, B, modulus)
		return True, res
			
	if (modulus > zero):
		A %= modulus
		B %= modulus
	
	if operation == '+':
		res = A + B

	elif operation == '-':
		res = A - B

	elif operation == '*':
		res = A * B

	elif operation == '/':
		if B == zero:
			print("Division by zero")
			return False, res
		res = A / B

	elif operation == '%':
		if (B == zero):
			print("Division by zero")
			return False, res
		res = A % B
	
	if (modulus > zero):
			res %= modulus
			while (res < zero):
				res += modulus
				
	return True, res
			
def saveRes(fileRes, binary, res):
	if binary:
		if not res.WriteToBin(fileRes):
			print("Can't save result to ", fileRes)
			return False
	else:
		if not res.WriteToTextFile(fileRes):
			print("Can't save result to ", fileRes)
			return False
	return True

def main():
	parser = argparse.ArgumentParser(prog = "Big_integer")
	parser.add_argument('A_filename', help = "filename of file with 1-st big integer")
	parser.add_argument('operation', choices=['+', '-', '*', '/', '%', '^'], help = "operations")
	parser.add_argument('B_filename', help = "filename of file with 2-nd big integer")
	parser.add_argument('result_filename', help = "filename of result file")
	parser.add_argument('-b', action='store_const', const=True,  default=False, help = "perform binary files")
	parser.add_argument('mod_filename', help = "filename of file with modulus", nargs='?')
	arguments = parser.parse_args()
	isRead, A, B, modulus = getFromFiles (arguments.A_filename, arguments.B_filename, arguments.mod_filename, arguments.b)
	if not isRead:
		sys.exit(-1)
	
	isProcess, res = process(A, B, modulus, arguments.operation)
	if not isProcess:
		sys.exit(-1)

	isWrite = saveRes(arguments.result_filename, arguments.b, res)
	if not isWrite:
		sys.exit(-1)

if __name__ == '__main__':
    main()
