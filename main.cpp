#include <iostream>
#include <fstream>

using namespace std;

class shopping{
private:
    int productCode;
    float price;
    float discount;
    string productName;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void shopping::menu() {
    m:
    int choice;
    string email;
    string password;

    cout << "\t\t\t\t________________________________________\n";
    cout << "\t\t\t\t________________________________________\n";
    cout << "\t\t\t\t       Supermarket Main Menu            \n";
    cout << "\t\t\t\t________________________________________\n";
    cout << "\t\t\t\t________________________________________\n";
    cout << "\t\t\t\t| 1) Administrator |\n";
    cout << "\t\t\t\t|                  |\n";
    cout << "\t\t\t\t| 2) Buyer         |\n";
    cout << "\t\t\t\t|                  |\n";
    cout << "\t\t\t\t| 3) exit          |\n";
    cout << "\t\t\t\t|                  |\n";
    cout << "\n\t\t\t Please select!    |\n";
    cin >> choice;
    
    switch (choice) {
        case 1:
            cout << "\t\t\t Please login   \n";
            cout << "\t\t\t Enter Email    \n";
            cin >> email;
            cout << "\t\t\t Enter Password \n";
            cin >> password;

            if (email == "admin@gmail.com" && password == "test"){
                administrator();
            }else {
                cout << "invalid username and password" << endl;
            }
            break;
        case 2:
            buyer();
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "Please select from the given options" << endl;
    }
    goto m;
}

void shopping::administrator() {
    m:
    int choice;
    cout << "\n\n\n\t\t\t Administrator menu";
    cout << "\n\n\n\t\t\t|________1) Add the product_____________|";
    cout << "\n\n\n\t\t\t|                                       |";
    cout << "\n\n\n\t\t\t|________2) Edit the product____________|";
    cout << "\n\n\n\t\t\t|                                       |";
    cout << "\n\n\n\t\t\t|________3) Delete the product__________|";
    cout << "\n\n\n\t\t\t|                                       |";
    cout << "\n\n\n\t\t\t|________4) Back to main menu-__________|";

    cout << "\n\n\t Please enter your choice ";
    cin >> choice;

    switch (choice) {
        case 1:
            add();
            break;
        case 2:
            edit();
            break;
        case 3:
            rem();
            break;
        case 4:
            menu();
        default:
            cout << "invalid choice" << endl;
    }
    goto m;
}

void shopping::buyer() {
    m:
    int  choice;
    cout << "\t\t\t  Buyer \n";
    cout << "\t\t\t______________________\n";
    cout << "\t\t\t                      \n";
    cout << "\t\t\t1) Buy product        \n";
    cout << "\t\t\t                      \n";
    cout << "\t\t\t2) Go back            \n";
    cout << "\t\t\t Enter your choice   :\n";
    cin>>choice;

    switch (choice) {
        case 1:
            receipt();
            break;
        case 2:
            menu();
            break;
        default:
            cout << "invalid choice";
    }
    goto m;
}

void shopping::add() {
    m:
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\n\n\t\t\t Add new product";
    cout << "\n\n\t Code of product";
    cin >> productCode;
    cout << "\n\n\t Name of product";
    cin >> productName;
    cout << "\n\n\t Price of product";
    cin >> price;
    cout << "\n\n\t Discount on product";
    cin >> discount;

    data.open("database.txt",ios::in);

    if (!data){
        data.open("database.txt", ios::app|ios::out);
        data << " " << productCode << " " << productName << " " << price << " " << discount << "\n";
        data.close();
    } else {
        data >> c >> n >> p >> d;
        while (!data.eof()) {
            if (c == productCode) {
                token++;
            }
            data >> c >> n >> p >> d;
        }
        data.close();

        if (token == 1) {
            goto m;
        } else {
            data.open("database.txt", ios::app | ios::out);
            data << " " << productCode << " " << productName << " " << price << " " << discount << "\n";
            data.close();
        }
    }
    cout << "record inserted \n";
}

void shopping::edit() {
    fstream data, data1;
    int pKey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << "\n\t\t\t Modify the product";
    cout << "\n\t\t\t Product code :";
    cin >> pKey;

    data.open("database.txt",ios::in);
    if (!data){
        cout << "file does not exist";
    }else {
        data1.open("database1.txt",ios::app|ios::out);
        data >> productCode >> productName >> price >> discount;
        while (!data.eof()){
            if (pKey == productCode){
                cout << "\n\t\t\t Product new code :";
                cin >> c;
                cout << "\n\t\t\t Product new name :";
                cin >> n;
                cout << "\n\t\t\t Product new price :";
                cin >> p;
                cout << "\n\t\t\t Product new discount :";
                cin >> d;
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\t\t\t record edited";
            }
            else {
                data1 << " " << productCode << " " << productName << " " << price << " " << discount << "\n";
            }
            data >> productCode >> productName >> price >> discount;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt","database.txt");

        if (token == 0) {
            cout << "record not found sorry !!";
        }
    }
}

void shopping::rem() {
    fstream data, data1;
    int pKey;
    int token = 0;
    cout << "\n\n\t Delete Product";
    cout << "\n\n\t Product code :";
    cin>>pKey;
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "file does not exist";
    }else{
        data1.open("database1.txt",ios::app|ios::out);
        data >> productCode >> productName >> price >> discount;

        while (!data.eof()){
            if (productCode == pKey){
                cout << "\n\n\t product deleted successfully";
                token++;
            }
            else {
                data1 << " " << productCode << " " << productName << " " << price << " " << discount << "\n";
            }
            data >> productCode >> productName >> price >> discount;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt","database.txt");

        if (token ==0){
            cout << "record not found \n";
        }
    }
}


void shopping::list() {
    fstream data;
    data.open("database.txt",ios::in);
    cout << "\n\n|____________________________________________________________________________________\n";
    cout << "ProNo\t\tName\t\tPrice\n";
    cout << "\n\n|____________________________________________________________________________________\n";
    data >> productCode >> productName >> price >> discount;

    while (!data.eof()){
        cout << productCode << "\t\t" << productName << "\t\t" << price << "\n";
        data >> productCode >> productName >> price >> discount;
    }
    data.close();
}

void shopping::receipt() {

    fstream data;
    int arrOfProductCodes[100];
    int arrOfProductQuantity[100];
    int c = 0;
    char choice;
    float amount = 0;
    float dis = 0;
    float total = 0;

    cout << "\n\n\t\t\t\t RECEIPT";
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n Empty database";
    } else {
        data.close();
        list();
        cout << "\n\n|_____________________________________________________________________________________\n";
        cout << "\n\n|                                                                                     \n";
        cout << "\n\n|         Please place the order                                                      \n";
        cout << "\n\n|                                                                                     \n";
        cout << "\n\n|_____________________________________________________________________________________\n";

        do {
            m:
            cout << "\n\nEnter product code :";
            cin >> arrOfProductCodes[c];
            cout << "\n\nEnter product quantity :";
            cin >> arrOfProductQuantity[c];
            for (int i = 0; i < c; ++i) {
                if (arrOfProductCodes[c] == arrOfProductCodes[i]) {
                    cout << "\n\n Duplicate product code. Please try again";
                    goto m;
                }
            }
            c++;
            cout << "\n\n Do you want to buy another product or not? if yes then press y else no";
            cin >> choice;
        } while (choice == 'y');

        cout
                << "\n\n\n\t\t______________________________RECEIPT_______________________________________________________\n";
        cout
                << "\nProduct No\tProduct Name\t Product quantity\t Product price\tProduct Amount\tProduct Amount with discount\t";

        for (int i = 0; i < c; ++i) {
            data.open("database.txt", ios::in);
            data >> productCode >> productName >> price >> discount;
            while (!data.eof()) {
                if (productCode == arrOfProductCodes[i]) {
                    amount = price * arrOfProductQuantity[i];
                    dis = amount - (amount * dis / 100);
                    total = total + dis;
                    cout << "\n" << productCode << "\t\t" << productName << "\t\t" << arrOfProductQuantity[i] << "\t\t"
                         << price << "\t\t" << amount << "\t\t" << dis;
                }
                data >> productCode >> productName >> price >> discount;
            }
        }
        data.close();
    }
    cout<< "\n\n\n\t\t_____________________________________________________________________________________\n";
    cout<< "\n\n\n\t\t Total amount :" << total;
}

int main() {
    shopping s;
    s.menu();
};
