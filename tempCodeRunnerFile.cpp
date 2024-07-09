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
    stack<int> rentedVideos; // Declare rentedVideos stack
    list<CustomerRent> customerRents; // Declare customerRents list

public:
    void insertVideo(const Video& video) {
        videos.push_back(video);
    }

    void rentVideo(int videoID) {
        // Check if the video is available
        if (checkVideoAvailability(videoID)) {
            // TODO: Implement rentVideo operation
            // Add the videoID to the rentedVideos stack for the current customer
            rentedVideos.push(videoID);
            cout << "Video " << videoID << " rented successfully." << endl;
        } else {
            cout << "Video " << videoID << " is not available for rent." << endl;
        }
    }

    void returnVideo(int videoID) {
        // TODO: Implement returnVideo operation
        for (auto& rent : customerRents) {
            if (!rent.rentedVideos.empty() && rent.rentedVideos.top() == videoID) {
                rent.rentedVideos.pop();
                cout << "Video " << videoID << " returned successfully." << endl;
                return;
            }
        }
        cout << "Video " << videoID << " is not rented by any customer." << endl;
    }

    void showVideoDetails(int videoID) {
        // TODO: Implement showVideoDetails operation
        for (const auto& video : videos) {
            if (video.videoID == videoID) {
                cout << "Video Details:" << endl;
                cout << "Video ID: " << video.videoID << endl;
                cout << "Title: " << video.movieTitle << endl;
                cout << "Genre: " << video.genre << endl;
                cout << "Production: " << video.production << endl;
                cout << "Number of Copies: " << video.numCopies << endl;
                cout << "Image Filename: " << video.movieImageFilename << endl;
                return;
            }
        }
        cout << "Video " << videoID << " not found." << endl;
    }

    void displayAllVideos() {
        cout << "All Videos:" << endl;
        for (const auto& video : videos) {
            cout << "Video ID: " << video.videoID << endl;
            cout << "Title: " << video.movieTitle << endl;
            cout << "Genre: " << video.genre << endl;
            cout << "Production: " << video.production << endl;
            cout << "Number of Copies: " << video.numCopies << endl;
            cout << "Image Filename: " << video.movieImageFilename << endl;
            cout << endl;
        }
    }

    bool checkVideoAvailability(int videoID) {
        // TODO: Implement checkVideoAvailability operation
        for (const auto& video : videos) {
            if (video.videoID == videoID) {
                return true;
            }
        }
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
    list<CustomerRent> customerRents; // Declare customerRents list

public:
    void addCustomer(const Customer& customer) {
        customers.push(customer);
    }

    void showCustomerDetails(int customerID) {
        for (const auto& customer : customers) {
            if (customer.customerID == customerID) {
                cout << "Customer Details:" << endl;
                cout << "Customer ID: " << customer.customerID << endl;
                cout << "Name: " << customer.name << endl;
                cout << "Address: " << customer.address << endl;
                return;
            }
        }
        cout << "Customer " << customerID << " not found." << endl;
    }

    void printRentedVideos(int customerID) {
        // TODO: Implement printRentedVideos operation
        for (auto& rent : customerRents) {
            if (rent.customerID == customerID) {
                cout << "Rented videos for customer " << customerID << ":" << endl;
                while (!rent.rentedVideos.empty()) {
                    int videoID = rent.rentedVideos.top();
                    rent.rentedVideos.pop();
                    cout << "Video ID: " << videoID << endl;
                }
                return;
            }
        }
    
        cout << "No rented videos found for customer " << customerID << endl;
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
        for (auto& rent : customerRents) {
            if (rent.customerID == customerID) {
                rent.rentedVideos.push(videoID);
                return;
            }
        }

        CustomerRent newRent;
        newRent.customerID = customerID;
        newRent.rentedVideos.push(videoID);
        customerRents.push_back(newRent);
    }

    void returnVideo(int customerID, int videoID) {
        // TODO: Implement returnVideo operation
        for (auto& rent : customerRents) {
            if (rent.customerID == customerID) {
                // Check if the video is rented by the customer
                if (!rent.rentedVideos.empty() && rent.rentedVideos.top() == videoID) {
                    rent.rentedVideos.pop();
                    cout << "Video " << videoID << " returned successfully." << endl;
                    return;
                }
            }
        }
        cout << "Video " << videoID << " is not rented by customer " << customerID << "." << endl;
    }

    void printAllRentedVideos() {
        // TODO: Implement printAllRentedVideos operation
        cout << "All Rented Videos:" << endl;
        for (const auto& rent : customerRents) {
            cout << "Customer ID: " << rent.customerID << endl;
            cout << "Rented Videos:" << endl;
            stack<int> rentedVideosCopy = rent.rentedVideos;
            while (!rentedVideosCopy.empty()) {
                int videoID = rentedVideosCopy.top();
                rentedVideosCopy.pop();
                cout << "Video ID: " << videoID << endl;
            }
            cout << endl;
        }
    }
};

int main() {
    // TODO: Implement the main program logic
    VideoStore videoStore;
    CustomerStore customerStore;
    CustomerRentStore customerRentStore;

    // Sample code to test the functionality
    Video video1 = {1, "Movie 1", "Action", "Production 1", 3, "movie1.jpg"};
    Video video2 = {2, "Movie 2", "Comedy", "Production 2", 2, "movie2.jpg"};
    Video video3 = {3, "Movie 3", "Drama", "Production 3", 1, "movie3.jpg"};

    Customer customer1 = {1, "John Doe", "Address 1"};
    Customer customer2 = {2, "Jane Smith", "Address 2"};

    videoStore.insertVideo(video1);
    videoStore.insertVideo(video2);
    videoStore.insertVideo(video3);

    customerStore.addCustomer(customer1);
    customerStore.addCustomer(customer2);

    customerRentStore.rentVideo(1, 1);
    customerRentStore.rentVideo(1, 2);
    customerRentStore.rentVideo(2, 3);

    videoStore.returnVideo(1);
    videoStore.returnVideo(1);
    videoStore.returnVideo(2);

    videoStore.displayAllVideos();
    customerStore.showCustomerDetails(1);
    customerRentStore.printAllRentedVideos();

    return 0;
}

