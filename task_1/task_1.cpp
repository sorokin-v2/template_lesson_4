#include <fstream>

class Printable
{
public:
    virtual ~Printable() = default;

    virtual std::string printAsHTML() const = 0;        //Нарушен принцип разделения интерфейса
    virtual std::string printAsText() const = 0;        //Вместо одного универсального интерфейса
    virtual std::string printAsJSON() const = 0;        //рекомендуется создавать несколько узкоспециализированных
};

class Data : public Printable
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };

    Data(std::string data, Format format)
        : data_(std::move(data)), format_(format) {}

    std::string printAsHTML() const override  //Здесь возможно нарушен принцип единственной ответственности. Возможно распечатку в определенном формате нужно вынести в другой объект
    {
        if (format_ != Format::kHTML) {
            throw std::runtime_error("Invalid format!");    //Здесь нарушен принцип подстановки Барбары Лисков из-за выбрасывания исключения
        }
        return "<html>" + data_ + "<html/>";
    }
    std::string printAsText() const override     //Здесь возможно нарушен принцип единственной ответственности. Возможно распечатку в определенном формате нужно вынести в другой объект
    {
        if (format_ != Format::kText) {
            throw std::runtime_error("Invalid format!");
        }
        return data_;
    }
    std::string printAsJSON() const override     //Здесь возможно нарушен принцип единственной ответственности. Возможно распечатку в определенном формате нужно вынести в другой объект
    {
        if (format_ != Format::kJSON) {
            throw std::runtime_error("Invalid format!");
        }
        return "{ \"data\": \"" + data_ + "\"}";
    }

private:
    std::string data_;
    Format format_;
};

void saveTo(std::ofstream& file, const Printable& printable, Data::Format format)   //Нарушен принцип инверсии зависимостей. Вместо потока std::ofstream рекомендуется использовать std::ostream
{
    switch (format)     //Нарушен принцип открытости/закрытости (при добавлении нового формата необходимо изменять отлаженный старый код)
    {
    case Data::Format::kText:
        file << printable.printAsText();
        break;
    case Data::Format::kJSON:
        file << printable.printAsJSON();
        break;
    case Data::Format::kHTML:
        file << printable.printAsHTML();
        break;
    }
}

void saveToAsHTML(std::ofstream& file, const Printable& printable) {    //Нарушен принцип инверсии зависимостей. Вместо потока std::ofstream рекомендуется использовать std::ostream
    saveTo(file, printable, Data::Format::kHTML);
}

void saveToAsJSON(std::ofstream& file, const Printable& printable) {    //Нарушен принцип инверсии зависимостей. Вместо потока std::ofstream рекомендуется использовать std::ostream
    saveTo(file, printable, Data::Format::kJSON);
}

void saveToAsText(std::ofstream& file, const Printable& printable) {    //Нарушен принцип инверсии зависимостей. Вместо потока std::ofstream рекомендуется использовать std::ostream
    saveTo(file, printable, Data::Format::kText);
}