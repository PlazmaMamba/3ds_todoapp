#ifndef TODO_H
#define TODO_H

#include <string>

class Todo {
    private:
        inline static int nextId = 0;
        int id;
        std::string title;
        bool completed;

    public:
    Todo(const std::string &title);
    int getId() const;
    std::string getTitle() const;
    bool isCompleted() const;
    void setCompleted(bool completed);
    void setTitle(const std::string &title);
    void setId(int id);
    void toggleCompleted();
    std::string toString() const;
    int getNextId() const;
    void setNextId(int nextId);
};

#endif

