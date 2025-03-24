//Christopher Jung
//Date: 3/24/2025
//First personal program
// Code assistance provided by ChatGPT (OpenAI) for the Flashcard program
// Helped with logic, structuring, and implementation of various functions





#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>  // For random_shuffle
#include <ctime>      // For seeding random number generator

using namespace std;

struct Flashcard {
    string question;
    string answer;
};

// Function to load flashcards from file
vector<Flashcard> loadFlashcards(const string &filename) {
    vector<Flashcard> flashcards;
    ifstream file(filename);
    if (!file) {
        cout << "No existing flashcards found. Creating a new set.\n";
        return flashcards;
    }

    Flashcard card;
    while (getline(file, card.question) && getline(file, card.answer)) {
        flashcards.push_back(card);
    }
    file.close();
    return flashcards;
}

// Function to save flashcards to file
void saveFlashcards(const vector<Flashcard> &flashcards, const string &filename) {
    ofstream file(filename);
    for (const auto &card : flashcards) {
        file << card.question << endl;
        file << card.answer << endl;
    }
    file.close();
}

// Function to add a flashcard
void addFlashcard(vector<Flashcard> &flashcards) {
    Flashcard newCard;
    cout << "Enter the question: ";
    getline(cin, newCard.question);
    cout << "Enter the answer: ";
    getline(cin, newCard.answer);
    
    flashcards.push_back(newCard);
    cout << "Flashcard added!\n";
}

// Function to quiz the user and track points
void quizUser(const vector<Flashcard> &flashcards, int &points) {
    if (flashcards.empty()) {
        cout << "No flashcards available! Add some first.\n";
        return;
    }

    for (const auto &card : flashcards) {
        string userAnswer;
        cout << "Question: " << card.question << endl;
        cout << "Your answer: ";
        getline(cin, userAnswer);

        if (userAnswer == card.answer) {
            cout << "Correct!\n";
            points++;  // Increase points for correct answer
        } else {
            cout << "Wrong. The correct answer is: " << card.answer << endl;
        }
    }
    cout << "Your current points: " << points << endl;
}

// Function to shuffle flashcards
void shuffleFlashcards(vector<Flashcard> &flashcards) {
    if (flashcards.empty()) {
        cout << "No flashcards available to shuffle!\n";
        return;
    }

    srand(time(0));  // Seed for randomness
    size_t n = flashcards.size();
    
    // Shuffle the flashcards manually using a for loop
    for (size_t i = 0; i < n; ++i) {
        // Generate a random index to swap with
        size_t randomIndex = i + rand() % (n - i);  // Random index in the remaining unshuffled portion

        // Swap the current element with the randomly selected one
        swap(flashcards[i], flashcards[randomIndex]);
    }

    cout << "Flashcards shuffled!\n";
}

// Function to display all flashcards
void displayAllFlashcards(const vector<Flashcard> &flashcards) {
    if (flashcards.empty()) {
        cout << "No flashcards available!\n";
        return;
    }
    cout << "\n--- All Flashcards ---\n";
    for (size_t i = 0; i < flashcards.size(); ++i) {
        cout << "Flashcard #" << i + 1 << "\n";
        cout << "Question: " << flashcards[i].question << endl;
        cout << "Answer: " << flashcards[i].answer << endl;
        cout << "-----------------------\n";
    }
}

// Function to delete a flashcard by index
void deleteFlashcard(vector<Flashcard> &flashcards) {
    if (flashcards.empty()) {
        cout << "No flashcards available to delete!\n";
        return;
    }

    displayAllFlashcards(flashcards);
    
    int index;
    cout << "Enter the number of the flashcard you want to delete: ";
    cin >> index;
    cin.ignore();

    if (index < 1 || index > flashcards.size()) {
        cout << "Invalid choice. Please enter a valid flashcard number.\n";
        return;
    }

    flashcards.erase(flashcards.begin() + index - 1);
    cout << "Flashcard deleted successfully.\n";
}

// Main Menu
int main() {
    string filename = "flashcards.txt";
    vector<Flashcard> flashcards = loadFlashcards(filename);
    int points = 0;  // Points start at zero

    int choice;
    do {
        cout << "\nFlashcard Program Menu:\n";
        cout << "1. Add Flashcard\n";
        cout << "2. Quiz Yourself\n";
        cout << "3. View All Flashcards\n";
        cout << "4. Delete a Flashcard\n";
        cout << "5. Shuffle Flashcards\n";
        cout << "6. Save and Exit\n";
        cout << "Your points: " << points << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addFlashcard(flashcards);
                break;
            case 2:
                quizUser(flashcards, points);
                break;
            case 3:
                displayAllFlashcards(flashcards);
                break;
            case 4:
                deleteFlashcard(flashcards);
                break;
            case 5:
                shuffleFlashcards(flashcards);
                break;
            case 6:
                saveFlashcards(flashcards, filename);
                cout << "Flashcards saved. Points reset to zero. Exiting...\n";
                points = 0;  // Reset points on exit
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
