#include "Trip.h"

std::vector<int> Trip::Identifiers;
double Trip::total_price = 0;
int Trip::total_duration = 0;

Trip::Trip(std::string name, std::string country, std::string city, std::string date_of_start, std::string date_of_end, double price, int personal_id, std::string name_of_customer, std::string name_of_manager, std::string date_of_booking)
{
	this->name = name;
	this->country = country;
	this->city = city;
	this->price = price;
	total_price += this->price;

	this->name_of_customer = name_of_customer;
	this->name_of_manager = name_of_manager;
	this->date_of_booking = date_of_booking;

	std::time_t mytime = std::time(NULL);
	std::tm now;
	gmtime_s(&now, &mytime);

	int start_day, start_month, start_year;
	int end_day, end_month, end_year;

	bool is_wrong_symbol;
	if ((date_of_start != "-" && date_of_end != "-") && date_of_booking == "-")
	{
		while (true) {

			if (date_of_start.length() < 10) {
				std::cout << "\n\nThe start date value is less than required.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if (date_of_start.length() > 10) {

				std::cout << "\n\nThe start date value is greater than required.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			is_wrong_symbol = false;
			for (size_t i = 1; i < date_of_start.length(); i++) {
				if (i != 2 && i != 5) {
					if (static_cast<int>(date_of_start[i]) < 48 || static_cast<int>(date_of_start[i]) > 57) {
						std::cout << "\n\nThe start date contains a symbol. Try again";
						std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
						std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
						std::cout << "\nNew start date (dd/mm/yyyy): ";
						std::cin >> date_of_start;
						std::cin.ignore(LLONG_MAX, '\n');
						is_wrong_symbol = true;
						break;
					}
				}
				else {
					if (date_of_start[i] != '/') {
						std::cout << "\n\nThe start date value is not in the correct format.";
						std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
						std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
						std::cout << "\nNew start date (dd/mm/yyyy): ";
						std::cin >> date_of_start;
						std::cin.ignore(LLONG_MAX, '\n');
					}
				}
			}
			if (is_wrong_symbol)
				continue;

			start_day = std::stoi(date_of_start.substr(0, 2));
			start_month = std::stoi(date_of_start.substr(3, 2));
			start_year = std::stoi(date_of_start.substr(6, 4));

			if (start_year > now.tm_year + 1901) {
				std::cout << "\n\nThe start date contains too much year value. The year value cannot exceed " << now.tm_year + 1901;
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if (start_month < 1 && start_month > 12) {
				std::cout << "\n\nThe start date contains an incorrect month value. Month value: 01-12";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if ((start_month == 1 || start_month == 3 || start_month == 5 || start_month == 7 || start_month == 8 || start_month == 10 || start_month == 12) && (start_day < 1 || start_day > 31)) {
				std::cout << "\n\nThe start date contains the wrong day.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if ((start_month == 4 || start_month == 6 || start_month == 9 || start_month == 11) && (start_day < 1 || start_day > 30)) {
				std::cout << "\n\nThe start date contains the wrong day.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if ((start_month == 2 && start_year % 4 == 0) && (start_day < 1 || start_day > 29)) {
				std::cout << "\n\nThe start date contains the wrong day.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if ((start_month == 2 && start_year % 4 != 0) && (start_day < 1 || start_day > 28)) {
				std::cout << "\n\nThe start date contains the wrong day.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if (
				(start_year > (now.tm_year + 1900))
				||
				((start_year >= (now.tm_year + 1900)) && (start_month > (now.tm_mon + 1)))
				||
				((start_year >= (now.tm_year + 1900)) && (start_month >= (now.tm_mon + 1)) && (start_day > now.tm_mday))
				) {
				this->date_of_start = date_of_start;
				break;
			}

			else {
				std::cout << "\nTicket \"" << name << "\" has an start date less than or equal to the current date.";
				std::cout << "\nPlease, enter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
			}
		}

		start_day = std::stoi(date_of_start.substr(0, 2));
		start_month = std::stoi(date_of_start.substr(3, 2));
		start_year = std::stoi(date_of_start.substr(6, 4));

		while (true) {

			if (date_of_end.length() < 10) {
				std::cout << "\n\nThe end date value is less than required.";
				std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
				std::cout << "\nNew end date (dd/mm/yyyy): ";
				std::cin >> date_of_end;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}
			if (date_of_end.length() > 10) {
				std::cout << "\n\nThe end date value is greater than required.";
				std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
				std::cout << "\nNew end date (dd/mm/yyyy): ";
				std::cin >> date_of_end;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}
			is_wrong_symbol = false;
			for (size_t i = 1; i < date_of_end.length(); i++) {
				if (i != 2 && i != 5) {
					if (static_cast<int>(date_of_end[i]) < 48 || static_cast<int>(date_of_end[i]) > 57) {
						std::cout << "\n\nThe end date contains a symbol. Try again";
						std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy)";
						std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
						std::cout << "\nNew start date (dd/mm/yyyy): ";

						std::cin >> date_of_end;
						std::cin.ignore(LLONG_MAX, '\n');
						is_wrong_symbol = true;
						break;
					}
				}
				else {
					if (date_of_end[i] != '/') {
						std::cout << "\n\nThe end date value is not in the correct format.";
						std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy)";
						std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
						std::cout << "\nNew start date (dd/mm/yyyy): ";
						std::cin >> date_of_end;
						std::cin.ignore(LLONG_MAX, '\n');
					}
				}
			}
			if (is_wrong_symbol)
				continue;

			end_day = std::stoi(date_of_end.substr(0, 2));
			end_month = std::stoi(date_of_end.substr(3, 2));
			end_year = std::stoi(date_of_end.substr(6, 4));

			if (end_year > start_year + 1901) {
				std::cout << "\n\nThe end date contains too much year value. The year value cannot exceed " << start_year + 1901;
				std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy)";
				std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_end;
				std::cin.ignore(LLONG_MAX, '\n');
			}

			if (end_month < 1 && end_month > 12) {
				std::cout << "\n\nThe start date contains an incorrect month value. Month value: 01-12";
				std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy)";
				std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_end;
				std::cin.ignore(LLONG_MAX, '\n');
			}

			if ((end_month == 1 || end_month == 3 || end_month == 5 || end_month == 7 || end_month == 8 || end_month == 10 || end_month == 12) && (end_day < 1 || end_day > 31)) {
				std::cout << "\n\nThe start date contains the wrong day.";
				std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy)";
				std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_end;
				std::cin.ignore(LLONG_MAX, '\n');
			}

			if ((end_month == 4 || end_month == 6 || end_month == 9 || end_month == 11) && (end_day < 1 || end_day > 30)) {
				std::cout << "\n\nThe start date contains the wrong day.";
				std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy)";
				std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_end;
				std::cin.ignore(LLONG_MAX, '\n');
			}

			if ((end_month == 2 && end_year % 4 == 0) && (end_day < 1 || end_day > 29)) {
				std::cout << "\n\nThe start date contains the wrong day.";
				std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy)";
				std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_end;
				std::cin.ignore(LLONG_MAX, '\n');
			}

			if ((end_month == 2 && end_year % 4 != 0) && (end_day < 1 || end_day > 28)) {
				std::cout << "\n\nThe start date contains the wrong day.";
				std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy)";
				std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_end;
				std::cin.ignore(LLONG_MAX, '\n');
			}

			if (
				(end_year > start_year)
				||
				((end_year >= start_year) && (end_month > start_month))
				||
				((end_year >= start_year) && (end_month >= start_month) && (end_day > start_day))
				) {
				this->date_of_end = date_of_end;
				break;
			}

			else {
				std::cout << "\nTicket \"" << name << "\" has an end date less than or equal to the start date.";
				std::cout << "\nPlease enter a new date that is greater than the start date: " << this->date_of_start;
				std::cout << "\nNew end date (dd/mm/yyyy): ";
				std::cin >> date_of_end;
				std::cin.ignore(LLONG_MAX, '\n');
			}
		}
	}

	else {
		this->date_of_start = date_of_start;
		this->date_of_end = date_of_end;
	}

	if (date_of_start != "-" && date_of_end != "-")
		total_duration += GetDateDifference(this->date_of_start, this->date_of_end);

	if (!personal_id == 0) {
		this->personal_id = personal_id;
		Identifiers.push_back(this->personal_id);
	}
	else {
		srand(static_cast<unsigned>(time(nullptr))); 
		while (true) {
			this->personal_id = rand() % 9'999'999 + 1'000'000;

			bool availability = false;
			for (size_t i = 0; i < Identifiers.size(); ++i) {
				if (this->personal_id == Identifiers[i]) {
					availability = true;
					break;
				}
			}

			if (availability) {
				continue;
			}
			else {
				Identifiers.push_back(this->personal_id);
				break;
			}
		}
	}
}


Trip::Trip(const Trip& trip)
{
	this->name = trip.name;
	this->country = trip.country;
	this->city = trip.city;
	this->date_of_start = trip.date_of_start;
	this->date_of_end = trip.date_of_end;
	this->price = trip.price;

	this->date_of_booking = "-";
	this->name_of_customer = "-";
	this->name_of_manager = "-";

	srand(static_cast<unsigned>(time(nullptr))); 
	while (true) {
		personal_id = rand() % 9'999'999 + 1'000'000; 

		bool availability = false;
		for (size_t i = 0; i < Identifiers.size(); ++i) {
			if (personal_id == Identifiers[i]) {
				availability = true;
				break;
			}
		}

		if (availability) 
			continue;
		else {
			Identifiers.push_back(personal_id);
			break;
		}
	}

	total_price += price;
	total_duration += GetDateDifference(this->date_of_start, this->date_of_end);
}

Trip::~Trip()
{
	auto currentId = Identifiers.begin();
	for (auto& id : Identifiers) {
		if (this->personal_id == id) {
			Identifiers.erase(currentId);
		}
		else {
			++currentId;
		}
	}
}


void Trip::ShowInfo()
{
	std::cout << "\n\n1) Name: " << name;
	std::cout << "\n2) Country: " << country;
	std::cout << "\n3) City: " << city;
	std::cout << "\n4) Date of start: " << date_of_start;
	std::cout << "\n5) Date of end: " << date_of_end;
	std::cout << "\n6) Duration: " << GetDateDifference(this->date_of_start, this->date_of_end) << " days ";
	std::cout << "\n7) Price: " << price << " grn.";
	std::cout << "\n8) Id: " << personal_id;
	if (GetStatus() == TripStatus::PURCHASED) {
		std::cout << "\n9) Customer who bought this tour: " << name_of_customer;
		std::cout << "\n10) Manager who sold this tour: " << name_of_manager << "\n";
	}
	else
		std::cout << "\n9) Trip not bought\n";
}


std::string Trip::GetFullName()
{
	return this->name;
}

void Trip::SetFullName(std::string name)
{
	this->name = name;
}


std::string Trip::GetCountry()
{
	return this->country;
}

void Trip::SetCountry(std::string country)
{
	this->country = country;
}


std::string Trip::GetCity()
{
	return this->city;
}

void Trip::SetCity(std::string city)
{
	this->city = city;
}


std::string Trip::GetDateOfBooking()
{
	return this->date_of_booking;
}


std::string Trip::GetDateOfStart() {
	return this->date_of_start;
}

void Trip::SetDateOfStart(std::string date_of_start) {
	std::time_t mytime = std::time(NULL);
	std::tm now;
	gmtime_s(&now, &mytime);

	int start_day, start_month, start_year;
	bool is_wrong_symbol;
	if (date_of_end == "-") {
		while (true) {

			if (date_of_start.length() < 10) {
				std::cout << "\n\nThe start date value is less than required.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if (date_of_start.length() > 10) {

				std::cout << "\n\nThe start date value is greater than required.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			is_wrong_symbol = false;
			for (size_t i = 1; i < date_of_start.length(); i++) {
				if (i != 2 && i != 5) {
					if (static_cast<int>(date_of_start[i]) < 48 || static_cast<int>(date_of_start[i]) > 57) {
						std::cout << "\n\nThe start date contains a symbol. Try again";
						std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
						std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
						std::cout << "\nNew start date (dd/mm/yyyy): ";
						std::cin >> date_of_start;
						std::cin.ignore(LLONG_MAX, '\n');
						is_wrong_symbol = true;
						break;
					}
				}
				else {
					if (date_of_start[i] != '/') {
						std::cout << "\n\nThe start date value is not in the correct format.";
						std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
						std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
						std::cout << "\nNew start date (dd/mm/yyyy): ";
						std::cin >> date_of_start;
						std::cin.ignore(LLONG_MAX, '\n');
					}
				}
			}
			if (is_wrong_symbol)
				continue;

			start_day = std::stoi(date_of_start.substr(0, 2));
			start_month = std::stoi(date_of_start.substr(3, 2));
			start_year = std::stoi(date_of_start.substr(6, 4));

			if (start_year > now.tm_year + 1901) {
				std::cout << "\n\nThe start date contains too much year value. The year value cannot exceed " << now.tm_year + 1901;
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if (start_month < 1 && start_month > 12) {
				std::cout << "\n\nThe start date contains an incorrect month value. Month value: 01-12";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if ((start_month == 1 || start_month == 3 || start_month == 5 || start_month == 7 || start_month == 8 || start_month == 10 || start_month == 12) && (start_day < 1 || start_day > 31)) {
				std::cout << "\n\nThe start date contains the wrong day.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if ((start_month == 4 || start_month == 6 || start_month == 9 || start_month == 11) && (start_day < 1 || start_day > 30)) {
				std::cout << "\n\nThe start date contains the wrong day.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}
			
			if ((start_month == 2 && start_year % 4 == 0) && (start_day < 1 || start_day > 29)) {
				std::cout << "\n\nThe start date contains the wrong day.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}
			
			if ((start_month == 2 && start_year % 4 != 0) && (start_day < 1 || start_day > 28)) {
				std::cout << "\n\nThe start date contains the wrong day.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if (
				(start_year > (now.tm_year + 1900))
				||
				((start_year >= (now.tm_year + 1900)) && (start_month > (now.tm_mon + 1)))
				||
				((start_year >= (now.tm_year + 1900)) && (start_month >= (now.tm_mon + 1)) && (start_day > now.tm_mday))
				) {
				this->date_of_start = date_of_start; 
				break;
			}

			else {
				std::cout << "\nTicket \"" << name << "\" has an start date less than or equal to the current date.";
				std::cout << "\nPlease, enter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
			}
		}
	}
	else {
		int end_day = std::stoi(this->date_of_end.substr(0, 2));
		int end_month = std::stoi(this->date_of_end.substr(3, 2));
		int end_year = std::stoi(this->date_of_end.substr(6, 4));

		int start_day, start_month, start_year;
		while (true) {

			if (date_of_start.length() < 10) {
				std::cout << "\n\nThe start date value is less than required.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal to or greater than the current date and less than the end date: ";
				std::cout << "\n\tcurrent date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\n\tend date: " << date_of_end;

				std::cout << "\n\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if (date_of_start.length() > 10) {

				std::cout << "\n\nThe start date value is greater than required.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal to or greater than the current date and less than the end date: ";
				std::cout << "\n\tcurrent date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\n\tend date: " << date_of_end;

				std::cout << "\n\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if (date_of_start[2] != '/' || date_of_start[5] != '/') {
				std::cout << "\n\nThe start date value is not in the correct format.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal to or greater than the current date and less than the end date: ";
				std::cout << "\n\tcurrent date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\n\tend date: " << date_of_end;

				std::cout << "\n\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			is_wrong_symbol = false;
			for (size_t i = 1; i < date_of_start.length(); i++) {
				if (i != 2 && i != 5) {
					if (static_cast<int>(date_of_start[i]) < 48 || static_cast<int>(date_of_start[i]) > 57) {
						std::cout << "\n\nThe start date contains a symbol. Try again";
						std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
						std::cout << "\nEnter a start date that is equal to or greater than the current date and less than the end date: ";
						std::cout << "\n\tcurrent date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
						std::cout << "\n\tend date: " << date_of_end;

						std::cout << "\n\nNew start date (dd/mm/yyyy): ";
						std::cin >> date_of_start;
						std::cin.ignore(LLONG_MAX, '\n');
						is_wrong_symbol = true;
						break;
					}
				}
				else {
					if (date_of_start[i] != '/') {
						std::cout << "\n\nThe start date value is not in the correct format.";
						std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
						std::cout << "\nEnter a start date that is equal or greater than the current date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
						std::cout << "\nNew start date (dd/mm/yyyy): ";
						std::cin >> date_of_start;
						std::cin.ignore(LLONG_MAX, '\n');
					}
				}
			}
			if (is_wrong_symbol)
				continue;

			start_day = std::stoi(date_of_start.substr(0, 2));
			start_month = std::stoi(date_of_start.substr(3, 2));
			start_year = std::stoi(date_of_start.substr(6, 4));

			if (start_year > now.tm_year + 1901) {
				std::cout << "\n\nThe start date contains too much year value. The year value cannot exceed " << now.tm_year + 1901;
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal to or greater than the current date and less than the end date: ";
				std::cout << "\n\tcurrent date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\n\tend date: " << date_of_end;

				std::cout << "\n\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if (start_month < 1 && start_month > 12) {
				std::cout << "\n\nThe start date contains an incorrect month value. Month value: 01-12";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal to or greater than the current date and less than the end date: ";
				std::cout << "\n\tcurrent date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\n\tend date: " << date_of_end;

				std::cout << "\n\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if ((start_month == 1 || start_month == 3 || start_month == 5 || start_month == 7 || start_month == 8 || start_month == 10 || start_month == 12) && (start_day < 1 || start_day > 31)) {
				std::cout << "\n\nThe start date contains the wrong day.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal to or greater than the current date and less than the end date: ";
				std::cout << "\n\tcurrent date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\n\tend date: " << date_of_end;

				std::cout << "\n\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if ((start_month == 4 || start_month == 6 || start_month == 9 || start_month == 11) && (start_day < 1 || start_day > 30)) {
				std::cout << "\n\nThe start date contains the wrong day.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal to or greater than the current date and less than the end date: ";
				std::cout << "\n\tcurrent date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\n\tend date: " << date_of_end;

				std::cout << "\n\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if ((start_month == 2 && start_year % 4 == 0) && (start_day < 1 || start_day > 29)) {
				std::cout << "\n\nThe start date contains the wrong day.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal to or greater than the current date and less than the end date: ";
				std::cout << "\n\tcurrent date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\n\tend date: " << date_of_end;

				std::cout << "\n\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if ((start_month == 2 && start_year % 4 != 0) && (start_day < 1 || start_day > 28)) {
				std::cout << "\n\nThe start date contains the wrong day.";
				std::cout << "\nPlease, enter the start date in the format (dd/mm/yyyy).";
				std::cout << "\nEnter a start date that is equal to or greater than the current date and less than the end date: ";
				std::cout << "\n\tcurrent date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\n\tend date: " << date_of_end;

				std::cout << "\n\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if (
				(start_year < (now.tm_year + 1900))
				||
				((start_year  <= (now.tm_year + 1900)) && (start_month < (now.tm_mon + 1)))
				||
				( (start_year <= (now.tm_year + 1900)) && (start_month <= (now.tm_mon + 1)) && (start_day <= now.tm_mday ) )
				) {
				std::cout << "\nTicket \"" << name << "\" has an start date less than or equal to the current date.";
				std::cout << "\nPlease, enter a start date that is equal to or greater than the current date and less than the end date: ";
				std::cout << "\n\tcurrent date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\n\tend date: " << date_of_end;

				std::cout << "\n\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			if (
				(start_year > end_year)
				||
				((start_year >= end_year) && (start_month > end_month))
				||
				((start_year >= end_year) && (start_month >= end_month) && (start_day >= end_day))
				) 
			{
				std::cout << "\nTicket \"" << name << "\" has an start date is greater than or equal to end date";
				std::cout << "\nPlease, enter a start date that is equal to or greater than the current date and less than the end date: ";
				std::cout << "\n\tcurrent date: " << std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_year + 1900) << "";
				std::cout << "\n\tend date: " << date_of_end;

				std::cout << "\n\nNew start date (dd/mm/yyyy): ";
				std::cin >> date_of_start;
				std::cin.ignore(LLONG_MAX, '\n');
				continue;
			}

			else {
				this->date_of_start = date_of_start; 
				break;
			}
		}
	}
}


std::string Trip::GetDateOfEnd() {
	return this->date_of_end;
}

void Trip::SetDateOfEnd(std::string date_of_end) {
	if (date_of_start == "-")
		return;

	std::time_t mytime = std::time(NULL);
	std::tm now;
	gmtime_s(&now, &mytime);
	int end_day, end_month, end_year;

	int start_day = std::stoi(date_of_start.substr(0, 2));
	int start_month = std::stoi(date_of_start.substr(3, 2));
	int start_year = std::stoi(date_of_start.substr(6, 4));

	bool is_wrong_symbol;
	while (true) {

		if (date_of_end.length() < 10) {
			std::cout << "\n\nThe end date value is less than required.";
			std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy).";
			std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
			std::cout << "\nNew end date (dd/mm/yyyy): ";
			std::cin >> date_of_end;
			std::cin.ignore(LLONG_MAX, '\n');
			continue;
		}
		if (date_of_end.length() > 10) {
			std::cout << "\n\nThe end date value is greater than required.";
			std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy).";
			std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
			std::cout << "\nNew end date (dd/mm/yyyy): ";
			std::cin >> date_of_end;
			std::cin.ignore(LLONG_MAX, '\n');
			continue;
		}
		is_wrong_symbol = false;
		for (size_t i = 1; i < date_of_end.length(); i++) {
			if (i != 2 && i != 5) {
				if (static_cast<int>(date_of_end[i]) < 48 || static_cast<int>(date_of_end[i]) > 57) {
					std::cout << "\n\nThe end date contains a symbol. Try again";
					std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy)";
					std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
					std::cout << "\nNew start date (dd/mm/yyyy): ";

					std::cin >> date_of_end;
					std::cin.ignore(LLONG_MAX, '\n');
					is_wrong_symbol = true;
					break;
				}
			}
			else {
				if (date_of_end[i] != '/') {
					std::cout << "\n\nThe end date value is not in the correct format.";
					std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy)";
					std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
					std::cout << "\nNew start date (dd/mm/yyyy): ";
					std::cin >> date_of_end;
					std::cin.ignore(LLONG_MAX, '\n');
				}
			}
		}
		if (is_wrong_symbol)
			continue;

		end_day = std::stoi(date_of_end.substr(0, 2));
		end_month = std::stoi(date_of_end.substr(3, 2));
		end_year = std::stoi(date_of_end.substr(6, 4));

		if (end_year > start_year + 1901) {
			std::cout << "\n\nThe end date contains too much year value. The year value cannot exceed " << start_year + 1901;
			std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy)";
			std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
			std::cout << "\nNew start date (dd/mm/yyyy): ";
			std::cin >> date_of_end;
			std::cin.ignore(LLONG_MAX, '\n');
		}

		if (end_month < 1 && end_month > 12) {
			std::cout << "\n\nThe start date contains an incorrect month value. Month value: 01-12";
			std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy)";
			std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
			std::cout << "\nNew start date (dd/mm/yyyy): ";
			std::cin >> date_of_end;
			std::cin.ignore(LLONG_MAX, '\n');
		}

		if ((end_month == 1 || end_month == 3 || end_month == 5 || end_month == 7 || end_month == 8 || end_month == 10 || end_month == 12) && (end_day < 1 || end_day > 31)) {
			std::cout << "\n\nThe start date contains the wrong day.";
			std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy)";
			std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
			std::cout << "\nNew start date (dd/mm/yyyy): ";
			std::cin >> date_of_end;
			std::cin.ignore(LLONG_MAX, '\n');
		}

		if ((end_month == 4 || end_month == 6 || end_month == 9 || end_month == 11) && (end_day < 1 || end_day > 30)) {
			std::cout << "\n\nThe start date contains the wrong day.";
			std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy)";
			std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
			std::cout << "\nNew start date (dd/mm/yyyy): ";
			std::cin >> date_of_end;
			std::cin.ignore(LLONG_MAX, '\n');
		}
		
		if ((end_month == 2 && end_year % 4 == 0) && (end_day < 1 || end_day > 29)) {
			std::cout << "\n\nThe start date contains the wrong day.";
			std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy)";
			std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
			std::cout << "\nNew start date (dd/mm/yyyy): ";
			std::cin >> date_of_end;
			std::cin.ignore(LLONG_MAX, '\n');
		}
		
		if ((end_month == 2 && end_year % 4 != 0) && (end_day < 1 || end_day > 28)) {
			std::cout << "\n\nThe start date contains the wrong day.";
			std::cout << "\nPlease, enter the end date in the format (dd/mm/yyyy)";
			std::cout << "\nEnter an end date that is greater than the start date: " << this->date_of_start;
			std::cout << "\nNew start date (dd/mm/yyyy): ";
			std::cin >> date_of_end;
			std::cin.ignore(LLONG_MAX, '\n');
		}

		if (
			(end_year > start_year)
			||
			((end_year >= start_year) && (end_month > start_month))
			||
			((end_year >= start_year) && (end_month >= start_month) && (end_day > start_day))
			) {
			this->date_of_end = date_of_end;
			break;
		}

		else {
			std::cout << "\nTicket \"" << name << "\" has an end date less than or equal to the start date.";
			std::cout << "\nPlease enter a new date that is greater than the start date: " << this->date_of_start;
			std::cout << "\nNew end date (dd/mm/yyyy): ";
			std::cin >> date_of_end;
			std::cin.ignore(LLONG_MAX, '\n');
		}
	}
}


int Trip::GetDuration() {
	if (date_of_start != "-" && date_of_end != "-")
		return GetDateDifference(this->date_of_start, this->date_of_end);
	else
		return 0;
}


double Trip::GetPrice() {return this->price;}

void Trip::SetPrice(double price) {
	while (true) {
		if (price <= 0) {
			std::cout << "\nThe product price cannot be less than 0. Enter a new price: ";
			std::cin >> price;
			std::cin.ignore(LLONG_MAX, '\n');
			continue;
		}
		else 
			break;
	}
	this->price = price;
}


int Trip::GetPersonalId(){
	return this->personal_id;
}


TripStatus Trip::GetStatus()
{
	if (this->date_of_booking == "-") {

		if (GetDateDifference(this->date_of_start) > 0)
			return TripStatus::SELLING;

		else if (GetDateDifference(this->date_of_start) <= 0)
			return TripStatus::EXPIRED;
	}
	else
	{
		if (GetDateDifference(this->date_of_start) > 0)
			return TripStatus::PURCHASED;
		
		else if ((GetDateDifference(this->date_of_start) <= 0) && (GetDateDifference(this->date_of_end) >=0 ))
			return TripStatus::USING;
		
		else if (GetDateDifference(this->date_of_end) < 0)
			return TripStatus::USED;
	}
}


std::string Trip::GetNameOfCustomer(){
	return this->name_of_customer;
}

std::string Trip::GetNameOfManager(){
	return this->name_of_manager;
}

void Trip::SetDataOfPurchase(std::string name_of_manager, std::string name_of_customer)
{
	this->name_of_manager = name_of_manager;
	this->name_of_customer = name_of_customer;
	
	std::time_t mytime = std::time(NULL);
	std::tm now;
	gmtime_s(&now, &mytime);

	this->date_of_booking = "";
	if (now.tm_mday < 10) 
		this->date_of_booking += "0" + std::to_string(now.tm_mday) + "/";
	else
		this->date_of_booking +=  std::to_string(now.tm_mday) + "/";

	if ((now.tm_mon + 1) < 10)
		this->date_of_booking += "0" + std::to_string(now.tm_mon + 1) + "/";
	else
		this->date_of_booking += std::to_string(now.tm_mon + 1) + "/";

	this->date_of_booking += std::to_string(now.tm_year + 1900);
}



double Trip::GetAveragePrice() {
	return total_price / static_cast<double>(Identifiers.size());
}


double Trip::GetAverageDuration() {
	return static_cast<double>(total_duration) / static_cast<double>(Identifiers.size());
}



void Trip::Return(){
	date_of_booking = "-";
	name_of_customer = "-";
	name_of_manager = "-";
}



// Рахує різницю між двома датами формату "dd/mm/yyyy"

int Trip::GetDateDifference(const std::string firstDate, const std::string secondDate)
{

	std::time_t mytime = std::time(NULL);
	std::tm now;
	gmtime_s(&now, &mytime);


	int day_1, month_1, year_1, day_2, month_2, year_2;

	std::tm time_1 = {}; 
	std::tm time_2 = {}; 
	std::time_t tt;


	if (secondDate == "today") {

		std::time_t mytime = std::time(NULL);
		std::tm now;
		gmtime_s(&now, &mytime);
		

		day_1 = now.tm_mday;
		month_1 = now.tm_mon + 1;
		year_1 = now.tm_year + 1900;

		time_1.tm_year = year_1 - 1900; 
		time_1.tm_mon = month_1 - 1;  
		time_1.tm_mday = day_1;


		day_2 = std::stoi(firstDate.substr(0, 2));
		month_2 = std::stoi(firstDate.substr(3, 2));
		year_2 = std::stoi(firstDate.substr(6, 4));

		time_2.tm_year = year_2 - 1900; 
		time_2.tm_mon = month_2 - 1; 
		time_2.tm_mday = day_2;


		tt = std::mktime(&time_1);
		int days_1 = static_cast<int>(tt / (60 * 60 * 24)); 

		tt = std::mktime(&time_2);
		int days_2 = static_cast<int>(tt / (60 * 60 * 24)); 

		return days_2 - days_1;

	}

	else 	
	{
		day_1 = std::stoi(firstDate.substr(0, 2));
		month_1 = std::stoi(firstDate.substr(3, 2));
		year_1 = std::stoi(firstDate.substr(6, 4));

		day_2 = std::stoi(secondDate.substr(0, 2));
		month_2 = std::stoi(secondDate.substr(3, 2));
		year_2 = std::stoi(secondDate.substr(6, 4));

		time_1.tm_year = year_1 - 1900; 
		time_1.tm_mon = month_1 - 1; 
		time_1.tm_mday = day_1;

		time_2.tm_year = year_2 - 1900;
		time_2.tm_mon = month_2 - 1;
		time_2.tm_mday = day_2;

		tt = std::mktime(&time_1);
		int days_1 = static_cast<int>(tt / (60 * 60 * 24));

		tt = std::mktime(&time_2);
		int days_2 = static_cast<int>(tt / (60 * 60 * 24));

		return days_2 - days_1;
	}

}
