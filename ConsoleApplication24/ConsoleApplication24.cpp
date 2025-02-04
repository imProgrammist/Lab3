#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Базовый класс для варианта ответа
class AnswerOption {
private:
    string text;       // Текст варианта ответа
    bool isCorrect;         // Флаг правильности ответа

public:
    AnswerOption(const string& text, bool isCorrect)
        : text(text), isCorrect(isCorrect) {}

    // Геттеры
    string getText() const { return text; }
    bool getIsCorrect() const { return isCorrect; }

    // Вывод варианта ответа
    void display() const {
        cout << "- " << text;
        if (isCorrect) cout << " (правильный)";
        cout << endl;
    }
};
// Базовый класс для вопроса
class Question {
protected:
    string text;                       // Текст вопроса
    vector<AnswerOption> answerOptions; // Варианты ответов

public:
    Question(const string& text) : text(text) {}

    // Добавление варианта ответа
    void addAnswerOption(const AnswerOption& option) {
        answerOptions.push_back(option);
    }
    // Вывод вопроса и вариантов ответа
    virtual void display() const {
        cout << "Вопрос: " << text << endl;
        for (const auto& option : answerOptions) {
            option.display();
        }
    }
    // Виртуальный метод для проверки ответа (полиморфизм)
    virtual bool checkAnswer(const vector<int>& selectedOptions) const {
        return false; // Базовая реализация
    }
};
// Класс для вопроса с множественным выбором
class MultipleChoiceQuestion : public Question {
public:
    MultipleChoiceQuestion(const string& text) : Question(text) {}

    // Переопределение метода проверки ответа
    bool checkAnswer(const vector<int>& selectedOptions) const override {
        for (size_t i = 0; i < answerOptions.size(); ++i) {
            // Если выбранный вариант не совпадает с правильным
            if (answerOptions[i].getIsCorrect() !=
                (find(selectedOptions.begin(), selectedOptions.end(), i) != selectedOptions.end())) {
                return false;
            }
        }
        return true;
    }
};
// Класс для дисциплины
class Discipline {
private:
    string name;                  // Название дисциплины
    vector<Question*> questions;  // Список вопросов

public:
    Discipline(const string& name) : name(name) {}

    // Добавление вопроса
    void addQuestion(Question* question) {
        questions.push_back(question);
    }

    // Вывод дисциплины и всех вопросов
    void display() const {
        cout << "Дисциплина: " << name << std::endl;
        for (const auto& question : questions) {
            question->display();
        }
    }

    // Деструктор для освобождения памяти
    ~Discipline() {
        for (auto& question : questions) {
            delete question;
        }
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    // Создаем дисциплину
    Discipline discipline("Программирование на C++");

    // Создаем вопросы
    Question* q1 = new Question("Что такое класс в C++?");
    q1->addAnswerOption(AnswerOption("Функция", false));
    q1->addAnswerOption(AnswerOption("Тип данных", true));
    q1->addAnswerOption(AnswerOption("Переменная", false));

    MultipleChoiceQuestion* q2 = new MultipleChoiceQuestion("Какие из перечисленных типов являются встроенными в C++?");
    q2->addAnswerOption(AnswerOption("int", true));
    q2->addAnswerOption(AnswerOption("float", true));
    q2->addAnswerOption(AnswerOption("string", false));

    // Добавляем вопросы в дисциплину
    discipline.addQuestion(q1);
    discipline.addQuestion(q2);

    // Выводим дисциплину и вопросы
    discipline.display();

    // Проверка ответов
    vector<int> selectedOptions = { 1 }; // Выбран второй вариант (индексация с 0)
    cout << "Ответ на первый вопрос " << (q1->checkAnswer(selectedOptions) ? "правильный" : "неправильный") << endl;

    selectedOptions = { 0, 1 }; // Выбраны первый и второй варианты
    cout << "Ответ на второй вопрос " << (q2->checkAnswer(selectedOptions) ? "правильный" : "неправильный") << endl;

    return 0;
}