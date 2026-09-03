import Functions;

#include <iostream>
int main() {
    ListSharedsManager_t Managers;
    ListSharedsCustomer_t Customers;
    ListSharedsTrip_t Trips;

    try{
        ReadManagersData(Managers, "Managers.txt");
        ReadTripsData(Trips, "Trips.txt");
        ReadCustomersData(Customers, Trips, "Customers.txt");
    }
    catch(std::exception& ex){
        std::cout<< "Exception in main after reading data: " << ex.what();
    }

    try{
        Interface(Managers, Customers, Trips, "Managers.txt", "Customers.txt", "Trips.txt", "Orders.txt", "History.txt");
    }
    catch(std::exception& ex){
        std::cout<< "Exception from interface: " << ex.what();
    }

    try{     
        SaveManagersData(Managers, "Managers.txt");
        SaveTripsData(Trips, "Trips.txt");
        SaveCustomersData(Customers, "Customers.txt");
    }
    catch(std::exception& ex){
        std::cout<< "Exception in main after writing data: " << ex.what();
    }
	return 0;
}

// need to add exception safety
