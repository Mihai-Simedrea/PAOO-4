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

    return 0;
}
