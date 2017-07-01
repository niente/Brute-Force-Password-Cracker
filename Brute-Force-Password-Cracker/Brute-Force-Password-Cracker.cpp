#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <iomanip>
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

#define MAX_CHARS 5
#define LOWER_ALPHA "abcdefghijklmnopqrstuvwxyz"
#define DUMMY_TRAILER "\177"

typedef chrono::duration<double> Runtime;
typedef chrono::duration <double, milli> PrintableRuntime;

///    printVector
// Template which prints contents of a vector of any type.
template <typename T>
void printVector(const T& inputVector)
{
	for (auto i = inputVector.begin(); i != inputVector.end(); ++i)
		cout << *i;
	cout << "\n";
}

// lambdas
auto isFinished = [](auto letter) {return letter == 0; }; // to clean brute force algorithm
auto resize = [](char *p, char c, int n) { return memset(p, c, n); }; // allocate additional memory for char array
auto fastPrint = [](char *p, char *n) {
	fwrite(p, sizeof(char), sizeof(p) - 1, stdout);
	fwrite(n, sizeof(char), 1, stdout);
}; // fwrite is faster than cout
auto isQuit = [](string s) { return s == "Q" || s == "q"; }; // check if user input says to exit program

// accepts password as input, performs brute force crack.
// uses async to execute the brute force function
// counts n attempts, and builds a vector of passwords the user has entered
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

// max attempts: polynomial sum (1 - pw_size) = available_characters^n
void PlainTextCracker::calculateMaxAttempts()
{
	maxAttempts = 0;
	for (int i = 1; i <= MAX_CHARS; i++)
		maxAttempts += pow(charSet.size(), i);
	cout << "Max attempts for a password of length " << MAX_CHARS << ": " << maxAttempts << "\n";
}

// passes resulting pw to future
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

// measure runtime of each search
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

// validate user input based on #defined character set
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

// container for results
class PasswordData
{
public:
	Runtime runtime;
	unsigned long long int attempts;
	string password;
	PasswordData(Runtime r, unsigned long long int a, string p);
	friend ostream &operator<<(ostream &os, const PasswordData &pwData);
};

PasswordData::PasswordData(Runtime r, unsigned long long int a, string p)
{
	runtime = r;
	attempts = a;
	password = p;
}

ostream &operator<<(ostream &os, const PasswordData &pwData)
{
	os << static_cast<PrintableRuntime>(pwData.runtime).count() << "ms to find [";
	os << pwData.password << "] in " << pwData.attempts << " attempts.\n";
	return os;
}

// calculates min, max, avg on password data
class Statistics
{
private:
	vector<PasswordData> pwData;
	Runtime avg_run;
	Runtime totalRuntime;
	pair<Runtime, int> min;
	pair<Runtime, int> max;
	double avg_len;
public:
	Statistics();
	void setPwData(vector<PasswordData> p);
	void summary();
	void calculate();
};

Statistics::Statistics()
{
	avg_run.zero();
	min.first.zero();
	max.first.zero();
	totalRuntime.zero();
}

void Statistics::setPwData(vector<PasswordData> p)
{
	pwData = p;
}

void Statistics::calculate()
{
	min.first = max.first = pwData[0].runtime;
	double totalLetters = 0;
	totalRuntime += pwData[0].runtime;
	for (int i = 1; i < pwData.size(); i++)
	{
		if (pwData[i].runtime < min.first)
		{
			min.first = pwData[i].runtime;
			min.second = i;
		}

		if (pwData[i].runtime > max.first)
		{
			max.first = pwData[i].runtime;
			max.second = i;
		}
		totalRuntime += pwData[i].runtime;
		totalLetters += pwData[i].password.length();
	}
	avg_run = totalRuntime / pwData.size();
	avg_len = totalLetters / pwData.size();
}


void Statistics::summary()
{
	cout << "Average runtime: " << blue << static_cast<PrintableRuntime>(avg_run).count();
	cout << "ms" << white << " for " << pwData.size() << " passwords.\n";
	cout << "Min runtime: " << green << pwData[min.second] << white;
	cout << "Max runtime: " << red << pwData[max.second] << white;
	cout << "Average pw length: " << fixed << setprecision(2) << avg_len << " characters.\n";
}

vector<PasswordData> buildPwData(vector<string> p, vector<unsigned long long int> a, vector<Runtime> r)
{
	vector<PasswordData> pwData;
	for (int i = 0; i < p.size(); i++)
	{
		PasswordData tempData(r[i], a[i], p[i]);
		pwData.push_back(tempData);
	}
	return pwData;
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
	vector<PasswordData> pwData = buildPwData(plaintext.getPwset(), plaintext.getAttempts(), timer.getRuntimeData());

	// calculate runtime data
	Statistics statistics;
	statistics.setPwData(pwData);
	statistics.calculate();
	statistics.summary();

	cout << "Printing password data:\n";
	printVector(pwData);

	system("pause");
	return 0;
}