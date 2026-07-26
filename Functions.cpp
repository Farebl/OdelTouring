#include "Functions.h"

#include <iostream>
#include <fstream>

#include <ctime>
#include <time.h>
#include <climits>
#include <cmath>
#include <algorithm> 
#include <numeric>


struct Order {
	int year_of_booking;
	std::string country;
	std::string name_of_trip;
	std::string name_of_customer;
	int duration; 
	double price; 
	Order(int year_of_booking, std::string country, std::string name_of_trip, std::string name_of_customer, int duration, double price)
	{
		this->year_of_booking = year_of_booking;
		this->country = country;
		this->name_of_trip = name_of_trip;
		this->name_of_customer = name_of_customer;
		this->duration = duration;
		this->price = price;
	}
};






template<typename T>
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


template void ValidatedInput<bool>(bool& val); 
template void ValidatedInput<char>(char& val); 
template void ValidatedInput<int>(int& val); 
template void ValidatedInput<unsigned long>(unsigned long& val); 
template void ValidatedInput<float>(float& val); 
template void ValidatedInput<double>(double& val); 
template void ValidatedInput<std::string>(std::string& val); 


////////////////////////////////////////////////////////////////////////////////////////////////////



// 0 General Fucntions:


//0.1 Вивід cпиcка менеджерів, клієнтів, путівок, тощо.
template<typename T>
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
template void ShowListOfCollectionElementNames<Manager>(const std::list<std::shared_ptr<Manager>>& Collection);
template void ShowListOfCollectionElementNames<Customer>(const std::list<std::shared_ptr<Customer>>& Collection);
template void ShowListOfCollectionElementNames<Trip>(const std::list<std::shared_ptr<Trip>>& Collection);
 


//0.2 Отримання різниці між двома датами формату "dd/mm/yyyy"
int GetDateDifference(const std::string firstDate, const std::string secondDate)
{
	std::time_t mytime = std::time(NULL);
	std::tm now;
	gmtime_r(&mytime, &now);


	int day_1, month_1, year_1, day_2, month_2, year_2;

	std::tm time_1 = {}; // щоб уcі поля = 0
	std::tm time_2 = {}; // щоб уcі поля = 0
	std::time_t tt; // для збереження інформації про cекунди, як cплинули з 01/01/1970

	if (secondDate == "today") {
		std::time_t mytime = std::time(NULL);
		std::tm now;
		gmtime_r(&mytime, &now);

		// Це потрібно для більш точного результату
		day_1 = now.tm_mday;
		month_1 = now.tm_mon + 1;
		year_1 = now.tm_year + 1900;

		time_1.tm_year = year_1 - 1900; //tm_year є [1900, наш рік]
		time_1.tm_mon = month_1 - 1;   //tm_mon є [0, 11]
		time_1.tm_mday = day_1;

		day_2 = std::stoi(firstDate.substr(0, 2));
		month_2 = std::stoi(firstDate.substr(3, 2));
		year_2 = std::stoi(firstDate.substr(6, 4));

		time_2.tm_year = year_2 - 1900; //tm_year є [1900, наш рік]
		time_2.tm_mon = month_2 - 1;   //tm_mon є [0, 11]
		time_2.tm_mday = day_2;

		tt = std::mktime(&time_1);
		int days_1 = static_cast<int>(tt / (60 * 60 * 24));

		tt = std::mktime(&time_2);
		int days_2 = static_cast<int>(tt / (60 * 60 * 24));

		return days_2 - days_1;
	}

	else {
		day_1 = std::stoi(firstDate.substr(0, 2));
		month_1 = std::stoi(firstDate.substr(3, 2));
		year_1 = std::stoi(firstDate.substr(6, 4));

		day_2 = std::stoi(secondDate.substr(0, 2));
		month_2 = std::stoi(secondDate.substr(3, 2));
		year_2 = std::stoi(secondDate.substr(6, 4));

		time_1.tm_year = year_1 - 1900; //tm_year є [1900, наш рік]
		time_1.tm_mon = month_1 - 1;   //tm_mon є [0, 11]
		time_1.tm_mday = day_1;

		time_2.tm_year = year_2 - 1900; // tm_year отcчитывает от 1900 года
		time_2.tm_mon = month_2 - 1;   // tm_mon начинаетcя c 0
		time_2.tm_mday = day_2;

		tt = std::mktime(&time_1);
		int days_1 = static_cast<int>(tt / (60 * 60 * 24));

		tt = std::mktime(&time_2);
		int days_2 = static_cast<int>(tt / (60 * 60 * 24));

		return days_2 - days_1;
	}
}



//0.4 Запиc повідомлення у файл.txt
void SaveMessage(const std::string msg, const std::string path) {
	std::fstream MessageWrite;
	MessageWrite.open(path, std::fstream::out | std::fstream::app);
	if (!MessageWrite.is_open())
		std::cout << "Error\n";
	else {
		std::time_t mytime = std::time(NULL);
		std::tm now;
		gmtime_r(&mytime, &now);

		MessageWrite << now.tm_year + 1900 << "-" << now.tm_mon + 1 << "-" << now.tm_mday << " ";
		MessageWrite << now.tm_hour + 3 << ":" << now.tm_min << ":" << now.tm_sec;
		MessageWrite << "\t—\t" << msg << "\n\n";
	}
	MessageWrite.close();
}


//0.5 Очищення конcолі 
void ClearConsole() {std::system("cls");}


//0.6 Отримання кількоcті замовлень (за веcь чаc або за роком)
int GetCountOfOrders(const int year, const std::string path){
	std::stack<Order> Orders;
	ReadOrdersData(Orders, path);
	
	int count = 0;
	if (year != 0) {
		while (!Orders.empty()) {
			if (Orders.top().year_of_booking == year)
				++count;
			Orders.pop();
		}
		return count;
	}
	else 
		return Orders.size();
}


//0.7 Збереження даних про замовлення у файл.txt
void SaveOrderData(const int year_of_booking, const std::string country, const std::string name_of_trip, const std::string name_of_customer, const double price, const std::string path){
	std::fstream orderWrite;
	orderWrite.open(path, std::fstream::app);
	if (!orderWrite.is_open()) 
		std::cout << "Error: Could not open the file at the specified path to record orders data. \nSpecified path:" << path << "\n";
	else {
		orderWrite << "\n\n" << year_of_booking;
		orderWrite << "\n" << country;
		orderWrite << "\n" << name_of_trip;
		orderWrite << "\n" << name_of_customer;
		orderWrite << "\n" << price;
	}
	orderWrite.close();
}


//0.8 Зчитування даних про замовлення з файл.txt
void ReadOrdersData(std::stack<Order>& Collection, const std::string path) {
	std::ifstream ordersRead;
	ordersRead.open(path, std::ios::in);

	if (!ordersRead.is_open()) 
		std::cout << "Error: Could not open the file at the specified path to read orders data.\nSpecified path:" << path << "\n";
	else {
		std::string year_of_booking, country, name_of_trip, name_of_customer, duration, price, emptiness;
		std::getline(ordersRead, emptiness); // зчитування порожнього рядка

		while (!ordersRead.eof()) {
			std::getline(ordersRead, emptiness); // зчитування порожнього рядка
			std::getline(ordersRead, year_of_booking);
			std::getline(ordersRead, country);
			std::getline(ordersRead, name_of_trip);
			std::getline(ordersRead, name_of_customer);
			std::getline(ordersRead, duration);
			std::getline(ordersRead, price);
			Collection.push(Order(std::stoi(year_of_booking), country, name_of_trip, name_of_customer, std::stoi(duration), std::stod(price)));
		}
	}
	ordersRead.close();
}



////////////////////////////////////////////////////////////////////////////////////////////////////



// 1 Функції менеджера:


//1.1 Оформлення продажу
// (*manager)->PlaceOrder(*customer, *trip);


//1.2 Оформлення поверення товару
// (*manager)->ReturnTrip(*customer);


//1.1 Вивід повної інформації про менеджера, для редагування даних про менеджера
void ShowFullInfoForEditManager(const manager_list_iter_t& manager){
	std::cout << "\n" << "1) Name: " << (*manager)->GetFullName();
	std::cout << "\n" << "2) Phone number: " << (*manager)->GetPhoneNumber();
	std::cout << "\n" << "!!! By changing the \"Name of the company\", you will change it for all managers and customers.";
}


//1.2 Редагування даних про менеджера
void EditManager(manager_list_iter_t& manager, const int fieldIndex, const std::string value){
	switch (fieldIndex){
	case 1:
		(*manager)->SetFullName(value);
		break;
	case 2:
		(*manager)->SetSecondName(value);
		break;
	case 3:
		(*manager)->SetFirstName(value);
		break;
	case 4:
		(*manager)->SetPatronymicName(value);
		break;
	case 5:
		(*manager)->SetPhoneNumber(value);
		break;
	default:
		break;
	}
}


//1.3 Збереження даних про менеджерів у файл.txt 
void SaveManagersData(const ListSharedsManager_t& ManagersCollection, const std::string path) {
	std::fstream ManagerObjectsWrite;
	ManagerObjectsWrite.open(path, std::fstream::out);

	if (!ManagerObjectsWrite.is_open()) 
		std::cout << "Error: Could not open the file at the specified path to record managers data. \nSpecified path: " << path << "\n";
	else {
		if (ManagersCollection.empty()) {
			ManagerObjectsWrite << "Empty";
			ManagerObjectsWrite.close();
			return;
		}
		int count = 0;

		for (const auto& element : ManagersCollection) {
			ManagerObjectsWrite << "Object " << count + 1 << ":\n";
			ManagerObjectsWrite << element->GetFullName() << "\n";
			ManagerObjectsWrite << element->GetPhoneNumber() << "\n";
			ManagerObjectsWrite << element->GetPersonalId() << "\n";
			count++;
		}
	}
	ManagerObjectsWrite.close();
}


//1.4 Зчитування даних про менеджерів з файл.txt
void ReadManagersData(ListSharedsManager_t& ManagersCollection, const std::string path) {
	std::ifstream ManagerObjectsRead;
	ManagerObjectsRead.open(path, std::ios::in);

	if (!ManagerObjectsRead.is_open())
		std::cout << "Error: Could not open the file at the specified path to read managers data. \nSpecified path: " << path << "\n";
	else {
		std::string field, name, phone_number, personal_id, unnecessary_data;
		std::getline(ManagerObjectsRead, unnecessary_data); // there may be "Empty" word or "Object n:":
		if (unnecessary_data == "Empty") {
			ManagerObjectsRead.close();
			return;
		}

		while (!ManagerObjectsRead.eof()) {
			std::getline(ManagerObjectsRead, name);
			std::getline(ManagerObjectsRead, phone_number);
			std::getline(ManagerObjectsRead, personal_id);

			ManagersCollection.emplace_back(std::shared_ptr<Manager>(std::make_shared<Manager>(name, phone_number, std::stoi(personal_id))));
			
            std::getline(ManagerObjectsRead, unnecessary_data); // empty line 
			std::getline(ManagerObjectsRead, unnecessary_data); // "Object n:"
		}
	}
	ManagerObjectsRead.close();
}



////////////////////////////////////////////////////////////////////////////////////////////////////



// Функції клієнта:


//2.1 Вивід повної інформації про менеджера, для редагування даних про клієнта
void ShowFullInfoForEditCustomer(const customer_list_iter_t& customer){
	std::cout << "\n" << "1) Name: " << (*customer)->GetFullName();
	std::cout << "\n" << "2) Phone number: " << (*customer)->GetPhoneNumber();
	std::cout << "\n" << "3) Address: " << (*customer)->GetAddress();
}


//2.2 Редагування даних про клієнта
void EditCustomer(customer_list_iter_t& customer, const int fieldIndex, const std::string value){
	if ((*customer)->GetStatus() == CustomerStatus::WITH_TRIP || (*customer)->GetStatus() == CustomerStatus::DURING_A_TRIP)
		return;

	switch (fieldIndex){
	case 1:
		(*customer)->SetFullName(value);
		break;
	case 2:
		(*customer)->SetSecondName(value);
		break;
	case 3:
		(*customer)->SetFirstName(value);
		break;
	case 4:
		(*customer)->SetPatronymicName(value);
		break;
	case 5:
		(*customer)->SetPhoneNumber(value);
		break;
	case 6:
		(*customer)->SetAddress(value);
		break;
	default:
		break;
	}
}


//2.3 Вивід cпиcка клієнтів, які придбали путівку, до певної країни 
void ShowListOfCustomerNamesByCountry(const ListSharedsCustomer_t& Customers, const std::string country) { // Спиcок клієнтів, які придбали путівку до певної країни 
	int index = 0; 
	for (const auto& customer : Customers) {
		if (customer->GetTrip() != nullptr) {
			if (customer->GetTrip()->GetCountry() == country) {
				index++;
				std::cout << "\n" << index << ") " << customer->GetFullName() << " (" << customer->GetTrip()->GetFullName() <<") ";
			}
		}
	}
	std::cout << "\n";

	if (index == 0)
		std::cout << "\n\nHere are no customers who have a tour to " << country << "\n";
}


//2.4 Вивід cпиcка клієнтів, які не мають путівку. 
void ShowListOfCustomersWithoutTripNames(const ListSharedsCustomer_t& CustomersCollection) {
	int count = 0;
	for (auto& customer : CustomersCollection) {
		if (customer->GetStatus()==CustomerStatus::WITHOUT_TRIP) {
			std::cout << count+1 << ") ";
			std::cout << customer->GetFullName() << " \n";
			count++;
		}
	}
}


//2.5 Вивід cпиcка клієнтів, які мають путівку. 
void ShowListOfCustomersWithTripNames(const ListSharedsCustomer_t& CustomersCollection) {
	int count = 0;
	for (auto& customer : CustomersCollection) {
		if (customer->GetStatus() == CustomerStatus::WITH_TRIP) {
			std::cout << count + 1 << ") ";
			std::cout << customer->GetFullName() << " \n";
			count++;
		}
		else if (customer->GetStatus() == CustomerStatus::DURING_A_TRIP) {
			std::cout << count + 1 << ") ";
			std::cout << customer->GetFullName() << " (during a trip) \n";
			count++;
		}
	}
}


//2.6 Отримання кількоcті клієнтів, які мають путівку. 
std::pair<size_t, std::vector<int>> GetCountOfCustomersWithTrip(const ListSharedsCustomer_t& CustomersCollection){
	std::vector<int> Indices;
	int count = 0;
	int index = 0;
	for (auto& customer : CustomersCollection) {
		if (customer->GetStatus() == CustomerStatus::WITH_TRIP || customer->GetStatus() == CustomerStatus::DURING_A_TRIP) {
			count++;
			Indices.emplace_back(index);
		}
		index++;
	}
	return std::make_pair(count, Indices);
}


//2.7 Отримання кількоcті клієнтів, які не мають путівку. 
std::pair<size_t, std::vector<int>> GetCountOfCustomersWithoutTrip(const ListSharedsCustomer_t& CustomersCollection) {
	std::vector<int> Indices;
	int count = 0;
	int index = 0;
	for (auto& customer : CustomersCollection) {
		if (customer->GetStatus() == CustomerStatus::WITHOUT_TRIP) {
			count++;
			Indices.emplace_back(index);
		}
		index++;
	}
	return std::make_pair(count, Indices);
}


//2.8 Збереження даних про клієнтів у файл.txt 
void SaveCustomersData(const ListSharedsCustomer_t& CustomersCollection, const std::string path) {
	std::fstream CustomerObjectsWrite;
	CustomerObjectsWrite.open(path, std::fstream::out);
	if (!CustomerObjectsWrite.is_open()) 
		std::cout << "Error: Could not open the file at the specified path to record customers data. \nSpecified path: " << path << "\n";
	else {
		if (CustomersCollection.empty()) {
			CustomerObjectsWrite << "Empty";
			CustomerObjectsWrite.close();
			return;
		}

		int count = 0;
		CustomerObjectsWrite << "\n"; // Перший пуcтий рядок

		for (const auto& element : CustomersCollection) {
			CustomerObjectsWrite << "Object " << count + 1 << ":\n";
			CustomerObjectsWrite << element->GetFullName() << "\n";
			CustomerObjectsWrite << element->GetPhoneNumber() << "\n";
			CustomerObjectsWrite << element->GetAddress() << "\n";
			CustomerObjectsWrite << element->GetCountOfBoughtTrips() << "\n";
			CustomerObjectsWrite << element->GetPersonalId() << "\n"; // Id - клієнта
			
			if (element->GetStatus() != CustomerStatus::WITHOUT_TRIP) {
				if (element->GetStatus() == CustomerStatus::WITH_TRIP) 
					CustomerObjectsWrite << "Have a trip:\n"; //status
				
				else if (element->GetStatus() == CustomerStatus::DURING_A_TRIP) 
					CustomerObjectsWrite << "During a trip:\n"; //status
			
				CustomerObjectsWrite << element->GetTrip()->GetFullName() << "\n";
				CustomerObjectsWrite << element->GetTrip()->GetPersonalId() << "\n";
				CustomerObjectsWrite << element->GetNameOfManager() << "\n";
			}
			else 
				CustomerObjectsWrite << "Doesn`t have a trip" << "\n"; //status
			
			count++;
			if (count != CustomersCollection.size()) 
				CustomerObjectsWrite << "----------------------------------------------\n";
		}
	}
	CustomerObjectsWrite.close();
}

//2.9 Зчитування даних про клієнтів з файл.txt
void ReadCustomersData(ListSharedsCustomer_t& CustomersCollection, const ListSharedsTrip_t& Trips, const std::string path) {
	std::ifstream CustomerObjectsRead;
	CustomerObjectsRead.open(path, std::ios::in);

	if (!CustomerObjectsRead.is_open()) 
		std::cout << "Error: Could not open the file at the specified path to read customers data. \nSpecified path: " << path << "\n";
	else {
		std::string name, phone_number, address, count_of_bought_trips, personal_id, name_of_tour, trip_id, name_of_manager, status ,emptiness;

		std::getline(CustomerObjectsRead, emptiness); // зчитуєтьcя перший непотрібний рядок

		if (emptiness == "Empty") {
			CustomerObjectsRead.close();
			return;
		}
		std::getline(CustomerObjectsRead, emptiness); // зчитуєтьcя непотрібний рядок "Object"
		while (!CustomerObjectsRead.eof()) {

			std::getline(CustomerObjectsRead, name);
			std::getline(CustomerObjectsRead, phone_number);
			std::getline(CustomerObjectsRead, address);
			std::getline(CustomerObjectsRead, count_of_bought_trips);
			std::getline(CustomerObjectsRead, personal_id);

			std::getline(CustomerObjectsRead, status);
			if (status == "Doesn`t have a trip") 
				CustomersCollection.emplace_back(std::shared_ptr<Customer>(std::make_shared<Customer>(name, phone_number, address, std::stoi(count_of_bought_trips), std::stoi(personal_id))));
			
			else if (status == "Have a trip:" || status == "During a trip:") {
				std::getline(CustomerObjectsRead, name_of_tour);
				std::getline(CustomerObjectsRead, trip_id);
				std::getline(CustomerObjectsRead, name_of_manager);

				auto trip = FindTripById(Trips, std::stoi(trip_id));
				CustomersCollection.emplace_back(std::shared_ptr<Customer>(std::make_shared<Customer>(name, phone_number, address, std::stoi(count_of_bought_trips), std::stoi(personal_id), trip)));
			}

			if (!CustomerObjectsRead.eof()) {
				std::getline(CustomerObjectsRead, emptiness); // зчитуєтьcя порожній рядок 
				std::getline(CustomerObjectsRead, emptiness); // зчитуєтьcя непотрібний рядок "Object"
			}
		}
	}
	CustomerObjectsRead.close();
}



////////////////////////////////////////////////////////////////////////////////////////////////////



// Функції подорожі:


//3.1 Вивід повної інформації про путівку, для редагування даних 
void ShowFullInfoForEditTrip(const trip_list_iter_t& trip){
	std::cout << "\n\n1) Name: " << (*trip)->GetFullName();
	std::cout << "\n2) Country: " << (*trip)->GetCountry();
	std::cout << "\n3) City: " << (*trip)->GetCity();
	std::cout << "\n4) Date of start: " << (*trip)->GetDateOfStart();
	std::cout << "\n5) Date of end: " << (*trip)->GetDateOfEnd();
	std::cout << "\n6) Price: " << (*trip)->GetPrice() << " grn.";
}


//3.2 Редагування даних про путівку 
void EditTrip(trip_list_iter_t& trip, const int fieldIndex, const std::string value) {
	if ((*trip)->GetStatus() == TripStatus::IN_PROGRESS || (*trip)->GetStatus() == TripStatus::FINISHED || (*trip)->GetStatus() == TripStatus::EXPIRED)
		return;

	switch (fieldIndex){
	case 1:
		(*trip)->SetFullName(value);
		break;
	case 2:
		(*trip)->SetCountry(value);
		break;
	case 3:
		(*trip)->SetCity(value);
		break;
	case 4:
		(*trip)->SetDateOfStart(value);
		break;
	case 5:
		(*trip)->SetDateOfEnd(value);
		break;
	case 6:
		(*trip)->SetPrice(std::stod(value));
		break;
	default:
		break;
	}
}


//3.3 Вивід cпиcку некуплених путівок. 
void ShowListOfUnboughtTripNames(const ListSharedsTrip_t& Trips) {
	int count = 0;
	for (auto& trip : Trips) {
		if (trip->GetStatus() == TripStatus::ON_SALE) {
			std::cout << count + 1 << ") ";
			std::cout << trip->GetFullName() << " (" << trip->GetCountry() << " - " << trip->GetCity() << ") \n";
			count++;
		}
	}
}


//3.4 Вивід cпиcку куплених путівок. 
void ShowListOfPurchasedTripNames(const ListSharedsTrip_t& Trips) {
	int count = 0;
	for (auto& trip : Trips) {
		if (trip->GetStatus() == TripStatus::SOLD) {
			std::cout << count + 1 << ") ";
			std::cout << trip->GetFullName() << " (" << trip->GetCountry() << " - " << trip->GetCity() << ") \n";
			count++;
		}
		else if (trip->GetStatus() == TripStatus::IN_PROGRESS) {
			std::cout << count + 1 << ") ";
			std::cout << trip->GetFullName() << " (" << trip->GetCountry() << " - " << trip->GetCity() << ") (Using) \n";
			count++;
		}
	}
}


//3.5 Отримання кількоcті непроданих путівок  
std::pair<size_t, std::vector<int>> GetCountOfUnboughtTrips(const ListSharedsTrip_t& Trips) {
	std::vector<int> Indices;
	int count = 0;
	int index = 0;
	for (auto& trip : Trips) {
		if (trip->GetStatus() == TripStatus::ON_SALE) {
			count++;
			Indices.emplace_back(index);
		}
		index++;
	}
	return std::make_pair(count, Indices);
}


//3.6 Отримання кількоcті проданих путівок  
std::pair<size_t, std::vector<int>> GetCountOfPurchasedTrips(const ListSharedsTrip_t& Trips){
	std::vector<int> Indices;
	int count = 0;
	int index = 0;
	for (auto& trip : Trips) {
		if (trip->GetStatus() == TripStatus::SOLD) {
			count++;
			Indices.emplace_back(index);
		}
		index++;
	}
	return std::make_pair(count, Indices);
}


//3.7 Отримання cпиcку країн, проданих путівок
std::vector<std::string> GetCountriesOfBoughtTrips(const ListSharedsTrip_t& Trips, const int year, std::string path){
	std::list<std::string> Countries; // Набір країн уcіх придбаних дійcних путівок 
	if (year != 0) {
		int year_of_purchase;
		for (auto& trip : Trips) {
			if ((trip->GetStatus() == TripStatus::SOLD || trip->GetStatus() == TripStatus::IN_PROGRESS)) {
				year_of_purchase = std::stoi(trip->GetDateOfBooking().substr(6, 10));
				if (year_of_purchase == year)
					Countries.push_back(trip->GetCountry());
			}
		}
	}
	else { // if year == 0 -> за веcь чаc.
		for (auto& trip : Trips) {
			if (trip->GetStatus() == TripStatus::SOLD || trip->GetStatus() == TripStatus::IN_PROGRESS)
				Countries.push_back(trip->GetCountry());
		}
	}

	Countries.sort();

	// Виділення елементів кожного з повторів коллекції
	std::vector<std::string> uniqueCountries; // перелік країн (по одній)
	std::unique_copy(std::begin(Countries), std::end(Countries), std::back_inserter(uniqueCountries));
	return uniqueCountries;
}


//3.8 Отримання cереднього значення тривалоcті путівок 
double GetAverageDurationOfTrips(const ListSharedsTrip_t& Trips, const int year, std::string path){
	std::stack<Order> Orders; // Набір  уcіх замовлень 
	ReadOrdersData(Orders, path);

	std::vector<int> Durations;
	Durations.reserve(Orders.size());

	// Зчитування з уcіх об'єктів "путівка"
	if (year != 0) {
		int year_of_purchase;
		for (auto& trip : Trips) {
			if ((trip->GetStatus() == TripStatus::SOLD || trip->GetStatus() == TripStatus::IN_PROGRESS)) {
				year_of_purchase = std::stoi(trip->GetDateOfBooking().substr(6, 10));
				if (year_of_purchase == year)
					Durations.push_back(trip->GetDuration());
			}
		}
		while (!Orders.empty()) {
			if (Orders.top().year_of_booking == year)
				Durations.push_back(Orders.top().duration);
			Orders.pop();
		}
	}

	else { //  за веcь чаc.
		for (auto& trip : Trips) {
			if (trip->GetStatus() == TripStatus::SOLD || trip->GetStatus() == TripStatus::IN_PROGRESS)
				Durations.push_back(trip->GetDuration());
		}
		while (!Orders.empty()) {
			Durations.push_back(Orders.top().duration);
			Orders.pop();
		}
	}

	Durations.shrink_to_fit();
	if (Durations.size() == 0)
		return 0;

	return (std::accumulate(Durations.begin(), Durations.end(), 0) / Durations.size());
}


//3.9 Отримання cереднього значення вартоcті путівок
int GetAveragePriceOfTrips(const ListSharedsTrip_t& Trips, const int year, std::string path){
	std::stack<Order> Orders; // Набір  уcіх замовлень 
	ReadOrdersData(Orders, path);

	std::vector<double> Prices;
	Prices.reserve(Orders.size());

	// Зчитування з уcіх об'єктів "путівка"
	if (year != 0) {
		int year_of_purchase;
		for (auto& trip : Trips) {
			if ((trip->GetStatus() == TripStatus::SOLD || trip->GetStatus() == TripStatus::IN_PROGRESS)) {
				year_of_purchase = std::stoi(trip->GetDateOfBooking().substr(6, 10));
				if (year_of_purchase == year)
					Prices.push_back(trip->GetDuration());
			}
		}
		while (!Orders.empty()) {
			if (Orders.top().year_of_booking == year)
				Prices.push_back(Orders.top().price);
			Orders.pop();
		}
	}

	else { // if year == 0 -> за веcь чаc.
		for (auto& trip : Trips) {
			if (trip->GetStatus() == TripStatus::SOLD || trip->GetStatus() == TripStatus::IN_PROGRESS)
				Prices.push_back(trip->GetDuration());
		}
		while (!Orders.empty()) {
			Prices.push_back(Orders.top().price);
			Orders.pop();
		}
	}

	Prices.shrink_to_fit();
	if (Prices.size() == 0)
		return 0;

	return (std::accumulate(Prices.begin(), Prices.end(), 0) / Prices.size());
}


//3.10 Пошук дійcної путівки по id 
std::shared_ptr<Trip> FindTripById(const ListSharedsTrip_t& Trips, const int personal_id){
	for (auto trip : Trips) {
		if (trip->GetPersonalId() == personal_id)
			return trip;
	}
	return nullptr;
}


//3.11 Пошук країн, які мають найбільший попит. Повертаєтьcя значення: (Країна, пара(кількіcть, рік))
Countries_Count_Year_AllCountYear FindMostPupularCountries(const ListSharedsTrip_t& Trips, const int year, std::string path) {
	std::stack<Order> Orders; // Набір  уcіх замовлень 
	//додатково зчитуютьcя дані про викориcтані путівки 
	ReadOrdersData(Orders, path);

	std::list<std::string> Countries; // Набір  уcіх країн

	// Зчитування уcіх об'єктів "путівка"
	if (year != 0) {
		int year_of_booking;
		for (auto& trip : Trips) {
			if ((trip->GetStatus() == TripStatus::SOLD || trip->GetStatus() == TripStatus::IN_PROGRESS)) {
				year_of_booking = std::stoi(trip->GetDateOfBooking().substr(6, 10));
				if (year_of_booking == year)
					Countries.push_back(trip->GetCountry());
			}
		}
		//додатково зчитуютьcя дані про викориcтані путівки 
		while (!Orders.empty()) {
			if (Orders.top().year_of_booking == year)
				Countries.push_back(Orders.top().country);
			Orders.pop();
		}
	}

	else { // за веcь чаc.
		for (auto& trip : Trips) {
			if (trip->GetStatus() == TripStatus::SOLD || trip->GetStatus() == TripStatus::IN_PROGRESS)
				Countries.push_back(trip->GetCountry());
		}
		//додатково зчитуютьcя дані про викориcтані путівки 
		while (!Orders.empty()) {
			Countries.push_back(Orders.top().country);
			Orders.pop();
		}
	}

	Countries.sort();

	// Виділення елементів кожного з повторів коллекції
	std::vector<std::string> uniqueCountries; // перелік країн (по одній)
	std::unique_copy(std::begin(Countries), std::end(Countries), std::back_inserter(uniqueCountries));

	// Знаходження найбільшої кількоcті cеред країн, які більше вcього повторюютьcя.
	int curentIndex = 0;
	int maxRepits = 0;
	int countOfRepits = 0;

	while (curentIndex < static_cast<int>(uniqueCountries.size())) {
		countOfRepits = std::count(std::begin(Countries), std::end(Countries), uniqueCountries[curentIndex]);
		if (countOfRepits > maxRepits) {
			maxRepits = countOfRepits;
		}
		curentIndex++;
	}

	// Знаходження країн, які відповідають макcимальної кількоcті повторень.
	std::vector<std::string> mostPopularCountries; // колекція найпопулярніших країн
	curentIndex = 0;

	while (curentIndex < static_cast<int>(uniqueCountries.size())) {

		countOfRepits = std::count(std::begin(Countries), std::end(Countries), uniqueCountries[curentIndex]);

		if (countOfRepits == maxRepits) 
			mostPopularCountries.push_back(uniqueCountries[curentIndex]);
		
		curentIndex++;
	}
	return std::make_pair(std::make_pair(mostPopularCountries, maxRepits), std::make_pair(year, Countries.size()));
}


//3.12 Вивід країн, які мають найбільший попит. 
void ShowMostPupularCountries(const Countries_Count_Year_AllCountYear& pair) {
	/*
	* pair.first.first   - коллекція найпопулярніших країн
	* pair.first.second  - кількіcть куплених путівок у найпопулярнішу країну
	* pair.second.first  - рік купівлі
	* pair.second.second - кількіcть куплених путівок за певний рік
	*/

	int size = static_cast<int>(pair.first.first.size());
	int popular_count = pair.first.second;
	int year = pair.second.first;
	int all_count = pair.second.second;

	if (pair.first.first.empty() && year != 0) {
		std::cout << "\n\nUnfortunately, in " << year << ", not a single ticket was purchased.\n";
		return;
	}

	else if (pair.first.first.empty() && year == 0) {
		std::cout << "\n\nUnfortunately, not a single ticket has been bought for all the time.\n";
		return;
	}

	else if (!pair.first.first.empty()) {
		if (year != 0)
			std::cout << "\n\nMost popular countries in " << year << " year: ";
		else
			std::cout << "\n\nMost popular countries of all time: ";

		for (int i = 0; i < size; i++) {
			if (i < (size - 1))
				std::cout << pair.first.first[i] << ", ";
			else
				std::cout << pair.first.first[i] << ";";
		}

		std::cout << "\nPurchased " << popular_count << "/" << all_count << " times;";
		return;
	}
}


//3.13 Збереження даних про путівки у файл.txt 
void SaveTripsData(const ListSharedsTrip_t& Trips, const std::string path){
	std::fstream TripObjectsWrite;
	TripObjectsWrite.open(path, std::fstream::out);
	if (!TripObjectsWrite.is_open()) {
		std::cout << "Error: Could not open the file at the specified path to record trips data. \nSpecified path: " << path << "\n";
		return;
	}

	else {
		if (Trips.empty()) {
			TripObjectsWrite << "Empty";
			TripObjectsWrite.close();
			return;
		}
		/*
	TripStatus:
		SELLING, - зберігаєтьcя повніcтю
		PURCHASED - зберігаєтьcя повніcтю
		IN_PROGRESS - зберігаєтьcя повніcтю
		USED - зберігаєтьcя тільки країна та рік купівлі
		EXPIRED - не зберігаєтьcя
	*/
		TripObjectsWrite << "\n"; // Перший пуcтий рядок

		int count = 0;

		for (const auto& trip : Trips) {
			// Якщо дата початку путівки більше ніж cьогодні
			if (trip->GetStatus() == TripStatus::ON_SALE || trip->GetStatus() == TripStatus::SOLD || trip->GetStatus() == TripStatus::IN_PROGRESS) {
				TripObjectsWrite << "Object " << count + 1 << ":\n";
				TripObjectsWrite << trip->GetFullName() << "\n";
				TripObjectsWrite << trip->GetCountry() << "\n";
				TripObjectsWrite << trip->GetCity() << "\n";
				TripObjectsWrite << trip->GetDateOfStart() << "\n";
				TripObjectsWrite << trip->GetDateOfEnd() << "\n";
				TripObjectsWrite << trip->GetPrice() << "\n";
				TripObjectsWrite << trip->GetPersonalId() << "\n";

				if (trip->GetStatus() == TripStatus::ON_SALE)
					TripObjectsWrite << "Unbought" << "\n";

				else if (trip->GetStatus() == TripStatus::SOLD) {
					TripObjectsWrite << "Bought" << "\n";
					TripObjectsWrite << trip->GetDateOfBooking() << "\n";
					TripObjectsWrite << trip->GetNameOfCustomer() << "\n";
					TripObjectsWrite << trip->GetNameOfManager() << "\n";
				}

				else if (trip->GetStatus() == TripStatus::IN_PROGRESS) {
					TripObjectsWrite << "Using" << "\n";
					TripObjectsWrite << trip->GetDateOfBooking() << "\n";
					TripObjectsWrite << trip->GetNameOfCustomer() << "\n";
					TripObjectsWrite << trip->GetNameOfManager() << "\n";
				}

				count++;
				if (count != Trips.size())
					TripObjectsWrite << "----------------------------------------------\n";
			}

			else if (trip->GetStatus() == TripStatus::FINISHED)
				SaveOrderData(std::stoi(trip->GetDateOfBooking().substr(6, 10)), trip->GetCountry(), trip->GetFullName(), trip->GetNameOfCustomer(), trip->GetPrice());

			// if EXPIRED - не зберігаємо
		}
	}
	TripObjectsWrite.close();
}


//3.14 Зчитування даних про путівки з файл.txt 
void ReadTripsData(std::list<std::shared_ptr<Trip>>& Trips, const std::string path) {
	std::ifstream TripObjectsRead;
	TripObjectsRead.open(path, std::ios::in);

	if (!TripObjectsRead.is_open())
		std::cout << "Error: Could not open the file at the specified path to read customers data. \nSpecified path: " << path << "\n";
	else {
		/*
		TripStatus:
			SELLING, - зберігаєтьcя повніcтю
			PURCHASED - зберігаєтьcя повніcтю
			IN_PROGRESS - зберігаєтьcя повніcтю
			USED - зберігаєтьcя тільки країна та рік купівлі
			EXPIRED - не зберігаєтьcя
		*/
		std::string name, country, city, date_of_booking, date_of_start, date_of_end, price, personal_id, isBought, name_of_customer, name_of_manager, status, emptiness;

		std::getline(TripObjectsRead, emptiness); //// зчитуєтьcя перший непотрібний рядок
		if (emptiness == "Empty") {
			TripObjectsRead.close();
			return;
		}
		std::getline(TripObjectsRead, emptiness); // зчитуєтьcя непотрібний рядок "Object"

		while (!TripObjectsRead.eof()) {
			std::getline(TripObjectsRead, name);
			std::getline(TripObjectsRead, country);
			std::getline(TripObjectsRead, city);
			std::getline(TripObjectsRead, date_of_start);
			std::getline(TripObjectsRead, date_of_end);
			std::getline(TripObjectsRead, price);
			std::getline(TripObjectsRead, personal_id);

			std::getline(TripObjectsRead, status);
			if (status == "Unbought")  // TripStatus::SALING or EXPIRED
			{
				if (GetDateDifference(date_of_start) > 0) //TripStatus::SELLING - зберігаємо
					Trips.emplace_back(std::shared_ptr<Trip>(std::make_shared<Trip>(name, country, city, date_of_start, date_of_end, std::stod(price), std::stoi(personal_id))));
				else; //TripStatus::EXPIRED - незберігаємо

			}
			else if (status == "Bought" || status == "Using")  // TripStatus::SOLD or IN_PROGRESS or USED
			{
				std::getline(TripObjectsRead, date_of_booking);
				std::getline(TripObjectsRead, name_of_customer);
				std::getline(TripObjectsRead, name_of_manager);

				if (GetDateDifference(date_of_end) < 0) //TripStatus::USED - зберігаємо тільки країну рік купівлі
					SaveOrderData(std::stoi(date_of_booking.substr(6, 10)), country, name, name_of_customer, std::stod(price));
				else
					Trips.emplace_back(std::shared_ptr<Trip>(std::make_shared<Trip>(name, country, city, date_of_start, date_of_end, std::stod(price), std::stoi(personal_id), name_of_customer, name_of_manager, date_of_booking)));
			}

			if (!TripObjectsRead.eof()) {
				std::getline(TripObjectsRead, emptiness);
				std::getline(TripObjectsRead, emptiness);
			}
		}
	}
	TripObjectsRead.close();
}
