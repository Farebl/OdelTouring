module;

#include <cstring>
#include <iostream>
#include <chrono>
#include <vector> 


export module CustomerManagerTrip:Trip;


export struct bad_date : public std::exception{
private:
    char buffer[128]{};

public:
    bad_date(const char* msg, std::chrono::year_month_day wrong_date) noexcept {
        std::snprintf(buffer, sizeof(buffer), "%s: %d/%02u/%02u", 
            msg ? msg : "Bad date", 
            static_cast<int>(wrong_date.year()),
            static_cast<unsigned int>(wrong_date.month()),
            static_cast<unsigned int>(wrong_date.day())
        );
    }

    const char* what() const noexcept override {
        return buffer; 
    }
};



export enum class TripStatus {
    ON_SALE,
	SOLD, 
    IN_PROGRESS, 
	FINISHED, 
	EXPIRED 
};

export class Trip {
	friend class Manager;

private:
	std::string name; 
	std::string country; 
	std::string city; 

    std::chrono::year_month_day date_of_start; 
    std::chrono::year_month_day date_of_end; 
	
	double price; 
	int personal_id; 

	std::string name_of_customer;
	std::string name_of_manager; 
    std::chrono::year_month_day date_of_booking; 

	static int total_duration; 
	static double total_price; 
	static std::vector<int> Identifiers; 

	void SetDataOfPurchase(std::string name_of_manager, std::string name_of_customer);

	void Return(); 

	int GetDateDifference(const std::string firstDate, const std::string secondDate = "today");

public:
	Trip(std::string name = "-", std::string country = "-", std::string city = "-", std::chrono::year_month_day date_of_start = std::chrono::year_month_day{}, std::chrono::year_month_day date_of_end = std::chrono::year_month_day{}, double price = 0, int personal_id = 0, std::string name_of_customer = "-", std::string name_of_manager = "-", std::chrono::year_month_day date_of_booking = std::chrono::year_month_day{});

	Trip(const Trip& trip); 

	~Trip(); 

	void ShowInfo(); 

	std::string GetFullName(); 
	void SetFullName(std::string name); 

	std::string GetCountry(); 
	void SetCountry(std::string country); 
	 
	std::string GetCity(); 
    void SetCity(std::string city); 

    std::chrono::year_month_day GetDateOfStart(); 
	void SetDateOfStart(std::chrono::year_month_day date_of_start); 

    std::chrono::year_month_day GetDateOfEnd(); 
	void SetDateOfEnd(std::chrono::year_month_day date_of_end); 

	long GetDuration(); 

	double GetPrice(); 
    void SetPrice(double price); 

	int GetPersonalId(); 

	TripStatus GetStatus();

    std::chrono::year_month_day GetDateOfBooking(); // date when this trip was bought
	std::string GetNameOfCustomer(); // customer, who bought this trip
	std::string GetNameOfManager(); // manager who sold this trip
	
	static double GetAveragePrice(); 
	static double GetAverageDuration();
};






// ------------------- Interface --------------------------
//
//////////////////////////////////////////////////////////////////////////////
//
// ------------------- Implementation --------------------------






std::vector<int> Trip::Identifiers;
double Trip::total_price = 0;
int Trip::total_duration = 0;



long getDateDifference(std::chrono::year_month_day startDate, std::chrono::year_month_day endDate){
    std::chrono::sys_days start{startDate};
    std::chrono::sys_days end{endDate};
    std::chrono::days result = end - start;
    return result.count();
}


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



Trip::Trip(std::string name, std::string country, std::string city, std::chrono::year_month_day date_of_start, std::chrono::year_month_day date_of_end, double price, int personal_id, std::string name_of_customer, std::string name_of_manager, std::chrono::year_month_day date_of_booking)
{
	this->name = name;
	this->country = country;
	this->city = city;
	this->price = price;
	total_price += this->price;

	this->name_of_customer = name_of_customer;
	this->name_of_manager = name_of_manager;
	this->date_of_booking = date_of_booking;


    if (date_of_start.ok()){
        SetDateOfStart(date_of_start);
    }
    else {
        throw bad_date("Invalid date of start: ", date_of_start);
    }
    if (date_of_end.ok()){
        if (int duration = getDateDifference(date_of_start, date_of_end); 
            duration > 1 && duration < 61 ){
            SetDateOfEnd(date_of_end);
        }
        else{
            throw bad_date("Tour duration must be within [1; 60]. Your date of end: ", date_of_end);        
        }
	}
    else{
        throw bad_date("Invalid date of end: ", date_of_end);
    }

	total_duration += getDateDifference(this->date_of_start, this->date_of_end);

	if (!(personal_id == 0)) {
		this->personal_id = personal_id;
		Identifiers.push_back(this->personal_id);
	}
	else {
		srand(static_cast<unsigned>(time(nullptr))); 
		while (true) {
			this->personal_id = rand() % 9'999'999 + 1'000'000;
        
			bool availability = false;
			for (size_t i = 0; i < Identifiers.size(); ++i) {
				if (this->personal_id == Identifiers[i]) {
					availability = true;
					break;
				}
			}

			if (availability) {
				continue;
			}
			else {
				Identifiers.push_back(this->personal_id);
				break;
			}
		}
	}
}


Trip::Trip(const Trip& trip)
{
	this->name = trip.name;
	this->country = trip.country;
	this->city = trip.city;
	this->date_of_start = trip.date_of_start;
	this->date_of_end = trip.date_of_end;
	this->price = trip.price;

	this->date_of_booking = std::chrono::year_month_day{};
	this->name_of_customer = "-";
	this->name_of_manager = "-";

	srand(static_cast<unsigned>(time(nullptr))); 
	while (true) {
		personal_id = rand() % 9'999'999 + 1'000'000; 

		bool availability = false;
		for (size_t i = 0; i < Identifiers.size(); ++i) {
			if (personal_id == Identifiers[i]) {
				availability = true;
				break;
			}
		}

		if (availability) 
			continue;
		else {
			Identifiers.push_back(personal_id);
			break;
		}
	}

	total_price += price;
	total_duration += getDateDifference(this->date_of_start, this->date_of_end);
}

Trip::~Trip()
{
	auto currentId = Identifiers.begin();
	for (auto& id : Identifiers) {
		if (this->personal_id == id) {
			Identifiers.erase(currentId);
		}
		else {
			++currentId;
		}
	}
}


void Trip::ShowInfo()
{
	std::cout << "\n\n1) Name: " << name;
	std::cout << "\n2) Country: " << country;
	std::cout << "\n3) City: " << city;
	std::cout << "\n4) Date of start: " << date_of_start;
	std::cout << "\n5) Date of end: " << date_of_end;
	std::cout << "\n6) Duration: " << getDateDifference(date_of_start, date_of_end);
	std::cout << "\n7) Price: " << price << " grn.";
	std::cout << "\n8) Id: " << personal_id;
	if (GetStatus() == TripStatus::SOLD) {
		std::cout << "\n9) Customer who bought this tour: " << name_of_customer;
		std::cout << "\n10) Manager who sold this tour: " << name_of_manager << "\n";
	}
	else
		std::cout << "\n9) Trip not bought\n";
}


std::string Trip::GetFullName()
{
	return this->name;
}

void Trip::SetFullName(std::string name)
{
	this->name = name;
}


std::string Trip::GetCountry()
{
	return this->country;
}

void Trip::SetCountry(std::string country)
{
	this->country = country;
}


std::string Trip::GetCity()
{
	return this->city;
}

void Trip::SetCity(std::string city)
{
	this->city = city;
}


std::chrono::year_month_day Trip::GetDateOfBooking()
{
	return this->date_of_booking;
}


std::chrono::year_month_day Trip::GetDateOfStart() {
	return this->date_of_start;
}


void Trip::SetDateOfStart(std::chrono::year_month_day date_of_start) {
    this->date_of_start = date_of_start;
}


std::chrono::year_month_day Trip::GetDateOfEnd() {
	return this->date_of_end;
}

void Trip::SetDateOfEnd(std::chrono::year_month_day date_of_end) {
    this->date_of_end = date_of_end;
}


long Trip::GetDuration() {
	return getDateDifference(this->date_of_start, this->date_of_end);
}


double Trip::GetPrice() {return this->price;}

void Trip::SetPrice(double price) {
	while (true) {
		if (price <= 0) {
			std::cout << "\nThe product price cannot be less than 0. Enter a new price: ";
			std::cin >> price;
			std::cin.ignore(std::numeric_limits<long>::max(), '\n');
			continue;
		}
		else 
			break;
	}
	this->price = price;
}


int Trip::GetPersonalId(){
	return this->personal_id;
}


TripStatus Trip::GetStatus()
{    
    std::chrono::time_point now{std::chrono::system_clock::now()};
    std::chrono::year_month_day today{std::chrono::floor<std::chrono::days>(now)};

    auto from_today_to_start = getDateDifference(today, this->date_of_start);

	if (this->date_of_booking.ok()) {
    
        auto from_today_to_end = getDateDifference(today, this->date_of_end);
		
        if (from_today_to_start > 0){
			return TripStatus::SOLD;
        } 
        else if ((from_today_to_start <= 0) && (from_today_to_end >= 0)){
			return TripStatus::IN_PROGRESS;
        } 
        else{ 
			return TripStatus::FINISHED;
	    }
    }
	else
	{
		if (from_today_to_start > 0){
			return TripStatus::ON_SALE;
        }
        else{ 
			return TripStatus::EXPIRED;
	    }
    }
}


std::string Trip::GetNameOfCustomer(){
	return this->name_of_customer;
}

std::string Trip::GetNameOfManager(){
	return this->name_of_manager;
}

void Trip::SetDataOfPurchase(std::string name_of_manager, std::string name_of_customer)
{
	this->name_of_manager = name_of_manager;
	this->name_of_customer = name_of_customer;

	std::chrono::time_point now{std::chrono::system_clock::now()};
    this->date_of_booking = std::chrono::year_month_day{std::chrono::floor<std::chrono::days>(now)};
}



double Trip::GetAveragePrice() {
	return total_price / static_cast<double>(Identifiers.size());
}


double Trip::GetAverageDuration() {
	return static_cast<double>(total_duration) / static_cast<double>(Identifiers.size());
}



void Trip::Return(){
	date_of_booking = std::chrono::year_month_day{};
	name_of_customer = "-";
	name_of_manager = "-";
}



// Ðàõóº ð³çíèöþ ì³æ äâîìà äàòàìè ôîðìàòó "dd/mm/yyyy"

int Trip::GetDateDifference(const std::string firstDate, const std::string secondDate)
{

	std::time_t mytime = std::time(NULL);
	std::tm now;
	gmtime_r(&mytime, &now);


	int day_1, month_1, year_1, day_2, month_2, year_2;

	std::tm time_1 = {}; 
	std::tm time_2 = {}; 
	std::time_t tt;


	if (secondDate == "today") {

		std::time_t mytime = std::time(NULL);
		std::tm now;
		gmtime_r(&mytime, &now);
		

		day_1 = now.tm_mday;
		month_1 = now.tm_mon + 1;
		year_1 = now.tm_year + 1900;

		time_1.tm_year = year_1 - 1900; 
		time_1.tm_mon = month_1 - 1;  
		time_1.tm_mday = day_1;


		day_2 = std::stoi(firstDate.substr(0, 2));
		month_2 = std::stoi(firstDate.substr(3, 2));
		year_2 = std::stoi(firstDate.substr(6, 4));

		time_2.tm_year = year_2 - 1900; 
		time_2.tm_mon = month_2 - 1; 
		time_2.tm_mday = day_2;


		tt = std::mktime(&time_1);
		int days_1 = static_cast<int>(tt / (60 * 60 * 24)); 

		tt = std::mktime(&time_2);
		int days_2 = static_cast<int>(tt / (60 * 60 * 24)); 

		return days_2 - days_1;

	}

	else 	
	{
		day_1 = std::stoi(firstDate.substr(0, 2));
		month_1 = std::stoi(firstDate.substr(3, 2));
		year_1 = std::stoi(firstDate.substr(6, 4));

		day_2 = std::stoi(secondDate.substr(0, 2));
		month_2 = std::stoi(secondDate.substr(3, 2));
		year_2 = std::stoi(secondDate.substr(6, 4));

		time_1.tm_year = year_1 - 1900; 
		time_1.tm_mon = month_1 - 1; 
		time_1.tm_mday = day_1;

		time_2.tm_year = year_2 - 1900;
		time_2.tm_mon = month_2 - 1;
		time_2.tm_mday = day_2;

		tt = std::mktime(&time_1);
		int days_1 = static_cast<int>(tt / (60 * 60 * 24));

		tt = std::mktime(&time_2);
		int days_2 = static_cast<int>(tt / (60 * 60 * 24));

		return days_2 - days_1;
	}

}
