/************************************
 * Автор: Важенин С.С               *
 * Дата:  08.11.2024                *
 * Название: Лабораторная работа №1 *
 ************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

bool checkTwoLetters(string checkedString) { // Проверяем буквы в строке на алфавитность
    for (int letter = 0; letter < checkedString.size(); ++letter) {
        if (isalpha(checkedString[letter]) && isalpha(checkedString[letter + 1])) {
            return true;
        } 
    }
    return false;
}

bool findElementVector(vector<char> lettersText, char vectorElement) {
    auto result{find(begin(lettersText), end(lettersText), vectorElement)}; // Находим элемент в массиве 
    if (result == end(lettersText)) {
        return false;      
    } 
    return true;
}

bool findElementVector(vector<string> lettersText, string vectorElement) {
    auto result{find(begin(lettersText), end(lettersText), vectorElement)}; // Находим элемент в массиве 
    if (result == end(lettersText)) {
        return false;      
    } 
    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");
  
    string word;
    string line;
    string fullLine;
  
    fstream file;
    int countElement = 0;
    file.open("1.txt");

    if (file.is_open()) {
        while (getline(file, line)) {
            fullLine += line + " "; // Получаем полную строку из абзацев
        }
    }
  
    cout <<  "Текст: " << endl;
    cout << fullLine << endl;

    stringstream ss(fullLine); // Запихиваем в поток строку

    vector<string> wordsText; // Вектор слов

    vector<string> wordsLettersTwo; // Общий вектор двух буквенных сочетаний
    vector<string> wordsLetterTwoPower; // Уникальный вектор двух буквенных сочетаний

    vector<char> lettersText; // Общий вектор букв
    vector<char> lettersPower; // Уникальный вектор lettersText

    while (getline(ss, word, ' ')) { // Получаем слова разделенные пробелом
        wordsText.push_back(word); // запихиваем в массив
    }

    for (int word = 0; word <  wordsText.size(); ++word) {
        for (int letter = 0; letter < wordsText[word].size(); ++letter) {
            lettersText.push_back(wordsText[word][letter]);  // Из слов в массив заталкиваем буквы
        }
    }

    sort(lettersText.begin(), lettersText.end()); // Сортируем массив букв

    for (int letter = 0; letter < lettersText.size(); ++letter) {
        if (isalpha(lettersText[letter]) && (findElementVector(lettersPower, lettersText[letter]) == false)) { // Проверяем является ли символ алфавитным и есть ли он в массиве
            lettersPower.push_back(lettersText[letter]);
        }
    }

    sort(lettersPower.begin(), lettersPower.end()); // Сортируем массив уникальных букв
    
    cout << "Однобуквенные символы: " << endl;

    for (int letter = 0; letter < lettersPower.size(); ++letter) {
        countElement = count(lettersText.begin(), lettersText.end(), lettersPower[letter]); // Считаем элементы в общем массиве букв
        cout << "Символ: " << lettersPower[letter] << " | ";
        cout << "Количество: " << countElement << endl;
    }

    string twoWords;

    for (int wordCount = 0; wordCount < wordsText.size(); ++wordCount) {
        string word = wordsText[wordCount];
        for (int letterCount = 0; letterCount < wordsText[wordCount].size() - 1; ++letterCount) {
            string oneLetter(1, word[letterCount]); // Преобразовываем char в string
            string twoLetter(1, word[letterCount + 1]); 
            twoWords = oneLetter + twoLetter;
            if (checkTwoLetters(twoWords) == 1) {
                wordsLettersTwo.push_back(twoWords);
            }
        }
    }

    sort(wordsLettersTwo.begin(), wordsLettersTwo.end());
  
    for (int wordTwo = 0; wordTwo < wordsLettersTwo.size(); ++wordTwo) {
        if (findElementVector(wordsLetterTwoPower, wordsLettersTwo[wordTwo]) == false) {
            wordsLetterTwoPower.push_back(wordsLettersTwo[wordTwo]);
        }
    }

    cout << "Двухбуквенные сочетания: " << endl;

    for (int wordTwo = 0; wordTwo < wordsLetterTwoPower.size(); ++wordTwo) {
        countElement = count(wordsLettersTwo.begin(), wordsLettersTwo.end(), wordsLetterTwoPower[wordTwo]);
        cout << "Символ: " << wordsLetterTwoPower[wordTwo] << " | ";
        cout << "Количество: " << countElement << endl;
    }
}
