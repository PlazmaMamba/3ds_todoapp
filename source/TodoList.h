#include <string>
#include "Todo.h"
#include <vector>

class TodoList{
    private:
        std::vector<Todo> todos;
    public:
        TodoList();
        void addTodo(const std::string &title);
        void removeTodoById(int id);
        Todo* getTodoById(int id);
        std::vector<Todo> getAllTodos() const;
        void toggleTodo(int id);
        std::string toString() const;

        bool saveToFile(const std::string &filename) const;
        bool loadFromFile(const std::string &filename);
};