#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base User class
class User
{
private:
    string username, password;

public:
    User(string name, string pass) : username(name), password(pass) {}

    string getUsername() const
    {
        return username;
    }

    void setUsername(const string &name)
    {
        username = name;
    }

    string getPassword() const
    {
        return password;
    }

    void setPassword(const string &pass)
    {
        password = pass;
    }

    virtual string getRole() const = 0; // Pure virtual function

    virtual ~User() {}
};

// Derived class for Admin User
class AdminUser : public User
{
public:
    AdminUser(string name, string pass) : User(name, pass) {}

    string getRole() const override
    {
        return "Admin";
    }
};

// Derived class for Regular User
class RegularUser : public User
{
public:
    RegularUser(string name, string pass) : User(name, pass) {}

    string getRole() const override
    {
        return "Regular";
    }
};

// UserManager class to handle users
class UserManager
{
private:
    vector<User *> users; // Use pointers to handle polymorphism

    bool userExists(const string &username) const
    {
        for (const auto &user : users)
        {
            if (user->getUsername() == username)
            {
                return true;
            }
        }
        return false;
    }

public:
    void registerUser()
    {
        string username, password;
        int userType;
        cout << "\t\tEnter User Name: ";
        cin >> username;
        cout << "\t\tEnter Password: ";
        cin >> password;
        cout << "\t\tEnter User Type (1 for Admin, 2 for Regular): ";
        cin >> userType;

        if (userExists(username))
        {
            cout << "\t\tUsername already taken. Try a different one." << endl;
            return;
        }

        User *newUser;
        if (userType == 1)
        {
            newUser = new AdminUser(username, password);
        }
        else
        {
            newUser = new RegularUser(username, password);
        }
        users.push_back(newUser);

        cout << "\t\tUser registered successfully." << endl;
    }

    bool loginUser(const string &name, const string &pass) const
    {
        for (const auto &user : users)
        {
            if (user->getUsername() == name && user->getPassword() == pass)
            {
                cout << "\t\tLogin successfully as " << user->getRole() << "." << endl;
                return true;
            }
        }
        cout << "\t\tInvalid username or password." << endl;
        return false;
    }

    void showUsers() const
    {
        if (users.empty())
        {
            cout << "\t\tNo users found." << endl;
        }
        else
        {
            cout << "\t\t--- Users List ---" << endl;
            for (const auto &user : users)
            {
                cout << "\t\t" << user->getUsername() << " (" << user->getRole() << ")" << endl;
            }
        }
    }

    void searchUser(const string &username) const
    {
        if (users.empty())
        {
            cout << "\t\tNo users found." << endl;
            return;
        }

        for (const auto &user : users)
        {
            if (user->getUsername() == username)
            {
                cout << "\t\tUser found: " << username << " (" << user->getRole() << ")" << endl;
                return;
            }
        }
        cout << "\t\tUser not found." << endl;
    }

    void deleteUser(const string &username)
    {
        if (users.empty())
        {
            cout << "\t\tNo users found." << endl;
            return;
        }

        for (auto it = users.begin(); it != users.end(); ++it)
        {
            if ((*it)->getUsername() == username)
            {
                delete *it;
                users.erase(it);
                cout << "\t\tUser removed successfully." << endl;
                return;
            }
        }
        cout << "\t\tUser not found." << endl;
    }

    ~UserManager()
    {
        for (auto user : users)
        {
            delete user;
        }
    }
};

// Menu class to handle user interface
class Menu
{
private:
    UserManager userManager;

public:
    void displayMenu()
    {
        int option;
        char choice;

        do
        {
            cout << "\n\n\t\t1. Register User" << endl;
            cout << "\t\t2. Login" << endl;
            cout << "\t\t3. Show User List" << endl;
            cout << "\t\t4. Search User" << endl;
            cout << "\t\t5. Delete User" << endl;
            cout << "\t\t6. Exit" << endl;
            cout << "\t\tEnter Your Choice: ";
            cin >> option;

            switch (option)
            {
            case 1:
                userManager.registerUser();
                break;
            case 2:
            {
                string username, password;
                cout << "\t\tEnter Username: ";
                cin >> username;
                cout << "\t\tEnter Password: ";
                cin >> password;
                userManager.loginUser(username, password);
                break;
            }
            case 3:
                userManager.showUsers();
                break;
            case 4:
            {
                string username;
                cout << "\t\tEnter Username: ";
                cin >> username;
                userManager.searchUser(username);
                break;
            }
            case 5:
            {
                string username;
                cout << "\t\tEnter Username: ";
                cin >> username;
                userManager.deleteUser(username);
                break;
            }
            case 6:
                exit(0);
            default:
                cout << "\t\tInvalid choice. Please try again." << endl;
            }

            cout << "\t\tDo you want to continue? [Y/N]: ";
            cin >> choice;
        } while (choice == 'y' || choice == 'Y');
    }
};

int main()
{
    system("cls");
    Menu menu;
    menu.displayMenu();
    return 0;
}
