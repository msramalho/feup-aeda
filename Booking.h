#pragma once

#include <utility>

#include "Date.h"
#include "Offer.h"
#include "Person.h"

class Broker;
class Booking {//Reserva
private:
	/**
	* pair<Date, Date> that holds the start and end dates of the current Booking
	*/
	pair<Date, Date> interval;
	/**
	* unsigned int status
	* 0 means the Booking is active and 1 means it is cancelled
	*/
	uint status;
	/**
	* unsigned int that holds the unique identifier of the current Booking
	*/
	uint id;
	/**
	* an Offer pointer to the associated Offer instance
	*/
	Offer * offer;
	/**
	* an Client pointer to the associated Client instance
	*/
	Client * client;
	/**
	* static unsigned int that holds the last given id
	*/
	static uint CURRENT_ID;
public:
	/**
	* Default constructor
	* Initializes the pointers to nullptr and some other default values
	*/
	Booking();
	/**
	* Parametered constructor
	* Initializes the pointers to and the other parameters
	* @param o Offer pointer
	* @param c Client pointer
	* @param start Date instance
	* @param end Date instance
	* @param the saved id value
	* @throws InvalidInput exception
	*/
	Booking(Offer * o, Client * c, Date start, Date end = Date(), uint id = 0);
	/**
	* Cancel a booking
	* Changes the state from 0 to 1 if possible
	* @return true if possible, false otherwise
	*/
	bool cancel_booking();
	/**
	* Get the value of the start and end dates
	* @return pair<Date, Date> with the start date as first and end date as second
	*/
	pair<Date, Date> get_date() const;
	/**
	* Get the value of the start date
	* @return Date with the start date
	*/
	Date get_start() const;
	/**
	* Get the value of the end date
	* @return Date with the end date
	*/
	Date get_end() const;
	/**
	* Get the value of the id
	* @return unsigned int with the id
	*/
	uint getId()const;

	/**
	* Get the value of the client that made this booking
	* @return client pointer of said client
	*/
	Client * getClient();

	/**
	* Get the value of the offer that made is in this booking
	* @return offer pointer of said offer
	*/
	Offer * getOffer();

	/**
	* Set the status of the current Booking instance to 1 (cancelled)
	* @return reference to the current Booking instance
	*/
	Booking & cancelBooking();

	/**
	* Set the value of client
	* @param c Client pointer
	* @return reference to the current Booking instance
	*/
	Booking & setClient(Client *c);
	/**
	* Set the value of offer
	* @param o Offer pointer
	* @return reference to the current Booking instance
	*/
	Booking & setOffer(Offer *o);

	/**
	* Set the value of the start date
	* @param start Date instance
	* @throws InvalidInput exception
	* @return reference to the current Booking instance
	*/
	Booking & setStart(Date start);
	/**
	* Set the value of the end date
	* @param end Date instance
	* @throws InvalidInput exception
	* @return reference to the current Booking instance
	*/
	Booking & setEnd(Date end);

	/**
	* read a Booking instance from an istream
	* @param in the istream to input from
	* @param right the Booking to input to
	* @return istream reference to the passed istream
	*/
	istream & readBooking(istream & is, Broker &b);
	/**
	* Output operator for a Booking object
	* @param out the ostream to output to
	* @param right the Booking to output
	* @return ostream reference to the passed ostream
	*/
	friend ostream & operator <<(ostream & os, const Booking &b);
	/**
	* virtual method
	* Generate a string that can be outputed to the console (in a legible state)
	* @return string with the information to output
	*/
	virtual string toConsole()const;
	/**
	* virtual method
	* Generate a string that can be outputed to the console (in a legible state)
	* @param broker to use for the price calculation of the booking
	* @return string with the information to output
	*/
	virtual string toConsole(Broker *b)const;

	/**
	* @brief Operator less than defined according to the specification
	* First the order is decided by the client's name then by the date of the booking
	* @param right the Booking to compare the current Booking to
	* @return true if the current booking is less than the right booking
	*/
	bool Booking::operator<(const Booking &right) const;

	/**
	* @brief Operator equal to defined according to the specification
	* First the order is decided by the client's name then by the date of the booking
	* @param right the Booking to compare the current Booking to
	* @return true if the current booking is less than the right booking
	*/
	bool Booking::operator==(const Booking &right) const;
};
