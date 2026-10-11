#ifndef LOGIN_H
#define LOGIN_H

#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<cmath>
#include<string>
using namespace std;

//---global/constant variables---
//for Admin
const int ms = 5;
int s = 0;
bool forceLogout = false;
string currentAdmin = "";

//--------LOGIN SYSTEM--------
//---Admin Class---
class admin{
public:
    string id;
    string password;

    admin(){
        id = "";
        password = "";
    }
    void addAdmin();
    void deleteAdmin();
    bool checkAdmin(string I, string P);
};

admin ad[ms];

//---Trimming function---
string trim(const string &str){
    size_t first = str.find_first_not_of(" \t");
    if(first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, last - first + 1);
}

//ADMIN CLASS FUNCTIONS
//---Save Admin File---
void saveAdminFile(){
    ofstream of("Admin.txt");
    for(int i = 0; i < s; i++){
        of << "|" << ad[i].id << "|" << ad[i].password << "|\n";
    }
    of.close();
}

//---Read Admin File---
void readAdminFile(){
    ifstream in("Admin.txt");
    s = 0;
    if(!in) return;
    string line, temp;
    while(getline(in, line) && s < ms){
        if(line.empty() || line[0] != '|') continue;

        stringstream ss(line);
        getline(ss, temp, '|'); //empty bcz it is before first
        getline(ss, temp, '|');
        ad[s].id = trim(temp);
        getline(ss, temp, '|');
        ad[s].password = trim(temp);
        s++;
    }
    in.close();
}

//---Add Admin---
void admin::addAdmin(){
    readAdminFile();

    if(s >= ms){
        cout << "Admin limit reached...\n";
        return;
    }
    cout << "Enter Admin ID: ";
    getline(cin, id);
    // check duplicate
    for(int i = 0; i < s; i++){
        if(ad[i].id == id){
            cout << "Admin ID already exists...\n";
            return;
        }
    }

    cout << "Enter Password: ";
    getline(cin, password);

    ad[s].id = id;
    ad[s].password = password;
    s++;
    saveAdminFile();

    cout << "Admin Added Successfully...\n";
}

//---Delete Admin---
void admin::deleteAdmin(){
    readAdminFile();

    string idd;
    cout << "Enter Admin ID to delete: ";
    getline(cin, idd);

    for(int i = 0; i < s; i++){
        if(ad[i].id == idd){
            if(idd == currentAdmin){
                forceLogout = true;
            }
            for(int j = i; j < s-1; j++){
                ad[j] = ad[j + 1];
                
            }
            s--;
            saveAdminFile();
            cout << "Admin Deleted Successfully...\n";
            return;
        }
    }
    cout << "Admin not found...\n";
}

//---Check Admin Login---
bool admin::checkAdmin(string I, string P){
    readAdminFile();
    for(int i = 0; i < s; i++){
        if(ad[i].id == I && ad[i].password == P)
            return true;
    }
    return false;
}

//---User Class---
class user{
    string email;
public:
    void addUser(){
        cout << "Enter Email ID: ";
        getline(cin, email);

        ofstream of("User.txt", ios::app);
        of << email << "\n";
        of.close();

        cout << "User Registered Successfully...\n";
    }

    bool checkUser(){
        cout << "Enter Email ID: ";
        getline(cin, email);

        ifstream in("User.txt");
        string line;

        while(getline(in, line)){
            if(trim(line) == email){
                in.close();
                return true;
            }
        }
        in.close();
        return false;
    }
};

#endif