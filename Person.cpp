#include "Person.h"
#include "Broker.h"
#include "Offer.h"

int Person::CURRENT_ID = 1;
usi Person::SETW = 25;

//Person
Person::Person() {
	id = 0;
	name = "NONE";
	nif = 0;
	address = "NONE";
}

Person::Person(string name,int nif,string morada, int id){
	this->name = name;
	this->nif = nif;
	this->address = morada;
	if (id == 0) {
		this->id = Person::CURRENT_ID++;
	} else {
		this->id = id;
		if (Person::CURRENT_ID <= id) {
			Person::CURRENT_ID = id + 1;//manter o id atualizado
		}
	}
}

Person::~Person(){}

int Person::getId() const{
	return id;
}

string Person::getName() const{
	return name;
}

int Person::getNif(){
	return nif;
}

string Person::getAddress(){
	return address;
}


void Person::setName(string name){
	this->name = name;
}

void Person::setId(int id){
	this->name = name;
}

void Person::setNif(int nif){
	this->name = name;
}

void Person::setAddress(string address){
	this->address = address;
}

string Person::toFile() const {
	stringstream ss;
	ss << id << nif << endl << name << endl << address << endl;
	return ss.str();
}

string Person::toConsole() const {
	stringstream os;
	os << setw(Supplier::SETW) << id;
	os << setw(Supplier::SETW) << name;
	os << setw(Supplier::SETW) << nif;
	os << setw(Supplier::SETW) << address;
	os << setw(Supplier::SETW) << "---";
	return os.str();
}

bool Person::operator==(const Person & p) const {
	return id == p.id;
}

ostream & operator<<(ostream & os, const Person & p1) {
	//TODO
	return os;
}
//Supplier
Supplier::Supplier() {
	offers = vector<Offer *>(0);
}

Supplier::Supplier(string name, int nif, string address): Person(name,nif,address){
	offers = vector<Offer *>(0);
}

Supplier & Supplier::addOffer(Offer * o) {
	offers.push_back(o);
	return *this;
}

vector<Offer *> Supplier::getOffers() {
	return offers;
}

vector<uint> Supplier::getOfferIds() {
	vector<uint> result(0);
	for (oit i = offers.begin(); i != offers.end(); i++) {
		result.push_back((*i)->getId());
	}
	return result;
}

string Supplier::toFile() const {
	stringstream ss;
	ss << id << ' ' << nif << endl << name << endl << address << endl << offers.size() << " " << offers << endl;
	return ss.str();
}

istream & Supplier::readSupplier(istream &is, Broker &b) {
	vector<int> offerIDs;
	int id, nif, offerID;
	uint count_offers;
	string name, address, line;
	is >> id >> nif;
	is.ignore(256, '\n');
	getline(is, name);
	getline(is, address);
	is >> count_offers;
	for (uint i = 0; i < count_offers; i++) {//imports the suppliers
		is >> offerID;
		offerIDs.push_back(offerID);
	}

	this->id = id;
	if (this->id >= Supplier::CURRENT_ID) {
		Supplier::CURRENT_ID = this->id + 1;
	}
	this->name = name;
	this->address = address;
	this->nif = nif;

	vector<int>::iterator it;
	for (it = offerIDs.begin(); it != offerIDs.end(); it++) {
		this->offers.push_back(b.findOffer(*it));
	}

	return is;
}

ostream & operator<<(ostream & os, const Supplier & s) {
	os << setw(Supplier::SETW) << s.id;
	os << setw(Supplier::SETW) << s.name;
	os << setw(Supplier::SETW) << s.nif;
	os << setw(Supplier::SETW) << s.address;
	os << setw(Supplier::SETW);
	for (vector<Offer*>::const_iterator i = s.offers.begin(); i != s.offers.end(); i++) {
		os << (*i)->getId() << " " ;
	}
	//os << setw(Supplier::SETW) << s.offers;
	return os;
}



//Client
Client::Client():Person() {}

Client::Client(string name,int nif,string address): Person(name,nif,address){}

// exampleClient
// ocasional 15 12234
// Joao Silva
// Rua das Couves
// 1234*
istream & Client::readClient(istream &is, Broker &b) {
	int id, nif;
	string name, address;

	is >> id >> nif;
	is.ignore(256, '\n');
	getline(is, name);
	getline(is, address);

	//a parte de verificar se é ocasional ou não tem de ser feita no broker, para saber que tipo de cliente criar
	this->id = id;
	if (Person::CURRENT_ID <= id) {
		Person::CURRENT_ID = id+1;//manter o id atualizado
	}
	this->name = name;
	this->address = address;
	this->nif = nif;

	return is;
}

string Client::toFile() const {
	stringstream ss;
	ss << id << ' ' << nif << endl << name << endl << address << endl;
	return ss.str();
}

//Registered

Registered::Registered():Client() { points = 0; }

Registered::Registered(int points) :points(points) {}

Registered::Registered(string name, int nif, string address, int points) : Client(name, nif, address) {
	this->points = points;
}

Registered& Registered::setPoints(int points) {
	this->points = points;
	return *this;
}

string Registered::toFile() const {
	stringstream ss;
	ss << "Registered " << points << ' '  << id << ' ' << nif << endl << name << endl << address << endl;
	return ss.str();
}

string Registered::toConsole() const {
	stringstream os;
	os << setw(Supplier::SETW) << id;
	os << setw(Supplier::SETW) << name;
	os << setw(Supplier::SETW) << nif;
	os << setw(Supplier::SETW) << address;
	os << setw(Supplier::SETW) << points;
	return os.str();
}

ostream & operator<<(ostream & os, const Registered & r) {
	os << setw(Supplier::SETW) << r.id;
	os << setw(Supplier::SETW) << r.name;
	os << setw(Supplier::SETW) << r.nif;
	os << setw(Supplier::SETW) << r.address;
	os << setw(Supplier::SETW) << r.points;
	return os;
}

//Ocasional
Ocasional::Ocasional() {}

Ocasional::Ocasional(string name, int nif, string address): Client(name,nif,address){

}

ostream & operator<<(ostream & os, const Ocasional & o) {
	os << setw(Supplier::SETW) << o.id;
	os << setw(Supplier::SETW) << o.name;
	os << setw(Supplier::SETW) << o.nif;
	os << setw(Supplier::SETW) << o.address;
	os << setw(Supplier::SETW) << "---";
	return os;
}

string Ocasional::toFile() const {
	stringstream ss;
	ss << "Ocasional " << id << ' ' << nif << endl << name << endl << address << endl;
	return ss.str();
}

string Ocasional::toConsole() const {
	stringstream os;
	os << setw(Supplier::SETW) << id;
	os << setw(Supplier::SETW) << name;
	os << setw(Supplier::SETW) << nif;
	os << setw(Supplier::SETW) << address;
	os << setw(Supplier::SETW) << "---";
	return os.str();
}


