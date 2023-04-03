/*//---------------------------------------------------------------------------

	Author: Nicholas Barsi-Rhyne
    CruzID: nbarsirh
    Assignment: pa6

Arithmetic.cpp
	This program takes two arguments <infile> <outfile> and does some large number arthmetic
	printing the results to a file. To run use ./Arthimetic <infile> <outfile>. The infile
	must be correctly formatted. Line 1 should be a number with either a +, -, or neither
	at the front. Line 2 must be blank. Line 3 must contain the second number with either
	+, -, or neither. Outfile will have the following equations seperated by a newline.
	𝐴, 𝐵, 𝐴 + 𝐵, 𝐴 − 𝐵, 𝐴 − 𝐴, 3𝐴 − 2𝐵, 𝐴𝐵, 𝐴^2, 𝐵^2, 9𝐴^4 + 16𝐵^5.

*///-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(int argc, char** argv) {
	ifstream inFile;
	ofstream outFile;
	
	BigInteger B;

	inFile.open(argv[1]);
	outFile.open(argv[2]);

	if (inFile && outFile) {
		string line;
		getline(inFile, line);
		BigInteger A(line);
		getline(inFile, line);
		getline(inFile, line);
		BigInteger B(line);

		outFile << A << endl;

		outFile << "\n";
		outFile << B << endl;

		outFile << "\n";
		BigInteger C = A + B;
		outFile << C << endl;

		outFile << "\n";
		C = A - B;
		outFile << C << endl;

		outFile << "\n";
		C = A - A;
		outFile << C << endl;

		outFile << "\n";
		BigInteger D("3");
		BigInteger E("2");
		C = D*A - E*B; 
		outFile << C << endl;

		outFile << "\n";
		C = A * B;
		outFile << C << endl;

		outFile << "\n";
		C = A * A;
		outFile << C << endl;

		outFile << "\n";
		C = B * B;
		outFile << C << endl;

		outFile << "\n";
		D *= D;
		BigInteger F("16");
		C = A * A * A * A * D + B * B * B * B * B * F;
		outFile << C << endl;
		outFile << "\n";
	}
	return 0;
}
