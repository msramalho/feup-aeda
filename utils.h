#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

#define ANSWER_YES "y"
#define ANSWER_NO "n"

/*typedef vector<Supplier *>::iterator sit;
typedef vector<Client *>::iterator cit;
typedef vector<Offer *>::iterator oit;
typedef vector<Booking *>::iterator bit;*/
typedef unsigned int uint;
typedef unsigned short us;
typedef unsigned int usi;
typedef unsigned long long ull;

class InvalidInput {
public:
	string message;
	InvalidInput();
	InvalidInput(string m);
	friend ostream & operator<<(ostream & out, const InvalidInput &i);
};

class FileNotFound : public InvalidInput{
public:
	FileNotFound() :InvalidInput() {};
	FileNotFound(string message) :InvalidInput(message) {};
	friend ostream & operator<<(ostream & out, const FileNotFound &i);
};

/**
* Tests if cin reading operation was successful changes the value of success
* accordingly so it can be handled by the caller
* @param success boolean value representing cin operation result
* @return success, as it is passed by reference
*/
void cinTest(bool &success);

/**
* Read any type of variable from the keyboard through std::cin, after outputing a message related to the value to read.
* @param message the message to show to user while asking for a valid value
* Returns:
* @param result read T1 value
*/
template<typename T1>
void cinValue(T1 &result, string message){
	bool success = false;
	while (!success) {
		cout << message;
		cin >> result;
		cinTest(success);
	}
}

/**
* Read string from the keyboard through std::cin.getline(), after outputing a message related to the
* value to read so as to allow strings with word-breaks.
* @param message the message to show to user while asking for a non-empty string
* Returns:
* @param result read string value
*/
void cinValueStr(string &result, string message);

/**
* Convert a string to lower case
* @param original the string to transform
* @return string with the result of the operation
*/
string toLower(string original);

/**
* Trim the original string, by removing all occurences of trimmed_char from its left and right and allowing only one betwee other chars
* @param original the string to trim
* @param char_trim char to remove
* @return s string trimmed
*/
string trim(string s, char char_trim = ' ');

/**
* Reads al the lines from a file into a vector<string>
* @throws FileNotFound();
* @param filename of the file to be read
* @return vector <string> with all the lines
*/
vector<string> readFile(string filename);

/**
* Reads al the lines from a file into a stringstream
* @throws FileNotFound();
* @param filename of the file to be read
* @return stringstream with all the lines
*/
stringstream readFileSS(string filename);

/**
* Tests if a filename corresponds to a valid file
* @throws FileNotFound
* @param filename to search
* @return boolean true if the file exists/ is readable or false if it does not
*/
bool fileExists(string filename);

/**
* Create new empty file
* @param filename to create
*/
void createNewFile(string filename, string extension = ".txt");

/**
* Write string to file
* @param filename to write to
* @throws FileNotFound();
* @return boolean true if the file exists and the operation is successful, false otherwise
*/
bool saveToFile(string filename, string content = "");

/**
* Continuously ask for either a yes or a no
* @param message message to display until user answers y or n
* @return true if the user answered yes, false otherwise
*/
bool yesNoQuestion(string message);

/**
* Replace a string for another inside a string
* @param str the string to be changed
* @param from the string to find
* @param to the string to replace with
*/
void replace(string& str, string& from, string& to);

//imprimir vector separado por espaços, nao usar para vetores dentro de vetores, porque a formatacao é para um e para escrever nos ficheiros
/**
* Outputs any vector to any ostream
* @param out ostream to send the data
* @param v vector of any kind to output
* @return the ostream after receiving the output
*/
template <class T>
ostream & operator<<(ostream & out, const vector<T> &v) {
	//out << "[";
	if (v.size()>0) {
		out << v[0];
	}
	if (v.size()<=1) {
		return out;
	}
	for (auto i = (v.begin() + 1); i != v.end(); i++) {
		out << " " << (*i);
	}
	//out << "]";
	return out;
}

/**
* Outputs any pair to any ostream
* @param out ostream to send the data
* @param p pair of any kind to output
* @return the ostream after receiving the output
*/
template <class T1, class T2>
ostream & operator<<(ostream & out, const pair<T1,T2> &p) {
	out << p.first << ' ' << p.second;
	return out;
}

template<class T>
vector<T> getUniqueValues(const vector<T> &v) {
	vector<T> res;
	vector<T>::iterator vti;
	vector<T>::const_iterator vcti;
	bool repeated;
	for (vcti = v.begin(); vcti != v.end(); vcti++) {
		repeated = false;
		for (vti = res.begin(); vti != res.end();vti++) {
			if ((*vcti)==(*vti)) {
				repeated = true;
				break;
			}
		}
		if (!repeated) {
			res.push_back(*vcti);
		}
	}
	return res;
}