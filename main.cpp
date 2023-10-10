#include <iostream>
#include <string>
#include <vector>

// Single Linked List Node
template <typename T> struct Node {
  T data;
  Node *next;
  Node(const T &item) : data(item), next(nullptr) {}
};

template <typename Item_Type> class Single_Linked_List {
private:
  Node<Item_Type> *head;
  Node<Item_Type> *tail;
  size_t num_items;

public:
  Single_Linked_List() : head(nullptr), tail(nullptr), num_items(0) {}

  Node<Item_Type> *getHead() const { return head; }

  void push_front(const Item_Type &item) {
    Node<Item_Type> *new_node = new Node<Item_Type>(item);
    if (empty()) {
      head = tail = new_node;
    } else {
      new_node->next = head;
      head = new_node;
    }
    num_items++;
  }

  void push_back(const Item_Type &item) {
    Node<Item_Type> *new_node = new Node<Item_Type>(item);
    if (empty()) {
      head = tail = new_node;
    } else {
      tail->next = new_node;
      tail = new_node;
    }
    num_items++;
  }

  void pop_front() {
    if (empty()) {
      std::cout << "List is empty, cannot pop_front()." << std::endl;
      return;
    }
    Node<Item_Type> *temp = head;
    head = head->next;
    delete temp;
    num_items--;
  }

  void pop_back() {
    if (empty()) {
      std::cout << "List is empty, cannot pop_back()." << std::endl;
      return;
    }
    if (head == tail) {
      delete head;
      head = tail = nullptr;
    } else {
      Node<Item_Type> *temp = head;
      while (temp->next != tail) {
        temp = temp->next;
      }
      delete tail;
      tail = temp;
      tail->next = nullptr;
    }
    num_items--;
  }

  Item_Type front() const {
    if (empty()) {
      std::cout << "List is empty, cannot access front()." << std::endl;
      return Item_Type();
    }
    return head->data;
  }

  Item_Type back() const {
    if (empty()) {
      std::cout << "List is empty, cannot access back()." << std::endl;
      return Item_Type();
    }
    return tail->data;
  }

  bool empty() const { return num_items == 0; }

  void insert(size_t index, const Item_Type &item) {
    if (index > num_items) {
      push_back(item);
    } else if (index == 0) {
      push_front(item);
    } else {
      Node<Item_Type> *new_node = new Node<Item_Type>(item);
      Node<Item_Type> *temp = head;
      for (size_t i = 0; i < index - 1; i++) {
        temp = temp->next;
      }
      new_node->next = temp->next;
      temp->next = new_node;
      num_items++;
    }
  }

  bool remove(size_t index) {
    if (empty() || index >= num_items) {
      return false;
    }

    if (index == 0) {
      pop_front();
    } else {
      Node<Item_Type> *temp = head;
      for (size_t i = 0; i < index - 1; i++) {
        temp = temp->next;
      }
      Node<Item_Type> *to_delete = temp->next;
      temp->next = to_delete->next;
      delete to_delete;
      if (index == num_items - 1) {
        tail = temp;
      }
      num_items--;
    }

    return true;
  }

  size_t find(const Item_Type &item) const {
    Node<Item_Type> *temp = head;
    size_t index = 0;
    while (temp != nullptr) {
      if (temp->data == item) {
        return index;
      }
      temp = temp->next;
      index++;
    }
    return num_items;
  }

  ~Single_Linked_List() {
    while (!empty()) {
      pop_front();
    }
  }
};

// Abstract base class for Employee
class Employee {
protected:
  std::string name;
  int id;

public:
  Employee(const std::string &n, int i) : name(n), id(i) {}

  virtual double calculateWeeklySalary() const = 0;
  virtual double calculateHealthCareContributions() const = 0;
  virtual int calculateVacationDays() const = 0;
  virtual int getId() const { return id; }

  virtual void displayInfo() const {
    std::cout << "Name: " << name << "\nID: " << id << std::endl;
  }
};

// Derived class for Professional Employees
class Professional : public Employee {
private:
  double monthlySalary;
  int vacationDays;

public:
  Professional(const std::string &n, int i, double salary, int days)
      : Employee(n, i), monthlySalary(salary), vacationDays(days) {}

  double calculateWeeklySalary() const override {
    return monthlySalary / 4; // Assuming a month has 4 weeks
  }

  double calculateHealthCareContributions() const override {
    return 0.2 * monthlySalary; // 20% of monthly salary for healthcare
  }

  int calculateVacationDays() const override { return vacationDays; }

  void displayInfo() const override {
    Employee::displayInfo();
    std::cout << "Salary: $" << monthlySalary << " per month\n";
    std::cout << "Healthcare Contributions: $"
              << calculateHealthCareContributions() << " per week\n";
    std::cout << "Vacation Days: " << vacationDays << " days per year"
              << std::endl;
  }
};

// Derived class for Nonprofessional Employees
class Nonprofessional : public Employee {
private:
  double hourlyRate;
  int hoursWorked;

public:
  Nonprofessional(const std::string &n, int i, double rate, int hours)
      : Employee(n, i), hourlyRate(rate), hoursWorked(hours) {}

  double calculateWeeklySalary() const override {
    return hourlyRate * hoursWorked;
  }

  double calculateHealthCareContributions() const override {
    return 0.1 * calculateWeeklySalary(); // 10% of weekly salary for healthcare
  }

  int calculateVacationDays() const override {
    return hoursWorked / 10; // Assuming 1 hour of work gives 0.1 vacation day
  }

  void displayInfo() const override {
    Employee::displayInfo();
    std::cout << "Hourly Rate: $" << hourlyRate << " per hour\n";
    std::cout << "Hours Worked: " << hoursWorked << " hours per week\n";
    std::cout << "Salary: $" << calculateWeeklySalary() << " per week\n";
    std::cout << "Healthcare Contributions: $"
              << calculateHealthCareContributions() << " per week\n";
    std::cout << "Vacation Days: " << calculateVacationDays()
              << " days per year" << std::endl;
  }
};


//MAIN PROGRAM MENU
int main() {
  Single_Linked_List<int> intList;
  std::vector<Employee *> employees;

  while (true) {
    std::cout << "Menu:\n";
    std::cout << "1. Add an integer to the list\n";
    std::cout << "2. Remove an integer from the list\n";
    std::cout << "3. Display the list\n";
    std::cout << "4. Add a Professional Employee\n";
    std::cout << "5. Add a Nonprofessional Employee\n";
    std::cout << "6. Display Employee Information\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1: {
      std::cout << "Enter an integer to add to the list: ";
      int item;
      std::cin >> item;
      intList.push_back(item);
      break;
    }
    case 2: {
      std::cout << "Enter the index of the integer to remove: ";
      size_t index;
      std::cin >> index;
      if (intList.remove(index)) {
        std::cout << "Integer removed successfully.\n";
      } else {
        std::cout << "Invalid index or list is empty.\n";
      }
      break;
    }
    case 3: {
      std::cout << "List Contents: ";
      Node<int> *current = intList.getHead(); // Access the head of the list
      while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next; // Move to the next node
      }
      std::cout << std::endl;
      break;
    }
    case 4: {
      std::cout << "Enter Professional Employee details:\n";
      std::string name;
      int id;
      double salary;
      int days;
      std::cout << "Name: ";
      std::cin.ignore();
      std::getline(std::cin, name);
      std::cout << "ID: ";
      std::cin >> id;
      std::cout << "Monthly Salary: ";
      std::cin >> salary;
      std::cout << "Vacation Days: ";
      std::cin >> days;
      employees.push_back(new Professional(name, id, salary, days));
      break;
    }
    case 5: {
      std::cout << "Enter Nonprofessional Employee details:\n";
      std::string name;
      int id;
      double rate;
      int hours;
      std::cout << "Name: ";
      std::cin.ignore();
      std::getline(std::cin, name);
      std::cout << "ID: ";
      std::cin >> id;
      std::cout << "Hourly Rate: ";
      std::cin >> rate;
      std::cout << "Hours Worked: ";
      std::cin >> hours;
      employees.push_back(new Nonprofessional(name, id, rate, hours));
      break;
    }
    case 6: {
      std::cout << "Enter Employee ID to display information: ";
      int id;
      std::cin >> id;
      bool found = false;
      for (const auto &emp : employees) {
        if (emp->getId() == id) {
          emp->displayInfo();
          found = true;
          break;
        }
      }
      if (!found) {
        std::cout << "Employee not found.\n";
      }
      break;
    }
    case 7: {
      // Clean up allocated memory for employees
      for (auto emp : employees) {
        delete emp;
      }
      return 0;
    }
    default:
      std::cout << "Invalid choice. Try again.\n";
    }
  }

  return 0;
}
