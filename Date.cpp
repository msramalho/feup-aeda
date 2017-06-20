#include "Date.h"
#include "utils.h"

Date::Date(){
	day = 1;
	month = 1;
	year = 0;
	//cout << year << " - " << isLeapYear(year) << endl;
}

Date::Date(string s) {
	stringstream ss(s);
	ss >> (*this);
}

Date::Date(us d, us m, us y) {
	if (!isValid(d, m, y)) {//if the date is not valid throw exception
		throw InvalidDate();
	} else {//create date with valid data
		day = d;
		month = m;
		year = y;
	}
}

us Date::getDay() const {
	return day;
}

us Date::getMonth() const {
	return month;
}

us Date::getYear() const {
	return year;
}

Date & Date::setDay(us d) {
	if (!isValid(d, month, year)) {//if the date is not valid throw exception
		throw InvalidDate();
	} else {//save the value
		day = d;
	}
	return *this;
}

Date & Date::setMonth(us m) {
	if (!isValid(day, m, year)) {//if the date is not valid throw exception
		throw InvalidDate();
	} else {//save the value
		month = m;
	}
	return *this;
}

Date & Date::setYear(us y) {
	if (!isValid(day, month, y)) {//if the date is not valid throw exception
		throw InvalidDate();
	} else {//save the value
		year = y;
	}
	return *this;
}

uint Date::toDays() const{
	ull days_this = 0;
	for (us i = 0; i < year; i++) {//add all the days of past years
		days_this += isLeapYear(i) ? DAYS_IN_LEAP_YEAR : DAYS_IN_YEAR;
	}
	vector<us> days_year = isLeapYear(year)?DAYS_PER_LEAP_YEAR: DAYS_PER_YEAR;
	for (us i = 1; i < month; i++) {//add all the days of past month
		days_this += days_year[i - 1];
	}
	return days_this + day;
}

bool Date::isValid(us d, us m, us y) const {
	if(d < 1 || m < 1 || m > 12 || y < 0)
		return false;

	return isLeapYear(y)?d <= DAYS_PER_LEAP_YEAR[m - 1]: d <= DAYS_PER_YEAR[m - 1];
}

bool Date::isLeapYear(us y) const{
	return ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0));
}

bool Date::operator<(const Date & right) const {
	return year < right.year
		|| (year == right.year && month < right.month)
		|| (year == right.year && month == right.month && day < right.day);
}

bool Date::operator==(const Date & right) const {
	return year == right.year && month == right.month && day == right.day;
}

ull Date::operator-(const Date & right) const {
	return std::abs((long double)(this->toDays() - right.toDays()));
}

ostream &operator << (ostream &out, const Date &right) {
	out << setw(2) << setfill('0') << right.day << "/" << setw(2) << right.month << "/" << setw(4) << right.year << setfill(' ');
	return out;
}
istream &operator >> (istream &in, Date &data) {
	us temp_d, temp_m, temp_y;
	char c;
	in >> temp_d >> c >> temp_m >> c >> temp_y;
	//cout << "test: " << endl << temp_d << c << temp_m << c << temp_y << endl;
	if (in.fail()) {//if the input is corrupt throw exception
		throw InvalidInput("This date does not respect the DD/MM/YYYY format");
	} else {
		data = Date(temp_d, temp_m, temp_y);
	}
	return in;
}

ostream & operator<<(ostream & out, const InvalidDate & right) {
	out << "Invalid_date error: " << right.message << ";";
	return out;
}

InvalidDate::InvalidDate():message("") {}

InvalidDate::InvalidDate(string m) : message(m) {}


