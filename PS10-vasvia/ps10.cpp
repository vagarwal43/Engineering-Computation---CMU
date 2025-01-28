#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class BowlingGame {
private:
    std::vector<int> rolls;

public:
    BowlingGame(const std::string &notation) {
        parseGame(notation);
    }

    int scoreFromFrame() {
        int score = 0;
        int roll_ind = 0;

        for (int frame = 0; frame < 10; ++frame) {
            //Last Frame
            if (frame == 9) {
                score = score + rolls[roll_ind]+rolls[roll_ind+1]+rolls[roll_ind+2];
                break;
            }
            //Strike
            else if (rolls[roll_ind] == 10) {
                score = score + 10;
                if (rolls[roll_ind+2] == 10) {
                    score = score + 10 + rolls[roll_ind+4];
                }
                else {
                    score = score + rolls[roll_ind+2] + rolls[roll_ind+3];
                }
                roll_ind +=2;
            }
            //Spare
            else if (rolls[roll_ind]+rolls[roll_ind+1] == 10) {
                score = score + 10 + rolls[roll_ind+2];
                roll_ind += 2;

            }
            //All others
            else {
                score = score + rolls[roll_ind]+ rolls[roll_ind+1];
                roll_ind+=2;
            } 
        }
        return score;
    }

    private:
    void parseGame(const std::string &notation) {
        // check for the validity of the notation
        if (notation.size() < 21) {
            throw std::invalid_argument("Invalid notation: Too short");
        }
        for (char c : notation) {
            if (c == 'X') { // Strike
                rolls.push_back(10);
            } else if (c == '/') { // Spare
                rolls.push_back(10 - rolls.back());
            } else if (c == '-' || c == ' ') { // Miss
                rolls.push_back(0);
            } else if (c >= '0' && c <= '9') { // Number of pins knocked down
                rolls.push_back(c - '0');
            }
            else {
                throw std::invalid_argument("Invalid notation: Wrong character");
            }
        }
    }
};

    int main() {
        std:: string gameString;
        std::cout << "Enter the bowling scores notation: ";
        std::getline(std::cin, gameString);

        try {
        BowlingGame bowl(gameString);
        int finalScore = bowl.scoreFromFrame();
        std::cout << "Final Score: " << finalScore << std::endl;
        }
        catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        return 0;
    }
