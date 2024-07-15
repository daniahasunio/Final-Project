#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>

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
Video* videos
    void insertVideo(const Video& video) {
        videos.push_back(video);
    }

    void rentVideo(int videoID) {
        // TODO: Implement rentVideo operation
        
    }

    void returnVideo(int videoID) {
        // TODO: Implement returnVideo operation
    }

    void showVideoDetails() {
    }

    void displayAllVideos(Video* videos, int VideoID, string filename) {
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

    //File
    string filename = "Video.txt";
    string filename = "Customer.txt";
    string filename = "CustomerRent.txt";

    //Main Menu
    

    

    return 0;
}

void showVideoDetails(Video* videos, int VideoID) {

system("cls");
    int choice;
	int id_input;

system("cls");
		cout << "----------------------------------------------" << endl;				
		cout << "\t    Search for a Product		 \n";
		cout << "----------------------------------------------" << endl;
   
while (true){
					cout << "Enter ID: ";
					if (cin >> id_input){
						break;
					}
					else{
						cout << "Invalid. Please enter a positive integer only.\n";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				}

system("cls");
				cout << "----------------------------------------------" << endl;				
				cout << "\t    Search for a Product		 \n";
				cout << "----------------------------------------------" << endl;
				cout << setw(5) << "ID" << setw(20) << "NAME" << setw(20) << "CATEGORY" << setw(20) << "UNIT PRICE" << setw(15) << "QUANTITY" << setw(20) << "INVENTORY VALUE" << endl;

				for (int i = 0; i < id_; i++){

					// Compares input and id
					if (videos[i].id == id_input){

						// Iterates through the structure product array and displays them
						cout << setw(5)  << videos[i].videoID << setw(20) << videos[i].movieTitle << setw(20) << videos[i].genre << setw(20) << fixed << setprecision(2) << videos[i].production<< endl;
						found = true;

						}
				}
				if (found == false){
					cout << "\nNo Product Found" << endl;
				}

				system("pause");

void displayAllVideos(Video* videos, int VideoID, string filename) {
        fstream inFile(filename);
    cout << "==============================================" << endl;
    cout << "          Displaying All Videos            " << endl;
    cout << "==============================================" << endl;

        //check if file is empty
        inFile.seekg(0, ios::end);
        
    if (inFile.tellg() == 0){
		cout << "No Products Found.";
	}
	else{
        // If there are products found it will display all products
        cout<<setw(5) << "VIDEO ID" << setw(20) << "MOVIE TITLE" << setw(20) << "GENRE" << setw(20) << "PRODUCTION" << endl;
        for (int i = 0; i < VideoiID; i++) {
        cout << setw(10) << video.videoID << setw(20) << video.movieTitle << setw(20) << video.genre << setw(20) << video.production << setw(15) << endl;
		inFile.close();

	cout << endl;
	system("pause");

}
