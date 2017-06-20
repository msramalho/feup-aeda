#include "Booking.h"
#include "Broker.h"

uint Booking::CURRENT_ID = 1;

Booking::Booking() {
	offer = nullptr;
	client = nullptr;
	status = 0;
	id = 0;
}

Booking::Booking(Offer * o, Client * c, Date start, Date end, uint id) :offer(o), client(c) {
	if (!(start < end) && !(start==end)) {
		throw InvalidInput("start date cannot come after end date");
	}
	if (!o->isAvailable(start, end)) {
		throw InvalidInput("The offer is not available in this timespan");
	}
	o->addUnavailability(start, end);
	interval = pair<Date, Date>(start, end);
	status = 0;
	if (id == 0) {
		this->id = ++Booking::CURRENT_ID;
	} else {
		this->id = id;
		if (Booking::CURRENT_ID < id) {
			Booking::CURRENT_ID = id;//manter o id atualizado
		}
	}
}


bool Booking::cancel_booking(){
	if (status == 0) {
		status = 1;
		return true;
	}
	return false;
}

pair<Date, Date> Booking::get_date() const{
	return interval;
}

Date Booking::get_start() const{
	return interval.first;
}

Date Booking::get_end() const {
	return interval.second;
}

uint Booking::getId() const {
	return id;
}

Client * Booking::getClient() {
	return client;
}

Offer * Booking::getOffer() {
	return offer;
}

Booking & Booking::cancelBooking() {
	status = 1;
	return *this;
}

Booking & Booking::setClient(Client * c) {
	client = c;
	return *this;
}

Booking & Booking::setOffer(Offer * o) {
	offer = o;
	return *this;
}

Booking & Booking::setStart(Date start) {
	if (!(start < interval.second)&& !(interval.second == start)) {
		throw InvalidInput("start date cannot come after end date");
	}
	interval.first = start;
	return *this;
}

Booking & Booking::setEnd(Date end) {
	if (!(interval.first < end) && !(interval.first == end)) {
		throw InvalidInput("start date cannot come after end date");
	}
	interval.second = end;
	return *this;
}

istream & Booking::readBooking(istream & is, Broker &b) {
	Date i,f;
	uint u;
	try {
		is >> u;
		id = u;
		//cout << "READING ID: " << id << ", currently: " << Booking::CURRENT_ID << endl;
		if (Booking::CURRENT_ID < id) {
			Booking::CURRENT_ID = id+1;//manter o id atualizado
		}
		is >> i;
		is >> f;
		this->setEnd(f);
		this->setStart(i);//tem de vir depois para não dar erro
		is >> u;
		this->client = b.findClient(u);//encontra um pointer client pelo id
		is >> u;
		this->offer = b.findOffer(u);//encontra um pointer offer pelo id
	} catch (InvalidInput &e) {
		cout << e << endl;
	}
	return is;
}

string Booking::toConsole() const {
	stringstream ss;
	ss << endl << "Client: " << client->toConsole() << endl << "Offer: " << offer->toConsole() << endl << "Booking between: "
		<< interval.first << " and " << interval.second << endl;
	ss << "Final price: " << offer->calculatePrice(interval.first, interval.second,NULL) << " euros ("
		<< (interval.second - interval.first) << " days)";
	return ss.str();
}

string Booking::toConsole(Broker * b) const {
	stringstream ss;
	ss << endl << "Client: " << client->toConsole() << endl << "Offer: " << offer->toConsole() << endl << "Booking between: "
		<< interval.first << " and " << interval.second << endl;
	ss << "Final price: " << offer->calculatePrice(interval.first, interval.second, &(*b)) << " euros (" 
		<< (interval.second - interval.first) << " days)";
	return ss.str();
}

ostream & operator << (ostream & os,const Booking & b) {
	os << b.id << ' ' << b.interval.first << ' ' << b.interval.second << ' ' << b.client->getId() << ' ' << b.offer->getId() << endl;
	return os;
}


bool Booking::operator<(const Booking &right) const {
	return (client->getName() < right.client->getName()) 
		|| (client->getName() == right.client->getName() && interval.first < right.interval.first)
		|| (client->getName() == right.client->getName() && interval.first == right.interval.first && interval.second < right.interval.second);
}

bool Booking::operator == (const Booking &right) const {
	return id == right.getId();/* client->getId() == right.client->getId() &&
			offer->getId() == right.offer->getId() &&
			interval.first == right.interval.first &&
			interval.second == right.interval.second;*/
}