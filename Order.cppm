module;
#include <string>

export module Order;

export struct Order {
	std::string name_of_trip;
	int year_of_booking;
	std::string country;
	size_t duration; 
	double price; 
	size_t customer_id;
	Order( std::string name_of_trip, int year_of_booking, std::string country, size_t duration, double price, size_t customer_id)
	: name_of_trip(name_of_trip)
	, year_of_booking(year_of_booking)
	, country(country)
	, duration(duration)
	, price(price)
	, customer_id(customer_id)
	{}
};


