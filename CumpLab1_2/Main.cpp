#include <iostream>
#include <cmath>
using namespace std;
bool enretedNumber(long double &number) {
	cout << "Enter your number: ";
	cin >> number;
	if (sizeof(number)*8 == 32 && (int)number != number) {
		cout << "Error, your number is not correct. ";
		cout << endl;
		return false;
	}
	else {
		return true;
	}
}
template<class T>
void ToBinary(T number) {
	for (int i = sizeof(number) * 8 -1; i >= 0; --i)
	{
		cout << ((*(long long int*)(&number) >> i) & 1);
	}
	cout << endl;
}
void ShiftLeft(int *binary, int size) {
	int tmp = binary[0];
	for (int i = 0; i < size-1; i++) {
		binary[i] = binary[i + 1];
	}
	binary[size - 1] = tmp;
}
void ShiftRight(int* binary, int size) {
	int tmp = binary[size-1];
	for (int i = size - 2; i >=0; i--) {
		binary[i+1] = binary[i];
	}
	binary[0] = tmp;
}
template<class T>
void ShiftFunc(T number) {
	char direction;
	int lowestDigit;
	int numDigits;
	int k;
	int rank;
	int tmp;
	int mantissa = sizeof(T) * 8 - 1;
	cin.clear();
	cout << "Select the direction to shift (</>): ";
	cin >> direction;
	cout << "Enter the lowest digit: ";
	cin >> lowestDigit;
	cin.clear();
	cout << "Enter the number of digits: ";
	cin >> numDigits;
	cin.clear();
	int *binary = new int[numDigits];
	cout << "How many digits is the shift: ";
	cin >> k;
	cin.clear();
	switch (direction)
	{
	case '<':
		// Get massive to shift
		for (int i = lowestDigit + (numDigits-1),j = 0; i >= lowestDigit ; --i,j++)
		{
			binary[j]=((*(long long int*)(&number) >> i) & 1);
		}
		// Shift
		for (int i = 0; i < k; i++) {
			ShiftLeft(binary,numDigits);
		}
		// Include new value after shift in number
		for (int i = 0,j = numDigits-1; i < numDigits;j--, i++) {
			rank = lowestDigit+i;
			unsigned long long int integerNumber = *(unsigned long long int*)(&number);
			if (binary[j] % 2 == 1)
			{
				unsigned long long int mask = (unsigned long long int)1 << rank;
				integerNumber |= mask;
				number = *(T*)(&integerNumber);
			}
			else
			{
				unsigned long long int mask = 0;
				for (int i = 0; i < sizeof(T) * 8; i++) {
					if (i != rank) mask |= ((unsigned long long int)1 << i);
				}
				integerNumber &= mask;
				number = *(T*)(&integerNumber);
			}
		}
		ToBinary(number);
		cout << number;
		cout << endl;
		break;
	case '>':
		// Get massive to shift
		for (int i = lowestDigit + (numDigits - 1), j = 0; i >= lowestDigit; --i, j++)
		{
			binary[j] = ((*(long long int*)(&number) >> i) & 1);
		}
		// Shift
		for (int i = 0; i < k; i++) {
			ShiftRight(binary, numDigits);
		}
		// Include new value after shift in number
		for (int i = 0, j = numDigits - 1; i < numDigits; j--, i++) {
			rank = lowestDigit + i;
			unsigned long long int integerNumber = *(unsigned long long int*)(&number);
			if (binary[j] % 2 == 1)
			{
				unsigned long long int mask = (unsigned long long int)1 << rank;
				integerNumber |= mask;
				number = *(T*)(&integerNumber);
			}
			else
			{
				unsigned long long int mask = 0;
				for (int i = 0; i < sizeof(T) * 8; i++) {
					if (i != rank) mask |= ((unsigned long long int)1 << i);
				}
				integerNumber &= mask;
				number = *(T*)(&integerNumber);
			}
		}
		ToBinary(number);
		cout << number;
		cout << endl;
		break;
	default:
		cout << "Error, your choose is not correct." << endl;
		break;
	}
	delete[] binary;
}
int main() {
	bool mainMenu = true;
	char choosedDataType;
	
	long double number;

	while (mainMenu) {
		cout << "Menu:\n1.unsigned int\n2.long double\nSelect your data type: ";
		cin >> choosedDataType;
		cin.clear();
		switch (choosedDataType)
		{
		case '1': 
			if (!enretedNumber(number)) {
				break;
			}
			ToBinary((int)number);
			ShiftFunc((int)number);
			break;
		case '2':
			if (!enretedNumber(number)) {
				break;
			}
			ToBinary(number);
			ShiftFunc(number);
			break;
		default:
			cout << "Error, your choose is not correct.";
			break;
		}


	}

	return 0;
}