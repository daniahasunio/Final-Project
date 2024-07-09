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
        cout << "Video ID not found in the inventory." << endl;
    }

    void showVideoDetails(int videoID) {
        for (const auto& video : videos) {
            if (video.videoID == videoID) {
                cout << "Video ID: " << video.videoID << endl;
                cout << "Title: " << video.movieTitle << endl;
                cout << "Genre: " << video.genre << endl;
                cout << "Production: " << video.production << endl;
                cout << "Number of Copies: " << video.numCopies << endl;
                cout << "Image Filename: " << video.movieImageFilename << endl;
                return;
            }
        }
        cout << "Video ID not found." << endl;
    }

    void displayAllVideos() {
        for (const auto& video : videos) {
            cout << "Video ID: " << video.videoID << endl;
            cout << "Title: " << video.movieTitle << endl;
            cout << "Genre: " << video.genre << endl;
            cout << "Production: " << video.production << endl;
            cout << "Number of Copies: " << video.numCopies << endl;
            cout << "Image Filename: " << video.movieImageFilename << endl;
        }
    }

    bool checkVideoAvailability(int videoID) {
        for (const auto& video : videos) {
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
    queue<Customer> customers;

public:
    void addCustomer(const Customer& customer) {
        customers.push(customer);
    }

    void showCustomerDetails(int customerID) {
        queue<Customer> temp = customers;
        while (!temp.empty()) {
            Customer customer = temp.front();
            temp.pop();
            if (customer.customerID == customerID) {
                cout << "Customer ID: " << customer.customerID << endl;
                cout << "Name: " << customer.name << endl;
                cout << "Address: " << customer.address << endl;
                return;
            }
        }
        cout << "Customer ID not found." << endl;
    }

    void printRentedVideos(int customerID, list<CustomerRent>& customerRents) {
        for (const auto& rent : customerRents) {
            if (rent.customerID == customerID) {
                cout << "Rented videos for customer " << customerID << ":" << endl;
                stack<int> rentedVideosCopy = rent.rentedVideos;
                while (!rentedVideosCopy.empty()) {
                    int videoID = rentedVideosCopy.top();
                    rentedVideosCopy.pop();
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
        for (auto& rent : customerRents) {
            if (rent.customerID == customerID) {
                stack<int> tempStack;
                bool videoFound = false;

                while (!rent.rentedVideos.empty()) {
                    int topVideoID = rent.rentedVideos.top();
                    rent.rentedVideos.pop();

                    if (topVideoID == videoID && !videoFound) {
                        videoFound = true;
                    } else {
                        tempStack.push(topVideoID);
                    }
                }

                while (!tempStack.empty()) {
                    rent.rentedVideos.push(tempStack.top());
                    tempStack.pop();
                }

                if (videoFound) {
                    cout << "Video " << videoID << " returned successfully by customer " << customerID << "." << endl;
                } else {
                    cout << "Video " << videoID << " not found in rented videos of customer " << customerID << "." << endl;
                }
                return;
            }
        }
        cout << "Customer ID not found." << endl;
    }

    void printAllRentedVideos() {
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

    list<CustomerRent>& getCustomerRents() {
        return customerRents;
    }
};

int main() {
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

    if (videoStore.checkVideoAvailability(1)) {
        videoStore.rentVideo(1);
        customerRentStore.rentVideo(1, 1);
    }

    if (videoStore.checkVideoAvailability(2)) {
        videoStore.rentVideo(2);
        customerRentStore.rentVideo(1, 2);
    }

    if (videoStore.checkVideoAvailability(3)) {
        videoStore.rentVideo(3);
        customerRentStore.rentVideo(2, 3);
    }

    videoStore.returnVideo(1);
    customerRentStore.returnVideo(1, 1);

    videoStore.displayAllVideos();
    customerStore.showCustomerDetails(1);
    customerStore.printRentedVideos(1, customerRentStore.getCustomerRents());
    customerRentStore.printAllRentedVideos();

    return 0;
}
