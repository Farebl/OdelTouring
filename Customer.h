#pragma once
#include "Trip.h" // Person.h +  <iostream> + <string> + <vector> + <list> 

// ������ ������� �볺��� 
enum class CustomerStatus {
	WITHOUT_TRIP, // �볺�� ��� ������
	WITH_TRIP, // �볺�� �� ������
	DURING_A_TRIP // �볺�� ����� � �������
};

class Customer : public Person {
	friend class Manager;

private:
	std::string address; // ������ ����������
	int count_of_bought_trips; // ������ �������� ������ �� ���� ���
	std::shared_ptr<Trip> trip; // �������� ������
	std::string name_of_manager; // ��'� ���������, ���� �볺�� ��� ��������������

	void BuyTrip(std::shared_ptr<Trip>& trip); // ����� �������� ����� ������
	void ReturnTrip(); // ����� �������� ��������� ������

public:

	// ����������� � �����������
	Customer(const std::string name = "-", const std::string phone_number = "-", const std::string address = "-", int count_of_bought_trips = 0, const int personal_id = 0,  const std::shared_ptr<Trip>& trip = nullptr);
	Customer(const Customer& �ustomer); // ���������� ���������
	~Customer() override; // ����������

	void ShowInfo() override; // ����� ��� ������ ����� ���������� ��� ��'���.

	std::string GetFullName() const; // ����� ��� ��������� ������� ���� (ϲ�).
	void SetFullName(std::string name); // ����� ��� ������������ ������� ���� (ϲ�).
	
	std::string GetFirstName(); // ����� ��� ��������� ��'�.
	void SetFirstName(std::string first_name); // ����� ��� ������������ ��'�.
	
	std::string GetSecondName(); // ����� ��� ��������� ��������.
	void SetSecondName(std::string second_name); // ����� ��� ������������ ��������.
	
	std::string GetPatronymicName(); // ����� ��� ��������� ��-�������.
	void SetPatronymicName(std::string patronymic_name); // ����� ��� ������������ ��-�������.

	std::string GetPhoneNumber(); // ����� ��� ��������� ������ ��������.
	void SetPhoneNumber(std::string phone_number); // ����� ��� ������������ ������ ��������.

	std::string GetAddress(); // ����� ��� ��������� ������ ����������.
	void SetAddress(std::string address); // ����� ��� ������������ ������ ����������.

	static std::string GetNameOfCompany(); // ����� ��� ��������� ����� ������.
	
	int GetCountOfBoughtTrips(); // ����� ��� ��������� ������� ��������� ������ �� ���� ���.

	int GetPersonalId(); // ����� ��� ��������� ������������� ��������������.

	std::shared_ptr<Trip>& GetTrip(); // ����� ��� ��������� �������� ������.

	std::string GetNameOfManager(); // ����� ��� ��������� ���� ���������, ���� �볺�� ��� ��������������.

	CustomerStatus GetStatus(); // ����� ��� ��������� ��������� ������� �볺���.
};
