module;

#include <string>
#include <vector>
#include <iostream> 
#include <climits> 
#include <algorithm>
#include <optional>

export module Person;

std::optional<const char*> phomeNumberIsWrong(const std::string& phone_number);

export class Person {
    friend std::optional<const char*> phomeNumberIsWrong(const std::string& phone_number);

protected:
	std::string first_name, second_name, patronymic_name; 
	std::string phone_number; 
	int personal_id; 
	
	static std::vector<int> Identifiers; 
    static std::vector<std::string> PhoneNumbers;

	Person(const std::string type, const std::string name, const std::string phone_number, const int personal_id = 0);
	virtual~Person();

public:
	virtual void ShowInfo() = 0;

};


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
        auto error = phomeNumberIsWrong(phone_number);
		while(error){		    	
            std::cout << "\nPlease enter a new phone number (format: +380 XXXXXXXXX) ";

            std::cout << "\nNew phone number: ";
            std::cin >> phone_number;
            std::cin.ignore(LLONG_MAX, '\n');
            error = phomeNumberIsWrong(phone_number);
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



std::optional<const char*> phomeNumberIsWrong(const std::string& phone_number){     
    if (phone_number.length() < 13) {
        return "This number is shorter than required";
    }

    if (phone_number.length() > 13) {
        return "This number is longer than required";
    }
    
    if (phone_number.substr(0, 4) != "+380") {
        return "This number has wrong code";
    }

    auto res_it = std::find_if(phone_number.begin()+3, phone_number.end(), [](char c){return (c < 48 || c > 57);});
    if (res_it != phone_number.end()){
        return "The entered number contains a symbol";
    }
    auto res_it2 = std::find(Person::PhoneNumbers.begin(), Person::PhoneNumbers.end(), phone_number);
    if (res_it2 != Person::PhoneNumbers.end()){
        return "This phone number is already registered";
    }

    return std::nullopt;
}
