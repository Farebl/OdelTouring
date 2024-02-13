#include "Functions.h"

// Структура, для опису об'єкту "Замовлення"
struct Order {
	int year_of_booking; // дата придбання путівки
	std::string country;// ім'я клієнта, який придбав цю путівку
	std::string name_of_trip;// ім'я клієнта, який придбав цю путівку
	std::string name_of_customer;// ім'я клієнта, який придбав цю путівку
	int duration; // тривалість путівки
	double price; // вартість путівки

	Order(int year_of_booking, std::string country, std::string name_of_trip, std::string name_of_customer, int duration, double price)
	{
		this->year_of_booking = year_of_booking;
		this->country = country;
		this->name_of_trip = name_of_trip;
		this->name_of_customer = name_of_customer;
		this->duration = duration;
		this->price = price;
	}
};


// Функція запуску програми
void Start(ListSharedsManager_t& Managers, ListSharedsCustomer_t& Customers, ListSharedsTrip_t& Trips)
{
	// Зчитування даних з файлів даних
    ReadManagersData(Managers, "Managers.txt");
    ReadTripsData(Trips, "Trips.txt");
    ReadCustomersData(Customers, Trips, "Customers.txt");

	// Запуск інтерфейсу
	Interface(Managers, Customers, Trips);
	
	// Запис даних у файли даних
	SaveManagersData(Managers, "Managers.txt");
	SaveTripsData(Trips, "Trips.txt");
	SaveCustomersData(Customers, "Customers.txt");
}


// Функція виклику інтерфейса користувача
void Interface(ListSharedsManager_t& Managers, ListSharedsCustomer_t& Customers, ListSharedsTrip_t& Trips,
	std::string ManagersDataPath,
	std::string CustomersDataPath,
	std::string TripsDataPath,
	std::string OrdersPath,
	std::string HistoryDataPath)
{
	size_t managerIndex = 0, customerIndex = 0, tripIndex = 0, fieldIndex = 0; // змінні, для збереження індексів обраних об'єіквт
	int menuItem = 0; // змінні, для збереження індексів обраного пункту меню
	int index = 0; // змінні, для збереження індексу

	std::time_t mytime = std::time(NULL);
	std::tm now = {};
	int current_year = 0; // поточний рік
	int year = 0; // змінні, для збереження введеного року

	bool try_again = false; // змінні, для перевірки, чи бажає елієнт ввести нове значення індексу
	
	// змінні, для збереження вданих, при створенні або редагуванні об'єктів класів
	std::string customer_name, customer_phone_number = "-", customer_address = "-", value = "-", name = "-", phone_number = "-", address = "-", country = "-", date_of_start = "-", date_of_end = "-", city = "-";
	double price = 0;
	int id = 0;
	
	// змінні для взаємодії з обраним об'єтом
	auto manager = Managers.begin(); 
	auto customer = Customers.begin();
	auto trip = Trips.begin();

	// змінні, для збереження шляхів, до файлів даних
	std::string managersDataPath = ManagersDataPath; // шлях до фалйу, куди зберігаються данні про менеджерів
	std::string customersDataPath = CustomersDataPath; // шлях до фалйу, куди зберігаються данні про клієнтів
	std::string tripsDataPath = TripsDataPath; // шлях до фалйу, куди зберігаються данні про путівки
	std::string ordersPath = OrdersPath; // шлях до фалйу, куди зберігаються данні про замовлення
	std::string historyDataPath = HistoryDataPath; // шлях до фалйу, куди зберігаються данні про історію дій

MAIN:
	std::cout << "\n\n|--- Main menu ---|\n";
	std::cout << "\n1) Managers ";
	std::cout << "\n2) Customers ";
	std::cout << "\n3) Trips";
	std::cout << "\n4) Close the program";

	std::cout << "\n\nEnter item number: ";
	ValidatedInput(menuItem);
	switch (menuItem) {
	case 1: // case 1: Managers
		ClearConsole();
	MANAGERS:
		std::cout << "\n\n|--- Managers ---|\n";
		std::cout << "\n1) Information"; 
		std::cout << "\n2) Orders";
		std::cout << "\n3) Add new manager";
		std::cout << "\n4) Remove manager";
		std::cout << "\n5) Back to the main menu";
		std::cout << "\n6) Close the program";

		std::cout << "\n\nEnter item number: ";
		ValidatedInput(menuItem);
		switch (menuItem) {
		case 1: // case 1: Information
			ClearConsole();
		MANAGERS_INFORMATION:
			std::cout << "\n\n|--- Information about managers ---|\n";
			std::cout << "\n1) List / full information / edit information";
			std::cout << "\n2) Count of managers";
			std::cout << "\n3) Back to \"Managers\"";
			std::cout << "\n4) Go to \"Main menu\"";
			std::cout << "\n5) Close the program";

			std::cout << "\n\nEnter item number: ";
			ValidatedInput(menuItem);
			switch (menuItem) {
			case 1: // case 1: List of managers (full info/edit)
				ClearConsole();
			MANAGERS_LIST:
				std::cout << "\n\n|--- Managers list / full information / edit information ---|\n";

				if (Managers.empty()) {
					while (true) {
						std::cout << "\n\nUnfortunately, there are no managers";
						std::cout << "\n1) Add new manager";
						std::cout << "\n2) Go to the \"Main menu\"";
						std::cout << "\n3) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto ADD_NEW_MANAGER;
							break;
						case 2:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 3:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
								ClearConsole();
								std::cout << "\n\n|--- Managers list / full information / edit information ---|\n";
								continue;
								break;
							}
							break; //кінець case 3: Are you sure you want to close the program?
						}
					}
				} // кінець if (Managers.empty())

				std::cout << "\nManagers: \n";
				ShowListOfCollectionElementNames(Managers);

				std::cout << "\n1) Show full information about the manager";
				std::cout << "\n2) Edit information about the manager";
				std::cout << "\n3) Back to \"Managers\"";
				std::cout << "\n4) Go to \"Main menu\"";
				std::cout << "\n5) Close the program";

				std::cout << "\n\nEnter item number: ";
				ValidatedInput(menuItem);
				switch (menuItem) {
				case 1: // case 1: Show full information about the manager
					ClearConsole();
				FULL_INFORMATION_ABOUT_THE_MANAGER:

					std::cout << "\n\n|--- Full information about the manager ---|\n";

					std::cout << "\nManagers: \n";
					ShowListOfCollectionElementNames(Managers);

					std::cout << "\n\nSelect the number of the manager you want to see full information about: ";
					ValidatedInput(managerIndex);

					if (managerIndex < 1 || managerIndex > Managers.size()) {
						while (true) {
							std::cout << "\n\nThere is no manager with such a serial number.";
							std::cout << "\n1) Try again";
							std::cout << "\n2) Back to \"Managers list \\ full information \\ edit information";
							std::cout << "\n3) Go to \"Information about managers\"";
							std::cout << "\n4) Go to \"Main menu\"";
							std::cout << "\n5) Close the program";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								ClearConsole();
								goto FULL_INFORMATION_ABOUT_THE_MANAGER;
								break;
							case 2:
								ClearConsole();
								goto MANAGERS_LIST;
								break;
							case 3:
								ClearConsole();
								goto MANAGERS_INFORMATION;
								break;
							case 4:
							default:
								ClearConsole();
								goto MAIN;
								break;
							case 5:
								std::cout << "\n\nAre you sure you want to close the program?";
								std::cout << "\n1) Yes";
								std::cout << "\n2) No";

								std::cout << "\n\nEnter item number: ";
								ValidatedInput(menuItem);
								switch (menuItem) {
								case 1: return; break;
								case 2:
								default:
									ClearConsole();
									std::cout << "\n\n|--- Full information about the manager ---|\n";
									continue;
									break;
								}
								break; //кінець case 5: Are you sure you want to close the program?
							}
						} //кінець while (true) 
					}//кінець if (managerIndex < 1 || managerIndex > Managers.size()) 

					manager = Managers.begin();
					std::advance(manager, managerIndex - 1);

					ClearConsole();
					std::cout << "\n\n|--- Full information about the manager ---|\n";
					(*manager)->ShowInfo();

					while (true) {
						std::cout << "\n\n1) See detailed information about another manager";
						std::cout << "\n2) Back to \"Managers list / full information / edit information";
						std::cout << "\n3) Go to \"Information about managers\"";
						std::cout << "\n4) Go to \"Main menu\"";
						std::cout << "\n5) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto FULL_INFORMATION_ABOUT_THE_MANAGER;
							break;
						case 2:
							ClearConsole();
							goto MANAGERS_LIST;
							break;
						case 3:
							ClearConsole();
							goto MANAGERS_INFORMATION;
							break;
						case 4:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 5:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								return;
								break;
							case 2:
							default:
								ClearConsole();
								std::cout << "\n\n|--- Full information about the manager ---|\n";
								continue;
								break;
							}
							break; //кінець case 4: Are you sure you want to close the program?
						}
					}// кінець while (true) у DETAILED_INFORMATION_ABOUT_MANAGER:

					break; // кінець case 1: Show full information about the manager

				case 2: // Edit information about the manager
					ClearConsole();
				EDIT_INFORMATION_ABOUT_THE_MANAGER:

					std::cout << "\n\n|--- Edit information about the manager ---|\n";

					std::cout << "\nManagers: \n";
					ShowListOfCollectionElementNames(Managers);

					std::cout << "\n\nSelect the number of the manager, whose information you want to edit: ";
					ValidatedInput(managerIndex);

					if (managerIndex < 1 || managerIndex > Managers.size()) {
						while (true) {
							std::cout << "\n\nThere is no manager with such a serial number";
							std::cout << "\n1) Try again";
							std::cout << "\n2) Back to \"Managers list/ full information / edit information";
							std::cout << "\n3) Go to \"Information about managers\"";
							std::cout << "\n4) Go to \"Main menu\"";
							std::cout << "\n5) Close the program";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								ClearConsole();
								goto EDIT_INFORMATION_ABOUT_THE_MANAGER;
								break;
							case 2:
								ClearConsole();
								goto MANAGERS_LIST;
								break;
							case 3:
								ClearConsole();
								goto MANAGERS_INFORMATION;
								break;
							case 4:
							default:
								ClearConsole();
								goto MAIN;
								break;
							case 5:
								std::cout << "\n\nAre you sure you want to close the program?";
								std::cout << "\n1) Yes";
								std::cout << "\n2) No";

								std::cout << "\n\nEnter item number: ";
								ValidatedInput(menuItem);
								switch (menuItem) {
								case 1: return; break;
								case 2:
								default:
									ClearConsole();
									std::cout << "\n\n|--- Edit information about the manager ---|\n";
									continue;
									break;
								}
								break; //кінець case 5: Are you sure you want to close the program?
							}
						} //кінець while (true) 
					}//кінець if (managerIndex < 1 || managerIndex > Managers.size()) 

					manager = Managers.begin();
					std::advance(manager, managerIndex - 1);

				SELECT_ANOTHER_FIELD_OF_THE_MANAGER:

					ClearConsole();
					std::cout << "\n\n|--- Edit information about the manager ---|\n";
					ShowFullInfoForEditManager(manager);

					while (true) {
						std::cout << "\n\nSelect the number of the field, that you want to edit: ";
						ValidatedInput(fieldIndex);

						try_again = false;

						if (fieldIndex < 1 || fieldIndex > 6) {
							while (true) {
								std::cout << "\n\nThere is no field with such a serial number";
								std::cout << "\n1) Try again";
								std::cout << "\n2) Select another manager to edit";
								std::cout << "\n3) Back to \"Managers list \\ full information \\ edit information";
								std::cout << "\n4) Go to \"Information about managers\"";
								std::cout << "\n5) Go to \"Main menu\"";
								std::cout << "\n6) Close the program";

								std::cout << "\n\nEnter item number: ";
								ValidatedInput(menuItem);
								switch (menuItem) {
								case 1:
									try_again = true;
									break;
								case 2:
									ClearConsole();
									goto EDIT_INFORMATION_ABOUT_THE_MANAGER;
									break;
								case 3:
									ClearConsole();
									goto MANAGERS_LIST;
									break;
								case 4:
									ClearConsole();
									goto MANAGERS_INFORMATION;
									break;
								case 5:
								default:
									ClearConsole();
									goto MAIN;
									break;
								case 6:
									std::cout << "\n\nAre you sure you want to close the program?";
									std::cout << "\n1) Yes";
									std::cout << "\n2) No";

									std::cout << "\n\nEnter item number: ";
									ValidatedInput(menuItem);
									switch (menuItem) {
									case 1: return; break;
									case 2:
									default:
										ClearConsole();
										std::cout << "\n\n|--- Edit information about the manager ---|\n";
										continue;
										break;
									}
									break; //кінець case 6: Are you sure you want to close the program?
								}

								break;
							} //кінець if (managerIndex < 1 || managerIndex > Managers.size()) 
						}

						if (!try_again)
							break;
						
						ClearConsole();
						std::cout << "\n\n|--- Edit information about the manager ---|\n";
						ShowFullInfoForEditManager(manager);
		
					}// кінець while (true) - Select the number of the manager you want to see full information about:

					if (fieldIndex == 1){
						ClearConsole();
						std::cout << "\n\n|--- Edit information about the manager ---|\n";
						
						std::cout << "\n1) Surname: " << (*manager)->GetSecondName();
						std::cout << "\n2) Name: " << (*manager)->GetFirstName();
						std::cout << "\n3) Patronymic: " << (*manager)->GetPatronymicName();

						while (true) {
							std::cout << "\n\nSelect the number of the field, that you want to edit: ";
							ValidatedInput(fieldIndex);

							try_again = false;

							if (fieldIndex < 1 || fieldIndex > 3) {
								while (true) {
									std::cout << "\n\nThere is no field with such a serial number";
									std::cout << "\n1) Try again";
									std::cout << "\n1) Select another field of manager \"" << (*manager)->GetFullName() <<"\" to edit";
									std::cout << "\n3) Select another manager to edit";
									std::cout << "\n4) Back to \"Managers list \\ full information \\ edit information";
									std::cout << "\n5) Go to \"Information about managers\"";
									std::cout << "\n6) Go to \"Main menu\"";
									std::cout << "\n7) Close the program";

									std::cout << "\n\nEnter item number: ";
									ValidatedInput(menuItem);
									switch (menuItem) {
									case 1:
										try_again = true;
										break;
									case 2:
										ClearConsole();
										goto SELECT_ANOTHER_FIELD_OF_THE_MANAGER;
										break;
									case 3:
										ClearConsole();
										goto EDIT_INFORMATION_ABOUT_THE_MANAGER;
										break;
									case 4:
										ClearConsole();
										goto MANAGERS_LIST;
										break;
									case 5:
										ClearConsole();
										goto MANAGERS_INFORMATION;
										break;
									case 6:
									default:
										ClearConsole();
										goto MAIN;
										break;
									case 7:
										std::cout << "\n\nAre you sure you want to close the program?";
										std::cout << "\n1) Yes";
										std::cout << "\n2) No";

										std::cout << "\n\nEnter item number: ";
										ValidatedInput(menuItem);
										switch (menuItem) {
										case 1: return; break;
										case 2:
										default:
											ClearConsole();
											std::cout << "\n\n|--- Edit information about the manager ---|\n";
											continue;
											break;
										}
										break; //кінець case 7: Are you sure you want to close the program?
									}

									break;
								} //кінець if (managerIndex < 1 || managerIndex > Managers.size()) 
							}

							if (!try_again)
								break;

							ClearConsole();
							std::cout << "\n\n|--- Edit information about the manager ---|\n";

							std::cout << "\n1) Surname: " << (*manager)->GetSecondName();
							std::cout << "\n2) Name: " << (*manager)->GetFirstName();
							std::cout << "\n3) Patronymic: " << (*manager)->GetPatronymicName();


						}// кінець while (true) - Select the number of the manager you want to see full information about:

						++fieldIndex;
					}
					else 
						fieldIndex += 3;


					std::cout << "\n\nEnter a new value for selected field: ";
					ValidatedInput(value);

					EditManager(manager, fieldIndex, value);
					
					ClearConsole();
					std::cout << "\n\n|--- Edit information about the manager ---|\n";

					std::cout << "\nInformation about the manager \"" << (*manager)->GetFullName() << "\" has been edited:";
					(*manager)->ShowInfo();
					SaveMessage("Changing information about manager by id: " + std::to_string((*manager)->GetPersonalId()), historyDataPath);


					while (true) {
						std::cout << "\n\n1) Select another manager to edit";
						std::cout << "\n2) Back to \"Managers list \\ full information \\ edit information";
						std::cout << "\n3) Go to \"Information about managers\"";
						std::cout << "\n4) Go to \"Main menu\"";
						std::cout << "\n5) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto EDIT_INFORMATION_ABOUT_THE_MANAGER;
							break;
						case 2:
							ClearConsole();
							goto MANAGERS_LIST;
							break;
						case 3:
							ClearConsole();
							goto MANAGERS_INFORMATION;
							break;
						case 4:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 5:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
							default:
								ClearConsole();
								std::cout << "\n\n|--- Edit information about the manager ---|\n";
								continue;
								break;
							}
							break; //кінець case 5: Are you sure you want to close the program?
						}

					}// кінець case 2: - No - while (true) у DETAILED_INFORMATION_ABOUT_MANAGER

					break;  // кінець case 2: Edit information about the manager

				case 3: // case 3: Back to MANAGERS
					ClearConsole();
					goto MANAGERS;
					break; //кінець case 3: Back to MANAGERS

				case 4: // case 4: Back to the main menu
				default:
					ClearConsole();
					goto MAIN;
					break; //кінець case 4: Back to the main menu

				case 5: // case 5: Close the program
					ClearConsole();
					return;
					break; //кінець case 5: Close the program
				}

				break; //кінець case 1: List of managers (full info/edit)

			case 2: // case 2:  Count of managers
				ClearConsole();
			COUNT_OF_MANAGERS:
				std::cout << "\n\n|--- Count of managers ---|\n";

				if (Managers.empty()) {
					while (true) {
						std::cout << "\n\nUnfortunately, there are no managers";
						std::cout << "\n1) Add new manager";
						std::cout << "\n2) Go to the \"Main menu\"";
						std::cout << "\n3) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto ADD_NEW_MANAGER;
							break;
						case 2:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 3:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
								ClearConsole();
								std::cout << "\n\n|--- Count of managers ---|\n";
								continue;
								break;
							}
							break; //кінець case 3: Are you sure you want to close the program?
						}
					}
				} // кінець if (Managers.empty())

				std::cout << "\nTotal count of managers: " << Managers.size();

				while (true) {
					std::cout << "\n\n1) Back to \"Information about managers\"";
					std::cout << "\n2) Go to \"Main menu\"";
					std::cout << "\n3) Close the program";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						ClearConsole();
						goto MANAGERS_INFORMATION;
						break;
					case 2:
					default:
						ClearConsole();
						goto MAIN;
						break;
					case 3:
						std::cout << "\n\nAre you sure you want to close the program?";
						std::cout << "\n1) Yes";
						std::cout << "\n2) No";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1: return; break;
						case 2:
						default:
							ClearConsole();
							std::cout << "\n\n|--- Count of managers ---|\n";
							goto COUNT_OF_MANAGERS;
							break;
						}
						break; //кінець case 4: Are you sure you want to close the program?
					}

				}// кінець case 2: - No - while (true) у DETAILED_INFORMATION_ABOUT_MANAGER

				break; //кінець case 2: Count of managers

			case 3: // case 3: Back to MANAGERS
				ClearConsole();
				goto MANAGERS;
				break; //кінець case 3: Back to MANAGERS

			case 4: // case 4: Back to the main menu
			default:
				ClearConsole();
				goto MAIN;
				break; //кінець case 4: Back to the main menu

			case 5: // case 5: Close the program
				ClearConsole();
				return;
				break; //кінець case 5: Close the program
			}
		
			break; //кінець case 1: Information

		case 2: // case 2: Orders
			ClearConsole();
		MANAGER_ORDERS:
			std::cout << "\n\n|--- Orders ---|\n";
			std::cout << "\n1) Make a trip purchase";
			std::cout << "\n2) Make a trip refund";
			std::cout << "\n3) Back to \"Managers\"";
			std::cout << "\n4) Go to \"Main menu\"";
			std::cout << "\n5) Close the program";

			std::cout << "\n\nEnter item number: ";
			ValidatedInput(menuItem);
			switch (menuItem) {
			case 1: // case 1: Make a tour purchase
				ClearConsole();
			MAKE_A_TRIP_PURCAHSE:
				
				std::cout << "\n\n|--- Making a trip purchase ---|\n";
				
				if (Managers.empty()) {
					while (true) {
						std::cout << "\n\nUnfortunately, there are no managers";
						std::cout << "\n1) Add new manager";
						std::cout << "\n2) Go to the \"Main menu\"";
						std::cout << "\n3) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto ADD_NEW_MANAGER;
							break;
						case 2:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 3:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
								ClearConsole();
								std::cout << "\n\n|--- Making a trip purchase ---|\n";
								continue;
								break;
							}
							break; //кінець case 3: Are you sure you want to close the program?
						}
					}
				} // кінець if (Managers.empty())

				if (GetCountOfCustomersWithoutTrip(Customers).first == 0) {
					while (true) {
						std::cout << "\n\nUnfortunately, there are no customers who can buy a trip";
						std::cout << "\n1) Add new customer";
						std::cout << "\n2) Back to \"Orders\"";
						std::cout << "\n3) Go to \"Main menu\"";
						std::cout << "\n4) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto ADD_NEW_CUSTOMER;
							break;
						case 2:
							ClearConsole();
							goto MANAGER_ORDERS;
							break;
						case 3:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 4:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								return;
								break;
							case 2:
							default:
								ClearConsole();
								std::cout << "\n\n|--- Making a trip purchase ---|\n";
								continue;
								break;
							}

							break;  //кінець case 3: Are you sure you want to close the program?
						}
					}
				} // кінець if (GetCountOfCustomersWithoutTrip(Customers) == 0)

				if (GetCountOfUnboughtTrips(Trips).first == 0) {
					while (true) {
						std::cout << "\n\nUnfortunately, there are no trips that can be sold";
						std::cout << "\n1) Add new trip";
						std::cout << "\n2) Back to \"Orders\"";
						std::cout << "\n3) Go to \"Main menu\"";
						std::cout << "\n4) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto ADD_NEW_TRIP;
							break;
						case 2:
							ClearConsole();
							goto MANAGER_ORDERS;
							break;
						case 3:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 4:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								return;
								break;
							case 2:
							default:
								ClearConsole();
								std::cout << "\n\n|--- Making a trip purchase ---|\n";
								continue;
								break;
							}

							break;  //кінець case 4: Are you sure you want to close the program?
						}
					}
				} // кінець if (GetCountOfUnboughtTrips(Trips)  == 0)

				std::cout << "\n\nManagers: \n";
				ShowListOfCollectionElementNames(Managers);

				std::cout << "\n\nSelect the number of the manager who will process the purchase of the trip: ";
				ValidatedInput(managerIndex);

				if (managerIndex < 1 || managerIndex > Managers.size()) {
					while (true) {
						std::cout << "\n\nThere is no manager with such a serial number.";
						std::cout << "\n1) Try again";
						std::cout << "\n2) Back to \"Orders\"";
						std::cout << "\n3) Go to \"Main menu\"";
						std::cout << "\n4) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto MAKE_A_TRIP_PURCAHSE;
							break;
						case 2:
							ClearConsole();
							goto MANAGER_ORDERS;
							break;
						case 3:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 4:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
							default:
								ClearConsole();
								std::cout << "\n\n|--- Making a trip purchase ---|\n";
								continue;
								break;
							}

							break; //кінець case 4: Are you sure you want to close the program?
						}
					} //кінець while (true) 
				}//кінець if (managerIndex < 1 || managerIndex > Managers.size()) 

				manager = Managers.begin();
				std::advance(manager, managerIndex - 1);

				ClearConsole();
				std::cout << "\n\n|--- Making a trip purchase ---|\n";
				std::cout << "\n\nCustomers: \n";
				ShowListOfCustomersWithoutTripNames(Customers);
				
				while (true) {
					std::cout << "\n\nSelect the number of the customer who will purchase the trip: ";
					ValidatedInput(customerIndex);

					try_again = false;

					if (customerIndex < 1 || customerIndex > GetCountOfCustomersWithoutTrip(Customers).first) {
						while (true) {
							std::cout << "\n\nThere is no customer with such a serial number.";
							std::cout << "\n1) Try again";
							std::cout << "\n2) Back to \"Orders\"";
							std::cout << "\n3) Go to \"Main menu\"";
							std::cout << "\n4) Close the program";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								try_again = true;
								break;
							case 2:
								ClearConsole();
								goto MANAGER_ORDERS;
								break;
							case 3:
							default:
								ClearConsole();
								goto MAIN;
								break;
							case 4:
								std::cout << "\n\nAre you sure you want to close the program?";
								std::cout << "\n1) Yes";
								std::cout << "\n2) No";

								std::cout << "\n\nEnter item number: ";
								ValidatedInput(menuItem);
								switch (menuItem) {
								case 1: return; break;
								case 2:
								default:
									ClearConsole();
									std::cout << "\n\n|--- Making a trip purchase ---|\n";
									continue;
									break;
								}
								break; //кінець case 5: Are you sure you want to close the program?
							}

							break;
						} //кінець if (managerIndex < 1 || managerIndex > Managers.size()) 
					}

					if (!try_again)
						break;

					ClearConsole();
					std::cout << "\n\n|--- Making a trip purchase ---|\n";
					std::cout << "\nCustomers: \n";
					ShowListOfCustomersWithoutTripNames(Customers);

				}// кінець while (true) - Select the number of the manager you want to see full information about:

				customerIndex = GetCountOfCustomersWithoutTrip(Customers).second[customerIndex - 1];
				customer = Customers.begin();
				std::advance(customer, customerIndex);


				ClearConsole();
				std::cout << "\n\n|--- Making a trip purchase ---|\n";
				ShowListOfUnboughtTripNames(Trips);

				while (true) {
					std::cout << "\n\nSelect the number of the trip you want to sell: ";
					ValidatedInput(tripIndex);

					try_again = false;

					if (tripIndex <= 0 || tripIndex > GetCountOfUnboughtTrips(Trips).first) {
						while (true) {
							std::cout << "\n\nThere is no trip with such a serial number.";
							std::cout << "\n1) Try again";
							std::cout << "\n2) Back to \"Orders\"";
							std::cout << "\n3) Go to \"Main menu\"";
							std::cout << "\n4) Close the program";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								try_again = true;
								break;
							case 2:
								ClearConsole();
								goto MANAGER_ORDERS;
								break;
							case 3:
							default:
								ClearConsole();
								goto MAIN;
								break;
							case 4:
								std::cout << "\n\nAre you sure you want to close the program?";
								std::cout << "\n1) Yes";
								std::cout << "\n2) No";

								std::cout << "\n\nEnter item number: ";
								ValidatedInput(menuItem);
								switch (menuItem) {
								case 1: return; break;
								case 2:
								default:
									ClearConsole();
									std::cout << "\n\n|--- Making a trip purchase ---|\n";
									continue;
									break;
								}
								break; //кінець case 5: Are you sure you want to close the program?
							}
							
							break;
						} //кінець if (managerIndex < 1 || managerIndex > Managers.size()) 
					}

					if (!try_again)
						break;

					ClearConsole();
					std::cout << "\n\n|--- Making a trip purchase ---|\n";
					std::cout << "\nTrips: \n";
					ShowListOfUnboughtTripNames(Trips);

				}// кінець while (true) - Select the number of the manager you want to see full information about:
				
				tripIndex = GetCountOfUnboughtTrips(Trips).second[tripIndex - 1];
				trip = Trips.begin();
				std::advance(trip, tripIndex);

				(*manager)->SaleTheTrip(*customer, *trip);
				
				std::cout << "\n\nManager " << (*manager)->GetFullName() << " sold to client " << (*customer)->GetFullName() << ", tour " << (*trip)->GetFullName() << ";\n";
				
				SaveMessage("Manager " + (*manager)->GetFullName() + " sold to client " + (*customer)->GetFullName() + ", tour " + (*trip)->GetFullName(), historyDataPath);

				while (true) {
					std::cout << "\n\n1) Make a new purchase";
					std::cout << "\n2) Back to \"Orders\"";
					std::cout << "\n3) Go to \"Main menu\"";
					std::cout << "\n4) Close the program";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						ClearConsole();
						goto MAKE_A_TRIP_PURCAHSE;
						break;
					case 2:
						ClearConsole();
						goto MANAGER_ORDERS;
						break;
					case 3:
					default:
						ClearConsole();
						goto MAIN;
						break;
					case 4:
						std::cout << "\n\nAre you sure you want to close the program?";
						std::cout << "\n1) Yes";
						std::cout << "\n2) No";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							return;
							break;
						case 2:
						default:
							ClearConsole();
							std::cout << "\n\n|--- Making a trip purchase ---|\n";
							continue;
							break;
						}
						break;  //кінець case 4: Are you sure you want to close the program?
					}
				}// кінець while(true)

				break;//кінець case 1:  Make a tour purchase

			case 2: // case 2: Make a tour refund
				ClearConsole();
			MAKE_A_TRIP_REFOUND: 

				std::cout << "\n\n|--- Making a trip refound ---|\n";

				if (Managers.empty()) {
					while (true) {
						std::cout << "\n\nUnfortunately, there are no managers";
						std::cout << "\n1) Add new manager";
						std::cout << "\n2) Go to the \"Main menu\"";
						std::cout << "\n3) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto ADD_NEW_MANAGER;
							break;
						case 2:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 3:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
								ClearConsole();
								std::cout << "\n\n|--- Making a trip refound ---|\n";
								continue;
								break;
							}

							break; //кінець case 3: Are you sure you want to close the program?
						}
					}
				} // кінець if (Managers.empty())
				if (GetCountOfCustomersWithTrip(Customers).first == 0) {
					while (true) {
						std::cout << "\n\nUnfortunately, there are no customers who can return a trip.";
						std::cout << "\n1) Back to \"Orders\"";
						std::cout << "\n2) Go to \"Main menu\"";
						std::cout << "\n3) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto MANAGER_ORDERS;;
							break;
						case 2:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 3:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								return;
								break;
							case 2:
							default:
								std::cout << "\n\n|--- Making a trip refound ---|\n";
								continue;
								break;
							}

							break;  //кінець case 3: Are you sure you want to close the program?
						}
					}
				} // кінець if (GetCountOfCustomersWithTrip(Customers) == 0)

				std::cout << "\n\nManagers: \n";
				ShowListOfCollectionElementNames(Managers);
				
				std::cout << "\n\nSelect the number of the manager who will process the refound of the trip: ";
				ValidatedInput(managerIndex);

				if (managerIndex < 1 || managerIndex > Managers.size()) {
					while (true) {
						std::cout << "\n\nThere is no manager with such a serial number.";
						std::cout << "\n1) Try again";
						std::cout << "\n2) Back to \"Orders\"";
						std::cout << "\n3) Go to \"Main menu\"";
						std::cout << "\n4) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto MAKE_A_TRIP_REFOUND;
							break;
						case 2:
							ClearConsole();
							goto MANAGER_ORDERS;
							break;
						case 3:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 4:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
							default:
								ClearConsole();
								std::cout << "\n\n|--- Making a trip refound ---|\n";
								continue;
								break;
							}
							break; //кінець case 4: Are you sure you want to close the program?
						}
					} //кінець while (true) 
				}//кінець if (managerIndex < 1 || managerIndex > Managers.size()) 
				
				manager = Managers.begin();
				std::advance(manager, managerIndex - 1);

				ClearConsole();
				std::cout << "\n\nCustomers: \n";
				ShowListOfCustomersWithTripNames(Customers);

				while (true) {
					std::cout << "\n\nSelect the number of the customer who want to return the trip: ";
					ValidatedInput(customerIndex);

					try_again = false;

					if (customerIndex <= 0 || customerIndex > GetCountOfCustomersWithTrip(Customers).first) {
						while (true) {
							std::cout << "\n\nThere is no customer with such a serial number.";
							std::cout << "\n1) Try again";
							std::cout << "\n2) Back to \"Orders\"";
							std::cout << "\n3) Go to \"Main menu\"";
							std::cout << "\n4) Close the program";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								try_again = true;
								break;
							case 2:
								ClearConsole();
								goto MANAGER_ORDERS;
								break;
							case 3:
							default:
								ClearConsole();
								goto MAIN;
								break;
							case 4:
								std::cout << "\n\nAre you sure you want to close the program?";
								std::cout << "\n1) Yes";
								std::cout << "\n2) No";

								std::cout << "\n\nEnter item number: ";
								ValidatedInput(menuItem);
								switch (menuItem) {
								case 1: return; break;
								case 2:
								default:
									ClearConsole();
									std::cout << "\n\n|--- Making a trip refound ---|\n";
									continue;
									break;
								}
								break; //кінець case 5: Are you sure you want to close the program?
							}

							break;
						} //кінець if (managerIndex < 1 || managerIndex > Managers.size()) 
					}

					if (!try_again)
						break;

					ClearConsole();
					std::cout << "\n\n|--- Making a trip refound ---|\n";
					std::cout << "\nCustomers: \n";
					ShowListOfCustomersWithTripNames(Customers);

				}// кінець while (true) - Select the number of the manager you want to see full information about:
			
				customerIndex = GetCountOfCustomersWithTrip(Customers).second[customerIndex - 1];
				customer = Customers.begin();
				std::advance(customer, customerIndex);

				//назва путівки
				name = (*customer)->GetTrip()->GetFullName();
				
				(*manager)->ReturnTheTrip(*customer);

				std::cout << "\n\nManager " << (*manager)->GetFullName() << " made a refound for client " << (*customer)->GetFullName() << ", tour \"" << name << "\"\n";
				
				SaveMessage("Manager " + (*manager)->GetFullName() + " made a refound for client " + (*customer)->GetFullName() + ", tour \"" + name + "\"", historyDataPath);

				while (true) {
					std::cout << "\n\n1) Make a new refound";
					std::cout << "\n2) Back to \"Orders\"";
					std::cout << "\n3) Go to \"Main menu\"";
					std::cout << "\n4) Close the program";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						ClearConsole();
						goto MAKE_A_TRIP_REFOUND;
						break;
					case 2:
						ClearConsole();
						goto MANAGER_ORDERS;
						break;
					case 3:
					default:
						ClearConsole();
						goto MAIN;
						break;
					case 4:
						std::cout << "\n\nAre you sure you want to close the program?";
						std::cout << "\n1) Yes";
						std::cout << "\n2) No";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							return;
							break;
						case 2:
						default:
							ClearConsole();
							std::cout << "\n\n|--- Making a trip refound ---|\n";
							continue;
							break;
						}

						break;  //кінець case 4: Are you sure you want to close the program?
					}
				}// кінець while(true)

				break;//кінець case 1:  Make a tour refund

			case 3: // case 3: Back to MANAGERS
				ClearConsole();
				goto MANAGERS;
				break; //кінець case 3: Back to MANAGERS

			case 4: // case 4: Back to the main menu
			default:
				ClearConsole();
				goto MAIN;
				break; //кінець case 4: Back to the main menu

			case 5: // case 5: Close the program
				ClearConsole();
				return;
				break; //кінець case 5: Close the program
			}

			break; //кінець case 2: Orders

		case 3: // case 3: Add new manager
			ClearConsole();
		ADD_NEW_MANAGER:
			
			Managers.emplace_back(std::shared_ptr<Manager>(std::make_shared<Manager>()));
			
			std::cout << "\n\n|--- Add new manager ---|\n";

			std::cout << "\nEnter manager`s name: ";
			std::getline(std::cin, name);
			Managers.back()->SetFullName(name);

			std::cout << "\nEnter manager`s phone number (format: +380XXXXXXXXX): ";
			std::getline(std::cin, phone_number);
			Managers.back()->SetPhoneNumber(phone_number);

			std::cout << "\n\nManager by name\"" << Managers.back()->GetFullName() << "\" was added.\nHis/Her id: " << Managers.back()->GetPersonalId() << "\n";
			
			SaveMessage("Manager by name \"" + Managers.back()->GetFullName() + "\" was added. His/Her id: " + std::to_string(Managers.back()->GetPersonalId()), historyDataPath);

			while (true) {
				std::cout << "\n\n1) Add new manager";
				std::cout << "\n2) Back to \"Managers\"";
				std::cout << "\n3) Go to \"Main menu\"";
				std::cout << "\n4) Close the program";

				std::cout << "\n\nEnter item number: ";
				ValidatedInput(menuItem);
				switch (menuItem) {
				case 1:
					ClearConsole();
					goto ADD_NEW_MANAGER;
					break;
				case 2:
					ClearConsole();
					goto MANAGERS;
					break;
				case 3:
				default:
					ClearConsole();
					goto MAIN;
					break;
				case 4:
					std::cout << "\n\nAre you sure you want to close the program?";
					std::cout << "\n1) Yes";
					std::cout << "\n2) No";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						return;
						break;
					case 2:
					default:
						ClearConsole();
						std::cout << "\n\n|--- Add new manager ---|\n";
						continue;
						break;
					}

					break;  //кінець case 4: Are you sure you want to close the program?
				}
			}// кінець while(true)

			break; //кінець case 3: Add new manager
		
		case 4: // case 4: Remove manager
			ClearConsole();
		REMOVE_MANAGER:

			std::cout << "\n\n|--- Remove manager ---|\n";

			if (Managers.empty()) {
				while (true) {
					std::cout << "\n\nUnfortunately, there are no managers. There is no one to delete";
					std::cout << "\n1) Back to \"Managers\"";
					std::cout << "\n2) Go to the \"Main menu\"";
					std::cout << "\n3) Close the program";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						ClearConsole();
						goto MANAGERS;
						break;
					case 2:
					default:
						ClearConsole();
						goto MAIN;
						break;
					case 3:
						std::cout << "\n\nAre you sure you want to close the program?";
						std::cout << "\n1) Yes";
						std::cout << "\n2) No";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1: return; break;
						case 2:
							ClearConsole();
							std::cout << "\n\n|--- Remove manager ---|\n";
							continue;
							break;
						}
						break; //кінець case 3: Are you sure you want to close the program?
					}
				}
			} // кінець if (Managers.empty())

			std::cout << "\nManagers: \n";
			ShowListOfCollectionElementNames(Managers);

			std::cout << "\n\nSelect the number of the manager you want to remove: ";
			ValidatedInput(managerIndex);

			if (managerIndex < 1 || managerIndex > Managers.size()) {
				while (true) {
					std::cout << "\n\nThere is no manager with such a serial number.";
					std::cout << "\n1) Try again";
					std::cout << "\n2) Back to \"Managers\"";
					std::cout << "\n3) Go to \"Main menu\"";
					std::cout << "\n4) Close the program";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						ClearConsole();
						goto REMOVE_MANAGER;
						break;
					case 2:
						ClearConsole();
						goto MANAGERS;
						break;
					case 3:
					default:
						ClearConsole();
						goto MAIN;
						break;
					case 4:
						std::cout << "\n\nAre you sure you want to close the program?";
						std::cout << "\n1) Yes";
						std::cout << "\n2) No";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1: return; break;
						case 2:
						default:
							ClearConsole();
							std::cout << "\n\n|--- Remove manager ---|\n";
							continue;
							break;
						}
						break; //кінець case 4: Are you sure you want to close the program?
					}
				} //кінець while (true) 
			}//кінець if (managerIndex < 1 || managerIndex > Managers.size()) 

			manager = Managers.begin();
			std::advance(manager, managerIndex - 1);

			name = (*manager)->GetFullName();
			id = (*manager)->GetPersonalId();

			Managers.remove(*manager);
			std::cout << "\nManager \"" << name << "\" has been removed.";

			SaveMessage("Manager by name \"" + name + "\" has been removed." + " His/Her id : " + std::to_string(id), historyDataPath);
			
			while (true) {
				std::cout << "\n\n1) Remove another manager";
				std::cout << "\n2) Back to \"Managers\"";
				std::cout << "\n3) Go to \"Main menu\"";
				std::cout << "\n4) Close the program";

				std::cout << "\n\nEnter item number: ";
				ValidatedInput(menuItem);
				switch (menuItem) {
				case 1:
					ClearConsole();
					goto REMOVE_MANAGER;
					break;
				case 2:
					ClearConsole();
					goto MANAGERS;
					break;
				case 3:
				default:
					ClearConsole();
					goto MAIN;
					break;
				case 4:
					std::cout << "\n\nAre you sure you want to close the program?";
					std::cout << "\n1) Yes";
					std::cout << "\n2) No";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						return;
						break;
					case 2:
					default:
						ClearConsole();
						std::cout << "\n\n|--- Remove manager ---|\n";
						continue;
						break;
					}

					break;  //кінець case 4: Are you sure you want to close the program?
				}
			}// кінець while(true)

			break; //кінець  case 4: Remove manager

		case 5: // case 5: Back to the main menu
		default:
			ClearConsole();
			goto MAIN;
			break; //кінець case 5: Back to the main menu

		case 6: // case 5: Close the program
			ClearConsole();
			return;
			break; //кінець case 5: Close the program
		}

		break; //кінець case 1: Managers

	case 2: // case 2: Customers
		ClearConsole();
	CUSTOMERS:
		std::cout << "\n\n|--- Customers ---|\n";
		std::cout << "\n1) Information";
		std::cout << "\n2) Add new customer";
		std::cout << "\n3) Remove customer";
		std::cout << "\n4) Back to \"Main menu\"";
		std::cout << "\n5) Close the program";

		std::cout << "\n\nEnter item number: ";
		ValidatedInput(menuItem);
		switch (menuItem) {
		case 1: // case 1: Information
			ClearConsole();
		CUSTOMERS_INFORMATION:
			
			std::cout << "\n\n|--- Information about customers ---|\n";
			std::cout << "\n1) List / full information / edit information";
			std::cout << "\n2) List of customers by trip`s country";
			std::cout << "\n3) Count of customers";
			std::cout << "\n4) Back to \"Customers\"";
			std::cout << "\n5) Go to \"Main menu\"";
			std::cout << "\n6) Close the program";

			std::cout << "\n\nEnter item number: ";
			ValidatedInput(menuItem);
			switch (menuItem) {
			case 1: // case 1: List of customers (full info/edit/country)
				ClearConsole();
			CUSTOMERS_LIST:
				std::cout << "\n\n|--- Customers list / full information / edit information ---|\n";

				if (Customers.empty()) {
					while (true) {
						std::cout << "\n\nUnfortunately, there are no customers";
						std::cout << "\n1) Add new customers";
						std::cout << "\n2) Go to the \"Main menu\"";
						std::cout << "\n3) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto ADD_NEW_CUSTOMER;
							break;
						case 2:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 3:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
								ClearConsole();
								std::cout << "\n\n|--- List / full information / edit information ---|\n";
								continue;
								break;
							}
							break; //кінець case 3: Are you sure you want to close the program?
						}
					}
				} // кінець if (Customers.empty())

				std::cout << "\nCustomers: \n";
				ShowListOfCollectionElementNames(Customers);

				std::cout << "\n1) Show full information about the customer";
				std::cout << "\n2) Edit information about the customer";
				std::cout << "\n3) Back to \"Information about customers\"";
				std::cout << "\n4) Go to \"Main menu\"";
				std::cout << "\n5) Close the program";

				std::cout << "\n\nEnter item number: ";
				ValidatedInput(menuItem);
				switch (menuItem) {
				case 1: // case 1: Show full information about the customer
					ClearConsole();
				FULL_INFORMATION_ABOUT_THE_CUSTOMER:

					std::cout << "\n\n|--- Full information about the customer ---|\n";

					std::cout << "\nCustomers: \n";
					ShowListOfCollectionElementNames(Customers);

					std::cout << "\n\nSelect the number of the customer you want to see full information about: ";
					ValidatedInput(customerIndex);

					if (customerIndex < 1 || customerIndex > Customers.size()) {
						while (true) {
							std::cout << "\n\nThere is no customer with such a serial number.";
							std::cout << "\n1) Try again";
							std::cout << "\n2) Back to \"Customers list / full information / edit information";
							std::cout << "\n3) Go to \"Information about customers\"";
							std::cout << "\n4) Go to \"Main menu\"";
							std::cout << "\n5) Close the program";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								ClearConsole();
								goto FULL_INFORMATION_ABOUT_THE_CUSTOMER;
								break;
							case 2:
								ClearConsole();
								goto CUSTOMERS_LIST;
								break;
							case 3:
								ClearConsole();
								goto CUSTOMERS_INFORMATION;
								break;
							case 4:
							default:
								ClearConsole();
								goto MAIN;
								break;
							case 5:
								std::cout << "\n\nAre you sure you want to close the program?";
								std::cout << "\n1) Yes";
								std::cout << "\n2) No";

								std::cout << "\n\nEnter item number: ";
								ValidatedInput(menuItem);
								switch (menuItem) {
								case 1: return; break;
								case 2:
								default:
									ClearConsole();
									std::cout << "\n\n|--- Full information about the customer ---|\n";
									continue;
									break;
								}
								break; //кінець case 5: Are you sure you want to close the program?
							}
						} //кінець while (true) 
					}//кінець if (customerIndex < 1 || customerIndex > Customers.size()) 

					customer = Customers.begin();
					std::advance(customer, customerIndex - 1);

					ClearConsole();
					(*customer)->ShowInfo();

					while (true) {
						std::cout << "\n\n1) See detailed information about another customer";
						std::cout << "\n2) Back to \"Customers list / full information / edit information";
						std::cout << "\n3) Go to \"Information about customers\"";
						std::cout << "\n4) Go to \"Main menu\"";
						std::cout << "\n5) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto FULL_INFORMATION_ABOUT_THE_CUSTOMER;
							break;
						case 2:
							ClearConsole();
							goto CUSTOMERS_LIST;
							break;
						case 3:
							ClearConsole();
							goto CUSTOMERS_INFORMATION;
							break;
						case 4:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 5:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								return;
								break;
							case 2:
							default:
								ClearConsole();
								std::cout << "\n\n|--- Full information about the customer ---|\n";
								continue;
								break;
							}
							break; //кінець case 4: Are you sure you want to close the program?
						}
					}// кінець while (true) у DETAILED_INFORMATION_ABOUT_MANAGER:

					break; // кінець case 1: Show full information about the customer

				case 2: // Edit information about the customer

					ClearConsole();
				EDIT_INFORMATION_ABOUT_THE_CUSTOMER:

					std::cout << "\n\n|--- Edit information about the customer ---|\n";
					std::cout << "\nCustomer: \n";

					ShowListOfCustomersWithoutTripNames(Customers);

					std::cout << "\n\nSelect the number of the customer, whose information you want to edit: ";
					ValidatedInput(customerIndex);

					if (customerIndex < 1 || customerIndex > GetCountOfCustomersWithoutTrip(Customers).first) {
						while (true) {
							std::cout << "\n\nThere is no customer with such a serial number";
							std::cout << "\n1) Try again";
							std::cout << "\n2) Back to \"Customers list / full information / edit information";
							std::cout << "\n3) Go to \"Information about customers\"";
							std::cout << "\n4) Go to \"Main menu\"";
							std::cout << "\n5) Close the program";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								ClearConsole();
								goto EDIT_INFORMATION_ABOUT_THE_CUSTOMER;
								break;
							case 2:
								ClearConsole();
								goto CUSTOMERS_LIST;
								break;
							case 3:
								ClearConsole();
								goto CUSTOMERS_INFORMATION;
								break;
							case 4:
							default:
								ClearConsole();
								goto MAIN;
								break;
							case 5:
								std::cout << "\n\nAre you sure you want to close the program?";
								std::cout << "\n1) Yes";
								std::cout << "\n2) No";

								std::cout << "\n\nEnter item number: ";
								ValidatedInput(menuItem);
								switch (menuItem) {
								case 1: return; break;
								case 2:
								default:
									ClearConsole();
									std::cout << "\n\n|--- Edit information about the customer ---|\n";
									continue;
									break;
								}
								break; //кінець case 5: Are you sure you want to close the program?
							}
						} //кінець while (true) 
					}//кінець if (customerIndex < 1 || customerIndex > Customers.size())

					customerIndex = GetCountOfCustomersWithoutTrip(Customers).second[customerIndex - 1];
					customer = Customers.begin();
					std::advance(customer, customerIndex);

				SELECT_ANOTHER_FIELD_OF_THE_CUSTOMER:

					ClearConsole();
					std::cout << "\n\n|--- Edit information about the customer ---|\n";
					ShowFullInfoForEditCustomer(customer);

					while (true) {
						std::cout << "\n\nSelect the number of the field, that you want to edit: ";
						ValidatedInput(fieldIndex);

						try_again = false;

						if (fieldIndex < 1 || fieldIndex > 6) {
							while (true) {
								std::cout << "\n\nThere is no field with such a serial number";
								std::cout << "\n1) Try again";
								std::cout << "\n2) Select another customer to edit";
								std::cout << "\n3) Back to \"Customers list \\ full information \\ edit information";
								std::cout << "\n4) Go to \"Information about customers\"";
								std::cout << "\n5) Go to \"Main menu\"";
								std::cout << "\n6) Close the program";

								std::cout << "\n\nEnter item number: ";
								ValidatedInput(menuItem);
								switch (menuItem) {
								case 1:
									try_again = true;
									break;
								case 2:
									ClearConsole();
									goto EDIT_INFORMATION_ABOUT_THE_CUSTOMER;
									break;
								case 3:
									ClearConsole();
									goto CUSTOMERS_LIST;
									break;
								case 4:
									ClearConsole();
									goto CUSTOMERS_INFORMATION;
									break;
								case 5:
								default:
									ClearConsole();
									goto MAIN;
									break;
								case 6:
									std::cout << "\n\nAre you sure you want to close the program?";
									std::cout << "\n1) Yes";
									std::cout << "\n2) No";

									std::cout << "\n\nEnter item number: ";
									ValidatedInput(menuItem);
									switch (menuItem) {
									case 1: return; break;
									case 2:
									default:
										ClearConsole();
										std::cout << "\n\n|--- Edit information about the customer ---|\n";
										continue;
										break;
									}
									break; //кінець case 5: Are you sure you want to close the program?
								}
						
								break;
							} //кінець if (fieldIndex < 1 || fieldIndex > 4)
						}

						if (!try_again)
							break;

						ClearConsole();
						std::cout << "\n\n|--- Edit information about the customer ---|\n";
						ShowFullInfoForEditCustomer(customer);

					}// кінець while (true) - Select the number of the field, that you want to edit: :

					if (fieldIndex == 1) {
						ClearConsole();
						std::cout << "\n\n|--- Edit information about the customer ---|\n";

						std::cout << "\nSurname: " << (*customer)->GetSecondName();
						std::cout << "\nName: " << (*customer)->GetFirstName();
						std::cout << "\nPatronymic: " << (*customer)->GetPatronymicName();


						while (true) {
							std::cout << "\n\nSelect the number of the field, that you want to edit: ";
							ValidatedInput(fieldIndex);

							try_again = false;

							if (fieldIndex < 1 || fieldIndex > 3) {
								while (true) {
									std::cout << "\n\nThere is no field with such a serial number";
									std::cout << "\n1) Try again";
									std::cout << "\n1) Select another field of customer \"" << (*customer)->GetFullName() << "\" to edit";
									std::cout << "\n3) Select another customer to edit";
									std::cout << "\n4) Back to \"Customer list / full information / edit information";
									std::cout << "\n5) Go to \"Information about managers\"";
									std::cout << "\n6) Go to \"Main menu\"";
									std::cout << "\n7) Close the program";

									std::cout << "\n\nEnter item number: ";
									ValidatedInput(menuItem);
									switch (menuItem) {
									case 1:
										try_again = true;
										break;
									case 2:
										ClearConsole();
										goto SELECT_ANOTHER_FIELD_OF_THE_CUSTOMER;
										break;
									case 3:
										ClearConsole();
										goto EDIT_INFORMATION_ABOUT_THE_CUSTOMER;
										break;
									case 4:
										ClearConsole();
										goto CUSTOMERS_LIST;
										break;
									case 5:
										ClearConsole();
										goto CUSTOMERS_INFORMATION;
										break;
									case 6:
									default:
										ClearConsole();
										goto MAIN;
										break;
									case 7:
										std::cout << "\n\nAre you sure you want to close the program?";
										std::cout << "\n1) Yes";
										std::cout << "\n2) No";

										std::cout << "\n\nEnter item number: ";
										ValidatedInput(menuItem);
										switch (menuItem) {
										case 1: return; break;
										case 2:
										default:
											ClearConsole();
											std::cout << "\n\n|--- Edit information about the customer ---|\n";
											continue;
											break;
										}
										break; //кінець case 5: Are you sure you want to close the program?
									}

									break;
								} //кінець if (customerIndex < 1 ||customerIndex > Managers.size()) 
							}

							if (!try_again)
								break;

							ClearConsole();
							std::cout << "\n\n|--- Edit information about the customer ---|\n";

							std::cout << "\nSurname: " << (*customer)->GetSecondName();
							std::cout << "\nName: " << (*customer)->GetFirstName();
							std::cout << "\nPatronymic: " << (*customer)->GetPatronymicName();

						}// кінець while (true) - Select the number of the manager you want to see full information about:
						
						++fieldIndex;
					}
					else
						fieldIndex += 3;

					std::cout << "\n\nEnter a new value for selected field: ";
					ValidatedInput(value);

					EditCustomer(customer, fieldIndex, value);

					ClearConsole();
					std::cout << "\n\n|--- Edit information about the customer ---|\n";

					std::cout << "\nInformation about the customer \"" << (*customer)->GetFullName() << "\" has been edited:";
					(*customer)->ShowInfo();
					SaveMessage("Changing information about customer by id: " + std::to_string((*customer)->GetPersonalId()), historyDataPath);


					while (true) {
						std::cout << "\n\n1) Select another customer to edit";
						std::cout << "\n2) Back to \"Customers list / full information / edit information";
						std::cout << "\n3) Go to \"Information about customers\"";
						std::cout << "\n4) Go to \"Main menu\"";
						std::cout << "\n5) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto EDIT_INFORMATION_ABOUT_THE_CUSTOMER;
							break;
						case 2:
							ClearConsole();
							goto CUSTOMERS_LIST;
							break;
						case 3:
							ClearConsole();
							goto CUSTOMERS_INFORMATION;
							break;
						case 4:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 5:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
							default:
								ClearConsole();
								std::cout << "\n\n|--- Edit information about the customer ---|\n";
								continue;
								break;
							}
							break; //кінець case 5: Are you sure you want to close the program?
						}

					}// кінець case 2: - No - while (true) у DETAILED_INFORMATION_ABOUT_MANAGER

					break;  // кінець case 2: Edit information about the manager

				case 3: // case 3: Back to CUSTOMERS
					ClearConsole();
					goto CUSTOMERS;
					break; //кінець case 3: Back to CUSTOMERS

				case 4: // case 4: Back to the main menu
				default:
					ClearConsole();
					goto MAIN;
					break; //кінець case 4: Back to the main menu

				case 5: // case 5: Close the program
					ClearConsole();
					return;
					break; //кінець case 5: Close the program
				}

				break; //кінець case 1: List of customer (full info/edit)

			case 2: // case 2: List of customers by trip`s country 
				ClearConsole();
			CUSTOMERS_LIST_BY_COUNTRY:
				std::cout << "\n\n|--- List of customers by trip`s country  ---|\n";

				if (Customers.empty()) {
					while (true) {
						std::cout << "\n\nUnfortunately, there are no customers";
						std::cout << "\n1) Add new customers";
						std::cout << "\n2) Go to the \"Main menu\"";
						std::cout << "\n3) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto ADD_NEW_CUSTOMER;
							break;
						case 2:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 3:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
								ClearConsole();
								std::cout << "\n\n|--- List of customers by trip`s country  ---|\n";
								continue;
								break;
							}
							break; //кінець case 3: Are you sure you want to close the program?
						}
					}
				} // кінець if (Customers.empty())

				if (GetCountOfCustomersWithTrip(Customers).first == 0) {
					while (true) {
						std::cout << "\n\nUnfortunately, there are no customers with a trip.";
						std::cout << "\n1) Back to \"Customers\"";
						std::cout << "\n2) Go to \"Main menu\"";
						std::cout << "\n3) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto CUSTOMERS;;
							break;
						case 2:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 3:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								return;
								break;
							case 2:
							default:
								std::cout << "\n\n|--- List of customers by trip`s country  ---|\n";
								continue;
								break;
							}

							break;  //кінець case 3: Are you sure you want to close the program?
						}
					}
				} // кінець if (GetCountOfCustomersWithTrip(Customers) == 0)

				if (GetCountriesOfBoughtTrips(Trips).size() == 1) {
					country = GetCountriesOfBoughtTrips(Trips).back();
					std::cout <<"\nAll current trips are trips to \""<< country <<"\" ";
					std::cout << "\n\nCustomers who have a trip to \"" << country << "\":";
					ShowListOfCustomerNamesByCountry(Customers, country);

					while (true) {
						std::cout << "\n\n1) Back to \"Information about customers\"";
						std::cout << "\n2) Go to \"Main menu\"";
						std::cout << "\n3) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto CUSTOMERS_INFORMATION;
							break;
						case 2:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 3:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								return;
								break;
							case 2:
							default:
								ClearConsole();
								std::cout << "\n\n|--- List of customers by trip`s country  ---|\n";
								continue;
								break;
							}
							break; //кінець case 3: Are you sure you want to close the program?
						}
					}// кінець while (true) у DETAILED_INFORMATION_ABOUT_MANAGER:
				}

				std::cout << "\nCountries: ";
				index = 1;
				for (auto country : GetCountriesOfBoughtTrips(Trips)) {
					std::cout << "\n" << index << ") " << country;
					index++;
				}
					
				
				std::cout << "\n\nSelect the country number, you are interested in: ";
				ValidatedInput(index);

				if (index < 1 || index > static_cast<int>(GetCountriesOfBoughtTrips(Trips).size())) {
					while (true) {
						std::cout << "\n\nThere is no country with such a serial number.";
						std::cout << "\n1) Try again";
						std::cout << "\n2) Back to \"Information about customers\"";
						std::cout << "\n3) Go to \"Main menu\"";
						std::cout << "\n4) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto CUSTOMERS_LIST_BY_COUNTRY;
							break;
						case 2:
							ClearConsole();
							goto CUSTOMERS_INFORMATION;
							break;
						case 3:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 4:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
							default:
								ClearConsole();
								std::cout << "\n\n|--- List of customers by trip`s country  ---|\n";
								continue;
								break;
							}
							break; //кінець case 5: Are you sure you want to close the program?
						}
					} //кінець while (true) 
				}//кінець if (customerIndex < 1 || customerIndex > Customers.size()) 

				country = GetCountriesOfBoughtTrips(Trips).at(index - 1);
				
				std::cout << "\nCustomers who have a trip to \""<< country <<"\":";
				ShowListOfCustomerNamesByCountry(Customers, country);

				while (true) {
					std::cout << "\n\n1) See list of customers by trip`s of another country";
					std::cout << "\n2) Back to \"Information about customers\"";
					std::cout << "\n3) Go to \"Main menu\"";
					std::cout << "\n4) Close the program";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						ClearConsole();
						goto CUSTOMERS_LIST_BY_COUNTRY;
						break;
					case 2:
						ClearConsole();
						goto CUSTOMERS_INFORMATION;
						break;
					case 3:
					default:
						ClearConsole();
						goto MAIN;
						break;
					case 4:
						std::cout << "\n\nAre you sure you want to close the program?";
						std::cout << "\n1) Yes";
						std::cout << "\n2) No";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							return;
							break;
						case 2:
						default:
							ClearConsole();
							std::cout << "\n\n|--- List of customers by trip`s country  ---|\n";
							continue;
							break;
						}
						break; //кінець case 4: Are you sure you want to close the program?
					}
				}// кінець while (true) у DETAILED_INFORMATION_ABOUT_MANAGER:

				break; //кінець case 2: List of customers by trip`s country 

			case 3: // case 3:  Count of customer
				ClearConsole();
			COUNT_OF_CUSTOMERS:
				std::cout << "\n\n|--- Count of customers ---|\n";

				if (Customers.empty()) {
					while (true) {
						std::cout << "\n\nUnfortunately, there are no customers";
						std::cout << "\n1) Add new customer";
						std::cout << "\n2) Go to the \"Main menu\"";
						std::cout << "\n3) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto ADD_NEW_CUSTOMER;
							break;
						case 2:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 3:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
								ClearConsole();
								std::cout << "\n\n|--- Count of customer ---|\n";
								continue;
								break;
							}
							break; //кінець case 3: Are you sure you want to close the program?
						}
					}
				} // кінець if (Customers.empty())

				std::cout << "\nTotal count of customers: " << Customers.size();

				while (true) {
					std::cout << "\n\n1) Back to \"Information about customers\"";
					std::cout << "\n2) Go to \"Main menu\"";
					std::cout << "\n3) Close the program";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						ClearConsole();
						goto CUSTOMERS_INFORMATION;
						break;
					case 2:
					default:
						ClearConsole();
						goto MAIN;
						break;
					case 3:
						std::cout << "\n\nAre you sure you want to close the program?";
						std::cout << "\n1) Yes";
						std::cout << "\n2) No";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1: return; break;
						case 2:
						default:
							ClearConsole();
							goto COUNT_OF_CUSTOMERS;
							break;
						}
						break; //кінець case 3: Are you sure you want to close the program?
					}

				}// кінець case 2: - No - while (true) у DETAILED_INFORMATION_ABOUT_MANAGER

				break; //кінець case 2: Count of managers

			case 4: // case 3: Back to Customers
				ClearConsole();
				goto CUSTOMERS;
				break; //кінець case 3: Back to Customers

			case 5: // case 5: Back to the main menu
			default:
				ClearConsole();
				goto MAIN;
				break; //кінець case 5: Back to the main menu

			case 6: // case 6: Close the program
				ClearConsole();
				return;
				break; //кінець case 6: Close the program
			}

			break; //кінець case 1: Information

		case 2: // case 2: Add new customer
			ClearConsole();
		ADD_NEW_CUSTOMER:
			std::cout << "\n\n|--- Add new customer ---|\n";

			Customers.emplace_back(std::shared_ptr<Customer>(std::make_shared<Customer>()));

			std::cout << "\nEnter customer`s name: ";
			std::getline(std::cin, customer_name);
			Customers.back()->SetFullName(customer_name);

			std::cout << "\nEnter customer`s phone number (format: +380XXXXXXXXX): ";
			std::getline(std::cin, customer_phone_number);
			Customers.back()->SetPhoneNumber(customer_phone_number);

			std::cout << "\nEnter customer`s address: ";
			std::getline(std::cin, customer_address);
			Customers.back()->SetAddress(customer_address);

			std::cout << "\n\nTo complete the process of creating a customer profile, you must purchase a trip";
			if (Managers.empty()) {
				while (true) {
					std::cout << "\n\nUnfortunately, there are no managers who could arrange the purchase of a trip. ";
					std::cout << "\nThe further process of creating a customer profile is not possible";
					std::cout << "\n\n1) Add a new manager and continue the process of creating a client profile";
					std::cout << "\n2) Back to \"Customers\"";
					std::cout << "\n3) Go to \"Main menu\"";
					std::cout << "\n4) Close the program";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						ClearConsole();
						Managers.emplace_back(std::shared_ptr<Manager>(std::make_shared<Manager>()));

						std::cout << "\n\n|--- Add new manager ---|\n";

						std::cout << "\nEnter manager`s name: ";
						std::getline(std::cin, name);
						Managers.back()->SetFullName(name);

						std::cout << "\nEnter manager`s phone number (format: +380XXXXXXXXX): ";
						std::getline(std::cin, phone_number);
						Managers.back()->SetPhoneNumber(phone_number);

						std::cout << "\n\nManager by name\"" << Managers.back()->GetFullName() << "\" was added.\nHis/Her id: " << Managers.back()->GetPersonalId() << "\n";

						SaveMessage("Manager by name \"" + Managers.back()->GetFullName() + "\" was added. His/Her id: " + std::to_string(Managers.back()->GetPersonalId()), historyDataPath);

						break;
					case 2:
						customer = Customers.begin();
						std::advance(customer, Customers.size() -1);
						Customers.remove(*customer);

						ClearConsole();
						goto CUSTOMERS;
						break;
					case 3:
					default:
						customer = Customers.begin();
						std::advance(customer, Customers.size() - 1);
						Customers.remove(*customer);

						ClearConsole();
						goto MAIN;
						break;
					case 4:
						std::cout << "\n\nAre you sure you want to close the program?";
						std::cout << "\n1) Yes";
						std::cout << "\n2) No";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1: 

							customer = Customers.begin();
							std::advance(customer, Customers.size() - 1);
							Customers.remove(*customer);

							return; 
							break;
						case 2:
							ClearConsole();
							std::cout << "\n\n|--- Making a trip purchase ---|\n";
							continue;
							break;
						}
						break; //кінець case 4: Are you sure you want to close the program?
					}
					
					break;
				}
			} // кінець if (Managers.empty())
			if (GetCountOfUnboughtTrips(Trips).first == 0) {
				while (true) {
					std::cout << "\n\nUnfortunately, there are no trips that can be sold";
					std::cout << "\nThe further process of creating a customer profile is not possible.";
					std::cout << "\n1) Add new trip and continue the process of creating a client profile";
					std::cout << "\n2) Back to \"Customers\"";
					std::cout << "\n3) Go to \"Main menu\"";
					std::cout << "\n4) Close the program";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						ClearConsole();
						std::cout << "\n\n|--- Add new trip ---|\n";

						Trips.emplace_back(std::shared_ptr<Trip>(std::make_shared<Trip>()));

						std::cout << "\nEnter trip`s name: ";
						std::getline(std::cin, name);
						Trips.back()->SetFullName(name);

						std::cout << "\nEnter trip`s country: ";
						std::getline(std::cin, country);
						Trips.back()->SetCountry(country);

						std::cout << "\nEnter trip`s city: ";
						std::getline(std::cin, city);
						Trips.back()->SetCity(city);

						std::cout << "\nEnter trip`s date of start (dd/mm/yyyy): ";
						std::getline(std::cin, date_of_start);
						Trips.back()->SetDateOfStart(date_of_start);

						std::cout << "\nEnter trip`s date of end (dd/mm/yyyy): ";
						std::getline(std::cin, date_of_end);
						Trips.back()->SetDateOfEnd(date_of_end);

						std::cout << "\nEnter trip`s price (grn.): ";
						ValidatedInput(price);
						Trips.back()->SetPrice(price);

						SaveMessage("Trip by name \"" + Trips.back()->GetFullName() + "\" was added. It id: " + std::to_string(Trips.back()->GetPersonalId()), historyDataPath);
						
						break;
					case 2:
						customer = Customers.begin();
						std::advance(customer, Customers.size() - 1);
						Customers.remove(*customer);

						ClearConsole();
						goto CUSTOMERS;
						break;
					case 3:
					default:
						customer = Customers.begin();
						std::advance(customer, Customers.size() - 1);
						Customers.remove(*customer);

						ClearConsole();
						goto MAIN;
						break;
					case 4:
						std::cout << "\n\nAre you sure you want to close the program?";
						std::cout << "\n1) Yes";
						std::cout << "\n2) No";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1: 
							customer = Customers.begin();
							std::advance(customer, Customers.size() - 1);
							Customers.remove(*customer);

							return; 
							break;
						case 2:
							ClearConsole();
							std::cout << "\n\n|--- Making a trip purchase ---|\n";
							continue;
							break;
						}
						break; //кінець case 4: Are you sure you want to close the program?
					}
					break;
				}
			} // кінець if (GetCountOfUnboughtTrips(Trips)  == 0)


			ClearConsole();
			std::cout << "\n\n|--- Add new customer ---|\n";

			std::cout << "\nManagers: \n";
			ShowListOfCollectionElementNames(Managers);

			while (true) {
				std::cout << "\n\nSelect the number of the manager who will process the purchase of the trip for new customer: ";
				ValidatedInput(managerIndex);

				try_again = false;

				if (managerIndex < 1 || managerIndex > Managers.size()) {
					while (true) {
						std::cout << "\n\nThere is no manager with such a serial number.";
						std::cout << "\n1) Try again";
						std::cout << "\n2) Back to \"Customers\"";
						std::cout << "\n3) Go to \"Main menu\"";
						std::cout << "\n4) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							try_again = true;
							break;
						case 2:
							ClearConsole();
							goto CUSTOMERS;
							break;
						case 3:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 4:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
							default:
								ClearConsole();
								std::cout << "\n\n|--- Add new customer ---|\n";
								continue;
								break;
							}
							break; //кінець case 5: Are you sure you want to close the program?
						}
					
						break;																		
					} //кінець if (managerIndex < 1 || managerIndex > Managers.size()) 
				}

				if (!try_again)
					break;

				ClearConsole();
				std::cout << "\n\n|--- Add new customer ---|\n";
				std::cout << "\n\nManagers: \n";
				ShowListOfCollectionElementNames(Managers);

			}// кінець while (true) - Select the number of the manager you want to see full information about:

			manager = Managers.begin();
			std::advance(manager, managerIndex - 1);


			ClearConsole();
			std::cout << "\n\nTrips: \n";
			ShowListOfUnboughtTripNames(Trips);

			while (true) {
				std::cout << "\n\nSelect the number of the trip you want to sell: ";
				ValidatedInput(tripIndex);

				try_again = false;

				if (tripIndex <= 0 || tripIndex > GetCountOfUnboughtTrips(Trips).first) {
					while (true) {
						std::cout << "\n\nThere is no trip with such a serial number.";
						std::cout << "\n1) Try again";
						std::cout << "\n2) Back to \"Customers\"";
						std::cout << "\n3) Go to \"Main menu\"";
						std::cout << "\n4) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							try_again = true;
							break;
						case 2:
							ClearConsole();
							goto CUSTOMERS;
							break;
						case 3:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 4:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
							default:
								ClearConsole();
								std::cout << "\n\n|--- Add new customer ---|\n";
								continue;
								break;
							}
							break; //кінець case 5: Are you sure you want to close the program?
						}

						break;					
					} //кінець if (managerIndex < 1 || managerIndex > Managers.size()) 
				}

				if (!try_again)
					break;

				ClearConsole();
				std::cout << "\n\n|--- Add new customer ---|\n";
				std::cout << "\nTrips: \n";
				ShowListOfUnboughtTripNames(Trips);

			}// кінець while (true) - Select the number of the manager you want to see full information about:

			tripIndex = GetCountOfUnboughtTrips(Trips).second[tripIndex - 1];
			trip = Trips.begin();
			std::advance(trip, tripIndex);

			std::cout << "\n\nCustomer by name \"" << Customers.back()->GetFullName() << "\" was added.\nHis/Her id: " << Customers.back()->GetPersonalId() << "\n";
			SaveMessage("Customer by name \"" + Customers.back()->GetFullName() + "\" was added. His/Her id: " + std::to_string(Customers.back()->GetPersonalId()), historyDataPath);

			customer = Customers.begin();
			std::advance(customer, Customers.size() - 1);

			(*manager)->SaleTheTrip(*customer, *trip);

			std::cout << "\n\nManager " << (*manager)->GetFullName() << " sold to client " << (*customer)->GetFullName() << ", tour " << (*trip)->GetFullName() << ";\n";
			SaveMessage("Manager " + (*manager)->GetFullName() + " sold to client " + (*customer)->GetFullName() + ", tour " + (*trip)->GetFullName(), historyDataPath);

			while (true) {
				std::cout << "\n\n1) Add new customer";
				std::cout << "\n2) Back to \"Customers\"";
				std::cout << "\n3) Go to \"Main menu\"";
				std::cout << "\n4) Close the program";

				std::cout << "\n\nEnter item number: ";
				ValidatedInput(menuItem);
				switch (menuItem) {
				case 1:
					ClearConsole();
					goto ADD_NEW_CUSTOMER;
					break;
				case 2:
					ClearConsole();
					goto CUSTOMERS;
					break;
				case 3:
				default:
					ClearConsole();
					goto MAIN;
					break;
				case 4:
					std::cout << "\n\nAre you sure you want to close the program?";
					std::cout << "\n1) Yes";
					std::cout << "\n2) No";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						return;
						break;
					case 2:
					default:
						ClearConsole();
						std::cout << "\n\n|--- Add new customer ---|\n";
						continue;
						break;
					}

					break;  //кінець case 4: Are you sure you want to close the program?
				}
			}// кінець while(true)

			break; //кінець case 2: Add new customer

		case 3: // case 3: Remove customer
			ClearConsole();
		REMOVE_CUSTOMER:

			std::cout << "\n\n|--- Remove customer ---|\n";

			if (GetCountOfCustomersWithoutTrip(Customers).first == 0) {
				while (true) {
					
					std::cout << "\n\nUnfortunately, there are no clients that can be removed: only those clients who have no trips can be removed";
					std::cout << "\n1) Back to \"Customers\"";
					std::cout << "\n2) Go to \"Main menu\"";
					std::cout << "\n3) Close the program";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						ClearConsole();
						goto CUSTOMERS;
						break;
					case 2:
					default:
						ClearConsole();
						goto MAIN;
						break;
					case 3:
						std::cout << "\n\nAre you sure you want to close the program?";
						std::cout << "\n1) Yes";
						std::cout << "\n2) No";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							return;
							break;
						case 2:
						default:
							ClearConsole();
							std::cout << "\n\n|--- Remove customer ---|\n";
							continue;
							break;
						}

						break;  //кінець case 3: Are you sure you want to close the program?
					}
				}
			} // кінець if (GetCountOfCustomersWithoutTrip(Customers) == 0)

			std::cout << "\nCustomers: \n";
			ShowListOfCustomersWithoutTripNames(Customers);

			std::cout << "\n\nSelect the number of the customer you want to remove: ";
			ValidatedInput(customerIndex);

			if (customerIndex < 1 || customerIndex > GetCountOfCustomersWithoutTrip(Customers).first) {
				while (true) {
					std::cout << "\n\nThere is no customer with such a serial number.";
					std::cout << "\n1) Try again";
					std::cout << "\n2) Back to \"Customers\"";
					std::cout << "\n3) Go to \"Main menu\"";
					std::cout << "\n4) Close the program";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						ClearConsole();
						goto REMOVE_CUSTOMER;
						break;
					case 2:
						ClearConsole();
						goto CUSTOMERS;
						break;
					case 3:
					default:
						ClearConsole();
						goto MAIN;
						break;
					case 4:
						std::cout << "\n\nAre you sure you want to close the program?";
						std::cout << "\n1) Yes";
						std::cout << "\n2) No";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							return;
							break;
						case 2:
						default:
							ClearConsole();
							std::cout << "\n\n|--- Remove customer ---|\n";
							continue;
							break;
						}

						break;  //кінець case 4: Are you sure you want to close the program?
					}
				} //кінець while (true) 
			}//кінець if (managerIndex < 1 || managerIndex > Managers.size()) 

			
			customerIndex = GetCountOfCustomersWithoutTrip(Customers).second[customerIndex - 1];
			customer = Customers.begin();
			std::advance(customer, customerIndex);

			name = (*customer)->GetFullName();
			id = (*customer)->GetPersonalId();
			Customers.remove(*customer);

			std::cout << "\nCustomer \"" << name << "\" has been removed.";
			SaveMessage("Customer \"" + name + "\" has been removed.", historyDataPath);
			
			SaveMessage("Customer by name \"" + name + "\" has been removed." + " His/Her id : " + std::to_string(id), historyDataPath);

			while (true) {
				std::cout << "\n\n1) Remove another customer";
				std::cout << "\n2) Back to \"Customers\"";
				std::cout << "\n3) Go to \"Main menu\"";
				std::cout << "\n4) Close the program";

				std::cout << "\n\nEnter item number: ";
				ValidatedInput(menuItem);
				switch (menuItem) {
				case 1:
					ClearConsole();
					goto REMOVE_CUSTOMER;
					break;
				case 2:
					ClearConsole();
					goto CUSTOMERS;
					break;
				case 3:
				default:
					ClearConsole();
					goto MAIN;
					break;
				case 4:
					std::cout << "\n\nAre you sure you want to close the program?";
					std::cout << "\n1) Yes";
					std::cout << "\n2) No";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						return;
						break;
					case 2:
					default:
						ClearConsole();
						std::cout << "\n\n|--- Remove customer ---|\n";
						continue;
						break;
					}

					break;  //кінець case 4: Are you sure you want to close the program?
				}
			}// кінець while(true)

			break; //кінець case 3: Remove customer

		case 4: // case 4: Back to \"Main menu\""
		default:
			ClearConsole();
			goto MAIN;
			break; //кінець case 4: Back to \"Main menu\""

		case 5: // case 5: Close the program
			ClearConsole();
			return;
			break; //кінець case 5: Close the program
		}

		break; //кінець case 2: Customers
	
case 3: // case 3: Trips
		ClearConsole();
	TRIPS:
		std::cout << "\n\n|--- Trips ---|\n";
		std::cout << "\n1) Information";
		std::cout << "\n2) Add new trip";
		std::cout << "\n3) Remove trip";
		std::cout << "\n4) Back to the main menu";
		std::cout << "\n5) Close the program";

		std::cout << "\n\nEnter item number: ";
		ValidatedInput(menuItem);
		switch (menuItem) {
		case 1: // case 1: Information
			ClearConsole();
		TRIPS_INFORMATION:
			std::cout << "\n\n|--- Information about trips ---|\n";
			std::cout << "\n1) List / full information / edit information   ";
			std::cout << "\n2) General information";
			std::cout << "\n3) Back to \"Trips\"";
			std::cout << "\n4) Go to \"Main menu\"";
			std::cout << "\n5) Close the program";

			std::cout << "\n\nEnter item number: ";
			ValidatedInput(menuItem);
			switch (menuItem) {
			case 1: // case 1: Trips get information
				ClearConsole();
			TRIPS_LIST:
				std::cout << "\n\n|--- Trips list / full information / edit information ---|\n";

				if (Trips.empty()) {
					while (true) {
						std::cout << "\n\nUnfortunately, there are no trips";
						std::cout << "\n1) Add new trip";
						std::cout << "\n2) Go to the \"Main menu\"";
						std::cout << "\n3) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto ADD_NEW_TRIP;
							break;
						case 2:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 3:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
								ClearConsole();
								std::cout << "\n\n|--- List \\ full information \\ edit information ---|\n";
								continue;
								break;
							}
							break; //кінець case 3: Are you sure you want to close the program?
						}
					}
				} // кінець if (Customers.empty())

				std::cout << "\nTrips: \n";
				ShowListOfCollectionElementNames(Trips);

				std::cout << "\n1) Show full information about the trip";
				std::cout << "\n2) Edit information about the trip";
				std::cout << "\n3) Back to \"Information about trips\"";
				std::cout << "\n4) Go to \"Main menu\"";
				std::cout << "\n5) Close the program";

				std::cout << "\n\nEnter item number: ";
				ValidatedInput(menuItem);
				switch (menuItem) {
				case 1: // case 1: Show full information about the trip
					ClearConsole();
				FULL_INFORMATION_ABOUT_THE_TRIP:

					std::cout << "\n\n|--- Full information about the trip ---|\n";

					std::cout << "\nTrips: \n";
					ShowListOfCollectionElementNames(Trips);

					std::cout << "\n\nSelect the number of the trip you want to see full information about: ";
					ValidatedInput(tripIndex);

					if (tripIndex < 1 || tripIndex > Trips.size()) {
						while (true) {
							std::cout << "\n\nThere is no customer with such a serial number.";
							std::cout << "\n1) Try again";
							std::cout << "\n2) Back to \"Trips list / full information / edit information";
							std::cout << "\n3) Go to \"Information about customers\"";
							std::cout << "\n4) Go to \"Main menu\"";
							std::cout << "\n5) Close the program";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								ClearConsole();
								goto FULL_INFORMATION_ABOUT_THE_CUSTOMER;
								break;
							case 2:
								ClearConsole();
								goto CUSTOMERS_LIST;
								break;
							case 3:
								ClearConsole();
								goto CUSTOMERS_INFORMATION;
								break;
							case 4:
							default:
								ClearConsole();
								goto MAIN;
								break;
							case 5:
								std::cout << "\n\nAre you sure you want to close the program?";
								std::cout << "\n1) Yes";
								std::cout << "\n2) No";

								std::cout << "\n\nEnter item number: ";
								ValidatedInput(menuItem);
								switch (menuItem) {
								case 1: return; break;
								case 2:
								default:
									ClearConsole();
									std::cout << "\n\n|--- Full information about the customer ---|\n";
									continue;
									break;
								}
								break; //кінець case 5: Are you sure you want to close the program?
							}
						} //кінець while (true) 
					}//кінець if (customerIndex < 1 || customerIndex > Customers.size()) 

					trip = Trips.begin();
					std::advance(trip, tripIndex - 1);

					ClearConsole();
					(*trip)->ShowInfo();

					while (true) {
						std::cout << "\n\n1) See detailed information about another trip";
						std::cout << "\n2) Back to \"Trips list / full information / edit information";
						std::cout << "\n3) Go to \"Information about trips\"";
						std::cout << "\n4) Go to \"Main menu\"";
						std::cout << "\n5) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto FULL_INFORMATION_ABOUT_THE_TRIP;
							break;
						case 2:
							ClearConsole();
							goto TRIPS_LIST;
							break;
						case 3:
							ClearConsole();
							goto TRIPS_INFORMATION;
							break;
						case 4:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 5:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								return;
								break;
							case 2:
							default:
								ClearConsole();
								std::cout << "\n\n|--- Full information about the trip ---|\n";
								continue;
								break;
							}
							break; //кінець case 4: Are you sure you want to close the program?
						}
					}// кінець while (true) у DETAILED_INFORMATION_ABOUT_MANAGER:

					break; // кінець case 1: Show full information about the customer

				case 2: // Edit information about the trip
					ClearConsole();
				EDIT_INFORMATION_ABOUT_THE_TRIP:
					 
					std::cout << "\n\n|--- Edit information about the trip ---|\n";
					
					if (Trips.empty()) {
						while (true) {
							std::cout << "\n\nUnfortunately, there are no trips";
							std::cout << "\n1) Add new trip";
							std::cout << "\n2) Go to \"Main menu\"";
							std::cout << "\n3) Close the program";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								ClearConsole();
								goto ADD_NEW_TRIP;
								break;
							case 2:
							default:
								ClearConsole();
								goto MAIN;
								break;
							case 3:
								std::cout << "\n\nAre you sure you want to close the program?";
								std::cout << "\n1) Yes";
								std::cout << "\n2) No";

								std::cout << "\n\nEnter item number: ";
								ValidatedInput(menuItem);
								switch (menuItem) {
								case 1: return; break;
								case 2:
									ClearConsole();
									std::cout << "\n\n|--- Edit information about the trip ---|\n";
									continue;
									break;
								}
								break; //кінець case 3: Are you sure you want to close the program?
							}
						}
					} // кінець if (Customers.empty())
					
					std::cout << "\n\nTrips: \n";
					ShowListOfUnboughtTripNames(Trips);

					std::cout << "\n\nSelect the number of the trip, that information you want to edit: ";
					ValidatedInput(tripIndex);

					if (tripIndex < 1 || tripIndex > GetCountOfUnboughtTrips(Trips).first) {
						while (true) {
							std::cout << "\n\nThere is no trip with such a serial number";
							std::cout << "\n1) Try again";
							std::cout << "\n2) Back to \"Trips list / full information / edit information";
							std::cout << "\n3) Go to \"Information about trips\"";
							std::cout << "\n4) Go to \"Main menu\"";
							std::cout << "\n5) Close the program";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								ClearConsole();
								goto EDIT_INFORMATION_ABOUT_THE_TRIP;
								break;
							case 2:
								ClearConsole();
								goto TRIPS_LIST;
								break;
							case 3:
								ClearConsole();
								goto TRIPS_INFORMATION;
								break;
							case 4:
							default:
								ClearConsole();
								goto MAIN;
								break;
							case 5:
								std::cout << "\n\nAre you sure you want to close the program?";
								std::cout << "\n1) Yes";
								std::cout << "\n2) No";

								std::cout << "\n\nEnter item number: ";
								ValidatedInput(menuItem);
								switch (menuItem) {
								case 1: return; break;
								case 2:
								default:
									ClearConsole();
									std::cout << "\n\n|--- Edit information about the trip ---|\n";
									continue;
									break;
								}
								break; //кінець case 5: Are you sure you want to close the program?
							}
						} //кінець while (true) 
					}//кінець if (customerIndex < 1 || customerIndex > Customers.size())

					tripIndex = GetCountOfUnboughtTrips(Trips).second[tripIndex - 1];
					trip = Trips.begin();
					std::advance(trip, tripIndex);

					ClearConsole();
					std::cout << "\n\n|--- Edit information about the trip ---|\n";
					ShowFullInfoForEditTrip(trip);

				EDIT_INFORMATION_ABOUT_THE_SAME_TRIP:

					while (true) {
						std::cout << "\n\nSelect the number of the field, that you want to edit: ";
						ValidatedInput(fieldIndex);

						try_again = false;

						if (fieldIndex < 1 || fieldIndex > 6) {
							while (true) {
								std::cout << "\n\nThere is no field with such a serial number";
								std::cout << "\n1) Try again";
								std::cout << "\n2) Select another trip to edit";
								std::cout << "\n3) Back to \"Trips list / full information / edit information";
								std::cout << "\n4) Go to \"Information about customers\"";
								std::cout << "\n5) Go to \"Main menu\"";
								std::cout << "\n6) Close the program";

								std::cout << "\n\nEnter item number: ";
								ValidatedInput(menuItem);
								switch (menuItem) {
								case 1:
									try_again = true;
									break;
								case 2:
									ClearConsole();
									goto EDIT_INFORMATION_ABOUT_THE_TRIP;
									break;
								case 3:
									ClearConsole();
									goto TRIPS_LIST;
									break;
								case 4:
									ClearConsole();
									goto TRIPS_INFORMATION;
									break;
								case 5:
								default:
									ClearConsole();
									goto MAIN;
									break;
								case 6:
									std::cout << "\n\nAre you sure you want to close the program?";
									std::cout << "\n1) Yes";
									std::cout << "\n2) No";

									std::cout << "\n\nEnter item number: ";
									ValidatedInput(menuItem);
									switch (menuItem) {
									case 1: return; break;
									case 2:
									default:
										ClearConsole();
										std::cout << "\n\n|--- Edit information about the trip ---|\n";
										continue;
										break;
									}
									break; //кінець case 5: Are you sure you want to close the program?
								}

								break;							
							} //кінець if (fieldIndex < 1 || fieldIndex > 4)
						}

						if (!try_again)
							break;

						ClearConsole();
						std::cout << "\n\n|--- Edit information about the trip ---|\n";
						ShowFullInfoForEditTrip(trip);


					}// кінець while (true) - Select the number of the field, that you want to edit: :

					std::cout << "\n\nEnter a new value for selected field: ";

					if (fieldIndex == 6) {
						ValidatedInput(price);
						(*trip)->SetPrice(price);
					}
					else {
						ValidatedInput(value);
						EditTrip(trip, fieldIndex, value);
					}
	
					ClearConsole();
					std::cout << "\n\n|--- Edit information about the trip ---|\n";

					std::cout << "\nInformation about the trip \"" << (*trip)->GetFullName() << "\" has been edited:";
					(*trip)->ShowInfo();

					SaveMessage("Changing information about trip by id: " + std::to_string((*trip)->GetPersonalId()), historyDataPath);

					while (true) {
						std::cout << "\n\n1) Edit enother field for selected trip: " << (*trip)->GetFullName();
						std::cout << "\n2) Edit information for another trip";
						std::cout << "\n3) Back to \"Information\"";
						std::cout << "\n4) Go to the \"Main menu\"";
						std::cout << "\n5) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							std::cout << "\n\n|--- Edit information about the trip ---|\n";
							ShowFullInfoForEditTrip(trip);
							goto EDIT_INFORMATION_ABOUT_THE_SAME_TRIP;
							break;
						case 2:
							ClearConsole();
							goto EDIT_INFORMATION_ABOUT_THE_TRIP;
							break;
						case 3:
							ClearConsole();
							goto TRIPS_INFORMATION;
							break;
						case 4:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 5:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								return;
								break;
							case 2:
							default:
								ClearConsole();
								std::cout << "\n\n|--- Edit information about the trip ---|\n";
								continue;
								break;
							}

							break;  //кінець case 5: Are you sure you want to close the program?
						}
					}// кінець while (true)

					break;  // кінець case 2: Edit information about the manager

				case 3: // case 3: Back to CUSTOMERS
					ClearConsole();
					goto CUSTOMERS;
					break; //кінець case 3: Back to CUSTOMERS

				case 4: // case 4: Back to the main menu
				default:
					ClearConsole();
					goto MAIN;
					break; //кінець case 4: Back to the main menu

				case 5: // case 5: Close the program
					ClearConsole();
					return;
					break; //кінець case 5: Close the program
				}

				break; //кінець case 1: Trips get information

			case 2: // case 2: General information
				ClearConsole();
			GENERAL_INFORMATION_ABOUT_TRIPS:
				std::cout << "\n\n|--- General information about trips ---|\n";
				
				if (Trips.empty()) {
					while (true) {
						std::cout << "\n\nUnfortunately, there are no trips";
						std::cout << "\n1) Add new trip";
						std::cout << "\n2) Go to \"Main menu\"";
						std::cout << "\n3) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto ADD_NEW_TRIP;
							break;
						case 2:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 3:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
								ClearConsole();
								std::cout << "\n\n|--- Edit information about the trip ---|\n";
								continue;
								break;
							}
							break; //кінець case 3: Are you sure you want to close the program?
						}
					}
				} // кінець if (Customers.empty())
				std::cout << "\nGeneral information for all time: ";
				std::cout << "\n\tCount of valid trips: " << Trips.size();
				std::cout << "\n\t\ton sale: " << GetCountOfUnboughtTrips(Trips).first;
				std::cout << "\n\t\tsold: " << GetCountOfPurchasedTrips(Trips).first;
				
				std::cout << "\n\tCount of successful orders: " << GetCountOfOrders();
				std::cout << "\n\tAverage duration of the trip: ";
				if ((std::ceil(GetAverageDurationOfTrips(Trips)) - GetAverageDurationOfTrips(Trips)) > 0.5)
					std::cout << std::floor(GetAverageDurationOfTrips(Trips)) << " days ";
				else
					std::cout << std::ceil(GetAverageDurationOfTrips(Trips)) << " days";
				
				std::cout << "\n\tAverage cost of the trip: " << GetAveragePriceOfTrips(Trips) << " UAH";
				
				ShowMostPupularCountries(FindMostPupularCountries(Trips));

				std::cout << "\n\nDo you want to see a general information about trips for a specific year?";
				std::cout << "\n1)Yes \n2)No";
				std::cout << "\n\nEnter item number: ";
				ValidatedInput(menuItem);
				switch (menuItem) {
				case 1: // yes - see a general information about trips for a specific year
					ClearConsole();

				GENERAL_INFORMATION_ABOUT_TRIPS_BY_YEAR:
					std::cout << "\n\n|--- General information about trips ---|\n";
					
					mytime = std::time(NULL);
					now;
					gmtime_s(&now, &mytime);
					current_year = now.tm_year + 1900;

					std::cout << "\nEnter the year you are interested in (recomended  2021-" << current_year << "): ";
					ValidatedInput(year);
					
					if (year > current_year) {
						while (true) {
							std::cout << "\n\nInvalid year: you may have entered a future year.";
							std::cout << "\n1) See a general information about trips for another year (recomended  2021-" << current_year<<")";
							std::cout << "\n2) Back to \"General information about trips for all time\"";
							std::cout << "\n3) Go to \"Information about trips\"";
							std::cout << "\n4) Go to \"Main menu\"";
							std::cout << "\n5) Close the program";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								ClearConsole();
								goto GENERAL_INFORMATION_ABOUT_TRIPS_BY_YEAR;
								break;
							case 2:
								ClearConsole();
								goto GENERAL_INFORMATION_ABOUT_TRIPS;
								break;
							case 3:
								ClearConsole();
								goto TRIPS_INFORMATION;
								break;
							case 4:
							default:
								ClearConsole();
								goto MAIN;
								break;
							case 5:
								std::cout << "\n\nAre you sure you want to close the program?";
								std::cout << "\n1) Yes";
								std::cout << "\n2) No";

								std::cout << "\n\nEnter item number: ";
								ValidatedInput(menuItem);
								switch (menuItem) {
								case 1: return; break;
								case 2:
								default:
									ClearConsole();
									std::cout << "\n\n|--- General information about trips ---|\n";
									break;
								}
								break; //кінець case 3: Are you sure you want to close the program?
							}

						}// кінець case 2: - No - while (true) у DETAILED_INFORMATION_ABOUT_MANAGER
					}
					if (year < current_year && year < 2021) {
						while (true) {
							std::cout << "\n\nInvalid year: you may have entered a year that is too old..";
							std::cout << "\n1) See a general information about trips for another year (recomended  2021-" << current_year<<")";
							std::cout << "\n2) Back to \"General information about trips for all time\"";
							std::cout << "\n3) Go to \"Information about trips\"";
							std::cout << "\n4) Go to \"Main menu\"";
							std::cout << "\n5) Close the program";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1:
								ClearConsole();
								goto GENERAL_INFORMATION_ABOUT_TRIPS_BY_YEAR;
								break;
							case 2:
								ClearConsole();
								goto GENERAL_INFORMATION_ABOUT_TRIPS;
								break;
							case 3:
								ClearConsole();
								goto TRIPS_INFORMATION;
								break;
							case 4:
							default:
								ClearConsole();
								goto MAIN;
								break;
							case 5:
								std::cout << "\n\nAre you sure you want to close the program?";
								std::cout << "\n1) Yes";
								std::cout << "\n2) No";

								std::cout << "\n\nEnter item number: ";
								ValidatedInput(menuItem);
								switch (menuItem) {
								case 1: return; break;
								case 2:
								default:
									ClearConsole();
									std::cout << "\n\n|--- General information about trips ---|\n";
									break;
								}
								break; //кінець case 3: Are you sure you want to close the program?
							}

						}// кінець case 2: - No - while (true) у DETAILED_INFORMATION_ABOUT_MANAGER
					}

					ClearConsole();

					std::cout << "\n\n|--- General information about trips ---|\n";
					std::cout << "\nGeneral information for " << year << " year:";
					if (year == current_year)
						std::cout << "\n\tCount of sold trips: " << GetCountOfOrders(year) + GetCountOfPurchasedTrips(Trips).first;
					else if (year < current_year && year >= 2021)
						std::cout << "\n\tCount of sold trips: " << GetCountOfOrders(year);
					
					std::cout << "\n\tAverage duration of the trip: ";
					if ((std::ceil(GetAverageDurationOfTrips(Trips, year)) - GetAverageDurationOfTrips(Trips, year)) > 0.5)
						std::cout << std::floor(GetAverageDurationOfTrips(Trips, year)) << " days ";
					else
						std::cout << std::ceil(GetAverageDurationOfTrips(Trips, year)) << " days";

					std::cout << "\n\tAverage cost of the trip: " << GetAveragePriceOfTrips(Trips, year) << " UAH";
					
					ShowMostPupularCountries(FindMostPupularCountries(Trips, year));

					while (true) {
						std::cout << "\n\n1) See a general information about trips for another year";
						std::cout << "\n2) Back to \"General information about trips for all time\"";
						std::cout << "\n3) Go to \"Information about trips\"";
						std::cout << "\n4) Go to \"Main menu\"";
						std::cout << "\n5) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto GENERAL_INFORMATION_ABOUT_TRIPS_BY_YEAR;
							break;
						case 2:
							ClearConsole();
							goto GENERAL_INFORMATION_ABOUT_TRIPS;
							break;
						case 3:
							ClearConsole();
							goto TRIPS_INFORMATION;
							break;
						case 4:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 5:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
							default:
								ClearConsole();
								std::cout << "\n\n|--- General information about trips ---|\n";
								break;
							}
							break; //кінець case 3: Are you sure you want to close the program?
						}

					}// кінець case 2: - No - while (true) у DETAILED_INFORMATION_ABOUT_MANAGER

					break; // кінець case 1: yes - see a general information about trips for a specific year

				case 2: // no
				default:
					while (true) {
						std::cout << "\n\n1) Back to \"Information about trips\"";
						std::cout << "\n2) Go to \"Main menu\"";
						std::cout << "\n3) Close the program";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							ClearConsole();
							goto TRIPS_INFORMATION;
							break;
						case 2:
						default:
							ClearConsole();
							goto MAIN;
							break;
						case 3:
							std::cout << "\n\nAre you sure you want to close the program?";
							std::cout << "\n1) Yes";
							std::cout << "\n2) No";

							std::cout << "\n\nEnter item number: ";
							ValidatedInput(menuItem);
							switch (menuItem) {
							case 1: return; break;
							case 2:
							default:
								ClearConsole();
								std::cout << "\n\n|--- General information about trips ---|\n";
								break;
							}
							break; //кінець case 3: Are you sure you want to close the program?
						}

					}// кінець case 2: - No - while (true) у DETAILED_INFORMATION_ABOUT_MANAGER
					break;// кінець case 1: no
				}

				break; //кінець case 2: General information

			case 3: // case 3: Back to TRIPS
				ClearConsole();
				goto TRIPS;
				break; //кінець case 3: Back to TRIPS

			case 4: // case 4: Back to the main menu
			default:
				ClearConsole();
				goto MAIN;
				break; //кінець case 4: Back to the main menu

			case 5: // case 5: Close the program
				ClearConsole();
				return;
				break; //кінець case 5: Close the program
			}

			break; //кінець case 1: Information

		case 2: // case 2: Add new trip
			ClearConsole();
		ADD_NEW_TRIP:

			std::cout << "\n\n|--- Add new trip ---|\n";
			
			Trips.emplace_back(std::shared_ptr<Trip>(std::make_shared<Trip>()));

			std::cout << "\nEnter trip`s name: ";
			std::getline(std::cin, name);
			Trips.back()->SetFullName(name);

			std::cout << "\nEnter trip`s country: ";
			std::getline(std::cin, country);
			Trips.back()->SetCountry(country);

			std::cout << "\nEnter trip`s city: ";
			std::getline(std::cin, city);
			Trips.back()->SetCity(city);

			std::cout << "\nEnter trip`s date of start (dd/mm/yyyy): ";
			std::getline(std::cin, date_of_start);
			Trips.back()->SetDateOfStart(date_of_start);

			std::cout << "\nEnter trip`s date of end (dd/mm/yyyy): ";
			std::getline(std::cin, date_of_end);
			Trips.back()->SetDateOfEnd(date_of_end);

			std::cout << "\nEnter trip`s price (grn.): ";
			ValidatedInput(price);
			Trips.back()->SetPrice(price);

		    std::cout << "\n\nTrip by name \"" << Trips.back()->GetFullName() << "\" was added.\nIt id: " << Trips.back()->GetPersonalId() << "\n";
			SaveMessage("Trip by name \"" + Trips.back()->GetFullName() + "\" was added. It id: " + std::to_string(Trips.back()->GetPersonalId()), historyDataPath);

			while (true) {
				std::cout << "\n\n1) Add new trip";
				std::cout << "\n2) Back to \"Trips\"";
				std::cout << "\n3) Go to \"Main menu\"";
				std::cout << "\n4) Close the program";

				std::cout << "\n\nEnter item number: ";
				ValidatedInput(menuItem);
				switch (menuItem) {
				case 1:
					ClearConsole();
					goto ADD_NEW_TRIP;
					break;
				case 2:
					ClearConsole();
					goto TRIPS;
					break;
				case 3:
				default:
					ClearConsole();
					goto MAIN;
					break;
				case 4:
					std::cout << "\n\nAre you sure you want to close the program?";
					std::cout << "\n1) Yes";
					std::cout << "\n2) No";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						return;
						break;
					case 2:
					default:
						ClearConsole();
						std::cout << "\n\n|--- Add new trip ---|\n";
						continue;
						break;
					}

					break;  //кінець case 4: Are you sure you want to close the program?
				}
			}// кінець while(true)

			break; //кінець case 2: Add new trip

		case 3: // case 3: Remove trip
			ClearConsole();
		REMOVE_TRIP:

			std::cout << "\n\n|--- Remove trip ---|\n";
			
			if (GetCountOfUnboughtTrips(Trips).first == 0) {
				while (true) {
					std::cout << "\n\nUnfortunately, there are no trips that can be removed: only trips that have not been purchased (on sale) can be removed.";
					std::cout << "\n1) Back to \"Trips\"";
					std::cout << "\n2) Go to \"Main menu\"";
					std::cout << "\n3) Close the program";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						ClearConsole();
						goto TRIPS;
						break;
					case 2:
					default:
						ClearConsole();
						goto MAIN;
						break;
					case 3:
						std::cout << "\n\nAre you sure you want to close the program?";
						std::cout << "\n1) Yes";
						std::cout << "\n2) No";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							return;
							break;
						case 2:
						default:
							ClearConsole();
							std::cout << "\n\n|--- Remove trip ---|\n";
							continue;
							break;
						}

						break;  //кінець case 3: Are you sure you want to close the program?
					}
				}
			} // кінець if (GetCountOfCustomersWithoutTrip(Customers) == 0)

			std::cout << "\nTrips: \n";
			ShowListOfUnboughtTripNames(Trips);

			std::cout << "\n\nSelect the number of the trip you want to remove: ";
			ValidatedInput(tripIndex);

			if (tripIndex < 1 || tripIndex > GetCountOfUnboughtTrips(Trips).first) {
				while (true) {
					std::cout << "\n\nThere is no trip with such a serial number.";
					std::cout << "\n1) Try again";
					std::cout << "\n2) Back to \"Trips\"";
					std::cout << "\n3) Go to \"Main menu\"";
					std::cout << "\n4) Close the program";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						ClearConsole();
						goto REMOVE_TRIP;
						break;
					case 2:
						ClearConsole();
						goto TRIPS;
						break;
					case 3:
					default:
						ClearConsole();
						goto MAIN;
						break;
					case 4:
						std::cout << "\n\nAre you sure you want to close the program?";
						std::cout << "\n1) Yes";
						std::cout << "\n2) No";

						std::cout << "\n\nEnter item number: ";
						ValidatedInput(menuItem);
						switch (menuItem) {
						case 1:
							return;
							break;
						case 2:
						default:
							ClearConsole();
							std::cout << "\n\n|--- Remove trip ---|\n";
							continue;
							break;
						}

						break;  //кінець case 4: Are you sure you want to close the program?
					}
				} //кінець while (true) 
			}//кінець if (managerIndex < 1 || managerIndex > Managers.size()) 


			tripIndex = GetCountOfUnboughtTrips(Trips).second[tripIndex - 1];
			trip = Trips.begin();
			std::advance(trip, tripIndex);

			name = (*trip)->GetFullName();
			id = (*trip)->GetPersonalId();
			Trips.remove(*trip);

			std::cout << "\nTrip \"" << name << "\" has been removed.";
			SaveMessage("Trip by name \"" + name + "\" has been removed." + " It id : " + std::to_string(id), historyDataPath);

			while (true) {
				std::cout << "\n\n1) Remove another trip";
				std::cout << "\n2) Back to \"Trips\"";
				std::cout << "\n3) Go to \"Main menu\"";
				std::cout << "\n4) Close the program";

				std::cout << "\n\nEnter item number: ";
				ValidatedInput(menuItem);
				switch (menuItem) {
				case 1:
					ClearConsole();
					goto REMOVE_TRIP;
					break;
				case 2:
					ClearConsole();
					goto TRIPS;
					break;
				case 3:
				default:
					ClearConsole();
					goto MAIN;
					break;
				case 4:
					std::cout << "\n\nAre you sure you want to close the program?";
					std::cout << "\n1) Yes";
					std::cout << "\n2) No";

					std::cout << "\n\nEnter item number: ";
					ValidatedInput(menuItem);
					switch (menuItem) {
					case 1:
						return;
						break;
					case 2:
					default:
						ClearConsole();
						std::cout << "\n\n|--- Remove trip ---|\n";
						continue;
						break;
					}

					break;  //кінець case 4: Are you sure you want to close the program?
				}
			}// кінець while(true)

			break; //кінець case 3: Remove trip
		
		case 4: // case 4: Back to the MAIN
		default:
			ClearConsole();
			goto MAIN;
			break; //кінець case 4: Back to the MAIN

		case 5: // case 5: Close the program
			ClearConsole();
			return;
			break; //кінець case 5: Close the program
		}
		break; //кінець case 3: Trips

case 4: // case 4: Close the program
	return;
	break; //кінець case 4: Close the program
	}

}




////////////////////////////////////////////////////////////////////////////////////////////////////



// 0 Загальні методи:


//0.1 Вивід списка менеджерів, клієнтів, путівок, тощо.
template<typename T>
void ShowListOfCollectionElementNames(const std::list<std::shared_ptr<T>>& Collection) {
	if (Collection.empty())
		return;

	int index = 1;
	for ( auto& element:Collection) {
		std::cout << index << ") ";
		std::cout << element->GetFullName() << " \n";
		index++;
	}
}


//0.2 Отримання різниці між двома датами формату "dd/mm/yyyy"
int GetDateDifference(const std::string firstDate, const std::string secondDate)
{
	std::time_t mytime = std::time(NULL);
	std::tm now;
	gmtime_s(&now, &mytime);


	int day_1, month_1, year_1, day_2, month_2, year_2;

	std::tm time_1 = {}; // щоб усі поля = 0
	std::tm time_2 = {}; // щоб усі поля = 0
	std::time_t tt; // для збереження інформації про секунди, як сплинули з 01/01/1970

	if (secondDate == "today") {
		std::time_t mytime = std::time(NULL);
		std::tm now;
		gmtime_s(&now, &mytime);

		// Це потрібно для більш точного результату
		day_1 = now.tm_mday;
		month_1 = now.tm_mon + 1;
		year_1 = now.tm_year + 1900;

		time_1.tm_year = year_1 - 1900; //tm_year є [1900, наш рік]
		time_1.tm_mon = month_1 - 1;   //tm_mon є [0, 11]
		time_1.tm_mday = day_1;

		day_2 = std::stoi(firstDate.substr(0, 2));
		month_2 = std::stoi(firstDate.substr(3, 2));
		year_2 = std::stoi(firstDate.substr(6, 4));

		time_2.tm_year = year_2 - 1900; //tm_year є [1900, наш рік]
		time_2.tm_mon = month_2 - 1;   //tm_mon є [0, 11]
		time_2.tm_mday = day_2;

		tt = std::mktime(&time_1);
		int days_1 = static_cast<int>(tt / (60 * 60 * 24));

		tt = std::mktime(&time_2);
		int days_2 = static_cast<int>(tt / (60 * 60 * 24));

		return days_2 - days_1;
	}

	else {
		day_1 = std::stoi(firstDate.substr(0, 2));
		month_1 = std::stoi(firstDate.substr(3, 2));
		year_1 = std::stoi(firstDate.substr(6, 4));

		day_2 = std::stoi(secondDate.substr(0, 2));
		month_2 = std::stoi(secondDate.substr(3, 2));
		year_2 = std::stoi(secondDate.substr(6, 4));

		time_1.tm_year = year_1 - 1900; //tm_year є [1900, наш рік]
		time_1.tm_mon = month_1 - 1;   //tm_mon є [0, 11]
		time_1.tm_mday = day_1;

		time_2.tm_year = year_2 - 1900; // tm_year отсчитывает от 1900 года
		time_2.tm_mon = month_2 - 1;   // tm_mon начинается с 0
		time_2.tm_mday = day_2;

		tt = std::mktime(&time_1);
		int days_1 = static_cast<int>(tt / (60 * 60 * 24));

		tt = std::mktime(&time_2);
		int days_2 = static_cast<int>(tt / (60 * 60 * 24));

		return days_2 - days_1;
	}
}


//0.3 Функція, для коректного вводу даних для числової змінної
template<typename T>
void ValidatedInput(T& val) {
	while (true) {
		std::cin >> val;
		if (std::cin.fail()) {
			std::cout << "\n\nYou may have entered a letter or symbol instead of a number";
			std::cout << "\nTry again;\n";
			std::cin.clear(); // 
			std::cin.ignore(INT_MAX, '\n');
		}
		else
			break;
	}
	std::cin.ignore(INT_MAX, '\n');
}


//0.4 Запис повідомлення у файл.txt
void SaveMessage(const std::string msg, const std::string path) {
	std::fstream MessageWrite;
	MessageWrite.open(path, std::fstream::out | std::fstream::app);
	if (!MessageWrite.is_open())
		std::cout << "Error\n";
	else {
		std::time_t mytime = std::time(NULL);
		std::tm now;
		gmtime_s(&now, &mytime);

		MessageWrite << now.tm_year + 1900 << "-" << now.tm_mon + 1 << "-" << now.tm_mday << " ";
		MessageWrite << now.tm_hour + 3 << ":" << now.tm_min << ":" << now.tm_sec;
		MessageWrite << "\t—\t" << msg << "\n\n";
	}
	MessageWrite.close();
}


//0.5 Очищення консолі 
void ClearConsole() {std::system("cls");}


//0.6 Отримання кількості замовлень (за весь час або за роком)
int GetCountOfOrders(const int year, const std::string path){
	std::stack<Order> Orders;
	ReadOrdersData(Orders, path);
	
	int count = 0;
	if (year != 0) {
		while (!Orders.empty()) {
			if (Orders.top().year_of_booking == year)
				++count;
			Orders.pop();
		}
		return count;
	}
	else 
		return Orders.size();
}


//0.7 Збереження даних про замовлення у файл.txt
void SaveOrderData(const int year_of_booking, const std::string country, const std::string name_of_trip, const std::string name_of_customer, const double price, const std::string path){
	std::fstream orderWrite;
	orderWrite.open(path, std::fstream::app);
	if (!orderWrite.is_open()) 
		std::cout << "Error: Could not open the file at the specified path to record orders data. \nSpecified path:" << path << "\n";
	else {
		orderWrite << "\n\n" << year_of_booking;
		orderWrite << "\n" << country;
		orderWrite << "\n" << name_of_trip;
		orderWrite << "\n" << name_of_customer;
		orderWrite << "\n" << price;
	}
	orderWrite.close();
}


//0.8 Зчитування даних про замовлення з файл.txt
void ReadOrdersData(std::stack<Order>& Collection, const std::string path) {
	std::ifstream ordersRead;
	ordersRead.open(path, std::ios::in);

	if (!ordersRead.is_open()) 
		std::cout << "Error: Could not open the file at the specified path to read orders data.\nSpecified path:" << path << "\n";
	else {
		std::string year_of_booking, сountry, name_of_trip, name_of_customer, duration, price, emptiness;
		std::getline(ordersRead, emptiness); // зчитування порожнього рядка

		while (!ordersRead.eof()) {
			std::getline(ordersRead, emptiness); // зчитування порожнього рядка
			std::getline(ordersRead, year_of_booking);
			std::getline(ordersRead, сountry);
			std::getline(ordersRead, name_of_trip);
			std::getline(ordersRead, name_of_customer);
			std::getline(ordersRead, duration);
			std::getline(ordersRead, price);
			Collection.push(Order(std::stoi(year_of_booking), сountry, name_of_trip, name_of_customer, std::stoi(duration), std::stod(price)));
		}
	}
	ordersRead.close();
}



////////////////////////////////////////////////////////////////////////////////////////////////////



// 1 Функції менеджера:


//1.1 Оформлення продажу
// (*manager)->PlaceOrder(*customer, *trip);


//1.2 Оформлення поверення товару
// (*manager)->ReturnTrip(*customer);


//1.1 Вивід повної інформації про менеджера, для редагування даних про менеджера
void ShowFullInfoForEditManager(const manager_list_iter_t& manager){
	std::cout << "\n" << "1) Name: " << (*manager)->GetFullName();
	std::cout << "\n" << "2) Phone number: " << (*manager)->GetPhoneNumber();
	std::cout << "\n" << "3) Name of the company: " << (*manager)->GetNameOfCompany();
	std::cout << "\n" << "!!! By changing the \"Name of the company\", you will change it for all managers and customers.";
}


//1.2 Редагування даних про менеджера
void EditManager(manager_list_iter_t& manager, const int fieldIndex, const std::string value){
	switch (fieldIndex){
	case 1:
		(*manager)->SetFullName(value);
		break;
	case 2:
		(*manager)->SetSecondName(value);
		break;
	case 3:
		(*manager)->SetFirstName(value);
		break;
	case 4:
		(*manager)->SetPatronymicName(value);
		break;
	case 5:
		(*manager)->SetPhoneNumber(value);
		break;
	case 6:
		(*manager)->SetNameOfCompany(value);
		break;
	default:
		break;
	}
}


//1.3 Збереження даних про менеджерів у файл.txt 
void SaveManagersData(const ListSharedsManager_t& ManagersCollection, const std::string path) {
	std::fstream ManagerObjectsWrite;
	ManagerObjectsWrite.open(path, std::fstream::out);

	if (!ManagerObjectsWrite.is_open()) 
		std::cout << "Error: Could not open the file at the specified path to record managers data. \nSpecified path: " << path << "\n";
	else {
		if (ManagersCollection.empty()) {
			ManagerObjectsWrite << "Empty";
			ManagerObjectsWrite.close();
			return;
		}
		int count = 0;
		ManagerObjectsWrite << "\n"; // Перший пустий рядок

		for (const auto& element : ManagersCollection) {
			ManagerObjectsWrite << "Object " << count + 1 << ":\n";
			ManagerObjectsWrite << element->GetFullName() << "\n";
			ManagerObjectsWrite << element->GetPhoneNumber() << "\n";
			ManagerObjectsWrite << element->GetNameOfCompany() << "\n";
			ManagerObjectsWrite << element->GetPersonalId() << "\n";

			count++;
			if (count != ManagersCollection.size())
				ManagerObjectsWrite << "----------------------------------------------\n";
		}
	}
	ManagerObjectsWrite.close();
}


//1.4 Зчитування даних про менеджерів з файл.txt
void ReadManagersData(ListSharedsManager_t& ManagersCollection, const std::string path) {
	std::ifstream ManagerObjectsRead;
	ManagerObjectsRead.open(path, std::ios::in);

	if (!ManagerObjectsRead.is_open())
		std::cout << "Error: Could not open the file at the specified path to read managers data. \nSpecified path: " << path << "\n";
	else {
		std::string field, name, phone_number, name_of_company, personal_id, emptiness;
		std::getline(ManagerObjectsRead, emptiness); // зчитується перший непотрібний рядок

		if (emptiness == "Empty") {
			ManagerObjectsRead.close();
			return;
		}

		std::getline(ManagerObjectsRead, emptiness); // зчитується непотрібний рядок "Object"
		while (!ManagerObjectsRead.eof()) {
			std::getline(ManagerObjectsRead, name);
			std::getline(ManagerObjectsRead, phone_number);
			std::getline(ManagerObjectsRead, name_of_company);	
			std::getline(ManagerObjectsRead, personal_id);

			ManagersCollection.emplace_back(std::shared_ptr<Manager>(std::make_shared<Manager>(name, phone_number, std::stoi(personal_id))));
			
			if (!ManagerObjectsRead.eof()) {
				std::getline(ManagerObjectsRead, emptiness); // зчитується порожній рядок 
				std::getline(ManagerObjectsRead, emptiness); // зчитується непотрібний рядок "Object"
			}
		}
	}
	ManagerObjectsRead.close();
}



////////////////////////////////////////////////////////////////////////////////////////////////////



// Функції клієнта:


//2.1 Вивід повної інформації про менеджера, для редагування даних про клієнта
void ShowFullInfoForEditCustomer(const customer_list_iter_t& customer){
	std::cout << "\n" << "1) Name: " << (*customer)->GetFullName();
	std::cout << "\n" << "2) Phone number: " << (*customer)->GetPhoneNumber();
	std::cout << "\n" << "3) Address: " << (*customer)->GetAddress();
}


//2.2 Редагування даних про клієнта
void EditCustomer(customer_list_iter_t& customer, const int fieldIndex, const std::string value){
	if ((*customer)->GetStatus() == CustomerStatus::WITH_TRIP || (*customer)->GetStatus() == CustomerStatus::DURING_A_TRIP)
		return;

	switch (fieldIndex){
	case 1:
		(*customer)->SetFullName(value);
		break;
	case 2:
		(*customer)->SetSecondName(value);
		break;
	case 3:
		(*customer)->SetFirstName(value);
		break;
	case 4:
		(*customer)->SetPatronymicName(value);
		break;
	case 5:
		(*customer)->SetPhoneNumber(value);
		break;
	case 6:
		(*customer)->SetAddress(value);
		break;
	default:
		break;
	}
}


//2.3 Вивід списка клієнтів, які придбали путівку, до певної країни 
void ShowListOfCustomerNamesByCountry(const ListSharedsCustomer_t& Customers, const std::string country) { // Список клієнтів, які придбали путівку до певної країни 
	int index = 0; 
	for (const auto& customer : Customers) {
		if (customer->GetTrip() != nullptr) {
			if (customer->GetTrip()->GetCountry() == country) {
				index++;
				std::cout << "\n" << index << ") " << customer->GetFullName() << " (" << customer->GetTrip()->GetFullName() <<") ";
			}
		}
	}
	std::cout << "\n";

	if (index == 0)
		std::cout << "\n\nHere are no customers who have a tour to " << country << "\n";
}


//2.4 Вивід списка клієнтів, які не мають путівку. 
void ShowListOfCustomersWithoutTripNames(const ListSharedsCustomer_t& CustomersCollection) {
	int count = 0;
	for (auto& customer : CustomersCollection) {
		if (customer->GetStatus()==CustomerStatus::WITHOUT_TRIP) {
			std::cout << count+1 << ") ";
			std::cout << customer->GetFullName() << " \n";
			count++;
		}
	}
}


//2.5 Вивід списка клієнтів, які мають путівку. 
void ShowListOfCustomersWithTripNames(const ListSharedsCustomer_t& CustomersCollection) {
	int count = 0;
	for (auto& customer : CustomersCollection) {
		if (customer->GetStatus() == CustomerStatus::WITH_TRIP) {
			std::cout << count + 1 << ") ";
			std::cout << customer->GetFullName() << " \n";
			count++;
		}
		else if (customer->GetStatus() == CustomerStatus::DURING_A_TRIP) {
			std::cout << count + 1 << ") ";
			std::cout << customer->GetFullName() << " (during a trip) \n";
			count++;
		}
	}
}


//2.6 Отримання кількості клієнтів, які мають путівку. 
std::pair<size_t, std::vector<int>> GetCountOfCustomersWithTrip(const ListSharedsCustomer_t& CustomersCollection){
	std::vector<int> Indices;
	int count = 0;
	int index = 0;
	for (auto& customer : CustomersCollection) {
		if (customer->GetStatus() == CustomerStatus::WITH_TRIP || customer->GetStatus() == CustomerStatus::DURING_A_TRIP) {
			count++;
			Indices.emplace_back(index);
		}
		index++;
	}
	return std::make_pair(count, Indices);
}


//2.7 Отримання кількості клієнтів, які не мають путівку. 
std::pair<size_t, std::vector<int>> GetCountOfCustomersWithoutTrip(const ListSharedsCustomer_t& CustomersCollection) {
	std::vector<int> Indices;
	int count = 0;
	int index = 0;
	for (auto& customer : CustomersCollection) {
		if (customer->GetStatus() == CustomerStatus::WITHOUT_TRIP) {
			count++;
			Indices.emplace_back(index);
		}
		index++;
	}
	return std::make_pair(count, Indices);
}


//2.8 Збереження даних про клієнтів у файл.txt 
void SaveCustomersData(const ListSharedsCustomer_t& CustomersCollection, const std::string path) {
	std::fstream CustomerObjectsWrite;
	CustomerObjectsWrite.open(path, std::fstream::out);
	if (!CustomerObjectsWrite.is_open()) 
		std::cout << "Error: Could not open the file at the specified path to record customers data. \nSpecified path: " << path << "\n";
	else {
		if (CustomersCollection.empty()) {
			CustomerObjectsWrite << "Empty";
			CustomerObjectsWrite.close();
			return;
		}

		int count = 0;
		CustomerObjectsWrite << "\n"; // Перший пустий рядок

		for (const auto& element : CustomersCollection) {
			CustomerObjectsWrite << "Object " << count + 1 << ":\n";
			CustomerObjectsWrite << element->GetFullName() << "\n";
			CustomerObjectsWrite << element->GetPhoneNumber() << "\n";
			CustomerObjectsWrite << element->GetAddress() << "\n";
			CustomerObjectsWrite << element->GetNameOfCompany() << "\n";
			CustomerObjectsWrite << element->GetCountOfBoughtTrips() << "\n";
			CustomerObjectsWrite << element->GetPersonalId() << "\n"; // Id - клієнта
			
			if (element->GetStatus() != CustomerStatus::WITHOUT_TRIP) {
				if (element->GetStatus() == CustomerStatus::WITH_TRIP) 
					CustomerObjectsWrite << "Have a trip:\n"; //status
				
				else if (element->GetStatus() == CustomerStatus::DURING_A_TRIP) 
					CustomerObjectsWrite << "During a trip:\n"; //status
			
				CustomerObjectsWrite << element->GetTrip()->GetFullName() << "\n";
				CustomerObjectsWrite << element->GetTrip()->GetPersonalId() << "\n";
				CustomerObjectsWrite << element->GetNameOfManager() << "\n";
			}
			else 
				CustomerObjectsWrite << "Doesn`t have a trip" << "\n"; //status
			
			count++;
			if (count != CustomersCollection.size()) 
				CustomerObjectsWrite << "----------------------------------------------\n";
		}
	}
	CustomerObjectsWrite.close();
}

//2.9 Зчитування даних про клієнтів з файл.txt
void ReadCustomersData(ListSharedsCustomer_t& CustomersCollection, const ListSharedsTrip_t& Trips, const std::string path) {
	std::ifstream CustomerObjectsRead;
	CustomerObjectsRead.open(path, std::ios::in);

	if (!CustomerObjectsRead.is_open()) 
		std::cout << "Error: Could not open the file at the specified path to read customers data. \nSpecified path: " << path << "\n";
	else {
		std::string name, phone_number, address, name_of_company, count_of_bought_trips, personal_id, name_of_tour, trip_id, name_of_manager, status ,emptiness;

		std::getline(CustomerObjectsRead, emptiness); // зчитується перший непотрібний рядок

		if (emptiness == "Empty") {
			CustomerObjectsRead.close();
			return;
		}
		std::getline(CustomerObjectsRead, emptiness); // зчитується непотрібний рядок "Object"
		while (!CustomerObjectsRead.eof()) {

			std::getline(CustomerObjectsRead, name);
			std::getline(CustomerObjectsRead, phone_number);
			std::getline(CustomerObjectsRead, address);
			std::getline(CustomerObjectsRead, name_of_company);
			std::getline(CustomerObjectsRead, count_of_bought_trips);
			std::getline(CustomerObjectsRead, personal_id);

			std::getline(CustomerObjectsRead, status);
			if (status == "Doesn`t have a trip") 
				CustomersCollection.emplace_back(std::shared_ptr<Customer>(std::make_shared<Customer>(name, phone_number, address, std::stoi(count_of_bought_trips), std::stoi(personal_id))));
			
			else if (status == "Have a trip:" || status == "During a trip:") {
				std::getline(CustomerObjectsRead, name_of_tour);
				std::getline(CustomerObjectsRead, trip_id);
				std::getline(CustomerObjectsRead, name_of_manager);

				auto trip = FindTripById(Trips, std::stoi(trip_id));
				CustomersCollection.emplace_back(std::shared_ptr<Customer>(std::make_shared<Customer>(name, phone_number, address, std::stoi(count_of_bought_trips), std::stoi(personal_id), trip)));
			}

			if (!CustomerObjectsRead.eof()) {
				std::getline(CustomerObjectsRead, emptiness); // зчитується порожній рядок 
				std::getline(CustomerObjectsRead, emptiness); // зчитується непотрібний рядок "Object"
			}
		}
	}
	CustomerObjectsRead.close();
}



////////////////////////////////////////////////////////////////////////////////////////////////////



// Функції подорожі:


//3.1 Вивід повної інформації про путівку, для редагування даних 
void ShowFullInfoForEditTrip(const trip_list_iter_t& trip){
	std::cout << "\n\n1) Name: " << (*trip)->GetFullName();
	std::cout << "\n2) Country: " << (*trip)->GetCountry();
	std::cout << "\n3) City: " << (*trip)->GetCity();
	std::cout << "\n4) Date of start: " << (*trip)->GetDateOfStart();
	std::cout << "\n5) Date of end: " << (*trip)->GetDateOfEnd();
	std::cout << "\n6) Price: " << (*trip)->GetPrice() << " grn.";
}


//3.2 Редагування даних про путівку 
void EditTrip(trip_list_iter_t& trip, const int fieldIndex, const std::string value) {
	if ((*trip)->GetStatus() == TripStatus::USING || (*trip)->GetStatus() == TripStatus::USED || (*trip)->GetStatus() == TripStatus::EXPIRED)
		return;

	switch (fieldIndex){
	case 1:
		(*trip)->SetFullName(value);
		break;
	case 2:
		(*trip)->SetCountry(value);
		break;
	case 3:
		(*trip)->SetCity(value);
		break;
	case 4:
		(*trip)->SetDateOfStart(value);
		break;
	case 5:
		(*trip)->SetDateOfEnd(value);
		break;
	case 6:
		(*trip)->SetPrice(std::stod(value));
		break;
	default:
		break;
	}
}


//3.3 Вивід списку некуплених путівок. 
void ShowListOfUnboughtTripNames(const ListSharedsTrip_t& Trips) {
	int count = 0;
	for (auto& trip : Trips) {
		if (trip->GetStatus() == TripStatus::SELLING) {
			std::cout << count + 1 << ") ";
			std::cout << trip->GetFullName() << " (" << trip->GetCountry() << " - " << trip->GetCity() << ") \n";
			count++;
		}
	}
}


//3.4 Вивід списку куплених путівок. 
void ShowListOfPurchasedTripNames(const ListSharedsTrip_t& Trips) {
	int count = 0;
	for (auto& trip : Trips) {
		if (trip->GetStatus() == TripStatus::PURCHASED) {
			std::cout << count + 1 << ") ";
			std::cout << trip->GetFullName() << " (" << trip->GetCountry() << " - " << trip->GetCity() << ") \n";
			count++;
		}
		else if (trip->GetStatus() == TripStatus::USING) {
			std::cout << count + 1 << ") ";
			std::cout << trip->GetFullName() << " (" << trip->GetCountry() << " - " << trip->GetCity() << ") (Using) \n";
			count++;
		}
	}
}


//3.5 Отримання кількості непроданих путівок  
std::pair<size_t, std::vector<int>> GetCountOfUnboughtTrips(const ListSharedsTrip_t& Trips) {
	std::vector<int> Indices;
	int count = 0;
	int index = 0;
	for (auto& trip : Trips) {
		if (trip->GetStatus() == TripStatus::SELLING) {
			count++;
			Indices.emplace_back(index);
		}
		index++;
	}
	return std::make_pair(count, Indices);
}


//3.6 Отримання кількості проданих путівок  
std::pair<size_t, std::vector<int>> GetCountOfPurchasedTrips(const ListSharedsTrip_t& Trips){
	std::vector<int> Indices;
	int count = 0;
	int index = 0;
	for (auto& trip : Trips) {
		if (trip->GetStatus() == TripStatus::PURCHASED) {
			count++;
			Indices.emplace_back(index);
		}
		index++;
	}
	return std::make_pair(count, Indices);
}


//3.7 Отримання списку країн, проданих путівок
std::vector<std::string> GetCountriesOfBoughtTrips(const ListSharedsTrip_t& Trips, const int year, std::string path){
	std::list<std::string> Countries; // Набір країн усіх придбаних дійсних путівок 
	if (year != 0) {
		int year_of_purchase;
		for (auto& trip : Trips) {
			if ((trip->GetStatus() == TripStatus::PURCHASED || trip->GetStatus() == TripStatus::USING)) {
				year_of_purchase = std::stoi(trip->GetDateOfBooking().substr(6, 10));
				if (year_of_purchase == year)
					Countries.push_back(trip->GetCountry());
			}
		}
	}
	else { // if year == 0 -> за весь час.
		for (auto& trip : Trips) {
			if (trip->GetStatus() == TripStatus::PURCHASED || trip->GetStatus() == TripStatus::USING)
				Countries.push_back(trip->GetCountry());
		}
	}

	Countries.sort();

	// Виділення елементів кожного з повторів коллекції
	std::vector<std::string> uniqueCountries; // перелік країн (по одній)
	std::unique_copy(std::begin(Countries), std::end(Countries), std::back_inserter(uniqueCountries));
	return uniqueCountries;
}


//3.8 Отримання середнього значення тривалості путівок 
double GetAverageDurationOfTrips(const ListSharedsTrip_t& Trips, const int year, std::string path){
	std::stack<Order> Orders; // Набір  усіх замовлень 
	ReadOrdersData(Orders, path);

	std::vector<int> Durations;
	Durations.reserve(Orders.size());

	// Зчитування з усіх об'єктів "путівка"
	if (year != 0) {
		int year_of_purchase;
		for (auto& trip : Trips) {
			if ((trip->GetStatus() == TripStatus::PURCHASED || trip->GetStatus() == TripStatus::USING)) {
				year_of_purchase = std::stoi(trip->GetDateOfBooking().substr(6, 10));
				if (year_of_purchase == year)
					Durations.push_back(trip->GetDuration());
			}
		}
		while (!Orders.empty()) {
			if (Orders.top().year_of_booking == year)
				Durations.push_back(Orders.top().duration);
			Orders.pop();
		}
	}

	else { //  за весь час.
		for (auto& trip : Trips) {
			if (trip->GetStatus() == TripStatus::PURCHASED || trip->GetStatus() == TripStatus::USING)
				Durations.push_back(trip->GetDuration());
		}
		while (!Orders.empty()) {
			Durations.push_back(Orders.top().duration);
			Orders.pop();
		}
	}

	Durations.shrink_to_fit();
	if (Durations.size() == 0)
		return 0;

	return (std::accumulate(Durations.begin(), Durations.end(), 0) / Durations.size());
}


//3.9 Отримання середнього значення вартості путівок
int GetAveragePriceOfTrips(const ListSharedsTrip_t& Trips, const int year, std::string path){
	std::stack<Order> Orders; // Набір  усіх замовлень 
	ReadOrdersData(Orders, path);

	std::vector<double> Prices;
	Prices.reserve(Orders.size());

	// Зчитування з усіх об'єктів "путівка"
	if (year != 0) {
		int year_of_purchase;
		for (auto& trip : Trips) {
			if ((trip->GetStatus() == TripStatus::PURCHASED || trip->GetStatus() == TripStatus::USING)) {
				year_of_purchase = std::stoi(trip->GetDateOfBooking().substr(6, 10));
				if (year_of_purchase == year)
					Prices.push_back(trip->GetDuration());
			}
		}
		while (!Orders.empty()) {
			if (Orders.top().year_of_booking == year)
				Prices.push_back(Orders.top().price);
			Orders.pop();
		}
	}

	else { // if year == 0 -> за весь час.
		for (auto& trip : Trips) {
			if (trip->GetStatus() == TripStatus::PURCHASED || trip->GetStatus() == TripStatus::USING)
				Prices.push_back(trip->GetDuration());
		}
		while (!Orders.empty()) {
			Prices.push_back(Orders.top().price);
			Orders.pop();
		}
	}

	Prices.shrink_to_fit();
	if (Prices.size() == 0)
		return 0;

	return (std::accumulate(Prices.begin(), Prices.end(), 0) / Prices.size());
}


//3.10 Пошук дійсної путівки по id 
std::shared_ptr<Trip> FindTripById(const ListSharedsTrip_t& Trips, const int personal_id){
	for (auto trip : Trips) {
		if (trip->GetPersonalId() == personal_id)
			return trip;
	}
	return nullptr;
}


//3.11 Пошук країн, які мають найбільший попит. Повертається значення: (Країна, пара(кількість, рік))
Countries_Count_Year_AllCountYear FindMostPupularCountries(const ListSharedsTrip_t& Trips, const int year, std::string path) {
	std::stack<Order> Orders; // Набір  усіх замовлень 
	//додатково зчитуються дані про використані путівки 
	ReadOrdersData(Orders, path);

	std::list<std::string> Countries; // Набір  усіх країн

	// Зчитування усіх об'єктів "путівка"
	if (year != 0) {
		int year_of_booking;
		for (auto& trip : Trips) {
			if ((trip->GetStatus() == TripStatus::PURCHASED || trip->GetStatus() == TripStatus::USING)) {
				year_of_booking = std::stoi(trip->GetDateOfBooking().substr(6, 10));
				if (year_of_booking == year)
					Countries.push_back(trip->GetCountry());
			}
		}
		//додатково зчитуються дані про використані путівки 
		while (!Orders.empty()) {
			if (Orders.top().year_of_booking == year)
				Countries.push_back(Orders.top().country);
			Orders.pop();
		}
	}

	else { // за весь час.
		for (auto& trip : Trips) {
			if (trip->GetStatus() == TripStatus::PURCHASED || trip->GetStatus() == TripStatus::USING)
				Countries.push_back(trip->GetCountry());
		}
		//додатково зчитуються дані про використані путівки 
		while (!Orders.empty()) {
			Countries.push_back(Orders.top().country);
			Orders.pop();
		}
	}

	Countries.sort();

	// Виділення елементів кожного з повторів коллекції
	std::vector<std::string> uniqueCountries; // перелік країн (по одній)
	std::unique_copy(std::begin(Countries), std::end(Countries), std::back_inserter(uniqueCountries));

	// Знаходження найбільшої кількості серед країн, які більше всього повторюються.
	int curentIndex = 0;
	int maxRepits = 0;
	int countOfRepits = 0;

	while (curentIndex < static_cast<int>(uniqueCountries.size())) {
		countOfRepits = std::count(std::begin(Countries), std::end(Countries), uniqueCountries[curentIndex]);
		if (countOfRepits > maxRepits) {
			maxRepits = countOfRepits;
		}
		curentIndex++;
	}

	// Знаходження країн, які відповідають максимальної кількості повторень.
	std::vector<std::string> mostPopularCountries; // колекція найпопулярніших країн
	curentIndex = 0;

	while (curentIndex < static_cast<int>(uniqueCountries.size())) {

		countOfRepits = std::count(std::begin(Countries), std::end(Countries), uniqueCountries[curentIndex]);

		if (countOfRepits == maxRepits) 
			mostPopularCountries.push_back(uniqueCountries[curentIndex]);
		
		curentIndex++;
	}
	return std::make_pair(std::make_pair(mostPopularCountries, maxRepits), std::make_pair(year, Countries.size()));
}


//3.12 Вивід країн, які мають найбільший попит. 
void ShowMostPupularCountries(const Countries_Count_Year_AllCountYear& pair) {
	/*
	* pair.first.first   - коллекція найпопулярніших країн
	* pair.first.second  - кількість куплених путівок у найпопулярнішу країну
	* pair.second.first  - рік купівлі
	* pair.second.second - кількість куплених путівок за певний рік
	*/

	int size = static_cast<int>(pair.first.first.size());
	int popular_count = pair.first.second;
	int year = pair.second.first;
	int all_count = pair.second.second;

	if (pair.first.first.empty() && year != 0) {
		std::cout << "\n\nUnfortunately, in " << year << ", not a single ticket was purchased.\n";
		return;
	}

	else if (pair.first.first.empty() && year == 0) {
		std::cout << "\n\nUnfortunately, not a single ticket has been bought for all the time.\n";
		return;
	}

	else if (!pair.first.first.empty()) {
		if (year != 0)
			std::cout << "\n\nMost popular countries in " << year << " year: ";
		else
			std::cout << "\n\nMost popular countries of all time: ";

		for (int i = 0; i < size; i++) {
			if (i < (size - 1))
				std::cout << pair.first.first[i] << ", ";
			else
				std::cout << pair.first.first[i] << ";";
		}

		std::cout << "\nPurchased " << popular_count << "/" << all_count << " times;";
		return;
	}
}


//3.13 Збереження даних про путівки у файл.txt 
void SaveTripsData(const ListSharedsTrip_t& Trips, const std::string path){
	std::fstream TripObjectsWrite;
	TripObjectsWrite.open(path, std::fstream::out);
	if (!TripObjectsWrite.is_open()) {
		std::cout << "Error: Could not open the file at the specified path to record trips data. \nSpecified path: " << path << "\n";
		return;
	}

	else {
		if (Trips.empty()) {
			TripObjectsWrite << "Empty";
			TripObjectsWrite.close();
			return;
		}
		/*
	TripStatus:
		SELLING, - зберігається повністю
		PURCHASED - зберігається повністю
		USING - зберігається повністю
		USED - зберігається тільки країна та рік купівлі
		EXPIRED - не зберігається
	*/
		TripObjectsWrite << "\n"; // Перший пустий рядок

		int count = 0;

		for (const auto& trip : Trips) {
			// Якщо дата початку путівки більше ніж сьогодні
			if (trip->GetStatus() == TripStatus::SELLING || trip->GetStatus() == TripStatus::PURCHASED || trip->GetStatus() == TripStatus::USING) {
				TripObjectsWrite << "Object " << count + 1 << ":\n";
				TripObjectsWrite << trip->GetFullName() << "\n";
				TripObjectsWrite << trip->GetCountry() << "\n";
				TripObjectsWrite << trip->GetCity() << "\n";
				TripObjectsWrite << trip->GetDateOfStart() << "\n";
				TripObjectsWrite << trip->GetDateOfEnd() << "\n";
				TripObjectsWrite << trip->GetPrice() << "\n";
				TripObjectsWrite << trip->GetPersonalId() << "\n";

				if (trip->GetStatus() == TripStatus::SELLING)
					TripObjectsWrite << "Unbought" << "\n";

				else if (trip->GetStatus() == TripStatus::PURCHASED) {
					TripObjectsWrite << "Bought" << "\n";
					TripObjectsWrite << trip->GetDateOfBooking() << "\n";
					TripObjectsWrite << trip->GetNameOfCustomer() << "\n";
					TripObjectsWrite << trip->GetNameOfManager() << "\n";
				}

				else if (trip->GetStatus() == TripStatus::USING) {
					TripObjectsWrite << "Using" << "\n";
					TripObjectsWrite << trip->GetDateOfBooking() << "\n";
					TripObjectsWrite << trip->GetNameOfCustomer() << "\n";
					TripObjectsWrite << trip->GetNameOfManager() << "\n";
				}

				count++;
				if (count != Trips.size())
					TripObjectsWrite << "----------------------------------------------\n";
			}

			else if (trip->GetStatus() == TripStatus::USED)
				SaveOrderData(std::stoi(trip->GetDateOfBooking().substr(6, 10)), trip->GetCountry(), trip->GetFullName(), trip->GetNameOfCustomer(), trip->GetPrice());

			// if EXPIRED - не зберігаємо
		}
	}
	TripObjectsWrite.close();
}


//3.14 Зчитування даних про путівки з файл.txt 
void ReadTripsData(std::list<std::shared_ptr<Trip>>& Trips, const std::string path) {
	std::ifstream TripObjectsRead;
	TripObjectsRead.open(path, std::ios::in);

	if (!TripObjectsRead.is_open())
		std::cout << "Error: Could not open the file at the specified path to read customers data. \nSpecified path: " << path << "\n";
	else {
		/*
		TripStatus:
			SELLING, - зберігається повністю
			PURCHASED - зберігається повністю
			USING - зберігається повністю
			USED - зберігається тільки країна та рік купівлі
			EXPIRED - не зберігається
		*/
		std::string name, country, city, date_of_booking, date_of_start, date_of_end, price, personal_id, isBought, name_of_customer, name_of_manager, status, emptiness;

		std::getline(TripObjectsRead, emptiness); //// зчитується перший непотрібний рядок
		if (emptiness == "Empty") {
			TripObjectsRead.close();
			return;
		}
		std::getline(TripObjectsRead, emptiness); // зчитується непотрібний рядок "Object"

		while (!TripObjectsRead.eof()) {
			std::getline(TripObjectsRead, name);
			std::getline(TripObjectsRead, country);
			std::getline(TripObjectsRead, city);
			std::getline(TripObjectsRead, date_of_start);
			std::getline(TripObjectsRead, date_of_end);
			std::getline(TripObjectsRead, price);
			std::getline(TripObjectsRead, personal_id);

			std::getline(TripObjectsRead, status);
			if (status == "Unbought")  // TripStatus::SALING or EXPIRED
			{
				if (GetDateDifference(date_of_start) > 0) //TripStatus::SELLING - зберігаємо
					Trips.emplace_back(std::shared_ptr<Trip>(std::make_shared<Trip>(name, country, city, date_of_start, date_of_end, std::stod(price), std::stoi(personal_id))));
				else; //TripStatus::EXPIRED - незберігаємо

			}
			else if (status == "Bought" || status == "Using")  // TripStatus::PURCHASED or USING or USED
			{
				std::getline(TripObjectsRead, date_of_booking);
				std::getline(TripObjectsRead, name_of_customer);
				std::getline(TripObjectsRead, name_of_manager);

				if (GetDateDifference(date_of_end) < 0) //TripStatus::USED - зберігаємо тільки країну рік купівлі
					SaveOrderData(std::stoi(date_of_booking.substr(6, 10)), country, name, name_of_customer, std::stod(price));
				else
					Trips.emplace_back(std::shared_ptr<Trip>(std::make_shared<Trip>(name, country, city, date_of_start, date_of_end, std::stod(price), std::stoi(personal_id), name_of_customer, name_of_manager, date_of_booking)));
			}

			if (!TripObjectsRead.eof()) {
				std::getline(TripObjectsRead, emptiness);
				std::getline(TripObjectsRead, emptiness);
			}
		}
	}
	TripObjectsRead.close();
}
