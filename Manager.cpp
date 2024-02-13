#include "Manager.h"


Manager::Manager(const std::string name, const std::string phone_number, const int personal_id) :Person("MANAGER", name, phone_number, personal_id) {
}

Manager::Manager(const Manager& manager) : Person("MANAGER", manager.GetFullName(), manager.phone_number) {
}

Manager::~Manager() {
}

void Manager::ShowInfo()
{
	std::cout << "\n\n" << "1) Name: " << (second_name + ' ' + first_name + ' ' + patronymic_name);
	std::cout << "\n" << "2) Phone number: " << phone_number;
	std::cout << "\n" << "3) Name of the company: " << name_of_company;
	std::cout << "\n" << "4) Id of manager: " << personal_id << "\n";
}



void Manager::SaleTheTrip(std::shared_ptr<Customer>& customer, std::shared_ptr<Trip>& trip) {

	if (trip->GetStatus() == TripStatus::PURCHASED || trip->GetStatus() == TripStatus::USING) {
		std::cout << "The trip \"" << trip->GetFullName() << "\" is already bought by" << trip->GetNameOfCustomer()<< "\n";
		return;
	}
	if (customer->GetStatus() == CustomerStatus::WITH_TRIP || customer->GetStatus() == CustomerStatus::DURING_A_TRIP) {
		std::cout << "The customer \"" << customer->GetFullName() << "\" is already have a trip \"" << customer->GetTrip()->GetFullName() << "\"\n";
		return;
	}

	trip->SetDataOfPurchase(this->second_name + ' ' + this->first_name + ' ' + this->patronymic_name, customer->GetFullName());

	customer->BuyTrip(trip);
}
																																					
void Manager::ReturnTheTrip(std::shared_ptr<Customer>& customer) {

	if (customer->GetStatus() == CustomerStatus::WITHOUT_TRIP) {
		std::cout << "A customer named " << customer->GetFullName() << " doesn`t have a trip - he has nothing to return";
		return;
	}

	else if (customer->GetStatus() == CustomerStatus::DURING_A_TRIP) {
		std::cout << "\n\nThe tour, client \"" << customer->GetFullName() <<"\", has already started, so it is non-refundable\n";
		return;
	}
		
	else if ((customer->GetStatus() == CustomerStatus::WITH_TRIP)) {
		customer->GetTrip()->Return();
		customer->ReturnTrip();
	}
}


std::string Manager::GetFullName() const
{
	return (second_name + ' ' + first_name + ' ' + patronymic_name);
}

void Manager::SetFullName(std::string name)
{
	while (true) {
		if (name == "-") {
			std::cout << "\n\nThe name " - " is not valid. \nEnter a new name: ";
			std::cin >> name;
			std::cin.ignore(LLONG_MAX, '\n');
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


std::string Manager::GetFirstName()
{
	return first_name;
}

void Manager::SetFirstName(std::string first_name)
{
	this->first_name = first_name;
}

std::string Manager::GetSecondName()
{
	return second_name;
}

void Manager::SetSecondName(std::string second_name)
{
	this->second_name = second_name;
}

std::string Manager::GetPatronymicName()
{
	return patronymic_name;
}

void Manager::SetPatronymicName(std::string patronymic_name)
{
	this->patronymic_name = patronymic_name;
}


std::string Manager::GetPhoneNumber()
{
	return this->phone_number;
}

void Manager::SetPhoneNumber(std::string phone_number)
{
	bool is_symbol, equal;
	long long  number = 0;

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
					std::cout << "\n\nThey are trying to assign someone else's number to a manager named " << this->GetFullName();
					
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

std::string Manager::GetNameOfCompany()
{
	return name_of_company;
}

void Manager::SetNameOfCompany(std::string name)
{
	name_of_company = name;
}

int Manager::GetPersonalId()
{
	return personal_id;
}
