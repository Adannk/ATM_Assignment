/* DECLARATIONS START */
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

struct ATM
{
    void CreateNewAccount(string newUsername, string newPassword);
    void AccountLogin(string loginUsername, string loginPassword);
    void DepositMoney(double depositAmount);
    void WithdrawMoney(double withdrawalAmount);
    void SetAccountLogin(int setAccountLocation);
    void SetLastMoneyMovement(int accountID, double amount);
    void SetBeginningBalance(int accountID);
    void SetLastOperation(int accountID, char userInput);
    void AccountMenu();
    double GetLastMoneyMovement(int accountID) const;
    double GetAccountBalance(int accountID) const;
    double GetBeginningBalance(int accountID) const;
    char GetLastOperation(int accountID) const;
    string GetUsername(int accountID) const;
    int loggedInAccountLocation = -1;
    double accountBalance = 0;
    double beginningBalance = 0;
    double lastMoneyMovement = 0;
    char lastOperation = '\0';
    string username = "";
    string password = "";
} tUser;
vector <ATM> tAccountList;
bool bMenu = true;
/* DECLARATIONS END */

/*INIT START*/
int main()
{
    while (bMenu)
    {
        std::string username, password;
        std::cout << "\nWelcome to Adams ATM Machine\n";
        std::cout << "C. Create Account\nL. Login\nQ. Quit\n";
        char menuChoise;
        std::cout << "\n>";
        std::cin >> menuChoise;
        switch (toupper(menuChoise))
        {
            case 'C':
                std::cout << "\nEnter User name: ";
                std::cin >> username;
                std::cout << "Enter User password: ";
                std::cin >> password;
                tUser.CreateNewAccount(username, password);
                break;

            case 'L':
                std::cout << "\nEnter User name: ";
                std::cin >> username;
                std::cout << "Enter User password: ";
                std::cin >> password;
            
                tUser.AccountLogin(username, password); 

                if (tUser.loggedInAccountLocation >= 0)
                {
                    //sends you to account menu if login is complete
                    tUser.AccountMenu();
                }                        
                else
                    //breaks case if login failed   
                    break;
                break;

            case 'Q':
                bMenu = false;
                break;

            default:
                std::cout << "\nWrong Input\n";
                break;
        }
    }

}
/*INIT END*/

/*FUNCTIONS START*/
void ATM::CreateNewAccount(string newUsername, string newPassword)
{
    tUser.username = newUsername;
    tUser.password = newPassword;
    tUser.beginningBalance = 0;
    tUser.accountBalance = 0;
    tUser.lastMoneyMovement = 0;

    // while (bCreateAccount)
    // {
    //     loggedInAccountLocation = countingCreatedAccounts;
    //     countingCreatedAccounts++;
    //     bCreateAccount = false;
    // }
    
    tAccountList.push_back(tUser);
    
    std::cout << "\nThank you, your account has been created!\n";
}
void ATM::AccountLogin(string loginUsername, string loginPassword)
{
    bool bFound = false;
    for (int i = 0; i < tAccountList.size(); i++)
    {
        if ((loginUsername == tAccountList[i].username) 
        && (loginPassword == tAccountList[i].password))
        {
            bFound = true;
            std::cout << "\nAccess granted: " << GetUsername(i) << std::endl;
            //set login with index found in vector
            SetAccountLogin(i);
        }
    }

    if (!bFound)
    {
        std::cout << "\n******Login Failed******\n";
    }
}
void ATM::AccountMenu()
{
    bool bAccountMenu = true;

    while (bAccountMenu)
    {
        std::cout << "\nD. Deposit Money\nW. Withdraw Money\nB. Request Balance\nL. Logout\nQ. Quit\n";
        char cAccountMenuInput;
        std::cout << "\n>";
        std::cin >> cAccountMenuInput;
        switch (toupper(cAccountMenuInput))
        {
        case 'D':
            double depositMoney;
            std::cout << "\nEnter Amount to Deposit: ";
            std::cin >> depositMoney;
            if ((depositMoney > 0) && (depositMoney < 2000000))
            {
                DepositMoney(depositMoney);
            }
            else   
            {
                std::cout << "Enter a positive and lower number then 2M\n";
            }
            break;

        case 'W':
            double withdrawlMoney;
            std::cout << "\nEnter Amount to Withdraw: ";
            std::cin >> withdrawlMoney;
            if ((depositMoney > 0) && (depositMoney < 2000000))
            {
                WithdrawMoney(withdrawlMoney);
            }
            else
            {
                std::cout << "Enter a positive and lower number then 2M\n";
            }

            break;

        case 'B':
            std::cout << "\nBeginning Balance: SEK" << GetBeginningBalance(loggedInAccountLocation) << std::endl;

            if (tAccountList[loggedInAccountLocation].lastOperation == 'D')
            {
                std::cout << "Depsoit amount: SEK" << GetLastMoneyMovement(loggedInAccountLocation) << std::endl;
            }
            else if (tAccountList[loggedInAccountLocation].lastOperation == 'W')
            {
                std::cout << "Withdrawl amount: SEK" << GetLastMoneyMovement(loggedInAccountLocation) << std::endl;
            }

            std::cout << "Your balance is: SEK" << GetAccountBalance(loggedInAccountLocation) << std::endl;
            break;

        case 'L':
            //resets active user
            loggedInAccountLocation = -1;
            bAccountMenu = false;
            break;

        case 'Q':
            bAccountMenu = false;
            bMenu = false;
            break;
        
        default:
            std::cout << "\nWrong Input\n";
            break;
        }
    }
}
void ATM::DepositMoney(double depositAmount)
{
    SetBeginningBalance(loggedInAccountLocation);
    tAccountList[loggedInAccountLocation].accountBalance += depositAmount;
    SetLastMoneyMovement(loggedInAccountLocation, depositAmount);
    tAccountList[loggedInAccountLocation].SetLastOperation(loggedInAccountLocation, 'D');
}
void ATM::WithdrawMoney(double withdrawalAmount)
{   
    if (withdrawalAmount <= tAccountList[loggedInAccountLocation].accountBalance)
    {
        SetBeginningBalance(loggedInAccountLocation);
        tAccountList[loggedInAccountLocation].accountBalance -= withdrawalAmount;
        SetLastMoneyMovement(loggedInAccountLocation, withdrawalAmount);
        tAccountList[loggedInAccountLocation].SetLastOperation(loggedInAccountLocation, 'W');
    }
    else
        std::cout << "\nNot enought funds\n";
}
void ATM::SetAccountLogin(int setAccountLocation)
{
    loggedInAccountLocation = setAccountLocation;
}
void ATM::SetLastMoneyMovement(int accountID, double amount)
{
    tAccountList[accountID].lastMoneyMovement = amount;
}
void ATM::SetBeginningBalance(int accountID)
{
    tAccountList[accountID].beginningBalance =  tAccountList[accountID].accountBalance;
}
void ATM::SetLastOperation(int accountID, char userInput)
{
    tAccountList[accountID].lastOperation = userInput;
}
double ATM::GetLastMoneyMovement(int accountID) const
{
    return tAccountList[accountID].lastMoneyMovement;
}
double ATM::GetAccountBalance(int accountID) const
{
    return tAccountList[accountID].accountBalance;
}
double ATM::GetBeginningBalance(int accountID) const
{
    return tAccountList[accountID].beginningBalance;
}
char ATM::GetLastOperation(int accountID) const
{
    return tAccountList[accountID].lastOperation;
}
string ATM::GetUsername(int accountID) const
{
    return tAccountList[accountID].username;
}
/*FUNCTIONS END*/