module;

#include <iostream>
#include <string>
#include <memory>
#include <coroutine>

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

   

struct MenuItemsHandles {
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
        std::coroutine_handle<> customers_add_customer_menu;
        std::coroutine_handle<> customers_remove_customer_menu;

};





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




///////////////////////////////////////////////////////////////////////////////////////////////////////
///
///  END MANAGERS MENU
///
///////////////////////////////////////////////////////////////////////////////////////////////////////




MenuItem MainMenu(const MenuItemsHandles& handles)
{
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
                //co_await CustomersMenu(Customers); 
                std::cout << "\n!!! Not ready yet !!!";  
                break;

            case 3:
                //co_await TripsMenu(Trips);
                std::cout << "\n!!! Not ready yet !!!";  
                break;

            case 4:
                //co_await OrderOrReturnMenu(Managers, Customers, Trips, OrdersPath, HistoryDataPath);
                std::cout << "\n!!! Not ready yet !!!";  
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





MenuItem ManagersMenu(const MenuItemsHandles& handles)
{
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

    while(true){

        ClearConsole();
        std::cout << "\n\n|--- Information about managers ---|";
        
        if (managers.empty()) {
            while (true) {
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




MenuItem ManagersShowFullInformationAboutManagerMenu(const ListSharedsManager_t& managers, const MenuItemsHandles& handles){
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
    size_t manager_index = 0;
    bool try_again_select_manager = true;
    bool remove_another_manager = true;

    while(remove_another_manager){
        remove_another_manager = false;

        ClearConsole();
        std::cout << "\n\n|--- Remove manager ---|\n";

        if (managers.empty()) {
            while (true) {
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





