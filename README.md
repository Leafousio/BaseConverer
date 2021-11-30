#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#define MOD 1000000007

static class ExamSolver
{
public:

	//File handling
	static std::vector<int> ReadFileI(const std::string dir);
	static std::vector<float> ReadFileF(const std::string dir);
	static std::vector<std::string> ReadFileS(const std::string dir);
	static std::vector<char> ReadFileC(const std::string dir);

	static void WriteFile(const std::string name, const std::vector < std::string > data);

	//Powers
	long long fast_power(long long base, long long power);

	//Paalindromes
	static bool isPaali(const std::string n);

	//Prime
	static bool isPrime(const int n);

	//Base Converter
	static std::string convertBase(std::string s, int baseFrom, int baseTO);


private:
	inline static int Clamp(int val, int min, int max);
	static int toDeci(std::string str, const int base);
	static char reVal(int num);
	static std::string fromDeci(int base, int inputNum);
	static int toDeciNum(int numAscii);
};



int main()
{
	std::cout << ExamSolver::convertBase("255", 10, 2);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////		CLASS_SRC		///////////////////////////////////////////////////////////////////////


bool ExamSolver::isPrime(const int n)
{
	if (n <= 1)
		return false;

	for (int i = 2; i < n; i++)
		if (n % i == 0)
			return false;
	return true;
}

bool ExamSolver::isPaali(const std::string str) {
	for (int i = 0; i < str.length() / 2; i++) {
		if (str[i] != str[str.length() - i - 1])
			return false;
	}
	return true;
	
}

long long ExamSolver::fast_power(long long base, long long pow) {
	long long res = 1;
	while (pow > 0) {

		if (pow % 2==1) {
			res *= base;
		}
		base *= base;
		pow /=2;
	}
	return res;
}

std::vector<int> ExamSolver::ReadFileI(const std::string dir) 
{
	std::vector<int> res;
	std::ifstream infile;
	infile.open(dir);
	
	int el;
	while (infile >> el)
		res.push_back(el);
	return res;
}

std::vector<float> ExamSolver::ReadFileF(const std::string dir)
{
	std::vector<float> res;
	std::ifstream infile;
	infile.open(dir);

	float el;
	while (infile >> el)
		res.push_back(el);
	return res;
}

std::vector<std::string> ExamSolver::ReadFileS(const std::string dir)
{
	std::vector<std::string> res;
	std::ifstream infile;
	infile.open(dir);

	std::string el;
	while (infile >> el)
		res.push_back(el);
	return res;
}

std::vector<char> ExamSolver::ReadFileC(const std::string dir)
{
	std::vector<char> res;
	std::ifstream infile;
	infile.open(dir);

	int el;
	while (infile >> el)
		res.push_back(el);
	return res;
}

void ExamSolver::WriteFile(const std::string name,const std::vector<std::string> data)
{
	std::ofstream outfile;
	outfile.open(name, std::ios_base::app);
	for (size_t i = 0; i < data.size(); i++)
		outfile << data[i];
	return;
}

inline int ExamSolver::Clamp(int val, int min, int max)
{
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

int ExamSolver::toDeciNum(int numAscii)
{
	if (numAscii > 255)
	{
		return -1;
	}
	if (numAscii >= 48 && numAscii < 58)
		return numAscii - 48;
	else if (numAscii >= 65)
		return numAscii - 55;

	return -1;
}

int ExamSolver::toDeci(std::string str, const int base)
{
	int pow = 1;
	int num = 0;
	int num2 = 0;

	for (int i = (int)str.size() - 1; i >= 0; i--) {
		num2 = toDeciNum(int(str[i]));

		if (num2 >= base) {
			return -1;
			std::cout << "wrong base!" << std::endl;
		}

		num += num2 * pow;
		pow *= base;
	}
	return num;
}

char ExamSolver::reVal(int num)
{
	if (num >= 0 && num <= 9)
		return (char)(num + '0');
	else
		return (char)(num - 10 + 'A');
}

std::string ExamSolver::fromDeci(int base, int inputNum)
{
	std::string res = "";

	while (inputNum > 0) {

		res += reVal(inputNum % base);
		inputNum /= base;
	}
	reverse(res.begin(), res.end());

	return res;
}

std::string ExamSolver::convertBase(std::string s, int baseFrom, int baseTO)
{
	int num = toDeci(s, baseFrom);
	std::string res = fromDeci(baseTO, num);
	return res;
}
