//Васильев Никита МОАИС Б9122-02.03.03тп, лаба 5
#include <iostream>
#include <sstream>
#include <stack>
#include <cmath>
#include <cctype>

class Parser {
public:
    // Метод для преобразования обычной записи в обратную польскую запись
    static std::string parseToRPN(const std::string& input) {
        std::stringstream output;
        std::stack<char> operators;

        for (char token : input) {
            if (std::isdigit(token)) { // Используем std::isdigit() из <cctype>
                output << token << " "; // Числа напрямую добавляем в вывод
            } else if (isOperator(token)) {
                while (!operators.empty() && hasHigherPrecedence(operators.top(), token)) {
                    output << operators.top() << " ";
                    operators.pop();
                }
                operators.push(token);
            } else if (token == '(') {
                operators.push(token);
            } else if (token == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    output << operators.top() << " ";
                    operators.pop();
                }
                operators.pop(); // Убираем '(' из стека
            }
            // Добавление новых операций (cos, sin, % и т.д.) по необходимости
            // else if (isNewOperation(token)) {
            //     // Обработка новой операции
            // }
        }

        while (!operators.empty()) {
            output << operators.top() << " ";
            operators.pop();
        }

        return output.str();
    }

public:
    // Проверка, является ли символ оператором
    static bool isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
    }

    // Проверка, является ли оператор1 с более высоким приоритетом, чем оператор2
    static bool hasHigherPrecedence(char op1, char op2) {
        int precedenceOp1 = getOperatorPrecedence(op1);
        int precedenceOp2 = getOperatorPrecedence(op2);

        return precedenceOp1 >= precedenceOp2;
    }

    // Получение приоритета оператора
    static int getOperatorPrecedence(char op) {
        if (op == '+' || op == '-') {
            return 1;
        } else if (op == '*' || op == '/') {
            return 2;
        } else if (op == '%') {
            return 3;
        }
        // Добавление приоритетов для новых операций по необходимости
        // else if (op == 'новая_операция') {
        //     return приоритет_новой_операции;
        // }
        return 0; // Для неизвестных операторов
    }
};

class Calculator {
public:
    // Метод для вычисления выражения в обратной польской записи
    static double calculateRPN(const std::string& rpn) {
        std::stack<double> operands;
        std::stringstream input(rpn);

        std::string token;
        while (input >> token) {
            if (std::isdigit(token[0])) { // Используем std::isdigit() из <cctype>
                operands.push(std::stod(token));
            } else if (Parser::isOperator(token[0])) {
                double operand2 = operands.top();
                operands.pop();
                double operand1 = operands.top();
                operands.pop();

                double result = performOperation(operand1, operand2, token[0]);
                operands.push(result);
            }
            // Обработка выполнения новой операции (cos, sin, % и т.д.) по необходимости
            // else if (isNewOperation(token)) {
            //     double operand = operands.top();
            //     operands.pop();
            //     double result = performNewOperation(operand, token);
            //     operands.push(result);
            // }
        }

        return operands.top();
    }

private:
    // Выполнение операции
    static double performOperation(double operand1, double operand2, char op) {
        switch (op) {
            case '+': return operand1 + operand2;
            case '-': return operand1 - operand2;
            case '*': return operand1 * operand2;
            case '/': return operand1 / operand2;
            case '%': return fmod(operand1, operand2);
            // Добавление выполнения новой операции (cos, sin, % и т.д.) по необходимости
            // case 'новая_операция': return выполнение_новой_операции(operand1);
            default: return 0.0; // Для неизвестных операторов
        }
    }
};

int main() {
    std::string inputExpression;
    std::cout << "Vvedite virajeniye (only nums in [0..9]): ";
    std::getline(std::cin, inputExpression);

    // Преобразование в обратную польскую запись
    std::string rpnExpression = Parser::parseToRPN(inputExpression);
    std::cout << "Reverse Polish Notation: " << rpnExpression << std::endl;

    // Вычисление результата
    double result = Calculator::calculateRPN(rpnExpression);
    std::cout << "Res: " << result << std::endl;

    return 0;
}