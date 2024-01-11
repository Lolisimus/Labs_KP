//�������� ������ ����� �9122-02.03.03��, ���� 5
#include <iostream>
#include <sstream>
#include <stack>
#include <cmath>
#include <cctype>

class Parser {
public:
    // ����� ��� �������������� ������� ������ � �������� �������� ������
    static std::string parseToRPN(const std::string& input) {
        std::stringstream output;
        std::stack<char> operators;

        for (char token : input) {
            if (std::isdigit(token)) { // ���������� std::isdigit() �� <cctype>
                output << token << " "; // ����� �������� ��������� � �����
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
                operators.pop(); // ������� '(' �� �����
            }
            // ���������� ����� �������� (cos, sin, % � �.�.) �� �������������
            // else if (isNewOperation(token)) {
            //     // ��������� ����� ��������
            // }
        }

        while (!operators.empty()) {
            output << operators.top() << " ";
            operators.pop();
        }

        return output.str();
    }

public:
    // ��������, �������� �� ������ ����������
    static bool isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
    }

    // ��������, �������� �� ��������1 � ����� ������� �����������, ��� ��������2
    static bool hasHigherPrecedence(char op1, char op2) {
        int precedenceOp1 = getOperatorPrecedence(op1);
        int precedenceOp2 = getOperatorPrecedence(op2);

        return precedenceOp1 >= precedenceOp2;
    }

    // ��������� ���������� ���������
    static int getOperatorPrecedence(char op) {
        if (op == '+' || op == '-') {
            return 1;
        } else if (op == '*' || op == '/') {
            return 2;
        } else if (op == '%') {
            return 3;
        }
        // ���������� ����������� ��� ����� �������� �� �������������
        // else if (op == '�����_��������') {
        //     return ���������_�����_��������;
        // }
        return 0; // ��� ����������� ����������
    }
};

class Calculator {
public:
    // ����� ��� ���������� ��������� � �������� �������� ������
    static double calculateRPN(const std::string& rpn) {
        std::stack<double> operands;
        std::stringstream input(rpn);

        std::string token;
        while (input >> token) {
            if (std::isdigit(token[0])) { // ���������� std::isdigit() �� <cctype>
                operands.push(std::stod(token));
            } else if (Parser::isOperator(token[0])) {
                double operand2 = operands.top();
                operands.pop();
                double operand1 = operands.top();
                operands.pop();

                double result = performOperation(operand1, operand2, token[0]);
                operands.push(result);
            }
            // ��������� ���������� ����� �������� (cos, sin, % � �.�.) �� �������������
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
    // ���������� ��������
    static double performOperation(double operand1, double operand2, char op) {
        switch (op) {
            case '+': return operand1 + operand2;
            case '-': return operand1 - operand2;
            case '*': return operand1 * operand2;
            case '/': return operand1 / operand2;
            case '%': return fmod(operand1, operand2);
            // ���������� ���������� ����� �������� (cos, sin, % � �.�.) �� �������������
            // case '�����_��������': return ����������_�����_��������(operand1);
            default: return 0.0; // ��� ����������� ����������
        }
    }
};

int main() {
    std::string inputExpression;
    std::cout << "Vvedite virajeniye (only nums in [0..9]): ";
    std::getline(std::cin, inputExpression);

    // �������������� � �������� �������� ������
    std::string rpnExpression = Parser::parseToRPN(inputExpression);
    std::cout << "Reverse Polish Notation: " << rpnExpression << std::endl;

    // ���������� ����������
    double result = Calculator::calculateRPN(rpnExpression);
    std::cout << "Res: " << result << std::endl;

    return 0;
}