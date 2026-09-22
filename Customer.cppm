module;

#include <string>
#include <memory>

export module CustomerManagerTrip:Customer;

import Person;
export import :Trip;


// Status of the customer
export enum class CustomerStatus {
	WITHOUT_TRIP, 
	WITH_TRIP, // customer have a trip, wich hasn`t started yet
	DURING_A_TRIP // customer in the trip now
};

export class Customer : public Person {
	friend class Manager;

private:
	std::string address; // where customer lives
	int count_of_bought_trips; 
	std::shared_ptr<Trip> trip; 
    std::string name_of_manager; // manager who serviced currrent trip

	void BuyTrip(std::shared_ptr<Trip>& trip); // ìåòîä ô³êñàö³¿ êóï³âë³ ïóò³âêè
	void ReturnTrip(); // ìåòîä ô³êñàö³¿ ïîâåðíåíÿ ïóò³âêè

public:

	Customer(const std::string name = "-", const std::string phone_number = "-", const std::string address = "-", int count_of_bought_trips = 0, const int personal_id = 0,  const std::shared_ptr<Trip>& trip = nullptr);
	Customer(const Customer& customer); 
    ~Customer() override; 

	void ShowInfo() override; 

	std::string GetAddress(); 
	void SetAddress(std::string address); 

	int GetCountOfBoughtTrips(); 

	int GetPersonalId();  

	std::shared_ptr<Trip>& GetTrip(); // returns current trip

	std::string GetNameOfManager(); //return the name of the manager who serviced currrent trip

	CustomerStatus GetStatus(); // return the current status of the customer
};


