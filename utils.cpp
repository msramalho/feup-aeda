
#include "utils.h"

//-------------Global Exceptions-------------------
InvalidInput::InvalidInput() :message("") {}

InvalidInput::InvalidInput(string m) : message(m) {}

ostream & operator<<(ostream & out, const InvalidInput &i) {
	out << "InvalidInput error: " << i.message << ";";
	return out;
}

ostream & operator<<(ostream & out, const FileNotFound & i) {
	out << "FileNotFound error: " << i.message << ";";
	return out;
}

//-------------Util functions-------------------

void cinTest(bool &success) {
	if (cin.fail()) {
		cin.clear();
	} else {
		success = true;
	}
	cin.ignore(1000, '\n');
}

void cinValueStr(string &result, string message) {
	result = "";
	while (result == "") {
		cout << message;
		char cstr_result[1000];
		cin.getline(cstr_result, 1000, '\n');
		result = string(cstr_result);
		if (cin.fail()) {
			cin.clear();
		}
	}
}

string toLower(string original) {
	transform(original.begin(), original.end(), original.begin(), tolower);
	return original;
}

string trim(string s, char char_trim) {
	stringstream double_trim;
	double_trim << char_trim << char_trim;
	string d_trim = double_trim.str();

	size_t pos = s.find(d_trim);
	while (pos != s.npos) {
		s.erase(pos, 1);
		pos = s.find(d_trim);
	}
	if (s[0] == char_trim) s.erase(0, 1);
	if (s[s.length() - 1] == char_trim) s.erase(s.length() - 1, 1);
	return s;
}

vector <string> readFile(string filename) {
	ifstream f;
	string line;
	vector <string> result;

	f.open(filename);

	if (f.is_open()) {
		while (getline(f, line)) {
			if (line != "") {//in case there are any additional empty lines in the file
				result.push_back(line);
			}
		}
	} else {
		throw FileNotFound("File '" + filename + "' not found");
	}
	f.close();
	return result;
}

stringstream readFileSS(string filename) {
	ifstream f;
	string line;
	stringstream result;

	f.open(filename);

	if (f.is_open()) {
		result << f.rdbuf();
		/*copy(istreambuf_iterator<char>(f),
			istreambuf_iterator<char>(),
			ostreambuf_iterator<char>(result));//copies the file contents into a stringstream*/
	} else {
		throw FileNotFound("File '" + filename + "' not found");
	}
	f.close();
	return result;
}

bool fileExists(string filename) {
	ifstream f;
	f.open(filename);
	if (f.is_open()) {
		f.close();
		return true;
	} else {
		return false;
	}
}

void createNewFile(string filename, string extension) {
	ofstream outfile(filename + extension);
	outfile.close();
}

bool saveToFile(string filename, string content) {
	bool success = true;
	ofstream outf;
	outf.open(filename);
	if (!outf.is_open()) {
		throw FileNotFound("File '" + filename + "' not found");
		success = false;
	} else {
		outf << content;
	}
	outf.close();
	return success;
}

bool yesNoQuestion(string message) {
	string answer = "";
	cinValue(answer, message);
	answer = trim(toLower(answer));
	while (answer != ANSWER_YES && answer != ANSWER_NO) {
		cout << "Your answer should be '"<< ANSWER_YES << "' (yes) or '" << ANSWER_NO << "' (no)" << endl;
		cinValue(answer, message);
		answer = trim(toLower(answer));
	}
	return answer == "s";
}

void replace(string& str, string& from, string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}
