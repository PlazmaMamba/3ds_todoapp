#include "TodoList.h"
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "json.hpp"

TodoList::TodoList() {
    todos = std::vector<Todo>();
}

void TodoList::addTodo(const std::string &title) {
    Todo newTodo(title);
    todos.push_back(newTodo);
}

void TodoList::removeTodoById(int id) {
    todos.erase(std::remove_if(todos.begin(), todos.end(),
        [id](const Todo &todo) 
        { return todo.getId() == id;}),
        todos.end());

}

Todo* TodoList::getTodoById(int id) {
    auto it = std::find_if(todos.begin(), todos.end(),
        [id](const Todo &todo) { return todo.getId() == id; });
    return (it != todos.end()) ? &(*it) : nullptr;
}

std::vector<Todo> TodoList::getAllTodos() const {
    return todos;
}

void TodoList::toggleTodo(int id) {
    Todo* todo = getTodoById(id);
    if (todo) {
        todo->toggleCompleted();
    }

}

std::string TodoList::toString() const {
    std::string result = "TodoList{\n";
    for (const auto &todo : todos) {
        result += "  " + todo.toString() + "\n";
    }
    result += "}";
    return result;
}

bool TodoList::saveToFile(const std::string &filename) const {
    /*std::ofstream file("save");

    if (!file.is_open()) {
        return false;
    }

    for (const auto &todo: todos){
        file << todo.getId() << "," << todo.getTitle() << "," << todo.isCompleted() << "\n";

    }
    file.close();
    return true;*/
    nlohmann::json data ;
    data["nextId"] = todos.empty() ? 0 : todos.back().getNextId();
    data["todos"]= nlohmann::json::array();
    for (const auto &todo: todos){
        nlohmann::json item;
        item["id"] = todo.getId();
        item["title"] = todo.getTitle();
        item["completed"] = todo.isCompleted();
        data["todos"].push_back(item);
    }

    std::ofstream file("save.json");
    if (!file.is_open()) {
        return false;
    }
    file << data.dump(4);
    file.close();
    return true;
}


bool TodoList::loadFromFile(const std::string &filename){
    std::ifstream file("save.json");
    if (!file.is_open()){
        return false;
    }
    todos.clear();

    nlohmann::json list;
    file >> list;
    for (const auto &item : list["todos"]) {
        int id = item["id"];
        std::string title = item["title"];
        bool completed = item["completed"];
        Todo todo(title);
        todo.setId(id);
        todo.setCompleted(completed);
        todos.push_back(todo);
    }

    if (!todos.empty()) {
        todos.back().setNextId(list["nextId"]);
    }

    file.close();
    return true;
}