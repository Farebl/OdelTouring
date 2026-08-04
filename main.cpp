import Functions;

ListSharedsManager_t Managers;
ListSharedsCustomer_t Customers;
ListSharedsTrip_t Trips;

int main() {

    ReadManagersData(Managers, "Managers.txt");
    ReadTripsData(Trips, "Trips.txt");
    ReadCustomersData(Customers, Trips, "Customers.txt");

	Interface(Managers, Customers, Trips, "Managers.txt", "Customers.txt", "Trips.txt", "Orders.txt", "History.txt");
	
	SaveManagersData(Managers, "Managers.txt");
	SaveTripsData(Trips, "Trips.txt");
	SaveCustomersData(Customers, "Customers.txt");

	return 0;
}
// need to soleve problem with default Trip-constructor --> need to separate true default and param (throw out default params)

// need to add exception safety
