#include "Todo.h"
#include <string>


Todo::Todo(const std::string &title)
    : id(nextId++), title(title), completed(false) {
        
    }

int Todo::getId() const{
    return id;
}

std::string Todo::getTitle() const{
    return title;
}

bool Todo::isCompleted() const{
    return completed;
}

void Todo::setCompleted(bool completed)
{
    this->completed = completed;
}

void Todo::setTitle(const std::string &title) {
    this->title = title;
}

void Todo::setId(int id) {
    this->id = id;
}

void Todo::toggleCompleted() {
    this->completed = !this->completed;
}

std::string Todo::toString() const{
    return "Todo{id: " + std::to_string(id) + ", title: " + title + ", completed: " + (completed ? "true" : "false") + "}";

}

int Todo::getNextId() const {
    return nextId;
}

void Todo::setNextId(int nextId) {
    this->nextId = nextId;
}