#include "login.cpp"
#include "stock.cpp"
#include "cart.cpp"

//---Main Function---
int main(){
    readAdminFile();
    admin a;
    stock s;

    int ch, cho, choice;
    do{
        cout << "\n1.Admin Login\n2.User Login\n3.Exit\nEnter choice: ";
        cin >> ch;
        cin.ignore();

        switch(ch){
        case 1:{
            string ID, pass;
            cout << "Enter Admin ID: ";
            getline(cin, ID);
            cout << "Enter Password: ";
            getline(cin, pass);

            if(!a.checkAdmin(ID, pass)){
                cout << "Invalid Credentials...\n";
                break;
            }
            currentAdmin = ID;
            forceLogout = false;
            do{
                if(forceLogout){
                    // cout<<"\nCurrent Admin Delete\nLogOut..\n";
                    // currentAdmin = "";
                    break;
                }
                cout<<"\n1.Admin Managment\n2.Stock manangment\n3.Exit\nEnter your choice: ";
                cin>>cho;
                switch(cho){
                case 1:
                    do{
                        if(forceLogout){
                            cout<<"\nCurrent Admin Delete\nLogOut..\n";
                            currentAdmin = "";
                            break;
                        }
                        cout << "\n1.Add Admin\n2.Delete Admin\n3.Exit\nEnter choice: ";
                        cin >> choice;
                        cin.ignore();

                        switch(choice){
                        case 1: a.addAdmin(); break;
                        case 2: a.deleteAdmin(); break;
                        case 3: cout << "Exiting Admin Management...\n"; break;
                        default: cout << "Invalid choice...\n";
                        }
                    }while(choice != 3);
                    break;
                
                case 2:
                    do{
                       cout<<"\n1.Add Stock\n2.Delete Stock\n3.Update Stock\n4.Display Stock \n5.Exit \nEnter your choice: ";
                       cin>>choice;
                       switch(choice){
                        case 1: s.addStock(); break;
                        case 2: s.deleteStock(); break;
                        case 3: s.updateStock(); break;  
                        case 4: s.displayStock(); break;
                        case 5: cout<<"Exiting Stock Management...\n"; break;         
                        default: cout<<"Invalid choice...";                
                        }
                    }while(choice!=5);
                    break;

                case 3: cout<<"Exiting Admin Panel...\n"; break;
                default: cout<<"Invalid choice...";
                }
            }while(cho != 3);
            break;
        }

        case 2: {
            user u;
            int cho;
            do {
                cout << "\n1. Existing User (Login)"
                << "\n2. New User (Register)"
                << "\n3. View Stock"
                << "\n4. Exit"
                << "\nEnter choice: ";
                cin >> cho;
                cin.ignore();

                if (cho == 1) {
                if (u.checkUser()) {
                    cout << "User Login Successful...\n";

                    // After successful login, show user menu
                    int choice;
                    do {
                        cout << "\n1. View Stock"
                            << "\n2. Add Product to Cart"
                            << "\n3. Remove from Cart"
                            << "\n4. Display Cart"
                            << "\n5. Checkout"
                            << "\n6. Exit"
                            << "\nEnter your choice: ";
                        cin >> choice;

                        switch (choice) {
                            case 1: s.displayStock(); break;
                            case 2: l.addProductToCart(); break;
                            case 3: l.removeFromCart(); break;
                            case 4: l.displayCart(); break;
                            case 5: l.checkOut(); break;
                            case 6: cout << "Exiting User...\n"; break;
                            default: cout << "Invalid choice...\n";
                        }
                    } while (choice != 6);
                } else {
                    cout << "User not found...\nReturning to main menu...\n";
                    // loop continues, so it goes back to main menu
                }
            }
            else if (cho == 2) {
                u.addUser();
                cout<<"Now, Login with your ID\n";
            }
            else if (cho == 3) {
                s.displayStock();
            }   
            else if (cho == 4) {
                cout << "Exiting...\n";
                break;
            }
            else {
                cout << "Invalid choice...\n";
            }

            } while (cho != 4);
            break;
        }

        case 3:
            cout << "Program Terminated...\n";
            break;

        default:
            cout << "Invalid choice...\n";
        }
        
    }while(ch != 3);

    return 0;
}