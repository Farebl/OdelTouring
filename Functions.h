#pragma once
#include <stack>
#include <algorithm> 
#include <numeric> 
#include <fstream> 

#include "Manager.h" // + Customer.h + Trip.h + Person.h +  <iostream> + <string> + <vector> + <list> 


// Структура, для опису об'єкту "Замовлення"
struct Order;

// Запровадження псевдонимів
using ListSharedsManager_t = std::list<std::shared_ptr<Manager>>;
using ListSharedsCustomer_t = std::list<std::shared_ptr<Customer>>;
using ListSharedsTrip_t = std::list<std::shared_ptr<Trip>>;

using manager_list_iter_t = std::list<std::shared_ptr<Manager>>::iterator;
using customer_list_iter_t = std::list<std::shared_ptr<Customer>>::iterator;
using trip_list_iter_t = std::list<std::shared_ptr<Trip>>::iterator;

using Countries_Count_Year_AllCountYear = std::pair <std::pair<std::vector<std::string>, int>, std::pair<int, int>>;


// Функція запуску програми
void Start(ListSharedsManager_t& Managers, ListSharedsCustomer_t& Customers, ListSharedsTrip_t& Trips);

// Функція виклику інтерфейса користувача
void Interface(ListSharedsManager_t& Managers, ListSharedsCustomer_t& Customers, ListSharedsTrip_t& Trips, 
	std::string managersDataPath = "Managers.txt",
	std::string customersDataPath = "Customers.txt",
	std::string tripsDataPath = "Trips.txt",
	std::string ordersPath = "Orders.txt",
	std::string historyDataPath = "History.txt");



//--------------------------------------------------------------------------------------------------------------------------------------------



// 0 Загальні функції

//0.1 Вивід списка менеджерів, клієнтів, путівок, тощо.
template<typename T> 
void ShowListOfCollectionElementNames(const std::list<std::shared_ptr<T>>& Collection);

//0.2 Отримання різниці між двома датами формату "dd/mm/yyyy"
int GetDateDifference(const std::string firstDate, const std::string secondDate = "today");

//0.3 Функція, для коректного вводу даних для числової змінної
template<typename T>
void ValidatedInput(T& val);

//0.4 Запис повідомлення у файл.txt
void SaveMessage(const std::string msg, const std::string path = "History.txt");

//0.5 Очищення консолі 
void ClearConsole(); 

//0.6 Отримання кількості замовлень (за весь час або за роком)
int GetCountOfOrders(const int year = 0, const std::string path = "Orders.txt");

//0.7 Збереження даних про замовлення у файл.txt
void SaveOrderData(const int year_of_booking, const std::string country, const std::string name_of_trip, const std::string name_of_customer, const double price, const std::string path = "Orders.txt");

//0.8 Зчитування даних про замовлення з файл.txt
void ReadOrdersData(std::stack<Order>& Collection, const std::string path = "Orders.txt");



//--------------------------------------------------------------------------------------------------------------------------------------------



// 1 Функції менеджера:


//1.1 Вивід повної інформації про менеджера, для редагування даних 
void ShowFullInfoForEditManager(const manager_list_iter_t& manager);

//1.2 Редагування даних про менеджера 
void EditManager(manager_list_iter_t& manager, const int fieldIndex, const std::string value);

//1.3 Збереження даних про менеджерів у файл.txt 
void SaveManagersData(const ListSharedsManager_t& ManagersCollection, const std::string path = "Managers.txt");

//1.4 Зчитування даних про менеджерів з файл.txt 
void ReadManagersData(ListSharedsManager_t& ManagersCollection, const std::string path = "Managers.txt");



//--------------------------------------------------------------------------------------------------------------------------------------------



// 2 Функції клієнта:

//2.1 Вивід повної інформації про клієнта, для редагування даних 
void ShowFullInfoForEditCustomer(const customer_list_iter_t& customer);

//2.2 Редагування даних про клієнта 
void EditCustomer(customer_list_iter_t& customer, const int fieldIndex, const std::string value);

//2.3 Вивід списка клієнтів, які придбали путівку, до певної країни  
void ShowListOfCustomerNamesByCountry(const ListSharedsCustomer_t& CustomersCollection, const std::string country);

//2.4 Вивід списка клієнтів, які не мають путівку. 
void ShowListOfCustomersWithoutTripNames(const ListSharedsCustomer_t& CustomersCollection);

//2.5 Вивід списка клієнтів, які мають путівку. 
void ShowListOfCustomersWithTripNames(const ListSharedsCustomer_t& CustomersCollection);

//2.6 Отримання кількості клієнтів, які мають путівку. 
std::pair<size_t, std::vector<int>> GetCountOfCustomersWithTrip(const ListSharedsCustomer_t& CustomersCollection);

//2.7 Отримання кількості клієнтів, які не мають путівку. 
std::pair<size_t, std::vector<int>> GetCountOfCustomersWithoutTrip(const ListSharedsCustomer_t& CustomersCollection);

//2.8 Збереження даних про клієнтів у файл.txt 
void SaveCustomersData(const ListSharedsCustomer_t& CustomersCollection, const std::string path = "Customers.txt");

//2.9 Зчитування даних про клієнтів з файл.txt 
void ReadCustomersData(ListSharedsCustomer_t& CustomersCollection, const ListSharedsTrip_t& Trips, const std::string path = "Customers.txt");



//--------------------------------------------------------------------------------------------------------------------------------------------



// 3 Функції подорожі:

//3.1 Вивід повної інформації про путівку, для редагування даних 
void ShowFullInfoForEditTrip(const trip_list_iter_t& trip);

//3.2 Редагування даних про путівку 
void EditTrip(trip_list_iter_t& trip, const int fieldIndex, const std::string value);

//3.3 Вивід списку некуплених путівок. 
void ShowListOfUnboughtTripNames(const ListSharedsTrip_t& Trips);

//3.4 Вивід списку куплених путівок. 
void ShowListOfPurchasedTripNames(const ListSharedsTrip_t& Trips);

//3.5 Отримання кількості непроданих путівок  
std::pair<size_t, std::vector<int>> GetCountOfUnboughtTrips(const ListSharedsTrip_t& Trips);

//3.6 Отримання кількості проданих путівок  
std::pair<size_t, std::vector<int>> GetCountOfPurchasedTrips(const ListSharedsTrip_t& Trips);

//3.7 Отримання списку країн, проданих путівок
std::vector<std::string> GetCountriesOfBoughtTrips(const ListSharedsTrip_t& Trips, const int year = 0, std::string path = "Orders.txt");

//3.8 Отримання середнього значення вартості путівок
int GetAveragePriceOfTrips(const ListSharedsTrip_t& Trips, const int year = 0, std::string path = "Orders.txt");

//3.9 Отримання середнього значення тривалості путівок 
double GetAverageDurationOfTrips(const ListSharedsTrip_t& Trips, const int year = 0, std::string path = "Orders.txt");

//3.10 Пошук дійсної путівки по id 
std::shared_ptr<Trip> FindTripById(const ListSharedsTrip_t& Collection, const int personal_id);

//3.11 Пошук країн, які мають найбільший попит. Повертається значення: (Країна, пара(кількість, рік))
Countries_Count_Year_AllCountYear FindMostPupularCountries(const ListSharedsTrip_t& Trips, const int year = 0, std::string path = "Orders.txt");

//3.12 Вивід країн, які мають найбільший попит. 
void ShowMostPupularCountries(const Countries_Count_Year_AllCountYear& pair);

//3.13 Збереження даних про путівки у файл.txt
void SaveTripsData(const ListSharedsTrip_t& Trips, const std::string path = "Trips.txt");

//3.14 Зчитування даних про путівки з файл.txt 
void ReadTripsData(std::list<std::shared_ptr<Trip>>& Trips, const std::string path = "Trips.txt");
















