#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <string>
#include <regex>
#include "ConsoleColor.h"
#include <bitset>
#include <chrono>
#include <ctime>
#include <stdio.h>
#include <functional>
#include <cctype>
#include <algorithm>
#include <numeric>
#include <future>
#include <atomic>

using namespace std;

#define LOWER_ALPHA_START 97
#define LOWER_ALPHA_END 122
#define MAX_CHARS 5
#define LOWER_ALPHA "abcdefghijklmnopqrstuvwxyz"
#define DUMMY_TRAILER "\177"

typedef chrono::duration<double> Runtime;
typedef chrono::duration <double, milli> PrintableRuntime;

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
	atomic<bool> found;
	future<string> answer;
	vector <string> pwset;
	vector<unsigned long long int> attemptset;
public:
	PlainTextCracker();
	string bruteForce();
	void crack();
	void calculateMaxAttempts();
	void setPassword(string p);
	void reset();
	void setType(string s);
	vector<unsigned long long int> getAttempts();
	vector<string> getPwset();
};

PlainTextCracker::PlainTextCracker()
{
	attempts = 0;
	maxAttempts = 0;
	fastLetter = 0;
	slowLetter = 0;
	inputPassword = "";
	charSet = "";
	found = false;
}

void PlainTextCracker::setPassword(string p)
{
	inputPassword = p;
}

void PlainTextCracker::setType(string set)
{
	charSet = set;
}

void PlainTextCracker::crack()
{
	answer = async(launch::deferred, &PlainTextCracker::bruteForce, this);
	string result = answer.get();
	if (result != DUMMY_TRAILER)
		cout << green << "The password is: " << result << white;
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

string PlainTextCracker::bruteForce()
{
	char s[] = "\n";
	char *newline = s;
	
	int last = charSet.size() - 1;

	cout << "charSet: " << charSet << endl;
	char guess[MAX_CHARS + 1];
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
				pwset.push_back(outputPassword);
				attemptset.push_back(attempts);
				found = true;
				return outputPassword;
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
	return DUMMY_TRAILER;
}

void PlainTextCracker::reset()
{
	inputPassword.clear();
	outputPassword.clear();
	attempts = 0;
	slowLetter = 0;
	found = false;
}

vector<unsigned long long int> PlainTextCracker::getAttempts()
{
	return attemptset;
}

vector<string> PlainTextCracker::getPwset()
{
	return pwset;
}

class Timer
{
private:
	chrono::time_point<chrono::system_clock> t1, t2;
	Runtime duration;
	vector <Runtime> runtimeData;
	time_t end;
public:
	void start();
	void stop();
	void calculate();
	void print();
	void reset();
	void batchFinish();
	vector<Runtime> getRuntimeData();
};

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
	cout << "Runtime: " << blue << PrintableRuntime(duration).count() << " ms\n" << white;
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

vector<Runtime> Timer::getRuntimeData()
{
	return runtimeData;
}

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
	function<bool(char)> isInSet;
};

Password::Password()
{
	password = "z";
	charSet = "";
	this->isQuit = [](string s) { return s == "Q" || s == "q"; };
	this->isInSet = [&](char c) 
	{ 
		for (auto i : charSet) if (c == i) 
			return true; 
		return false;
	};
}

bool Password::isValid(string s)
{
	if (!s.empty() && s.size() <= MAX_CHARS)
		if (all_of(s.begin(), s.end(), [&](char c) { return isInSet(c); }))
			return true;
	cout << red << "This password is invalid for the selected set!\n";
	cout << "Use up to " << MAX_CHARS << " of the following characters: " << charSet << "\n" << white;
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
		if (isQuit(password))
			return password;
		trim(password);
	} while (!isValid(password));
	return password;
}

void Password::trim(string text)
{
	if (text.empty())
		return;
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

class Statistics
{
private:
	vector<Runtime> runtimes;
	vector<unsigned long long int> attempts;
	vector<string> passwords;
	Runtime avg;
	Runtime min;
	Runtime max;
	double avg_len;
public:
	Statistics();
	void averageRuntime();
	void averageLength();
	void summary();
	void calculate();
	void setRuntimes(vector<Runtime> r);
	void setAttempts(vector<unsigned long long int> a);
	void setPasswords(vector<string> p);
};

Statistics::Statistics()
{
	avg.zero();
	min.zero();
	max.zero();
}

void Statistics::setRuntimes(vector<Runtime> r)
{
	runtimes = r;
}

void Statistics::setAttempts(vector<unsigned long long int> a)
{
	attempts = a;
}

void Statistics::setPasswords(vector<string> p)
{
	passwords = p;
}

void Statistics::calculate()
{
	min = *min_element(runtimes.begin(), runtimes.end());
	max = *max_element(runtimes.begin(), runtimes.end());
	averageLength();
	averageRuntime();
}

void Statistics::averageRuntime()
{
	Runtime total;
	for (int i = 0; i < runtimes.size(); i++)
		total += runtimes[i];
	avg = total / (runtimes.size());
}

void Statistics::averageLength()
{
	int total;
	for (auto i : passwords)
		total += i.length();
	avg_len = total / passwords.size();
}

void Statistics::summary()
{
	cout << "Average runtime: " << blue << static_cast<PrintableRuntime>(avg).count();
	cout << "ms for " << passwords.size() << " passwords.\n" << white;
	cout << "Min runtime: " << green << static_cast<PrintableRuntime>(min).count() << "ms\t" << white;
	cout << "Max runtime: " << red << static_cast<PrintableRuntime>(max).count() << "ms\n" << white;
}

int main()
{
	cout << "This program will guess your password.\n";
	cout << "You may only use a-z, and 1-5 characters.\n";
	cout << "Type Q to quit.\n";
	Password password;
	Timer timer;
	PlainTextCracker plaintext;
	string input = " ";
	password.setType(LOWER_ALPHA);
	plaintext.setType(LOWER_ALPHA);
	plaintext.calculateMaxAttempts();

	while (!isQuit(input))
	{
		input.clear();
		input = password.promptUser();
		if (isQuit(input))
			break;
		plaintext.setPassword(password.getPassword());
		timer.start();
		plaintext.crack();
		timer.batchFinish();
		plaintext.reset();
	}

	// calculate runtime data
	Statistics statistics;
	statistics.setRuntimes(timer.getRuntimeData());
	statistics.setPasswords(plaintext.getPwset());
	statistics.setAttempts(plaintext.getAttempts());
	statistics.calculate();
	statistics.summary();

	system("pause");
	return 0;
}