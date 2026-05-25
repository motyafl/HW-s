#include <iostream>
#include <string>
#include <stdexcept>

class Item {
protected:
    int id;
    std::string title;
    int year;

public:
    Item(int id, std::string title, int year) 
        : id(id), title(std::move(title)), year(year) {}

    Item(const Item& other) 
        : id(other.id), title(other.title), year(other.year) {}

    virtual ~Item() = default;

    Item& operator=(const Item& other) {
        if (this != &other) {
            id = other.id;
            title = other.title;
            year = other.year;
        }
        return *this;
    }

    char& operator[](size_t index) {
        if (index >= title.length()) {
            throw std::out_of_range("Индекс вышел за границы названия");
        }
        return title[index];
    }

    const char& operator[](size_t index) const {
        if (index >= title.length()) {
            throw std::out_of_range("Индекс вышел за границы названия");
        }
        return title[index];
    }

    virtual void printInfo() const {
        std::cout << "ID: " << id << ", Название: " << title << ", Год: " << year;
    }

    int getYear() const { return year; }

    friend void compareByYear(const Item& first, const Item& second);
};

void compareByYear(const Item& first, const Item& second) {
    if (first.year < second.year) {
        std::cout << "Старший объект: ";
        first.printInfo();
        std::cout << std::endl;
    } else {
        std::cout << "Старший объект: ";
        second.printInfo();
        std::cout << std::endl;
    }
}

class Book : public Item {
private:
    std::string author;
    static int count;

public:
    Book(int id, std::string title, int year, std::string author)
        : Item(id, std::move(title), year), author(std::move(author)) {
        ++count;
    }

    Book(const Book& other) : Item(other), author(other.author) {
        ++count;
    }

    ~Book() override {
        --count;
    }

    void printInfo() const override {
        Item::printInfo();
        std::cout << ", Автор: " << author << std::endl;
    }

    static int getCount() { return count; }
};

int Book::count = 0;

class Magazine : public Item {
private:
    int issueNumber;
    static int count;

public:
    Magazine(int id, std::string title, int year, int issueNumber)
        : Item(id, std::move(title), year), issueNumber(issueNumber) {
        ++count;
    }

    Magazine(const Magazine& other) : Item(other), issueNumber(other.issueNumber) {
        ++count;
    }

    ~Magazine() override {
        --count;
    }

    void printInfo() const override {
        Item::printInfo();
        std::cout << ", Номер выпуска: " << issueNumber << std::endl;
    }

    static int getCount() { return count; }
};

int Magazine::count = 0;

class DVD : public Item {
private:
    int duration;
    static int count;

public:
    DVD(int id, std::string title, int year, int duration)
        : Item(id, std::move(title), year), duration(duration) {
        ++count;
    }

    DVD(const DVD& other) : Item(other), duration(other.duration) {
        ++count;
    }

    ~DVD() override {
        --count;
    }

    void printInfo() const override {
        Item::printInfo();
        std::cout << ", Длительность: " << duration << " мин." << std::endl;
    }

    static int getCount() { return count; }
};

int DVD::count = 0;

int main() {
    try {
        Item* library[3];
        library[0] = new Book(101, "Преступление и наказание", 1866, "Фёдор Достоевский");
        library[1] = new Magazine(202, "Наука и жизнь", 2024, 5);
        library[2] = new DVD(303, "Интерстеллар", 2014, 169);

        std::cout << "Информация об объектах через базовый указатель" << std::endl;
        for (int i = 0; i < 3; ++i) {
            library[i]->printInfo();
        }
        std::cout << std::endl;

        std::cout << "Количество книг в системе: " << Book::getCount() << std::endl;
        std::cout << "Количество журналов в системе: " << Magazine::getCount() << std::endl;
        std::cout << "Количество DVD в системе: " << DVD::getCount() << std::endl;
        std::cout << std::endl;

        std::cout << "Проверка работы с символами названия" << std::endl;
        std::cout << "3-й символ названия первой книги: " << (*library[0])[2] << std::endl;
        
        std::cout << "Попытка обратиться к 100-му символу названия журнала..." << std::endl;
        std::cout << (*library[1])[100] << std::endl;

    } catch (const std::out_of_range& e) {
        std::cout << "Перехвачено исключение: " << e.what() << std::endl;
    }

    std::cout << std::endl;

    Book book1(104, "Старик и море", 1952, "Эрнест Хемингуэй");
    Book book2(105, "Оно", 1986, "Стивен Кинг");
    
    std::cout << "--- Сравнение по году издания ---" << std::endl;
    compareByYear(book1, book2);

    return 0;
}

