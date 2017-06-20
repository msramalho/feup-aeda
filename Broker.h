#pragma once

#include <vector>
#include <queue>
#include <sstream>
#include "utils.h"
#include "BST.h"
#include "Offer.h"
#include <unordered_set>
using namespace std;

class Booking;
class Supplier;
class Broker;
class Offer;
class Client;


template<>
struct hash<Client *> {
	size_t operator()(const Client * c) const{
		size_t res = c->getId();
		string name = c->getName();
		string::iterator i = name.begin();
		for (; i != name.end(); i++) {
			res += (size_t)(pow(43, (name.end() - i)) * (int)(*i));
		}
		return res;
	}
};

typedef unordered_set<Client *, hash<Client *>> tabHInt;
typedef vector<Supplier *>::iterator sit;
typedef vector<Offer *>::iterator oit;
typedef vector<Client *>::iterator cit;
typedef vector<Booking *>::iterator bit;

class Broker {
private:
	/**
	* double balance, the output of all the trades, this value is saved in the suppliers' file
	*/
	double balance;
	/**
	* string main_file points to the other 4 files
	*/
	string main_file;
	/**
	* string variables to save the file name of the files that hold the data
	*/
	string file_offers, file_suppliers, file_clients, file_bookings;
	/**
	* a vector containing all the suppliers for a Broker instance
	*/
	vector<Supplier *> suppliers;
	/**
	* a vector containing all the offers for a Broker instance
	*/
	vector<Offer *> offers;
	/**
	* a vector containing all the clients for a Broker instance
	*/
	vector<Client *> clients;
	/**
	* a vector containing all the bookings for a Broker instance
	*/
	vector<Booking *> bookings;
	/**
	* an hashtable that contains all the inactive clients 
	*/
	tabHInt inactCli;
public:
	/**
	* BST for the first task of the second part of the project
	*/
	BST<Booking> bookingsReceipt;
	/**
	* a priority_queue of offers that are in discount
	*/
	priority_queue<Offer, vector<Offer>, Compare> onDiscount;

	/**
	* Boolean variables to flag unsaved changes made to the respective vector
	*/
	bool changes_offers, changes_suppliers, changes_clients, changes_bookings;
	/**
	* A constructor.
	* Default constructor sets the default params
	*/

	Broker();
	/**
	* A constructor.
	* Constructor that finds the four files' names from one main file
	* @param main_file the file where the other file names are
	*/
	Broker(string main_file);
	/**
	* A constructor.
	* Constructor that receives the four files' names
	* @param file_offers the file where the offers data is
	* @param file_suppliers the file where the suppliers data is
	* @param file_clients the file where the clients data is
	* @param file_bookings the file where the bookings data is
	*/
	Broker(string file_offers, string file_suppliers, string file_clients, string file_bookings);
	/**
	* A destructor for a Broker instance
	*/
	~Broker();

	/**
	* get the size of the suppliers vector
	* @return unsigned int with the vector size
	*/
	uint getSizeSuppliers()const;
	/**
	* get the size of the offers vector
	* @return unsigned int with the vector size
	*/
	uint getSizeOffers()const;
	/**
	* get the size of the clients vector
	* @return unsigned int with the vector size
	*/
	uint getSizeClients()const;
	/**
	* get the size of the bookings vector
	* @return unsigned int with the vector size
	*/
	uint getSizeBookings()const;

	/**
	* get a copy of the suppliers vector
	* @return vector<Supplier *> containing a copy of the suppliers vector
	*/
	vector<Supplier *> getSuppliers() const;
	/**
	* get a copy of the offers vector
	* @return vector<Offer *> containing a copy of the offers vector
	*/
	vector<Offer *> getOffers() const ;
	/**
	* get a copy of the clients vector
	* @return Client<Booking *> containing a copy of the clients vector
	*/
	vector<Client *> getClients() const;
	/**
	* get a copy of the bookings vector
	* @return vector<Booking *> containing a copy of the bookings vector
	*/
	vector<Booking *> getBookings() const;
	/*
	* returns the hashtable of inactive clients
	*/
	tabHInt & getInactCli();
	/*
	* displays the name of the clients currently in the inactive hashtable
	*/
	void inactCliDisplay()const;
	/**
	* Removes a supplier from the broker's suppliers by its Id
	* @see Supplier::operator==
	* @param s the Supplier pointer to search and remove
	* @return bool if the supplier was removed
	*/
	bool removeSupplier(Supplier* s);
	/**
	* Removes a offer from the broker's offers by its Id
	* @see Offer::operator==
	* @param o the Offer pointer to search and remove
	* @return bool if the offer was removed
	*/
	bool removeOffer(Offer * o);
	/**
	* Removes a client from the broker's clients by its Id
	* @see Client::operator==
	* @param c the Client pointer to search and remove
	* @return bool if the client was removed
	*/
	bool removeClient(Client * c);
	/**
	* Removes a booking from the broker's bookings by its Id
	* @see Booking::operator==
	* @param b the Booking pointer to search and remove
	* @return bool if the booking was removed
	*/
	bool removeBooking(Booking* b);

	/**
	* Ads a new Offer to the offers vector
	* @param offer the Offer to insert, pointer
	* @return Broker& for chain calling
	*/
	Broker & addOffer(Offer* offer);
	/**
	* Ads a new Supplier to the suppliers vector
	* @param supplier the Supplier to insert, pointer
	* @return Broker& for chain calling
	*/
	Broker & addSupplier(Supplier* supplier);
	/**
	* Ads a new Client to the clients vector
	* @param client the Client to insert, pointer
	* @return Broker& for chain calling
	*/
	Broker & addClient(Client* client);
	/**
	* Ads a new Booking to the bookings vector
	* @param booking the Booking to insert, pointer
	* @return Broker& for chain calling
	*/
	Broker & addBooking(Booking* booking);

	/**
	* Finds a supplier by id
	* @param supplierId the id of the Supplier pointer to return
	* @return Supplier*
	*/
	Supplier *findSupplier(uint supplierId);
	/**
	* Finds a client by id
	* @param clientId the id of the client pointer to return
	* @return Client*
	*/
	Client *findClient(uint clientId);
	/**
	* Finds an offer by id
	* @param offerId the id of the offer pointer to return
	* @return Offer*
	*/
	Offer *findOffer(uint offerId);
	/**
	* Finds a booking by id
	* @param bookingId the id of the booking pointer to return
	* @return Booking*
	*/
	Booking *findBooking(uint bookingId);

	/**
	 * Reads offers from a file
	 * @throws FileNotFound exception
	 * @return Broker& the current broker
	 */
	Broker & importOffers();

	/**
	 * Reads the suppliers from a file
	 * @throws FileNotFound exception
	 * @return Broker& the current broker
	 */
	Broker & importSuppliers();
	/**
	 * Reads the clients from a file
	 * @throws FileNotFound exception
	 * @return Broker& the current broker
	 */
	Broker & importClients();
	/**
	* Reads the bookings from a file
	* @throws FileNotFound exception
	* @return Broker& the current broker
	*/
	Broker & importBookings();

	/**
	* Checks if there are any unsaved changes to the broker's data
	* @return bool true if there are unsaved changes, false otherwise;
	*/
	bool unsavedChanges();
	/**
	* Saves any unsaved changes in the broker's data
	* @return bool true if there are no unsaved changes, false otherwise;
	*/
	bool saveChanges();
	
	/**
	* Input operator for a Broker object in the format: file_suppliers file_offers file_clients file_bookings
	* @param in the istream to input from
	* @param right the Broker to input to
	* @return istream reference to the passed istream
	*/
	friend istream& operator>>(istream &in, Broker &b);
	/**
	* Output operator for a Broker object's file names
	* @param out the ostream to output to
	* @param right the Broker to output
	* @return ostream reference to the passed ostream
	*/
	friend ostream& operator<<(ostream &out, const Broker &b);
	/**
	* adds a offer to de discount priority_queue.
	* @param offer to be added to discounts.
	*/
	void addToDiscount(const Offer &o);
	/**
	* to acess the offers that have a discount.
	* @return the offers on sale.
	*/
	priority_queue<Offer, vector<Offer>, Compare> getDiscount();
	/*
	* to reset the priority_queue of discounts
	*/
	void resetDiscount();
	/*
	* to fill the hashtable of inactive clients
	*/
	void fillInactClie(us d, us m, us y);
};
