#pragma once

#include "Customer.h" // Trip.h + Person.h +  <iostream> + <string> + <vector> + <list> 

class Manager : public Person {
public:
	// ����������� � �����������
	Manager(const std::string name = "-", const std::string phone_number = "-", const int personal_id = 0);
	Manager(const Manager& manager); // ����������� ���������
	~Manager() override; // ����������

	void ShowInfo() ; // ����� ��� ������ ����� ���������� ��� ��'���.

	void SaleTheTrip(std::shared_ptr<Customer>& customer, std::shared_ptr<Trip>& trip); // ����� ���������� ���������
	void ReturnTheTrip(std::shared_ptr<Customer>& customer); // ����� ���������� ��������� ���������

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

	static std::string GetNameOfCompany(); // ����� ��� ��������� ����� ������.
	static void SetNameOfCompany(std::string name_of_company); // ����� ��� ������������ ����� ������.

	int GetPersonalId(); // ����� ��� ��������� ������������� ��������������.
};
