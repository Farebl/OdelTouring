#pragma once
#include "Trip.h" // Person.h +  <iostream> + <string> + <vector> + <list> 

// перелік статусів клієнта 
enum class CustomerStatus {
	WITHOUT_TRIP, // клієнт без путівки
	WITH_TRIP, // клієнт має путівку
	DURING_A_TRIP // клієнт поїхав у подорож
};

class Customer : public Person {
	friend class Manager;

private:
	std::string address; // адреса проживання
	int count_of_bought_trips; // кількісь куплених путівок за весь час
	std::shared_ptr<Trip> trip; // придбана путівка
	std::string name_of_manager; // Їм'я менеджера, яким клієнт був обслуговуваний

	void BuyTrip(std::shared_ptr<Trip>& trip); // метод фіксації купівлі путівки
	void ReturnTrip(); // метод фіксації поверненя путівки

public:

	// конструктор з параметрами
	Customer(const std::string name = "-", const std::string phone_number = "-", const std::string address = "-", int count_of_bought_trips = 0, const int personal_id = 0,  const std::shared_ptr<Trip>& trip = nullptr);
	Customer(const Customer& сustomer); // Констуктор копіювання
	~Customer() override; // деструктор

	void ShowInfo() override; // метод для виводу повної інформації про об'єкт.

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

	std::string GetAddress(); // метод для отримання адреса проживання.
	void SetAddress(std::string address); // метод для встановлення адреса проживання.

	static std::string GetNameOfCompany(); // метод для отримання назви компанії.
	
	int GetCountOfBoughtTrips(); // метод для отримання кількості придбаних путівок за весь час.

	int GetPersonalId(); // метод для отримання персонального ідентифікатора.

	std::shared_ptr<Trip>& GetTrip(); // метод для отримання придбаної путівки.

	std::string GetNameOfManager(); // метод для отримання імені менеджера, яким клієнт був обслуговуваний.

	CustomerStatus GetStatus(); // метод для отримання поточного статусу клієнта.
};
