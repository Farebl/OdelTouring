module;

#include <iostream>
#include <fstream>

#include <climits>
#include <cmath>
#include <chrono> 

#include <memory>
#include <numeric>
#include <algorithm>

#include <stack>
#include <vector>
#include <list>

module Functions; // Вказуємо ГОЛОВНИЙ модуль
import :QueryFunctions; // Імпортуємо свою ж партицію, щоб бачити її оголошення




////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& os, const std::chrono::year_month_day& ymd) {
    if (ymd.ok()) {
        os << static_cast<int>(ymd.year()) << "/"
           << static_cast<unsigned>(ymd.month()) << "/"
           << static_cast<unsigned>(ymd.day());
    } else {
        os << "Invalid Date";
    }
    return os;
}




// 0 General fucntions:

// yyyy/mm/dd --> std::chrono::year_month_day

std::chrono::year_month_day stringToYearMonthDay(const std::string& date){
    short y, m, d; // fot parsing inoput date: dauy, month, year;
    if (std::sscanf(date.c_str(), "%hd/%hd/%hd", &y, &m, &d) == 3){
        std::chrono::year_month_day date_of_start = std::chrono::year_month_day{
            std::chrono::year(y), 
            std::chrono::month(static_cast<unsigned>(m)), 
            std::chrono::day(static_cast<unsigned>(d))
        };
        return date_of_start;
    }
    else{
        throw std::runtime_error("Error: wrong format of data");
    }
}

// logging to a file
void SaveMessage(const std::string msg, const std::string path) {
	std::fstream MessageWrite;
	MessageWrite.open(path, std::fstream::out | std::fstream::app);
	if (!MessageWrite.is_open())
		std::cout << "Error\n";
	else {
        std::chrono::zoned_time now{std::chrono::current_zone(), std::chrono::system_clock::now()};

    	MessageWrite << now;
		MessageWrite << "\t-->\t" << msg << "\n\n";
	}
	MessageWrite.close();
}


void ClearConsole() {std::cout << "\033[2J\033[H" << std::flush;}


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


void SaveOrderData(int year_of_booking, const std::string& country, const std::string& name_of_trip, const std::string& name_of_customer, unsigned int duration, double price, const std::string& path){
	std::fstream orderWrite;
	orderWrite.open(path, std::fstream::app);
	if (!orderWrite.is_open()) 
		std::cout << "Error: Could not open the file at the specified path to record orders data. \nSpecified path:" << path << "\n";
	else {
		orderWrite << "\n\n" << year_of_booking;
		orderWrite << "\n" << country;
		orderWrite << "\n" << name_of_trip;
		orderWrite << "\n" << name_of_customer;
		orderWrite << "\n" << duration;
		orderWrite << "\n" << price;
	}
	orderWrite.close();
}


void ReadOrdersData(std::stack<Order>& Collection, const std::string path) {
	std::ifstream ordersRead;
	ordersRead.open(path, std::ios::in);

	if (!ordersRead.is_open()) 
		std::cout << "Error: Could not open the file at the specified path to read orders data.\nSpecified path:" << path << "\n";
	else {
		std::string year_of_booking, country, name_of_trip, name_of_customer, duration, price, emptiness;
		std::getline(ordersRead, emptiness); // ç÷èòóâàííÿ ïîðîæíüîãî ðÿäêà

		while (!ordersRead.eof()) {
			std::getline(ordersRead, emptiness); // ç÷èòóâàííÿ ïîðîæíüîãî ðÿäêà
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



// 1 Manager funcuions:



void ShowFullInfoForEditManager(const manager_list_iter_t& manager){
	std::cout << "\n" << "1) First name: " << (*manager)->GetFirstName();
	std::cout << "\n" << "2) Second name: " << (*manager)->GetSecondName();
	std::cout << "\n" << "3) Patronymic name: " << (*manager)->GetPatronymicName();
	std::cout << "\n" << "4) Phone number: " << (*manager)->GetPhoneNumber();
}


void EditManager(manager_list_iter_t& manager, const int fieldIndex, const std::string value){
	switch (fieldIndex){
	case 1:
		(*manager)->SetFirstName(value);
		break;	
    case 2:
		(*manager)->SetSecondName(value);
		break;
	case 3:
		(*manager)->SetPatronymicName(value);
		break;
	case 4:
		(*manager)->SetPhoneNumber(value);
		break;
	default:
		break;
	}
}


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



// Customer Functions


void ShowFullInfoForEditCustomer(const customer_list_iter_t& customer){
	std::cout << "\n" << "1) Name: " << (*customer)->GetFullName();
	std::cout << "\n" << "2) Phone number: " << (*customer)->GetPhoneNumber();
	std::cout << "\n" << "3) Address: " << (*customer)->GetAddress();
}


void EditCustomer(customer_list_iter_t& customer, const int fieldIndex, const std::string value){
	if ((*customer)->GetStatus() == CustomerStatus::WITH_TRIP || (*customer)->GetStatus() == CustomerStatus::DURING_A_TRIP)
		return;

	switch (fieldIndex){
	case 1:
		(*customer)->SetFirstName(value);
		break;
    case 2:
		(*customer)->SetSecondName(value);
		break;
	case 3:
		(*customer)->SetPatronymicName(value);
		break;
	case 4:
		(*customer)->SetPhoneNumber(value);
		break;
	case 5:
		(*customer)->SetAddress(value);
		break;
	default:
		break;
	}
}


void ShowListOfCustomerNamesByCountry(const ListSharedsCustomer_t& Customers, const std::string country) { // Ñïècîê êë³ºíò³â, ÿê³ ïðèäáàëè ïóò³âêó äî ïåâíî¿ êðà¿íè 
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
		CustomerObjectsWrite << "\n"; // Ïåðøèé ïócòèé ðÿäîê

		for (const auto& element : CustomersCollection) {
			CustomerObjectsWrite << "Object " << count + 1 << ":\n";
			CustomerObjectsWrite << element->GetFullName() << "\n";
			CustomerObjectsWrite << element->GetPhoneNumber() << "\n";
			CustomerObjectsWrite << element->GetAddress() << "\n";
			CustomerObjectsWrite << element->GetCountOfBoughtTrips() << "\n";
			CustomerObjectsWrite << element->GetPersonalId() << "\n"; // Id - êë³ºíòà
			
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

//2.9 Ç÷èòóâàííÿ äàíèõ ïðî êë³ºíò³â ç ôàéë.txt
void ReadCustomersData(ListSharedsCustomer_t& CustomersCollection, const ListSharedsTrip_t& Trips, const std::string path) {
	std::ifstream CustomerObjectsRead;
	CustomerObjectsRead.open(path, std::ios::in);

	if (!CustomerObjectsRead.is_open()) 
		std::cout << "Error: Could not open the file at the specified path to read customers data. \nSpecified path: " << path << "\n";
	else {
		std::string name, phone_number, address, count_of_bought_trips, personal_id, name_of_tour, trip_id, name_of_manager, status ,emptiness;

		std::getline(CustomerObjectsRead, emptiness); // ç÷èòóºòücÿ ïåðøèé íåïîòð³áíèé ðÿäîê

		if (emptiness == "Empty") {
			CustomerObjectsRead.close();
			return;
		}
		std::getline(CustomerObjectsRead, emptiness); // ç÷èòóºòücÿ íåïîòð³áíèé ðÿäîê "Object"
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
				std::getline(CustomerObjectsRead, emptiness); // ç÷èòóºòücÿ ïîðîæí³é ðÿäîê 
				std::getline(CustomerObjectsRead, emptiness); // ç÷èòóºòücÿ íåïîòð³áíèé ðÿäîê "Object"
			}
		}
	}
	CustomerObjectsRead.close();
}



////////////////////////////////////////////////////////////////////////////////////////////////////



// Trips functions:


void ShowFullInfoForEditTrip(const trip_list_iter_t& trip){
	std::cout << "\n\n1) Name: " << (*trip)->GetFullName();
	std::cout << "\n2) Country: " << (*trip)->GetCountry();
	std::cout << "\n3) City: " << (*trip)->GetCity();
	std::cout << "\n4) Date of start: " << (*trip)->GetDateOfStart();
	std::cout << "\n5) Date of end: " << (*trip)->GetDateOfEnd();
	std::cout << "\n6) Price: " << (*trip)->GetPrice() << " grn.";
}


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
	case 6:
		(*trip)->SetPrice(std::stod(value));
		break;
	default:
		break;
	}
}
void EditTrip(trip_list_iter_t& trip, const int fieldIndex, std::chrono::year_month_day date) {
	if ((*trip)->GetStatus() == TripStatus::IN_PROGRESS || (*trip)->GetStatus() == TripStatus::FINISHED || (*trip)->GetStatus() == TripStatus::EXPIRED)
		return;

	switch (fieldIndex){
	case 4:
		(*trip)->SetDateOfStart(date);
		break;
	case 5:
		(*trip)->SetDateOfEnd(date);
		break;
	default:
		break;
	}
}

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


// count of bought trips + thier indexes
std::pair<size_t, std::vector<int>> GetCountOfPurchasedTrips(const ListSharedsTrip_t& Trips, unsigned short year){
	std::vector<int> Indices;
	int count = 0;
	int index = 0;
    if (year == 0){
        for (auto& trip : Trips) {
            if (trip->GetStatus() == TripStatus::SOLD) {
                count++;
                Indices.emplace_back(index);
            }
            index++;
        }
    }
    else{
        for (auto& trip : Trips) {
            if (trip->GetStatus() == TripStatus::SOLD && static_cast<int>(trip->GetDateOfBooking().year()) == year) {
                count++;
                Indices.emplace_back(index);
            }
            index++;
        }
    }
	return std::make_pair(count, Indices);
}


std::vector<std::string> GetCountriesOfBoughtTrips(const ListSharedsTrip_t& Trips, const int year, std::string path){
	std::list<std::string> Countries; // Íàá³ð êðà¿í óc³õ ïðèäáàíèõ ä³écíèõ ïóò³âîê 
	if (year != 0) {
        int year_of_booking;
		for (auto& trip : Trips) {
			if ((trip->GetStatus() == TripStatus::SOLD || trip->GetStatus() == TripStatus::IN_PROGRESS)) {
				year_of_booking = static_cast<int>(trip->GetDateOfBooking().year());
				if (year_of_booking == year)
					Countries.push_back(trip->GetCountry());
			}
		}
	}
	else { // if year == 0 
		for (auto& trip : Trips) {
			if (trip->GetStatus() == TripStatus::SOLD || trip->GetStatus() == TripStatus::IN_PROGRESS)
				Countries.push_back(trip->GetCountry());
		}
	}

	Countries.sort();

	std::vector<std::string> uniqueCountries;
	std::unique_copy(std::begin(Countries), std::end(Countries), std::back_inserter(uniqueCountries));
	return uniqueCountries;
}


double GetAverageDurationOfTrips(const ListSharedsTrip_t& Trips, const int year, std::string path){
	std::stack<Order> Orders; 
	ReadOrdersData(Orders, path);

	std::vector<int> Durations;
	Durations.reserve(Orders.size());

	if (year != 0) {
		int date_of_booking;
		for (auto& trip : Trips) {
			if ((trip->GetStatus() == TripStatus::SOLD || trip->GetStatus() == TripStatus::IN_PROGRESS)) {
				date_of_booking = static_cast<int>(trip->GetDateOfBooking().year());
				if (date_of_booking == year)
					Durations.push_back(trip->GetDuration());
			}
		}
		while (!Orders.empty()) {
			if (Orders.top().year_of_booking == year)
				Durations.push_back(Orders.top().duration);
			Orders.pop();
		}
	}

	else { 
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


int GetAveragePriceOfTrips(const ListSharedsTrip_t& Trips, const int year, std::string path){
	std::stack<Order> Orders; 
	ReadOrdersData(Orders, path);

	std::vector<double> Prices;
	Prices.reserve(Orders.size());

	if (year != 0) {
        int date_of_booking;
		for (auto& trip : Trips) {
			if ((trip->GetStatus() == TripStatus::SOLD || trip->GetStatus() == TripStatus::IN_PROGRESS)) {
				date_of_booking = static_cast<int>(trip->GetDateOfBooking().year());
				if (date_of_booking == year)
					Prices.push_back(trip->GetDuration());
			}
		}
		while (!Orders.empty()) {
			if (Orders.top().year_of_booking == year)
				Prices.push_back(Orders.top().price);
			Orders.pop();
		}
	}

	else { 
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

std::shared_ptr<Trip> FindTripById(const ListSharedsTrip_t& Trips, const int personal_id){
	for (auto trip : Trips) {
		if (trip->GetPersonalId() == personal_id)
			return trip;
	}
	return nullptr;
}


Countries_Count_Year_AllCountYear FindMostPupularCountries(const ListSharedsTrip_t& Trips, const int year, std::string path) {
	std::stack<Order> Orders;  
	ReadOrdersData(Orders, path);

	std::list<std::string> Countries; 

	if (year != 0) {
		int year_of_booking;
		for (auto& trip : Trips) {
			if ((trip->GetStatus() == TripStatus::SOLD || trip->GetStatus() == TripStatus::IN_PROGRESS)) {
				year_of_booking = static_cast<int>(trip->GetDateOfBooking().year());
				if (year_of_booking == year)
					Countries.push_back(trip->GetCountry());
			}
		}
		while (!Orders.empty()) {
			if (Orders.top().year_of_booking == year)
				Countries.push_back(Orders.top().country);
			Orders.pop();
		}
	}

	else { 
		for (auto& trip : Trips) {
			if (trip->GetStatus() == TripStatus::SOLD || trip->GetStatus() == TripStatus::IN_PROGRESS)
				Countries.push_back(trip->GetCountry());
		}
		while (!Orders.empty()) {
			Countries.push_back(Orders.top().country);
			Orders.pop();
		}
	}

	Countries.sort();

	std::vector<std::string> uniqueCountries;
	std::unique_copy(std::begin(Countries), std::end(Countries), std::back_inserter(uniqueCountries));

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

	std::vector<std::string> mostPopularCountries; 
	curentIndex = 0;

	while (curentIndex < static_cast<int>(uniqueCountries.size())) {

		countOfRepits = std::count(std::begin(Countries), std::end(Countries), uniqueCountries[curentIndex]);

		if (countOfRepits == maxRepits) 
			mostPopularCountries.push_back(uniqueCountries[curentIndex]);
		
		curentIndex++;
	}
	return std::make_pair(std::make_pair(mostPopularCountries, maxRepits), std::make_pair(year, Countries.size()));
}


void ShowMostPupularCountries(const Countries_Count_Year_AllCountYear& pair) {
	/*
	* pair.first.first   - names of most popular countries 
	* pair.first.second  - count of bought trips to those countries
	* pair.second.first  - year
	* pair.second.second - count of all countries
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
		TripObjectsWrite << "\n"; 

		int count = 0;

		for (const auto& trip : Trips) {
			// ßêùî äàòà ïî÷àòêó ïóò³âêè á³ëüøå í³æ cüîãîäí³
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
					TripObjectsWrite << "On sale" << "\n";

				else if (trip->GetStatus() == TripStatus::SOLD) {
					TripObjectsWrite << "Sold" << "\n";
					TripObjectsWrite << trip->GetDateOfBooking() << "\n";
					TripObjectsWrite << trip->GetNameOfCustomer() << "\n";
					TripObjectsWrite << trip->GetNameOfManager() << "\n";
				}

				else if (trip->GetStatus() == TripStatus::IN_PROGRESS) {
					TripObjectsWrite << "In progress" << "\n";
					TripObjectsWrite << trip->GetDateOfBooking() << "\n";
					TripObjectsWrite << trip->GetNameOfCustomer() << "\n";
					TripObjectsWrite << trip->GetNameOfManager() << "\n";
				}

				count++;
				if (count != Trips.size())
					TripObjectsWrite << "----------------------------------------------\n";
			}

			else if (trip->GetStatus() == TripStatus::FINISHED)
				SaveOrderData(static_cast<int>(trip->GetDateOfBooking().year()), trip->GetCountry(), trip->GetFullName(), trip->GetNameOfCustomer(), trip->GetDuration(), trip->GetPrice());

		}
	}
	TripObjectsWrite.close();
}


void ReadTripsData(std::list<std::shared_ptr<Trip>>& Trips, const std::string path) {
	std::ifstream TripObjectsRead;
	TripObjectsRead.open(path, std::ios::in);

	if (!TripObjectsRead.is_open())
		std::cout << "Error: Could not open the file at the specified path to read customers data. \nSpecified path: " << path << "\n";
	else {
		std::string name, country, city, date_of_start_str, date_of_end_str, price, personal_id, status, name_of_customer, name_of_manager, date_of_booking_str, emptiness;
        std::chrono::year_month_day date_of_start, date_of_end, date_of_booking;

		std::getline(TripObjectsRead, emptiness); 
		if (emptiness == "Empty") {
			TripObjectsRead.close();
			return;
		}
		std::getline(TripObjectsRead, emptiness); 
        //
        std::chrono::time_point now{std::chrono::system_clock::now()};
        std::chrono::year_month_day today{std::chrono::floor<std::chrono::days>(now)};

		while (!TripObjectsRead.eof()) {
			std::getline(TripObjectsRead, name);
			std::getline(TripObjectsRead, country);
			std::getline(TripObjectsRead, city);
			std::getline(TripObjectsRead, date_of_start_str);
			std::getline(TripObjectsRead, date_of_end_str);
            std::getline(TripObjectsRead, price); 
            std::getline(TripObjectsRead, personal_id); 
            std::getline(TripObjectsRead, status);
            if (status == "Sold" || status == "In progress") {
                std::getline(TripObjectsRead, date_of_booking_str);
                std::getline(TripObjectsRead, name_of_customer);
                std::getline(TripObjectsRead, name_of_manager);
            }	
            if (!TripObjectsRead.eof()) {
                std::getline(TripObjectsRead, emptiness);
                std::getline(TripObjectsRead, emptiness);
            }

            try{
                date_of_start = stringToYearMonthDay(date_of_start_str);
                date_of_end = stringToYearMonthDay(date_of_end_str);
                if (status == "Sold" || status == "In progress") 
                    date_of_booking = stringToYearMonthDay(date_of_booking_str);

            }
            catch(std::exception& ex){
                std::cout << "Exception while reading date of start/end/booking of the trip \"" << name << "\" (id: " << personal_id <<"): "<< ex.what();
                continue;
            }
            
			if (status == "On sale")  // TripStatus::ON_SALE or EXPIRED
			{
				if (getDateDifference(today, date_of_start) > 0) //TripStatus::SELLING - çáåð³ãàºìî
					Trips.emplace_back(std::make_shared<Trip>(name, country, city, date_of_start, date_of_end, std::stod(price), std::stoi(personal_id)));
			}
			else if (status == "Sold" || status == "In progress")  // TripStatus::SOLD or IN_PROGRESS or FINISHED
			{
				if (getDateDifference(today, date_of_end) < 0) 
					SaveOrderData(static_cast<int>(date_of_booking.year()), country, name, name_of_customer, Trips.back()->GetDuration(), std::stod(price));
				else
					Trips.emplace_back(std::make_shared<Trip>(name, country, city, date_of_start, date_of_end, std::stod(price), std::stoi(personal_id), name_of_customer, name_of_manager, date_of_booking));
			}
		}
	}
	TripObjectsRead.close();
}

