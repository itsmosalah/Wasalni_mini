#include<string>

using namespace std;

class Validation
{
public:

	static bool CheckEB(string s);
	static void CheckYN(string& choice);
	static void CheckNumbers(int i, string& choice);
	static void userGuide(string& choice,string s, int i, int& var, string s2 = "Are you sure? y/n");
	static string format(string s);
};

