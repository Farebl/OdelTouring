module;
#include <string>
#include <memory>
#include <cstring>
#include <chrono>
#include <vector> 


export module CustomerManagerTrip:Trip;

const unsigned char MAX_TRIP_DURATION = 60; // days


export enum class TripStatus {
    ON_SALE,
	SOLD, 
    IN_PROGRESS, 
	FINISHED, 
	EXPIRED 
};

export size_t getDateDifference(std::chrono::year_month_day startDate, std::chrono::year_month_day endDate);

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
    Trip();

    Trip(std::string name, std::string country, std::string city, std::chrono::year_month_day date_of_start, std::chrono::year_month_day date_of_end, double price, int personal_id);
    Trip(std::string name, std::string country, std::string city, std::chrono::year_month_day date_of_start, std::chrono::year_month_day date_of_end, double price, int personal_id, std::string name_of_customer, std::string name_of_manager, std::chrono::year_month_day date_of_booking);

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
    std::optional<const char*> SetDateOfStart(std::chrono::year_month_day date_of_start); 

    std::chrono::year_month_day GetDateOfEnd(); 
    std::optional<const char*> SetDateOfEnd(std::chrono::year_month_day date_of_end); 

    size_t GetDuration(); 

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

