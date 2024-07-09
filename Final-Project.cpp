#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <queue>
#include <stack>

using namespace std;

// Video ADT
struct Video {
    int videoID;
    string movieTitle;
    string genre;
    string production;
    int numCopies;
    string movieImageFilename;
};

class VideoStore {
private:
    list<Video> videos;

public:
    void insertVideo(const Video& video) {
        videos.push_back(video);
    }

    void rentVideo(int videoID) {
        // TODO: Implement rentVideo operation
        
    }

    void returnVideo(int videoID) {
        // TODO: Implement returnVideo operation
    }

    void showVideoDetails(int videoID) {
        // TODO: Implement showVideoDetails operation
    }

    void displayAllVideos() {
        // TODO: Implement displayAllVideos operation
    }

    bool checkVideoAvailability(int videoID) {
        // TODO: Implement checkVideoAvailability operation
        return false;
    }
};

// Customer ADT
struct Customer {
    int customerID;
    string name;
    string address;
};

class CustomerStore {
private:
    queue<Customer> customers;

public:
    void addCustomer(const Customer& customer) {
        customers.push(customer);
    }

    void showCustomerDetails(int customerID) {
        // TODO: Implement showCustomerDetails operation
        
    }

    void printRentedVideos(int customerID) {
        // TODO: Implement printRentedVideos operation
    }
};

// Customer-Rent ADT
struct CustomerRent {
    int customerID;
    stack<int> rentedVideos;
};

class CustomerRentStore {
private:
    list<CustomerRent> customerRents;

public:
    void rentVideo(int customerID, int videoID) {
        // TODO: Implement rentVideo operation
    }

    void returnVideo(int customerID, int videoID) {
        // TODO: Implement returnVideo operation
    }

    void printAllRentedVideos() {
        // TODO: Implement printAllRentedVideos operation
    }
};

int main() {
    // TODO: Implement the main program logic

    return 0;
}