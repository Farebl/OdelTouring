module;
#include <string>

export module Order;

export struct Order {
	std::string name_of_trip;
	int year_of_booking;
	std::string country;
	size_t duration; 
	double price; 
	std::string name_of_customer;
	Order( std::string name_of_trip, int year_of_booking, std::string country, size_t duration, double price, std::string name_of_customer)
	: name_of_trip(name_of_trip)
	, year_of_booking(year_of_booking)
	, country(country)
	, duration(duration)
	, price(price)
	, name_of_customer(name_of_customer)
	{}
};


