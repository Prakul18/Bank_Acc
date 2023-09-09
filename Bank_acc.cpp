#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <ctime>
using namespace std;

class Account
{
private :
    string f_name, l_name;
    unsigned int acc_no = 0;
    int pin,age;
    string gender;
    unsigned long int mob_no;
    double acc_balance = 0;
    vector<vector<string>> content;
    int row_no;
    
public :
    
    // Read CSV file Bank_accounts and stores it in vector<vector<string>> 2D vectors of strings
    // Process takes place every iteration to update the content
    void get_content()
    {
        fstream fin;
        vector<string> row;
	    string line, word;
        bool found=0;
        content.clear();
        
        fin.open("Bank_accounts.csv", ios::in);

        if(fin.is_open())
        {
            while(getline(fin, line))
            {
                row.clear();
                stringstream str(line);

                while(getline(str, word, ','))
                {
                    row.push_back(word);
                }
                content.push_back(row);
            }
        }

        fin.close();
    }

    // To check if the given entered string is a number or not.
    bool isNumber(const string& s)
    {
        for (char const &ch : s)
        {
            if (isdigit(ch) == 0) 
                return false;
        }
        return true;
    }

    // Making a new account with necessary details and checks.
    // Adding all the information inputted into Bank_accounts.csv file
    int sign_up()
    {
        // Taking input in string so that program continues without errors.
        string acc_nocheck, agecheck, mob_nocheck, pinc, checkpin;
        bool check;
        cout << "Enter your first name: ";
        cin >> f_name;
        cout << "Enter your last name: ";
        cin >> l_name;
        cout << "Enter account number(Natural number): ";
        cin >> acc_nocheck;

        check = isNumber(acc_nocheck);
        if(check == 0 || stoi(acc_nocheck)<0)
        {
            cout << "Account number must be natural number please sign-up again." << endl;
            return 0;
        }

        if(acc_nocheck == "0")
        {
            cout << "Not possible to take this acc_no" << endl;
            return 0;
        }

        for(int i=0; i<content.size() ; i++)
        {
            if(acc_nocheck == content[i][0])
            {
                cout << "Account number already taken. Please choose another number." << endl;
                return 0;
            }
        }

        cout << "Enter Age(Natural number): ";
        cin >> agecheck;
        check = isNumber(agecheck);

        if(check == 0 || stoi(agecheck)<0)
        {
            cout << "Age must be natural number please sign-up again." << endl;
            return 0;
        }

        if (stoi(agecheck)<18)
        {
            cout << "Age must be above 18years" << endl;
            return 0;
        }

        cout << "Enter Gender(M or F or T[third gender]): ";
        cin >> gender;

        cout << "Enter mobile number(Natural number)";
        cin >> mob_nocheck;
        check = isNumber(mob_nocheck);
        if(check == 0 || stoi(mob_nocheck)<0)
        {
            cout << "Mobile number must be natural number please sign-up again." << endl;
            return 0;
        }

        cout << "Enter pin(Natural number)";
        cin >> pinc;
        check = isNumber(pinc);

        if(check == 0 || stoi(pinc)<0)
        {
            cout << "Pin must be natural number please sign-up again." << endl;
            return 0;
        }

        cout << "Confirm pin";
        cin >> checkpin;

        if (pinc != checkpin)
        {
            cout << "Both the pins should be same, Please try again." << endl;
            return 0;
        }
        // Converting all the strings into integers.
        acc_no = stoi(acc_nocheck);
        age = stoi(agecheck);
        mob_no = stoi(mob_nocheck);
        pin = stoi(pinc);

        fstream fout;
        fout.open("Bank_accounts.csv", ios::out | ios::app);

        fout << acc_no << ","
             << f_name << ","
             << l_name << ","
             << age << ","
             << gender << ","
             << mob_no << ","
             << acc_balance << ","
             << pin << "\n";

        fout.close();

        cout << "Account succesfully created "<< endl;
        return 0;
    }

    // Login into already made account by giving account number and password.
    void login()
    {
        fstream fin;
        string checkacc_no;
        string ch_pin;
        cout << "Enter account number to check its details: ";
        cin >> checkacc_no;
        cout << "Enter pin: ";
        cin >> ch_pin;
        
        bool found=0;

        // Storing all the details into the private variables
        for(int i=0; i<content.size() ; i++)
        {
            if(content[i][0] == checkacc_no)
            {
                found = 1;
                if(content[i][7] == ch_pin)
                {                        
                    acc_no = stoi(content[i][0]);
                    f_name = content[i][1];
                    l_name = content[i][2];
                    age = stoi(content[i][3]);
                    gender = content[i][4];
                    mob_no = stoi(content[i][5]);                        
                    acc_balance = stoi(content[i][6]);
                    row_no = i;
                }
                else
                {
                    cout << "Incorrect Password. Try Again" << endl;
                    break;
                }
            }
        }

        if(found == 0)
        {
            cout << "Account Number Not Present." << endl;
        }

        fin.close();
    }

    // Displays all account details except password
    void display_details()
    {  
        cout << "Acc number : " << acc_no << endl;
        cout << "Name       : " << f_name << " " << l_name << endl;
        cout << "Age        : " << age << endl;
        cout << "Gender     : " << gender << endl;
        cout << "Mobile no  : " << mob_no << endl;
        cout << "Balance    : " << acc_balance << endl;
    }

    // Displays balance
    void dis_balance()
    {
        acc_balance = stoi(content[row_no][6]);
        cout << "Balance : " << acc_balance << endl;
    }

    /* Used to update the records on balances after transfer,withdraw and transactions.
    // Done by deleting file and making another file with same name and storing the 2D vector
    // in the file after changes*/
    void update_records()
    {
        fstream fout;
        remove("Bank_accounts.csv");
        fout.open("Bank_accounts.csv", ios::out);
        
        for(int i =0; i<content.size() ; i++)
        {
            for(int j=0; j<content[i].size() ; j++)
            {
                fout << content[i][j] << ",";
            }
            fout << "\n";
        }
        fout.close();
    }

    // Depositing money into bank account
    int deposit()
    {
        string deposit;
        acc_balance = stoi(content[row_no][6]);
        cout << "Enter money to deposit: ";
        cin >> deposit;

        if(!isNumber(deposit) || stoi(deposit)<0)
        {
            cout << "Deposit must be natural number" << endl;
            return 0;
        }

        // updating content
        acc_balance += stoi(deposit);
        content[row_no][6] = to_string(acc_balance);
        update_records();
        dis_balance();

        // Adding account number, money and time at which deposit was made is stored in Transaction.csv
        fstream fout;
        fout.open("Transaction.csv", ios::out | ios::app);
        time_t now = time(0);
        string dt = ctime(&now);
        for(int i=0;i<dt.length();i++) 
            if(dt[i]=='\n') 
                dt.erase(dt.begin()+i);
        fout << dt << ","
             << "d" << ","
             << acc_no << ","
             << deposit << ","
             << endl ;
        cout << "Deposit succesful" << endl;
        fout.close();
        return 0;
    }

    // Withdrawing money from bank account
    // The balance cannot go into negatives so cant withdraw value more than balance
    void withdraw()
    {
        float withdraw;
        acc_balance = stoi(content[row_no][6]);
        cout << "Balance : " << acc_balance << endl;
        cout << "Enter money to withdraw: ";
        cin >> withdraw;
        acc_balance -= withdraw;

        if(acc_balance >= 0)
        {
            cout << "Withdraw succesful" << endl;
            cout << "Balance after withdraw: " << acc_balance << endl;
            // updating balance
            content[row_no][6] = to_string(acc_balance);
            update_records();
            // Adding account number, money and time at which withdrawl was made is stored in Transaction.csv
            fstream fout;
            fout.open("Transaction.csv", ios::out | ios::app);
            time_t now = time(0);
            string dt = ctime(&now);
            for(int i=0;i<dt.length();i++) 
                if(dt[i]=='\n') 
                    dt.erase(dt.begin()+i);
            fout << dt << ","
                 << "w" << ","
                 << acc_no << ","
                 << withdraw << ","
                 << endl  ;
            fout.close();
        }
        else
        {
            cout << "Insufficient balance, Balance should remain positive" << endl;
            acc_balance += withdraw;
        }
    }

    // Transfer money from one account to another using account number by checking all account conditions
    int transfer()
    {
        string acc_numsend, amt_transferstr;
        int rankrow, check=1;
        cout << "Enter acc_no of who you want to transfer: ";
        cin >> acc_numsend;

        if(!isNumber(acc_numsend))
        {
            cout << "Account number is natural number" << endl;
            return 0;
        }

        cout << "Enter amount to transfer: ";
        cin >> amt_transferstr;

        if(!isNumber(amt_transferstr))
        {
            cout << "Amount is a natural number" << endl;
            return 0;
        }

        int amt_transfer = stoi(amt_transferstr);

        for (int i=0; i<content.size(); i++)
        {
            if(content[i][0] == acc_numsend)
            {
                rankrow = i;
                check = 0;
                break;
            }
        }

        if(check == 1)
        {
            cout << "Account does not exist." << endl;
            return 0;
        }

        if(stoi(content[row_no][6]) >= amt_transfer)
        {
            acc_balance -= amt_transfer;
            content[row_no][6] = to_string(acc_balance);
        }
        else
        {
            cout << "Amount wanted to transfer exceeds account balance. Not possible";
            return 0;
        }

        content[rankrow][6] = to_string(stoi(content[rankrow][6]) + amt_transfer);

        // Adding account number, money and time at which transaction was made is stored in Transaction.csv
        fstream fout;
        fout.open("Transaction.csv", ios::out | ios::app);
        time_t now = time(0);
        string dt = ctime(&now);
        for(int i=0;i<dt.length();i++) 
            if(dt[i]=='\n') 
                dt.erase(dt.begin()+i);
        fout << dt << ","
             << "t" << ","
             << acc_no << ","
             << amt_transfer << "," 
             << acc_numsend << ","
             << endl ;
        fout.close();

        cout << "Transaction succesful" << endl;
        update_records();
        return 0;
    }

    // To check if login was succesful or not
    bool check_login()
    {
        if(acc_no == 0)
            return 1;
        else
            return 0;
    }

    // To display the transaction history of a specific account by reading from transaction.csv
    void tran_history()
    {
        // vector<vector<string>> t_content to store the transaction.csv file
        vector<vector<string>> t_content;
        vector<string> row;
	    string line, word;
        bool found=0;
        t_content.clear();

        fstream fin;
        fin.open("Transaction.csv", ios::in);

        if(fin.is_open())
        {
            while(getline(fin, line))
            {
                row.clear();

                stringstream str(line);

                while(getline(str, word, ','))
                {
                    row.push_back(word);
                }
                t_content.push_back(row);
            }
        }

        // Checks which transactions are related to the logged in account
        for (int i=0; i<(t_content.size()); i++)
        {
            //Gives custom sentences for deposit, withdraw, transfer 
            if(stoi(t_content[i][2]) == acc_no)
            {
                found = 1;
                if((t_content[i][1]) == "d")
                {
                    cout << t_content[i][2] << "Rs - Self Deposited on "<< t_content[i][0] << endl;
                }
                if((t_content[i][1]) == "w")
                {
                    cout << t_content[i][2] << "Rs - Withdraw "<< t_content[i][0] << endl;
                }
                if((t_content[i][1]) == "t")
                {
                    cout << t_content[i][2] << "Rs - Transfered to Account number " << t_content[i][3] << " on "<< t_content[i][0] << endl;
                }
            }

            if(t_content[i].size() == 5)
            {
                if(stoi(t_content[i][4]) == acc_no)
                {
                    found = 1;
                    cout << t_content[i][3] << "Rs - " << t_content[i][2] << " transferred you" << t_content[i][0] << endl;
                }
            }
        }

        if(found == 0)
        {
            cout << "No transactions made yet." << endl;
        }
        fin.close();
    }

    // Logging out of the account by equating all the private variables to 0
    void logout()
    {
        acc_no = 0;
        f_name = "0";
        l_name = "0";
        age = 0;
        gender = "0";
        mob_no = 0;
        acc_balance = 0;
        row_no = 1000;
    }

};

// Main function - Execution starts here
int main()
{
    // Making object client
    Account client;

    int choice;
    string choicestr;
    bool loop = 1;
    bool notlogin = 1;

    // Loop will continue running until the user Enters particulat number to exit code
    while (loop)
    {
        client.get_content(); // Copies the Bank_accounts.csv file into vector<vector<string>> content

        // If not logged in then will ask the user to create a new account, login or exit.
        if(notlogin)
        {
            cout << "Choose your Choice" << endl;
            cout << "Enter 1 to Sign-up" << endl;
            cout << "Enter 2 to Login" << endl;
            cout << "Enter 3 to Exit" << endl;
            cin >> choicestr;
            if(client.isNumber(choicestr))
                choice = stoi(choicestr);
            else
            {
                cout << "Enter any of the choice numbers." << endl;
                continue;
            }

            switch (choice)
            {
                case 1: 
                    client.sign_up();
                    break;
                case 2:
                    client.login();
                    notlogin = client.check_login(); // checks if login was succesfull or not
                    if(!notlogin)
                        cout << "Login succesful" << endl;
                    break;
                case 3:
                    loop = 0;
                    break;
                default:
                    cout << "Enter valid choice" << endl;
                    break;
            }
        }

        // If loggined will ask which operation the user wants.
        else
        {
            cout << "Choose your Choice" << endl;
            cout << "Enter 1 to Display Details" << endl;
            cout << "Enter 2 to Display balance" << endl;
            cout << "Enter 3 to Deposit" << endl;
            cout << "Enter 4 to Withdraw" << endl;
            cout << "Enter 5 to Transfer" << endl;
            cout << "Enter 6 to Logout" << endl;
            cout << "Enter 7 to Transaction History" << endl;
            cout << "Enter 8 to Exit " << endl;
            cin >> choicestr;

            if(client.isNumber(choicestr))
                choice = stoi(choicestr);
            else
            {
                cout << "Enter any of the choice numbers." << endl;
                continue;
            }

            switch (choice)
            {
                case 1:
                    client.display_details();
                    break;
                case 2:
                    client.dis_balance();
                    break;
                case 3:
                    client.deposit();
                    break;
                case 4:
                    client.withdraw();
                    break;
                case 5:
                    client.transfer();
                    break;
                case 6:
                    client.logout();
                    notlogin=1;
                    break;
                case 7:
                    client.tran_history();
                    break;
                case 8:
                    loop = 0;
                    break;
                default:
                    cout << "Invalid response";
                    break;

            }
        }
    }

    return 0;
}