#include <iostream>
#include <string>

struct Date {
    int day;
    int month;
    int year;
};

enum class Priority {
    LOW,
    MEDIUM,
    HIGH
};

class Task {
protected:
    std::string title;
    Date creationDate;
    Priority priority;

public:
    Task(std::string t, Date d, Priority p) 
        : title(std::move(t)), creationDate(d), priority(p) {}

    virtual ~Task() = default;

    virtual void printInfo() const {
        std::string priorityStr;
        switch (priority) {
            case Priority::LOW: priorityStr = "Низкий"; break;
            case Priority::MEDIUM: priorityStr = "Средний"; break;
            case Priority::HIGH: priorityStr = "Высокий"; break;
        }

        std::cout << "Наименование задачи: " << title << "\n"
                  << "Дата создания: " << creationDate.day << "." << creationDate.month << "." << creationDate.year << "\n"
                  << "Приоритет: " << priorityStr << std::endl;
    }
};

class TimedTask : public Task {
private:
    std::string duration;

public:
    TimedTask(std::string t, Date d, Priority p, std::string dur)
        : Task(std::move(t), d, p), duration(std::move(dur)) {}

    void printInfo() const override {
        Task::printInfo();
        std::cout << "Длительность выполнения процесса \"" << title << "\": " << duration << std::endl;
    }
};

int main() {
    Date date{25, 5, 2026};
    TimedTask timedTask("Выполнение базового процесса", date, Priority::HIGH, "2 часа");
    
    Task* taskPtr = &timedTask;
    taskPtr->printInfo();

    return 0;
}

