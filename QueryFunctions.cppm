
module;

#include <iostream>

#include <chrono> 
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
export using ListSharedsOrder_t = std::list<std::shared_ptr<Order>>;

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
export std::ostream& operator<<(std::ostream& os, const std::chrono::year_month_day& ymd);

export std::chrono::year_month_day stringToYearMonthDay(const std::string& date);

// logging actions
export void SaveMessage(const std::string msg, const std::string path = "History.txt");

// clear console gui
export void ClearConsole(); 



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

export std::pair<size_t, std::vector<int>> GetCountOfPurchasedTrips(const ListSharedsTrip_t& Trips, unsigned short year = 0);

export std::vector<std::string> GetCountriesOfBoughtTrips(const ListSharedsTrip_t& Trips);

export std::shared_ptr<Trip> FindTripById(const ListSharedsTrip_t& Collection, const int personal_id);

export void SaveTripsData(const ListSharedsTrip_t& Trips, const std::string path = "Trips.txt");

export void ReadTripsData(std::list<std::shared_ptr<Trip>>& Trips, const std::string path = "Trips.txt");



//--------------------------------------------------------------------------------------------------------------------------------------------



// 4 Orders functions:

export int GetCountOfOrdersByYear(const ListSharedsOrder_t& orders, const int year = 0);

export int GetAveragePriceOfSoldTripsByYear(const ListSharedsOrder_t& orders, const int year = 0);

export double GetAverageDurationOfSoldTripsByYear(const ListSharedsOrder_t& orders, const int year = 0);

export Countries_Count_Year_AllCountYear FindMostPupularCountriesOfSoldTrips(const ListSharedsOrder_t& orders, const int year = 0);

export void ShowMostPupularCountriesOfSoldTrips(const Countries_Count_Year_AllCountYear& pair);

export void RemoveOrderByCustomerId(ListSharedsOrder_t& orders, size_t customer_id);

// save orders to storage
export void SaveOrdersData(const ListSharedsOrder_t& orders, const std::string& path);

// read orders from storage
export void ReadOrdersData(ListSharedsOrder_t& orders, const std::string path = "Orders.txt");


