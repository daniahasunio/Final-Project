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
        for (auto& video : videos) {
            if (video.videoID == videoID && video.numCopies > 0) {
                video.numCopies--;
                cout << "Video rented successfully." << endl;
                return;
            }
        }
        cout << "Video not available for rent." << endl;
        
    }

    void returnVideo(int videoID) {
        for (auto& video : videos) {
            if (video.videoID == videoID) {
                video.numCopies++;
                cout << "Video returned successfully." << endl;
                return;
            }
        }
        cout << "Video not found." << endl;
    }

    void showVideoDetails(int videoID) {
        for (auto& video : videos) {
            if (video.videoID == videoID) {
                cout << "Video ID: " << video.videoID << endl;
                cout << "Movie Title: " << video.movieTitle << endl;
                cout << "Genre: " << video.genre << endl;
                cout << "Production: " << video.production << endl;
                cout << "Number of Copies: " << video.numCopies << endl;
                cout << "Movie Image Filename: " << video.movieImageFilename << endl;
                return;
            }
        }
        cout << "Video not found." << endl;
    }

    void displayAllVideos() {
        for (auto& video : videos) {
            cout << "Video ID: " << video.videoID << endl;
            cout << "Movie Title: " << video.movieTitle << endl;
            cout << "Genre: " << video.genre << endl;
            cout << "Production: " << video.production << endl;
            cout << "Number of Copies: " << video.numCopies << endl;
            cout << "Movie Image Filename: " << video.movieImageFilename << endl;
            cout << endl;
        }
    }

    bool checkVideoAvailability(int videoID) {
        for (auto& video : videos) {
            if (video.videoID == videoID && video.numCopies > 0) {
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
    list<Customer> customers;

public:
    void addCustomer(const Customer& customer) {
        customers.push_back(customer);
    }

    void showCustomerDetails(int customerID) {
        for (auto& customer : customers) {
            if (customer.customerID == customerID) {
                cout << "Customer ID: " << customer.customerID << endl;
                cout << "Name: " << customer.name << endl;
                cout << "Address: " << customer.address << endl;
                return;
            }
        }
        cout << "Customer not found." << endl;
    }


    void printRentedVideos(int customerID) {
        for (auto& customer : customers) {
            if (customer.customerID == customerID) {
                cout << "Customer ID: " << customer.customerID << endl;
                cout << "Name: " << customer.name << endl;
                cout << "Address: " << customer.address << endl;
                return;
            }
        }
        cout << "Customer not found." << endl;
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
        for (auto& rent : customerRents) {
            if (rent.customerID == customerID) {
                rent.rentedVideos.push(videoID);
                cout << "Video rented successfully." << endl;
                return;
            }
        }
        CustomerRent newRent;
        newRent.customerID = customerID;
        newRent.rentedVideos.push(videoID);
        customerRents.push_back(newRent);
        cout << "Video rented successfully." << endl;
    }

    void returnVideo(int customerID, int videoID) {
        for (auto& rent : customerRents) {
            if (rent.customerID == customerID) {
                stack<int>& rentedVideos = rent.rentedVideos;
                while (!rentedVideos.empty()) {
                    if (rentedVideos.top() == videoID) {
                        rentedVideos.pop();
                        cout << "Video returned successfully." << endl;
                        return;
                    }
                    rentedVideos.pop();
                }
                cout << "Video not found." << endl;
                return;
            }
        }
        cout << "Customer not found." << endl;
    }

    void printAllRentedVideos() {
        for (auto& rent : customerRents) {
            cout << "Customer ID: " << rent.customerID << endl;
            cout << "Rented Videos: ";
            stack<int> rentedVideos = rent.rentedVideos;
            while (!rentedVideos.empty()) {
                cout << rentedVideos.top() << " ";
                rentedVideos.pop();
            }
            cout << endl;
        }
    }
};

int main() {
    VideoStore videoStore;
    CustomerStore customerStore;
    CustomerRentStore customerRentStore;

    // Create some videos
    Video video1 = {1, "Movie 1", "Action", "Production 1", 5, "movie1.jpg"};
    Video video2 = {2, "Movie 2", "Comedy", "Production 2", 3, "movie2.jpg"};
    Video video3 = {3, "Movie 3", "Drama", "Production 3", 2, "movie3.jpg"};

    // Insert videos into the video store
    videoStore.insertVideo(video1);
    videoStore.insertVideo(video2);
    videoStore.insertVideo(video3);

    // Create some customers
    Customer customer1 = {1, "John Doe", "Address 1"};
    Customer customer2 = {2, "Jane Smith", "Address 2"};

    // Add customers to the customer store
    customerStore.addCustomer(customer1);
    customerStore.addCustomer(customer2);

    // Rent videos
    customerRentStore.rentVideo(1, 1);
    customerRentStore.rentVideo(1, 2);
    customerRentStore.rentVideo(2, 3);

    // Return videos
    customerRentStore.returnVideo(1, 1);
    customerRentStore.returnVideo(2, 3);

    // Display video details
    videoStore.showVideoDetails(1);
    videoStore.showVideoDetails(2);
    videoStore.showVideoDetails(3);

    // Display all videos
    videoStore.displayAllVideos();

    // Display customer details
    customerStore.showCustomerDetails(1);
    customerStore.showCustomerDetails(2);

    // Display rented videos
    customerRentStore.printAllRentedVideos();

    return 0;
}