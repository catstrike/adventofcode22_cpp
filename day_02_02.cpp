#include <iostream>
#include <stdexcept>
#include <sstream>

const int SCORE_LOST = 0;
const int SCORE_DRAW = 3;
const int SCORE_WIN = 6;

int match_score(char opponent, char you)
{
    int opponent_decoded = opponent - 'A';

    if (opponent_decoded < 0 || opponent_decoded > 2) {
        throw new std::invalid_argument(std::string("Can't decode oponent's action ") + opponent);
    }

    switch (you) {
        case 'X': // you need to lose
            return SCORE_LOST + (opponent_decoded + 2) % 3 + 1;
        case 'Y': // end in a draw
            return SCORE_DRAW + opponent_decoded + 1;
        case 'Z': // you need to win
            return SCORE_WIN + (opponent_decoded + 1) % 3 + 1;
    }

    throw new std::invalid_argument(std::string("Can't decode expected outcome ") + you);
}

int main()
{
    int result {0};
    char opponent, recommended;

    while(std::cin >> opponent && std::cin >> recommended) {
        int score = match_score(opponent, recommended);

        result += score;
    }

    std::cout << result << std::endl;

    return 0;
}