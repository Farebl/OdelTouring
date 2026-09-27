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
#include <set>
#include <nlohmann/json.hpp>


module Functions; 


////////////////////////////////  HELPER FUNCTIONS ///////////////////////////////



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


void to_json(nlohmann::ordered_json& json, const Order& order) {
    json = nlohmann::ordered_json{
        {"name_of_trip",    order.name_of_trip},
        {"year_of_booking", order.year_of_booking},
        {"country",         order.country},
        {"duration",        order.duration},
        {"price",           order.price},
        {"customer_id",     order.customer_id}
    };
}

std::shared_ptr<Order> getOrderFromJson(const nlohmann::ordered_json& json) {
    std::shared_ptr<Order> order = std::make_shared<Order>(
        json.at("name_of_trip").get<std::string>(),
        json.at("year_of_booking").get<int>(),
        json.at("country").get<std::string>(),
        json.at("duration").get<int>(),
        json.at("price").get<double>(),
        json.at("customer_id").get<long>()
    );
    return order;
}


void to_json(nlohmann::ordered_json& json, const Manager& manager) {
    json = nlohmann::ordered_json{
        {"name",         manager.GetFullName()},
        {"phone_number", manager.GetPhoneNumber()},
        {"personal_id",  manager.GetPersonalId()}
    };
}

std::shared_ptr<Manager> getManagerFromJson(const nlohmann::ordered_json& json) {
    std::shared_ptr<Manager> manager = std::make_shared<Manager>(
        json.at("name").get<std::string>(),
        json.at("phone_number").get<std::string>(),
        json.at("personal_id").get<int>()
    );
    return manager;
}


NLOHMANN_JSON_SERIALIZE_ENUM( CustomerStatus, {
    {CustomerStatus::WITHOUT_TRIP, "WITHOUT_TRIP"},
    {CustomerStatus::WITH_TRIP, "WITH_TRIP"},
    {CustomerStatus::DURING_A_TRIP, "DURING_A_TRIP"},
})

void to_json(nlohmann::ordered_json& json, const Customer& customer) {
    auto customer_status = customer.GetStatus();
    json = nlohmann::ordered_json{
        {"name",                  customer.GetFullName()},
        {"phone_number",          customer.GetPhoneNumber()},
        {"address",               customer.GetAddress()},
        {"count_of_bought_trips", customer.GetCountOfBoughtTrips()},
        {"personal_id",           customer.GetPersonalId()},
        {"status",                customer_status},
    };
    if (customer_status != CustomerStatus::WITHOUT_TRIP){
        json["trip_name"]    = customer.GetTrip()->GetFullName();
        json["trip_id"]      = customer.GetTrip()->GetPersonalId();
        json["manager_name"] = customer.GetTrip()->GetFullName();
    }
}


std::shared_ptr<Customer> getCustomerFromJson(const nlohmann::ordered_json& json, const ListSharedsTrip_t& trips) {
    std::shared_ptr<Customer> customer = nullptr;
    
    auto customer_status = json.at("status").get<CustomerStatus>();
    if (customer_status == CustomerStatus::WITHOUT_TRIP){
        customer = std::make_shared<Customer>(
            json.at("name").get<std::string>(),
            json.at("phone_number").get<std::string>(),
            json.at("address").get<std::string>(),
            json.at("count_of_bought_trips").get<int>(),
            json.at("personal_id").get<int>()
        );
    }
    else{
        auto bought_trip = FindTripById(trips, json.at("trip_id").get<int>());
        customer = std::make_shared<Customer>(
            json.at("name").get<std::string>(),
            json.at("phone_number").get<std::string>(),
            json.at("address").get<std::string>(),
            json.at("count_of_bought_trips").get<int>(),
            json.at("personal_id").get<int>(),
            bought_trip
        );
    }
    return customer;
}


/////////////////////////MAIN FUNCTIONS///////////////////////////



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




void SaveManagersData(const ListSharedsManager_t& managers, const std::string path) {
    nlohmann::ordered_json j = nlohmann::ordered_json::array();

    for (const auto& manager : managers) {
        j.push_back(*manager);    
    }

    std::ofstream managers_write(path);
    if (!managers_write.is_open()) {
        std::cout << "Error: Could not open the file at the specified path to record managers data. \nSpecified path:" << path << "\n";
        return;
    }

    managers_write << j.dump(4);
    managers_write.close();
}




void ReadManagersData(ListSharedsManager_t& managers, const std::string path) {
    std::ifstream managers_reader(path);

    if (!managers_reader.is_open()) {
        std::cout << "Error: Could not open the file at the specified path to read managers data.\nSpecified path:" << path << "\n";
        return;
    }

    nlohmann::ordered_json j;
    try {
        managers_reader >> j;
    } catch (const nlohmann::ordered_json::parse_error& e) {
        std::cout << "Error: Failed to parse managers JSON file.\n" << e.what() << "\n";
        managers_reader.close();
        return;
    }

    for (const auto& item : j) {
        managers.push_back(getManagerFromJson(item));
    }

    managers_reader.close();
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


void SaveCustomersData(const ListSharedsCustomer_t& customers, const std::string path) {
    nlohmann::ordered_json j = nlohmann::ordered_json::array();

    for (const auto& customer : customers) {
        j.push_back(*customer);    
    }

    std::ofstream customers_write(path);
    if (!customers_write.is_open()) {
        std::cout << "Error: Could not open the file at the specified path to record customers data. \nSpecified path:" << path << "\n";
        return;
    }

    customers_write << j.dump(4);
    customers_write.close();
}


void ReadCustomersData(ListSharedsCustomer_t& customers, const ListSharedsTrip_t& trips, const std::string path) {
    std::ifstream customers_reader(path);

    if (!customers_reader.is_open()) {
        std::cout << "Error: Could not open the file at the specified path to read customers data.\nSpecified path:" << path << "\n";
        return;
    }

    nlohmann::ordered_json j;
    try {
        customers_reader >> j;
    } catch (const nlohmann::ordered_json::parse_error& e) {
        std::cout << "Error: Failed to parse customers JSON file.\n" << e.what() << "\n";
        customers_reader.close();
        return;
    }

    for (const auto& item : j) {
        customers.push_back(getCustomerFromJson(item, trips));
    }

    customers_reader.close();
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

std::shared_ptr<Trip> FindTripById(const ListSharedsTrip_t& Trips, const int personal_id){
	for (auto trip : Trips) {
		if (trip->GetPersonalId() == personal_id)
			return trip;
	}
	return nullptr;
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
  

			if (getDateDifference(today, date_of_start) > 0){
                if (status == "On sale")
                    Trips.emplace_back(std::make_shared<Trip>(name, country, city, date_of_start, date_of_end, std::stod(price), std::stoi(personal_id)));
                else if (status == "Sold")
					Trips.emplace_back(std::make_shared<Trip>(name, country, city, date_of_start, date_of_end, std::stod(price), std::stoi(personal_id), name_of_customer, name_of_manager, date_of_booking));

			}
		}
	}
	TripObjectsRead.close();
}










///////////////////////////////////////////////////////////////////////////////////


// 4 Orders funcuions:

int GetCountOfOrdersByYear(const ListSharedsOrder_t& orders, const int year){
	int count = 0;
	if (year != 0) {
        for (const auto& order : orders){
			if (order->year_of_booking == year)
				++count;
		}
		return count;
	}
	else 
		return orders.size();
}



std::vector<std::string> GetCountriesOfBoughtTrips(const ListSharedsTrip_t& trips){
	std::set<std::string> countries; 

    for (const auto& trip : trips) {
        auto trip_status = trip->GetStatus();
        if (trip_status == TripStatus::SOLD || trip_status == TripStatus::IN_PROGRESS)
            countries.insert(trip->GetCountry());
    }
    
	std::vector<std::string> unique_countries{countries.begin(), countries.end()};
	return unique_countries;
}


double GetAverageDurationOfSoldTripsByYear(const ListSharedsOrder_t& orders, const int year){
	std::vector<int> durations;
	durations.reserve(orders.size());

	if (year != 0) {
		for (const auto& order : orders) {
			if (order->year_of_booking == year){
				durations.push_back(order->duration);
			}
		}
	}

	else { 
		for (const auto& order : orders) {
            durations.push_back(order->duration);
		}
	}

	if (durations.size() == 0)
		return 0;

	return (std::accumulate(durations.begin(), durations.end(), 0) / durations.size());
}


int GetAveragePriceOfSoldTripsByYear(const ListSharedsOrder_t& orders, const int year){
	std::vector<double> prices;
	prices.reserve(orders.size());

	if (year != 0) {
		for (const auto& order : orders) {
			if (order->year_of_booking == year){
				prices.push_back(order->price);
			}
		}
	}

	else { 
		for (const auto& order : orders) {
            prices.push_back(order->price);
		}
	}

	if (prices.size() == 0)
		return 0;

	return (std::accumulate(prices.begin(), prices.end(), 0) / prices.size());
}






Countries_Count_Year_AllCountYear FindMostPupularCountriesOfSoldTrips(const ListSharedsOrder_t& orders, const int year) {
	std::list<std::string> countries; 

	if (year != 0) {
		for (const auto& order : orders) {
            if (order->year_of_booking == year){
                countries.push_back(order->country);
			}
		}
	}
	else { 
		for (const auto& order : orders) {
            countries.push_back(order->country);
		}
	}

	countries.sort();

	std::vector<std::string> unique_countries;
	std::unique_copy(std::begin(countries), std::end(countries), std::back_inserter(unique_countries));

	int curent_index = 0;
	int max_repits = 0;
	int current_count_of_repits = 0;

	while (curent_index < static_cast<int>(unique_countries.size())) {
		current_count_of_repits = std::count(std::begin(countries), std::end(countries), unique_countries[curent_index]);
		if (current_count_of_repits > max_repits) {
			max_repits = current_count_of_repits;
		}
		curent_index++;
	}

	std::vector<std::string> mostPopularcountries; 
	curent_index = 0;

	while (curent_index < static_cast<int>(unique_countries.size())) {

		current_count_of_repits = std::count(std::begin(countries), std::end(countries), unique_countries[curent_index]);

		if (current_count_of_repits == max_repits) 
			mostPopularcountries.push_back(unique_countries[curent_index]);
		
		curent_index++;
	}
	return std::make_pair(std::make_pair(mostPopularcountries, max_repits), std::make_pair(year, countries.size()));
}


void ShowMostPupularCountriesOfSoldTrips(const Countries_Count_Year_AllCountYear& pair) {
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
		std::cout << "\n\nUnfortunately, in " << year << ", not a single order made.\n";
		return;
	}

	else if (pair.first.first.empty() && year == 0) {
		std::cout << "\n\nUnfortunately, not a single order has been made for all the time.\n";
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




void RemoveOrderByCustomerId(ListSharedsOrder_t& orders, size_t customer_id){
    auto border = std::remove_if(orders.begin(), orders.end(), [customer_id](const auto& order){return order->customer_id == customer_id;});
    orders.erase(border, orders.end());
}




void SaveOrdersData(const ListSharedsOrder_t& orders, const std::string& path) {
    nlohmann::ordered_json j = nlohmann::ordered_json::array();

    for (const auto& order : orders) {
        j.push_back(*order); // розіменовуємо shared_ptr, викликається to_json(Order)
    }

    std::ofstream orders_writer(path);
    if (!orders_writer.is_open()) {
        std::cout << "Error: Could not open the file at the specified path to record orders data. \nSpecified path:" << path << "\n";
        return;
    }

    orders_writer << j.dump(4);
    orders_writer.close();
}

void ReadOrdersData(ListSharedsOrder_t& orders, const std::string path) {
    std::ifstream orders_reader(path);

    if (!orders_reader.is_open()) {
        std::cout << "Error: Could not open the file at the specified path to read orders data.\nSpecified path:" << path << "\n";
        return;
    }

    nlohmann::ordered_json j;
    try {
        orders_reader >> j;
    } catch (const nlohmann::ordered_json::parse_error& e) {
        std::cout << "Error: Failed to parse orders JSON file.\n" << e.what() << "\n";
        orders_reader.close();
        return;
    }

    for (const auto& item : j) {
        orders.push_back(getOrderFromJson(item));
    }

    orders_reader.close();
}
