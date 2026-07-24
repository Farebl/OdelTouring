#include "Functions.h"

ListSharedsManager_t Managers;
ListSharedsCustomer_t Customers;
ListSharedsTrip_t Trips;

int main() {

	Start(Managers, Customers, Trips); // Запуск програми: зчитування даних, інтерфейс, збереження даних

	return 0;
}

