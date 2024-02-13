#pragma once
#include "Person.h" // <iostream> + <string> + <vector> 
#include <list>


// ������ ������� ������
enum class TripStatus {
	SELLING, // ������ � ������
	PURCHASED, // ������ �������
	USING, // ������ ��������������� (������� ��������)
	USED, // ������ ����������� (������� ����������)
	EXPIRED // ������ ����������� (������� ��������, ����� ������ �� ��������)
};

class Trip
{
	friend class Manager;
	friend void ReadTripsData(std::list<std::shared_ptr<Trip>>& Trips, const std::string path); // ����� ��� ���������� ����� ��� ������ � �����

private:
	std::string name; // ����� ������
	std::string country; // ����� ������
	std::string city; // ���� ������
	std::string date_of_start; // ���� ������� ������
	std::string date_of_end; // ���� ���������� ������
	
	double price; //���� ������
	int personal_id; // ������������ ��������������

	std::string name_of_customer;// ��'� �볺���, ���� ������� �� ������
	std::string name_of_manager; // ��'� ���������, ���� ������ �� ������
	std::string date_of_booking; // ���� ��������� ������

	static int total_duration; // �������� ��������� ���������
	static double total_price; // �������� ������� ���������
	static std::vector<int> Identifiers; // ��������� ������������ ���������������

	void SetDataOfPurchase(std::string name_of_manager, std::string name_of_customer); // ����� �������� ����� ������

	void Return(); // ����� �������� ���������� ������

	int GetDateDifference(const std::string firstDate, const std::string secondDate = "today"); // ����� ��� ��������� ������ �� ����� ������

public:
	Trip(std::string name = "-", std::string country = "-", std::string city = "-", std::string date_of_start = "-", std::string date_of_end = "-", double price = 0, int personal_id = 0, std::string name_of_customer = "-", std::string name_of_manager = "-", std::string date_of_booking = "-");

	Trip(const Trip& trip); // ���������� ���������

	~Trip(); // ����������

	void ShowInfo(); // ����� ��� ������ ����� ���������� ��� ��'���.

	std::string GetFullName(); // ����� ��� ��������� ����� �����.
	void SetFullName(std::string name); // ����� ��� ������������ ����� �����.

	std::string GetCountry(); // ����� ��� ��������� ����� �����.
	void SetCountry(std::string country); // ����� ��� ������������ ����� �����.
	 
	std::string GetCity(); // ����� ��� ��������� ����� ����.
	void SetCity(std::string city); // ����� ��� ������������ ����� ����.

	std::string GetDateOfStart(); // ����� ��� ��������� ���� �������.
	void SetDateOfStart(std::string date_of_start); // ����� ��� ������������ ���� �������.

	std::string GetDateOfEnd(); // ����� ��� ��������� ���� ���������.
	void SetDateOfEnd(std::string date_of_end);  // ����� ��� ������������ ���� ���������.

	int GetDuration(); // ����� ��� ��������� ��������� (� ����).

	double GetPrice(); // ����� ��� ��������� ������� (� UAH).
	void SetPrice(double price); // ����� ��� ������������ ������� (� UAH).

	int GetPersonalId(); // ����� ��� ��������� ������������� ��������������.

	TripStatus GetStatus(); // ����� ��� ��������� ��������� ������� ������.

	std::string GetDateOfBooking(); // ����� ��� ��������� ���� ��������� ������.
	std::string GetNameOfCustomer(); // ����� ��� ��������� ��'� �볺���, ���� ������� �� ������.
	std::string GetNameOfManager(); // ����� ��� ��������� ��'� ���������, ���� ������ �� ������.
	
	static double GetAveragePrice();  // ����� ��� ��������� �������� ������� (� UAH).
	static double GetAverageDuration(); // ����� ��� ��������� �������� ��������� (� ����).
};
