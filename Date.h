#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>

#include "utils.h"

using namespace std;

const us DAYS_IN_LEAP_YEAR = 366;
const us DAYS_IN_YEAR = 365;
const vector<us> DAYS_PER_YEAR = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const vector<us> DAYS_PER_LEAP_YEAR = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Date {
private:
	/**
	* unsigned short variables to hold the day, month and year of the date
	*/
	us day, month, year;
public:
	/**
	* Empty constructor for Date class
	*/
	Date();
	/**
	* Constructor for Date class from date string
	* 
	* Can throw Invalid_input and Invalid_date exceptions
	* @see Invalid_input
	* @see Invalid_date
	* @param d a string that should contain the date in the format "DD/MM/YYYY", though the char '/' can be replaced and the number of digits can also vary
	*/
	Date(string d);
	/**
	* Constructor for Date class that receives unsigned short (us)
	* 
	* Can throw Invalid_date exception
	* @see Invalid_date
	* @param d day
	* @param m month
	* @param y year
	*/
	Date(us d, us m, us y);

	/**
	* Getter for private variable day
	*/
	us getDay() const;
	/**
	* Getter for private variable month
	*/
	us getMonth() const;
	/**
	* Getter for private variable year
	*/
	us getYear() const;


	/**
	* Setter for private variable day
	* 
	* Can throw Invalid_date exception
	* @see Invalid_date
	* @param d the new value for day
	* @return reference to the current instance of Date
	*/
	Date & setDay(us d);
	/**
	* Setter for private variable month
	*
	* Can throw Invalid_date exception
	* @see Invalid_date
	* @param m the new value for month
	* @return reference to the current instance of Date
	*/
	Date & setMonth(us m);
	/**
	* Setter for private variable year
	*
	* Can throw Invalid_date exception
	* @see Invalid_date
	* @param y the new value for year
	* @return reference to the current instance of Date
	*/
	Date & setYear(us y);

	/**
	* Get the number of days in a date since 01/01/0000, including
	*
	* @return uint with number if days
	*/
	uint toDays() const;

	/**
	* Check if a given date is valid
	* @param d the day
	* @param m the month
	* @param y the year
	* @return bool true if the date is valid, false otherwise
	*/
	bool isValid(us d, us m, us y) const;
	/**
	* Check if a given year is a leap year
	* @param y the year
	* @return bool true if the year is a leap year, false otherwise
	*/
	bool isLeapYear(us y) const;

	/**
	* Operator less than for Date
	* @param right the date to compare to
	* @return bool true if the current instance is previous to right, false otherwise
	*/
	bool operator<(const Date & right) const;
	/**
	* Operator equal to for Date
	* @param right the date to compare to
	* @return bool true if the current instance is the same day of the same month of the same year as right, false otherwise
	*/
	bool operator==(const Date & right) const;
	/**
	* Operator minus for Date
	* @param right the date to subtract
	* @return unit number of days between both dates, always a positive value
	*/
	ull operator-(const Date & right) const;

	/**
	* Output operator for a Date object in the format "DD/MM/YYYY"
	* @param out the ostream to output to
	* @param right the Date to output
	* @return ostream reference to the passed ostream
	*/
	friend ostream &operator << (ostream &out, const Date &right);
	/**
	* Input operator for a Date object in the format "DD/MM/YYYY", though the char '/' can be replaced and the number of digits can also vary
	* @param in the istream to input from
	* @param right the Date to input to
	* @return istream reference to the passed istream
	*/
	friend istream &operator >> (istream &in,  Date &right);
};

class InvalidDate {// : public logic_error {
public:
	string message;
	/**
	* Default constructor for InvalidDate exception class
	*/
	InvalidDate();
	/**
	* Constructor for InvalidDate exception class with one parameter
	* @param m the message to associate with this exception
	*/
	InvalidDate(string m);
	/**
	* Output operator for an InvalidDate object
	* @param out the ostream to output to
	* @param right the InvalidDate to output
	* @return ostream reference to the passed ostream
	*/
	friend ostream & operator<<(ostream & out, const InvalidDate & right);
};