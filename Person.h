#pragma once

#include <string>
#include <vector>

class Person {
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
