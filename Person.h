#pragma once

#include "Offer.h"
#include "utils.h"
using namespace std;

class Broker;
class Offer;

class Person{
protected:
	/**
	* integer value of the id
	*/
	int id;
	/**
	* string value of the name
	*/
	string name;
	/**
	* integer value of the nif
	*/
	int nif;
	/**
	* string value of the adress
	*/
	string address;
	/**
	* static int that holds the last given id.
	*/
	static int CURRENT_ID;
public:
	/**
	* Default constructor
	* Initializes the pointers to nullptr and some other default values
	*/
	Person();
	/**
	* Parametered constructor
	* @param name
	* @param nif
	* @param adress
	* @param id
	*/
	Person(string name,int nif,string address, int id = 0);
	/**
	* Default virtual destructor definition
	*/
	virtual ~Person();
	/**
	* Get the value of the name
	* @return string with the name
	*/
	string getName() const;
	/**
	* Get the value of the nif
	* @return integer with the nif
	*/
	int getNif();
	/**
	* Get the value of the adress
	* @return string with the adress
	*/
	string getAddress();
	/**
	* Get the value of the id
	* @return integer with the id
	*/
	int getId() const;
	/**
	* set the name of person
	* @param name of person
	* @return void
	*/
	void setName(string name);
	/**
	* set value of id
	* @param value of id
	* @return void
	*/
	void setId(int id);
	/**
	* set value of nif
	* @param value of nif
	* @return void
	*/
	void setNif(int nif);
	/**
	* set value of adress
	* @param value of adress
	* @return void
	*/
	void setAddress(string address);
	/**
	 * Output operator for a Person object
	 * @param os the ostream to output to
	 * @param right the Person to output
	 * @return ostream reference to the passed ostream
	 */
	friend ostream& operator<<(ostream& os, const Person& p1);
	/**
	* Overloading of operator equals
	* @param right Person
	* @return bool(true if Person is equal)
	*/
	bool operator==(const Person & p) const;
	/**
	* Sets the field width to be used on output operations
	*/
	static usi SETW;
	/**
	* Write output to text file
	* @return string
	*/
	virtual string toFile() const;
	/**
	* Write output to console
	* @return string
	*/
	virtual string toConsole()const;
};

class Supplier: public Person{
private:
	/**
	* vector of Offer pointers with all the offers
	* @return vector
	*/
	vector<Offer *> offers;
public:
	/**
	* Default constructor
	* Initializes the pointers to nullptr and some other default values
	*/
	Supplier();
	/**
	* Parametered constructor
	* @param name
	* @param nif
	* @param adress
	*/
	Supplier(string name,int nif, string address);
	/**
	 * add an offer
	 * @param Offer ptr
	 * @return reference of the current Supplier instance
	 */
	Supplier & addOffer(Offer * o);
	/**
	* read a Supplier instance from an istream
	* @param in the istream to input from
	* @param right the Broker to input to
	* @return istream reference to the passed istream
	*/
	istream & readSupplier(istream &is, Broker &b);
	/**
	* Get the vector with all offers
	* @return vector of Offer ptr
	*/
	vector<Offer *> getOffers();
	/**
	* Get the vector with all Id's
	* @return vector of uints
	*/
	vector<uint> getOfferIds();
	/**
	* Write output to text file
	* @return string
	*/
	string toFile() const;
	/**
	 * Output operator for a Supplier object
	 * @param os the ostream to output to
	 * @param right the Supplier to output
	 * @return ostream reference to the passed ostream
	 */
	friend ostream& operator<<(ostream& os, const Supplier& s);
};

class Client: public Person{
private:
public:
	/**
	* Default constructor
	* Initializes the pointers to nullptr and some other default values
	*/
	Client();
	/**
	* Parametered constructor
	* @param name
	* @param nif
	* @param address
	* */
	Client(string name,int nif, string address);
	/**
	* read a Supplier instance from an istream
	* @param in the istream to input from
	* @param right the Broker to input to
	* @return istream reference to the passed istream
	*/
	istream & readClient(istream &is, Broker &b);
	/**
	* Write output to text file
	* @return string
	*/
	string toFile() const;
};


class Registered: public Client{
private:
	/**
	* integer value of the points
	*/
	int points;
public:
	/**
	* Default constructor
	* Initializes the pointers to nullptr and some other default values
	*/
	Registered();
	/**
	* Parametered constructor
	* @param points
	*/
	Registered(int points);
	/**
	* Parametered constructor
	* @param name
	* @param nif
	* @param address
	* @param points
	* */
	Registered(string name,int nif, string address,int points);
	/**
	* set the number of Client points
	* @param value of points
	* @return reference to Registered Client
	*/
	Registered& Registered::setPoints(int points);
	/**
	 * Output operator for a Registered object
	 * @param os the ostream to output to
	 * @param right the Registered to output
	 * @return ostream reference to the passed ostream
	 */
	friend ostream& operator<<(ostream& os, const Registered& r);
	/**
	* Write output to text file
	* @return string
	*/
	string toFile() const;
	/**
	* Write output to console
	* @return string
	*/
	string toConsole()const;
};

class Ocasional: public Client{
private:
public:
	/**
	* Default constructor
	* Initializes the pointers to nullptr and some other default values
	*/
	Ocasional();
	/**
	* Parametered constructor
	* @param name
	* @param nif
	* @param address
	* */
	Ocasional(string name,int nif, string address);
	/**
	 * Output operator for a Ocasional object
	 * @param os the ostream to output to
	 * @param right the Ocasional Client to output
	 * @return ostream reference to the passed ostream
	 */
	friend ostream& operator<<(ostream& os, const Ocasional& o);
	/**
	* Write output to text file
	* @return string
	*/
	string toFile() const;
	/**
	* Write output to console
	* @return string
	*/
	string toConsole()const;
};
