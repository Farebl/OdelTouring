module;

#include <iostream>
#include <string>
#include <cmath>
#include <memory>
#include <coroutine>
#include <chrono>

module Functions; 
import :QueryFunctions; 




//////////////////// COROUTINE STRUCTS //////////////////////////



struct SwitchTo {
    std::coroutine_handle<> m_target_handle;
    SwitchTo(std::coroutine_handle<> handle) : m_target_handle(handle){}

    bool await_ready() const noexcept { return false; }

    std::coroutine_handle<> await_suspend(std::coroutine_handle<>) const noexcept {
        return m_target_handle;
    }

    void await_resume() const noexcept {}
};



MenuItem MenuItem::promise_type::get_return_object() { return MenuItem{ coro_handle::from_promise(*this) }; }
auto MenuItem::promise_type::initial_suspend() { return std::suspend_always{}; }
auto MenuItem::promise_type::final_suspend() noexcept { return std::suspend_always{}; }
void MenuItem::promise_type::return_void() {}
void MenuItem::promise_type::unhandled_exception() { throw; }


MenuItem::MenuItem(coro_handle handle) : m_handle(handle){}
MenuItem::MenuItem(MenuItem&& other) noexcept : m_handle(other.m_handle) {other.m_handle = nullptr;   }
MenuItem::~MenuItem() {if (m_handle) m_handle.destroy(); }
std::coroutine_handle<> MenuItem::get_handle() const { return m_handle; }

   




//////////////////// HELP GUI FUNCTIONS //////////////////////////

void StopInterface(){
    throw std::logic_error{"stop signal"};
}

bool ConfirmationOfProgramCompletionMenu(){
    size_t menu_item = 0;
    std::cout << "\n\nAre you sure you want to close the program?";
    std::cout << "\n1) Yes";
    std::cout << "\n2) No (or any other input except \"1\")";

    std::cout << "\n\nEnter item number: ";
    ValidatedInput(menu_item);
    switch (menu_item) {
        case 1: return true; 
        default: return false;
    }
}







///////////////// MENU ITEMS COROUTINES ////////////////////////////





MenuItem MainMenu(const MenuItemsHandles& handles){
    size_t menu_item = 0; 

    while (true) {
        ClearConsole();
        std::cout << "\n\n|--- Main menu ---|\n";

        std::cout << "\n1) Managers ";
        std::cout << "\n2) Customers ";
        std::cout << "\n3) Trips";
        std::cout << "\n4) Order or return";
        std::cout << "\n5) Close the program";

        std::cout << "\n\nEnter item number: ";
        ValidatedInput(menu_item);        
        switch(menu_item){
            case 1: 
                co_await SwitchTo{ handles.managers_menu };  
                break;

            case 2:
                co_await SwitchTo{ handles.customers_menu };  
                break;

            case 3:
                co_await SwitchTo{ handles.trips_menu };  
                break;

            case 4:
                //co_await OrderOrReturnMenu(Managers, Customers, Trips, OrdersPath, HistoryDataPath);
                break;

            case 5:
                if (ConfirmationOfProgramCompletionMenu()){
                    StopInterface();
                }
                break;

            default:
                std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                break;
        }
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////////////
///
///  MANAGERS MENU
///
///////////////////////////////////////////////////////////////////////////////////////////////////////




MenuItem ManagersMenu(const MenuItemsHandles& handles){
    size_t menu_item = 0;

    while(true){
        ClearConsole();
        std::cout << "\n|--- Managers ---|";

		std::cout << "\n\n1) Information"; 
		std::cout << "\n2) Add manager";
		std::cout << "\n3) Remove manager";
		std::cout << "\n4) Back to the main menu";
		std::cout << "\n5) Close the program";

        std::cout << "\n\nEnter item number: ";
        ValidatedInput(menu_item);
        switch (menu_item) {
            case 1:
                co_await SwitchTo{handles.managers_info_menu}; 
                break;

            case 2:
                co_await SwitchTo{handles.managers_add_manager_menu}; 
                break;

            case 3:
                co_await SwitchTo{handles.managers_remove_manager_menu}; 
                break;

            case 4:
                co_await SwitchTo{handles.main_menu}; 
                break;

            case 5:
                if (ConfirmationOfProgramCompletionMenu()){
                    StopInterface();
                }
                break;

            default:
                std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                break;
        }
    }
}



MenuItem ManagersInfoMenu(ListSharedsManager_t& managers, const MenuItemsHandles& handles) {
    size_t menu_item = 0;
    
    if (managers.empty()) {
        while (true) {
            ClearConsole();
            std::cout << "\n\n|--- Information about managers ---|";

            std::cout << "\n\nUnfortunately, there are no managers";
            std::cout << "\n1) Add new manager";
            std::cout << "\n2) Go to the \"Main menu\"";
            std::cout << "\n3) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
            case 1:
                co_await SwitchTo{handles.managers_add_manager_menu}; 
                break;

            case 2:
                co_await SwitchTo{handles.main_menu}; 
                break;

            case 3:
                if (ConfirmationOfProgramCompletionMenu()){
                    StopInterface();
                }
                break;

            default:
                std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                break;
            }
        }
    }

    while(true){
        ClearConsole();
        std::cout << "\n\n|--- Information about managers ---|";

        std::cout << "\n\nCount of managers: " << managers.size();

        std::cout << "\n\n1) Full information about the manager";
        std::cout << "\n2) Edit information about the manager";
        std::cout << "\n3) Back to \"Managers\"";
        std::cout << "\n4) Go to \"Main menu\"";
        std::cout << "\n5) Close the program";
        std::cout << "\n\n!!! If you choose (1) or (2) you will see full list of managers";

        std::cout << "\n\nEnter item number: ";
        ValidatedInput(menu_item);
        switch (menu_item) {
            case 1:
                co_await SwitchTo{handles.managers_show_full_info_menu};
                break;
                
            case 2:
                co_await SwitchTo{handles.managers_edit_info_menu}; 
                break;
                
            case 3:
                co_await SwitchTo{handles.managers_menu}; 
                break;
                
            case 4:
                 co_await SwitchTo{handles.main_menu}; 
                break;
                
            case 5:
                if (ConfirmationOfProgramCompletionMenu()){
                    StopInterface();
                }
                break;

            default:
                std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                break;
        }
    }
}




MenuItem ShowFullInformationAboutManagerMenu(const ListSharedsManager_t& managers, const MenuItemsHandles& handles){
    size_t menu_item = 0;
    size_t manager_index = 0;
    bool try_again_select_manager = true;
    while(try_again_select_manager){
        try_again_select_manager = false;

        ClearConsole();
        std::cout << "\n\n|--- Full information about the manager ---|\n";

        std::cout << "\nManagers: \n";
        ShowListOfCollectionElementNames(managers);

        std::cout << "\n\nSelect the number of the manager you want to see full information about: ";
        ValidatedInput(manager_index);

        if (manager_index < 1 || manager_index > managers.size()) {
            while (true) {
                std::cout << "\n\nThere is no manager with such a serial number.";
                std::cout << "\n1) Try again to select a manager";
                std::cout << "\n2) Back to \"Information about managers\"";
                std::cout << "\n3) Go to \"Main menu\"";
                std::cout << "\n4) Close the program";

                std::cout << "\n\nEnter item number: ";
                ValidatedInput(menu_item);
                switch (menu_item) {
                    case 1:
                        try_again_select_manager = true;
                        break;

                    case 2:
                        co_await SwitchTo{handles.managers_info_menu}; 
                        break;

                    case 3:
                        co_await SwitchTo{handles.main_menu}; 
                        break;

                    case 4:
                        if (ConfirmationOfProgramCompletionMenu()){
                            StopInterface();
                        }
                        break;

                    default:
                        std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                        break;
                }
                if (try_again_select_manager) break;
            } 
            if (try_again_select_manager) continue;
        } 

        auto manager = managers.begin();
        std::advance(manager, manager_index - 1);

        ClearConsole();
        std::cout << "\n\n|--- Full information about the manager ---|\n";
        (*manager)->ShowInfo();

        while (true) {
            std::cout << "\n\n1) See detailed information about another manager";
            std::cout << "\n2) Back to \"Information about managers\"";
            std::cout << "\n3) Go to \"Main menu\"";
            std::cout << "\n4) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
                case 1:
                    try_again_select_manager = true;
                    break;
                case 2:
                    co_await SwitchTo{handles.managers_info_menu}; 
                    break;

                case 3:
                    co_await SwitchTo{handles.main_menu}; 
                    break;

                case 4:
                    if (ConfirmationOfProgramCompletionMenu()){
                        StopInterface();
                    }
                    break;

                default:
                    std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                    break;
            }
            if (try_again_select_manager) break;
        }
        if (try_again_select_manager) continue;
    }
}




MenuItem EditInformationAboutManagerMenu(const ListSharedsManager_t& managers, const std::string& historyDataPath, const MenuItemsHandles& handles){
    size_t menu_item = 0;
    size_t manager_index = 0;
    size_t field_index = 0;
    bool try_again_select_manager = true;
    std::string new_value; 

    while(try_again_select_manager){
        try_again_select_manager = false;

        ClearConsole();
        std::cout << "\n|--- Edit information about the manager ---|\n";

        std::cout << "\nManagers: \n";
        ShowListOfCollectionElementNames(managers);

        std::cout << "\n\nSelect the number of the manager, whose information you want to edit: ";
        ValidatedInput(manager_index);

        if (manager_index < 1 || manager_index > managers.size()) {
            while (true) {
                std::cout << "\n\nThere is no manager with such a serial number";
                std::cout << "\n1) Try again to select a manager";
                std::cout << "\n2) Back to \"Information about managers\"";
                std::cout << "\n3) Go to \"Main menu\"";
                std::cout << "\n4) Close the program";

                std::cout << "\n\nEnter item number: ";
                ValidatedInput(menu_item);
                switch (menu_item) {
                    case 1:
                        try_again_select_manager = true;
                        break;

                    case 2:
                        co_await SwitchTo{handles.managers_info_menu}; 
                        break;

                    case 3:
                        co_await SwitchTo{handles.main_menu}; 
                        break;

                    case 4:
                        if (ConfirmationOfProgramCompletionMenu()){
                            StopInterface();
                        }
                        break;

                    default:
                        std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                        break;
                }
                if (try_again_select_manager) break;
            } 
            if (try_again_select_manager) continue;
        }

        auto manager = managers.begin();
        std::advance(manager, manager_index - 1);
        
        bool try_again_select_field = true;
        while(try_again_select_field){
            try_again_select_field = false;
            
            ClearConsole();
            std::cout << "\n|--- Edit information about the manager \"" << (*manager)->GetFullName() << "\" " << (*manager)->GetPhoneNumber() << " ---|\n";
           	std::cout << "\n" << "1) First name: " << (*manager)->GetFirstName();
            std::cout << "\n" << "2) Second name: " << (*manager)->GetSecondName();
            std::cout << "\n" << "3) Patronymic name: " << (*manager)->GetPatronymicName();
            std::cout << "\n" << "4) Phone number: " << (*manager)->GetPhoneNumber();

            std::cout << "\n\nSelect the number of the field, that you want to edit: ";
            ValidatedInput(field_index);

            if (field_index < 1 || field_index > 4) {
                while (true) {
                    std::cout << "\n\nThere is no field with such a serial number";
                    std::cout << "\n1) Try again to select a field";
                    std::cout << "\n2) Select another manager to edit";
                    std::cout << "\n3) Back to \"Information about managers\"";
                    std::cout << "\n4) Go to \"Main menu\"";
                    std::cout << "\n5) Close the program";

                    std::cout << "\n\nEnter item number: ";
                    ValidatedInput(menu_item);
                    switch (menu_item) {
                        case 1:
                            try_again_select_field = true;
                            break;

                        case 2:
                            try_again_select_manager = true;
                            break;

                        case 3:
                            co_await SwitchTo{handles.managers_info_menu}; 
                            break;

                        case 4:
                            co_await SwitchTo{handles.main_menu}; 
                            break;

                        case 5:
                            if (ConfirmationOfProgramCompletionMenu()){
                                StopInterface();
                            }
                            break;

                        default:
                            std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                            break;
                    }
                            
                    if (try_again_select_field || try_again_select_manager) break;
                }
                if (try_again_select_field)  continue;
                if (try_again_select_manager) break;
            }
            

            bool try_again_edit_selected_field = true;
            while(try_again_edit_selected_field){
                try_again_edit_selected_field = false;

                std::cout << "\n\nEnter a new value for selected field: ";
                ValidatedInput(new_value);

                switch (field_index){
                    case 1:
                        (*manager)->SetFirstName(new_value);
                        break;	
                    case 2:
                        (*manager)->SetSecondName(new_value);
                        break;
                    case 3:
                        (*manager)->SetPatronymicName(new_value);
                        break;
                    case 4:
                        (*manager)->SetPhoneNumber(new_value);
                        break;
                    default:
                        break;
                }
                
                ClearConsole();
                std::cout << "\n\n|--- Edit information about the manager ---|\n";

                std::cout << "\nInformation about the manager \"" << (*manager)->GetFullName() << "\" has been edited:";
                (*manager)->ShowInfo();
                SaveMessage("Changing information about manager by id: " + std::to_string((*manager)->GetPersonalId()), historyDataPath);


                while (true) {
                    std::cout << "\n\n1) Enter another value for selected field: " << 
                        (field_index == 1 ? "First name" : (field_index == 2 ? "Second name" : (field_index == 3 ? "Patronymic name" : "Pnone number")));
                    std::cout << "\n2) Select another field of the current manager " << "(\"" << (*manager)->GetFullName() << "\" " << (*manager)->GetPhoneNumber() << ") to edit"; 
                    std::cout << "\n3) Select another manager to edit";
                    std::cout << "\n4) Back to \"Information about managers\"";
                    std::cout << "\n5) Go to \"Main menu\"";
                    std::cout << "\n6) Close the program";

                    std::cout << "\n\nEnter item number: ";
                    ValidatedInput(menu_item);
                    switch (menu_item) {
                        case 1:
                            try_again_edit_selected_field = true;
                            break;

                        case 2:
                            try_again_select_field = true;
                            break;

                        case 3:
                            try_again_select_manager = true;
                            break;

                        case 4:
                            co_await SwitchTo{handles.managers_info_menu}; 
                            break;

                        case 5:
                            co_await SwitchTo{handles.main_menu}; 
                            break;

                        case 6:
                            if (ConfirmationOfProgramCompletionMenu()){
                                StopInterface();
                            }
                            break;

                        default:
                            std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                            break;
                    }

                    if (try_again_edit_selected_field || try_again_select_field || try_again_select_manager) break;
                }
                if (try_again_edit_selected_field) continue;
                if (try_again_select_field || try_again_select_manager) break;
            }
            if (try_again_select_field) continue;
            if (try_again_select_manager) break;
        }
    }
}





MenuItem AddNewManagerMenu(ListSharedsManager_t& managers, const std::string& historyDataPath, const MenuItemsHandles& handles){
    size_t menu_item = 0;
    bool add_new_manager_again = true;
    std::string name;
    std::string phone_number;

    while (add_new_manager_again){

        add_new_manager_again = false;
        auto new_manager = std::make_shared<Manager>();

        
        ClearConsole();
        std::cout << "\n\n|--- Add new manager ---|\n";

        std::cout << "\nEnter manager`s name: ";
        std::getline(std::cin, name);
        new_manager->SetFullName(name);

        std::cout << "\nEnter manager`s phone number (format: +380XXXXXXXXX): ";
        std::getline(std::cin, phone_number);
        new_manager->SetPhoneNumber(phone_number);

        try{
            managers.emplace_back(new_manager);
            std::cout << "\n\nManager by name\"" << new_manager->GetFullName() << "\" was added.\nHis/Her id: " << new_manager->GetPersonalId() << "\n";
            SaveMessage("Manager by name \"" + new_manager->GetFullName() + "\" was added. His/Her id: " + std::to_string(new_manager->GetPersonalId()), historyDataPath);
        }
        catch(...){
            std::cout << "\n\nERROR: something went wrong while adding the manager by name\"" << new_manager->GetFullName();
        }

        while (true) {
            std::cout << "\n\n1) Add new manager";
            std::cout << "\n2) Back to \"Managers\"";
            std::cout << "\n3) Go to \"Main menu\"";
            std::cout << "\n4) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
                case 1:
                    add_new_manager_again = true;
                    break;

                case 2:
                    co_await SwitchTo{handles.managers_menu}; 
                    break;
                    
                case 3:
                     co_await SwitchTo{handles.main_menu}; 
                    break;
                    
                case 4:
                    if (ConfirmationOfProgramCompletionMenu()){
                        StopInterface();
                    }
                    break;

                default:
                    std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                    break;
            }

            if (add_new_manager_again) break;
        }
    }
}


MenuItem RemoveManagerMenu(ListSharedsManager_t& managers, const std::string& historyDataPath, const MenuItemsHandles& handles){
    size_t menu_item = 0;
    
    if (managers.empty()) {
        while (true) {
            ClearConsole();
            std::cout << "\n\n|--- Remove manager ---|\n";

            std::cout << "\n\nUnfortunately, there are no managers (no one to delete)";
            std::cout << "\n1) Back to \"Managers\"";
            std::cout << "\n2) Go to the \"Main menu\"";
            std::cout << "\n3) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
                case 1:
                    co_await SwitchTo{handles.managers_menu}; 
                    break;
                    
                case 2:
                     co_await SwitchTo{handles.main_menu}; 
                    break;
                    
                case 3:
                    if (ConfirmationOfProgramCompletionMenu()){
                        StopInterface();
                    }
                    break;

                default:
                    std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                    break;
            }
        }
    } 

    size_t manager_index = 0;
    bool try_again_select_manager = true;
    bool remove_another_manager = true;

    while(remove_another_manager){
        remove_another_manager = false;

        ClearConsole();
        std::cout << "\n\n|--- Remove manager ---|\n";

 
        std::cout << "\nManagers: \n";
        ShowListOfCollectionElementNames(managers);

        std::cout << "\n\nSelect the number of the manager you want to remove: ";
        ValidatedInput(manager_index);

        if (manager_index < 1 || manager_index > managers.size()) {
            while (try_again_select_manager) {
                try_again_select_manager = false;

                std::cout << "\n\nThere is no manager with such a serial number.";
                std::cout << "\n1) Try again";
                std::cout << "\n2) Back to \"Managers\"";
                std::cout << "\n3) Go to \"Main menu\"";
                std::cout << "\n4) Close the program";

                std::cout << "\n\nEnter item number: ";
                ValidatedInput(menu_item);
                switch (menu_item) {
                    case 1:
                         try_again_select_manager = true;
                        break;

                    case 2:
                        co_await SwitchTo{handles.managers_menu}; 
                        break;
                        
                    case 3:
                         co_await SwitchTo{handles.main_menu}; 
                        break;
                        
                    case 4:
                        if (ConfirmationOfProgramCompletionMenu()){
                            StopInterface();
                        }
                        break;

                    default:
                        std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                        break;
                }
                if (try_again_select_manager) break;
            } 
            if (try_again_select_manager) continue;
        }
    

        auto manager = managers.begin();
        std::advance(manager, manager_index - 1);

        auto name = (*manager)->GetFullName();
        auto id = (*manager)->GetPersonalId();

        managers.remove(*manager);
        std::cout << "\nManager \"" << name << "\" has been removed.";

        SaveMessage("Manager by name \"" + name + "\" has been removed." + " His/Her id : " + std::to_string(id), historyDataPath);
        
        while (true) {
            std::cout << "\n\n1) Remove another manager";
            std::cout << "\n2) Back to \"Managers\"";
            std::cout << "\n3) Go to \"Main menu\"";
            std::cout << "\n4) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
                case 1:
                    try_again_select_manager = true;
                    break;

                case 2:
                    co_await SwitchTo{handles.managers_menu}; 
                    break;
                    
                case 3:
                     co_await SwitchTo{handles.main_menu}; 
                    break;
                    
                case 4:
                    if (ConfirmationOfProgramCompletionMenu()){
                        StopInterface();
                    }
                    break;

                default:
                    std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                    break;
            }
            if (try_again_select_manager) break;
        }
    }
}













///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///
///  END MANAGERS MENU
///
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// CUSTOMERS MENU
///
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////











MenuItem CustomersMenu(const MenuItemsHandles& handles)
{
    size_t menu_item = 0;

    while(true){
        ClearConsole();
    	std::cout << "\n\n|--- Customers ---|";

		std::cout << "\n\n1) Information";
		std::cout << "\n2) Add new customer";
		std::cout << "\n3) Remove customer";
		std::cout << "\n4) Back to \"Main menu\"";
		std::cout << "\n5) Close the program";


        std::cout << "\n\nEnter item number: ";
        ValidatedInput(menu_item);
        switch (menu_item) {
            case 1:
                co_await SwitchTo{handles.customers_info_menu}; 
                break;

            case 2:
                co_await SwitchTo{handles.customers_add_customer_menu}; 
                break;

            case 3:
                co_await SwitchTo{handles.customers_remove_customer_menu}; 
                break;

            case 4:
                co_await SwitchTo{handles.main_menu}; 
                break;

            case 5:
                if (ConfirmationOfProgramCompletionMenu()){
                    StopInterface();
                }
                break;

            default:
                std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                break;
        }
    }
}


MenuItem CustomersInfoMenu(ListSharedsCustomer_t& customers, const MenuItemsHandles& handles) {
    size_t menu_item = 0;
    
    if (customers.empty()) {
        while (true) {
            ClearConsole();
            std::cout << "\n\n|--- Information about customers ---|";

            std::cout << "\n\nUnfortunately, there are no customers";
            std::cout << "\n1) Add new customer";
            std::cout << "\n2) Go to the \"Main menu\"";
            std::cout << "\n3) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
            case 1:
                co_await SwitchTo{handles.customers_add_customer_menu}; 
                break;

            case 2:
                co_await SwitchTo{handles.main_menu}; 
                break;

            case 3:
                if (ConfirmationOfProgramCompletionMenu()){
                    StopInterface();
                }
                break;

            default:
                std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                break;
            }
        }
    } 

    while(true){
        ClearConsole();
        std::cout << "\n\n|--- Information about customers ---|";

        std::cout << "\n\nCount of customers: " << customers.size();
        
        std::cout << "\n\n1) Show full information about the customer"; 
        std::cout << "\n2) Edit information about the customer";
        std::cout << "\n3) List of customers by trip`s country";
        std::cout << "\n4) Back to \"Customers\"";
        std::cout << "\n5) Go to \"Main menu\"";
        std::cout << "\n6) Close the program";
        std::cout << "\n\n!!! If you choose (1) or (2) you will see full list of managers";

        std::cout << "\n\nEnter item number: ";
        ValidatedInput(menu_item);
        switch (menu_item) {
            case 1:
                co_await SwitchTo{handles.customers_show_full_info_menu};
                break;
                
            case 2:
                co_await SwitchTo{handles.customers_edit_info_menu}; 
                break;

            case 3:
                co_await SwitchTo{handles.customers_list_by_trip_country_menu}; 
                break;
            
            case 4:
                co_await SwitchTo{handles.customers_menu}; 
                break;
                
            case 5:
                 co_await SwitchTo{handles.main_menu}; 
                break;
                
            case 6:
                if (ConfirmationOfProgramCompletionMenu()){
                    StopInterface();
                }
                break;

            default:
                std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                break;
        }
    }
}




MenuItem ShowFullInformationAboutCustomerMenu(const ListSharedsCustomer_t& customers, const MenuItemsHandles& handles){
    size_t menu_item = 0;
    size_t customer_index = 0;
    bool try_again_select_customer = true;
    while(try_again_select_customer){
        try_again_select_customer = false;

        ClearConsole();
        std::cout << "\n\n|--- Full information about the customer ---|\n";

        std::cout << "\nCustomers: \n";
        ShowListOfCollectionElementNames(customers);

        std::cout << "\n\nSelect the number of the customer you want to see full information about: ";
        ValidatedInput(customer_index);

        if (customer_index < 1 || customer_index > customers.size()) {
            while (true) {
                std::cout << "\n\nThere is no customer with such a serial number.";
                std::cout << "\n1) Try again to select a customer";
                std::cout << "\n2) Back to \"Information about customers\"";
                std::cout << "\n3) Go to \"Main menu\"";
                std::cout << "\n4) Close the program";

                std::cout << "\n\nEnter item number: ";
                ValidatedInput(menu_item);
                switch (menu_item) {
                    case 1:
                        try_again_select_customer = true;
                        break;

                    case 2:
                        co_await SwitchTo{handles.customers_info_menu}; 
                        break;

                    case 3:
                        co_await SwitchTo{handles.main_menu}; 
                        break;

                    case 4:
                        if (ConfirmationOfProgramCompletionMenu()){
                            StopInterface();
                        }
                        break;

                    default:
                        std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                        break;
                }
                if (try_again_select_customer) break;
            } 
            if (try_again_select_customer) continue;
        } 

        auto customer = customers.begin();
        std::advance(customer, customer_index - 1);

        ClearConsole();
        std::cout << "\n\n|--- Full information about the customer ---|\n";
        (*customer)->ShowInfo();

        while (true) {
            std::cout << "\n\n1) See detailed information about another customer";
            std::cout << "\n2) Back to \"Information about customers\"";
            std::cout << "\n3) Go to \"Main menu\"";
            std::cout << "\n4) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
                case 1:
                    try_again_select_customer = true;
                    break;

                case 2:
                    co_await SwitchTo{handles.customers_info_menu}; 
                    break;

                case 3:
                    co_await SwitchTo{handles.main_menu}; 
                    break;

                case 4:
                    if (ConfirmationOfProgramCompletionMenu()){
                        StopInterface();
                    }
                    break;

                default:
                    std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                    break;
            }
            if (try_again_select_customer) break;
        }
        if (try_again_select_customer) continue;
    }
}




MenuItem EditInformationAboutCustomerMenu(const ListSharedsCustomer_t& customers, const std::string& historyDataPath, const MenuItemsHandles& handles){
    size_t menu_item = 0;
    size_t customer_index = 0;
    size_t field_index = 0;
    bool try_again_select_customer = true;
    std::string new_value; 

    while(try_again_select_customer){
        try_again_select_customer = false;

        ClearConsole();
        std::cout << "\n|--- Edit information about the customer ---|\n";

        std::cout << "\nCustomers: \n";
        ShowListOfCollectionElementNames(customers);

        std::cout << "\n\nSelect the number of the customer, whose information you want to edit: ";
        ValidatedInput(customer_index);

        if (customer_index < 1 || customer_index > customers.size()) {
            while (true) {
                std::cout << "\n\nThere is no customer with such a serial number";
                std::cout << "\n1) Try again to select a customer";
                std::cout << "\n2) Back to \"Information about customers\"";
                std::cout << "\n3) Go to \"Main menu\"";
                std::cout << "\n4) Close the program";

                std::cout << "\n\nEnter item number: ";
                ValidatedInput(menu_item);
                switch (menu_item) {
                    case 1:
                        try_again_select_customer = true;
                        break;

                    case 2:
                        co_await SwitchTo{handles.customers_info_menu}; 
                        break;

                    case 3:
                        co_await SwitchTo{handles.main_menu}; 
                        break;

                    case 4:
                        if (ConfirmationOfProgramCompletionMenu()){
                            StopInterface();
                        }
                        break;

                    default:
                        std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                        break;
                }
                if (try_again_select_customer) break;
            } 
            if (try_again_select_customer) continue;
        }

        auto customer = customers.begin();
        std::advance(customer, customer_index - 1);
        
        bool try_again_select_field = true;
        while(try_again_select_field){
            try_again_select_field = false;
            
            ClearConsole();
            std::cout << "\n|--- Edit information about the customer \"" << (*customer)->GetFullName() << "\" " << (*customer)->GetPhoneNumber() << " ---|\n";
           	std::cout << "\n" << "1) First name: " << (*customer)->GetFirstName();
            std::cout << "\n" << "2) Second name: " << (*customer)->GetSecondName();
            std::cout << "\n" << "3) Patronymic name: " << (*customer)->GetPatronymicName();
            std::cout << "\n" << "4) Phone number: " << (*customer)->GetPhoneNumber();
            std::cout << "\n" << "5) Address: " << (*customer)->GetAddress();

            std::cout << "\n\nSelect the number of the field, that you want to edit: ";
            ValidatedInput(field_index);

            if (field_index < 1 || field_index > 5) {
                while (true) {
                    std::cout << "\n\nThere is no field with such a serial number";
                    std::cout << "\n1) Try again to select a field";
                    std::cout << "\n2) Select another customer to edit";
                    std::cout << "\n3) Back to \"Information about customers\"";
                    std::cout << "\n4) Go to \"Main menu\"";
                    std::cout << "\n5) Close the program";

                    std::cout << "\n\nEnter item number: ";
                    ValidatedInput(menu_item);
                    switch (menu_item) {
                        case 1:
                            try_again_select_field = true;
                            break;

                        case 2:
                            try_again_select_customer = true;
                            break;

                        case 3:
                            co_await SwitchTo{handles.customers_info_menu}; 
                            break;

                        case 4:
                            co_await SwitchTo{handles.main_menu}; 
                            break;

                        case 5:
                            if (ConfirmationOfProgramCompletionMenu()){
                                StopInterface();
                            }
                            break;

                        default:
                            std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                            break;
                    }
                            
                    if (try_again_select_field || try_again_select_customer) break;
                }
                if (try_again_select_field)  continue;
                if (try_again_select_customer) break;
            }
            

            bool try_again_edit_selected_field = true;
            while(try_again_edit_selected_field){
                try_again_edit_selected_field = false;

                std::cout << "\n\nEnter a new value for selected field: ";
                ValidatedInput(new_value);

                switch (field_index){
                    case 1:
                        (*customer)->SetFirstName(new_value);
                        break;

                    case 2:
                        (*customer)->SetSecondName(new_value);
                        break;

                    case 3:
                        (*customer)->SetPatronymicName(new_value);
                        break;

                    case 4:
                        (*customer)->SetPhoneNumber(new_value);
                        break;

                    case 5:
                        (*customer)->SetAddress(new_value);
                        break;

                    default:
                        break;
                }
                
                ClearConsole();
                std::cout << "\n\n|--- Edit information about the customer ---|\n";

                std::cout << "\nInformation about the customer \"" << (*customer)->GetFullName() << "\" has been edited:";
                (*customer)->ShowInfo();
                SaveMessage("Changing information about customer by id: " + std::to_string((*customer)->GetPersonalId()), historyDataPath);


                while (true) {
                    std::cout << "\n\n1) Enter another value for selected field: " << 
                        (field_index == 1 ? "First name" : (field_index == 2 ? "Second name" : (field_index == 3 ? "Patronymic name" : (field_index == 4 ? "Pnone number" : "Address"))));
                    std::cout << "\n2) Select another field of the current customer " << "(\"" << (*customer)->GetFullName() << "\" " << (*customer)->GetPhoneNumber() << ") to edit"; 
                    std::cout << "\n3) Select another customer to edit";
                    std::cout << "\n4) Back to \"Information about customers\"";
                    std::cout << "\n5) Go to \"Main menu\"";
                    std::cout << "\n6) Close the program";

                    std::cout << "\n\nEnter item number: ";
                    ValidatedInput(menu_item);
                    switch (menu_item) {
                        case 1:
                            try_again_edit_selected_field = true;
                            break;

                        case 2:
                            try_again_select_field = true;
                            break;

                        case 3:
                            try_again_select_customer = true;
                            break;

                        case 4:
                            co_await SwitchTo{handles.customers_info_menu}; 
                            break;

                        case 5:
                            co_await SwitchTo{handles.main_menu}; 
                            break;

                        case 6:
                            if (ConfirmationOfProgramCompletionMenu()){
                                StopInterface();
                            }
                            break;

                        default:
                            std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                            break;
                    }

                    if (try_again_edit_selected_field || try_again_select_field || try_again_select_customer) break;
                }
                if (try_again_edit_selected_field) continue;
                if (try_again_select_field || try_again_select_customer) break;
            }
            if (try_again_select_field) continue;
            if (try_again_select_customer) break;
        }
    }
}



MenuItem ListOfCustomersByTripsCountryMenu(const ListSharedsCustomer_t& customers, const ListSharedsTrip_t& trips, const MenuItemsHandles& handles){
    size_t menu_item = 0;
    
    if (GetCountOfCustomersWithTrip(customers).first == 0) {
        while (true) {
            ClearConsole();
            std::cout << "\n\n|--- List of customers by trip`s country  ---|";

            std::cout << "\n\nUnfortunately, there are no customers with a trip.";
            std::cout << "\n1) Back to \"Customers information\"";
            std::cout << "\n2) Go to \"Main menu\"";
            std::cout << "\n3) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
                case 1:
                    co_await SwitchTo{handles.customers_info_menu}; 
                    break;

                case 2:
                    co_await SwitchTo{handles.main_menu}; 
                    break;

                case 3:
                    if (ConfirmationOfProgramCompletionMenu()){
                        StopInterface();
                    }
                    break;

                default:
                    std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                    break;
            }
        }
    }

    size_t customer_index = 0;
    size_t country_index = 1;
    std::string country;
    bool try_to_select_country_again = true;
    
    while(try_to_select_country_again){
        try_to_select_country_again = false;
        
        ClearConsole();
        std::cout << "\n\n|--- List of customers by trip`s country  ---|\n";

        auto countries_of_bought_trips = GetCountriesOfBoughtTrips(trips);
        std::cout << "\nCountries: ";
        country_index = 1;
        for (const auto& country : countries_of_bought_trips) {
            std::cout << "\n" << country_index << ") " << country;
            country_index++;
        }
					
				
        std::cout << "\n\nSelect the country number, you are interested in: ";
        ValidatedInput(country_index);

    	if (country_index < 1 || country_index > countries_of_bought_trips.size()) {
            while (true) {
                std::cout << "\n\nThere is no country with such a serial number.";
                std::cout << "\n1) Try again";
                std::cout << "\n2) Back to \"Information about customers\"";
                std::cout << "\n3) Go to \"Main menu\"";
                std::cout << "\n4) Close the program";

                std::cout << "\n\nEnter item number: ";
                ValidatedInput(menu_item);
                switch (menu_item) {
                    case 1:
                        try_to_select_country_again = true;
                        break;
                    
                    case 2:
                        co_await SwitchTo{handles.customers_info_menu}; 
                        break;

                    case 3:
                        co_await SwitchTo{handles.main_menu}; 
                        break;

                    case 4:
                        if (ConfirmationOfProgramCompletionMenu()){
                            StopInterface();
                        }
                        break;

                    default:
                        std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                        break;
                }
                if (try_to_select_country_again) break;
            } 
            if (try_to_select_country_again) continue;
        }

        country = countries_of_bought_trips.at(country_index - 1);
				
		std::cout << "\nCustomers who have a trip to \""<< country <<"\":";
		ShowListOfCustomerNamesByCountry(customers, country);

        while (true) {
            std::cout << "\n\n1) See list of customers by trip`s of another country";
            std::cout << "\n2) Back to \"Information about customers\"";
            std::cout << "\n3) Go to \"Main menu\"";
            std::cout << "\n4) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
                case 1:
                    try_to_select_country_again = true;
                    break;
                
                case 2:
                    co_await SwitchTo{handles.customers_info_menu}; 
                    break;

                case 3:
                    co_await SwitchTo{handles.main_menu}; 
                    break;

                case 4:
                    if (ConfirmationOfProgramCompletionMenu()){
                        StopInterface();
                    }
                    break;

                default:
                    std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                    break;
            }
            if (try_to_select_country_again) break;
        }
    }
}





MenuItem AddNewCustomerMenu(ListSharedsCustomer_t& customers, const std::string& historyDataPath, const MenuItemsHandles& handles){
    size_t menu_item = 0;
    bool add_new_customer_again = true;
    std::string name;
    std::string phone_number;
    std::string address;

    while (add_new_customer_again){

        add_new_customer_again = false;
        auto new_customer = std::make_shared<Customer>();
        
        ClearConsole();
        std::cout << "\n\n|--- Add new customer ---|\n";

        std::cout << "\nEnter customer`s name: ";
        std::getline(std::cin, name);
        new_customer->SetFullName(name);

        std::cout << "\nEnter customer`s phone number (format: +380XXXXXXXXX): ";
        std::getline(std::cin, phone_number);
        new_customer->SetPhoneNumber(phone_number);

        std::cout << "\nEnter customer`s address ";
        std::getline(std::cin, address);
        new_customer->SetAddress(address);


        try{
            customers.emplace_back(new_customer);
            std::cout << "\n\nCustomer by name\"" << new_customer->GetFullName() << "\" was added.\nHis/Her id: " << new_customer->GetPersonalId() << "\n";
            SaveMessage("Customer by name \"" + new_customer->GetFullName() + "\" was added. His/Her id: " + std::to_string(new_customer->GetPersonalId()), historyDataPath);
        }
        catch(...){
            std::cout << "\n\nERROR: something went wrong while adding the customer by name\"" << new_customer->GetFullName();
        }

        while (true) {
            std::cout << "\n\n1) Add new customer";
            std::cout << "\n2) Back to \"Customers\"";
            std::cout << "\n3) Go to \"Main menu\"";
            std::cout << "\n4) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
                case 1:
                    add_new_customer_again = true;
                    break;

                case 2:
                    co_await SwitchTo{handles.customers_menu}; 
                    break;
                    
                case 3:
                     co_await SwitchTo{handles.main_menu}; 
                    break;
                    
                case 4:
                    if (ConfirmationOfProgramCompletionMenu()){
                        StopInterface();
                    }
                    break;

                default:
                    std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                    break;
            }

            if (add_new_customer_again) break;
        }
    }
}


MenuItem RemoveCustomerMenu(ListSharedsCustomer_t& customers, const std::string& historyDataPath, const MenuItemsHandles& handles){
    size_t menu_item = 0;
    
    if (customers.empty()) {
        while (true) {
            ClearConsole();
            std::cout << "\n\n|--- Remove customer ---|\n";

            std::cout << "\n\nUnfortunately, there are no customers (no one to delete)";
            std::cout << "\n1) Back to \"Customers\"";
            std::cout << "\n2) Go to the \"Main menu\"";
            std::cout << "\n3) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
                case 1:
                    co_await SwitchTo{handles.customers_menu}; 
                    break;
                    
                case 2:
                     co_await SwitchTo{handles.main_menu}; 
                    break;
                    
                case 3:
                    if (ConfirmationOfProgramCompletionMenu()){
                        StopInterface();
                    }
                    break;

                default:
                    std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                    break;
            }
        }
    } 

    size_t customer_index = 0;
    bool try_again_select_customer = true;
    bool remove_another_customer = true;

    while(remove_another_customer){
        remove_another_customer = false;

        ClearConsole();
        std::cout << "\n\n|--- Remove customer ---|\n";

        std::cout << "\nCustomers: \n";
        ShowListOfCollectionElementNames(customers);

        std::cout << "\n\nSelect the number of the customer you want to remove: ";
        ValidatedInput(customer_index);

        if (customer_index < 1 || customer_index > customers.size()) {
            while (try_again_select_customer) {
                try_again_select_customer = false;

                std::cout << "\n\nThere is no customer with such a serial number.";
                std::cout << "\n1) Try again";
                std::cout << "\n2) Back to \"Customers\"";
                std::cout << "\n3) Go to \"Main menu\"";
                std::cout << "\n4) Close the program";

                std::cout << "\n\nEnter item number: ";
                ValidatedInput(menu_item);
                switch (menu_item) {
                    case 1:
                         try_again_select_customer = true;
                        break;

                    case 2:
                        co_await SwitchTo{handles.customers_menu}; 
                        break;
                        
                    case 3:
                         co_await SwitchTo{handles.main_menu}; 
                        break;
                        
                    case 4:
                        if (ConfirmationOfProgramCompletionMenu()){
                            StopInterface();
                        }
                        break;

                    default:
                        std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                        break;
                }
                if (try_again_select_customer) break;
            } 
            if (try_again_select_customer) continue;
        }
    

        auto customer = customers.begin();
        std::advance(customer, customer_index - 1);

        auto name = (*customer)->GetFullName();
        auto id = (*customer)->GetPersonalId();

        customers.remove(*customer);
        std::cout << "\nCustomer \"" << name << "\" has been removed.";

        SaveMessage("Customer by name \"" + name + "\" has been removed." + " His/Her id : " + std::to_string(id), historyDataPath);
        
        while (true) {
            std::cout << "\n\n1) Remove another customer";
            std::cout << "\n2) Back to \"Customers\"";
            std::cout << "\n3) Go to \"Main menu\"";
            std::cout << "\n4) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
                case 1:
                    try_again_select_customer = true;
                    break;

                case 2:
                    co_await SwitchTo{handles.customers_menu}; 
                    break;
                    
                case 3:
                     co_await SwitchTo{handles.main_menu}; 
                    break;
                    
                case 4:
                    if (ConfirmationOfProgramCompletionMenu()){
                        StopInterface();
                    }
                    break;

                default:
                    std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                    break;
            }
            if (try_again_select_customer) break;
        }
    }
}





















///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///
///  END CUSTOMERS MENU
///
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// TRIPS MENU
///
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////




















MenuItem TripsMenu(const MenuItemsHandles& handles){
    size_t menu_item = 0;

    while(true){
        ClearConsole();
		std::cout << "\n\n|--- Trips ---|\n";
		std::cout << "\n1) Information";
		std::cout << "\n2) Add new trip";
		std::cout << "\n3) Remove trip";
		std::cout << "\n4) Back to the main menu";
		std::cout << "\n5) Close the program";


        std::cout << "\n\nEnter item number: ";
        ValidatedInput(menu_item);
        switch (menu_item) {
            case 1:
                co_await SwitchTo{handles.trips_info_menu}; 
                break;

            case 2:
                co_await SwitchTo{handles.trips_add_trip_menu}; 
                break;

            case 3:
                co_await SwitchTo{handles.trips_remove_trip_menu}; 
                break;

            case 4:
                co_await SwitchTo{handles.main_menu}; 
                break;

            case 5:
                if (ConfirmationOfProgramCompletionMenu()){
                    StopInterface();
                }
                break;

            default:
                std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                break;
        }
    }
}



MenuItem TripsInfoMenu(ListSharedsTrip_t& trips, const MenuItemsHandles& handles) {
    size_t menu_item = 0;
    
    if (trips.empty()) {
        while (true) {
            ClearConsole();
            std::cout << "\n\n|--- Information about trips ---|";

            std::cout << "\n\nUnfortunately, there are no trips";
            std::cout << "\n1) Add new trip";
            std::cout << "\n2) Go to the \"Main menu\"";
            std::cout << "\n3) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
                case 1:
                    co_await SwitchTo{handles.trips_add_trip_menu}; 
                    break;

                case 2:
                    co_await SwitchTo{handles.main_menu}; 
                    break;

                case 3:
                    if (ConfirmationOfProgramCompletionMenu()){
                        StopInterface();
                    }
                    break;

                default:
                    std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                    break;
            }
        }
    } 

    while(true){
        ClearConsole();
        std::cout << "\n\n|--- Information about trips ---|";
        std::cout << "\n\n1) General information";
        std::cout << "\n2) Show full information about the customer"; 
        std::cout << "\n3) Edit information about the customer";
        std::cout << "\n4) Back to \"Trips\"";
        std::cout << "\n5) Go to \"Main menu\"";
        std::cout << "\n6) Close the program";
        std::cout << "\n\n!!! If you choose (1) or (2) you will see full list of managers";

        std::cout << "\n\nEnter item number: ";
        ValidatedInput(menu_item);
        switch (menu_item) {
            case 1:
                co_await SwitchTo{handles.trips_general_info_menu}; 
                break;
                
            case 2:
                co_await SwitchTo{handles.trips_show_full_info_menu};
                break;

            case 3:
                co_await SwitchTo{handles.trips_edit_info_menu}; 
                break;
            
            case 4:
                co_await SwitchTo{handles.trips_menu}; 
                break;
                
            case 5:
                 co_await SwitchTo{handles.main_menu}; 
                break;
                
            case 6:
                if (ConfirmationOfProgramCompletionMenu()){
                    StopInterface();
                }
                break;

            default:
                std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                break;
        }
    }
}




MenuItem ShowFullInformationAboutTripMenu(const ListSharedsTrip_t& trips, const MenuItemsHandles& handles){
    size_t menu_item = 0;
    size_t trip_index = 0;
    bool try_again_select_trip = true;

    while(try_again_select_trip){
        try_again_select_trip = false;

        ClearConsole();
        std::cout << "\n\n|--- Full information about the trip ---|\n";

        std::cout << "\nTrips: \n";
        ShowListOfCollectionElementNames(trips);

        std::cout << "\n\nSelect the number of the trip you want to see full information about: ";
        ValidatedInput(trip_index);

        if (trip_index < 1 || trip_index > trips.size()) {
            while (true) {
                std::cout << "\n\nThere is no trip with such a serial number.";
                std::cout << "\n1) Try again to select a trip";
                std::cout << "\n2) Back to \"Information about trips\"";
                std::cout << "\n3) Go to \"Main menu\"";
                std::cout << "\n4) Close the program";

                std::cout << "\n\nEnter item number: ";
                ValidatedInput(menu_item);
                switch (menu_item) {
                    case 1:
                        try_again_select_trip = true;
                        break;

                    case 2:
                        co_await SwitchTo{handles.trips_info_menu}; 
                        break;

                    case 3:
                        co_await SwitchTo{handles.main_menu}; 
                        break;

                    case 4:
                        if (ConfirmationOfProgramCompletionMenu()){
                            StopInterface();
                        }
                        break;

                    default:
                        std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                        break;
                }
                if (try_again_select_trip) break;
            } 
            if (try_again_select_trip) continue;
        } 

        auto trip = trips.begin();
        std::advance(trip, trip_index - 1);

        ClearConsole();
        std::cout << "\n\n|--- Full information about the trip ---|\n";
        (*trip)->ShowInfo();

        while (true) {
            std::cout << "\n\n1) See detailed information about another trip";
            std::cout << "\n2) Back to \"Information about trips\"";
            std::cout << "\n3) Go to \"Main menu\"";
            std::cout << "\n4) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
                case 1:
                    try_again_select_trip = true;
                    break;

                case 2:
                    co_await SwitchTo{handles.trips_info_menu}; 
                    break;

                case 3:
                    co_await SwitchTo{handles.main_menu}; 
                    break;

                case 4:
                    if (ConfirmationOfProgramCompletionMenu()){
                        StopInterface();
                    }
                    break;

                default:
                    std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                    break;
            }
            if (try_again_select_trip) break;
        }
        if (try_again_select_trip) continue;
    }
}




MenuItem EditInformationAboutTripMenu(const ListSharedsTrip_t& trips, const std::string& historyDataPath, const MenuItemsHandles& handles){
    size_t menu_item = 0;
    size_t trip_index = 0;
    size_t field_index = 0;
    bool try_again_select_trip = true;
    std::string new_str_value;
    double new_price; 

    while(try_again_select_trip){
        try_again_select_trip = false;

        ClearConsole();
        std::cout << "\n|--- Edit information about the trip ---|\n";

        std::cout << "\nTrips: \n";
        ShowListOfCollectionElementNames(trips);

        std::cout << "\n\nSelect the number of the trip, whose information you want to edit: ";
        ValidatedInput(trip_index);

        if (trip_index < 1 || trip_index > trips.size()) {
            while (true) {
                std::cout << "\n\nThere is no trip with such a serial number";
                std::cout << "\n1) Try again to select a trip";
                std::cout << "\n2) Back to \"Information about trips\"";
                std::cout << "\n3) Go to \"Main menu\"";
                std::cout << "\n4) Close the program";

                std::cout << "\n\nEnter item number: ";
                ValidatedInput(menu_item);
                switch (menu_item) {
                    case 1:
                        try_again_select_trip = true;
                        break;

                    case 2:
                        co_await SwitchTo{handles.trips_info_menu}; 
                        break;

                    case 3:
                        co_await SwitchTo{handles.main_menu}; 
                        break;

                    case 4:
                        if (ConfirmationOfProgramCompletionMenu()){
                            StopInterface();
                        }
                        break;

                    default:
                        std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                        break;
                }
                if (try_again_select_trip) break;
            } 
            if (try_again_select_trip) continue;
        }

        auto trip = trips.begin();
        std::advance(trip, trip_index - 1);
        
        bool try_again_select_field = true;
        while(try_again_select_field){
            try_again_select_field = false;
            
            ClearConsole();
            std::cout << "\n|--- Edit information about the trip \"" << (*trip)->GetFullName() << "\" ---|\n";
            std::cout << "\n\n1) Name: " << (*trip)->GetFullName();
            std::cout << "\n2) Country: " << (*trip)->GetCountry();
            std::cout << "\n3) City: " << (*trip)->GetCity();
            std::cout << "\n4) Date of start: " << (*trip)->GetDateOfStart();
            std::cout << "\n5) Date of end: " << (*trip)->GetDateOfEnd();
            std::cout << "\n6) Price: " << (*trip)->GetPrice() << " grn.";

            std::cout << "\n\nSelect the number of the field, that you want to edit: ";
            ValidatedInput(field_index);

            if (field_index < 1 || field_index > 6) {
                while (true) {
                    std::cout << "\n\nThere is no field with such a serial number";
                    std::cout << "\n1) Try again to select a field";
                    std::cout << "\n2) Select another trip to edit";
                    std::cout << "\n3) Back to \"Information about trips\"";
                    std::cout << "\n4) Go to \"Main menu\"";
                    std::cout << "\n5) Close the program";

                    std::cout << "\n\nEnter item number: ";
                    ValidatedInput(menu_item);
                    switch (menu_item) {
                        case 1:
                            try_again_select_field = true;
                            break;

                        case 2:
                            try_again_select_trip = true;
                            break;

                        case 3:
                            co_await SwitchTo{handles.trips_info_menu}; 
                            break;

                        case 4:
                            co_await SwitchTo{handles.main_menu}; 
                            break;

                        case 5:
                            if (ConfirmationOfProgramCompletionMenu()){
                                StopInterface();
                            }
                            break;

                        default:
                            std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                            break;
                    }
                            
                    if (try_again_select_field || try_again_select_trip) break;
                }
                if (try_again_select_field) continue;
                if (try_again_select_trip) break;
            }
            

            bool try_again_edit_selected_field = true;
            while(try_again_edit_selected_field){
                try_again_edit_selected_field = false;

                std::cout << "\n\nEnter a new value for selected field: ";
                switch (field_index){
                    case 1:
                        ValidatedInput(new_str_value);
                        (*trip)->SetFullName(new_str_value);
                        break;

                    case 2:
                        ValidatedInput(new_str_value);
                        (*trip)->SetCountry(new_str_value);
                        break;

                    case 3:
                        ValidatedInput(new_str_value);
                        (*trip)->SetCity(new_str_value);
                        break;

                    case 4:
                        ValidatedInput(new_str_value);
                        (*trip)->SetDateOfStart(stringToYearMonthDay(new_str_value));
                        break;

                    case 5:
                        ValidatedInput(new_str_value);
                        (*trip)->SetDateOfEnd(stringToYearMonthDay(new_str_value));
                        break;

                    case 6:
                        ValidatedInput(new_price);
                        (*trip)->SetPrice(new_price);
                        break;

                    default:
                        break;
                }
                
                ClearConsole();
                std::cout << "\n\n|--- Edit information about the trip ---|\n";

                std::cout << "\nInformation about the trip \"" << (*trip)->GetFullName() << "\" has been edited:";
                (*trip)->ShowInfo();
                SaveMessage("Changing information about trip by id: " + std::to_string((*trip)->GetPersonalId()), historyDataPath);


                while (true) {
                    std::cout << "\n\n1) Enter another value for selected field: " << 
                        (field_index == 1 ? "Name" : 
                            (field_index == 2 ? "Country" : 
                                (field_index == 3 ? "City" : 
                                    (field_index == 4 ? "Date of start" : 
                                        (field_index == 5 ? "Date of end" : "Price"))))); 
                    std::cout << "\n2) Select another field of the current trip " << "(\"" << (*trip)->GetFullName() << "\") to edit"; 
                    std::cout << "\n3) Select another trip to edit";
                    std::cout << "\n4) Back to \"Information about trips\"";
                    std::cout << "\n5) Go to \"Main menu\"";
                    std::cout << "\n6) Close the program";

                    std::cout << "\n\nEnter item number: ";
                    ValidatedInput(menu_item);
                    switch (menu_item) {
                        case 1:
                            try_again_edit_selected_field = true;
                            break;

                        case 2:
                            try_again_select_field = true;
                            break;

                        case 3:
                            try_again_select_trip = true;
                            break;

                        case 4:
                            co_await SwitchTo{handles.trips_info_menu}; 
                            break;

                        case 5:
                            co_await SwitchTo{handles.main_menu}; 
                            break;

                        case 6:
                            if (ConfirmationOfProgramCompletionMenu()){
                                StopInterface();
                            }
                            break;

                        default:
                            std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                            break;
                    }

                    if (try_again_edit_selected_field || try_again_select_field || try_again_select_trip) break;
                }
                if (try_again_edit_selected_field) continue;
                if (try_again_select_field || try_again_select_trip) break;
            }
            if (try_again_select_field) continue;
            if (try_again_select_trip) break;
        }
    }
}



MenuItem TripsGeneralInformationMenu(const ListSharedsTrip_t& trips, std::string orders_path, const MenuItemsHandles& handles){
    size_t menu_item = 0;
    size_t trip_index = 0;
    size_t country_index = 1;
    std::string country;
    
    while(true){
        std::cout << "\nGeneral information for all time: ";
        std::cout << "\n\tCount of valid trips in system: " << trips.size();
        std::cout << "\n\t\ton sale: " << GetCountOfUnboughtTrips(trips).first;
        std::cout << "\n\t\tsold: " << GetCountOfPurchasedTrips(trips).first;
        
        std::cout << "\n\tCount of successful orders: " << GetCountOfOrders(0, orders_path);
        std::cout << "\n\tAverage duration of the trip: " << std::round(GetAverageDurationOfTrips(trips)) << " days";
        std::cout << "\n\tAverage cost of the trip: " << std::round(GetAveragePriceOfTrips(trips)) << " UAH";
        
        ShowMostPupularCountries(FindMostPupularCountries(trips));

        std::cout << "\n\nDo you want to see the information about trips for a specific year?";
        std::cout << "\n1)Yes \n2)No";
        std::cout << "\n\nEnter item number: ";
        ValidatedInput(menu_item);
        switch (menu_item) {
            case 1:
                co_await SwitchTo{handles.trips_info_for_specific_year_menu}; 
                break;

            case 2:
                while (true) {
                    std::cout << "\n\n1) Back to \"Information about trips\"";
                    std::cout << "\n2) Go to \"Main menu\"";
                    std::cout << "\n3) Close the program";

                    std::cout << "\n\nEnter item number: ";
                    ValidatedInput(menu_item);
                    switch (menu_item) {
                        case 1:
                            co_await SwitchTo{handles.trips_info_menu}; 
                            break;

                        case 2:
                            co_await SwitchTo{handles.main_menu}; 
                            break;

                        case 3:
                            if (ConfirmationOfProgramCompletionMenu()){
                                StopInterface();
                            }
                            break;

                        default:
                            std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                            break;
                    }
                }
                break;

            default:
                std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                break;
        }
    } 
}


MenuItem TripsInformationForSpecificYearMenu(const ListSharedsTrip_t& trips, std::string orders_path, const MenuItemsHandles& handles){
    size_t menu_item = 0;
    bool try_select_year_again = true;

    while(try_select_year_again){
        try_select_year_again = false;

        std::cout << "\n\n|--- Information about trips for a specific year ---|\n";

        unsigned short current_year = static_cast<unsigned short>(
                            static_cast<int>(
                                std::chrono::year_month_day{
                                    floor<std::chrono::days>(std::chrono::system_clock::now())
                                }.year()
                            )
                        );

        std::cout << "\nEnter the year you are interested in: ";
        unsigned short input_year = 0;
        ValidatedInput(input_year);
        
        if (input_year > current_year) {
            while (true) {
                std::cout << "\n\nInvalid year: you have entered a future year.";
                std::cout << "\n1) See the information about trips for another year";
                std::cout << "\n2) Back to \"General information about trips for all time\"";
                std::cout << "\n3) Go to \"Information about trips\"";
                std::cout << "\n4) Go to \"Main menu\"";
                std::cout << "\n5) Close the program";

                std::cout << "\n\nEnter item number: ";
                ValidatedInput(menu_item);
                switch (menu_item) {
                    case 1:
                        try_select_year_again = true;
                        break;

                    case 2:
                        co_await SwitchTo{handles.trips_general_info_menu}; 
                        break;

                    case 3:
                        co_await SwitchTo{handles.trips_info_menu}; 
                        break;

                    case 4:
                        co_await SwitchTo{handles.main_menu}; 
                        break;

                    case 5:
                        if (ConfirmationOfProgramCompletionMenu()){
                            StopInterface();
                        }
                        break;

                    default:
                        std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                        break;
                }
                if (try_select_year_again) break;
            }
            if (try_select_year_again) continue;
        }

        ClearConsole();

        std::cout << "\n\n|--- Information about trips for a specific year  ---|\n";
        std::cout << "\nGeneral information for " << input_year << " year:";
        std::cout << "\n\tCount of sold trips: " << GetCountOfOrders(input_year) + GetCountOfPurchasedTrips(trips, input_year).first;
        
        std::cout << "\n\tAverage duration of the trip: " << std::round(GetAverageDurationOfTrips(trips, input_year)) << " days ";
        std::cout << "\n\tAverage cost of the trip: "     << std::round(GetAveragePriceOfTrips(trips, input_year))    << " UAH";
        
        ShowMostPupularCountries(FindMostPupularCountries(trips, input_year));

        while (true) {
            std::cout << "\n\n1) See a general information about trips for another year";
            std::cout << "\n2) Back to \"General information about trips for all time\"";
            std::cout << "\n3) Go to \"Information about trips\"";
            std::cout << "\n4) Go to \"Main menu\"";
            std::cout << "\n5) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
                case 1:
                    try_select_year_again = true;
                    break;

                case 2:
                    co_await SwitchTo{handles.trips_general_info_menu}; 
                    break;

                case 3:
                    co_await SwitchTo{handles.trips_info_menu}; 
                    break;

                case 4:
                    co_await SwitchTo{handles.main_menu}; 
                    break;

                case 5:
                    if (ConfirmationOfProgramCompletionMenu()){
                        StopInterface();
                    }
                    break;

                default:
                    std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                    break;
            }
            if (try_select_year_again) break;
        }
    }
}



MenuItem AddNewTripMenu(ListSharedsTrip_t& trips, const std::string& historyDataPath, const MenuItemsHandles& handles){
    size_t menu_item = 0;
    std::string new_str_value;
    double new_price; ;

    bool add_new_trip_again = true;
    bool try_enter_value_again = true;

    while (add_new_trip_again){
        add_new_trip_again = false;

        ClearConsole();
        std::cout << "\n\n|--- Add new trip ---|";
    
        auto new_trip = std::make_shared<Trip>();

        std::cout << "\n\nEnter trip`s name: ";
        std::getline(std::cin, new_str_value);
        new_trip->SetFullName(new_str_value);

        std::cout << "\nEnter trip`s country: ";
        std::getline(std::cin, new_str_value);
        new_trip->SetCountry(new_str_value);

        std::cout << "\nEnter trip`s city: ";
        std::getline(std::cin, new_str_value);
        new_trip->SetCity(new_str_value);
       
        try_enter_value_again = true;
        while (try_enter_value_again){
            std::cout << "\nEnter trip`s date of start (yyyy/mm/dd): ";
            if (std::cin >> new_str_value){
                try{
                    std::chrono::year_month_day date_of_start = stringToYearMonthDay(new_str_value);

                    if (date_of_start.ok()) {
                        new_trip->SetDateOfStart(date_of_start);
                        try_enter_value_again = false;
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


              
        try_enter_value_again = true;
        while (try_enter_value_again){
            std::cout << "\nEnter trip`s date of end (yyyy/mm/dd): ";
            if (std::cin >> new_str_value) {
                try{
                    std::chrono::year_month_day date_of_end = stringToYearMonthDay(new_str_value);
                    if (date_of_end.ok()) {
                        new_trip->SetDateOfEnd(date_of_end);
                        try_enter_value_again = false;
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
        
        try_enter_value_again = true;
        while (try_enter_value_again){
            std::cout << "\nEnter trip`s price (grn.): ";
            ValidatedInput(new_price);
            if (new_price > 0) 
                try_enter_value_again = false;
            else  
                std::cout << "Error: Invalid calendar date entered! Try again\n";

        }
        new_trip->SetPrice(new_price);


        try{
            trips.emplace_back(new_trip);
            std::cout << "\n\nTrip by name \"" << new_trip->GetFullName() << "\" was added.\nIt id: " << new_trip->GetPersonalId() << "\n";
            SaveMessage("Trip by name \"" + new_trip->GetFullName() + "\" was added. It id: " + std::to_string(new_trip->GetPersonalId()), historyDataPath);
        }
        catch(...){
            std::cout << "\n\nERROR: something went wrong while adding the trip by name\"" << new_trip->GetFullName();
        }

        while (true) {
            std::cout << "\n\n1) Add new trip";
            std::cout << "\n2) Back to \"Trips\"";
            std::cout << "\n3) Go to \"Main menu\"";
            std::cout << "\n4) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
                case 1:
                    add_new_trip_again = true; 
                    break;

                case 2:
                    co_await SwitchTo{handles.main_menu}; 
                    break;

                case 3:
                    if (ConfirmationOfProgramCompletionMenu()){
                        StopInterface();
                    }
                    break;

                default:
                    std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                    break;
            }
            if (add_new_trip_again) break;
        }
    }
}


MenuItem RemoveTripMenu(ListSharedsTrip_t& trips, const std::string& historyDataPath, const MenuItemsHandles& handles){
    size_t menu_item = 0;
    
    if (trips.empty()) {
        while (true) {
            ClearConsole();
            std::cout << "\n\n|--- Remove trip ---|\n";

            std::cout << "\n\nUnfortunately, there are no trips (no one to delete)";
            std::cout << "\n1) Back to \"Trips\"";
            std::cout << "\n2) Go to the \"Main menu\"";
            std::cout << "\n3) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
                case 1:
                    co_await SwitchTo{handles.trips_menu}; 
                    break;
                    
                case 2:
                     co_await SwitchTo{handles.main_menu}; 
                    break;
                    
                case 3:
                    if (ConfirmationOfProgramCompletionMenu()){
                        StopInterface();
                    }
                    break;

                default:
                    std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                    break;
            }
        }
    } 

    size_t trip_index = 0;
    bool try_again_select_trip = true;
    bool remove_another_trip = true;

    while(remove_another_trip){
        remove_another_trip = false;

        ClearConsole();
        std::cout << "\n\n|--- Remove trip ---|\n";

        std::cout << "\nTrips: \n";
        ShowListOfCollectionElementNames(trips);

        std::cout << "\n\nSelect the number of the trip you want to remove: ";
        ValidatedInput(trip_index);

        if (trip_index < 1 || trip_index > trips.size()) {
            while (try_again_select_trip) {
                try_again_select_trip = false;

                std::cout << "\n\nThere is no trip with such a serial number.";
                std::cout << "\n1) Try again";
                std::cout << "\n2) Back to \"Trips\"";
                std::cout << "\n3) Go to \"Main menu\"";
                std::cout << "\n4) Close the program";

                std::cout << "\n\nEnter item number: ";
                ValidatedInput(menu_item);
                switch (menu_item) {
                    case 1:
                        try_again_select_trip = true;
                        break;

                    case 2:
                        co_await SwitchTo{handles.trips_menu}; 
                        break;
                        
                    case 3:
                         co_await SwitchTo{handles.main_menu}; 
                        break;
                        
                    case 4:
                        if (ConfirmationOfProgramCompletionMenu()){
                            StopInterface();
                        }
                        break;

                    default:
                        std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                        break;
                }
                if (try_again_select_trip) break;
            } 
            if (try_again_select_trip) continue;
        }
    

        auto delete_trip = trips.begin();
        std::advance(delete_trip, trip_index - 1);

        auto name = (*delete_trip)->GetFullName();
        auto id = (*delete_trip)->GetPersonalId();

        trips.remove(*delete_trip);
        std::cout << "\nTrip \"" << name << "\" has been removed.";

        SaveMessage("Trip by name \"" + name + "\" has been removed." + " His/Her id : " + std::to_string(id), historyDataPath);
        
        while (true) {
            std::cout << "\n\n1) Remove another trip";
            std::cout << "\n2) Back to \"Trips\"";
            std::cout << "\n3) Go to \"Main menu\"";
            std::cout << "\n4) Close the program";

            std::cout << "\n\nEnter item number: ";
            ValidatedInput(menu_item);
            switch (menu_item) {
                case 1:
                    remove_another_trip = true;
                    break;

                case 2:
                    co_await SwitchTo{handles.trips_menu}; 
                    break;
                    
                case 3:
                     co_await SwitchTo{handles.main_menu}; 
                    break;
                    
                case 4:
                    if (ConfirmationOfProgramCompletionMenu()){
                        StopInterface();
                    }
                    break;

                default:
                    std::cout << "\n\n!!! Incorrect action number entered. Try again:";
                    break;
            }
            if (remove_another_trip) break;
        }
    }
}




