#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <utility>
#include "Date.h"
#include "utils.h"

using namespace std;

class Broker;
class Compare;

class Offer{
protected:
	/**
	 * static int that holds the last given id.
	 */
	static int CURRENT_ID;
	/**
	 * integer value of the id
	 */
	int id;
	/**
	 *
	 * integer number of unities of an offer. It can be number of nights for example.
	 */
	int numUni; // num de noites por exemplo.
	/**
	 * string of the city of that offer.
	 */
	string city;
	/**
	 *  string that specifies the type of the unities.(day/week/month).
	 */
	string typeUni; // ('day','week','month')
	/**
	 * float value of the price per typeUni.
	 */
	float price;
	/**
	 *  vector of pair<Date,Date> that defines the periods that the offer is unavailable
	 */
	vector<pair<Date,Date>> unavailability; // periodos indisponiveis
	/**
	* value of days since the last booking.
	*/
	int period;
	/**
	* bool value to which a offer is on sale or not
	*/
	bool sale;
public:
	/**
	 * Default constructor
	 * Initializes the pointers to nullptr and some other default values
	 */
	Offer();
	/**
	 * Parametered constructor
	 * @param numU
	 * @param c
	 * @param t of unity
	 * @param vector<pair<Date,Date>>
	 * @param id
	 */
	Offer(int numU, string c, string t, float price, vector<pair<Date,Date>> disp = vector<pair<Date, Date>>(0), int id = 0);
	/**
	 * add a period of unavailability
	 * @param iDate starting date
	 * @param iDate ending date
	 * @throws InvalidInput exception
	 * @return reference of the current offer instance
	 */
	Offer & addUnavailability(Date iDate, Date fDate);
	/**
	 * eliminate a period of unavailability
	 * @param iDate starting date
	 * @param fDate ending date
	 * @throws InvalidInput exception
	 * @return reference of the current offer instance
	 */
	Offer & elimUnavailability(Date iDate, Date fDate);
	/**
	 * get the periods of unavailabilities
	 * @return vector with unavailable periods
	 */
	vector<pair<Date,Date>> getUnavailability()const;
	/**
	 * Get the value of the id
	 * @return unsigned int with the id
	 */
	int getId()const;
	/**
	 * calculates the price upon the unity type
	 * @return the price
	 */
	float getPrice()const;
	/**
	 * get the city of the offer
	 * @return city of the offer
	 */
	string getCity()const;
	/**
	 * get the type of unity of the offer
	 * @return the unity type
	 */
	string getTypeUni()const;
	/**
	 * get the number of unities of that offer
	 * @return the number of unities
	 */
	int getNumUni()const;
	/**
	 * set the value of the id
	 * @param value of the id
	 * @return reference to the current Offer instance
	 */
	Offer & setId(int id);
	/**
	 * set the number of unities
	 * @param numUni number of unities
	 * @return reference to the current Offer instance
	 */
	Offer & setNumUni(int numUni);
	/**
	 * set the offer's city
	 * @param c city of the offer
	 * @return reference to the current Offer instance
	 */
	Offer & setCity(string city);
	/**
	 * set the type of unities
	 * @param typeUni type of unities
	 * @return reference to the current Offer instance
	 */
	Offer & setTypeUni(string typeUni);
	/**
	 * set the price value
	 * @param price value
	 * @return reference to the current Booking instance
	 */
	Offer & setPrice(float price);
	/**
	 * calculate the price upon the type of unity
	 * @param start date
	 * @param end date
	 * @return double value of zero
	 */
	double calculatePrice(Date start, Date end, Broker  * broker);
	/**
	 * Output operator for a Offer object
	 * @param os the ostream to output to
	 * @param right the Offer to output
	 * @return ostream reference to the passed ostream
	 */
	friend ostream & operator <<(ostream & os, const Offer &o);
	//friend istream & operator >>(istream & in, Offer &o);
	/**
	 * read a Offer instance from an istream
	 * @param in the istream to input from
	 * @param right the Offer to input to
	 * @return istream reference to the passed istream
	 */
	virtual istream& readOffer(istream & is, Broker &b);
	/**
	 *  write a string with the offer info
	 *  @return string with the offer info
	 */
	virtual string toFile()const;
	/**
	 * write to a string the city, numUni, typeUni, the size of the vector of unavailabiblity and its dates
	 * @return the string written
	 */
	virtual string toConsole()const;

	/**
	* Checks if the current offer is available between the start and end dates, including thoso two days.
	* If start > end then the two dates are swapped
	* @param start the start off the period to check for availability, this day is included
	* @param end the end off the period to check for availability, this day is included
	* @return false if there is any unavailability or if end < start, true
	*/
	bool isAvailable(Date start, Date end);
	/**
	* set the value of period
	*/
	void setPeriod();
	/*
	* get the period of the offer.
	* @return the period between the current date and the last booking.
	*/
	int getPeriod()const;
	/**
	* operator for the priority queue. Determins which offer was more dicount.
	* @param the offer to compare with.
	* @return the offer with the biggest discount
	*/
	bool operator<(const Offer  & o);
	/**
	* get the value of sale, of a offer.
	* @return sale value.
	*/
	bool getSaleValue()const;
	/**
	* set a new value for the sale, with the value of the parameter.
	* @param value to be set.
	* 
	*/
	void setSaleValue(bool v);
	/*
	* Calculates the value of the discount depending on the position of the offer in the P_Q
	* @param pointer to the priority_queue
	* @return value of the discount
	*/
	double ref(priority_queue<Offer, vector<Offer>, Compare>  * temp);
};

class Room:public Offer{
private:
	/**
	 * type of room  's' - simple, 'd' - double, 'e' - double_extra_bed
	 */
	string type;//simple - 's', double - 'd' or double_extra_bed - 'e'
	/**
	 * boolean type if it is a hotel room, sharedHouse or bedAndBreakfast;
	 * 1 for yes, 0 otherwise
	 */
	bool hotel,sharedHouse,bedAndBreakfast;
public:
	/**
	 * Default constructor
	 * Initializes the pointers to nullptr and some other default values
	 */
	Room();
	/**
	 * Parametered constructor
	 * @param numU number of unities
	 * @param c city
	 * @param t type of unity
	 * @param price price
	 * @param vector<pair<Date, Date>> vector of pair of dates
	 * @param typ type of room
	 * @param h hotel
	 * @param shrHouse sharedHouse
	 * @param bf bedAndbreakfast
	 * @param id
	 */
	Room(int numU, string c, string t, float price, vector<pair<Date, Date>> disp,
		string typ, bool h, bool shdHouse, bool bf, int id = 0);
	/**
	 * get the hotel boolean value
	 * @return hotel value
	 */
	bool getHotelVal() const;
	/**
	 * get the sharedHouse boolean value
	 * @return sharedHouse value
	 */
	bool getSharedHouseVal() const;
	/**
	 *  get the bedAndbreakfast boolean value
	 *  @return bedAndbreakfast value
	 */
	bool getBedAndBreakfastVal() const;
	/**
	 * set the type of the room
	 * @param type type of room
	 * @return reference to the current Room instance
	 */
	Room & setType(string type);
	/**
	 * set the hotel value
	 * @param hotel new hotel value
	 * @return reference to the current Room instance
	 */
	Room & setHotel(bool hotel);
	/**
	 * set the sharedHouse value
	 * @param shatedHouse new sharedHouse value
	 * @return reference to the current Room instance
	 */
	Room & setSharedHouse(bool sharedHouse);
	/**
	 * set the BedAndBreakfast value
	 * @param bedAndBreakfast new BedAndBreakfast value
	 * @return reference to the current Room instance
	 */
	Room & setBedAndBreakfast(bool bedAndBreakfast);
	/**
	 *  write a string with the room info
	 *  @return string written
	 */
	string toFile()const;
	/**
	 * write to a string the room info
	 * @return the string written
	 */
	string toConsole()const;
	/**
	 * read a Offer instance from an istream
	 * @param is the istream to input from
	 * @param right the Room offer to input to
	 * @return istream reference to the passed istream
	 */
	istream& readOffer(istream & is, Broker &b);

	/**
	 * Input operator for a Room in format: offer atributes, room atributes, unavailabilities
	 * @param in the istream to input from
	 * @param right the Room offer to input to
	 * @return istream reference to the passed istream
	 */
	friend istream & operator >> (istream & in, Room &r);
	/**
	 * Output operator for a Offer object
	 * @param out the ostream to output to
	 * @param right the Room offer to output
	 * @return ostream reference to the passed ostream
	 */
	friend ostream & operator <<(ostream & os, const Room &o);
};

class Flat: public Offer{
private:
	/**
	 *  boolean room value
	 *  1 if has one room, 0 otherwise
	 */
	bool fRoom;
	/**
	 * boolean kitchen value
	 * 1 if has kitchen, 0 otherwise
	 */
	bool kitchen;
	/**
	 * boolean bathroom value
	 * 1 if has bathroom, 0 otherwise
	 */
	bool bathroom;
public:
	/**
	 * Default constructor
	 * Initializes the pointers to nullptr and some other default values
	 */
	Flat();
	/**
	 * Parametered constructor
	 * @param numU number of unities
	 * @param c city
	 * @param t type of unity
	 * @param price price
	 * @param vector<pair<Date, Date>> vector of pair of dates
	 * @param fr boolean room value
	 * @param k boolean kitchen value
	 * @param br boolean bathroom value
	 * @param id
	 */
	Flat(int numU, string c, string t, float price,
		vector<pair<Date, Date>> disp, bool fr, bool k, bool br, int id = 0);
	/**
	 * set the boolean room value with new parameter value
	 * @param fRoom new boolean room value
	 * @return reference to the current Flat instance
	 */
	Flat & setFRoom(bool fRoom);
	/**
	 * set the boolean kitchen value with new parameter value
	 * @param kitchen new boolean kitchen value
	 * @return reference to the current Flat instance
	 */
	Flat & setKitchen(bool kitchen);
	/**
	 * set the boolean bathroom value with new parameter value
	 * @param bathroom new boolean bathroom value
	 * @return reference to the current Flat instance
	 */
	Flat & setfBathroom(bool bathroom);
	/**
	 *  write a string with the Flat info
	 *  @return string written
	 */
	string toFile()const;
	/**
	 * write to a string the room info
	 * @return the string written
	 */
	string toConsole()const;
	/**
	 * read a Offer instance from an istream
	 * @param is the istream to input from
	 * @param right the Flat offer to input to
	 * @return istream reference to the passed istream
	 */
	istream& readOffer(istream & is, Broker &b);
	/**
	 * Input operator for a Flat in format: offer atributes, flat atributes, unavailabilities
	 * @param in the istream to input from
	 * @param right the Flat offer to input to
	 * @return istream reference to the passed istream
	 */
	friend istream & operator >> (istream & in, Flat &f);
	/**
	 * Output operator for a Flat object
	 * @param out the ostream to output to
	 * @param right the Flat offer to output
	 * @return ostream reference to the passed ostream
	 */
	friend ostream & operator <<(ostream & os, const Flat &o);
};


class Apartment: public Offer{
private:
	/**
	 * vector of paires of string and booleans
	 * string represents room type
	 * bool is true when room is a suite
	 */
	vector<pair<string,bool>> rooms;//bool true == this room is a suite
	/**
	 * boolean kitchen value is 1 if apartment has a kitchen, 0 otherwise
	 */
	bool kitchen;
	/**
	 * boolean livingRoom value is 1 if apartment has a living room, 0 otherwise
	 */
	bool livingRoom;
public:
	/**
	 * Default constructor
	 * Initializes the pointers to nullptr and some other default values
	 */
	Apartment();
	/**
	 * Parametered constructor
	 * @param numU number of unities
	 * @param c city
	 * @param t type of unity
	 * @param price price
	 * @param vector<pair<string,bool>> vector of pair of dates
	 * @param rm boolean room value
	 * @param s boolena suite value
	 * @param k boolean kitchen value
	 * @param lr boolean livingRoom value
	 * @param id
	 */
	Apartment(int numU, string c, string t, float price, vector<pair<Date, Date>> disp
		,vector<pair<string,bool>> rm, bool s, bool k, bool lr, int id = 0);
	/**
	 * add a room to the vector of room of the apartment
	 * @param room_type string with the room type
	 * @param is_suite boolean value the represent if it is a suite
	 * @return reference to the current Apartment instance
	 */
	Apartment & addRoom(string room_type, bool is_suite);
	/**
	 * get the Apartment boolean kitchen value
	 * @return boolean kitchen value
	 */
	bool getKitchenVal()const;
	/**
	 * get the Apartment boolean livingRoom value
	 * @return boolean livingRoom value
	 */
	bool getLivingRoomVal()const;
	/**
	 * set Apartment kitchen boolean value with the value in the parameter
	 * @param kitchen new boolean kitchen value
	 * @return reference to the current Apartment instance
	 */
	Apartment & setKitchen(bool kitchen);
	/**
	 * set Apartment livingRoom boolean value with the value in the parameter
	 * @param livingRomm new boolean livingRomm value
	 * @return reference to the current Apartment instance
	 */
	Apartment & setLivingRoom(bool livingRoom);
	/**
	 *  write a string with the Apartment info
	 *  @return string written
	 */
	string toFile() const;
	/**
	 * write to a string the Apartment info
	 * @return the string written
	 */
	string toConsole()const;
	/**
	 * read a Offer instance from an istream
	 * @param is the istream to input from
	 * @param write the Apartment offer to input to
	 * @return istream reference to the passed istream
	 */
	istream& readOffer(istream & is, Broker &b);
	/**
	 * Input operator for a Apartment in format: offer atributes, Apartment atributes, unavailabilities
	 * @param in the istream to input from
	 * @param right the Apartment offer to input to
	 * @return istream reference to the passed istream
	 */
	friend istream & operator >> (istream & in, Apartment &a);
	/**
	 * Output operator for a Apartment object
	 * @param out the ostream to output to
	 * @param right the Apartment offer to output
	 * @return ostream reference to the passed ostream
	 */
	friend ostream & operator <<(ostream & os, const Apartment &o);
};


class Compare {
public:
	bool operator()(Offer & right, Offer & left) {
		return (left.getPeriod() > right.getPeriod());
	}
};