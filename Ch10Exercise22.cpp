#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class bankAccount
{
protected:
    int accountNumber;
    double balance;

public:
    bankAccount()
    {
        accountNumber = 0;
        balance = 0.0;
    }

    bankAccount(int number, double amount)
    {
        accountNumber = number;
        balance = amount;
    }

    void setAccountNumber(int number)
    {
        accountNumber = number;
    }

    int getAccountNumber()
    {
        return accountNumber;
    }

    double getBalance()
    {
        return balance;
    }

    void deposit(double amount)
    {
        if (amount > 0)
            balance += amount;
    }

    virtual void withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
            balance -= amount;
        else
            cout << "Insufficient funds." << endl;
    }

    virtual void printAccountInfo()
    {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << fixed << setprecision(2)
             << balance << endl;
    }
};

class checkingAccount : public bankAccount
{
private:
    double interestRate;
    double minimumBalance;
    double serviceCharges;

public:
    checkingAccount() : bankAccount()
    {
        interestRate = 0.0;
        minimumBalance = 0.0;
        serviceCharges = 0.0;
    }

    checkingAccount(int number, double amount,
                    double rate, double minimum, double charges)
        : bankAccount(number, amount)
    {
        interestRate = rate;
        minimumBalance = minimum;
        serviceCharges = charges;
    }

    void setInterestRate(double rate)
    {
        interestRate = rate;
    }

    double getInterestRate()
    {
        return interestRate;
    }

    void setMinimumBalance(double amount)
    {
        minimumBalance = amount;
    }

    double getMinimumBalance()
    {
        return minimumBalance;
    }

    void setServiceCharges(double charges)
    {
        serviceCharges = charges;
    }

    double getServiceCharges()
    {
        return serviceCharges;
    }

    void postInterest()
    {
        balance += balance * interestRate / 100;
    }

    bool lessThanMinimumBalance()
    {
        return balance < minimumBalance;
    }

    void writeCheck(double amount)
    {
        cout << "Writing a check for $" << amount << endl;
        withdraw(amount);
    }

    void withdraw(double amount) override
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;

            if (lessThanMinimumBalance())
            {
                balance -= serviceCharges;
                cout << "Service charge applied: $"
                     << serviceCharges << endl;
            }
        }
        else
        {
            cout << "Insufficient funds." << endl;
        }
    }

    void printAccountInfo() override
    {
        cout << "\nChecking Account" << endl;
        bankAccount::printAccountInfo();
        cout << "Interest Rate: " << interestRate << "%" << endl;
        cout << "Minimum Balance: $" << minimumBalance << endl;
        cout << "Service Charges: $" << serviceCharges << endl;
    }
};

class savingsAccount : public bankAccount
{
private:
    double interestRate;

public:
    savingsAccount() : bankAccount()
    {
        interestRate = 0.0;
    }

    savingsAccount(int number, double amount, double rate)
        : bankAccount(number, amount)
    {
        interestRate = rate;
    }

    void setInterestRate(double rate)
    {
        interestRate = rate;
    }

    double getInterestRate()
    {
        return interestRate;
    }

    void postInterest()
    {
        balance += balance * interestRate / 100;
    }

    void withdraw(double amount) override
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
        }
        else
        {
            cout << "Lack of funds in savings account." << endl;
        }
    }

    void printAccountInfo() override
    {
        cout << "\nSavings Account" << endl;
        bankAccount::printAccountInfo();
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

int main()
{
    checkingAccount checking(1001, 1500.00, 2.5, 1000.00, 25.00);

    checking.printAccountInfo();

    checking.deposit(200.00);
    cout << "\nAfter depositing $200:" << endl;
    checking.printAccountInfo();

    checking.writeCheck(800.00);
    cout << "\nAfter writing a check:" << endl;
    checking.printAccountInfo();

    checking.postInterest();
    cout << "\nAfter posting interest:" << endl;
    checking.printAccountInfo();

    savingsAccount savings(2001, 3000.00, 3.0);

    savings.printAccountInfo();

    savings.deposit(500.00);
    cout << "\nAfter depositing $500:" << endl;
    savings.printAccountInfo();

    savings.withdraw(400.00);
    cout << "\nAfter withdrawing $400:" << endl;
    savings.printAccountInfo();

    savings.postInterest();
    cout << "\nAfter posting interest:" << endl;
    savings.printAccountInfo();

    return 0;
}
