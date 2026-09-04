module;

#include <cmath>
#include <coroutine>
#include <string>

export module Functions:NewInterface;

import :QueryFunctions;
import Order;




/*
MENU:

Main
|---Managers
|   |---Information
|   |   |---Show full information about the manager
|   |   |---Edit information about the manager
|	|	|---Back to Managers
|   |	|---Go to Main menu
|	|	|---Close the program
|   |
|	|---Add new manager
|	|	|---Back to Managers
|   |	|---Go to Main menu
|	|	|---Close the program
|   |
|	|---Remove manager
|	|	|---Back to Managers
|   |	|---Go to Main menu
|	|	|---Close the program
|   |
|	|---Back to the main menu
|	|---Close the program
|
|---Customers 
|   |---Information
|   |   |---Show full information about the customer
|   |   |---Edit information about the customer
|   |   |---List of customers by trip`s country
|	|	|---Back to Customers 
|   |	|---Go to Main menu
|	|	|---Close the program
|   |
|	|---Add new customer
|	|	|---Back to Customers 
|   |	|---Go to Main menu
|	|	|---Close the program
|   |
|	|---Remove customer
|	|	|---Back to Customers 
|   |	|---Go to Main menu
|	|	|---Close the program
|   |
|	|---Back to the main menu
|	|---Close the program
|
|---Trips
|   |---Information
|   |   |---Show full information about the trip
|   |   |---Edit information about the trip
|   |   |---General information
|	|	|---Back to Trips
|   |	|---Go to Main menu
|	|	|---Close the program
|   |
|	|---Add new trip
|	|	|---Back to Trips 
|   |	|---Go to Main menu
|	|	|---Close the program
|   |
|	|---Remove trip
|	|	|---Back to Trips 
|   |	|---Go to Main menu
|	|	|---Close the program
|   |
|	|---Back to the main menu
|	|---Close the program

|---Orders (not ready)
|
|---Close the program
*/



export struct MenuItemsHandles;

export struct MenuItem {
    struct promise_type {
        using coro_handle = std::coroutine_handle<promise_type>;
        
        MenuItem get_return_object();
        
        auto initial_suspend();
        auto final_suspend() noexcept;
        void return_void();
        void unhandled_exception(); 
    };

    using coro_handle = promise_type::coro_handle;
    
    MenuItem(coro_handle handle);
    MenuItem(const MenuItem&) = delete;
    MenuItem(MenuItem&& other) noexcept;
    ~MenuItem();

    std::coroutine_handle<> get_handle() const;

private:
    coro_handle m_handle;
};


export struct MenuItemsHandles {
    std::coroutine_handle<> main_menu;
    std::coroutine_handle<> managers_menu;
        std::coroutine_handle<> managers_info_menu;
            std::coroutine_handle<> managers_show_full_info_menu;
            std::coroutine_handle<> managers_edit_info_menu;
        std::coroutine_handle<> managers_add_manager_menu;
        std::coroutine_handle<> managers_remove_manager_menu;

    std::coroutine_handle<> customers_menu;
        std::coroutine_handle<> customers_info_menu;
            std::coroutine_handle<> customers_show_full_info_menu;
            std::coroutine_handle<> customers_edit_info_menu;
            std::coroutine_handle<> customers_list_by_trip_country_menu;
        std::coroutine_handle<> customers_add_customer_menu;
        std::coroutine_handle<> customers_remove_customer_menu;

    std::coroutine_handle<> trips_menu;
        std::coroutine_handle<> trips_info_menu;
            std::coroutine_handle<> trips_show_full_info_menu;
            std::coroutine_handle<> trips_edit_info_menu;
            std::coroutine_handle<> trips_general_info_menu;
                std::coroutine_handle<> trips_info_for_specific_year_menu;
        std::coroutine_handle<> trips_add_trip_menu;
        std::coroutine_handle<> trips_remove_trip_menu;
};





export MenuItem MainMenu(const MenuItemsHandles& handles);

// Managers menu
export MenuItem ManagersMenu(const MenuItemsHandles& handles);
export MenuItem ManagersInfoMenu(ListSharedsManager_t& managers, const MenuItemsHandles& handles);
export MenuItem ShowFullInformationAboutManagerMenu(const ListSharedsManager_t& managers, const MenuItemsHandles& handles);
export MenuItem EditInformationAboutManagerMenu(const ListSharedsManager_t& managers, const std::string& historyDataPath, const MenuItemsHandles& handles);
export MenuItem AddNewManagerMenu(ListSharedsManager_t& managers, const std::string& historyDataPath, const MenuItemsHandles& handles);
export MenuItem RemoveManagerMenu(ListSharedsManager_t& managers, const std::string& historyDataPath, const MenuItemsHandles& handles);

// Customers menu
export MenuItem CustomersMenu(const MenuItemsHandles& handles);
export MenuItem CustomersInfoMenu(ListSharedsCustomer_t& customers, const MenuItemsHandles& handles);
export MenuItem ShowFullInformationAboutCustomerMenu(const ListSharedsCustomer_t& customers, const MenuItemsHandles& handles);
export MenuItem EditInformationAboutCustomerMenu(const ListSharedsCustomer_t& customers, const std::string& historyDataPath, const MenuItemsHandles& handles);
export MenuItem ListOfCustomersByTripsCountryMenu(const ListSharedsCustomer_t& customers, const ListSharedsTrip_t& trips, const MenuItemsHandles& handles);
export MenuItem AddNewCustomerMenu(ListSharedsCustomer_t& customers, const std::string& historyDataPath, const MenuItemsHandles& handles);
export MenuItem RemoveCustomerMenu(ListSharedsCustomer_t& customers, const std::string& historyDataPath, const MenuItemsHandles& handles);

// Trips menu
export MenuItem TripsMenu(const MenuItemsHandles& handles);
export MenuItem TripsInfoMenu(ListSharedsTrip_t& trips, const MenuItemsHandles& handles);
export MenuItem ShowFullInformationAboutTripMenu(const ListSharedsTrip_t& trips, const MenuItemsHandles& handles);
export MenuItem EditInformationAboutTripMenu(const ListSharedsTrip_t& trips, const std::string& historyDataPath, const MenuItemsHandles& handles);
export MenuItem TripsGeneralInformationMenu(const ListSharedsTrip_t& trips, std::string orders_path, const MenuItemsHandles& handles);
export MenuItem TripsInformationForSpecificYearMenu(const ListSharedsTrip_t& trips, std::string orders_path, const MenuItemsHandles& handles);
export MenuItem AddNewTripMenu(ListSharedsTrip_t& trips, const std::string& historyDataPath, const MenuItemsHandles& handles);
export MenuItem RemoveTripMenu(ListSharedsTrip_t& trips, const std::string& historyDataPath, const MenuItemsHandles& handles);
