/* Запрограммируйте шаблонный класс, реализующий стек. Класс должен поддерживать следующие операции:
 * помещение объекта в стек, извлечение объекта из стека, получение размерности стека.
 * В случае попытки вызова операции извлечение объекта из стека при условии, что стек пуст,
 * должно генерироваться исключение класса EStackEmpty. Данный класс должен содержать публичный
 * метод char* what(), возвращающий диагностическое сообщение. */

#include <iostream>
#include <string.h>

//#include <cstdlib>
//using namespace std;

// макрос для определения емкости стека LIFO
#define SIZE 10
  // ---------------------- start of namespace exc
namespace exc {


class Exception
{
private:
    char* message;
public:
    Exception(const char* arg_message)
    {
        message = new char[strlen(arg_message)+1];
        strcpy(message,arg_message);
    }

    Exception(const Exception &arg)
    {
        message = new char[strlen(arg.message)+1];
        strcpy(message, arg.message);
    }
    ~Exception()
    {
        delete message;
    }
    const char* what() const { return message; }

};

class EStackEmpty : public Exception
{
public:
    explicit EStackEmpty(const char* arg) : Exception(arg) {}
    explicit EStackEmpty(const Exception& arg) : Exception(arg) {}
};
} // ---------------------- end of namespace exc

class Stack
{
    int *arr;           // указатель начала массива
    int top;            // текущий размер масссива
    int capacity;       // максимальная емкость массива

public:
    Stack(int size = SIZE); 		// constructor
    ~Stack();   					// destructor

    void push(int);     // помещение объекта в стек
    int pop();          // извлечение объекта из стека
    int peek();         // чтение элемента Last In

    int size();         // размер непустого стека
    bool isEmpty();     // проверка на пустоту
    bool isFull();      // проверка на заполненность

friend class Exception;
};

// constructor to initialize the stack
Stack::Stack(int size)
{
    arr = new int[size];
    capacity = size;
    top = -1;
}

// destructor to free memory allocated to the stack
Stack::~Stack() {
    delete[] arr;
}

// функция - реализация метода inserting to stack
void Stack::push(int x)
{
    if (isFull())       // проверка заполненности стека
        {            
            throw exc::EStackEmpty("Insertion fault: Stack is Full!");
        }
    std::cout << "Inserting " << x << std::endl;
    arr[++top] = x;
}

// функция - извлечение из стека extacting from stack
int Stack::pop()
{    
    if (isEmpty())      // проверка не пуст ли стек
    {        
        throw exc::EStackEmpty("Extraction fault: Stack is Empty!");
    }
    std::cout << "Removed " << peek() << std::endl;
    return arr[top--];
}

// функция - возврат "верхнего"(LastOut) значения стека
int Stack::peek()
{
    if (!isEmpty()) {
        return arr[top];
    }
    else {
        exit(EXIT_FAILURE);
    }
}

// функция - возврат текущего количества введенных в стек значений (заполненность стека)
int Stack::size() {
    std::cout << "stack size : ";
    return top + 1;
}

// функция - проверка не пуст ли стек
bool Stack::isEmpty() {
    return top == -1;
}

//функция - проверка заполненности стека
bool Stack::isFull() {
    return top == capacity - 1;
}

int main()
{
    Stack pt(3);    // емкость стека, для удобства проверки кода, иначе SIZE
    try {           // Критический участок. Возможны исключительные ситуации
        pt.push(10);
        pt.push(20);
        pt.push(3);
        pt.push(33);
    }
    catch (const exc::Exception &s)     // перехват исключения и вывод на экран диагностического сообщения
    {
        std::cout << s.what() << std::endl;
    }

    std::cout << pt.size() << std::endl;

    try {           // Критический участок. Возможны исключительные ситуации
        pt.pop();
        pt.pop();
        pt.pop();
        pt.pop();
    }
    catch (const exc::Exception &s)     // перехват исключения и вывод на экран диагностического сообщения
    {
        std::cout << s.what() << std::endl;
    }

    return 0;
}
