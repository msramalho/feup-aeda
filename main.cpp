
#include "main.h"

//---------------------------------------------------------Suppliers

bool getSupplierById(Supplier *& sup) {
	uint id = -1;
	sup = nullptr;
	while (sup == nullptr) {//find a supplier
		cinValue(id, "What's the supplier's ID (0 to stop)?");
		if (id == 0) {
			return false;
		}
		sup = broker.findSupplier(id);
		if (sup == nullptr) {
			cout << "No supplier for that ID" << endl;
		}
	}
	return true;
}

bool addSupplier() {
	string name, address;
	int nif;
	//get supplier name
	cinValueStr(name, "What's the new supplier's NAME (abort to stop)?");
	if (toLower(name) == "abort") {
		return false;
	}

	//get supplier address
	cinValueStr(address, "What's the new supplier's ADDRESS (abort to stop)?");
	if (toLower(address) == "abort") {
		return false;
	}

	//get supplier NIF
	cinValue(nif, "What's the new supplier's NIF/VAT (0 to stop)?");
	if (nif == 0) {
		return false;
	}

	Supplier * s = new Supplier(name, nif, address);
	broker.addSupplier(s);
	cout << "Supplier: " << name << " added!" << endl;
	return true;
}

bool editSupplier() {
	Supplier* sup = nullptr;
	if (!getSupplierById(sup)) {
		return false;
	}

	string name, address;
	int nif;
	//get supplier name
	cinValueStr(name, "What's the supplier's new NAME (abort to stop, i to ignore)?");
	if (toLower(name) == "abort") {
		return false;
	}
	if (toLower(name) != "i") {//not to ignore
		sup->setName(name);
		cout << "...Name updated." << endl;
	}

	//get supplier address
	cinValueStr(address, "What's the supplier's new ADDRESS (abort to stop, i to ignore)?");
	if (toLower(address) == "abort") {
		return false;
	}
	if (toLower(address) != "i") {//not to ignore
		sup->setAddress(address);
		cout << "...Address updated." << endl;
	}

	//get supplier NIF
	cinValue(nif, "What's the supplier's new NIF/VAT (0 to ignore)?");
	if (nif != 0) {
		sup->setNif(nif);
		cout << "...NIF updated." << endl;
	}
	return true;
}

bool removeSupplier() {
	Supplier* sup = nullptr;
	if (!getSupplierById(sup)) {
		return false;
	}
	return broker.removeSupplier(sup);
}

bool infoSupplier() {
	Supplier* sup = nullptr;
	if (!getSupplierById(sup)) {
		return false;
	}

	
	vector <Offer *> offers = sup->getOffers();
	cout << offers.size() << " Offer(s):" << endl;
	int count = 0;
	for (oit i = offers.begin(); i != offers.end(); i++, count++) {
		cout << (*(*i)).toConsole() << endl << endl;
	}
	return true;
}
void listSuppliers() {
	vector <Supplier *> suppliers = broker.getSuppliers();
	cout << suppliers.size() << " Supplier(s)" << endl;
	cout << setw(Person::SETW) << "ID: ";
	cout << setw(Person::SETW) << "Name: ";
	cout << setw(Person::SETW) << "NIF: ";
	cout << setw(Person::SETW) << "Address: ";
	cout << setw(Person::SETW) << "Offers: ";
	cout << endl;
	int count = 0;
	for (sit i = suppliers.begin(); i != suppliers.end(); i++, count++) {
		cout << (*(*i)) << endl;
	}
	cout << setw(0) << endl;
}

void displayMenuSuppliers() {
	cout << endl << endl;
	cout << "------------------Suppliers Menu-------------------" << endl;
	cout << "Add Supplier....................................add" << endl;
	cout << "Edit Supplier..................................edit" << endl;
	cout << "Remove Supplier..............................remove" << endl;
	cout << "Specific Supplier info.........................info" << endl;
	cout << "List Suppliers.................................list" << endl;
	cout << "Suppliers Menu.................................menu" << endl;
	cout << "Return to Main Menu..........................return" << endl;
	cout << "Exit 'A place in the sun' program..............exit" << endl;
}

bool executeSuppliersAction(string user_cmd, bool &exit) {
	if (user_cmd == "add") {
		addSupplier();
	} else if (user_cmd == "edit") {
		if (broker.getSizeSuppliers() == 0) {//if there are no suppliers to edit
			cout << "No Supplier available for editing" << endl;
			return true;
		}
		editSupplier();
	} else if (user_cmd == "remove") {
		if (broker.getSizeSuppliers() == 0) {//if there are no suppliers to remove
			cout << "No Supplier available for deleting" << endl;
			return true;
		}
		if (removeSupplier()) {
			cout << "Supplier removed." << endl;
		}
	} else if (user_cmd == "info") {//show supplier's info
		infoSupplier();
	} else if (user_cmd == "list") {//show all suppliers
		listSuppliers();
	} else if (user_cmd == "menu") {
		displayMenuSuppliers();
	} else if (user_cmd == "return") {//return to main menu
		return false;
	} else if (user_cmd == "exit") {//exit the program
		exit = true;
		return false;
	} else {
		cout << "Command '" << user_cmd << "' not found." << endl;
	}
	return true;
}

//---------------------------------------------------------Clients

bool getClientById(Client *& c) {
	uint id = -1;
	c = nullptr;
	while (c == nullptr) {//find a supplier
		cinValue(id, "What's the client's ID (0 to stop)?");
		if (id == 0) {
			return false;
		}
		c = broker.findClient(id);
		if (c == nullptr) {
			cout << "No client found for that ID" << endl;
		}
	}
	return true;
}

bool addClient() {
	string name, address;
	bool registered;
	int nif;
	//get supplier name
	cinValueStr(name, "What's the new client's NAME (abort to stop)?");
	if (toLower(name) == "abort") {
		return false;
	}

	//get supplier address
	cinValueStr(address, "What's the new client's ADDRESS (abort to stop)?");
	if (toLower(address) == "abort") {
		return false;
	}

	//get supplier NIF
	cinValue(nif, "What's the new client's NIF/VAT (0 to stop)?");
	if (nif == 0) {
		return false;
	}

	//get Client type
	cinValue(registered, "Is this a Registered client?");
	Client * c;
	if (registered) {
		c = new Registered(name, nif, address, 0);
	} else {
		c = new Ocasional(name, nif, address);
	}

	broker.addClient(c);
	cout << "Client: " << name << " added!" << endl;
	return true;
}

bool editClient() {
	Client* c = nullptr;
	if (!getClientById(c)) {
		return false;
	}

	string name, address;
	int nif;
	//get supplier name
	cinValueStr(name, "What's the clients's new NAME (abort to stop, i to ignore)?");
	if (toLower(name) == "abort") {
		return false;
	}
	if (toLower(name) != "i") {//not to ignore
		c->setName(name);
		cout << "...Name updated." << endl;
	}

	//get supplier address
	cinValueStr(address, "What's the clients's new ADDRESS (abort to stop, i to ignore)?");
	if (toLower(address) == "abort") {
		return false;
	}
	if (toLower(address) != "i") {//not to ignore
		c->setAddress(address);
		cout << "...Address updated." << endl;
	}

	//get supplier NIF
	cinValue(nif, "What's the clients's new NIF/VAT (0 to ignore)?");
	if (nif != 0) {
		c->setNif(nif);
		cout << "...NIF updated." << endl;
	}
	return true;
}

bool removeClient() {
	Client* c = nullptr;
	if (!getClientById(c)) {
		return false;
	}
	return broker.removeClient(c);
}

void listClients() {
	vector <Client *> clients = broker.getClients();
	cout << clients.size() << " Client(s)" << endl;
	cout << setw(Person::SETW) << "ID: ";
	cout << setw(Person::SETW) << "Name: ";
	cout << setw(Person::SETW) << "NIF: ";
	cout << setw(Person::SETW) << "Address: ";
	cout << setw(Person::SETW) << "Points: ";
	cout << endl;
	int count = 0;
	for (cit i = clients.begin(); i != clients.end(); i++, count++) {
		cout << "Client " << count << ": " << (*(*i)).toConsole() << endl;
	}
	cout << setw(0) << endl;
}

bool infoClient() {
	Client* c = nullptr;
	if (!getClientById(c)) {
		return false;
	}
	cout << "Client: " << c->toConsole() << endl;
	vector <Booking *> bookings = broker.getBookings();
	cout << "Booking(s):" << endl;
	int count = 0;
	for (bit i = bookings.begin(); i != bookings.end(); i++, count++) {
		if ((*i)->getClient()->getId() == c->getId()) {
			cout << "------------------------------------------------" << endl << "Booking " << (*i)->getId() << ": ";
			cout << (*(*i)).toConsole(&broker) << endl;
		}
	}
	return true;
}

void displayMenuClients() {
	cout << endl << endl;
	cout << "-------------------Clients Menu--------------------" << endl;
	cout << "Add Client......................................add" << endl;
	cout << "Edit Client....................................edit" << endl;
	cout << "Remove Client................................remove" << endl;
	cout << "Specific Client info...........................info" << endl;
	cout << "List Clients...................................list" << endl;
	cout << "List inactive Clients...........................ina" << endl;
	cout << "Clients Menu...................................menu" << endl;
	cout << "Return to Main Menu..........................return" << endl;
	cout << "Exit 'A place in the sun' program..............exit" << endl;
}

bool executeClientsAction(string user_cmd, bool &exit) {
	if (user_cmd == "add") {
		addClient();
	} else if (user_cmd == "edit") {
		if (broker.getSizeClients() == 0) {//if there are no clients to edit
			cout << "No Clients available for editing" << endl;
			return true;
		}
		editClient();
	} else if (user_cmd == "remove") {
		if (broker.getSizeClients() == 0) {//if there are no clients to remove
			cout << "No Client available for deleting" << endl;
			return true;
		}
		if (removeClient()) {
			cout << "Client removed." << endl;
		}
	} else if (user_cmd == "info") {//show client info
		infoClient();
	} else if (user_cmd == "list") {//show all clients
		listClients();
	} else if (user_cmd == "ina") {//show all inactive clients
		broker.inactCliDisplay();
	} else if (user_cmd == "menu") {
		displayMenuClients();
	} else if (user_cmd == "return") {//return to main menu
		return false;
	} else if (user_cmd == "exit") {//exit the program
		exit = true;
		return false;
	} else {
		cout << "Command '" << user_cmd << "' not found." << endl;
	}
	return true;
}

//---------------------------------------------------------Offers

bool getOfferById(Offer *& off) {
	uint id = -1;
	off = nullptr;
	while (off == nullptr) {//find a supplier
		cinValue(id, "What's the offer's ID (0 to stop)?");
		if (id == 0) {
			return false;
		}
		off = broker.findOffer(id);
		if (off == nullptr) {
			cout << "No offer found for that ID" << endl;
		}
	}
	return true;
}

bool removeOffer() {
	Offer* off = nullptr;
	if (!getOfferById(off)) {
		return false;
	}
	return broker.removeOffer(off);
}

bool editOffer() {
	float price;
	string city, typeUni, offerType;
	int numUni;

	Offer* off = nullptr;
	if (!getOfferById(off)) {
		return false;
	}

	//cinValueStr(offerType, "What's the offer's new TYPE - room | flat | apartment - (abort to stop, i to ignore)?");
	//if (toLower(offerType) == "abort") {
	//	return false;
	//}
	//if (toLower(offerType) != "i") {//not to ignore
	//	offerType = toLower(offerType);
	//	//off->setOfferType(offerType);
	//	//cout << "...Offer type updated." << endl;
	//}

	cinValueStr(city, "What's the offer's new CITY (abort to stop, i to ignore)?");
	if (toLower(city) == "abort") {
		return false;
	}
	if (toLower(city) != "i") {//not to ignore
		off->setCity(city);
		cout << "...City updated." << endl;
	}

	cinValueStr(typeUni, "What's the offer's new UNIT TYPE - day | week | month - (abort to stop, i to ignore)?");
	if (toLower(typeUni) == "abort") {
		return false;
	}
	if (toLower(typeUni) != "i") {
		off->setTypeUni(typeUni);
		cout << "...Unit type updated." << endl;
	}

	cinValue(numUni, "What's the offer's new NUMBER of " + typeUni + "'s (0 to ignore)?");
	if (numUni != 0) {
		off->setNumUni(numUni);
		cout << "... Number of " + typeUni + "'s updated." << endl;
	}

	cinValue(price, "What's the clients's new PRICE (0 to ignore)?");
	if (price != 0) {
		off->setPrice(price);
		cout << "...Price updated." << endl;
	}

	Room *r = dynamic_cast<Room *>(off);
	Flat *f = dynamic_cast<Flat *>(off);
	Apartment *a = dynamic_cast<Apartment *>(off);

	if (r) {//offer pointer is a room
		Room *r = nullptr;
		string type;//simple - 's', double - 'd' or double_extra_bed - 'e'
		int location = -1;//hotel - 1, shared - 2, bed and breakfast - 3
		bool hotel = false, sharedHouse = false, bedAndBreakfast = false;

		//edit room type
		while (type != "abort" && type != "s" && type != "d" && type != "e" && type != "i") {
			cinValue(type, "What's the new offer's TYPE ('s' for simple bedroom,'d' for double, 'e' for double with extra bed) (abort to stop)?");
			type = toLower(type);
		}
		if (type == "abort") {
			return false;
		} else if (type != "i") {
			r->setType(type);
			cout << "...Type updated." << endl;
		}

		//edit room location
		while (location < 0 || location >3) {
			cinValue(location, "What's the new offer's Unit Type ('1' for hotel,'2' for shared house, '3' for bed and breakfast) (0 to ignore)?");
		}
		switch (location) {
		case 0:
			break;
		case 1:
			hotel = true; break;
		case 2:
			sharedHouse = true; break;
		case 3:
			bedAndBreakfast = true; break;
		}
		r->setHotel(hotel).setSharedHouse(sharedHouse).setBedAndBreakfast(bedAndBreakfast);
		off = r;
		cout << "...Unit type preferences updated." << endl;
	} else if (f) {//offer pointer is a flat
		Flat *f = nullptr;
		bool fRoom, kitchen, bathroom;
		cinValue(fRoom, "Does this flat have a bedroom (0 for no, 1 for yes)?");
		cinValue(kitchen, "Does this flat have a kitchen (0 for no, 1 for yes)?");
		cinValue(bathroom, "Does this flat have a bathroom (0 for no, 1 for yes)?");
		f->setFRoom(fRoom).setKitchen(kitchen).setfBathroom(bathroom);
		off = f;
		cout << "...Unit type preferences updated." << endl;
	} else if (a) {//offer pointer is an apartment
		Apartment * a = nullptr;
		string room;
		bool kitchen, livingRoom;
		cinValue(kitchen, "Does this apartment have a kitchen (0 for no, 1 for yes)?");
		cinValue(livingRoom, "Does this apartment have a living room (0 for no, 1 for yes)?");

		//TODO: se houver tempo editar rooms atuais e adicionar outros

		a->setKitchen(kitchen).setLivingRoom(livingRoom);
		off = a;
		cout << "...Unit type preferences updated." << endl;
	} else {
		return false;
	}

	cout << "The changes were updated." << endl;
	return true;
}

bool addOffer() {
	Supplier* sup = nullptr;
	if (!getSupplierById(sup)) {
		return false;
	}

	int numUni;
	string city, typeUni = "", offerType = "";
	float price;

	//get offer type
	while (offerType != "abort" && offerType != "room" && offerType != "flat" && offerType != "apartment") {
		cinValue(offerType, "What's the new offer's Type ('room','flat','apartment') (abort to stop)?");
		offerType = toLower(offerType);
	}
	if (offerType == "abort") {
		return false;
	}

	//get offer city
	cinValueStr(city, "What's the new offer's CITY (abort to stop)?");
	if (toLower(city) == "abort") {
		return false;
	}

	//get offer address
	while (typeUni != "abort" && typeUni != "day" && typeUni != "week" && typeUni != "month") {
		cinValue(typeUni, "What's the new offer's COST UNIT TYPE ('day','week','month') (abort to stop)?");
		typeUni = toLower(typeUni);
	}
	if (typeUni == "abort") {
		return false;
	}

	//get offer numUni
	cinValue(numUni, "What's the new offer's number of " + typeUni + "s (0 to stop)?");
	if (numUni == 0) {
		return false;
	}

	//get offer price
	cinValue(price, "What's the new offer's PRICE (0 to stop)?");
	if (price == 0.0) {
		return false;
	}
	Offer * o = new Offer(numUni, city, typeUni, price);
	//cout << "OFFER_ID =" << o->getId() << endl;
	if (offerType == "room") {
		Room *r = new Room();
		r->setId(o->getId());
		string type;//simple - 's', double - 'd' or double_extra_bed - 'e'
		int location = -1;//hotel - 1, shared - 2, bed and breakfast - 3
		bool hotel = false, sharedHouse = false, bedAndBreakfast = false;

		//get room type
		while (type != "abort" && type != "s" && type != "d" && type != "e") {
			cinValue(type, "What's the new offer's TYPE ('s' for simple bedroom,'d' for double, 'e' for double with extra bed) (abort to stop)?");
			type = toLower(type);
		}
		if (type == "abort") {
			return false;
		}

		//get room location
		while (location < 0 || location >3) {
			cinValue(location, "What's the new offer's Unit Type ('1' for hotel,'2' for shared house, '3' for bed and breakfast) (0 to stop)?");
		}

		switch (location) {
		case 0:
			return false;
		case 1:
			hotel = true; break;
		case 2:
			sharedHouse = true; break;
		case 3:
			bedAndBreakfast = true; break;
		}
		r->setType(type).setHotel(hotel).setSharedHouse(sharedHouse).setBedAndBreakfast(bedAndBreakfast);
		o = r;
	} else if (offerType == "flat") {
		Flat *f = new Flat();
		f->setId(o->getId());
		bool fRoom, kitchen, bathroom;
		cinValue(fRoom, "Does this flat have a bedroom (0 for no, 1 for yes)?");
		cinValue(kitchen, "Does this flat have a kitchen (0 for no, 1 for yes)?");
		cinValue(bathroom, "Does this flat have a bathroom (0 for no, 1 for yes)?");
		f->setFRoom(fRoom).setKitchen(kitchen).setfBathroom(bathroom);
		o = f;
	} else if (offerType == "apartment") {
		Apartment * a = new Apartment();
		a->setId(o->getId());
		bool kitchen, livingRoom;
		cinValue(kitchen, "Does this apartment have a kitchen (0 for no, 1 for yes)?");
		cinValue(livingRoom, "Does this apartment have a living room (0 for no, 1 for yes)?");

		string room;
		bool is_suite;
		while (room != "end") {//add all the rooms
			//get room type
			room = "";
			while (room != "abort" && room != "end" && room != "s" && room != "d" && room != "e") {
				cinValue(room, "Add another room to this apartment, what's its TYPE ('s' for simple bedroom,'d' for double, 'e' for double with extra bed) (end to finish, abort to stop)?");
				room = toLower(room);
			}
			if (room == "abort") {
				return false;
			}
			if (room != "end") {
				cinValue(is_suite, "Is this " + room + " a suite (0 for no, 1 for yes)?");
				a->addRoom(room, is_suite);
			}
		}
		a->setKitchen(kitchen).setLivingRoom(livingRoom);
		o = a;
	} else {
		return false;
	}
	//cout << "OFFER_ID =" << o->getId() << endl;
	o->setCity(city).setTypeUni(typeUni).setNumUni(numUni).setPrice(price);
	sup->addOffer(o);
	broker.addOffer(o);
	cout << "Offer added!" << endl;
	return true;
}

bool addUnavailabilities() {
	Offer* off = nullptr;
	if (!getOfferById(off)) {
		return false;
	}

	bool proceed = true;
	Date from, to;
	while (proceed) {
		cout << "Unavailability start and end dates (format: 'DD/MM/YYYY DD/MM/YYYY') (anything else to stop)?";
		try {
			cin >> from >> to;
			off->addUnavailability(from, to);
			off->setPeriod();
		} catch(InvalidInput &e){
			cout << e << endl << "...operation terminated" << endl;
			proceed = false;
		}
	}
	broker.changes_offers = true;
	return true;
}

void listOffers() {
	vector <Offer *> offers = broker.getOffers();
	cout << offers.size() << " Offer(s):" << endl;
	int count = 0;
	for (oit i = offers.begin(); i != offers.end(); i++, count++) {
		cout << (*(*i)).toConsole() << endl << endl;
	}
	cout << endl;
}

void listDiscount() {
	int interval;
	int count = 0;
	bool found = false;
	vector <Offer *> offers = broker.getOffers();
	cout << "Please enter the interval(number of days) to which a offer is on sale: ";
	cin >> interval;

	broker.resetDiscount();
	for (oit i = offers.begin(); i != offers.end(); i++, count++)
	{
		priority_queue<Offer, vector<Offer>, Compare> temp = broker.getDiscount();
		if ((*(*i)).getPeriod() > interval)
		{
			while (!temp.empty())
			{
				if (temp.top().getId() != ((*(*i)).getId()))
				{
					temp.pop();
				}
				else if (temp.top().getId() == ((*(*i)).getId()))
				{
					found = true;
					break;
				}
			}
			if(found == false)
				broker.addToDiscount((*(*i)));
			found = false;
		}
	}
	priority_queue<Offer, vector<Offer>, Compare> sale = broker.getDiscount();
	cout << endl << sale.size() << " Offer(s) on sale:" << endl;

	while (!sale.empty())
	{
		cout << "Period: " << sale.top().getPeriod() << "  Days since last booking. "<< endl << sale.top().toConsole() << endl << endl;
		sale.pop();
		//broker.getDiscount().pop();
	}
}

void findOfferByCity() {
	//display all cities
	vector <Offer *> offers = broker.getOffers();
	vector<string>cities;
	cout << "Available cities:" << endl;
	for (oit i = offers.begin(); i != offers.end(); i++) {
		cities.push_back((*i)->getCity());
	}
	cities = getUniqueValues(cities);
	sort(cities.begin(), cities.end());
	for (vector<string>::iterator i = cities.begin(); i != cities.end(); i++) {
		cout << (*i) << "  ";
	}
	cout << endl;
	//search the requested city
	string city;
	cinValueStr(city, "What's the CITY to search in?");
	city = toLower(city);
	cout << endl << "Results: " << endl;
	for (oit i = offers.begin(); i != offers.end(); i++) {
		if (toLower((*i)->getCity()) == city) {
			cout << (*(*i)).toConsole() << endl << endl;
		}
	}
}

void displayMenuOffers() {
	cout << endl << endl;
	cout << "--------------------Offers Menu--------------------" << endl;
	cout << "Add Offer.......................................add" << endl;
	cout << "Edit Offer.....................................edit" << endl;
	cout << "Add Unavailability..............................una" << endl;
	cout << "Remove Offer.................................remove" << endl;
	cout << "List Offers....................................list" << endl;
	cout << "List Offers on discount........................sale" << endl;
	cout << "Search Offers by city..........................find" << endl;
	cout << "Offers Menu....................................menu" << endl;
	cout << "Return to Main Menu..........................return" << endl;
	cout << "Exit 'A place in the sun' program..............exit" << endl;
}

bool executeOffersAction(string user_cmd, bool &exit) {
	if (user_cmd == "add") {
		if (broker.getSizeSuppliers() == 0) {
			cout << "Error - At least one supplier is needed to add an offer" << endl;
			return true;
		}
		addOffer();
	} else if (user_cmd == "edit") {
		if (broker.getSizeOffers() == 0) {//if there are no suppliers to edit
			cout << "No Offer is available for editing" << endl;
			return true;
		}
		editOffer();
	} else if (user_cmd == "una") {//unavailabilities
		if (broker.getSizeOffers() == 0) {//if there are no suppliers
			cout << "No Offer is available" << endl;
			return true;
		}
		addUnavailabilities();
	} else if (user_cmd == "remove") {
		if (broker.getSizeOffers() == 0) {//if there are no offers to remove
			cout << "No Offer available for deleting" << endl;
			return true;
		}
		if (removeOffer()) {
			cout << "Offer removed." << endl;
		}
	} else if (user_cmd == "list") {//show all offers
		listOffers();
	} else if (user_cmd == "sale") {//show offers on discount
		listDiscount();
	}
	else if (user_cmd == "find") {//find offers in city
		findOfferByCity();
	} else if (user_cmd == "menu") {
		displayMenuOffers();
	} else if (user_cmd == "return") {//return to main menu
		return false;
	} else if (user_cmd == "exit") {//exit the program
		exit = true;
		return false;
	} else {
		cout << "Command '" << user_cmd << "' not found." << endl;
	}
	return true;
}

//---------------------------------------------------------Bookings

bool getBookingById(Booking *& bk) {
	uint id = -1;
	bk = nullptr;
	while (bk == nullptr) {//find a supplier
		cinValue(id, "What's the booking's ID (0 to stop)?");
		if (id == 0) {
			return false;
		}
		bk = broker.findBooking(id);
		if (bk == nullptr) {
			cout << "No booking for that ID" << endl;
		}
	}
	return true;
}

bool addBooking() {
	Date di, df;
	Offer * o = nullptr;
	Client *c = nullptr;

	//get the client
	if (!getClientById(c)) {
		return false;
	}

	//get the offer
	if (!getOfferById(o)) {
		return false;
	}
	//cout << "On Discount: " << broker.getDiscount().size() << endl;
	priority_queue<Offer, vector<Offer>, Compare> temp = broker.getDiscount();
	while (!temp.empty())
	{
		if (o->getId() == temp.top().getId())
		{
			o->setSaleValue(true);
			break;
		}
		temp.pop();
	}
	if (o->getSaleValue() == true)
		cout  << endl << "This offer is on sale! A discount will be applied" << endl << endl;


	//get offer dates
	Booking *b = new Booking();
	try {
		cinValue(di, "What's the booking's initial date (DD/MM/YYYY format, anything else to stop)?");
		cinValue(df, "What's the booking's final date (DD/MM/YYYY format, anything else to stop)?");
		b = new Booking(o, c, di, df);
		o->setPeriod();
	} catch (InvalidInput &e) {
		cout << e << endl << "booking aborted." <<endl;
		return false;
	}

	broker.addBooking(b);
	cout << "Booking for client: " << c->getName() << " added between:" << di << " and " << df << endl;

	
	broker.fillInactClie(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
	/*tabHInt::iterator it;
	tabHInt temp = broker.getInactCli();
	for(it= temp.begin();it!=broker.getInactCli().end();it++){
		if((*it)->getId() == c->getId()){
			broker.getInactCli().erase(c);
		}
	} */
	return true;
}

bool editBooking() {
	Booking* b = nullptr;
	if (!getBookingById(b)) {
		return false;
	}

	//update the offer
	Offer * o = nullptr;
	if (yesNoQuestion("Change the associated offer?")) {
		if (!getOfferById(o)) {
			return false;
		}
		if (o != nullptr) {
			b->setOffer(o);
		}
	}

	//update the client
	Client *c = nullptr;
	if (yesNoQuestion("Change the associated client?")) {
		if (!getClientById(c)) {
			return false;
		}
		if (c != nullptr) {
			b->setClient(c);
		}
	}

	//update the start date
	Date temp;
	if (yesNoQuestion("Change the start date?")) {
		cinValue(temp, "What's the new booking's initial date (DD/MM/YYYY format, anything else to ignore)?");
		try {
			b->setStart(temp);
		} catch (InvalidInput &e) {
			cout << e << endl;
		}
	}

	//update the end date
	if (yesNoQuestion("Change the end date?")) {
		cinValue(temp, "What's the new booking's end date (DD/MM/YYYY format, anything else to ignore)?");
		try {
			b->setStart(temp);
		} catch (InvalidInput &e) {
			cout << e << endl;
		}
	}
	cout << "...Booking edited" << endl;
	return true;
}

bool removeBooking() {
	Booking* b = nullptr;
	if (!getBookingById(b)) {
		return false;
	}
	return broker.removeBooking(b);
}

bool cancelBooking() {
	Booking* b = nullptr;
	if (!getBookingById(b)) {
		return false;
	}
	b->cancelBooking();
	return true;
}

void listBookings() {
	vector <Booking *> bookings = broker.getBookings();
	cout << bookings.size() << " Booking(s)" << endl;
	int count = 0;
	for (bit i = bookings.begin(); i != bookings.end(); i++, count++) {
		cout << "------------------------------------------------" << endl << "Booking " << (*i)->getId() << ": ";
		cout << (*(*i)).toConsole(&broker) << endl;
	}
	cout << setw(0) << endl;
}

void displayMenuBookings() {
	cout << endl << endl;
	cout << "-------------------Bookings Menu-------------------" << endl;
	cout << "Add Booking.....................................add" << endl;
	cout << "Edit Booking...................................edit" << endl;
	cout << "Remove Booking...............................remove" << endl;
	cout << "Cancel Booking...............................cancel" << endl;
	cout << "Bookings Bookings..............................list" << endl;
	cout << "Bookings Menu..................................menu" << endl;
	cout << "Return to Main Menu..........................return" << endl;
	cout << "Exit 'A place in the sun' program..............exit" << endl;
}

bool executeBookingsAction(string user_cmd, bool &exit) {
	if (user_cmd == "add") {
		addBooking();
	} else if (user_cmd == "edit") {
		if (broker.getSizeBookings() == 0) {//if there are no bookings to edit
			cout << "No Booking available for editing" << endl;
			return true;
		}
		editBooking();
	} else if (user_cmd == "remove") {
		if (broker.getSizeBookings() == 0) {//if there are no bookings to remove
			cout << "No Booking available for deleting" << endl;
			return true;
		}
		if (removeBooking()) {
			cout << "Booking removed." << endl;
		}
	} else if (user_cmd == "cancel") {
		if (broker.getSizeBookings() == 0) {//if there is no booking to cancel
			cout << "No Booking available to cancel" << endl;
			return true;
		}
		if (cancelBooking()) {
			cout << "Booking cancelled." << endl;
		}
	} else if (user_cmd == "list") {//show all bookings
		listBookings();
	} else if (user_cmd == "menu") {
		displayMenuBookings();
	} else if (user_cmd == "return") {//return to main menu
		return false;
	} else if (user_cmd == "exit") {//exit the program
		exit = true;
		return false;
	} else {
		cout << "Command '" << user_cmd << "' not found." << endl;
	}
	return true;
}

//---------------------------------------------------------MAIN

void bstList() {
	BSTItrIn<Booking> it(broker.bookingsReceipt);
	while (!it.isAtEnd()) {
		cout << it.retrieve().toConsole(&broker);
		it.advance();
	}
}

void bstClient() {
	Client* c = nullptr;
	if (!getClientById(c)) {
		return ;
	}

	BSTItrIn<Booking> it(broker.bookingsReceipt);
	while (!it.isAtEnd()) {
		if (it.retrieve().getClient() == c) {
			cout << it.retrieve().toConsole(&broker);
		}
		it.advance();
	}
}

void bstDates() {
	bool proceed = true;
	Date from, to;
	while (proceed) {
		cout << "Start and end dates (format: 'DD/MM/YYYY DD/MM/YYYY') (anything else to stop)?";
		try {
			cin >> from >> to;
			proceed = false;
		} catch (InvalidInput &e) {
			cout << e << endl << "...operation terminated" << endl;
			return;
		}
	}

	BSTItrIn<Booking> it(broker.bookingsReceipt);
	while (!it.isAtEnd()) {
		if ((from < it.retrieve().get_start() || from == it.retrieve().get_start())
			&& ((it.retrieve().get_end() < to) || to == it.retrieve().get_end())) {
			cout << it.retrieve().toConsole(&broker);
		}
		it.advance();
	}
}

bool execute_main_action(string user_cmd) {
	bool stay = true; //stay in the sub menus' loops
	bool exit = false; //stop the program
	if (user_cmd == "exit") {
		return false;
	} else if (user_cmd == "sup") {
		displayMenuSuppliers();
		while (stay) {
			cinValue(user_cmd, ">suppliers $ ");//read user command
			stay = executeSuppliersAction(user_cmd, exit);
		}
	} else if (user_cmd == "off") {
		displayMenuOffers();
		while (stay) {
			cinValue(user_cmd, ">offers $ ");//read user command
			stay = executeOffersAction(user_cmd, exit);
		}
	} else if (user_cmd == "cli") {
		displayMenuClients();
		while (stay) {
			cinValue(user_cmd, ">clients $ ");//read user command
			stay = executeClientsAction(user_cmd, exit);
		}
	} else if (user_cmd == "boo") {
		displayMenuBookings();
		while (stay) {
			cinValue(user_cmd, ">bookings $ ");//read user command
			stay = executeBookingsAction(user_cmd, exit);
		}
	} else if (user_cmd == "bst-list") {
		bstList();
	} else if (user_cmd == "bst-c") {
		bstClient();
	} else if (user_cmd == "bst-d") {
		bstDates();
	} else if (user_cmd == "file") {//change the file
		read_files();
	} else if (user_cmd == "reload") {//reload the file
		read_files();
	}
	return !exit;
}

void display_main_menu() {
	cout << endl << endl;
	cout << "----------------------Main Menu--------------------" << endl;
	cout << "Manage Suppliers................................sup" << endl;
	cout << "Manage Offers...................................off" << endl;
	cout << "Manage Clients..................................cli" << endl;
	cout << "Manage Bookings.................................boo" << endl;
	cout << "Change Broker's File...........................file" << endl;
	cout << "Reload Broker's File.........................reload" << endl;
	cout << "BST Booking's list complete................bst-list" << endl;
	cout << "BST Booking's list by client..................bst-c" << endl;
	cout << "BST Booking's list between dates..............bst-d" << endl;
	cout << "Exit 'A place in the sun' program..............exit" << endl;
}

bool user_interface() {
	string user_cmd;
	display_main_menu();
	cinValue(user_cmd, "$ ");//read user command
	return execute_main_action(toLower(user_cmd));
}

bool read_files() {
	string filename;
	bool exit = false;
	while (!exit) {
		cinValueStr(filename, "Which file holds the Broker's data (exit to abort, new to create)?\n$ ");
		if (filename == "exit") {
			return false;
		} else if (filename == "new") {
			cinValueStr(filename, "New file's name, without the extension(exit to abort)?\n$");
			if (filename == "exit") {
				return false;
			}
			createNewFile(filename);
			return true;
		}
		try {
			readFileSS(filename) >> broker;//imports the data from all the files
			cout << endl << "IMPORTED DATA:" << endl;
			cout << "IMPORTED " << setw(4) << broker.getSizeSuppliers() << " Supplier(s)" << endl;
			cout << "IMPORTED " << setw(4) << broker.getSizeOffers() << " Offer(s)" << endl;
			cout << "IMPORTED " << setw(4) << broker.getSizeClients() << " Clients(s)" << endl;
			cout << "IMPORTED " << setw(4) << broker.getSizeBookings() << " Bookings(s)" << endl;
			exit = true;
		} catch (FileNotFound &e) {
			cout << e << endl;
		} catch (InvalidInput &e) {
			cout << e << endl;
		}
	}
	return true;
}

bool saveFiles() {
	if (broker.unsavedChanges()) {
		if (broker.saveChanges()) {
			cout << "...Changes saved" << endl;
		} else {
			cout << "...ERROR when saving changes" << endl;
			return false;
		}
	} else {
		cout << "...No changes were made" << endl;
	}
	return true;
}

int main() {
	if (read_files()) {
		broker.fillInactClie(now->tm_mday,now->tm_mon+1,now->tm_year+ 1900);
		while (user_interface()) {
			//runs until the user_interface returns false
		}
		saveFiles();
	}
	cout << endl << "---------------------Execution end---------------------" << endl << endl;
	return 0;
}
