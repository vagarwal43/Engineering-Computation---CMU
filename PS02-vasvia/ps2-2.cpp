#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstdio>

// shuffling function
void shuffle(int n, std::vector<int> & array)   // taking integers and array
{
    for (int i=n; i>0; i--)
    {
        int rand_id = rand() % (i+1);
        std::swap(array[i], array[rand_id]);
    }
}

// Printing the cards
void displayCard(int x, int y) 
{
    std::cout << "+-----+" << std::endl;
    std::cout << "|     |" << std::endl;
    printf("|%2dx%2d|\n", x, y);
    std::cout << "|     |" << std::endl;
    std::cout << "+-----+" << std::endl;
    std::cout << "Enter Your Answer> ";

}

int main() 
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int n;
    std::vector<int> cards;

    for (int i= 1; i <=12; i++)
    {
        for (int j=1; j<=12; j++)
        {
            cards.push_back(100*i+j);
        }
    }

    // condition for getting the number of practices
    do 
    {
        std::cout << "Enter the number of flash cards to work on (1-144): ";
        std::cin >> n;
        if (n < 1 || n > 144) 
        {
            std::cout << "The number of cards must be between 1 and 144." << std::endl;
        }
    } while (n < 1 || n > 144);

    shuffle(144, cards);    //shuffling the cards

    int total_correct = 0;  //total number of correct answers
    int user_input;         //the answers entered by user
    time_t startTime = time(nullptr);

    for (int i=0; i <n; i++) 
    {
        int card = cards[i];
        int x = card / 100;
        int y = card %100;

        //displaying the cards randomly
        displayCard(x,y);
        std::cin >> user_input;

        // condition to see if the answers are correct
        if (user_input == x*y) 
        {
            std::cout << "Correct!" << std::endl;
            total_correct ++;
        } 
        else 
        {
            std::cout << "Incorrect! The correct answer is " << x * y << "." << std::endl;
        }
    }

    time_t endTime = time(nullptr);
    int timeTaken = static_cast<int>(endTime - startTime);
    double perc = 100.0 * total_correct / n;   // percentage of answers correct

    std::cout << "You answered " << n << " problems in " << timeTaken << " seconds. ";
    std::cout << "You answered " << total_correct << " problems correctly (" << perc << "%)." << std::endl;

    return 0;

}
