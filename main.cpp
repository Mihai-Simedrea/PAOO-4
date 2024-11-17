#include <iostream>
#include <string>
#include <list>

/// Item 4

// but for consistency, it's often best to initialize everything via member initialization.

class PhoneNumber {
    public:
        PhoneNumber(const std::string& number) : number_(number) {}
        std::string getNumber() const { return number_; }
    private:
        std::string number_;
};

class ABEntry {
    public:
        ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones)
            : theName(name),
            theAddress(address),
            thePhones(phones),
            numTimesConsulted(0)
            // member init
        {}

        void display() const {
            std::cout << "Name: " << theName << "\nAddress: " << theAddress << "\nPhones: ";
            for (const auto& phone : thePhones) {
                std::cout << phone.getNumber() << " ";
            }
            std::cout << "\nConsulted: " << numTimesConsulted << " times\n";
        }

    private:
        std::string theName;
        std::string theAddress;
        std::list<PhoneNumber> thePhones;
        int numTimesConsulted;
};



/*
Fortunately, a small design change eliminates the problem entirely.
All that has to be done is to move each non-local static object into its

own function, where it’s declared static.
*/

class FileSystem {
    public:
        std::size_t numDisks() const { return 5; }
    };

    FileSystem& getFileSystem() {
        static FileSystem fs;
        return fs;
}

class Directory {
    public:
        Directory() {
            disks_ = getFileSystem().numDisks();
        }

        void showDisks() const {
            std::cout << "Number of disks: " << disks_ << std::endl;
        }

    private:
        std::size_t disks_;
    };

    Directory& getTempDirectory() {
        static Directory tempDir;
        return tempDir;
}


/// Item 5

template<typename T>
class NamedObject {
    public:
        // the default ctor won't exist anymore
        // only copy assignment operator, copy ctor, destructor
        NamedObject(const std::string& name, const T& value)
            : nameValue(name), objectValue(value) {}

    private:
        std::string nameValue;
        T objectValue;
};


class Const {
    public:
        Const(int val) : constValue(val) {}
    private:
        const int constValue;
};

class Ref {
    public:
        Ref(int& ref) : refValue(ref) {}
    private:
        int& refValue;
};


// Item 6 

/*
Instead, declare the copy constructor and the
copy assignment operator private. By declaring a member function
explicitly, you prevent compilers from generating their own version,
*/


class Uncopyable {
    protected:
        Uncopyable() {}          // Allow construction
        ~Uncopyable() {}         // Allow destruction
    private:
        Uncopyable(const Uncopyable&);            // Prevent copying
        Uncopyable& operator=(const Uncopyable&); // Prevent assignment
};

// Make HomeForSale non-copyable by inherit from Uncopyable
class HomeForSale : private Uncopyable {
    public:
        HomeForSale() {}
        ~HomeForSale() {}
};


int main(int argc, char** argv) {
    // Item 4

    std::list<PhoneNumber> phones = { PhoneNumber("+40724231204"), PhoneNumber("+40724531241") };
    ABEntry entry("Steve Jobs", "2101 Waverley St, Palo Alto, CA", phones);
    entry.display();

    Directory& dir = getTempDirectory();
    dir.showDisks();


    // Item 5
    NamedObject<int> no1("Smallest Prime Number", 2);
    NamedObject<int> no2(no1);
    no2 = no1;

    Const a(10), b(20);
    // b = a; // error: copy assignment operator isn't generated

    int x = 10, y = 20;
    Ref obj1(x);
    Ref obj2(y);
    // obj1 = obj2; // error: copy ctor isn't generated


    // Item 6
    HomeForSale h1;
    // HomeForSale h2(h1); // compilation error

    HomeForSale h3;
    // h3 = h1; // compilation error

    return 0;
}
