#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <queue>
#include <stack>
#include <limits> 
#include <cctype>
#include <iomanip>

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
                cout << "Video ID: " << setw(5) << video.videoID << endl;
                cout << "Movie Title: " << setw(5) << video.movieTitle << endl;
                cout << "Genre: " << setw(5) << video.genre << endl;
                cout << "Production: " << setw(5) << video.production << endl;
                cout << "Number of Copies: " << setw(5) << video.numCopies << endl;
                return;
            }
        }
        cout << "Video not found." << endl;
    }

    void displayAllVideos() {
        for (auto& video : videos) {
            cout << "Video ID: " << setw(5) << video.videoID << endl;
            cout << "Movie Title: " << setw(5) << video.movieTitle << endl;
            cout << "Genre: " << setw(5) << video.genre << endl;
            cout << "Production: " << setw(5) << video.production << endl;
            cout << "Number of Copies: "  << setw(5) << video.numCopies << endl;
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
                cout << "Customer ID: " << setw(5) << customer.customerID << endl;
                cout << "Name: " << setw(5) << customer.name << endl;
                cout << "Address: " << setw(5) << customer.address << endl;
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

// Function to validate if input contains only alphabetic characters and spaces
bool isValidName(const string& name) {
    for (char ch : name) {
        if (!isalpha(ch) && !isspace(ch)) {
            return false;
        }
    }
    return true;
}

int main() {
    
    VideoStore videoStore;
    CustomerStore customerStore;
    CustomerRentStore customerRentStore;

    // Load data from files
    videoStore.loadFromFile("videos.txt");
    customerStore.loadFromFile("customers.txt");
    customerRentStore.loadFromFile("customer_rents.txt");

    Video video1 = { 1, "Longlegs", "Horror", "C2 Motion picture Group", 10 };
    Video video2 = { 2, "Immaculate", "Horror", "Black Bear Pictures", 10 };
    Video video3 = { 3, "The First Omen", "Horror", "Phantom Four Films", 10 };
    Video video4 = { 4, "MaXXXine", "Horror", "Motel Mojave", 10 };
    Video video5 = { 5, "In A Violent Nature", "Horror", "Shudder Films", 10 };

    Video video6 = { 6, "The Tearsmith", "Romance", "Colorado Films", 10 };
    Video video7 = { 7, "Upgraded", "Romance", "Amazon MGM Studios", 10 };
    Video video8 = { 8, "The Idea of You", "Romance", "Welle Entertainment", 10 };
    Video video9 = { 9, "Players", "Romance", "Mark Platt Productions", 10 };
    Video video10 = { 10, "Love, Divided", "Romance", "Tripictures", 10 };

    Video video11 = { 11, "Spaceman", "Sci-Fi", "Tango Entertainment", 10 };
    Video video12 = { 12, "Atlas", "Sci-Fi", "ASAP Entertainmentt", 10 };
    Video video13 = { 13, "Ghostbusters: Frozen Empire", "Sci-Fi", "Columbia Pictures", 10 };
    Video video14 = { 14, "Dune: Part Two", "Sci-Fi", "Legendary Pictures", 10 };
    Video video15 = { 15, "Ultraman: Rising", "Sci-Fi", "Netflix Animation", 10 };

    Video video16 = { 16, "Furiosa: A Mad Max Saga", "Action", "Domain Entertainment", 10 };
    Video video17 = { 17, "The Beekeeper", "Action", "Miramax", 10 };
    Video video18 = { 18, "Damsel", "Action", "Roth Films", 10 };
    Video video19 = { 19, "Roadhouse", "Action", "Silver Pictures", 10 };
    Video video20 = { 20, "Argylle", "Action", "Apple Original Films", 10 };

    Video video21 = { 21, "IF", "Comedy", "Sunday Night Productions", 10 };
    Video video22 = { 22, "Ricky Stanicky", "Comedy", "Footloose Production", 10 };
    Video video23 = { 23, "The Fall Guy", "Comedy", "87 North Productions", 10 };
    Video video24 = { 24, "Lift", "Comedy", "Hartbeat", 10 };
    Video video25 = { 25, "The Garfield Movie", "Comedy", "Columbia Pictures", 10 };


    videoStore.insertVideo(video1);
    videoStore.insertVideo(video2);
    videoStore.insertVideo(video3);
    videoStore.insertVideo(video4);
    videoStore.insertVideo(video5);
    videoStore.insertVideo(video6);
    videoStore.insertVideo(video7);
    videoStore.insertVideo(video8);
    videoStore.insertVideo(video9);
    videoStore.insertVideo(video10);
    videoStore.insertVideo(video11);
    videoStore.insertVideo(video12);
    videoStore.insertVideo(video13);
    videoStore.insertVideo(video14);
    videoStore.insertVideo(video15);
    videoStore.insertVideo(video16);
    videoStore.insertVideo(video17);
    videoStore.insertVideo(video18);
    videoStore.insertVideo(video19);
    videoStore.insertVideo(video20);
    videoStore.insertVideo(video21);
    videoStore.insertVideo(video22);
    videoStore.insertVideo(video23);
    videoStore.insertVideo(video24);
    videoStore.insertVideo(video25);

    int choice;
	cout << "==============================================" << endl;
	cout << "    QUEUETI PIE: Video Rental System   "<< endl;
	cout << "==============================================" << endl;

    do {
        cout << "Enter your choice:" << endl;
        cout << "[1] New Video" << endl;
        cout << "[2] Rent a Video" << endl;
        cout << "[3] Return a Video" << endl;
        cout << "[4] Show Video Details	" << endl;
        cout << "[5] Display all videos" << endl;
        cout << "[7] Customer Maintenance" << endl;
        cout << "[8] Exit Program" << endl;
        choice = getValidatedIntInput("Choice: ");

        switch (choice) {
        case 1: {
            cout<<"==============================================\n"<<endl;
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
            cout<<"==============================================\n"<<endl;
            break;
        }
        case 2: {
            cout<<"==============================================\n"<<endl;
            int customerID = getValidatedIntInput("Enter customer ID: ");
            int videoID = getValidatedIntInput("Enter video ID: ");
            if (videoStore.checkVideoAvailability(videoID)) {
                videoStore.rentVideo(videoID);
                customerRentStore.rentVideo(customerID, videoID);
            } else {
                cout << "Video not available for rent." << endl;
            }
            cout<<"==============================================\n"<<endl;
            break;
        }
        case 3: {
            cout<<"==============================================\n"<<endl;
            int customerID = getValidatedIntInput("Enter customer ID: ");
            int videoID = getValidatedIntInput("Enter video ID: ");
            videoStore.returnVideo(videoID);
            customerRentStore.returnVideo(customerID, videoID);
            cout<<"==============================================\n"<<endl;
            break;
        }
        case 4: {
            cout<<"==============================================\n"<<endl;
            int videoID = getValidatedIntInput("Enter video ID: ");
            videoStore.showVideoDetails(videoID);
            cout<<"==============================================\n"<<endl;
            break;
        }
        case 5: {
            cout<<"==============================================\n"<<endl;
            videoStore.displayAllVideos();
            cout<<"==============================================\n"<<endl;
            break;
        }
        case 6: {
            cout << "==============================================\n" << endl;
            int videoID = getValidatedIntInput("Enter video ID: ");
            if (videoStore.checkVideoAvailability(videoID)) {
                cout << "Video is available for rent." << endl;
            } else {
                cout << "Video is not available for rent." << endl;
            }
            cout << "==============================================\n" << endl;
            break;
        }

        case 7: {
            int input;
            cout<<"==============================================\n"<<endl;
            cout<< "[1] Add New Customer" << endl;
            cout<< "[2] Show Customer Details" << endl;
            cout<< "[3] List of Videos Rented by a Customer" << endl;
            input = getValidatedIntInput("Choice: ");

            switch (input) {
                case 1:{
                    cout<<"==============================================\n"<<endl;
                    Customer customer;
                    customer.customerID = getValidatedIntInput("Enter Customer ID: ");

                    // Clear input buffer
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    do {
                        cout << "Enter Name: ";
                        getline(cin, customer.name);

                        if (!isValidName(customer.name)) {
                            cout << "Invalid Input. Please enter a valid name (alphabetic characters and spaces only)." << endl;
                        }

                    } while (!isValidName(customer.name));

                    cout << "Enter Address: ";
                    getline(cin, customer.address);
                    customerStore.addCustomer(customer);
                    cout<<"==============================================\n"<<endl;
                    break;
                }
    
                case 2:{
                    cout<<"==============================================\n"<<endl;
                    int customerID = getValidatedIntInput("Enter customer ID: ");
                customerStore.showCustomerDetails(customerID);
                cout<<"==============================================\n"<<endl;
                break;
                }

                case 3:{
                    cout<<"==============================================\n"<<endl;
                    customerRentStore.printAllRentedVideos();
                    cout<<"==============================================\n"<<endl;
                    break;
                }
                default:
                cout << "Invalid choice." << endl;
                break;
            }
            break;
        }
        case 8: {
            cout<<"==============================================\n"<<endl;
            videoStore.saveToFile("videos.txt");
            customerStore.saveToFile("customers.txt");
            customerRentStore.saveToFile("customer_rents.txt");
            cout << "Data saved successfully. Exiting..." << endl;
            cout<<"==============================================\n"<<endl;
            break;
        }
        default:
        cout<<"==============================================\n"<<endl;
            cout << "Invalid choice." << endl;
            cout<<"==============================================\n"<<endl;
            break;
        }

    } while (choice != 0 && choice != 9);

    return 0;
}
