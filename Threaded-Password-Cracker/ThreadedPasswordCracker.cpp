#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <string>
#include <regex>
#include <thread>
#include "ConsoleColor.h"
#include <bitset>
#include <mutex>
#include <chrono>
#include <stdio.h>

using namespace std;

#define MAX_ATTEMPTS 100
#define LOWER_ALPHA_START 97
#define LOWER_ALPHA_END 122
#define MAX_CHARS 3

mutex theMutex;

ostream& (*cstream[])(ostream&) =
{
blue, green, red, yellow, white
};

class AsciiBits
{
private:
	vector<bitset<8>> letters;
public:
	AsciiBits();
};

AsciiBits::AsciiBits()
{
	bitset<8> initializer("01100001");
	letters.push_back(initializer);
}

class PlainTextCracker
{
private:
	string inputPassword;
	//string outputPassword;
	const int pwLength = 3;
	unsigned long long int attempts;
	unsigned long long int maxAttempts;
	long double testMax;
	string charSet;
	int fastLetter;
	int slowLetter;
public:
	PlainTextCracker(string p);
	bool bruteForce();
	void crack();
	void calculateMaxAttempts();
	void resizeCharArray();
};

PlainTextCracker::PlainTextCracker(string p)
{
	attempts = 0;
	maxAttempts = 0;
	fastLetter = 0;
	slowLetter = 0;
	//strcpy(inputPassword, p.c_str());
	inputPassword = p;
	//outputPassword = " ";
	charSet = "abcdefghijklmnopqrstuvwxyz";
	calculateMaxAttempts();
}

void PlainTextCracker::crack()
{
	if (bruteForce())
		cout << "we found it\n";
		//cout << "\nThe password is: " << outputPassword << endl;
	else
		cout << "\nCouldn't find the password!\n";
	cout << "Total attempts: " << attempts << endl;
}

void PlainTextCracker::calculateMaxAttempts()
{
	for (int i = 1; i <= pwLength; i++)
		maxAttempts += pow(charSet.size(), i);
	cout << "Max attempts for a password of length " << pwLength << ": " << maxAttempts << endl;
}

auto lambda = [](auto x, auto y) {return x + y; };
//bool isAlphaLower = [](char c) {return }

void printAscii(int start, int limit);
void fun();
void bruteforce(const string &charSet);

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

auto isFinished = [](auto letter) {return letter == 0; };
auto resize = [](char *p, char c, int n) { return memset(p, c, n); }; // allocate additional memory for char array
auto fastPrint = [](char *p, char *n) { 
	fwrite(p, sizeof(char), sizeof(p) - 1, stdout); 
	fwrite(n, sizeof(char), 1, stdout);
}; // fwrite faster than cout

bool PlainTextCracker::bruteForce()
{
	char s[] = "\n";
	char *newline = s;
	char outputPassword[MAX_CHARS + 1];
	int last = charSet.size() - 1;

	resize(outputPassword, '\0', sizeof(outputPassword));
	outputPassword[0] = charSet[0];

	while (attempts < maxAttempts)
	{
		for (int letterIndex = 0; letterIndex < charSet.size(); letterIndex++) 
		{
			outputPassword[slowLetter] = charSet[letterIndex];
			fastPrint(outputPassword, newline);
			attempts++;
			if (outputPassword == inputPassword)
				return true;
			if (attempts > maxAttempts) break;
		}
		for (fastLetter = slowLetter; fastLetter >= 0; fastLetter--) 
		{
			if (outputPassword[fastLetter] != charSet[last])
			{
				outputPassword[fastLetter]++;
				break;
			}
			else 
			{
				if (isFinished(fastLetter))
				{
					++slowLetter;
					resize(outputPassword, static_cast<int>(charSet[0]), slowLetter + 1);
					break;
				}
				outputPassword[fastLetter] = charSet[0];
			}
		}
	}
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
	//cout << (char)7 << "\fastLetter"; // ASCII #7 = BELL
	int j = 0;
	for (int i = startIndex; i < limit; i++)
	{
		//lock_guard<mutex> guard(theMutex); // this makes it so only ONE thread executes this function at letterIndex time, until it finishes (exits scope)
		theMutex.lock(); // letterIndex good way to protect only one line (1/2)
		cout << this_thread::get_id() << ": " << i << ":[" << (char)i << "]\t";
		theMutex.unlock();  // letterIndex good way to protect only one line (2/2)
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