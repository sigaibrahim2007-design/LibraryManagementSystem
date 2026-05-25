#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    char name[50];
    double balance;

public:
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        cin.ignore();

        cout << "Enter Customer Name: ";
        cin.getline(name,50);

        cout << "Enter Initial Deposit Amount: ";
        cin >> balance;

        cout << "\nAccount Created Successfully.\n";
    }

    void showAccount() const {
        cout << "\n-----------------------------";
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nCustomer Name  : " << name;
        cout << "\nBalance        : Rs." << fixed << setprecision(2) << balance;
        cout << "\n-----------------------------\n";
    }

    int getAccountNo() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if(amount > balance){
            return false;
        }

        balance -= amount;
        return true;
    }
};

void writeAccount() {
    BankAccount acc;

    ofstream file("bank.dat", ios::binary | ios::app);

    if(!file){
        cout << "File Error!\n";
        return;
    }

    acc.createAccount();

    file.write(reinterpret_cast<char*>(&acc),sizeof(acc));

    file.close();
}

void displayAllAccounts() {

    BankAccount acc;

    ifstream file("bank.dat", ios::binary);

    if(!file){
        cout << "\nNo records found.\n";
        return;
    }

    while(file.read(reinterpret_cast<char*>(&acc),sizeof(acc))){
        acc.showAccount();
    }

    file.close();
}

void searchAccount(int accNo){

    BankAccount acc;
    bool found=false;

    ifstream file("bank.dat", ios::binary);

    while(file.read(reinterpret_cast<char*>(&acc),sizeof(acc))){

        if(acc.getAccountNo()==accNo){
            acc.showAccount();
            found=true;
            break;
        }
    }

    file.close();

    if(!found){
        cout<<"\nAccount not found.\n";
    }
}

void depositMoney(int accNo){

    BankAccount acc;
    bool found=false;
    double amount;

    fstream file("bank.dat",ios::binary|ios::in|ios::out);

    while(file.read(reinterpret_cast<char*>(&acc),sizeof(acc))){

        if(acc.getAccountNo()==accNo){

            cout<<"\nEnter Amount to Deposit: ";
            cin>>amount;

            if(amount<=0){
                cout<<"Invalid amount.\n";
                return;
            }

            acc.deposit(amount);

            int pos=(-1)*static_cast<int>(sizeof(acc));

            file.seekp(pos,ios::cur);

            file.write(reinterpret_cast<char*>(&acc),sizeof(acc));

            cout<<"\nAmount Deposited Successfully.\n";

            found=true;
            break;
        }
    }

    file.close();

    if(!found){
        cout<<"\nAccount not found.\n";
    }
}

void withdrawMoney(int accNo){

    BankAccount acc;
    bool found=false;
    double amount;

    fstream file("bank.dat",ios::binary|ios::in|ios::out);

    while(file.read(reinterpret_cast<char*>(&acc),sizeof(acc))){

        if(acc.getAccountNo()==accNo){

            cout<<"\nEnter Amount to Withdraw: ";
            cin>>amount;

            if(amount<=0){
                cout<<"Invalid amount.\n";
                return;
            }

            if(acc.withdraw(amount)){

                int pos=(-1)*static_cast<int>(sizeof(acc));

                file.seekp(pos,ios::cur);

                file.write(reinterpret_cast<char*>(&acc),sizeof(acc));

                cout<<"\nWithdrawal Successful.\n";
            }
            else{
                cout<<"\nInsufficient Balance.\n";
            }

            found=true;
            break;
        }
    }

    file.close();

    if(!found){
        cout<<"\nAccount not found.\n";
    }
}

int main() {

    int choice,accNo;

    do{

        cout<<"\n========== BANK MANAGEMENT SYSTEM ==========\n";

        cout<<"1. Create Account\n";
        cout<<"2. Display All Accounts\n";
        cout<<"3. Search Account\n";
        cout<<"4. Deposit Money\n";
        cout<<"5. Withdraw Money\n";
        cout<<"6. Exit\n";

        cout<<"\nEnter Choice: ";
        cin>>choice;

        switch(choice){

            case 1:
                writeAccount();
                break;

            case 2:
                displayAllAccounts();
                break;

            case 3:
                cout<<"Enter Account Number: ";
                cin>>accNo;
                searchAccount(accNo);
                break;

            case 4:
                cout<<"Enter Account Number: ";
                cin>>accNo;
                depositMoney(accNo);
                break;

            case 5:
                cout<<"Enter Account Number: ";
                cin>>accNo;
                withdrawMoney(accNo);
                break;

            case 6:
                cout<<"\nThank You.\n";
                break;

            default:
                cout<<"\nInvalid Choice.\n";
        }

    }while(choice!=6);

    return 0;
}