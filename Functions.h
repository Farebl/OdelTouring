#pragma once


#include <memory>

#include <list>
#include <stack>
#include <vector>

import CustomerManagerTrip;

struct Order;

using ListSharedsManager_t = std::list<std::shared_ptr<Manager>>;
using ListSharedsCustomer_t = std::list<std::shared_ptr<Customer>>;
using ListSharedsTrip_t = std::list<std::shared_ptr<Trip>>;

using manager_list_iter_t = std::list<std::shared_ptr<Manager>>::iterator;
using customer_list_iter_t = std::list<std::shared_ptr<Customer>>::iterator;
using trip_list_iter_t = std::list<std::shared_ptr<Trip>>::iterator;

using Countries_Count_Year_AllCountYear = std::pair <std::pair<std::vector<std::string>, int>, std::pair<int, int>>;


// Функція виклику інтерфейса користувача
void Interface(ListSharedsManager_t& Managers, ListSharedsCustomer_t& Customers, ListSharedsTrip_t& Trips, 
	std::string managersDataPath = "Managers.txt",
	std::string customersDataPath = "Customers.txt",
	std::string tripsDataPath = "Trips.txt",
	std::string ordersPath = "Orders.txt",
	std::string historyDataPath = "History.txt");



//--------------------------------------------------------------------------------------------------------------------------------------------



// 0 General functions

template<typename T> 
void ShowListOfCollectionElementNames(const std::list<std::shared_ptr<T>>& Collection);

int GetDateDifference(const std::string firstDate, const std::string secondDate = "today");

// Safety cin input
template<typename T>
void ValidatedInput(T& val);

// logging actions
void SaveMessage(const std::string msg, const std::string path = "History.txt");

// clear console gui
void ClearConsole(); 

int GetCountOfOrders(const int year = 0, const std::string path = "Orders.txt");

// save orders to storage
void SaveOrderData(const int year_of_booking, const std::string country, const std::string name_of_trip, const std::string name_of_customer, const double price, const std::string path = "Orders.txt");

// read orders from storage
void ReadOrdersData(std::stack<Order>& Collection, const std::string path = "Orders.txt");


//--------------------------------------------------------------------------------------------------------------------------------------------



// 1 Managers functions:


void ShowFullInfoForEditManager(const manager_list_iter_t& manager);

void EditManager(manager_list_iter_t& manager, const int fieldIndex, const std::string value);

void SaveManagersData(const ListSharedsManager_t& ManagersCollection, const std::string path = "Managers.txt");

void ReadManagersData(ListSharedsManager_t& ManagersCollection, const std::string path = "Managers.txt");



//--------------------------------------------------------------------------------------------------------------------------------------------



// 2 Customers functions:

void ShowFullInfoForEditCustomer(const customer_list_iter_t& customer);

void EditCustomer(customer_list_iter_t& customer, const int fieldIndex, const std::string value);

void ShowListOfCustomerNamesByCountry(const ListSharedsCustomer_t& CustomersCollection, const std::string country);

void ShowListOfCustomersWithoutTripNames(const ListSharedsCustomer_t& CustomersCollection);

void ShowListOfCustomersWithTripNames(const ListSharedsCustomer_t& CustomersCollection);

std::pair<size_t, std::vector<int>> GetCountOfCustomersWithTrip(const ListSharedsCustomer_t& CustomersCollection);

std::pair<size_t, std::vector<int>> GetCountOfCustomersWithoutTrip(const ListSharedsCustomer_t& CustomersCollection);

void SaveCustomersData(const ListSharedsCustomer_t& CustomersCollection, const std::string path = "Customers.txt");

void ReadCustomersData(ListSharedsCustomer_t& CustomersCollection, const ListSharedsTrip_t& Trips, const std::string path = "Customers.txt");



//--------------------------------------------------------------------------------------------------------------------------------------------



// 3 Trips functions:

void ShowFullInfoForEditTrip(const trip_list_iter_t& trip);

void EditTrip(trip_list_iter_t& trip, const int fieldIndex, const std::string value);

void ShowListOfUnboughtTripNames(const ListSharedsTrip_t& Trips);

void ShowListOfPurchasedTripNames(const ListSharedsTrip_t& Trips);

std::pair<size_t, std::vector<int>> GetCountOfUnboughtTrips(const ListSharedsTrip_t& Trips);

std::pair<size_t, std::vector<int>> GetCountOfPurchasedTrips(const ListSharedsTrip_t& Trips);

std::vector<std::string> GetCountriesOfBoughtTrips(const ListSharedsTrip_t& Trips, const int year = 0, std::string path = "Orders.txt");

int GetAveragePriceOfTrips(const ListSharedsTrip_t& Trips, const int year = 0, std::string path = "Orders.txt");

double GetAverageDurationOfTrips(const ListSharedsTrip_t& Trips, const int year = 0, std::string path = "Orders.txt");

std::shared_ptr<Trip> FindTripById(const ListSharedsTrip_t& Collection, const int personal_id);

Countries_Count_Year_AllCountYear FindMostPupularCountries(const ListSharedsTrip_t& Trips, const int year = 0, std::string path = "Orders.txt");

void ShowMostPupularCountries(const Countries_Count_Year_AllCountYear& pair);

void SaveTripsData(const ListSharedsTrip_t& Trips, const std::string path = "Trips.txt");

void ReadTripsData(std::list<std::shared_ptr<Trip>>& Trips, const std::string path = "Trips.txt");

