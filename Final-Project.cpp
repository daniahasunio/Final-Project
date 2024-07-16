#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

struct Video {
    int videoID;
    string movieTitle;
    string genre;
    string production;
    int numCopies;
};

class VideoStore {
private:
    vector<Video> videos;

public:

    const vector<Video>& getVideos() const {
        return videos;
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            Video video;
            size_t pos = 0;

            pos = line.find(',');
            video.videoID = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            pos = line.find(',');
            video.movieTitle = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            video.genre = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            video.production = line.substr(0, pos);
            line.erase(0, pos + 1);

            video.numCopies = stoi(line);

            videos.push_back(video);
        }
        file.close();
    }

    void insertVideo(const Video& video) {
        videos.push_back(video);
    }

    bool checkVideoAvailability(int videoID) {
        for (const auto& video : videos) {
            if (video.videoID == videoID && video.numCopies > 0) {
                return true;
            }
        }
        return false;
    }

    void rentVideo(int videoID) {
        for (auto& video : videos) {
            if (video.videoID == videoID && video.numCopies > 0) {
                video.numCopies--;
                return;
            }
        }
    }

    void returnVideo(int videoID) {
        for (auto& video : videos) {
            if (video.videoID == videoID) {
                video.numCopies++;
                return;
            }
        }
    }

    void showVideoDetails(int videoID) {
        for (const auto& video : videos) {
            if (video.videoID == videoID) {
                cout<< " " << endl;
                cout << "Video ID: " << video.videoID << endl;
                cout << "Title: " << video.movieTitle << endl;
                cout << "Genre: " << video.genre << endl;
                cout << "Production: " << video.production << endl;
                cout << "Number of Copies: " << video.numCopies << endl;
                cout<< " " << endl;
                return;
            }
        }
        cout << "Video not found." << endl;
    }

    void displayAllVideos() {
        for (const auto& video : videos) {
            cout << " " << endl;
            cout << "Video ID: " << video.videoID<<endl;
            cout << "Title: " << video.movieTitle<<endl; 
            cout<< "Genre: " << video.genre<<endl; 
            cout<< "Production: " << video.production<<endl; 
            cout<< "Copies: " << video.numCopies<<endl;
            cout <<" "<< endl;
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        for (const auto& video : videos) {
            file << video.videoID << "," << video.movieTitle << "," << video.genre << "," << video.production << "," << video.numCopies << endl;
        }
        file.close();
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
    const list<Customer>& getCustomers() const {
        return customers;
    }


    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            Customer customer;
            size_t pos = 0;

            pos = line.find(',');
            customer.customerID = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            pos = line.find(',');
            customer.name = line.substr(0, pos);
            line.erase(0, pos + 1);

            customer.address = line;

            customers.push_back(customer);
        }
        file.close();
    }

    void addCustomer(const Customer& customer) {
        for (auto& existingCustomer : customers) {
            if (existingCustomer.customerID == customer.customerID) {
                // Update the existing customer details
                existingCustomer.name = customer.name;
                existingCustomer.address = customer.address;
                cout << "Customer updated successfully." << endl;
                return;
            }
        }
        customers.push_back(customer);
        cout << "Customer added successfully." << endl;
    }

    void showCustomerDetails(int customerID) {
        for (const auto& customer : customers) {
            if (customer.customerID == customerID) {
                cout<< " " << endl;
                cout << "Customer ID: " << customer.customerID << endl;
                cout << "Name: " << customer.name << endl;
                cout << "Address: " << customer.address << endl;
                cout<< " " << endl;
                return;
            }
        }
        cout << "Customer not found." << endl;
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        for (const auto& customer : customers) {
            file << customer.customerID << "," << customer.name << "," << customer.address << endl;
        }
        file.close();
    }
};

class CustomerRentStore {
private:
    list<pair<int, int>> rentedVideos; // pair<customerID, videoID>

public:
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            int customerID = stoi(line.substr(0, pos));
            int videoID = stoi(line.substr(pos + 1));
            rentedVideos.push_back(make_pair(customerID, videoID));
        }
        file.close();
    }

    void rentVideo(int customerID, int videoID) {
        rentedVideos.push_back(make_pair(customerID, videoID));
    }

    void returnVideo(int customerID, int videoID) {
        rentedVideos.remove(make_pair(customerID, videoID));
    }

    void printAllRentedVideos(const CustomerStore& customerStore, const VideoStore& videoStore) {
        for (const auto& rent : rentedVideos) {
            int customerID = rent.first;
            int videoID = rent.second;

            // Get the movie title
            string movieTitle;
            for (const auto& video : videoStore.getVideos()) {
                if (video.videoID == videoID) {
                    movieTitle = video.movieTitle;
                    break;
                }
            }

            // Get the customer name
            string customerName;
            for (const auto& customer : customerStore.getCustomers()) {
                if (customer.customerID == customerID) {
                    customerName = customer.name;
                    break;
                }
            }

            // Get the genre
            string genre;
            for (const auto& video : videoStore.getVideos()) {
                if (video.videoID == videoID) {
                    genre = video.genre;
                    break;
                }
            }

            // Get the production
            string production;
            for (const auto& video : videoStore.getVideos()) {
                if (video.videoID == videoID) {
                    production = video.production;
                    break;
                }
            }

            cout << " " << endl;
            cout << "Customer ID: " << customerID << endl;
            cout << "Customer Name: " << customerName << endl;
            cout << "Video ID: " << videoID << endl;
            cout << "Movie Title: " << movieTitle << endl;
            cout << "Genre: " << genre << endl;
            cout << "Production: " << production << endl;
            cout << " " << endl;
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        for (const auto& rent : rentedVideos) {
            file << rent.first << "," << rent.second << endl;
        }
        file.close();
    }
};
int getValidatedIntInput(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter an integer: ";
    }
    return value;
}

int main() {
    VideoStore videoStore;
    CustomerStore customerStore;
    CustomerRentStore customerRentStore;

    // Load data from files
    videoStore.loadFromFile("videos.txt");
    customerStore.loadFromFile("customers.txt");
    customerRentStore.loadFromFile("customer_rents.txt");

    int choice;
    cout << "==============================================" << endl;
    cout << "        QUEUETI PIE: Video Rental System      " << endl;
    cout << "==============================================" << endl;

    do {
        cout << "Enter your choice:" << endl;
        cout << "1. Insert videos into the video store" << endl;
        cout << "2. Add customers to the customer store" << endl;
        cout << "3. Rent videos" << endl;
        cout << "4. Return videos" << endl;
        cout << "5. Display video details" << endl;
        cout << "6. Display all videos" << endl;
        cout << "7. Display customer details" << endl;
        cout << "8. Display all rented videos" << endl;
        cout << "9. Save and exit" << endl;
        cout << "0. Exit without saving" << endl;

        choice = getValidatedIntInput("Choice: ");

        switch (choice) {
        case 1: {
            Video video;
            video.videoID = getValidatedIntInput("Enter Video ID: ");
            cout << "Enter Movie Title: ";
            cin.ignore();
            getline(cin, video.movieTitle);
            cout << "Enter Genre: ";
            getline(cin, video.genre);
            cout << "Enter Production: ";
            getline(cin, video.production);
            video.numCopies = getValidatedIntInput("Enter Number of Copies: ");
            videoStore.insertVideo(video);
            break;
        }
        case 2: {
            Customer customer;
            customer.customerID = getValidatedIntInput("Enter Customer ID: ");
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, customer.name);
            cout << "Enter Address: ";
            getline(cin, customer.address);
            customerStore.addCustomer(customer);
            break;
        }
        case 3: {
            int customerID = getValidatedIntInput("Enter customer ID: ");
            int videoID = getValidatedIntInput("Enter video ID: ");
            if (videoStore.checkVideoAvailability(videoID)) {
                videoStore.rentVideo(videoID);
                customerRentStore.rentVideo(customerID, videoID);
            } else {
                cout << "Video not available for rent." << endl;
            }
            break;
        }
        case 4: {
            int customerID = getValidatedIntInput("Enter customer ID: ");
            int videoID = getValidatedIntInput("Enter video ID: ");
            videoStore.returnVideo(videoID);
            customerRentStore.returnVideo(customerID, videoID);
            break;
        }
        case 5: {
            int videoID = getValidatedIntInput("Enter video ID: ");
            videoStore.showVideoDetails(videoID);
            break;
        }
        case 6: {
            videoStore.displayAllVideos();
            break;
        }
        case 7: {
            int customerID = getValidatedIntInput("Enter customer ID: ");
            customerStore.showCustomerDetails(customerID);
            break;
        }
        case 8: {
            customerRentStore.printAllRentedVideos(customerStore, videoStore);
            break;
        }
        case 9: {
            videoStore.saveToFile("videos.txt");
            customerStore.saveToFile("customers.txt");
            customerRentStore.saveToFile("customer_rents.txt");
            cout << "Data saved successfully. Exiting..." << endl;
            break;
        }
        case 0:
            cout << "Exiting without saving..." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
        }
    } while (choice != 0 && choice != 9);

    return 0;
}
