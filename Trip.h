#pragma once
#include "Person.h" // <iostream> + <string> + <vector> 
#include <list>


// перелік статусів путівки
enum class TripStatus {
	SELLING, // путівка у продажі
	PURCHASED, // путівка продана
	USING, // путівка використовується (подорож почалася)
	USED, // путівка використана (подорож закінчилася)
	EXPIRED // путівка прострочена (подорож почалася, проте путівка не придбана)
};

class Trip
{
	friend class Manager;
	friend void ReadTripsData(std::list<std::shared_ptr<Trip>>& Trips, const std::string path); // метод для зчитування даних про путівки з файлу

private:
	std::string name; // назва путівки
	std::string country; // країна путівки
	std::string city; // місто путівки
	std::string date_of_start; // дата початку путівки
	std::string date_of_end; // дата завершення путівки
	
	double price; //ціна путівки
	int personal_id; // персональний індентифікатор

	std::string name_of_customer;// ім'я клієнта, який придбав цю путівку
	std::string name_of_manager; // ім'я менеджера, який продав цю путівку
	std::string date_of_booking; // дата придбання путівки

	static int total_duration; // загальна тривалість подорожей
	static double total_price; // загальна вартість подорожей
	static std::vector<int> Identifiers; // коллекція персональних індентифікаторів

	void SetDataOfPurchase(std::string name_of_manager, std::string name_of_customer); // метод фіксації купівлі путівки

	void Return(); // метод фіксації повернення путівки

	int GetDateDifference(const std::string firstDate, const std::string secondDate = "today"); // метод для отримання різниці між двома датами

public:
	Trip(std::string name = "-", std::string country = "-", std::string city = "-", std::string date_of_start = "-", std::string date_of_end = "-", double price = 0, int personal_id = 0, std::string name_of_customer = "-", std::string name_of_manager = "-", std::string date_of_booking = "-");

	Trip(const Trip& trip); // Констуктор копіювання

	~Trip(); // деструктор

	void ShowInfo(); // метод для виводу повної інформації про об'єкт.

	std::string GetFullName(); // метод для отримання повної назви.
	void SetFullName(std::string name); // метод для встановлення повної назви.

	std::string GetCountry(); // метод для отримання назви країни.
	void SetCountry(std::string country); // метод для встановлення назви країни.
	 
	std::string GetCity(); // метод для отримання назви міста.
	void SetCity(std::string city); // метод для встановлення назви міста.

	std::string GetDateOfStart(); // метод для отримання дати початку.
	void SetDateOfStart(std::string date_of_start); // метод для встановлення дати початку.

	std::string GetDateOfEnd(); // метод для отримання дати закінчення.
	void SetDateOfEnd(std::string date_of_end);  // метод для встановлення дати закінчення.

	int GetDuration(); // метод для отримання тривалості (в днях).

	double GetPrice(); // метод для отримання вартості (в UAH).
	void SetPrice(double price); // метод для встановлення вартості (в UAH).

	int GetPersonalId(); // метод для отримання персонального ідентифікатора.

	TripStatus GetStatus(); // метод для отримання поточного статусу путівки.

	std::string GetDateOfBooking(); // метод для отримання дати придбання путівки.
	std::string GetNameOfCustomer(); // метод для отримання ім'я клієнта, який придбав цю путівку.
	std::string GetNameOfManager(); // метод для отримання ім'я менеджера, який продав цю путівку.
	
	static double GetAveragePrice();  // метод для отримання середньої вартості (в UAH).
	static double GetAverageDuration(); // метод для отримання середньої тривалост (в днях).
};
