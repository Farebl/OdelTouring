import Functions;

#include <iostream>



int main() {

    std::string history_path = "History.txt";
    std::string orders_path = "Orders.txt";


    ListSharedsManager_t managers;
    ListSharedsCustomer_t customers;
    ListSharedsTrip_t trips;


    MenuItemsHandles handles;

    MenuItem main_menu                    = MainMenu(handles);

//Managers menu items 
    MenuItem managers_menu                = ManagersMenu(handles);
    MenuItem managers_info_menu           = ManagersInfoMenu(managers, handles);
    MenuItem managers_show_full_info_menu = ShowFullInformationAboutManagerMenu(managers, handles);
    MenuItem managers_edit_info_menu      = EditInformationAboutManagerMenu(managers, "History.txt", handles);
    MenuItem managers_add_manager_menu    = AddNewManagerMenu(managers, history_path, handles);
    MenuItem managers_remove_manager_menu = RemoveManagerMenu(managers, history_path, handles);
 
    handles.main_menu                    = main_menu.get_handle();
    handles.managers_menu                = managers_menu.get_handle();
    handles.managers_info_menu           = managers_info_menu.get_handle();
    handles.managers_show_full_info_menu = managers_show_full_info_menu.get_handle();
    handles.managers_edit_info_menu      = managers_edit_info_menu.get_handle();
    handles.managers_add_manager_menu    = managers_add_manager_menu.get_handle();
    handles.managers_remove_manager_menu = managers_remove_manager_menu.get_handle();

//Customers menu items 
    MenuItem customers_menu                 = CustomersMenu(handles);
    MenuItem customers_info_menu            = CustomersInfoMenu(customers, handles);
    MenuItem customers_show_full_info_menu  = ShowFullInformationAboutCustomerMenu(customers, handles);
    MenuItem customers_edit_info_menu       = EditInformationAboutCustomerMenu(customers, "History.txt", handles);
    MenuItem customers_add_customer_menu    = AddNewCustomerMenu(customers, history_path, handles);
    MenuItem customers_remove_customer_menu = RemoveCustomerMenu(customers, history_path, handles);
 
    handles.customers_menu                 = customers_menu.get_handle();
    handles.customers_info_menu            = customers_info_menu.get_handle();
    handles.customers_show_full_info_menu  = customers_show_full_info_menu.get_handle();
    handles.customers_edit_info_menu       = customers_edit_info_menu.get_handle();
    handles.customers_add_customer_menu    = customers_add_customer_menu.get_handle();
    handles.customers_remove_customer_menu = customers_remove_customer_menu.get_handle();


// Trips menu items
    MenuItem trips_menu                        = TripsMenu(handles);
    MenuItem trips_info_menu                   = TripsInfoMenu(trips, handles);
    MenuItem trips_show_full_info_menu         = ShowFullInformationAboutTripMenu(trips, handles);
    MenuItem trips_edit_info_menu              = EditInformationAboutTripMenu(trips, history_path, handles);
    MenuItem trips_general_info_menu           = TripsGeneralInformationMenu(trips, orders_path, handles);
    MenuItem trips_info_for_specific_year_menu = TripsInformationForSpecificYearMenu(trips, orders_path, handles);
    MenuItem trips_add_trip_menu               = AddNewTripMenu(trips, history_path, handles);
    MenuItem trips_remove_trip_menu            = RemoveTripMenu(trips, history_path, handles);

    handles.trips_menu                        = trips_menu.get_handle();
    handles.trips_info_menu                   = trips_info_menu.get_handle();
    handles.trips_show_full_info_menu         = trips_show_full_info_menu.get_handle();
    handles.trips_edit_info_menu              = trips_edit_info_menu.get_handle();
    handles.trips_general_info_menu           = trips_general_info_menu.get_handle();
    handles.trips_info_for_specific_year_menu = trips_info_for_specific_year_menu.get_handle();
    handles.trips_add_trip_menu               = trips_add_trip_menu.get_handle();
    handles.trips_remove_trip_menu            = trips_remove_trip_menu.get_handle();

    try{
        ReadManagersData(managers, "Managers.txt");
        ReadTripsData(trips, "Trips.txt");
        ReadCustomersData(customers, trips, "Customers.txt");
    }
    catch(std::exception& ex){
        std::cout<< "Exception in main after reading data: " << ex.what();
    }

    try{
       handles.main_menu.resume();
    }
    catch(std::exception& ex){
        std::cout<< "Exception in interface: " << ex.what();
    }

    try{     
        SaveManagersData(managers, "Managers.txt");
        SaveTripsData(trips, "Trips.txt");
        SaveCustomersData(customers, "Customers.txt");
    }
    catch(std::exception& ex){
        std::cout<< "Exception in main after writing data: " << ex.what();
    }
	return 0;
}

// need to add exception safety
