#pragma once

#include <iostream>
#include <string>
#include <vector>


class Person {
protected:
	std::string first_name, second_name, patronymic_name; // ім'я призвищеб по-батькові
	std::string phone_number; // номер телефону
	static std::string name_of_company; // назва компанії
	int personal_id; // персональний індентифікатор

	static std::vector<int> Identifiers; // коллекція персональних індентифікаторів
	static std::vector<std::string> PhoneNumbers;// коллекція номерів телефонів

	Person(const std::string type, const std::string name, const std::string phone_number, const int personal_id = 0);
	virtual~Person();

	// метод для коректного вводу знаення до типу даних. 
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
