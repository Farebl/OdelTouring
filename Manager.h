#pragma once

#include "Customer.h" // Trip.h + Person.h +  <iostream> + <string> + <vector> + <list> 

class Manager : public Person {
public:
	// конструктор з параметрами
	Manager(const std::string name = "-", const std::string phone_number = "-", const int personal_id = 0);
	Manager(const Manager& manager); // конструктор копіювання
	~Manager() override; // деструктор

	void ShowInfo() ; // метод для виводу повної інформації про об'єкт.

	void SaleTheTrip(std::shared_ptr<Customer>& customer, std::shared_ptr<Trip>& trip); // метод оформлення змовлення
	void ReturnTheTrip(std::shared_ptr<Customer>& customer); // метод оформлення поверення змовлення

	std::string GetFullName() const; // метод для отримання повного імені (ПІБ).
	void SetFullName(std::string name); // метод для встановлення повного імені (ПІБ).

	std::string GetFirstName(); // метод для отримання ім'я.
	void SetFirstName(std::string first_name); // метод для встановлення ім'я.

	std::string GetSecondName(); // метод для отримання призвища.
	void SetSecondName(std::string second_name); // метод для встановлення призвища.

	std::string GetPatronymicName(); // метод для отримання по-батькові.
	void SetPatronymicName(std::string patronymic_name); // метод для встановлення по-батькові.

	std::string GetPhoneNumber(); // метод для отримання номера телефона.
	void SetPhoneNumber(std::string phone_number); // метод для встановлення номера телефона.

	static std::string GetNameOfCompany(); // метод для отримання назви компанії.
	static void SetNameOfCompany(std::string name_of_company); // метод для встановелння назви компанії.

	int GetPersonalId(); // метод для отримання персонального ідентифікатора.
};
