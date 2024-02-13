#include "Person.h"

std::string Person::name_of_company = "Odel Touring";
std::vector<int> Person::Identifiers;
std::vector<std::string> Person::PhoneNumbers;


Person::Person(const std::string type, const std::string name, std::string phone_number, const int personal_id) {

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

	for (size_t i = (first_name.length() + second_name.length() + 2); i < name.length(); i++)
		patronymic_name.push_back(name[i]);



	bool is_symbol, equal;


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
					
					if (type == "MANAGER") 
						std::cout << "\n\nThey are trying to assign someone else's number to a manager named " << name;
					else
						std::cout << "\n\nThey are trying to assign someone else's number to a customer named " << name;

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

	
	
	
	if (personal_id != 0) {
		this->personal_id = personal_id;
		Identifiers.push_back(this->personal_id);
	}
	else {
		srand(static_cast<unsigned>(time(nullptr)));
		while (true) {
			this->personal_id = rand() % 999 + 1;

			bool availability = false;
			for (size_t i = 0; i <Identifiers.size(); ++i) {
				if (this->personal_id == Identifiers[i]) {
					availability = true;
					break;
				}
			}
			if (availability)
				continue;

			else {
				Identifiers.push_back(this->personal_id);
				break;
			}
		}
	}
}

Person::~Person() {

	auto currentId = Identifiers.begin();
	for (auto& id : Identifiers) {
		if (this->personal_id == id) {
			Identifiers.erase(currentId);
			break;
		}
		else {
			std::advance(currentId, 1);
		}
	}
	auto currentNum = PhoneNumbers.begin();
	for (auto& number : PhoneNumbers) {
		if (this->phone_number == number) {
			PhoneNumbers.erase(currentNum);
			break;
		}
		else {
			std::advance(currentNum, 1);
		}
	}
}


//template<typename T>
//void Person::ValidatedInput(T& val) {
//	while (true) {
//		std::cin >> val;
//		if (std::cin.fail())
//		{
//			std::cout << "\n\nYou may have entered wrong value. Try again.\n";
//			std::cin.clear(); // 
//			std::cin.ignore(LLONG_MAX, '\n');
//		}
//		else
//			break;
//	}
//	std::cin.ignore(INT_MAX, '\n');
//}