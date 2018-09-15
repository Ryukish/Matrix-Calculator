
/*
1.Use the argumentManager to read and parse the filenames
a.Check for errors
Check if the file has opened

2.Then read in the files and check for errors
a.For reading in matric rows -> vectors

Use while loop and getline to grab lines like (1 5 3 6) ->while(getline(inFile,str)
When reading in, create a new vector (vector<double> temp)
create stringstream so that you can use >> to read the numbers from the string you got from getline,
then you change the string  into numbers (doubles) most likely
stringstream numberHold(str);
double numTemp;

then use >> to put the numbers you grabbed into the vector via Push_back.
while(numberHold >> numTemp)
temp.push_back(numTemp);

Once you have (1 5 3 6) in the vector, you push that into the double vector (a vector in a vector)
vector<vector<double>> first;
first.push_back(temp);

This creates a row inside the double vector
first[0] is the row
first[0][0] is the columns
The push_back store the (1 5 3 6) into the first row, then waits for the next row @first[1]
You can use first.size() for number of Rows and first[0].size() for number of Columns

b.For types of errors possible
matrix size
illegal input characters
empty input files
wrong number  of rows/columns

3.then check that you can mutiply the matrics Then mutiply and output to C
a.how to check
columns x rows
A     *    B
n x m 	 m x p

n x m  = the columns of A must match rows of B to multiply
m x p  = n x P = Dimensions of matrix C

A          B                   C
{1,2,3     {6,3   =  1*6+2*5+3*4 , 1*3+2*2+3*1
4,5,6}     5,2   =  4*6+5*5+6*4 , 4*3+5*2+6*1
4,1}

b.Loop to multiply
int x,y,z;

double sum;

for (x = 0; x < first.size(); x++) {
for (y = 0; y < second[0].size(); y++) {
sim = 0.0;
for (z = 0; z < first[0].size(); z++) {
sum += a[x][z] * b[z][y];
}
outfile << sum<<" ";
}
cout << '\n';
}
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<iomanip>
#include"ArgumentManager.h"



using namespace std;

bool readInA(const char* fileNameA, vector<vector<double>>& first); //Puts the input into vector for first matric
bool readInB(const char* fileNameB, vector<vector<double>>& second); //Puts the input into vector for seccond matric
void denseMultOutput(const char* outFileName, vector<vector<double>>& first, vector<vector<double>>& second); //multiplies and outputs to file

int main(int argc, char* argv[]) {

	if (argc < 2) {
		cout << "Wrong number of arguments";
		return 1;
	}
	//For command line parsing 
	ArgumentManager clparse(argc, argv);
	//Assigning the file names A B C
	string fileNameA = clparse.get("A");
	string fileNameB = clparse.get("B");
	string outFileNameC = clparse.get("C");


	//STL template <class identifier> function_declaration;
	//A vector inside a vector to hold a matric
	vector<vector<double> > first;
	vector<vector<double> > second;


	if (readInA(fileNameA.c_str(), first) && readInB(fileNameB.c_str(), second)) {

		if (first[0].size() != second.size()) {
			ofstream outfile(outFileNameC, ios::binary);
			outfile << "error";
			cout << "ERROR matric sizes are incorrect for multiplying.";
			return -1;
		}
		else

			ofstream outfile(outFileNameC, ios::binary);
		denseMultOutput(outFileNameC.c_str(), first, second);
	}
	else {
		ofstream outfile(outFileNameC, ios::binary);
		outfile << "error";
	}

	return 0;
}

bool readInA(const char* fileNameA, vector<vector<double> >& first) {
	ifstream inFileA(fileNameA, ios::binary);
	string matricTemp;
	double numTemp;
	int matricChecker = 0;
	int l;

	if (inFileA.is_open()) {
		while (getline(inFileA, matricTemp)) {
		
		
			for (l = 0; matricTemp[l] != '\0'; ++l) {
				if (isdigit(matricTemp[l]) == 0) {

					if (matricTemp[l] == '+') {
						if (matricTemp[l + 1] == ' ') {
							cout << "ERROR, case sensitive. A";
							return false;
						}
					}
					else if (matricTemp[l] == '-') {
						if (matricTemp[l + 1] == ' ' || matricTemp[l + 1] == '-') {
							cout << "ERROR, case sensitive. A";
							return false;
						}

					}
					else {
						if (matricTemp[l] != '.') {
							if (matricTemp[l] != '-') {
								if (matricTemp[l] != ' ') {
									if (matricTemp[l] != '+') {
										cout << "ERROR, case sensitive. A";
										return false;
									}
								}
							}
						}
					}
				}
			}
			vector<double> temp; // used to make rows in the double vector First
			stringstream numberHold(matricTemp); //stringstream is used here to allow us to use >> on SS, which allows us to read the number in

			while (numberHold >> numTemp)
				temp.push_back(numTemp);
			if (!temp.empty()) {
				first.push_back(temp);
				if (first[0].size() != first[matricChecker].size()) {
					cout << "ERROR, matric size is inorrect. A";
					return false;
				}
				++matricChecker;
			}
		}
		inFileA.close();
		return true;
	}
	else
		return false;
}

bool readInB(const char* fileNameB, vector<vector<double>>& second) {
	ifstream inFileB(fileNameB, ios::binary);
	string matricTemp;
	double numTemp;
	int matricChecker = 0;
	int l;

	if (inFileB.is_open()) {
		while (getline(inFileB, matricTemp)) {
			
			for (l = 0; matricTemp[l] != '\0'; ++l) {
				if (isdigit(matricTemp[l]) == 0) {


					if (matricTemp[l] == '+') {
						if (matricTemp[l + 1] == ' ') {
							cout << "ERROR, case sensitive. B";
							return false;

						}
					}
					else if (matricTemp[l] == '-') {
						if (matricTemp[l + 1] == ' ' || matricTemp[l + 1] == '-') {
							cout << "ERROR, case sensitive. B";
							return false;
						}

					}
					else {
						if (matricTemp[l] != '.') {
							if (matricTemp[l] != '-') {
								if (matricTemp[l] != ' ') {
									if (matricTemp[l] != '+') {
										cout << "ERROR, case sensitive. B";
										return false;
									}
								}
							}
						}
					}
				}
			}
			vector<double> temp; // used to make rows in the double vector First
			stringstream numberHold(matricTemp); //stringstream is used here to allow us to use >> on SS, which allows us to read the number in

			while (numberHold >> numTemp)
				temp.push_back(numTemp);
			if (!temp.empty()) {
				second.push_back(temp);
				if (second[0].size() != second[matricChecker].size()) {
					cout << "ERROR, matric size is inorrect. B";
					return false;
				}
				++matricChecker;
			}
		}
		inFileB.close();
		return true;
	}
	else
		return false;
}


void denseMultOutput(const char* outFileName, vector<vector<double>>& first, vector<vector<double>>& second) {
	ofstream outfile(outFileName, ios::binary);
	vector<vector<double>>output;
	unsigned int x;
	unsigned int y;
	unsigned int z;
	double sum;
	if (outfile.is_open()) {
		outfile.precision(2);
		outfile << fixed;
		for (x = 0; x < first.size(); ++x) {
			for (y = 0; y < second[0].size(); ++y) {
				sum = 0.0;
				for (z = 0; z < first[0].size(); ++z) {
					sum += first[x][z] * second[z][y];
				}
				outfile << sum << " ";
			}
			outfile << endl;
		}
		outfile.close();
	}
	else

		cout << "ERROR with opening the output file.";
}













