#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <queue>
#include <stack>
#include <limits> 

using namespace std;

// Video ADT
struct Video {
    int videoID;
    string movieTitle;
    string genre;
    string production;
    int numCopies;
};

class VideoStore {
private:
    list<Video> videos;

public:
    void insertVideo(const Video& video) {
        for (auto& existingVideo : videos) {
            if (existingVideo.videoID == video.videoID) {
                // Update the existing video details
                existingVideo.movieTitle = video.movieTitle;
                existingVideo.genre = video.genre;
                existingVideo.production = video.production;
                existingVideo.numCopies += video.numCopies; // Increment the number of copies
                cout << "Video updated successfully." << endl;
                return;
            }
        }
        // If video does not exist, insert it
        videos.push_back(video);
        cout << "Video inserted successfully." << endl;
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

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (auto& video : videos) {
            file << video.videoID << "," << video.movieTitle << "," << video.genre << ","
                << video.production << "," << video.numCopies << endl;
        }
        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
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

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (auto& customer : customers) {
            file << customer.customerID << "," << customer.name << "," << customer.address << endl;
        }
        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
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
                stack<int> tempStack;
                bool found = false;
                while (!rentedVideos.empty()) {
                    if (rentedVideos.top() == videoID) {
                        rentedVideos.pop();
                        found = true;
                        break;
                    }
                    tempStack.push(rentedVideos.top());
                    rentedVideos.pop();
                }
                while (!tempStack.empty()) {
                    rentedVideos.push(tempStack.top());
                    tempStack.pop();
                }
                if (found) {
                    cout << "Video returned successfully." << endl;
                }
                else {
                    cout << "Video not found in customer's rented videos." << endl;
                }
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

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (auto& rent : customerRents) {
            file << rent.customerID;
            stack<int> rentedVideos = rent.rentedVideos;
            while (!rentedVideos.empty()) {
                file << "," << rentedVideos.top();
                rentedVideos.pop();
            }
            file << endl;
        }
        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            CustomerRent rent;
            size_t pos = 0;
            pos = line.find(',');
            rent.customerID = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            while ((pos = line.find(',')) != string::npos) {
                int videoID = stoi(line.substr(0, pos));
                rent.rentedVideos.push(videoID);
                line.erase(0, pos + 1);
            }
            if (!line.empty()) {
                int videoID = stoi(line);
                rent.rentedVideos.push(videoID);
            }

            customerRents.push_back(rent);
        }
        file.close();
    }
};

int getValidatedIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        } else {
            cout << "Invalid input. Please enter an integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main() {
    VideoStore videoStore;
    CustomerStore customerStore;
    CustomerRentStore customerRentStore;

	//load files
    videoStore.loadFromFile("videos.txt");
    customerStore.loadFromFile("customers.txt");
    customerRentStore.loadFromFile("customer_rents.txt");
	
    int choice;
	cout << "==============================================" << endl;
	cout << "    QUEUETI PIE: Video Rental System   "<< endl;
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
        cout << "8. Display rented videos" << endl;
        cout << "9. Save data and exit" << endl;
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
            customerRentStore.printAllRentedVideos();
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
