#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <string>
#include <regex>
#include <thread>
#include "ConsoleColor.h"
#include <bitset>
#include <mutex>
#include <chrono>
#include <ctime>
#include <stdio.h>
#include <functional>
#include <cctype>
#include <algorithm>

using namespace std;

#define LOWER_ALPHA_START 97
#define LOWER_ALPHA_END 122
#define MAX_CHARS 5
#define LOWER_ALPHA "abcdefghijklmnopqrstuvwxyz"

mutex theMutex;

ostream& (*cstream[])(ostream&) =
{
blue, green, red, yellow, white
};

auto isFinished = [](auto letter) {return letter == 0; };
auto resize = [](char *p, char c, int n) { return memset(p, c, n); }; // allocate additional memory for char array
auto fastPrint = [](char *p, char *n) {
	fwrite(p, sizeof(char), sizeof(p) - 1, stdout);
	fwrite(n, sizeof(char), 1, stdout);
}; // fwrite faster than cout
auto isQuit = [](string s) { return s == "Q" || s == "q"; };

class PlainTextCracker
{
private:
	string outputPassword;
	string inputPassword;
	unsigned long long int attempts;
	unsigned long long int maxAttempts;
	long double testMax;
	string charSet;
	int fastLetter;
	int slowLetter;
public:
	PlainTextCracker();
	bool bruteForce();
	void crack();
	void calculateMaxAttempts();
	void setPassword(string p);
	void reset();
};

PlainTextCracker::PlainTextCracker()
{
	attempts = 0;
	maxAttempts = 0;
	fastLetter = 0;
	slowLetter = 0;
	inputPassword = "";
	charSet = "abcdefghijklmnopqrstuvwxyz";
}

void PlainTextCracker::setPassword(string p)
{
	inputPassword = p;
	
}

void PlainTextCracker::crack()
{
	
	if (bruteForce())
		cout << green << "The password is: " << outputPassword << white;
	else
		cout << red << "\nCouldn't find the password!" << white;
	cout << "\nTotal attempts: " << yellow << attempts << white << endl;
}

void PlainTextCracker::calculateMaxAttempts()
{
	maxAttempts = 0;
	for (int i = 1; i <= MAX_CHARS; i++)
		maxAttempts += pow(charSet.size(), i);
	cout << "Max attempts for a password of length " << MAX_CHARS << ": " << maxAttempts << "\n";
}

bool PlainTextCracker::bruteForce()
{
	char s[] = "\n";
	char *newline = s;
	char guess[MAX_CHARS + 1];
	int last = charSet.size() - 1;

	resize(guess, '\0', sizeof(guess));
	guess[0] = charSet[0];

	while (attempts < maxAttempts)
	{
		for (int letterIndex = 0; letterIndex < charSet.size(); letterIndex++)
		{
			guess[slowLetter] = charSet[letterIndex];
			//fastPrint(guess, newline);
			attempts++;
			if (guess == inputPassword)
			{
				outputPassword = guess;
				return true;
			}

			if (attempts > maxAttempts) break;
		}
		for (fastLetter = slowLetter; fastLetter >= 0; fastLetter--)
		{
			if (guess[fastLetter] != charSet[last])
			{
				guess[fastLetter]++;
				break;
			}
			else
			{
				if (isFinished(fastLetter))
				{
					++slowLetter;
					resize(guess, static_cast<int>(charSet[0]), slowLetter + 1);
					break;
				}
				guess[fastLetter] = charSet[0];
			}
		}
	}
	return false;
}

void PlainTextCracker::reset()
{
	inputPassword.clear();
	outputPassword.clear();
	attempts = 0;
	slowLetter = 0;
}

class Timer
{
private:
	chrono::time_point<chrono::system_clock> t1, t2;
	chrono::duration<double> duration;
	vector <chrono::duration<double>> runtimeData;
	time_t end;
public:
	Timer();
	void start();
	void stop();
	void calculate();
	void print();
	void reset();
	void batchFinish();
};

Timer::Timer()
{
	
}

void Timer::start()
{
	cout << blue << "Beginning the timer...\n" << white;
	t1 = chrono::system_clock::now();
}

void Timer::stop()
{
	t2 = chrono::system_clock::now();
	cout << blue << "Timer has stopped.\n" << white;
}

void Timer::calculate()
{
	duration = t2 - t1;
	end = chrono::system_clock::to_time_t(t2);
	runtimeData.push_back(chrono::duration<double>(duration));
}

void Timer::print()
{
	cout << "Finished at: " << blue << std::ctime(&end) << white;
	cout << "Runtime: " << blue << chrono::duration <double, milli>(duration).count() << " ms\n" << white;
}

void Timer::reset()
{
	duration.zero();
}

void Timer::batchFinish()
{
	stop();
	calculate();
	print();
	reset();
}

void printAscii(int start, int limit);
void fun();

class Password
{
private:
	string password;
	string charSet;
public:
	Password();
	void setPassword(string p);
	string promptUser();
	void trim(string s);
	string getPassword();
	void setType(string set);
	function<bool(string)> isQuit;
	bool isValid(string s);
};

Password::Password()
{
	password = "z";
	charSet = "";
	this->isQuit = [](string s) { return s == "Q" || s == "q"; };
}

bool Password::isValid(string s)
{
	if (all_of(s.begin(), s.end(), [](char c) { return isalpha(c); }))
		return true;
	cout << red << "This password contains invalid characters for the selected set!\n";
	cout << "Use only the following characters: " << charSet << "\n" << white;
	return false;
}

void Password::setPassword(string p)
{
	password = p;
}

void Password::setType(string set)
{
	charSet = set;
}

string Password::promptUser()
{
	do
	{
		password.clear();
		cout << "\nPlease type in a password: ";
		getline(cin, password);
		trim(password);
	} while (!isValid(password));
	return password;
}

void Password::trim(string text)
{
	string whitespace = "\040\t";
	auto front = text.find_first_not_of(whitespace);
	auto back = text.find_last_not_of(whitespace);
	auto length = back - front + 1;
	text.substr(front, length);
}

string Password::getPassword()
{
	return password;
}



int main()
{
	cout << "This program will guess your password.\n";
	cout << "You may only use a-z, and 1-5 characters.\n";
	Password password;
	Timer timer;
	PlainTextCracker plaintext;
	plaintext.calculateMaxAttempts();
	string input = " ";
	password.setType(LOWER_ALPHA);

	while (!isQuit(input))
	{
		input.clear();
		input = password.promptUser();
		plaintext.setPassword(password.getPassword());
		timer.start();
		plaintext.crack();
		timer.batchFinish();
		plaintext.reset();
	}

	// OR call the function before starting the thread!
	//thread t1(printAscii, 32, 79);
	//fun();
	//thread t2(printAscii, 80, 127);
	//t1.join(); // JOIN the thread before executing other functions.
	//t2.join();

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