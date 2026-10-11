#ifndef CART_H
#define CART_H

#include "stock.cpp"

//---Cart SYSTEM---
class node{
    public:
        product data;
        int cartQuantity;
        node*next;

        node(product obj){
            data = obj;
            cartQuantity = 1;
            next = NULL;
        }
};

class linkedList{
    node*head;
    public:
        linkedList(){ head = NULL; }
        string IDD;
        void addProductToCart();
        void removeFromCart();
        void displayCart();
        void checkOut();
        void clearCart();
};

//---Global Cart/linkedList object---
linkedList l;

//---Add To Cart---
void linkedList::addProductToCart(){
    LoadFromFile();
    cin.ignore();
    cout<<"Enter Product ID to be added to Cart: ";
    getline(cin,IDD);
    for(int i=0 ; i<mySize ; i++){
        if(IDD == p[i].id){
            if(head == NULL){
                head = new node(p[i]);
            }
            else{
                node*temp = head;
                while(temp->next != NULL){
                    if(temp->data.id == p[i].id){
                        temp->cartQuantity++; 
                        cout<<"Added successfully...\n";
                        return;
                    }
                    temp = temp->next;
                }
                if(temp->data.id == p[i].id){
                    temp->cartQuantity++;
                } else {
                    temp->next = new node(p[i]);
                }
            }
            cout<<"Added successfully...\n";
            return;
        }
    }
    cout<<"Wrong ID...\n";
}

//---Remove From Cart---
void linkedList::removeFromCart(){
    if(head == NULL){
        cout<<"Cart is Empty...\n";
        return;
    }
    cin.ignore();
    displayCart();
    cout<<"Enter ID to remove one product from Cart: ";
    getline(cin,IDD);

    node *temp = head, *prev = NULL;
    while(temp != NULL){
        if(IDD == temp->data.id){
            if(temp->cartQuantity > 1){
                temp->cartQuantity--;
                cout<<"Removed successfully...\n";
            } else {
                if(prev == NULL) head = temp->next;
                else prev->next = temp->next;
                delete temp;
                cout<<"Product removed from Cart.\n";
            }
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout<<"Product ID not found in Cart.\n";
}

//---Clear Cart---
void linkedList::clearCart(){
    node*temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        delete temp;
    }
}

//---Checkout---
void linkedList::checkOut(){
    if(head == NULL){
        cout<<"Cart is Empty...\n";
        return;
    }
    displayCart();

    //check stock quantity
    node* temp = head;
    bool canCheckout = true;
    while(temp != NULL){
        bool found = false;
        for(int i=0; i<mySize; i++){
            if(temp->data.id == p[i].id){
                found = true;
                if(temp->cartQuantity > p[i].quantity){
                    cout << "Not enough stock for Product ID: " << p[i].id 
                         << " (Available: " << p[i].quantity << ", In Cart: " 
                         << temp->cartQuantity << ")\n";
                    canCheckout = false;
                }
                break;
            }
        }
        if(!found) {
            cout << "Product in cart not found in stock: " << temp->data.id << "\n";
            canCheckout = false;
        }
        temp = temp->next;
    }

    if(!canCheckout){
        cout << "Cannot checkout\nRecheck cart quantities...\n";
        return;
    }

    //Calculate total
    temp = head;
    float total = 0.0;
    while(temp != NULL){
        if(temp->data.discount != 0.0){
            float priceAfterDiscount;
            priceAfterDiscount = temp->data.price * (1-temp->data.discount / 100.00);
            total += priceAfterDiscount * temp->cartQuantity;
        }
        else{
            total += temp->data.price * temp->cartQuantity;
        }
            temp = temp->next;
    }
    cout<<"Total Bill: "<< total <<"\n";

    //Payment options
    int choice;
    cout<<"\n1.Payment on delivery\n2.Through Bank account\nChoose payment method: ";
    cin>>choice;
    if(choice==1 || choice==2){
        cout<<"Order Confirmed...\n";
        //Update stock
        temp = head;
        while(temp != NULL){
            for(int i=0 ; i<mySize ; i++){
                if(temp->data.id == p[i].id){
                    p[i].quantity -= temp->cartQuantity;
                    break;
                }
            }
            temp = temp->next;
        }
        SaveToFile();
        clearCart();
    } else {
        cout<<"Invalid payment choice...\n";
    }
}

//---Display Cart---
void linkedList::displayCart(){
    if(head==NULL){
        cout<<"Cart is Empty..."<<endl;
        return;
    }
    cout<<"\n|"<< setw(5) << left <<"PID"
        <<"|"<< setw(20) <<"ProductName"
        <<"|"<< setw(20) <<"ProductPrice"
        <<"|"<< setw(10) <<"Quantity"
        <<"|"<< setw(10) <<"Discount"<<"|\n";

    node *temp=head;
    while(temp!=NULL){
        cout<<"|"<< setw(5) << left << temp->data.id
            <<"|"<< setw(20) << temp->data.name
            <<"|"<< setw(20) << fixed << setprecision(2) << temp->data.price
            <<"|"<< setw(10) << temp->cartQuantity 
            <<"|"<< setw(10) << fixed << setprecision(2) << temp->data.discount<<"|\n";
        temp = temp->next;
    }
}

#endif