module;

#include <iostream> 
#include <memory>
#include <expected>

export module CustomerManagerTrip:Manager;
import Person;
import Order;
import :Customer;



export class Manager : public Person {
public:
	Manager(const std::string name = "-", const std::string phone_number = "-", const int personal_id = 0);
	Manager(const Manager& manager); 
	~Manager() override; 

	void ShowInfo() override; 

    std::expected<Order, const char*> SaleTheTrip(std::shared_ptr<Customer>& customer, std::shared_ptr<Trip>& trip);
	std::expected<bool, const char*> ReturnTheTrip(std::shared_ptr<Customer>& customer); 
	
    std::string GetFullName() const; 
	void SetFullName(std::string name); 

	std::string GetFirstName();
	void SetFirstName(std::string first_name);

	std::string GetSecondName(); 
    void SetSecondName(std::string second_name);

	std::string GetPatronymicName(); 
	void SetPatronymicName(std::string patronymic_name); 

	std::string GetPhoneNumber(); 
    void SetPhoneNumber(std::string phone_number); 

	int GetPersonalId(); 
};
