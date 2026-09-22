
module;

#include <iostream>
#include <memory>

module CustomerManagerTrip;




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
