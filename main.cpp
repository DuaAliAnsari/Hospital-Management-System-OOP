#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class RoomAlreadyReserved: public exception{ //custom exception to handle already booked rooms
public:
    const char*what(){
        return "This room is already reserved";
    }
};

class InSufficientFunds : public exception { //custom excpetion to handle if amount is not enought to carry out transaction
    const char* what() const noexcept override {
            return "You do not have sufficient funds to carry out this transaction";
    }
};

class User {
protected:
    string name;
    int ID;
    string password;

public:
    User(){}
    User(string n, int i, string p) : name(n), ID(i), password(p) {}

    void setName(string n) {
        name = n;
    }

    void setID(int i) {
        ID = i;
    }

    string getName() {
        return name;
    }

    int getID() {
        return ID;
    }
};

class Doctor : public User {
protected:
    string specialty;
    string time;
    int fee;
    int appointments;

public:
    Doctor(string n, int i, string s, string t, int f, int a) : User(n, i, ""), specialty(s), time(t), fee(f), appointments(a) {}
    static int getDoctorFee(const string& filename, const string& name) {
        ifstream file(filename);
        string line;
        int fee = -1;

        if (file.is_open()) {
            while (getline(file, line)) {
                stringstream ss(line);
                string idStr, doctorName, spec, time, feeStr;
                int id;

                getline(ss, idStr, ',');
                getline(ss, doctorName, ',');
                getline(ss, spec, ',');
                getline(ss, time, ',');
                getline(ss, feeStr, ',');

                id = stoi(idStr);

                if (doctorName == name) {
                    fee = stoi(feeStr);
                    break;
                }
            }
            file.close();
        } else {
            cout << "Error: Unable to open file " << filename << endl;
        }

        return fee;
    }
    static vector<Doctor> filterDoctorsBySpecialty(const string& filename, const string& specialty) {
        vector<Doctor> filteredDoctors;
        ifstream file(filename);
        string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                stringstream ss(line);
                string idStr, name, spec, time, feeStr;
                int id, fee;

                getline(ss, idStr, ',');
                getline(ss, name, ',');
                getline(ss, spec, ',');
                getline(ss, time, ',');
                getline(ss, feeStr, ',');

                id = stoi(idStr);
                fee = stoi(feeStr);

                if (spec == specialty) {
                    Doctor doctor(name, id, spec, time, fee, 0);
                    filteredDoctors.push_back(doctor);
                }
            }
            file.close();
        } else {
            cout << "Error: Unable to open file " << filename << endl;
        }

        return filteredDoctors;
    }

    static void print(const vector<Doctor>& doctors) {
        if (!doctors.empty()) {
            for (const Doctor& doctor : doctors) {
                cout << "Name: " << doctor.name << endl;
                cout << "Specialty: " << doctor.specialty << endl;
                cout << "Time: " << doctor.time << endl;
                cout << "Fee: " << doctor.fee << endl;
                cout << endl;
            }
        } else {
            cout << "No doctors found for this specialty." << endl;
        }
    }

    static void filterByName(const vector<Doctor>& doctors, const string& name) {
        bool found = false;
        for (const Doctor& doctor : doctors) {
            if (doctor.name == name) {
                cout << "Name: " << doctor.name << endl;
                cout << "Specialty: " << doctor.specialty << endl;
                cout << "Time: " << doctor.time << endl;
                cout << "Fee: " << doctor.fee << endl;
                cout << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No doctors found with the name " << name << "." << endl;
        }
    }

    static void filterByFee(const vector<Doctor>& doctors, int fee) {
        bool found = false;
        for (const Doctor& doctor : doctors) {
            if (doctor.fee <= fee) {
                cout << "Name: " << doctor.name << endl;
                cout << "Specialty: " << doctor.specialty << endl;
                cout << "Time: " << doctor.time << endl;
                cout << "Fee: " << doctor.fee << endl;
                cout << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No doctors found with a fee less than or equal to " << fee << "." << endl;
        }
    }

    static int bookAppointment(const string& filename, const string& name) {
        ifstream file(filename);
        ofstream tempFile("temp.csv");
        string line;
        int appointmentNumber = -1; // Initialize appointment number

        if (file.is_open() && tempFile.is_open()) {
            while (getline(file, line)) {
                stringstream ss(line);
                string idStr, doctorName, spec, time, feeStr, appointmentStr;
                int Id, fee, appointments;

                getline(ss, idStr, ',');
                getline(ss, doctorName, ',');
                getline(ss, spec, ',');
                getline(ss, time, ',');
                getline(ss, feeStr, ',');
                getline(ss, appointmentStr, ',');

                Id = stoi(idStr);
                fee = stoi(feeStr);
                appointments = stoi(appointmentStr);

                if (doctorName == name) {
                    appointments++;
                    appointmentNumber = appointments; // Assign appointment number
                    tempFile << Id << "," << doctorName << "," << spec << "," << time << "," << fee << "," << appointments << endl;
                } else {
                    tempFile << line << endl;
                }
            }
            file.close();
            tempFile.close();
            if (remove(filename.c_str()) != 0) {
                cerr << "Error: Unable to delete the original file: " << filename << endl;
            }
            if (rename("temp.csv", filename.c_str()) != 0) {
                cerr << "Error: Unable to rename the temporary file." << endl;
            }
        } else {
            cerr << "Error: Unable to open files for reading/writing." << endl;
        }

        return appointmentNumber;
    }

};

class Patient : public User {
protected:
    int age;
    double height;
    double weight;
    string bloodType;

public:

    double getbalance() {
        return balance;
    }
    Patient(): User(){}
    Patient(int i, string n, string pa,int a,double w, double h, string bt, double b)
            : User(n, i, pa), age(a), height(h), weight(w), bloodType(bt), balance(b) {}


    bool UserLogin(const string& pass, int id, const string& filename) {
        ifstream file(filename);
        string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                stringstream ss(line);
                string userIdStr, userName, userPass, ageStr, heightStr, weightStr, bloodType, balanceStr;

                getline(ss, userIdStr, ',');
                getline(ss, userName, ',');
                getline(ss, userPass, ',');
                getline(ss, ageStr, ',');
                getline(ss, heightStr, ',');
                getline(ss, weightStr, ',');
                getline(ss, bloodType, ',');
                getline(ss, balanceStr, ',');

                int ID = 0;
                try {
                    ID = stoi(userIdStr);
                } catch (const invalid_argument& e) {
                    cout << "Invalid ID format in file: " << userIdStr << endl;
                    continue;
                }

                if (pass == userPass && id == ID) {
                    cout << "You're successfully logged in!" << endl;
                    return true;
                }
            }
            file.close();
        } else {
            cout << "Error: Unable to open file " << filename << endl;
        }

        return false;
    }

    vector<Patient> loadpatients(string filename) { //process to get to it
        ifstream file(filename);
        vector<Patient> patients; //using to store contents of file
        if (!file.is_open()) {
            cerr << "Unable to open file" << endl;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);


            int id, age;
            string name, pass, bloodtype;
            double height, weight, balance;

            ss >> id;
            ss.ignore();
            getline(ss, name, ',');
            getline(ss, pass, ',');
            ss >> age;
            ss.ignore();
            ss >> weight;
            ss.ignore();
            ss >> height;
            ss.ignore();
            getline(ss, bloodtype, ',');
            ss >> balance;
            ss.ignore();

            Patient patient(id, name, pass, age, weight, height, bloodtype, balance);
            patients.push_back(patient);

        }
        file.close();
        return patients;
    }


    void savePatients(vector<Patient>& patients, const string& filename) { //this is to ensure all the changes written are saved
        ofstream file(filename);

        if (!file.is_open()) {
            cerr << "Error: Unable to open file." << endl;
            return;
        }

        for (auto& p : patients) {
            file << p.getID() << ","
                 << p.getName() << ","
                 << p.password << ","
                 << p.age << ","
                 << p.height << ","
                 << p.weight << ","
                 << p.bloodType << ","
                 << p.balance << endl;
        }

        file.close();
    }


    void make_payment(int patientID, double amount, const string& filename) {
        vector<Patient> patients = loadpatients("patients.csv"); //store patient data from load patients to patients vector
        bool found = false;

        for (auto& p : patients) {
            if (p.getID() == patientID) {
                if (amount <= p.balance) {
                    p.balance -= amount;
                    found = true;
                } else {
                    throw InSufficientFunds();
                }
            }
        }

        if (found) {
            savePatients(patients, filename);
            cout<<"ID: "<<patientID<<" your transaction has been carried out successfully of RS "<<amount<<endl;
        }
        else {
            cerr << "Error: Patient ID not found." << endl;
        }
    }

    double balance;
};

class room {
protected:
    string room_id;
    string room_type;
    bool booked;
    double price;
    vector<room> rooms;

public:
    room() {}
    room(string ri, string rt, bool b, double p) : room_id(ri), room_type(rt), booked(b), price(p) {}

    string getroom_id() const {
        return room_id;
    }

    string getroom_type() const {
        return room_type;
    }

    bool get_availblity() const {
        return booked;
    }

    double getprice() const {
        return price;
    }

    void set_availblity(bool b) {
        booked = b;
    }
};


class reserved_room {
protected:
    vector<room> rooms;
public:
    reserved_room() {
        rooms = loadrooms("rooms.csv");
    }

    vector<room> loadrooms(const string &filename) {
        vector<room> rooms;
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: unable to open file" << endl;
            return rooms;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);

            string r_id, r_type;
            bool book;
            double cost;

            getline(ss, r_id, ',');
            getline(ss, r_type, ',');
            ss >> book;
            ss.ignore();
            ss >> cost;
            ss.ignore();

            room room_(r_id, r_type, book, cost);
            rooms.push_back(room_);
        }
        file.close();
        return rooms;
    }

    void display_rooms() {
        cout << "--------------------Rooms--------------------" << endl;
        for (const auto &r: rooms) {
            cout << "Room ID: " << r.getroom_id()
                 << " Room Type: " << r.getroom_type()
                 << " Room Availability: " << (r.get_availblity() ? "Booked" : "Available")
                 << " Room Price: " << r.getprice() << endl;
        }
    }


    void saverooms(string filename) {
        ofstream file(filename);
        if (!file.is_open()) {

        }

        for (auto r: rooms) {
            file << r.getroom_id() << ',' << r.getroom_type() << ',' << r.get_availblity() << ',' << r.getprice()
                 << endl;
        }

        file.close();

    }

    void book_room(int id, const string &roomfile, const string &patientfile) {
        display_rooms();
        string room_id;
        cout << "Enter the ID of the room you want to book: ";
        cin >> room_id;

        bool roomFound = false;
        double roomPrice = 0.0;
        for (auto &r: rooms) {
            if (r.getroom_id() == room_id) {
                if (r.get_availblity()) {
                    throw RoomAlreadyReserved();
                } else {
                    r.set_availblity(true); // Update the availability status correctly
                    roomPrice = r.getprice();
                    roomFound = true;
                    break;
                }
            }
        }

        if (!roomFound) {
            cout << "Room with ID " << room_id << " not found." << endl;
            return;
        }

        // Save updated room information to file
        saverooms(roomfile);

        // Load patients to update the balance
        Patient p;
        vector<Patient> patients = p.loadpatients(patientfile);

        for (auto &pat: patients) {
            if (pat.getID() == id) {
                if (pat.getbalance() >= roomPrice) {
                    pat.make_payment(id, roomPrice, patientfile);
                    cout << "Room booked successfully!" << endl;
                } else {
                    throw InSufficientFunds();
                }
                break;
            }
        }
    }
};

class Medicine {
protected:
    string med_id;
    string name;
    double price;
    int quantity;

public:
    Medicine(string m,string n, double p, int q) :med_id(m), name(n), price(p), quantity(q){}

    string getmed_id() {
        return med_id;
    }

    string getName() {
        return name;
    }

    double getPrice() {
        return price;
    }

    int getQuantity() {
        return quantity;
    }

    void decreaseQuantity(int quan) {
        if (quan<=quantity) {
            quantity-=quan;
        }
    }
};

class Pharmacy {
public:
    vector<Medicine> loadMedicines(string filename) {
        vector<Medicine> medicines;
        ifstream file(filename); // reading file medicines
        if(!file.is_open()){
            cerr<<"Unable to open file"<<endl;
        }
        string line; // to read each line from csv
        while(getline(file,line)){ //reading till last line
            stringstream ss(line); //helps with comma

            string m_id, m_name; //making variables to store file data
            int m_quantity;
            double m_price;

            getline(ss, m_id, ',');
            getline(ss, m_name, ',');
            ss>>m_price;
            ss.ignore();
            ss>>m_quantity;
            ss.ignore();

            Medicine meds(m_id,m_name,m_price,m_quantity);
            medicines.push_back(meds);
        }

        file.close();
        return medicines;
    }

    void display_medicines(){
        cout<<"--------------------Medicines--------------------"<<endl;
        for(auto m: loadMedicines("medicines.csv")){
            cout<<"Medicine ID: "<<m.getmed_id()<<" Medicine Name: "<<m.getName()<<" Medicine Price: "<<m.getPrice()<<endl;
        }
    }

    void saveMedicinechanges(vector<Medicine> &meds, string &filename){
        ofstream file(filename);
        if(!file.is_open()){
            cerr<<"Error: unable to open file"<<endl;
        }

        for(auto m: meds){
            file<<m.getmed_id()<<","<<m.getName()<<","<<m.getPrice()<<","<<m.getQuantity()<<endl;
        }
        file.close();
    }


    void purchase_medicines(int id, string medfile, string patientfile) {
        vector<Medicine> meds = loadMedicines("medicines.csv");
        Patient p;
        vector<Patient> patients = p.loadpatients("patients.csv");

        display_medicines();

        string m_code;
        int quantity;

        cout << "Enter the code of the medicine you want to purchase: ";
        cin >> m_code;
        cout << "Enter the quantity you want to purchase: ";
        cin >> quantity;

        double total = 0.0;
        bool found = false;

        for (auto& m : meds) {
            if (m_code == m.getmed_id() && quantity <= m.getQuantity()) {
                total = m.getPrice() * quantity;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Medicine not found or insufficient quantity available." << endl;
            return;
        }

        for (auto& pat : patients) {
            if (pat.getID() == id) {
                if (total <= pat.balance) {
                    pat.make_payment(id, total, "patients.csv");
                    for (auto& m : meds) {
                        if (m_code == m.getmed_id()) {
                            m.decreaseQuantity(quantity);
                            break;
                        }
                    }
                    saveMedicinechanges(meds, medfile);
                    return;
                } else {
                    throw InSufficientFunds();
                }
            }
        }

    }


};

int main() {
    int userID;
    string password;
    int count = 0;

    while (count < 3) {
        cout << "Enter your user ID: ";
        cin >> userID;
        cin.ignore();
        cout << "Enter your password: ";
        getline(cin, password);

        Patient patient(0, "", "", 0, 0.0, 0.0, "", 0.0);

        if (patient.UserLogin(password, userID, "patients.csv")) {
            cout << "---------------------------------------" << endl;
            cout << "Welcome to Dua and Zara's Hospital App" << endl;
            cout << "---------------------------------------" << endl;

            int choice;
            do {
                cout << "Select an option to proceed further:" << endl;
                cout << "1. Doctor Section" << endl;
                cout << "2. Pharmacy Section" << endl;
                cout << "3. Room Section" << endl;
                cout << "0. Exit" << endl; // Added exit option for clarity
                cin >> choice;
                cin.ignore();

                switch (choice) {
                    case 1: {
                        string specialty;
                        cout << "Enter the field of doctor you would like to see (e.g. Cardiologist): ";
                        getline(cin, specialty);

                        vector<Doctor> filteredDoctors = Doctor::filterDoctorsBySpecialty("docFile.csv", specialty);

                        Doctor::print(filteredDoctors);

                        if (filteredDoctors.empty()) {
                            break;
                        }

                        bool filterAgain = true;
                        while (filterAgain) {
                            cout << "Choose an option to filter the doctors again:" << endl;
                            cout << "1. Filter by name" << endl;
                            cout << "2. Filter by fee" << endl;
                            cout << "3. Book an appointment" << endl;
                            cout << "4. Return to Main Menu" << endl;

                            int option;
                            cin >> option;
                            cin.ignore();

                            switch (option) {
                                case 1: {
                                    string name;
                                    cout << "Enter the name of the doctor you want to find: ";
                                    getline(cin, name);
                                    Doctor::filterByName(filteredDoctors, name);
                                    break;
                                }
                                case 2: {
                                    int fee;
                                    cout << "Enter the fee you want to filter doctors by: ";
                                    cin >> fee;
                                    cin.ignore();
                                    Doctor::filterByFee(filteredDoctors, fee);
                                    break;
                                }
                                case 3: {
                                    Patient patient{userID,"",password,0,0,0,"",0 };
                                    string name;
                                    cout << "Enter the name of the doctor to book an appointment with: ";
                                    getline(cin, name);
                                    int appointmentNumber = Doctor::bookAppointment("docFile.csv", name); // Get appointment number
                                    if (appointmentNumber != -1) {
                                        cout << "Appointment booked successfully! Your appointment number is: " << appointmentNumber << endl;
                                        patient.make_payment(userID,Doctor::getDoctorFee("docFile.csv",name),"patients.csv");
                                    } else {
                                        cout << "Failed to book appointment. Please try again later." << endl;
                                    }
                                    break;
                                }


                                case 4: {
                                    filterAgain = false;
                                    cout << "Returning to Main Menu." << endl;
                                    break;
                                }
                                default:
                                    cout << "Invalid option. Please choose again." << endl;
                                    break;
                            }
                        }
                        break; // Ensure to break after case 1
                    }

                    case 2: {
                        Pharmacy p;
                        int option;
                        do {
                            cout << "Select an option to further explore pharmacy:" << endl;
                            cout << "0. To Exit Pharmacy" << endl;
                            cout << "1. View Medicines" << endl;
                            cout << "2. Purchase Medicines" << endl;
                            cin >> option;
                            cin.ignore();

                            switch (option) {
                                case 0: {
                                    cout << "Going back to menu." << endl;
                                    break;
                                }
                                case 1: {
                                    p.display_medicines();
                                    break;
                                }
                                case 2: {
                                    // Call the purchase_medicines function if implemented
                                    p.purchase_medicines(userID,"medicines.csv","patient.csv");
                                    break;
                                }
                                default: {
                                    cout << "Incorrect option selected." << endl;
                                    break;
                                }
                            }
                        } while (option != 0);
                        break;
                    }

                    case 3: {
                        reserved_room r;
                        int option;
                        do {
                            cout << "Select an option to further explore Room section:" << endl;
                            cout << "0. To Exit Room" << endl;
                            cout << "1. View Rooms" << endl;
                            cout << "2. Rent room" << endl;
                            cin >> option;
                            cin.ignore();

                            switch (option) {
                                case 0: {
                                    cout << "Going back to menu." << endl;
                                    break;
                                }
                                case 1: {
                                    r.display_rooms();
                                    break;
                                }
                                case 2: {
                                    r.book_room(userID, "rooms.csv", "patients.csv");
                                    break;
                                }
                                default: {
                                    cout << "Incorrect option selected." << endl;
                                    break;
                                }
                            }
                        } while (option != 0);
                        break;
                    }

                    case 0: {
                        cout << "Exiting the program." << endl;
                        break;
                    }

                    default: {
                        cout << "Invalid option. Please choose again." << endl;
                        break;
                    }
                }
            } while (choice != 0);
            break;
        } else {
            cout << "Invalid userID/password, please try again." << endl;
            count++;
        }
    }

    if (count == 3) {
        cerr << "You have exceeded the number of login attempts." << endl;
    } return 0; }