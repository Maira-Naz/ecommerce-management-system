#ifndef STOCK_H
#define STOCK_H

#include "login.cpp"

//for Stock
const int max_record = 100;
int mySize=0,num;
string ID;

//--------STOCK MANAGEMENT SYSTEM--------
class product{
    public:
        string id;
        string name;
        float price;
        int quantity;
        float discount;

        product(){
            id = "";
            name = "";
            price = 0.0;
            quantity = 0;
            discount = 0.0;
        }
        void input(){
            cin.ignore(); //to clear previos \n
            cout<<"Enter Product Name: ";
            getline(cin,name);
            cout<<"Enter Product Price: ";
            cin>>price;
            cout<<"Enter Product Quantity: ";
            cin>>quantity;
            cout<<"Enter Product Discount(either 0.0 or more): ";
            cin>>discount;
        }
        void output(){
            cout<<"|"<< setw(5) << left << id 
                <<"|"<< setw(20) << name
                <<"|"<< setw(20) << fixed << setprecision(2) << price
                <<"|"<< setw(10) << quantity 
                <<"|"<< setw(10) << fixed << setprecision(2) << discount <<"|\n";
        }
};
//---product class global object---
product p[max_record];

class stock{
    public:
        void addStock();
        void deleteStock();
        void updateStock();
        void displayStock();
};

//---save to file function---
void SaveToFile(){
	ofstream of;
	of.open("Stock.txt", ios::out);
	
    for(int i=0 ; i<mySize ; i++){
        of<<"|"<< p[i].id 
          <<"|"<< p[i].name 
          <<"|"<< fixed << setprecision(2) << p[i].price 
          <<"|"<< p[i].quantity 
          <<"|"<< fixed << setprecision(2) << p[i].discount <<"|\n";
    }
    of.close();
}

//---read from file function---
void LoadFromFile(){
	ifstream in;
	in.open("Stock.txt");
	if(!in){
        mySize = 0;
		return;
    }
	string line;
	mySize=0;  //reset size to 0
	
	while(getline(in,line) && mySize<max_record){
		if(line.empty()) continue;
		if(line[0] != '|') continue;
		string temp;
		stringstream ss(line);
		
		getline(ss,temp,'|');  // empty(bcz line starts with |)
		getline(ss,temp,'|');
		p[mySize].id = trim(temp);
				
        getline(ss,temp,'|');
        p[mySize].name = trim(temp);

        getline(ss,temp,'|');
        p[mySize].price = stof(trim(temp));

        getline(ss,temp,'|');
        p[mySize].quantity = stoi(trim(temp));

        getline(ss,temp,'|');
        p[mySize].discount = stof(trim(temp));

        mySize++;
	}
    for(int k=0 ; k<mySize ; k++){
        p[k].id = to_string(k+1);
    }
	in.close();
}

//---Add Stock---
void stock::addStock(){
    LoadFromFile();
    cout<<"How many to add? ";
    cin>>num;
    cin.ignore();
    for(int i=mySize,j=0 ; j<num && mySize<max_record ; i++){
        cout<<"Enter Product "<< i+1 <<"\n";
        p[i].input();
        j++;
        p[i].id = to_string(i+1);
        mySize++;
    }
    cout<<"Added Successfully!\n";
    SaveToFile();
}

//---Delete Stock---
void stock::deleteStock(){
    LoadFromFile();
    cout <<"Enter Product ID to delete: ";
    cin.ignore();
    getline(cin, ID);
    bool found = false;
    for(int i = 0; i < mySize; i++){
        if(ID == p[i].id){
            cout << "Product deleted!\n";
            p[i].output();
            for(int j = i; j < mySize-1; j++){
                p[j] = p[j+1];
            }
            mySize--;
            for(int k=0 ; k<mySize ; k++){
                p[k].id = to_string(k+1);
            }
            found = true;
            break;
        }
    }
    if(!found) cout << "ID not found!\n";
    SaveToFile();
}

//---Update Stock---
void stock::updateStock(){
    LoadFromFile();
    int ch;
    cout<<"Enter Product ID: ";
    cin.ignore();
    getline(cin,ID);
    bool found = false;
    for(int i=0 ; i<mySize ; i++){
        if(ID == p[i].id){
            cout<<"What to update (1.name / 2.price / 3.quantity / 4.discount)";
            cin>>ch;
            switch(ch){
                case 1:
                    cout<<"Enter new name: ";
                    cin.ignore();
                    getline(cin,p[i].name);
                    break;
                case 2:
                    cout<<"Enter new price: ";
                    cin>>p[i].price;
                    break;
                case 3:
                    cout<<"Enter new quantity: ";
                    cin>>p[i].quantity;
                    break;
                case 4:
                    cout<<"Enter new discount: ";
                    cin>>p[i].discount;
                    break;
                default:
                    cout<<"Invalid choice";
            }
            cout<<"Updated Successfully!\n";
            found = true;
            SaveToFile();
            break;
        }
    }
    if(!found) cout << "ID not found!\n";
}

//---Display Stock---
void stock::displayStock(){
    LoadFromFile();
    cout<<"\n-Complete Stock---\n";
    cout<<"|"<< setw(5) << left <<"PID"
        <<"|"<< setw(20) <<"ProductName"
        <<"|"<< setw(20) <<"ProductPrice"
        <<"|"<< setw(10) <<"Quantity"
        <<"|"<< setw(10) <<"Discount"<<"|\n";

    for(int i=0 ; i<mySize ; i++){
        p[i].output();
        cout<<"\n";
    }
    cout<<"\n\n";
}

#endif