#include <iostream>
#include <cstdlib>
#include <ctime>

int main() 
{
    //Arrays of all the foods (7 candidates)
    std::string lunches[7] = {
        "Pizza from Domino's",
        "Tofu Tikka Masala from Taste of India",
        "Crispy Salmon Bowl from Sushi Fuku",
        "Sub from Subway",
        "Fried Rice and Orange Chicken from Hunan",
        "Sandwiches from La Prima",
        "Chicken Spaghetti from Ciao Bella"
    };

    //Arrays of the days
    std::string days[7] = {
        "Sun","Mon","Tue","Wed","Thr","Fri","Sat"
    };

    srand(static_cast<unsigned int>(time(0)));

    //assigning food to days randomly
    for (int i=0; i<7; i++)
    {
        int rand_id = rand() % 7;
        std:: string temp = lunches[i];
        lunches[i] = lunches[rand_id];
        lunches[rand_id] = temp;
    }

    //displaying the array
    for (int i =0; i<7; i++)
    {
        std::cout << days[i] << "  " << lunches[i] << std::endl;
    }

    return 0;

}