#include <iostream>
#include <string>
using namespace std;

// NGO class with static donation_id_counter and different functionalities
class NGO {
public:
    string name;
    int fund;
    static int donation_id_counter;
    int Donation_id;
    static string nextId();

    NGO() : name("Unknown"), fund(0), Donation_id(donation_id_counter++) {}
    
    NGO(string n, int f) : name(n), fund(f), Donation_id(donation_id_counter++) {}

    // Unary operators
    NGO& operator++() {
        fund++;
        return *this;
    }

    NGO& operator--() {
        fund--;
        return *this;
    }

    bool operator!() const {
        return fund == 0;
    }

    // Binary operators
    NGO operator+(const NGO& other) const {
        return NGO(name + " and " + other.name, fund + other.fund);
    }

    NGO operator-(const NGO& other) const {
        return NGO(name + " and " + other.name, fund - other.fund);
    }

    NGO operator*(int multiplier) const {
        return NGO(name, fund * multiplier);
    }

    void print() const {
        cout << name << ": " << fund << " (Donation ID: " << Donation_id << ")" << endl;
    }

    // Subscript operator
    string projects[4] = { "Healthcare Program", "Education Initiative", "Clean Water Project", "Women Empowerment" };
    string operator[](int index) {
        if (index < 0 || index >= 4) return "Invalid index!";
        return projects[index];
    }
};

int NGO::donation_id_counter = 101;
string NGO::nextId() {
    return "DON" + to_string(donation_id_counter++);
}

// User class with overloaded constructors
class User {
    string donor, Place, email;
    int amt;
public:
    User(string u) : donor(u), email("Not provided"), Place("Not provided"), amt(0) {}

    User(string u, string e, string ev) : donor(u), email(e), Place(ev), amt(0) {}

    User(string u, string e, string ev, int a) : donor(u), email(e), Place(ev), amt(a) {}

    void display() {
        cout << "Donor: " << donor;
        cout << "\nEmail: " << email;
        cout << "\nPlace: " << Place;
        cout << "\nAmount: " << amt << "\n";
    }
};

// Donor class hierarchy
class Donor {
protected:
    string name;
    int id;
    double amount;
    string place;

public:
    Donor(string n, int i, double a, string p) : name(n), id(i), amount(a), place(p) {}

    virtual void display() {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Amount: $" << amount << endl;
        cout << "Place: " << place << endl;
    }

    virtual ~Donor() {}
};

class CashDonor : public Donor {
public:
    CashDonor(string n, int i, double a, string p) : Donor(n, i, a, p) {}

    void display() override {
        cout << "Cash Donation:\n";
        Donor::display();
    }
};

// Volunteer class
class Volunteer {
    string name;
public:
    Volunteer(string n) : name(n) {}

    void showVolunteer() {
        cout << "Volunteer Name: " << name << endl;
    }
};

// Event and FEvent classes
class Event : public NGO {
    string eventType;
public:
    Event(string ngoName, string type) : NGO(ngoName, 0), eventType(type) {}

    void showEvent() {
        cout << "Event Type: " << eventType << endl;
    }
};

class FEvent : public Event, public Donor, public Volunteer {
    string fundType;
public:
    FEvent(string ngoName, string eventType, string donorName, double amount, int donorID, string place, string volName, string fundType)
        : Event(ngoName, eventType), Donor(donorName, donorID, amount, place), Volunteer(volName), fundType(fundType) {}

    void showDetails() {
        cout << "Fundraising Event Details:\n";
        showEvent();
        Donor::display();
        Volunteer::showVolunteer();
        cout << "Fundraising Type: " << fundType << endl;
    }
};

// Helper function
string& retVal(string& x) {
    return x;
}

void disp(string X, string x, string Y, string y) {
    cout << X << " = " << x;
    cout << "\n";
    cout << Y << " = " << y;
}

int main() {
    // Part 1: NGO Fund Management
    NGO ngo1("CRY NGO", 800);
    NGO ngo2("CARE NGO", 200);

    ++ngo1;
    --ngo2;
    bool isInactive = !ngo2;

    NGO combined = ngo1 + ngo2;
    NGO difference = ngo1 - ngo2;
    NGO multiplied = ngo1 * 2;

    ngo1.print();
    ngo2.print();
    cout << "Is NGO2 inactive? " << (isInactive ? "Yes" : "No") << endl;
    combined.print();
    difference.print();
    multiplied.print();

    // Part 2: User Profiles
    User user1("Rachel");
    User user2("Fay", "fay2006@gmail.com", "Chennai");
    User user3("Praveena", "praveena2024@hotmail.com", "Mumbai", 25000);

    cout << "\nUser1 Profile:\n";
    user1.display();
    cout << "\nUser2 Profile:\n";
    user2.display();
    cout << "\nUser3 Profile:\n";
    user3.display();

    // Part 3: Event and Fundraising
    FEvent fundraisingEvent("Green Earth", "Gala", "John", 10000, 123, "New York", "Sarah", "Online Auction");
    fundraisingEvent.showDetails();

    // Part 4: Subscript operator
    cout << "Project at index 0: " << ngo1[0] << endl;
    cout << "Project at index 4: " << ngo1[4] << endl;

    // Part 5: String Reference Example
    string p = "The election is decided.";
    string& q = retVal(p);
    disp("p", p, "q", q);
    p = "The votes have been counted.";
    cout << "\n\nAfter only changing p:\n";
    disp("p", p, "q", q);

    return 0;
}
