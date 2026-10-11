# E-Commerce Management System (C++)

A console-based e-commerce management system in C++ with admin and user login, stock management, and a linked-list shopping cart. Built as a Data Structures & Algorithms (DSA) course project.

## Features

- **Admin login:** add and delete admins (maximum 5). Deleting the admin you are logged in as logs you out automatically.
- **Stock management:** add, update, delete and display products (maximum 100). Product IDs are renumbered automatically.
- **User login:** register or log in with an email ID.
- **Shopping cart:** built on a singly linked list. Add or remove products, view the cart, and check out.
- **Checkout:** verifies stock, applies percentage discounts, shows the total bill, and updates stock after payment (cash on delivery or bank account).
- **File storage:** data is saved in plain text files, so it persists between runs.

## Project Structure

| File | Purpose |
|------|---------|
| `main.cpp` | Program entry point and menus |
| `login.cpp` | Admin and user classes, login system |
| `stock.cpp` | Product class and stock management |
| `cart.cpp` | Linked-list cart and checkout |

## Data Files

Created in the folder where you run the program:

- `Admin.txt`: admin credentials, one per line as `|id|password|`
- `User.txt`: registered user emails
- `Stock.txt`: products as `|id|name|price|quantity|discount|`

## How to Run

```bash
g++ main.cpp -o ecom
./ecom
```

Compile only `main.cpp`. It includes the other `.cpp` files itself.

**First run:** there is no default admin. Before using Admin Login, create an `Admin.txt` file next to the program containing one line, for example:

```
|admin|1234|
```

You can then log in and add more admins from the Admin Management menu.

## Concepts Used

- Classes and objects
- Singly linked list (cart)
- Arrays (admins and stock)
- File handling with `ifstream` / `ofstream`
- String streams for parsing records
