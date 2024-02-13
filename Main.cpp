#include "Functions.h" // <stack> + <algorithm> + <numeric> + <fstream> + Manager.h + Customer.h + Trip.h + Person.h +  <iostream> + <string> + <vector> + <list>

ListSharedsManager_t Managers; // Коллекція менеджерів
ListSharedsCustomer_t Customers;// Коллекція клієнтів
ListSharedsTrip_t Trips;// Коллекція путівок

int main() {

	Start(Managers, Customers, Trips); // Запуск програми: зчитування даних, інтерфейс, збереження даних

	return 0;
}

/*
Запити до системи.
1.Список менеджерів. 
2.Кількість клієнтів. 
3.Список клієнтів, які вибрали  певну країну. 
4.Середня вартість путівки.
5.Середня тривалість путівки. 
6.Країна, яка має найбільший попит.
*/
