#include "Broker.h"
#include "Person.h"
#include "Booking.h"
#include "Offer.h"
#include "Date.h" 

Broker::Broker() :bookingsReceipt(Booking()) {
	changes_offers = changes_suppliers = changes_clients = changes_bookings = false;
	file_offers = file_suppliers = file_clients = file_bookings = "";
	offers = vector<Offer * >(0);
	suppliers = vector<Supplier * >(0);
	clients = vector<Client * >(0);
	bookings = vector<Booking * >(0);
}

Broker::Broker(string main_file) :bookingsReceipt(Booking()) {
	changes_offers = changes_suppliers = changes_clients = changes_bookings = false;
	if (!fileExists(main_file)) {
		throw FileNotFound("Broker's file (" + main_file + ") not found!");
	}
	this->main_file = main_file;
	//import everything
	this->importOffers().importSuppliers().importClients().importBookings();
}

Broker::Broker(string file_offers, string file_suppliers, string file_clients, string file_bookings) :bookingsReceipt(Booking()) {
	changes_offers = changes_suppliers = changes_clients = changes_bookings = false;
	if (!fileExists(file_offers)) {
		throw FileNotFound("Offers file (" + file_offers + ") not found!");
	}
	if (!fileExists(file_suppliers)) {
		throw FileNotFound("Suppliers file (" + file_suppliers + ") not found!");
	}
	if (!fileExists(file_clients)) {
		throw FileNotFound("Clients file (" + file_clients + ") not found!");
	}
	if (!fileExists(file_bookings)) {
		throw FileNotFound("Bookings file (" + file_bookings + ") not found!");
	}
	this->file_suppliers = file_suppliers;
	this->file_offers = file_offers;
	this->file_clients = file_clients;
	this->file_bookings = file_bookings;
}

Broker::~Broker() {}

uint Broker::getSizeSuppliers() const {
	return suppliers.size();
}

uint Broker::getSizeOffers() const {
	return offers.size();
}

uint Broker::getSizeClients() const {
	return clients.size();
}

uint Broker::getSizeBookings() const {
	return bookings.size();
}

vector<Supplier *> Broker::getSuppliers()const {
	return suppliers;
}

vector<Offer * > Broker::getOffers() const{
	return offers;
}

vector<Client *> Broker::getClients() const{
	return clients;
}

vector<Booking *> Broker::getBookings() const{
	return bookings;
}

bool Broker::removeSupplier(Supplier * s) {
	for (sit i = suppliers.begin(); i != suppliers.end(); i++) {
		if ((*i) == s) {
			suppliers.erase(i);
			return true;
		}
	}
	return false;
}

bool Broker::removeOffer(Offer * o) {
	for (oit i = offers.begin(); i != offers.end(); i++) {
		if ((*i) == o) {
			offers.erase(i);
			return true;
		}
	}
	return false;
}

bool Broker::removeClient(Client * c) {
	for (cit i = clients.begin(); i != clients.end(); i++) {
		if ((*i) == c) {
			clients.erase(i);
			return true;
		}
	}
	return false;
}

bool Broker::removeBooking(Booking * b) {
	for (bit i = bookings.begin(); i != bookings.end(); i++) {
		if ((*i) == b) {
			bookings.erase(i);
			return true;
		}
	}
	return false;
}


Broker & Broker::addOffer(Offer * offer) {
	changes_offers = true;
	offers.push_back(offer);
	return *this;
}

Broker & Broker::addSupplier(Supplier * supplier) {
	changes_suppliers = true;
	suppliers.push_back(supplier);
	return *this;
}

Broker & Broker::addClient(Client * client) {
	changes_clients = true;
	clients.push_back(client);
	return *this;
}

Broker & Broker::addBooking(Booking * booking) {
	changes_bookings = true;
	changes_offers = true; //because of added unavailability
	bookings.push_back(booking);
	return *this;
}

Supplier * Broker::findSupplier(uint supplierId) {
	for (sit i = suppliers.begin(); i != suppliers.end(); i++) {
		if ((*i)->getId() == supplierId) {
			return (*i);
		}
	}
	return nullptr;
}

Client * Broker::findClient(uint clientId) {
	for (cit i = clients.begin(); i != clients.end(); i++) {
		if ((*i)->getId() == clientId) {
			return (*i);
		}
	}
	return nullptr;
}

Offer * Broker::findOffer(uint offerId) {
	for (oit i = offers.begin(); i != offers.end(); i++) {
		if ((*i)->getId() == offerId) {
			return (*i);
		}
	}
	return nullptr;
}

Booking * Broker::findBooking(uint bookingId) {
	for (bit i = bookings.begin(); i != bookings.end(); i++) {
		if ((*i)->getId() == bookingId) {
			return (*i);
		}
	}
	return nullptr;
}

Broker & Broker::importOffers() {
	offers = vector<Offer *>(0);
	stringstream ss = readFileSS(file_offers);//read the file -throws FileNotFound
	if (ss.str().size() > 0) {//if the file is not empty
		string offer_type;
		uint count_offers;
		ss >> count_offers;
		cout << "Importing " << count_offers << " Offers..." << endl;
		for (uint i = 0; i < count_offers; i++) {
			Offer *o;
			ss >> offer_type;
			if (offer_type == "Room") {
				o = new Room();
			} else if (offer_type == "Flat") {
				o = new Flat();
			} else if (offer_type == "Apartment") {
				o = new Apartment();
			} else {
				continue;
			}
			o->readOffer(ss, *this);
			o->setPeriod();
			//cout << o->getCity() << " ID: " << o->getId() << " pedriod: " << o->getPeriod() << endl << endl;
			offers.push_back(o);
		}
		cout << "Done" << endl;
	}

	return *this;
}

Broker & Broker::importSuppliers() {
	suppliers = vector<Supplier *>(0);
	stringstream ss = readFileSS(file_suppliers);//read the file -throws FileNotFound
	if (ss.str().size() > 0) {//if the file is not empty
		uint count_suppliers = 0;
		ss >> count_suppliers;
		cout << "Importing " << count_suppliers << " Suppliers...";
		for (uint i = 0; i < count_suppliers; i++) {
			Supplier *s = new Supplier();
			s->readSupplier(ss, *this);
			suppliers.push_back(s);
		}
		cout << "Done" << endl;
	}
	return *this;
}

Broker & Broker::importClients() {
	clients = vector<Client *>(0);
	stringstream ss = readFileSS(file_clients);//read the file -throws FileNotFound
	if (ss.str().size() > 0) {//if the file is not empty
		uint count_clients, temp_points;
		string client_type;
		ss >> count_clients;
		cout << "Importing " << count_clients << " Clients...";
		for (uint i = 0; i < count_clients; i++) {
			Client *c;
			ss >> client_type;
			if (client_type == "Ocasional") {
				c = new Ocasional();
			} else {
				ss >> temp_points;
				c = new Registered(temp_points);
			}
			c->readClient(ss, *this);
			clients.push_back(c);
		}
		cout << "Done" << endl;
	}
	return *this;
}

Broker & Broker::importBookings() {
	bookings = vector<Booking *>(0);//empty the vector
	stringstream ss = readFileSS(file_bookings);//read the file - throws FileNotFound
	if (ss.str().size() > 0) {//if the file is not empty
		uint count_bookings;
		ss >> count_bookings;//the first line of the file should contain the number of bookings to import
		cout << "Importing " << count_bookings << " Bookings...";
		for (uint i = 0; i < count_bookings; i++) {
			Booking *b = new Booking();
			b->readBooking(ss, *this);
			bookingsReceipt.insert(*b);
			bookings.push_back(b);
		}
		cout << "Done" << endl;
	}
	return *this;
}

bool Broker::unsavedChanges() {
	return changes_bookings || changes_clients || changes_offers || changes_suppliers;
}

bool Broker::saveChanges() {
	stringstream ss;//reutiliza-se esta stringstream para cada uma das changes
	if (changes_offers) {
		cout << "Saving Offers ..." ;
		ss.str("");
		ss.clear();
		ss << offers.size() << endl;
		for (oit i = offers.begin(); i != offers.end(); i++) {
			ss << (*i)->toFile() << endl;
		}
		try {
			saveToFile(file_offers, ss.str());
			changes_offers = false;
			cout << "Done" << endl;
		} catch (FileNotFound &e) { cout << e << endl; }
	}
	if (changes_suppliers) {
		cout << "Saving Suppliers ...";
		ss.str("");
		ss.clear();
		ss << suppliers.size() << endl;
		for (sit i = suppliers.begin(); i != suppliers.end(); i++) {
			ss << (*i)->toFile() << endl;
		}
		try {
			saveToFile(file_suppliers, ss.str());
			changes_suppliers = false;
			cout << "Done" << endl;
		} catch (FileNotFound &e) {
			cout << e << endl;
		}
	}
	if (changes_clients) {
		cout << "Saving Clients ...";
		ss.str("");
		ss.clear();
		ss << clients.size() << endl;
		for (cit i = clients.begin(); i != clients.end(); i++) {
			ss << (*i)->toFile() << endl;
		}
		try {
			saveToFile(file_clients, ss.str());
			changes_clients = false;
			cout << "Done" << endl;
		} catch (FileNotFound &e) {
			cout << e << endl;
		}
	}
	if (changes_bookings) {
		cout << "Saving Bookings ...";
		ss.str("");
		ss.clear();
		ss << bookings.size() << endl;
		for (bit i = bookings.begin(); i != bookings.end(); i++) {
			ss << (*(*i)) << endl;
		}
		try {
			saveToFile(file_bookings, ss.str());
			changes_bookings = false;
			cout << "Done" << endl;
		} catch (FileNotFound &e) {
			cout << e << endl;
		}
	}
	return !unsavedChanges();
}

void Broker::addToDiscount(const Offer & o)
{
	onDiscount.push(o);
}

priority_queue<Offer, vector<Offer>, Compare> Broker::getDiscount()
{
	return onDiscount;
}

void Broker::resetDiscount()
{
	priority_queue<Offer, vector<Offer>, Compare> empty;
	onDiscount = empty;
}

tabHInt & Broker::getInactCli(){
	return inactCli;
};

void Broker::inactCliDisplay() const{
	tabHInt::const_iterator it;
	for(it=inactCli.begin();it!=inactCli.end();it++){
		cout << "Client : " << " Id " << (*it)->getId() << " : " << (*it)->getName() <<endl;
	}
} 

void Broker::fillInactClie(us d,us m,us y ){
	inactCli.clear();
	Date h;
	h.setDay(d);
	h.setMonth(m);
	h.setYear(y);
	vector<Client *>::iterator it;
	vector<Booking *>:: iterator ite;
	long periodInact = 30;
	long dayDiff, tempDiff;
	for(it=clients.begin();it!=clients.end();it++){
		dayDiff = periodInact + 1;
		for(ite=bookings.begin();ite!=bookings.end();ite++){
			if((*it)->getId() == (*ite)->getClient()->getId()){ 
				tempDiff = (h.toDays() - (*ite)->get_date().second.toDays());//diferenca de dias
				if (tempDiff < dayDiff) {
					dayDiff = tempDiff;
				}
			}
		}
		if(dayDiff > periodInact){
			inactCli.insert(*it);
		}
	}
}


istream & operator >> (istream & in, Broker & b) {
	try {
		in >> b.file_suppliers >> b.file_offers >> b.file_clients >> b.file_bookings;
		if (!fileExists(b.file_suppliers)) {
			throw FileNotFound("Suppliers file (" + b.file_suppliers + ") not found!");
		}
		if (!fileExists(b.file_offers)) {
			throw FileNotFound("Offers file (" + b.file_offers + ") not found!");
		}
		if (!fileExists(b.file_clients)) {
			throw FileNotFound("Clients file (" + b.file_clients + ") not found!");
		}
		if (!fileExists(b.file_bookings)) {
			throw FileNotFound("Bookings file (" + b.file_bookings + ") not found!");
		}

		//import everything
		b.importOffers().importSuppliers().importClients().importBookings();

	} catch (FileNotFound &e) {
		throw e;
	} catch (...) {
		throw InvalidInput("Unable to read other filenames from stream");
	}
	return in;
}

ostream & operator<<(ostream & out, const Broker & b) {
	out << b.file_offers << b.file_suppliers << b.file_clients << b.file_bookings;
	return out;
}
