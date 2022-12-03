#include <iostream>
#include <stdexcept>

const int SCORE_LOST = 0;
const int SCORE_DRAW = 3;
const int SCORE_WIN = 6;

int match_score(char opponent, char you)
{
    int opponent_decoded = opponent - 'A';
    int you_decoded = you - 'X';

    if (opponent_decoded < 0 || opponent_decoded > 2) {
        throw new std::invalid_argument(std::string("Can't decode oponent's action ") + opponent);
    }

    if (you_decoded < 0 || you_decoded > 2) {
        throw new std::invalid_argument(std::string("Can't decode your action ") + you);
    }

    if (opponent_decoded == you_decoded) {
        return you_decoded + 1 + SCORE_DRAW; 
    }

    int to_win = (opponent_decoded + 1) % 3;

    return (you_decoded == to_win ? SCORE_WIN : SCORE_LOST) + you_decoded + 1;
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