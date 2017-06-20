#include "Offer.h"

#include "Broker.h"
#include <queue>

using namespace std;

//Offer:
int Offer::CURRENT_ID =1;

Offer::Offer() {
	//id = Offer::CURRENT_ID++;
}

Offer::Offer(int numU, string c, string t, float p, vector<pair<Date,Date>> undisp, int id):
		numUni(numU),city(c),typeUni(t),price(p),unavailability(undisp){

	if (id == 0) {
		this->id = ++Offer::CURRENT_ID;
	} else {
		this->id = id;
		if (Offer::CURRENT_ID < id) {
			Offer::CURRENT_ID = id;//manter o id atualizado
		}
	}
}

Offer & Offer::addUnavailability(Date iDate, Date fDate){
	//cout << endl << iDate << " - " << fDate << endl;
	if (!(iDate < fDate) && !(iDate == fDate)){
		throw InvalidInput("start date cannot come after end date");
	}

	unavailability.push_back(pair<Date,Date>(iDate,fDate));
	return *this;
}

Offer & Offer::elimUnavailability(Date iDate, Date fDate){

	bool found=false;
	for(uint i=0; i < unavailability.size();i++)
	{
		if(unavailability[i].first == iDate && unavailability[i].second == iDate)
		{
			unavailability.erase(unavailability.begin()+i);
			found = true;
		}
	}
	if(found == false) throw InvalidInput("No such period is unavailable");
	return *this;
}

int Offer::getId() const {
	return id;
}

Offer & Offer::setId(int id){
	this->id = id;
	return *this;
}

Offer & Offer::setNumUni(int numUni) {
	this->numUni = numUni;
	return *this;
}

Offer & Offer::setCity(string city) {
	this->city = city;
	return *this;
}

Offer & Offer::setTypeUni(string typeUni) {
	this->typeUni = typeUni;
	return *this;
}

Offer & Offer::setPrice(float price) {
	this->price = price;
	return *this;
}

double Offer::ref(priority_queue<Offer, vector<Offer>, Compare>  * temp) {
	double discount_value = 1;
	double i = 0.8;

	while (!(*temp).empty())
	{
		if ((*temp).top().getId() == getId())
		{
			discount_value = (1 - i);
			if (discount_value <= 0)
				discount_value = 1;
			break;
		}
		i -= 0.1;
		(*temp).pop();
	}
	return discount_value;

}



double Offer::calculatePrice(Date start, Date end, Broker * broker) {
	ull days = end - start;


	double discount = Offer::ref(&(broker->getDiscount()));
	int i = 1;

	if (typeUni == "day") 
	{
		if (getSaleValue() == true)
			return (price / numUni) * days * discount;
		else 
			return (price / numUni) * days;
	} 
	else if (typeUni == "week")
	{
		if (getSaleValue() == true)
			return (price / (numUni * 7)) * days * discount;
		else
			return (price / (numUni * 7)) * days;
	}
	else if (typeUni == "month") 
	{
		if (getSaleValue() == true)
			return (price / (numUni * 31)) * days* discount;
		else
			return (price / (numUni * 31)) * days;
	}
	return 0.0f;
}


float Offer::getPrice()const{
	//TODO tem de ter em conta o tipo de unidades
	return price * numUni;
}

string Offer::getCity()const{return city;}

vector<pair<Date,Date>> Offer::getUnavailability()const{return unavailability;}
string Offer::getTypeUni()const{return typeUni;}

int Offer::getNumUni()const{return numUni;}

istream & Offer::readOffer(istream &is, Broker &b) {
	string temp;
	Date startD, endD;
	uint i;
	try {
		is >> temp;
		this->city = temp;
		is >> i;
		this->numUni = i;
		is >> temp;
		this->typeUni = temp;
		is >> i;
		//this->unavailability.size() = i;// Não necessário
		for (uint j = 0; j < i; j++) {
			is >> startD; is >> endD;
			try {
				this->addUnavailability(startD, endD);
			} catch (InvalidInput &e) {
				throw e;
			}
		}
	} catch (InvalidInput &e) { cout << e; } catch (exception &e) { cout << "Error imporing offer: " << e.what() << endl; }
	
	return is;
}

string Offer::toFile() const {
	stringstream ss;
	ss << id << ' ' << numUni << ' ' << typeUni << ' ' << city << ' ' << price << endl <<
		unavailability.size() << ' '  << unavailability << endl;
	return ss.str();
}

string Offer::toConsole() const {
	stringstream os;
	os << "City: " << city << endl << "Num of Uni: " << numUni << endl << "Type of Uni: " << typeUni << endl << "Num of bookings: " << unavailability.size() << ' ';
	for (uint i = 0; i < unavailability.size(); i++) {
		os << unavailability[i].first << ' ' << unavailability[i].second <<  " |   ";
	}
	os << endl;
	return os.str();
}

bool Offer::isAvailable(Date start, Date end) {
	if (end < start) {//start must come before end
		Date temp = start;
		start = end;
		end = temp;
	}
	vector<pair<Date, Date>>::iterator vit = unavailability.begin();
	for (vit; vit != unavailability.end(); vit++) {
		if (!((*vit).second < start || end < (*vit).first)) {//if the start date is intercepted by this unavailabilty
			return false;
		}
	}
	return true;
}

void Offer::setPeriod()
{
	Date hoje = Date(2, 1, 2017);
	sort(unavailability.begin(), unavailability.end());
	/*
	for (vector<pair<Date, Date>>::iterator it = unavailability.begin(); it != unavailability.end(); it++)
	{
		cout << " " << *it;
	}
	*/
	if (unavailability.size() == 0) {
		period = 0;
		return;
	}
	else
	{
		period = (int)hoje.operator-(unavailability[unavailability.size() - 1].second); // ou seja hoje - o mais actual booking
		//period = unavailability[unavailability.size() - 1].second.operator-(hoje);
	}
	return;
}

int Offer::getPeriod() const
{
	return period;
}

bool Offer::operator<(const Offer & o)
{
	return (this->period > o.period);
}

bool Offer::getSaleValue() const
{
	return sale;
}

void Offer::setSaleValue(bool v)
{
	sale = v;
	return;
}




ostream & operator <<(ostream & os, const Offer &o) {
	os << o.getCity() << ' ' << o.getNumUni() << ' ' << o.getTypeUni() << ' ' << o.getUnavailability().size();
	for (uint i = 0; i < o.getUnavailability().size(); i++) {
		os << o.getUnavailability()[i].first << ' ' << o.getUnavailability()[i].second << ' ';
	}
	os << endl;
	return os;
}

//Room:
Room::Room() :Offer() {}

Room::Room(int numU, string c, string t, float price, vector<pair<Date, Date>> disp, 
	string typ, bool h, bool shdHouse, bool bf, int id) :Offer(numU, c, t, price, disp, id),
	type(typ), hotel(h), sharedHouse(shdHouse), bedAndBreakfast(bf) {}

bool Room::getHotelVal()const {return hotel;}

bool Room::getSharedHouseVal()const {return sharedHouse;}

bool Room::getBedAndBreakfastVal()const{return bedAndBreakfast;}

Room & Room::setType(string type) {
	this->type = type;
	return *this;
}

Room & Room::setHotel(bool hotel) {
	this->hotel = hotel;
	return *this;
}

Room & Room::setSharedHouse(bool sharedHouse) {
	this->sharedHouse = sharedHouse;
	return *this;
}

Room & Room::setBedAndBreakfast(bool bedAndBreakfast) {
	this->bedAndBreakfast = bedAndBreakfast;
	return *this;
}

string Room::toFile() const {
	stringstream ss;
	string temp_city = city, from = " ", to = "_";
	replace(temp_city, from, to);
	ss << "Room " << id << ' ' << numUni << ' ' << typeUni << ' ' << temp_city << ' ' << price << ' '
		<< type << ' ' << hotel << ' ' << sharedHouse <<  ' ' << bedAndBreakfast << endl <<
		unavailability.size() << ' ' << unavailability;
	return ss.str();
}
string Room::toConsole() const {
	stringstream ss;
	ss << "Room Id: " << id << ", numUni: " << numUni << ", typeUni: " << typeUni << ", city:" << city
		<< ", price: " << price << "€, roomType: " << type << ", Location: ";
	if (hotel) {
		ss << "hotel";
	} else if (sharedHouse) {
		ss << "sharedHouse";
	} else if (bedAndBreakfast) {
		ss << "bedAndBreakfast";
	}
	ss << endl << "->Unavailiabilties (pairs of start, end): " << unavailability;
	return ss.str();
}
istream & Room::readOffer(istream & is, Broker & br) {
	Date startD, endD;
	string s;
	uint i;
	float p;
	bool b;
	try {
		is >> i; id = i;
		is >> i; numUni = i;
		is >> s; typeUni = s;
		is >> s; city = s;
		string from = "_", to = " ";
		replace(city, from, to);
		is >> p; price = p;
		is >> s; type = s;
		is >> b; hotel = b;
		is >> b; sharedHouse = b;
		is >> b; bedAndBreakfast = b;

		if (Offer::CURRENT_ID < id) {
			Offer::CURRENT_ID = id;//manter o id atualizado
		}

		is >> i;
		//this->unavailability.size() = i;// Não necessário
		for (uint j = 0; j < i; j++) {
			is >> startD; is >> endD;
			try {
				this->addUnavailability(startD, endD);
			} catch (InvalidInput &e) {
				throw e;
			}
		}
	} catch (InvalidInput &e) { cout << e; } catch (exception &e) { cout << "Error imporing offer: " << e.what() << endl; }

	return is;
}
istream & operator >> (istream & in, Room & r) {
	int id, numUni;
	uint count_unavailability;
	string typeUni, city, type;
	float price;
	bool hotel, sharedHouse, bedAndBreakfast;
	Date start, end;

	in >> id >> numUni >> typeUni >> city >> price >> type >> hotel >> sharedHouse >> bedAndBreakfast;
	in >> count_unavailability;
	r.setId(id).setNumUni(numUni).setTypeUni(typeUni).setCity(city).setPrice(price);//offer attributes
	r.setType(type).setHotel(hotel).setSharedHouse(sharedHouse).setBedAndBreakfast(bedAndBreakfast);//room attributes
	for (uint i = 0; i < count_unavailability; i++) {//imports the unavailabilities
		try {
			in >> start >> end;
			r.addUnavailability(start, end);
		} catch (InvalidInput &e) {
			cout << e.message << ", while importing offer (room) with ID " << id << " (pair ignored)" << endl;
		}
	}
	return in;
}

ostream & operator <<(ostream & os, const Room &o) {
	os << "Room Id: " << o.id << ", numUni: " << o.numUni << ", typeUni: " << o.typeUni << ", city:" << o.city
		<< ", price: " << o.price << "€, roomType: " << o.type << ", Location: ";
	if (o.hotel) {
		os << "hotel";
	} else if (o.sharedHouse) {
		os << "sharedHouse";
	} else if (o.bedAndBreakfast) {
		os << "bedAndBreakfast";
	}
	os << endl << "->Unavailiabilties (pairs of start, end): " << o.unavailability << endl;
	return os;
}



Flat::Flat() :Offer() {}

//Flat:
Flat::Flat(int numU, string c, string t, float price, vector<pair<Date, Date>> disp,
	bool fr, bool k, bool br, int id) : Offer(numU, c, t, price, disp, id),
	fRoom(fr), kitchen(k), bathroom(br) {}

Flat & Flat::setFRoom(bool fRoom) {
	this->fRoom = fRoom;
	return *this;
}

Flat & Flat::setKitchen(bool kitchen) {
	this->kitchen = kitchen;
	return *this;
}

Flat & Flat::setfBathroom(bool bathroom) {
	this->bathroom = bathroom;
	return *this;
}

string Flat::toFile() const {
	stringstream ss;
	string temp_city = city, from = " ", to = "_";
	replace(temp_city, from, to);
	ss << "Flat " << id << ' ' << numUni << ' ' << typeUni << ' ' << temp_city << ' ' << price << ' '
		<< fRoom << ' ' << kitchen << ' ' << bathroom  << endl <<
		unavailability.size() << ' ' << unavailability;
	return ss.str();
}

string Flat::toConsole() const {
	stringstream ss;
	ss << "Flat Id: " << id << ", numUni: " << numUni << ", typeUni: " << typeUni << ", city:" << city
		<< ", price: " << price
		<< "€, has bedroom?: " << (fRoom ? "yes" : "no")
		<< ", has kitchen?: " << (kitchen ? "yes" : "no")
		<< ", has bathroom?: " << (bathroom ? "yes" : "no");
	ss << endl << "->Unavailiabilties (pairs of start, end): " << unavailability;
	return ss.str();
}

istream & Flat::readOffer(istream & is, Broker & br) {
	Date startD, endD;
	string s;
	uint i;
	float p;
	bool b;
	try {
		is >> i; id = i;
		is >> i; numUni = i;
		is >> s; typeUni = s;
		is >> s; city = s;
		string from = "_", to = " ";
		replace(city, from, to);
		is >> p; price = p;
		is >> b; fRoom = b;
		is >> b; kitchen = b;
		is >> b; bathroom = b;

		if (Offer::CURRENT_ID < id) {
			Offer::CURRENT_ID = id;//manter o id atualizado
		}

		is >> i;
		//this->unavailability.size() = i;// Não necessário
		for (uint j = 0; j < i; j++) {
			is >> startD; is >> endD;
			try {
				this->addUnavailability(startD, endD);
			} catch (InvalidInput &e) {
				throw e;
			}
		}
	} catch (InvalidInput &e) { cout << e; } catch (exception &e) { cout << "Error imporing offer: " << e.what() << endl; }

	return is;
}

istream & operator >> (istream & in, Flat & f) {
	int id, numUni;
	uint count_unavailability;
	string typeUni, city;
	float price;
	bool fRoom, kitchen, bathroom;
	Date start, end;

	in >> id >> numUni >> typeUni >> city >> price >> fRoom >> kitchen >> bathroom;
	in >> count_unavailability;
	f.setId(id).setNumUni(numUni).setTypeUni(typeUni).setCity(city).setPrice(price);//offer attributes
	f.setFRoom(fRoom).setKitchen(kitchen).setfBathroom(bathroom);//flat attributes
	for (uint i = 0; i < count_unavailability; i++) {//imports the unavailabilities
		try {
			in >> start >> end;
			f.addUnavailability(start, end);
		} catch (InvalidInput &e) {
			cout << e.message << ", while importing offer (flat) with ID " << id << " (pair ignored)" << endl;
		}
	}
	return in;
}

Apartment::Apartment():Offer() {}

ostream & operator <<(ostream & os, const Flat &o) {
	os << "Flat Id: " << o.id << ", numUni: " << o.numUni << ", typeUni: " << o.typeUni << ", city:" << o.city
		<< ", price: " << o.price 
		<< "€, has bedroom?: " << (o.fRoom ? "yes" : "no") 
		<< ", has kitchen?: " << (o.kitchen ? "yes" : "no")
		<< ", has bathroom?: " << (o.bathroom ? "yes" : "no");
	os << endl << "->Unavailiabilties (pairs of start, end): " << o.unavailability << endl;
	return os;
}
//Apartment:
Apartment::Apartment(int numU, string c, string t, float price, vector<pair<Date, Date>> disp,
	vector<pair<string, bool>> rm, bool s, bool k, bool lr, int id) : Offer(numU, c, t, price, disp, id),
	rooms(rm), kitchen(k), livingRoom(lr) {}

Apartment & Apartment::addRoom(string room_type, bool is_suite) {
	rooms.push_back(pair<string, bool>(room_type, is_suite));
	return *this;
}

bool Apartment::getKitchenVal()const {return kitchen;}

bool Apartment::getLivingRoomVal()const {return livingRoom;}

Apartment & Apartment::setKitchen(bool kitchen) {
	this->kitchen = kitchen;
	return *this;
}

Apartment & Apartment::setLivingRoom(bool livingRoom) {
	this->livingRoom = livingRoom;
	return *this;
}

string Apartment::toFile() const {
	stringstream ss;
	string temp_city = city, from = " ", to = "_";
	replace(temp_city, from, to);
	ss << "Apartment " << id << ' ' << numUni << ' ' << typeUni << ' ' << temp_city << ' ' << price << ' '
		<< kitchen << ' ' << livingRoom << endl <<
		unavailability.size() << ' ' << unavailability << endl <<
		rooms.size() << ' ' << rooms;
	return ss.str();
}

string Apartment::toConsole() const {
	stringstream ss;
	ss << "Apartment Id: " << id << ", numUni: " << numUni << ", typeUni: " << typeUni << ", city:" << city
		<< ", price: " << price
		<< "€, has kitchen?: " << (kitchen ? "yes" : "no")
		<< ", has living Room?: " << (livingRoom ? "yes" : "no");
	ss << endl << "->Unavailiabilties (pairs of start, end): " << unavailability;
	ss << endl << "->Rooms (pairs of type, is suite?): " << rooms;
	return ss.str();
}

istream & Apartment::readOffer(istream & is, Broker & br) {
	Date startD, endD;
	string s;
	uint i;
	float p;
	bool b;
	try {
		is >> i; id = i;
		is >> i; numUni = i;
		is >> s; typeUni = s;
		is >> s; city = s;
		string from = "_", to = " ";
		replace(city, from, to);
		is >> p; price = p;
		is >> b; kitchen = b;
		is >> b; livingRoom = b;

		if (Offer::CURRENT_ID < id) {
			Offer::CURRENT_ID = id;//manter o id atualizado
		}

		is >> i;
		//this->unavailability.size() = i;// Não necessário
		for (uint j = 0; j < i; j++) {
			is >> startD; is >> endD;
			try {
				this->addUnavailability(startD, endD);
			} catch (InvalidInput &e) {
				throw e;
			}
		}

		is >> i;
		//vector<pair<string,bool>> rooms;
		//this->rooms.size() = i;// Não necessário
		for (uint j = 0; j < i; j++) {
			is >> s; is >> b;
			this->addRoom(s, b);
		}
	} catch (InvalidInput &e) { cout << e; } catch (exception &e) { cout << "Error imporing offer: " << e.what() << endl; }

	return is;
}

istream & operator >> (istream & in, Apartment & a) {
	int id, numUni;
	uint count;
	string typeUni, city;
	float price;
	bool kitchen, livingRoom;
	Date start, end;

	in >> id >> numUni >> typeUni >> city >> price >> kitchen >> livingRoom;
	a.setId(id).setNumUni(numUni).setTypeUni(typeUni).setCity(city).setPrice(price);//offer attributes
	a.setKitchen(kitchen).setLivingRoom(livingRoom);//apartment attributes
	in >> count;
	for (uint i = 0; i < count; i++) {//imports the unavailabilities
		try {
			in >> start >> end;
			a.addUnavailability(start, end);
		} catch (InvalidInput &e) {
			cout << e.message << ", while importing offer (apartment) with ID " << id << " (pair ignored)" << endl;
		}
	}

	string room;
	bool suite;
	in >> count;
	for (uint i = 0; i < count; i++) {//imports the rooms
		in >> room >> suite;
		a.addRoom(room, suite);
	}

	return in;
}

ostream & operator <<(ostream & os, const Apartment &o) {
	os << "Flat Id: " << o.id << ", numUni: " << o.numUni << ", typeUni: " << o.typeUni << ", city:" << o.city
		<< ", price: " << o.price
		<< "€, has kitchen?: " << (o.kitchen ? "yes" : "no")
		<< ", has living Room?: " << (o.livingRoom ? "yes" : "no");
	os << endl << "->Unavailiabilties (pairs of start, end): " << o.unavailability << endl;
	return os;
}