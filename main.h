#pragma once
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS for localtime
/*! \mainpage "A place in the sun" Reservas
*
* \section memebers_sc Autoria
* Luís Cruz - 201303248 - up201303248@fe.up.pt
*
* Miguel Ramalho - 201403027 - up201403027@fe.up.pt
*
* Paulo Costa - 201206045 - ei12086@fe.up.pt
*
* Instituição:			Faculdade de Engenharia da Universidade do Porto -  <a href ="http://www.fe.up.pt">FEUP</a>
*
* Curso:				Mestrado Integrado em Engenharia Informática e Computação - <a href ="https://sigarra.up.pt/feup/pt/cur_geral.cur_view?pv_ano_lectivo=2016&pv_origem=CUR&pv_tipo_cur_sigla=MI&pv_curso_id=742">MIEIC</a>
*
* Unidade Curricular:	Algoritmos e Estruturas de Dados - <a href="https://sigarra.up.pt/feup/pt/ucurr_geral.ficha_uc_view?pv_ocorrencia_id=384931">AEDA</a>
*
* Sexta-feira, 18 de Novembro de 2016
*
* \section install_sec Instalação
* Este projeto foi desenvolvido em ambiente <strong>Visual Studio C++</strong>, pelo que se notaram alguns erros ao tentar compilar o mesmo no ambiente Eclipse.
* 
* Como tal aconselhamos o uso do primeiro.
*
* \subsection note_sec Notas
* De forma a produzir a documentação doxygen das funções em main.cpp fomos forçados a criar um ficheiro main.h, sendo que a sua utilização era desnecessária. 
*/

#include <iostream>
#include <iomanip>
#include <ctime>
#include <unordered_set>
#include "Date.h"
#include "Booking.h"
#include "Person.h"
#include "utils.h"
#include "Broker.h"
#include "Offer.h"

using namespace std;
/**
* @defgroup main main
* @brief Main file where the program state machine flow is implemented by using all the remaining modules and classes
* @{
* 
*/

/** typedefs */
typedef vector<Supplier *>::iterator sit;
time_t t = time(0);   
struct tm * now = localtime( & t ); 

/** forward declarations */
bool read_files();
/** broker instance for the current execution, iteracts with the data in the specified files */
Broker broker;//A broker instance

//---------------------------------------------------------Suppliers

/**
* Find and return a supplier pointer by asking the user for an id
* @param sup reference to a supplier pointer
* @return bool true if the user identifies a valid supplier, false otherwise
*/
bool getSupplierById(Supplier *& sup);

/**
* Interface for inserting a new supplier to the Broker instance
* @return bool true if the user correctly inserts a supplier, false otherwise (if the user aborts the operation)
*/
bool addSupplier();

/**
* Interface for editing a given supplier in the Broker instance, searched for by its id
* @return bool true if the user does not abort the operation, false otherwise
*/
bool editSupplier();

/**
* Interface for deleting a given supplier in the Broker instance, searched for by its id
* @return bool true if the user specifies a valid supplier, false otherwise
*/
bool removeSupplier();

/**
* List all the suppliers in a user friendly way
*/
void listSuppliers();

/**
* Display a user friendly menu of the functions available in the suppliers context
*/
void displayMenuSuppliers();

/**
* Execute the action specified by the user in the command line input
*/
bool executeSuppliersAction(string user_cmd, bool &exit);

//---------------------------------------------------------Clients
/**
* Find and return a client pointer by asking the user for an id
* @param c reference to a client pointer
* @return bool true if the user identifies a valid client, false otherwise
*/
bool getClientById(Client *& c);

/**
* Interface for inserting a new client to the Broker instance
* @return bool true if the user correctly inserts a client, false otherwise (if the user aborts the operation)
*/
bool addClient();

/**
* Interface for editing a given client in the Broker instance, searched for by its id
* @return bool true if the user does not abort the operation, false otherwise
*/
bool editClient();

/**
* Interface for deleting a given client in the Broker instance, searched for by its id
* @return bool true if the user specifies a valid client, false otherwise
*/
bool removeClient();

/**
* List all the clients in a user friendly way
*/
void listClients();

/**
* Display a user friendly menu of the functions available in the clients context
*/
void displayMenuClients();

/**
* Execute the action specified by the user in the command line input
*/
bool executeClientsAction(string user_cmd, bool &exit);

//---------------------------------------------------------Offers
/**
* Find and return an offer pointer by asking the user for an id
* @param off reference to a offer pointer
* @return bool true if the user identifies a valid offer, false otherwise
*/
bool getOfferById(Offer *& off);

/**
* Interface for deleting a given offer in the Broker instance, searched for by its id
* @return bool true if the user specifies a valid offer, false otherwise
*/
bool removeOffer();

/**
* Interface for editing a given offer in the Broker instance, searched for by its id
* @return bool true if the user does not abort the operation, false otherwise
*/
bool editOffer();

/**
* Interface for inserting a new offer to the Broker instance
* @return bool true if the user correctly inserts an offer, false otherwise (if the user aborts the operation)
*/
bool addOffer();

/**
* Interface for inserting a unavailabilities (pair<Date, Date>) to an Offer of the Broker instance
* @see InvalidInput
* @return bool true if the user correctly inserts the two dates, false otherwise (if the user aborts the operation)
*/
bool addUnavailabilities();

/**
* List all the offers in a user friendly way
*/
void listOffers();

/**
* List all the offers in a user friendly way for a given city
*/
void findOfferByCity();

/**
* Display a user friendly menu of the functions available in the offers context
*/
void displayMenuOffers();

/**
* Execute the action specified by the user in the command line input
*/
bool executeOffersAction(string user_cmd, bool &exit);

//---------------------------------------------------------Bookings
/**
* Find and return a booking pointer by asking the user for an id
* @param bk reference to a booking pointer
* @return bool true if the user identifies a valid booking, false otherwise
*/
bool getBookingById(Booking *& bk);

/**
* Interface for inserting a new booking to the Broker instance
* @return bool true if the user correctly inserts a booking, false otherwise (if the user aborts the operation)
*/
bool addBooking();

/**
* Interface for editing a given booking in the Broker instance, searched for by its id
* @return bool true if the user does not abort the operation, false otherwise
*/
bool editBooking();

/**
* Interface for deleting a given booking in the Broker instance, searched for by its id
* @return bool true if the user specifies a valid booking, false otherwise
*/
bool removeBooking();

/**
* Interface for canceling a given booking (change its status) in the Broker instance, searched for by its id
* @return bool true if the user specifies a valid booking, false otherwise
*/
bool cancelBooking();

/**
* List all the bookings in a user friendly way
*/
void listBookings();

/**
* Display a user friendly menu of the functions available in the bookings context
*/
void displayMenuBookings();

/**
* Execute the action specified by the user in the command line input
*/
bool executeBookingsAction(string user_cmd, bool &exit);

//---------------------------------------------------------MAIN

/**
* List all the bookings from the bst sorted as specified in the projects requirements
*/
void bstList();

/**
* List all the bookings from the bst for a given client
*/
void bstClient();

/**
* List all the bookings from the bst between two given dates
*/
void bstDates();

/**
* Execute the action specified by the user in the command line input
*/
bool execute_main_action(string user_cmd);

/**
* Displays the main menu in the console
*/
void display_main_menu();

/**
* Executes the interface and response to input functions
* @return bool indicating to exit the program on true
*/
bool user_interface();

/**
* @brief Function to import all the data from a .txt file
* Reads or creates a broker txt file, that holds the names of four other files: suppliers, offers, clients and bookings files.
* Afterwards it calls the importing methods for each of the classes and stores them in the current instance of Broker
*/
bool read_files();

/**
* @brief Function to save all the data from a .txt file
* Calls the current Broker instance's method to save the changes in the current data.
* This function is called when the user exits the program through the proper channels
* @see Broker::saveChanges()
*/
bool saveFiles();

/*
* @brief main function that triggers all the program functionality
* Runs an 'inifite loop' that runs until the user chooses to exit the application, this loop calls the user_interface function to show menus, receive and process user commands
*/
int main();
