#include <iostream>
#include <ostream>
#include <fstream>

struct IPrintable
{
    virtual ~IPrintable() = default;
    virtual std::string print(const std::string&) const = 0;
};

struct PrintAsHTML : public IPrintable {

    PrintAsHTML() = default;
    ~PrintAsHTML() override = default;

    std::string print(const std::string& str) const override {
        return "<html>" +str + "<html/>";
    }
};

struct PrintAsText : public IPrintable {

    PrintAsText() = default;
    ~PrintAsText() override = default;

    std::string print(const std::string& str) const override {
        return str;
    }
};

struct PrintAsJSON : public IPrintable {

    PrintAsJSON() = default;
    ~PrintAsJSON() override = default;

    std::string print(const std::string& str) const override {
        return "{ \"data\": \"" + str + "\"}";
    }
};

class Data
{
public:

    explicit Data(std::string data) : data_(std::move(data)){}
    std::string get_data() { return data_; }

private:
    std::string data_;
};

void SaveTo(std::ostream& out, const std::string& str, const IPrintable& printable)
{
    out << printable.print(str);
 }


int main()
{
    Data data("Test");
    SaveTo(std::cout, data.get_data(), PrintAsHTML());
    std::cout << std::endl;
    SaveTo(std::cout, data.get_data(), PrintAsText());
    std::cout << std::endl;
    SaveTo(std::cout, data.get_data(), PrintAsJSON());
    std::cout << std::endl;
    std::ofstream file("test.txt", std::ios::app);
    SaveTo(file, data.get_data(), PrintAsHTML());
    SaveTo(file, data.get_data(), PrintAsText());
    SaveTo(file, data.get_data(), PrintAsJSON());
}
