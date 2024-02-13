
#include "Customer.h"
        
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
	std::cout << "\n" << "4) Name of company: " << name_of_company;
	std::cout << "\n" << "5) Id of customer: " << personal_id;
	std::cout << "\n" << "6) Count of purchased trips: " << count_of_bought_trips;
	if (GetStatus() == CustomerStatus::WITHOUT_TRIP) {
		std::cout << "\n" << "7) Doesn`t have a trip\n";
		
	}
	else {
		std::cout << "\n" << "7) Have a trip: " << this->trip->GetFullName();
		std::cout << "\n" << "8) Was served by manager: " << name_of_manager;
		
		if (GetStatus() == CustomerStatus::WITH_TRIP)
			std::cout << "\n" << "9) Status: Have a trip\n";

		if (GetStatus() == CustomerStatus::DURING_A_TRIP)
			std::cout << "\n" << "9) Status: during a trip\n";
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


std::string Customer::GetFullName() const
{
	return (second_name + ' ' + first_name + ' ' + patronymic_name);
}

void Customer::SetFullName(std::string name)
{
	while (true) {
		if (name == "-") {
			std::cout << "\n\nThe name "-" is not valid. \nEnter a new name: ";
			std::cin>>name;
			continue;
		}
		else {

			second_name.clear();

			for (char i : name) {
				if (i == ' ')
					break;
				second_name.push_back(i);
			}

			for (size_t i = second_name.length() + 1; i < name.length(); i++) {
				if (name[i] == ' ')
					break;
				first_name.push_back(name[i]);
			}

			for (size_t i = first_name.length() + second_name.length() + 2; i < name.length(); i++)
				patronymic_name.push_back(name[i]);

			break;
		}	
	}
}


std::string Customer::GetFirstName()
{
	return first_name;
}

void Customer::SetFirstName(std::string first_name)
{
	this->first_name = first_name;
}

std::string Customer::GetSecondName()
{
	return second_name;
}

void Customer::SetSecondName(std::string second_name)
{
	this->second_name = second_name;
}

std::string Customer::GetPatronymicName()
{
	return patronymic_name;
}

void Customer::SetPatronymicName(std::string patronymic_name)
{
	this->patronymic_name = patronymic_name;
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


std::string Customer::GetPhoneNumber()
{
	return this->phone_number;
}

void Customer::SetPhoneNumber(std::string phone_number)
{
	bool is_symbol, equal;
	long long number = 0;

	if (phone_number == "-") {
		this->phone_number = phone_number;
		PhoneNumbers.emplace_back(this->phone_number);
	}

	else {
		while (true) {

			if (phone_number.length() < 13) {
				std::cout << "\n\nYour number is shorter than required. Try again";
				std::cout << "\nPlease enter a new phone number (format: +380XXXXXXXXX) ";

				std::cout << "\nNew phone number: ";
				std::cin >> phone_number;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if (phone_number.length() > 13) {
				std::cout << "\n\nYour number is longer than required. Try again";
				std::cout << "\nPlease enter a new phone number (format: +380XXXXXXXXX) ";

				std::cout << "\nNew phone number: ";
				std::cin >> phone_number;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if (phone_number.substr(0, 4) != "+380") {
				std::cout << "\n\nYour number is in the wrong format. Try again";
				std::cout << "\nPlease enter a new phone number (format: +380XXXXXXXXX) ";

				std::cout << "\nNew phone number: ";
				std::cin >> phone_number;
				std::cin.ignore(LLONG_MAX, '\n');
			}


			is_symbol = false;
			for (size_t i = 1; i < phone_number.length(); i++) {
				if (static_cast<int>(phone_number[i]) < 48 || static_cast<int>(phone_number[i]) > 57) {
					std::cout << "\n\nThe entered number contains a symbol. Try again";
					std::cout << "\nPlease enter a new phone number (format: +380 XXXXXXXXX) ";
					std::cout << "\nNew phone number: ";
					std::cin >> phone_number;
					std::cin.ignore(LLONG_MAX, '\n');
					is_symbol = true;
					break;
				}
			}
			if (is_symbol)
				continue;

			equal = false;

			for (size_t i = 0; i < PhoneNumbers.size(); i++) {

				if (phone_number == PhoneNumbers[i]) {
					std::cout << "\n\nThey are trying to assign someone else's number to a customer named " << this->GetFullName();

					equal = true;

					std::cout << "\nPlease enter a new phone number (format: +380 XXXXXXXXX) ";

					std::cout << "\nNew phone number: ";
					std::cin >> phone_number;
					std::cin.ignore(LLONG_MAX, '\n');
					break;

				}
			}

			if (equal)
				continue;
			else
				break;
		}
		this->phone_number = phone_number;
		PhoneNumbers.emplace_back(this->phone_number);
	}
}


std::string  Customer::GetNameOfCompany()
{
	return name_of_company;
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
		if (this->trip->GetStatus() == TripStatus::PURCHASED)
			return CustomerStatus::WITH_TRIP;
		else if (this->trip->GetStatus() == TripStatus::USING)
			return CustomerStatus::DURING_A_TRIP;
		else if (this->trip->GetStatus() == TripStatus::USED)
			return CustomerStatus::WITHOUT_TRIP;
}
