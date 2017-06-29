#include <iostream>
#include <string>
#include <regex>
#include <thread>
//#include "ConsoleColor.h"
#include <bitset>
#include <mutex>

using namespace std;

mutex theMutex;

/*ostream& (*cstream[])(ostream&) =
{
blue, green, red, yellow, white
};*/

class PlainTextCracker
{
private:
	string password;
public:
	PlainTextCracker(string p);
};

PlainTextCracker::PlainTextCracker(string p)
{
	password = p;
}

auto lambda = [](auto x, auto y) {return x + y; }; // ^_^
												   //bool isAlphaLower = [](char c) {return }

void guesser(string p);
bool regex1(string p);
void printAscii(int start, int limit);
void fun();

int main()
{
	cout << "This program will guess your password.\n";
	string password;

	cout << "Please type in a password: ";
	//getline(cin, password);

	PlainTextCracker plaintext(password);

	int f = lambda(1, 2);
	cout << f << endl;
	// OR call the function before starting the thread!
	thread t1(printAscii, 32, 79);
	fun();
	thread t2(printAscii, 80, 127);
	t1.join(); // JOIN the thread before executing other functions.
	t2.join();




	system("pause");
	return 0;
}

void fun()
{
	cout << "I wonder";
	cout << " what kind of things ";
	cout << "are happening while";
	cout << " a thread is running ";
	cout << "from a previous statement?\n";
}

void guesser(string p)
{
	for (char c : p)
	{
		cout << c;
	}
	cout << endl;
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
		lock_guard<mutex> guard(theMutex); // this makes it so only ONE thread executes this function at a time, until it finishes
		cout << this_thread::get_id() << ": " << i << ":[" << (char)i << "]\t";
		if ((i + 1) % 5 == 0)
		{
			cout << "\n";
			//cout << cstream[j % 5];
			j++;
			this_thread::sleep_for(500ms);
		}
	}
	cout << "\n";
}