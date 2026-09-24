module;

#include <cstring>
#include <iostream>
#include <chrono>
#include <vector> 


module CustomerManagerTrip;

std::vector<int> Trip::Identifiers;
double Trip::total_price = 0;
long long Trip::total_duration = 0;



size_t getDateDifference(std::chrono::year_month_day startDate, std::chrono::year_month_day endDate){
    std::chrono::sys_days start{startDate};
    std::chrono::sys_days end{endDate};
    std::chrono::days result = end - start;
    return result.count();
}

void Trip::setId(size_t id){
	if (!(id == 0)) {
		this->personal_id = id;
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

Trip::Trip()
    : name("-")
    , country("-")
    , city("-")
    , price(0.0)
    , date_of_start(std::chrono::year_month_day{})
    , date_of_end(std::chrono::year_month_day{})
    , date_of_booking(std::chrono::year_month_day{})
    , name_of_customer("-")
    , name_of_manager("-") 
{
    setId();
}


Trip::Trip(std::string name, std::string country, std::string city, std::chrono::year_month_day date_of_start, std::chrono::year_month_day date_of_end, double price, int personal_id)
    : name(name)
    , country(country)
    , city(city)
    , price(0.0)
    , name_of_customer("-")
    , name_of_manager("-")
    , date_of_booking(std::chrono::year_month_day{})
{
    setId(personal_id);

    if(price < 0){
        throw std::runtime_error("Invalid price");
    }
    SetPrice(price);

    if (date_of_start.ok()){
        SetDateOfStart(date_of_start);
    }
    else {
        throw std::runtime_error("Invalid date of start");
    }
    
    if (date_of_end.ok()){
        if (int duration = getDateDifference(date_of_start, date_of_end); 
            duration > 1 && duration < MAX_TRIP_DURATION){
            SetDateOfEnd(date_of_end);
        }
        else{
            throw std::runtime_error("Tour duration must be within [1; 60]. Your date of end");        
        }
    }
    else{
        throw std::runtime_error("Invalid date of end");
    }
}


Trip::Trip(std::string name, std::string country, std::string city, std::chrono::year_month_day date_of_start, std::chrono::year_month_day date_of_end, double price, int personal_id, std::string name_of_customer, std::string name_of_manager, std::chrono::year_month_day date_of_booking)
    : Trip(name, country, city, date_of_start, date_of_end, price, personal_id)
{
    this->name_of_customer = name_of_customer;
	this->name_of_manager = name_of_manager;
    if (date_of_booking.ok()){
        auto diff_booking_and_start = getDateDifference(date_of_booking, date_of_start);
	    if (diff_booking_and_start < 1){
            throw std::runtime_error("The trip cannot be purchased on the start date or after");
        }
        this->date_of_booking = date_of_booking;
    }
    else{
        throw std::runtime_error("Invalid date of booking");
    }
}





Trip::Trip(const Trip& trip)
    : name(trip.name)
	, country(trip.country)
    , city(trip.city)
    , date_of_start(std::chrono::year_month_day{}) // special logic in set method
    , date_of_end(std::chrono::year_month_day{})   // special logic in set method
    , price(0)                                     // special logic in set method
    , date_of_booking(std::chrono::year_month_day{})
    , name_of_customer("-")
    , name_of_manager("-")
{
    setId();
    SetDateOfStart(trip.date_of_start);
    SetDateOfEnd(trip.date_of_end);
    SetPrice(trip.price);
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
    total_price -= price;
	total_duration -= getDateDifference(this->date_of_start, this->date_of_end);
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




std::chrono::year_month_day Trip::GetDateOfStart() {
	return this->date_of_start;
}


std::optional<const char*> Trip::SetDateOfStart(std::chrono::year_month_day date_of_start) {
    if (date_of_end.ok()) {
        if (date_of_start >= this->date_of_end){
            return "Date of start cannot be greater or equal then date of end";
        }
        
        else if (getDateDifference(date_of_start, this->date_of_end) > MAX_TRIP_DURATION){
            return "Max trip duration cannot be over than 60 days";
        }
        Trip::total_duration -= GetDuration();
        this->date_of_start = date_of_start;
        Trip::total_duration += GetDuration();
    }
    else{
        this->date_of_start = date_of_start;
    }
    return std::nullopt;
}


std::chrono::year_month_day Trip::GetDateOfEnd() {
	return this->date_of_end;
}

std::optional<const char*> Trip::SetDateOfEnd(std::chrono::year_month_day date_of_end) {
    if (!this->date_of_start.ok())
        return "Before setting the date of end, set valid date of start";
     
    else if (date_of_end <= this->date_of_start)
        return "Date of end cannot be less or equal then date of start";
   
    else if (getDateDifference(this->date_of_start, date_of_end) > MAX_TRIP_DURATION)
        return "Max trip duration cannot be over than 60 days";

    
    Trip::total_duration -= GetDuration();
    this->date_of_end = date_of_end;
    Trip::total_duration += GetDuration();

    return std::nullopt;
}


size_t Trip::GetDuration() {
    if (!date_of_start.ok() || !date_of_end.ok()) return 0;
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
    total_price -= this->price;
	this->price = price;
    total_price += this->price;
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

std::chrono::year_month_day Trip::GetDateOfBooking()
{
	return this->date_of_booking;
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

