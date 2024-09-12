#ifndef CHESS_VIEW_H
#define CHESS_VIEW_H
void print_board(std::vector<std::vector<Piece *>> pieces);
void print_history(History history);
void print_formal(History history);
void print_state(State state);
void print_verdict(Verdict verdict);
#endif //CHESS_VIEW_H
