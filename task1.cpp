#include <iostream>
#include <vector>
#include <string>

// MenuItem class represents a single menu item in the menu tree
class MenuItem {
public:
    std::string name;           // Name of the menu item
    std::vector<MenuItem> subMenuItems; // List of submenu items

    MenuItem(const std::string& name) : name(name) {}

    // Add a submenu item to this menu item
    void addSubMenuItem(const MenuItem& item) {
        subMenuItems.push_back(item);
    }
};

// MenuSystem class for managing navigation and interaction
class MenuSystem {
private:
    std::vector<MenuItem> menuItems;  // Top-level menu items
    MenuItem* currentMenu;            // Pointer to the current menu item
    int currentSelection;             // Index of the current selection

public:
    // Constructor that sets up the initial menu structure
    MenuSystem() : currentMenu(nullptr), currentSelection(0) {
        // Create the menu structure
        MenuItem mainMenu("Main Menu");

        // Add submenus to Main Menu
        MenuItem settings("Settings");
        settings.addSubMenuItem(MenuItem("Display Settings"));
        settings.addSubMenuItem(MenuItem("Audio Settings"));
        mainMenu.addSubMenuItem(settings);

        // Add Media menu
        MenuItem media("Media");
        media.addSubMenuItem(MenuItem("Radio"));
        media.addSubMenuItem(MenuItem("Bluetooth Audio"));
        mainMenu.addSubMenuItem(media);

        // Set the main menu as the starting point
        menuItems.push_back(mainMenu);
        currentMenu = &menuItems[0]; // Start from the main menu
    }

    // Function to display the current menu options
    void displayMenu() {
        std::cout << "\n" << currentMenu->name << "\n";
        for (int i = 0; i < currentMenu->subMenuItems.size(); ++i) {
            std::cout << (i + 1) << ". " << currentMenu->subMenuItems[i].name << "\n";
        }
    }

    // Function to navigate through the menu (up, down, enter, back)
    void navigate() {
        bool running = true;
        while (running) {
            displayMenu();

            std::cout << "\nChoose an option (1 to navigate down, 2 to navigate up, 3 to enter, 4 to go back): ";
            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1: // Navigate Down (Select the current submenu)
                    if (currentSelection < currentMenu->subMenuItems.size()) {
                        currentMenu = &currentMenu->subMenuItems[currentSelection];
                        currentSelection = 0; // Reset selection to first submenu item
                    }
                    break;
                case 2: // Navigate Up (Go back to the previous menu)
                    if (currentMenu != &menuItems[0]) {
                        currentMenu = &menuItems[0]; // Go back to the top level
                        currentSelection = 0;
                    }
                    break;
                case 3: // Enter the submenu (choose option)
                    if (currentSelection < currentMenu->subMenuItems.size()) {
                        currentMenu = &currentMenu->subMenuItems[currentSelection];
                        currentSelection = 0;
                    }
                    break;
                case 4: // Go Back (Exit the program or go to previous menu)
                    running = false;
                    break;
                default:
                    std::cout << "Invalid option, please choose a valid number.\n";
                    break;
            }
        }
    }
};

// Main function
int main() {
    // Initialize the menu system
    MenuSystem menuSystem;
    
    // Start the navigation
    menuSystem.navigate();

    return 0;
}
