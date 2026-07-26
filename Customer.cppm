module;

#include <iostream>
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



Customer::Customer(std::string name, std::string phone_number, std::string address, int count_of_bought_trips, int personal_id, const std::shared_ptr<Trip>& trip) :Person("CUSTOMER", name, phone_number, personal_id)
{
	this->address = address;
	this->count_of_bought_trips = count_of_bought_trips;
	this->trip = trip;

	if (GetStatus() == CustomerStatus::WITHOUT_TRIP)
		name_of_manager = "-";
	else
		name_of_manager = trip->GetNameOfManager();
}

Customer::Customer(const Customer& customer) :Person("CUSTOMER", customer.GetFullName(), customer.phone_number) {
	this->address = customer.address;
	this->trip = nullptr;

	this->name_of_manager = "-";
}

Customer::~Customer()
{
}

void Customer::ShowInfo()
{
	std::cout << "\n\n" << "1) Name: " << (second_name + ' ' + first_name + ' ' + patronymic_name);
	std::cout << "\n" << "2) Phone number: " << phone_number;
	std::cout << "\n" << "3) Address: " << address;
	std::cout << "\n" << "4) Id of customer: " << personal_id;
	std::cout << "\n" << "5) Count of purchased trips: " << count_of_bought_trips;
	if (GetStatus() == CustomerStatus::WITHOUT_TRIP) {
		std::cout << "\n" << "6) Doesn`t have a trip\n";
		
	}
	else {
		std::cout << "\n" << "6) Have a trip: " << this->trip->GetFullName();
		std::cout << "\n" << "7) Was served by manager: " << name_of_manager;
		
		if (GetStatus() == CustomerStatus::WITH_TRIP)
			std::cout << "\n" << "8) Status: Have a trip\n";

		if (GetStatus() == CustomerStatus::DURING_A_TRIP)
			std::cout << "\n" << "8) Status: during a trip\n";
	}
}


std::shared_ptr<Trip>& Customer::GetTrip() {
	return this->trip;
}

void Customer::BuyTrip(std::shared_ptr<Trip>& trip) {
	this->trip = trip;
	this->name_of_manager = this->trip->GetNameOfManager();
	this->count_of_bought_trips++;
}

void Customer::ReturnTrip()
{
	this->trip.reset();
	this->name_of_manager = "-";
	this->count_of_bought_trips--;
}


std::string Customer::GetAddress()
{
	return this->address;
}

void Customer::SetAddress(std::string address)
{
	this->address = address;
}


int Customer::GetCountOfBoughtTrips()
{
	return this->count_of_bought_trips;
}



int Customer::GetPersonalId()
{
	return this->personal_id;
}


std::string Customer::GetNameOfManager()
{
	return this->name_of_manager;
}


CustomerStatus Customer::GetStatus()
{
	if (this->trip == nullptr)
		return CustomerStatus::WITHOUT_TRIP;
	else
		if (this->trip->GetStatus() == TripStatus::SOLD)
			return CustomerStatus::WITH_TRIP;
		else if (this->trip->GetStatus() == TripStatus::IN_PROGRESS)
			return CustomerStatus::DURING_A_TRIP;
		else if (this->trip->GetStatus() == TripStatus::FINISHED)
			return CustomerStatus::WITHOUT_TRIP;
}
