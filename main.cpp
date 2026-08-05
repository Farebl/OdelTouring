import Functions;

ListSharedsManager_t Managers;
ListSharedsCustomer_t Customers;
ListSharedsTrip_t Trips;
#include <iostream>
int main() {
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
        std::cout<< "Exception in interface: " << ex.what();
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
// need to soleve problem with default Trip-constructor --> need to separate true default and param (throw out default params)

<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
// need to add exception safety
