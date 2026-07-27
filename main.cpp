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

