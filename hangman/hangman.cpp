//Christopher Jung
//Date: 3/25/2025
//The Hangman Game is a fun word-guessing game made in C++. Players choose a category like Animals, Countries, or Foods and select a difficulty level (Easy, Medium, or Hard).
//The game picks a random word, and the player must guess it letter by letter. Each wrong guess reduces their limited attempts, and they must guess each letter within 10 seconds.
//If they get stuck, they can use a hint to reveal a letter. The game ends when the player either guesses the word correctly or runs out of attempts.
//This project is great for learning C++ basics, randomization, and user input handling.





#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

struct WordCategory {
    string category;
    vector<pair<string, string>> words; // Pair of word and hint
};

vector<WordCategory> categories = {
    {"Animals", { {"elephant", "Large land mammal with a trunk"},
                   {"giraffe", "Tallest land animal"},
                   {"dolphin", "Intelligent marine mammal"},
                   {"penguin", "Flightless bird that swims"},
                   {"kangaroo", "Australian animal that hops"} }},

    {"Fruits", { {"banana", "Long yellow fruit"},
                 {"strawberry", "Small red berry with seeds on the outside"},
                 {"pineapple", "Spiky fruit with sweet yellow flesh"},
                 {"blueberry", "Small blue fruit often used in muffins"},
                 {"mango", "Sweet tropical fruit with a large pit"} }},

    {"Countries", { {"canada", "North American country known for maple syrup"},
                     {"brazil", "Largest country in South America"},
                     {"japan", "Island nation known for sushi"},
                     {"italy", "European country famous for pizza"},
                     {"egypt", "Home of the pyramids"} }}
};

void displayWord(const string &word, const vector<char> &guessedLetters) {
    for (char c : word) {
        if (find(guessedLetters.begin(), guessedLetters.end(), c) != guessedLetters.end()) {
            cout << c << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

void playGame(const WordCategory &category, int maxAttempts) {
    srand(time(0));
    int index = rand() % category.words.size();
    string word = category.words[index].first;
    string hint = category.words[index].second;
    vector<char> guessedLetters;
    int attemptsLeft = maxAttempts;
    
    cout << "\nCategory: " << category.category << endl;
    cout << "Hint: " << hint << endl;
    
    while (attemptsLeft > 0) {
        displayWord(word, guessedLetters);
        cout << "Attempts left: " << attemptsLeft << endl;
        cout << "Guess a letter (10 seconds max): ";

        char guess;
        auto start = chrono::steady_clock::now();
        bool timeout = false;

        // Read input with a timer
        while (true) {
            if (cin.peek() != EOF) {  // Check if user entered input
                cin >> guess;
                break;
            }
            auto elapsed = chrono::steady_clock::now() - start;
            if (chrono::duration_cast<chrono::seconds>(elapsed).count() >= 10) {
                timeout = true;
                break;
            }
            this_thread::sleep_for(chrono::milliseconds(100));  // Check every 100ms
        }

        if (timeout) {
            cout << "\nTime's up! You lost an attempt.\n";
            attemptsLeft--;
            continue;
        }

        if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
            cout << "You already guessed that letter! Try again." << endl;
            continue;
        }
        guessedLetters.push_back(guess);
        
        if (word.find(guess) == string::npos) {
            attemptsLeft--;
        }
        
        bool allGuessed = true;
        for (char c : word) {
            if (find(guessedLetters.begin(), guessedLetters.end(), c) == guessedLetters.end()) {
                allGuessed = false;
                break;
            }
        }
        
        if (allGuessed) {
            cout << "Congratulations! You guessed the word: " << word << endl;
            return;
        }
    }
    cout << "Game over! The word was: " << word << endl;
}

int main() {
    cout << "Welcome to Hangman!" << endl;
    cout << "Choose a difficulty level:\n1. Easy (10 attempts)\n2. Medium (7 attempts)\n3. Hard (5 attempts)" << endl;
    int choice;
    cin >> choice;
    int maxAttempts = (choice == 1) ? 10 : (choice == 2) ? 7 : 5;
    
    cout << "Choose a category:" << endl;
    for (size_t i = 0; i < categories.size(); i++) {
        cout << i + 1 << ". " << categories[i].category << endl;
    }
    int categoryChoice;
    cin >> categoryChoice;
    
    if (categoryChoice < 1 || categoryChoice > categories.size()) {
        cout << "Invalid choice. Exiting..." << endl;
        return 1;
    }
    
    playGame(categories[categoryChoice - 1], maxAttempts);
    return 0;
}
