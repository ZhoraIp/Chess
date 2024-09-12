#ifndef CHESS_HELPER_H
#define CHESS_HELPER_H
#include <vector>
std::vector<int> coordinates(std::string &move);
std::string to_move(std::vector<int> &coo);
void print_moves(std::vector<std::string> &moves);
void collision(int x, int y, std::string &from, std::vector<std::string> &moves, std::vector<std::string> &possible);
bool enter(std::string &move, const std::string &msg);
bool condition(std::vector<int> &coo);
void time_minutes(float time);

#endif //CHESS_HELPER_H