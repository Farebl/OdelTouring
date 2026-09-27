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
export std::ostream& operator<<(std::ostream& os, const std::chrono::year_month_day& ymd);
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

	static long long total_duration; 
	static double total_price; 
	static std::vector<int> Identifiers; 

	void SetDataOfPurchase(std::string name_of_manager, std::string name_of_customer);

	void Return();
    void setId(size_t id = 0);

public:
    Trip();

    Trip(std::string name, std::string country, std::string city, std::chrono::year_month_day date_of_start, std::chrono::year_month_day date_of_end, double price, int personal_id);
    Trip(std::string name, std::string country, std::string city, std::chrono::year_month_day date_of_start, std::chrono::year_month_day date_of_end, double price, int personal_id, std::string name_of_customer, std::string name_of_manager, std::chrono::year_month_day date_of_booking);

	Trip(const Trip& trip); 

    ~Trip(); 

	void ShowInfo() const; 


	std::string GetFullName() const; 
	void SetFullName(std::string name); 

	std::string GetCountry() const; 
	void SetCountry(std::string country); 
	 
	std::string GetCity() const; 
    void SetCity(std::string city); 

    std::chrono::year_month_day GetDateOfStart() const; 
    std::optional<const char*> SetDateOfStart(std::chrono::year_month_day date_of_start); 

    std::chrono::year_month_day GetDateOfEnd() const; 
    std::optional<const char*> SetDateOfEnd(std::chrono::year_month_day date_of_end); 

    size_t GetDuration() const; 

	double GetPrice() const; 
    void SetPrice(double price); 

	int GetPersonalId() const; 

	TripStatus GetStatus() const;

    std::chrono::year_month_day GetDateOfBooking() const; // date when this trip was bought
	std::string GetNameOfCustomer() const; // customer, who bought this trip
	std::string GetNameOfManager() const; // manager who sold this trip
	
	static double GetAveragePrice(); 
	static double GetAverageDuration();
};

