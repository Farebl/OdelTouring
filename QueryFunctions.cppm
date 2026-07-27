
module;

#include <iostream>

#include <memory>

#include <list>
#include <stack>
#include <vector>


export module Functions:QueryFunctions;

export import CustomerManagerTrip;
export import Order;




export using ListSharedsManager_t = std::list<std::shared_ptr<Manager>>;
export using ListSharedsCustomer_t = std::list<std::shared_ptr<Customer>>;
export using ListSharedsTrip_t = std::list<std::shared_ptr<Trip>>;

export using manager_list_iter_t = std::list<std::shared_ptr<Manager>>::iterator;
export using customer_list_iter_t = std::list<std::shared_ptr<Customer>>::iterator;
export using trip_list_iter_t = std::list<std::shared_ptr<Trip>>::iterator;

export using Countries_Count_Year_AllCountYear = std::pair <std::pair<std::vector<std::string>, int>, std::pair<int, int>>;


//--------------------------------------------------------------------------------------------------------------------------------------------



// 0 General functions


export template<typename T>
void ShowListOfCollectionElementNames(const std::list<std::shared_ptr<T>>& Collection) {
	if (Collection.empty())
		return;

	int index = 1;
	for ( auto& element:Collection) {
		std::cout << index << ") ";
		std::cout << element->GetFullName() << " \n";
		index++;
	}
}



// Safety cin input
export template<typename T>
void ValidatedInput(T& val) {
    while (true) {
        std::cin >> val;
        if (std::cin.fail())
        {
            std::cout << "\n\nYou may have entered wrong value. Try again.\n";
            std::cin.clear(); // 
            std::cin.ignore(LLONG_MAX, '\n');
        }
        else
            break;
    }
    std::cin.ignore(INT_MAX, '\n');
}



int GetDateDifference(const std::string firstDate, const std::string secondDate = "today");

// logging actions
export void SaveMessage(const std::string msg, const std::string path = "History.txt");

// clear console gui
export void ClearConsole(); 

export int GetCountOfOrders(const int year = 0, const std::string path = "Orders.txt");

// save orders to storage
export void SaveOrderData(const int year_of_booking, const std::string country, const std::string name_of_trip, const std::string name_of_customer, const double price, const std::string path = "Orders.txt");

// read orders from storage
export void ReadOrdersData(std::stack<Order>& Collection, const std::string path = "Orders.txt");


//--------------------------------------------------------------------------------------------------------------------------------------------



// 1 Managers functions:


export void ShowFullInfoForEditManager(const manager_list_iter_t& manager);

export void EditManager(manager_list_iter_t& manager, const int fieldIndex, const std::string value);

export void SaveManagersData(const ListSharedsManager_t& ManagersCollection, const std::string path = "Managers.txt");

export void ReadManagersData(ListSharedsManager_t& ManagersCollection, const std::string path = "Managers.txt");



//--------------------------------------------------------------------------------------------------------------------------------------------



// 2 Customers functions:

export void ShowFullInfoForEditCustomer(const customer_list_iter_t& customer);

export void EditCustomer(customer_list_iter_t& customer, const int fieldIndex, const std::string value);

export void ShowListOfCustomerNamesByCountry(const ListSharedsCustomer_t& CustomersCollection, const std::string country);

export void ShowListOfCustomersWithoutTripNames(const ListSharedsCustomer_t& CustomersCollection);

export void ShowListOfCustomersWithTripNames(const ListSharedsCustomer_t& CustomersCollection);

export std::pair<size_t, std::vector<int>> GetCountOfCustomersWithTrip(const ListSharedsCustomer_t& CustomersCollection);

export std::pair<size_t, std::vector<int>> GetCountOfCustomersWithoutTrip(const ListSharedsCustomer_t& CustomersCollection);

export void SaveCustomersData(const ListSharedsCustomer_t& CustomersCollection, const std::string path = "Customers.txt");

export void ReadCustomersData(ListSharedsCustomer_t& CustomersCollection, const ListSharedsTrip_t& Trips, const std::string path = "Customers.txt");



//--------------------------------------------------------------------------------------------------------------------------------------------



// 3 Trips functions:

export void ShowFullInfoForEditTrip(const trip_list_iter_t& trip);

export void EditTrip(trip_list_iter_t& trip, const int fieldIndex, const std::string value);

export void ShowListOfUnboughtTripNames(const ListSharedsTrip_t& Trips);

export void ShowListOfPurchasedTripNames(const ListSharedsTrip_t& Trips);

export std::pair<size_t, std::vector<int>> GetCountOfUnboughtTrips(const ListSharedsTrip_t& Trips);

export std::pair<size_t, std::vector<int>> GetCountOfPurchasedTrips(const ListSharedsTrip_t& Trips);

export std::vector<std::string> GetCountriesOfBoughtTrips(const ListSharedsTrip_t& Trips, const int year = 0, std::string path = "Orders.txt");

export int GetAveragePriceOfTrips(const ListSharedsTrip_t& Trips, const int year = 0, std::string path = "Orders.txt");

export double GetAverageDurationOfTrips(const ListSharedsTrip_t& Trips, const int year = 0, std::string path = "Orders.txt");

export std::shared_ptr<Trip> FindTripById(const ListSharedsTrip_t& Collection, const int personal_id);

export Countries_Count_Year_AllCountYear FindMostPupularCountries(const ListSharedsTrip_t& Trips, const int year = 0, std::string path = "Orders.txt");

export void ShowMostPupularCountries(const Countries_Count_Year_AllCountYear& pair);

export void SaveTripsData(const ListSharedsTrip_t& Trips, const std::string path = "Trips.txt");

export void ReadTripsData(std::list<std::shared_ptr<Trip>>& Trips, const std::string path = "Trips.txt");

