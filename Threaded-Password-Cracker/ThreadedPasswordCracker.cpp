#include <iostream>
#include <string>
#include <regex>
#include <thread>
#include "ConsoleColor.h"
#include <bitset>
#include <mutex>
#include <chrono>

using namespace std;

#define MAX_ATTEMPTS 100

mutex theMutex;

ostream& (*cstream[])(ostream&) =
{
blue, green, red, yellow, white
};

class PlainTextCracker
{
private:
	string inputPassword;
	string outputPassword;
	int pwLength;
	int iterations;

public:
	PlainTextCracker(string p);
	bool bruteForce();
	void crack();
};

PlainTextCracker::PlainTextCracker(string p)
{
	iterations = 0;
	inputPassword = p;
	outputPassword = "";
	pwLength = 2;
}

void PlainTextCracker::crack()
{
	if (bruteForce())
		cout << "\nThe password is: " << outputPassword << endl;
	else
		cout << "\nCouldn't find the password!\n";
	cout << "Total attempts: " << iterations << endl;
}

auto lambda = [](auto x, auto y) {return x + y; };
//bool isAlphaLower = [](char c) {return }

void guesser(string p);
void printAscii(int start, int limit);
void fun();

int main()
{
	cout << "This program will guess your password.\n";
	string password;

	cout << "Please type in a password: ";
	getline(cin, password);

	PlainTextCracker plaintext(password);
	plaintext.crack();
	

	//int f = lambda(1, 2);
	//cout << f << endl;
	// OR call the function before starting the thread!
	//thread t1(printAscii, 32, 79);
	//fun();
	//thread t2(printAscii, 80, 127);
	//t1.join(); // JOIN the thread before executing other functions.
	//t2.join();




	system("pause");
	return 0;
}

bool PlainTextCracker::bruteForce()
{
	string temp = "";
	string assist = "";
	int i = 1, n;
	outputPassword.resize(2);

	//while (iterations < MAX_ATTEMPTS)
	//{
	//	for (int c = 97; c < 123; c++)
	//	{
	//		outputPassword[i - 1] = static_cast<char>(c);
	//		cout << outputPassword << endl;
	//		if (iterations++ >= MAX_ATTEMPTS) break;
	//	}
	//	for (n = i; n >= 0; n--)
	//	{
	//		for (int j = 97; j < 123; j++)
	//			outputPassword[n] = static_cast<char>(j);
	//		if (n == 0)
	//		{
	//			++i;
	//		}
	//		outputPassword.resize(i + 1);
	//		outputPassword[n] = static_cast<char>(97);
	//	}
	//}


	//for (int i = 0; i < pwLength; i++)
	//{
	//	for (int c = 97; c < 123; c++) // 32 - 127 = printable ascii. 97-123 = a-z
	//	{
	//		cout << static_cast<char>(c);
	//		outputPassword[i] = static_cast<char>(c);
	//		assist = + static_cast<char>(c);
	//		cout << temp << endl;
	//		iterations++;
	//		if (outputPassword == inputPassword)
	//			return true;
	//	}
	//	assist = 
	//}
	return false;
}



void fun()
{
	cout << "I wonder";
	cout << " what kind of things ";
	cout << "are happening while";
	cout << " a thread is running ";
	cout << "from a previous statement?\n";
}

bool isAlphaUpper(string p)
{
	return true;
}

bool isDigit(string p)
{
	return true;
}

bool isSpecialChar(string p)
{
	return true;
}

void printAscii(int startIndex, int limit)
{
	//cout << (char)7 << "\n"; // ASCII #7 = BELL
	int j = 0;
	for (int i = startIndex; i < limit; i++)
	{
		//lock_guard<mutex> guard(theMutex); // this makes it so only ONE thread executes this function at a time, until it finishes (exits scope)
		theMutex.lock(); // a good way to protect only one line (1/2)
		cout << this_thread::get_id() << ": " << i << ":[" << (char)i << "]\t";
		theMutex.unlock();  // a good way to protect only one line (2/2)
		if ((i + 1) % 5 == 0)
		{
			cout << "\n";
			cout << cstream[j % 5];
			j++;
			this_thread::sleep_for(500ms);
		}
	}
	cout << "\n";
}