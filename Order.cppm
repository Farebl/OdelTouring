module;
#include <string>

export module Order;

export struct Order {
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


