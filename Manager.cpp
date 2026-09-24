module;

#include <iostream>
#include <memory>
#include <expected>

module CustomerManagerTrip;


Manager::Manager(const std::string name, const std::string phone_number, const int personal_id) :Person("MANAGER", name, phone_number, personal_id) {}

Manager::Manager(const Manager& manager) : Person("MANAGER", manager.GetFullName(), manager.phone_number) {}

Manager::~Manager() {}


void Manager::ShowInfo()
{
	std::cout << "\n\n" << "1) Name: " << (second_name + ' ' + first_name + ' ' + patronymic_name);
	std::cout << "\n" << "2) Phone number: " << phone_number;
	std::cout << "\n" << "3) Id of manager: " << personal_id << "\n";
}



std::expected<std::shared_ptr<Order>, const char*> Manager::SaleTheTrip(std::shared_ptr<Customer>& customer, std::shared_ptr<Trip>& trip) {

	if (trip->GetStatus() == TripStatus::SOLD || trip->GetStatus() == TripStatus::IN_PROGRESS) {
		return std::unexpected{"The trip is already bought"};
	}
	if (customer->GetStatus() == CustomerStatus::WITH_TRIP || customer->GetStatus() == CustomerStatus::DURING_A_TRIP) {
		return std::unexpected{"The trip is already bought"};
	}

	trip->SetDataOfPurchase(GetFullName(), customer->GetFullName());
	customer->BuyTrip(trip);

    auto year = static_cast<int>(trip->GetDateOfBooking().year());

    auto order_ptr = std::make_shared<Order>(trip->GetFullName(), year, trip->GetCountry(), trip->GetDuration(), trip->GetPrice(), customer->GetPersonalId());
    return order_ptr;
}
																																					
std::expected<bool, const char*> Manager::ReturnTheTrip(std::shared_ptr<Customer>& customer) {

	if (customer->GetStatus() == CustomerStatus::WITHOUT_TRIP) {
		return std::unexpected{"The customer doesn`t have a trip "};
	}

	else if (customer->GetStatus() == CustomerStatus::DURING_A_TRIP) {
		return std::unexpected{"The trip has already started, so it is non-refundable"};
	}
		
	customer->GetTrip()->Return();
	customer->ReturnTrip();
    return true;
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

int Manager::GetPersonalId()
{
	return personal_id;
}

