// -------------------------------------- INCLUDES -------------------------------------
#include <iostream>
#include <string>
#include "vector"
#include "csvstream/csvstream.h"

// -------------------------------------- CLASSES -------------------------------------
class Customer {
public:
    std::string id;
    std::string name;
    std::string address;
};
class Product : public std::basic_string<char> {
public:
    std::string id;
    std::string name;
    int price;
};

// --------------------------------------- FUNCTIONS -------------------------------------------

// ---------------------MAPS-----------------------
std::map<std::string, std::string> customersRow;
std::map<std::string, std::string> allCustomersIdAndName;
// ------------------------------------------------

void readCustomers(){
    Customer currentCustomer;
    // Open file
    csvstream csvin("customers.csv");
    // Rows have key = column name, value = cell datum
    while (csvin >> customersRow) {

        // Print the values
        std::cout  << "Customer: " << customersRow["name"] <<  ", " << customersRow["address"] << "\n";

        // Add values to current customer
        currentCustomer.id =  customersRow["id"];
        currentCustomer.name =  customersRow["name"];
        currentCustomer.address =  customersRow["address"];

        // Push current customer to array
        allCustomersIdAndName.insert(std::make_pair(currentCustomer.id, currentCustomer.name));
    }
}

// ---------------------MAPS-----------------------
std::map<std::string, std::string> productsRow;
std::map<std::string, Product> allProducts;
std::map<std::string, int> allProductsNameAndPrice;
// ------------------------------------------------

void readProducts() {
    // Open file
    csvstream csvin("products.csv");

    Product currentProduct;

    while (csvin >> productsRow) {
        std::cout << "Product: "<< productsRow["name"] << ", " << productsRow["price"] << "\n";

        // Add values to current product
        currentProduct.id =  productsRow["id"];
        currentProduct.name =  productsRow["name"];
        currentProduct.price =  std::stoi(productsRow["price"]);

        // Push current product to array
        allProducts.insert(std::make_pair(currentProduct.id, currentProduct));
        allProductsNameAndPrice.insert(std::make_pair(currentProduct.name, currentProduct.price));
    }
}

// Rows have key = column name, value = cell datum
std::map<std::string, std::string> ordersRow;
std::map<std::string, int> allOrders;
std::map<std::string, int> allOrdersCustomerMoney;
void amountOrdered() {
    // Open file
    csvstream csvin("orders.csv");
    while (csvin >> ordersRow) {

        std::cout << "Product ID: " << ordersRow["productid"] << " Amount: " << ordersRow["amount"] << std::endl;
        allOrders.insert(std::make_pair(allProducts[ordersRow["productid"]].name, 0));
        for(auto &order : allOrders) {
            if(order.first == allProducts[ordersRow["productid"]].name && allProducts[ordersRow["productid"]].id == ordersRow["productid"]) {
                order.second += std::stoi(ordersRow["amount"]);
            }
        }

        /* ------------ CUSTOMER ---------------------------------------------------------------------------------------------------------------------- */
        allOrdersCustomerMoney.insert(std::make_pair( allCustomersIdAndName[ordersRow["customerid"]],0));
        for(auto &order : allOrdersCustomerMoney) {
            if(order.first == allCustomersIdAndName[ordersRow["customerid"]]) {
                order.second += allProducts[ordersRow["productid"]].price * std::stoi(ordersRow["amount"]);
            }
        }


    }

    for(const auto &order : allOrders) {
        std::cout << order.first << " " << "amount: " << order.second << std::endl;
    }

    for(const auto &order : allOrdersCustomerMoney) {
        std::cout << order.first << " " << "money spent: " << order.second << std::endl;
    }
};

void grossIncome() {
    for(auto &orderedItem : allOrders) {
        int productPrice = allProductsNameAndPrice[orderedItem.first];
        std::cout << orderedItem.first << " " << "gross income: " << orderedItem.second * productPrice << std::endl;
    };
};

void moneySpent() {

}

int main() {
    readCustomers();
    readProducts();
    amountOrdered();
    grossIncome();
    return 0;
}