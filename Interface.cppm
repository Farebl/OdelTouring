module;

#include <iostream>
#include <chrono>
#include <cmath>
#include <memory>

export module Functions:Interface;

import :QueryFunctions;
import Order;



std::ostream& operator<<(std::ostream& os, const std::chrono::year_month_day& ymd) {
    if (ymd.ok()) {
        os << static_cast<int>(ymd.year()) << "/"
           << static_cast<unsigned>(ymd.month()) << "/"
           << static_cast<unsigned>(ymd.day());
    } else {
        os << "Invalid Date";
    }
    return os;
}


export void Interface(ListSharedsManager_t& Managers, ListSharedsCustomer_t& Customers, ListSharedsTrip_t& Trips,
	std::string ManagersDataPath,
	std::string CustomersDataPath,
	std::string TripsDataPath,
	std::string OrdersPath,
	std::string HistoryDataPath)
{
	size_t managerIndex = 0, customerIndex = 0, tripIndex = 0, fieldIndex = 0;
	int menuItem = 0; // index of choised menu item
	int index = 0; // index of choised element/object of list 

    unsigned short input_year = 0, current_year = 0; // çì³íí³, äëÿ çáåðåæåííÿ ââåäåíîãî ðîêó

	bool try_again = false; // çì³íí³, äëÿ ïåðåâ³ðêè, ÷è áàæàº åë³ºíò ââåcòè íîâå çíà÷åííÿ ³íäåêcó
	
	// çì³íí³, äëÿ çáåðåæåííÿ âäàíèõ, ïðè còâîðåíí³ àáî ðåäàãóâàíí³ îá'ºêò³â êëàc³â
    
    std::string input_date;
    std::chrono::year_month_day date_of_start, date_of_end;

	std::string customer_name, customer_phone_number = "-", customer_address = "-", value = "-", name = "-", phone_number = "-", address = "-", country = "-", city = "-";
	double price = 0;
	int id = 0;
	
	// çì³íí³ äëÿ âçàºìîä³¿ ç îáðàíèì îá'ºòîì
	auto manager = Managers.begin(); 
	auto customer = Customers.begin();
	auto trip = Trips.begin();

	// çì³íí³, äëÿ çáåðåæåííÿ øëÿõ³â, äî ôàéë³â äàíèõ
	std::string managersDataPath = ManagersDataPath; // øëÿõ äî ôàëéó, êóäè çáåð³ãàþòücÿ äàíí³ ïðî ìåíåäæåð³â
	std::string customersDataPath = CustomersDataPath; // øëÿõ äî ôàëéó, êóäè çáåð³ãàþòücÿ äàíí³ ïðî êë³ºíò³â
	std::string tripsDataPath = TripsDataPath; // øëÿõ äî ôàëéó, êóäè çáåð³ãàþòücÿ äàíí³ ïðî ïóò³âêè
	std::string ordersPath = OrdersPath; // øëÿõ äî ôàëéó, êóäè çáåð³ãàþòücÿ äàíí³ ïðî çàìîâëåííÿ
	std::string historyDataPath = HistoryDataPath; // øëÿõ äî ôàëéó, êóäè çáåð³ãàþòücÿ äàíí³ ïðî ³còîð³þ ä³é

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
							break; //ê³íåöü case 3: Are you sure you want to close the program?
						}
					}
				} // ê³íåöü if (Managers.empty())

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
								break; //ê³íåöü case 5: Are you sure you want to close the program?
							}
						} //ê³íåöü while (true) 
					}//ê³íåöü if (managerIndex < 1 || managerIndex > Managers.size()) 

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
							break; //ê³íåöü case 4: Are you sure you want to close the program?
						}
					}// ê³íåöü while (true) ó DETAILED_INFORMATION_ABOUT_MANAGER:

					break; // ê³íåöü case 1: Show full information about the manager

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
								break; //ê³íåöü case 5: Are you sure you want to close the program?
							}
						} //ê³íåöü while (true) 
					}//ê³íåöü if (managerIndex < 1 || managerIndex > Managers.size()) 

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
									break; //ê³íåöü case 6: Are you sure you want to close the program?
								}

								break;
							} //ê³íåöü if (managerIndex < 1 || managerIndex > Managers.size()) 
						}

						if (!try_again)
							break;
						
						ClearConsole();
						std::cout << "\n\n|--- Edit information about the manager ---|\n";
						ShowFullInfoForEditManager(manager);
		
					}// ê³íåöü while (true) - Select the number of the manager you want to see full information about:

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
										break; //ê³íåöü case 7: Are you sure you want to close the program?
									}

									break;
								} //ê³íåöü if (managerIndex < 1 || managerIndex > Managers.size()) 
							}

							if (!try_again)
								break;

							ClearConsole();
							std::cout << "\n\n|--- Edit information about the manager ---|\n";

							std::cout << "\n1) Surname: " << (*manager)->GetSecondName();
							std::cout << "\n2) Name: " << (*manager)->GetFirstName();
							std::cout << "\n3) Patronymic: " << (*manager)->GetPatronymicName();


						}// ê³íåöü while (true) - Select the number of the manager you want to see full information about:

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
							break; //ê³íåöü case 5: Are you sure you want to close the program?
						}

					}// ê³íåöü case 2: - No - while (true) ó DETAILED_INFORMATION_ABOUT_MANAGER

					break;  // ê³íåöü case 2: Edit information about the manager

				case 3: // case 3: Back to MANAGERS
					ClearConsole();
					goto MANAGERS;
					break; //ê³íåöü case 3: Back to MANAGERS

				case 4: // case 4: Back to the main menu
				default:
					ClearConsole();
					goto MAIN;
					break; //ê³íåöü case 4: Back to the main menu

				case 5: // case 5: Close the program
					ClearConsole();
					return;
					break; //ê³íåöü case 5: Close the program
				}

				break; //ê³íåöü case 1: List of managers (full info/edit)

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
							break; //ê³íåöü case 3: Are you sure you want to close the program?
						}
					}
				} // ê³íåöü if (Managers.empty())

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
						break; //ê³íåöü case 4: Are you sure you want to close the program?
					}

				}// ê³íåöü case 2: - No - while (true) ó DETAILED_INFORMATION_ABOUT_MANAGER

				break; //ê³íåöü case 2: Count of managers

			case 3: // case 3: Back to MANAGERS
				ClearConsole();
				goto MANAGERS;
				break; //ê³íåöü case 3: Back to MANAGERS

			case 4: // case 4: Back to the main menu
			default:
				ClearConsole();
				goto MAIN;
				break; //ê³íåöü case 4: Back to the main menu

			case 5: // case 5: Close the program
				ClearConsole();
				return;
				break; //ê³íåöü case 5: Close the program
			}
		
			break; //ê³íåöü case 1: Information

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
							break; //ê³íåöü case 3: Are you sure you want to close the program?
						}
					}
				} // ê³íåöü if (Managers.empty())

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

							break;  //ê³íåöü case 3: Are you sure you want to close the program?
						}
					}
				} // ê³íåöü if (GetCountOfCustomersWithoutTrip(Customers) == 0)

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

							break;  //ê³íåöü case 4: Are you sure you want to close the program?
						}
					}
				} // ê³íåöü if (GetCountOfUnboughtTrips(Trips)  == 0)

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

							break; //ê³íåöü case 4: Are you sure you want to close the program?
						}
					} //ê³íåöü while (true) 
				}//ê³íåöü if (managerIndex < 1 || managerIndex > Managers.size()) 

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
								break; //ê³íåöü case 5: Are you sure you want to close the program?
							}

							break;
						} //ê³íåöü if (managerIndex < 1 || managerIndex > Managers.size()) 
					}

					if (!try_again)
						break;

					ClearConsole();
					std::cout << "\n\n|--- Making a trip purchase ---|\n";
					std::cout << "\nCustomers: \n";
					ShowListOfCustomersWithoutTripNames(Customers);

				}// ê³íåöü while (true) - Select the number of the manager you want to see full information about:

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
								break; //ê³íåöü case 5: Are you sure you want to close the program?
							}
							
							break;
						} //ê³íåöü if (managerIndex < 1 || managerIndex > Managers.size()) 
					}

					if (!try_again)
						break;

					ClearConsole();
					std::cout << "\n\n|--- Making a trip purchase ---|\n";
					std::cout << "\nTrips: \n";
					ShowListOfUnboughtTripNames(Trips);

				}// ê³íåöü while (true) - Select the number of the manager you want to see full information about:
				
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
						break;  //ê³íåöü case 4: Are you sure you want to close the program?
					}
				}// ê³íåöü while(true)

				break;//ê³íåöü case 1:  Make a tour purchase

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

							break; //ê³íåöü case 3: Are you sure you want to close the program?
						}
					}
				} // ê³íåöü if (Managers.empty())
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

							break;  //ê³íåöü case 3: Are you sure you want to close the program?
						}
					}
				} // ê³íåöü if (GetCountOfCustomersWithTrip(Customers) == 0)

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
							break; //ê³íåöü case 4: Are you sure you want to close the program?
						}
					} //ê³íåöü while (true) 
				}//ê³íåöü if (managerIndex < 1 || managerIndex > Managers.size()) 
				
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
								break; //ê³íåöü case 5: Are you sure you want to close the program?
							}

							break;
						} //ê³íåöü if (managerIndex < 1 || managerIndex > Managers.size()) 
					}

					if (!try_again)
						break;

					ClearConsole();
					std::cout << "\n\n|--- Making a trip refound ---|\n";
					std::cout << "\nCustomers: \n";
					ShowListOfCustomersWithTripNames(Customers);

				}// ê³íåöü while (true) - Select the number of the manager you want to see full information about:
			
				customerIndex = GetCountOfCustomersWithTrip(Customers).second[customerIndex - 1];
				customer = Customers.begin();
				std::advance(customer, customerIndex);

				//íàçâà ïóò³âêè
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

						break;  //ê³íåöü case 4: Are you sure you want to close the program?
					}
				}// ê³íåöü while(true)

				break;//ê³íåöü case 1:  Make a tour refund

			case 3: // case 3: Back to MANAGERS
				ClearConsole();
				goto MANAGERS;
				break; //ê³íåöü case 3: Back to MANAGERS

			case 4: // case 4: Back to the main menu
			default:
				ClearConsole();
				goto MAIN;
				break; //ê³íåöü case 4: Back to the main menu

			case 5: // case 5: Close the program
				ClearConsole();
				return;
				break; //ê³íåöü case 5: Close the program
			}

			break; //ê³íåöü case 2: Orders

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

					break;  //ê³íåöü case 4: Are you sure you want to close the program?
				}
			}// ê³íåöü while(true)

			break; //ê³íåöü case 3: Add new manager
		
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
						break; //ê³íåöü case 3: Are you sure you want to close the program?
					}
				}
			} // ê³íåöü if (Managers.empty())

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
						break; //ê³íåöü case 4: Are you sure you want to close the program?
					}
				} //ê³íåöü while (true) 
			}//ê³íåöü if (managerIndex < 1 || managerIndex > Managers.size()) 

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

					break;  //ê³íåöü case 4: Are you sure you want to close the program?
				}
			}// ê³íåöü while(true)

			break; //ê³íåöü  case 4: Remove manager

		case 5: // case 5: Back to the main menu
		default:
			ClearConsole();
			goto MAIN;
			break; //ê³íåöü case 5: Back to the main menu

		case 6: // case 5: Close the program
			ClearConsole();
			return;
			break; //ê³íåöü case 5: Close the program
		}

		break; //ê³íåöü case 1: Managers

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
							break; //ê³íåöü case 3: Are you sure you want to close the program?
						}
					}
				} // ê³íåöü if (Customers.empty())

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
								break; //ê³íåöü case 5: Are you sure you want to close the program?
							}
						} //ê³íåöü while (true) 
					}//ê³íåöü if (customerIndex < 1 || customerIndex > Customers.size()) 

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
							break; //ê³íåöü case 4: Are you sure you want to close the program?
						}
					}// ê³íåöü while (true) ó DETAILED_INFORMATION_ABOUT_MANAGER:

					break; // ê³íåöü case 1: Show full information about the customer

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
								break; //ê³íåöü case 5: Are you sure you want to close the program?
							}
						} //ê³íåöü while (true) 
					}//ê³íåöü if (customerIndex < 1 || customerIndex > Customers.size())

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
									break; //ê³íåöü case 5: Are you sure you want to close the program?
								}
						
								break;
							} //ê³íåöü if (fieldIndex < 1 || fieldIndex > 4)
						}

						if (!try_again)
							break;

						ClearConsole();
						std::cout << "\n\n|--- Edit information about the customer ---|\n";
						ShowFullInfoForEditCustomer(customer);

					}// ê³íåöü while (true) - Select the number of the field, that you want to edit: :

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
										break; //ê³íåöü case 5: Are you sure you want to close the program?
									}

									break;
								} //ê³íåöü if (customerIndex < 1 ||customerIndex > Managers.size()) 
							}

							if (!try_again)
								break;

							ClearConsole();
							std::cout << "\n\n|--- Edit information about the customer ---|\n";

							std::cout << "\nSurname: " << (*customer)->GetSecondName();
							std::cout << "\nName: " << (*customer)->GetFirstName();
							std::cout << "\nPatronymic: " << (*customer)->GetPatronymicName();

						}// ê³íåöü while (true) - Select the number of the manager you want to see full information about:
						
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
							break; //ê³íåöü case 5: Are you sure you want to close the program?
						}

					}// ê³íåöü case 2: - No - while (true) ó DETAILED_INFORMATION_ABOUT_MANAGER

					break;  // ê³íåöü case 2: Edit information about the manager

				case 3: // case 3: Back to CUSTOMERS
					ClearConsole();
					goto CUSTOMERS;
					break; //ê³íåöü case 3: Back to CUSTOMERS

				case 4: // case 4: Back to the main menu
				default:
					ClearConsole();
					goto MAIN;
					break; //ê³íåöü case 4: Back to the main menu

				case 5: // case 5: Close the program
					ClearConsole();
					return;
					break; //ê³íåöü case 5: Close the program
				}

				break; //ê³íåöü case 1: List of customer (full info/edit)

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
							break; //ê³íåöü case 3: Are you sure you want to close the program?
						}
					}
				} // ê³íåöü if (Customers.empty())

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

							break;  //ê³íåöü case 3: Are you sure you want to close the program?
						}
					}
				} // ê³íåöü if (GetCountOfCustomersWithTrip(Customers) == 0)

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
							break; //ê³íåöü case 3: Are you sure you want to close the program?
						}
					}// ê³íåöü while (true) ó DETAILED_INFORMATION_ABOUT_MANAGER:
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
							break; //ê³íåöü case 5: Are you sure you want to close the program?
						}
					} //ê³íåöü while (true) 
				}//ê³íåöü if (customerIndex < 1 || customerIndex > Customers.size()) 

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
						break; //ê³íåöü case 4: Are you sure you want to close the program?
					}
				}// ê³íåöü while (true) ó DETAILED_INFORMATION_ABOUT_MANAGER:

				break; //ê³íåöü case 2: List of customers by trip`s country 

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
							break; //ê³íåöü case 3: Are you sure you want to close the program?
						}
					}
				} // ê³íåöü if (Customers.empty())

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
						break; //ê³íåöü case 3: Are you sure you want to close the program?
					}

				}// ê³íåöü case 2: - No - while (true) ó DETAILED_INFORMATION_ABOUT_MANAGER

				break; //ê³íåöü case 2: Count of managers

			case 4: // case 3: Back to Customers
				ClearConsole();
				goto CUSTOMERS;
				break; //ê³íåöü case 3: Back to Customers

			case 5: // case 5: Back to the main menu
			default:
				ClearConsole();
				goto MAIN;
				break; //ê³íåöü case 5: Back to the main menu

			case 6: // case 6: Close the program
				ClearConsole();
				return;
				break; //ê³íåöü case 6: Close the program
			}

			break; //ê³íåöü case 1: Information

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
						break; //ê³íåöü case 4: Are you sure you want to close the program?
					}
					
					break;
				}
			} // ê³íåöü if (Managers.empty())
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
                       
                        try_again = true;
                        while (try_again){
                            std::cout << "\nEnter trip`s date of start (yyyy/mm/dd): ";
                            if (std::cin >> input_date) {
                                try{
                                    date_of_start = stringToYearMonthDay(input_date);

                                    if (date_of_start.ok()) {
                                        Trips.back()->SetDateOfStart(date_of_start);
                                        try_again = false;
                                    } 
                                    else {
                                        std::cout << "Error: Invalid calendar date entered! Try again\n";
                                    }
                                }
                                catch(std::exception& ex){
                                    std::cout<<ex.what();
                                }
                            } 
                            else {
                                std::cout << "Error: Wrong input format!\n";
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            }
                        }


                        try_again = true;
                        while (try_again){
<<<<<<< Updated upstream
                            std::cout << "\nEnter trip`s date of start (yyyy/mm/dd): ";
=======
                            std::cout << "\nEnter trip`s date of end (yyyy/mm/dd): ";
>>>>>>> Stashed changes
                            if (std::cin >> input_date) {
                                try{
                                    date_of_end = stringToYearMonthDay(input_date);

<<<<<<< Updated upstream
                                    if (date_of_start.ok()) {
=======
                                    if (date_of_end.ok()) {
>>>>>>> Stashed changes
                                        Trips.back()->SetDateOfEnd(date_of_end);
                                        try_again = false;
                                    } 
                                    else {
                                        std::cout << "Error: Invalid calendar date entered! Try again\n";
                                    }
                                }
                                catch(std::exception& ex){
                                    std::cout<<ex.what();
                                }
                            } 
                            else {
                                std::cout << "Error: Wrong input format!\n";
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            }
                        }
                        
                        try_again = true;
					    while (try_again){
                            std::cout << "\nEnter trip`s price (grn.): ";
                            ValidatedInput(price);
                            if (price > 0) {try_again = false;}
                        }
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
						break; //ê³íåöü case 4: Are you sure you want to close the program?
					}
					break;
				}
			} // ê³íåöü if (GetCountOfUnboughtTrips(Trips)  == 0)


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
							break; //ê³íåöü case 5: Are you sure you want to close the program?
						}
					
						break;																		
					} //ê³íåöü if (managerIndex < 1 || managerIndex > Managers.size()) 
				}

				if (!try_again)
					break;

				ClearConsole();
				std::cout << "\n\n|--- Add new customer ---|\n";
				std::cout << "\n\nManagers: \n";
				ShowListOfCollectionElementNames(Managers);

			}// ê³íåöü while (true) - Select the number of the manager you want to see full information about:

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
							break; //ê³íåöü case 5: Are you sure you want to close the program?
						}

						break;					
					} //ê³íåöü if (managerIndex < 1 || managerIndex > Managers.size()) 
				}

				if (!try_again)
					break;

				ClearConsole();
				std::cout << "\n\n|--- Add new customer ---|\n";
				std::cout << "\nTrips: \n";
				ShowListOfUnboughtTripNames(Trips);

			}// ê³íåöü while (true) - Select the number of the manager you want to see full information about:

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

					break;  //ê³íåöü case 4: Are you sure you want to close the program?
				}
			}// ê³íåöü while(true)

			break; //ê³íåöü case 2: Add new customer

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

						break;  //ê³íåöü case 3: Are you sure you want to close the program?
					}
				}
			} // ê³íåöü if (GetCountOfCustomersWithoutTrip(Customers) == 0)

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

						break;  //ê³íåöü case 4: Are you sure you want to close the program?
					}
				} //ê³íåöü while (true) 
			}//ê³íåöü if (managerIndex < 1 || managerIndex > Managers.size()) 

			
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

					break;  //ê³íåöü case 4: Are you sure you want to close the program?
				}
			}// ê³íåöü while(true)

			break; //ê³íåöü case 3: Remove customer

		case 4: // case 4: Back to \"Main menu\""
		default:
			ClearConsole();
			goto MAIN;
			break; //ê³íåöü case 4: Back to \"Main menu\""

		case 5: // case 5: Close the program
			ClearConsole();
			return;
			break; //ê³íåöü case 5: Close the program
		}

		break; //ê³íåöü case 2: Customers
	
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
							break; //ê³íåöü case 3: Are you sure you want to close the program?
						}
					}
				} // ê³íåöü if (Customers.empty())

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
								break; //ê³íåöü case 5: Are you sure you want to close the program?
							}
						} //ê³íåöü while (true) 
					}//ê³íåöü if (customerIndex < 1 || customerIndex > Customers.size()) 

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
							break; //ê³íåöü case 4: Are you sure you want to close the program?
						}
					}// ê³íåöü while (true) ó DETAILED_INFORMATION_ABOUT_MANAGER:

					break; // ê³íåöü case 1: Show full information about the customer

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
								break; //ê³íåöü case 3: Are you sure you want to close the program?
							}
						}
					} // ê³íåöü if (Customers.empty())
					
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
								break; //ê³íåöü case 5: Are you sure you want to close the program?
							}
						} //ê³íåöü while (true) 
					}//ê³íåöü if (customerIndex < 1 || customerIndex > Customers.size())

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
									break; //ê³íåöü case 5: Are you sure you want to close the program?
								}

								break;							
							} //ê³íåöü if (fieldIndex < 1 || fieldIndex > 4)
						}

						if (!try_again)
							break;

						ClearConsole();
						std::cout << "\n\n|--- Edit information about the trip ---|\n";
						ShowFullInfoForEditTrip(trip);


					}// ê³íåöü while (true) - Select the number of the field, that you want to edit: :

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

							break;  //ê³íåöü case 5: Are you sure you want to close the program?
						}
					}// ê³íåöü while (true)

					break;  // ê³íåöü case 2: Edit information about the manager

				case 3: // case 3: Back to CUSTOMERS
					ClearConsole();
					goto CUSTOMERS;
					break; //ê³íåöü case 3: Back to CUSTOMERS

				case 4: // case 4: Back to the main menu
				default:
					ClearConsole();
					goto MAIN;
					break; //ê³íåöü case 4: Back to the main menu

				case 5: // case 5: Close the program
					ClearConsole();
					return;
					break; //ê³íåöü case 5: Close the program
				}

				break; //ê³íåöü case 1: Trips get information

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
							break; //ê³íåöü case 3: Are you sure you want to close the program?
						}
					}
				} // ê³íåöü if (Customers.empty())
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
       
					current_year = static_cast<unsigned short>(
                                        static_cast<int>(
                                            std::chrono::year_month_day{
                                                floor<std::chrono::days>(std::chrono::system_clock::now())
                                            }.year()
                                        )
                                    );

					std::cout << "\nEnter the year you are interested in (recomended  2021 - " << current_year << "): ";
					ValidatedInput(input_year);
					
					if (input_year > current_year) {
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
								break; //ê³íåöü case 3: Are you sure you want to close the program?
							}

						}// ê³íåöü case 2: - No - while (true) ó DETAILED_INFORMATION_ABOUT_MANAGER
					}
					if (input_year < current_year && input_year < 2021) {
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
								break; //ê³íåöü case 3: Are you sure you want to close the program?
							}

						}// ê³íåöü case 2: - No - while (true) ó DETAILED_INFORMATION_ABOUT_MANAGER
					}

					ClearConsole();

					std::cout << "\n\n|--- General information about trips ---|\n";
					std::cout << "\nGeneral information for " << input_year << " year:";
					if (input_year == current_year)
						std::cout << "\n\tCount of sold trips: " << GetCountOfOrders(input_year) + GetCountOfPurchasedTrips(Trips).first;
					else if (input_year < current_year && input_year >= 2021)
						std::cout << "\n\tCount of sold trips: " << GetCountOfOrders(input_year);
					
					std::cout << "\n\tAverage duration of the trip: ";
					if ((std::ceil(GetAverageDurationOfTrips(Trips, input_year)) - GetAverageDurationOfTrips(Trips, input_year)) > 0.5)
						std::cout << std::floor(GetAverageDurationOfTrips(Trips, input_year)) << " days ";
					else
						std::cout << std::ceil(GetAverageDurationOfTrips(Trips, input_year)) << " days";

					std::cout << "\n\tAverage cost of the trip: " << GetAveragePriceOfTrips(Trips, input_year) << " UAH";
					
					ShowMostPupularCountries(FindMostPupularCountries(Trips, input_year));

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
							break; //ê³íåöü case 3: Are you sure you want to close the program?
						}

					}// ê³íåöü case 2: - No - while (true) ó DETAILED_INFORMATION_ABOUT_MANAGER

					break; // ê³íåöü case 1: yes - see a general information about trips for a specific year

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
							break; //ê³íåöü case 3: Are you sure you want to close the program?
						}

					}// ê³íåöü case 2: - No - while (true) ó DETAILED_INFORMATION_ABOUT_MANAGER
					break;// ê³íåöü case 1: no
				}

				break; //ê³íåöü case 2: General information

			case 3: // case 3: Back to TRIPS
				ClearConsole();
				goto TRIPS;
				break; //ê³íåöü case 3: Back to TRIPS

			case 4: // case 4: Back to the main menu
			default:
				ClearConsole();
				goto MAIN;
				break; //ê³íåöü case 4: Back to the main menu

			case 5: // case 5: Close the program
				ClearConsole();
				return;
				break; //ê³íåöü case 5: Close the program
			}

			break; //ê³íåöü case 1: Information

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
           
            try_again = true;
            while (try_again){
                std::cout << "\nEnter trip`s date of start (yyyy/mm/dd): ";
                if (std::cin >> input_date) {
                    try{
                        date_of_start = stringToYearMonthDay(input_date);

                        if (date_of_start.ok()) {
                            Trips.back()->SetDateOfStart(date_of_start);
                            try_again = false;
                        } 
                        else {
                            std::cout << "Error: Invalid calendar date entered! Try again\n";
                        }
                    }
                    catch(std::exception& ex){
                        std::cout<<ex.what();
                    }
                } 
                else {
                    std::cout << "Error: Wrong input format!\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }


                  
            try_again = true;
            while (try_again){
<<<<<<< Updated upstream
                std::cout << "\nEnter trip`s date of start (yyyy/mm/dd): ";
=======
                std::cout << "\nEnter trip`s date of end (yyyy/mm/dd): ";
>>>>>>> Stashed changes
                if (std::cin >> input_date) {
                    try{
                        date_of_end = stringToYearMonthDay(input_date);

<<<<<<< Updated upstream
                        if (date_of_start.ok()) {
=======
                        if (date_of_end.ok()) {
>>>>>>> Stashed changes
                            Trips.back()->SetDateOfEnd(date_of_end);
                            try_again = false;
                        } 
                        else {
                            std::cout << "Error: Invalid calendar date entered! Try again\n";
                        }
                    }
                    catch(std::exception& ex){
                        std::cout<<ex.what();
                    }
                } 
                else {
                    std::cout << "Error: Wrong input format!\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            
            try_again = true;
            while (try_again){
                std::cout << "\nEnter trip`s price (grn.): ";
                ValidatedInput(price);
                if (price > 0) {try_again = false;}
            }
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

					break;  //ê³íåöü case 4: Are you sure you want to close the program?
				}
			}// ê³íåöü while(true)

			break; //ê³íåöü case 2: Add new trip

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

						break;  //ê³íåöü case 3: Are you sure you want to close the program?
					}
				}
			} // ê³íåöü if (GetCountOfCustomersWithoutTrip(Customers) == 0)

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

						break;  //ê³íåöü case 4: Are you sure you want to close the program?
					}
				} //ê³íåöü while (true) 
			}//ê³íåöü if (managerIndex < 1 || managerIndex > Managers.size()) 


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

					break;  //ê³íåöü case 4: Are you sure you want to close the program?
				}
			}// ê³íåöü while(true)

			break; //ê³íåöü case 3: Remove trip
		
		case 4: // case 4: Back to the MAIN
		default:
			ClearConsole();
			goto MAIN;
			break; //ê³íåöü case 4: Back to the MAIN

		case 5: // case 5: Close the program
			ClearConsole();
			return;
			break; //ê³íåöü case 5: Close the program
		}
		break; //ê³íåöü case 3: Trips

case 4: // case 4: Close the program
	return;
	break; //ê³íåöü case 4: Close the program
	}

}

