import Functions;

#include <iostream>



int main() {

    ListSharedsManager_t Managers;
    ListSharedsCustomer_t Customers;
    ListSharedsTrip_t Trips;


    MenuItemsHandles handles;

    MenuItem main_menu                    = MainMenu(handles);

//Managers menu items 
    MenuItem managers_menu                = ManagersMenu(handles);
    MenuItem managers_info_menu           = ManagersInfoMenu(Managers, handles);
    MenuItem managers_show_full_info_menu = ShowFullInformationAboutManagerMenu(Managers, handles);
    MenuItem managers_edit_info_menu      = EditInformationAboutManagerMenu(Managers, "History.txt", handles);
    MenuItem managers_add_manager_menu    = AddNewManagerMenu(Managers, "History.txt", handles);
    MenuItem managers_remove_manager_menu = RemoveManagerMenu(Managers, "History.txt", handles);
 
    handles.main_menu                    = main_menu.get_handle();
    handles.managers_menu                = managers_menu.get_handle();
    handles.managers_info_menu           = managers_info_menu.get_handle();
    handles.managers_show_full_info_menu = managers_show_full_info_menu.get_handle();
    handles.managers_edit_info_menu      = managers_edit_info_menu.get_handle();
    handles.managers_add_manager_menu    = managers_add_manager_menu.get_handle();
    handles.managers_remove_manager_menu = managers_remove_manager_menu.get_handle();

//Customers menu items 
    MenuItem customers_menu                 = CustomersMenu(handles);
    MenuItem customers_info_menu            = CustomersInfoMenu(Customers, handles);
    MenuItem customers_show_full_info_menu  = ShowFullInformationAboutCustomerMenu(Customers, handles);
    MenuItem customers_edit_info_menu       = EditInformationAboutCustomerMenu(Customers, "History.txt", handles);
    MenuItem customers_add_customer_menu    = AddNewCustomerMenu(Customers, "History.txt", handles);
    MenuItem customers_remove_customer_menu = RemoveCustomerMenu(Customers, "History.txt", handles);
 
    handles.customers_menu                 = customers_menu.get_handle();
    handles.customers_info_menu            = customers_info_menu.get_handle();
    handles.customers_show_full_info_menu  = customers_show_full_info_menu.get_handle();
    handles.customers_edit_info_menu       = customers_edit_info_menu.get_handle();
    handles.customers_add_customer_menu    = customers_add_customer_menu.get_handle();
    handles.customers_remove_customer_menu = customers_remove_customer_menu.get_handle();

    try{
        ReadManagersData(Managers, "Managers.txt");
        ReadTripsData(Trips, "Trips.txt");
        ReadCustomersData(Customers, Trips, "Customers.txt");
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
        SaveManagersData(Managers, "Managers.txt");
        SaveTripsData(Trips, "Trips.txt");
        SaveCustomersData(Customers, "Customers.txt");
    }
    catch(std::exception& ex){
        std::cout<< "Exception in main after writing data: " << ex.what();
    }
	return 0;
}

// need to add exception safety
