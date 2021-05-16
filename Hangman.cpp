#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>

#ifdef _WIN32
#define CLRSCR system("cls");
#else
#define CLRSCR system("clear");
#endif

//#define CLRSCR system("cls"); // windows
//#define CLRSCR system("clear"); // linux & other

    /*
        ___
       |   |
       |   o
       |  /|\
       |  / \
      _|______
     |________|

     Word:
     _ _ _ _ _ _  _ _ _ _

     Aviable letters:
     A B C D E F G H I J K L M
     N O P Q R S T U V W X Y Z

     */

std::vector<std::string> chooseTopicOfWords() {
    std::vector<std::string> wordsData;
    std::string topic;
    std::cout << " Choose topic: ";
    std::cin >> topic;
    // random method: if type "random" to open random .txt file
    std::ifstream inputFile(topic +".txt");
    std::string word;
    while (std::getline(inputFile, word)) {
        wordsData.push_back(word);
    }
    return wordsData;
}

std::vector<std::string> createHang() {
    std::vector<std::string> hang;
    hang.push_back("    ___"); // 0
    hang.push_back("   |   "); // 1 rope
    hang.push_back("   |   "); // 2 head
    hang.push_back("   |  "); // 3 arms and body
    hang.push_back("   |  "); // 4 legs
    hang.push_back("  _|______"); // 5
    hang.push_back(" |________|"); // 6
    return hang;
}

void drawPartsOfHangman(int& wrongAttempts, std::vector<std::string>& hang) {
    switch (wrongAttempts) {
    case 1: hang[1] += "|"; break;
    case 2: hang[2] += "o"; break;
    case 3: hang[3] += "/"; break;
    case 4: hang[3] += "|"; break;
    case 5: hang[3] += "\\"; break;
    case 6: hang[4] += "/"; break;
    case 7: hang[4] += " \\"; break;
    }
}

void drawHangman(int& wrongAttempts, std::vector<std::string>& hang) {
    for (int i = 0; i < 7; i++) {
        std::cout << hang[i] << std::endl;
    }
    std::cout << std::endl;
}

int getRandomNumber(size_t lowRange, size_t highRange) {
    return lowRange + (rand() % (highRange - lowRange));
}

std::string getRandWord(const std::vector<std::string>& data) {
    std::string word;
    word = data[getRandomNumber(0, data.size())];
    //word = "Iron-man planet"; //example
    for (int i = 0; i < word.length(); ++i) {
        word[i] = toupper(word[i]);
    }
    return word;
}

void drawWord(const std::string& emptyWord, const std::vector<std::string>& data) {
    std::cout << " Word:" << std::endl;
    for (const char letter : emptyWord) {
        std::cout << " " << letter;
    }
    std::cout << std::endl;
}

std::string createEmptyWord(const std::string& word, int& foundLetters) {
    std::string emptyWord;
    for (const char letter : word) {
        if (letter == ' ') {
            emptyWord += ' ';
            foundLetters++;
            continue;
        }
        if (letter == '-') {
            emptyWord += '-';
            foundLetters++;
            continue;
        }
        emptyWord += '_';
    }
    return emptyWord;
}

bool checkLetterIfUsed(const char& letter, std::string& alphabet) {
    for (int i = 0; i < alphabet.length(); ++i) {
        if (alphabet[i] == toupper(letter)) {
            alphabet[i] = ' ';
            return false;
        }
    }
    return true;
}

void drawAviableLetters(const std::string& alphabet) {
    std::cout << std::endl;
    std::cout << " Aviable letters:" << std::endl;
    for (int i = 0; i < alphabet.length(); ++i) {
        std::cout << ' ' << alphabet[i] ;
        if (i == 12) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

bool checkLetter(const std::string& word, const char& letter, std::string& emptyWord, int& foundLetters) {
    bool found = false;
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == toupper(letter)) {
            emptyWord[i] = word[i];
            foundLetters++;
            found = true;
        }
    }
    return found;
}

int main()
{
    srand(time(nullptr));
    int foundLetters = 0;
    int wrongAttempts = 0;
    std::vector<std::string> data = chooseTopicOfWords();
    std::vector<std::string> hang = createHang();
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char letter;
    std::string word = getRandWord(data);
    std::string emptyWord = createEmptyWord(word, foundLetters);
    while (wrongAttempts != 7) {
        CLRSCR;
        drawHangman(wrongAttempts, hang);
        drawWord(emptyWord, data);
        drawAviableLetters(alphabet);
        std::cout << " Try with: ";
        std::cin >> letter;
        while (checkLetterIfUsed(letter, alphabet)) {
            std::cout << " Already used: ";
            std::cin >> letter;
        }
        if (checkLetter(word, letter, emptyWord, foundLetters)) {
            if (foundLetters == word.length()) {
                break;
            }
            continue;
        }
        wrongAttempts++; 
        drawPartsOfHangman(wrongAttempts, hang);
    }
    CLRSCR;
    drawHangman(wrongAttempts, hang);
    drawWord(word, data);
    drawAviableLetters(alphabet);
}
