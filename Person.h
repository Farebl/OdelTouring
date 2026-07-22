#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <climits>


class Person {
protected:
	std::string first_name, second_name, patronymic_name; 
	std::string phone_number; 
	static std::string name_of_company;
	int personal_id; 

	static std::vector<int> Identifiers; 
    static std::vector<std::string> PhoneNumbers;

	Person(const std::string type, const std::string name, const std::string phone_number, const int personal_id = 0);
	virtual~Person();

	 
	template<typename T>
	void ValidatedInput(T& val) {
		while (true) {
			std::cin >> val;
			if (std::cin.fail())
			{
				std::cout << "\n\nYou may have entered wrong value. Try again.\n";
				std::cin.clear(); // 
				std::cin.ignore(LLONG_MAX, '\n');
			}
			else
				break;
		}
		std::cin.ignore(INT_MAX, '\n');
	}

public:
	virtual void ShowInfo() = 0;

};
