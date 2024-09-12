#include <iostream>
#include <iomanip>
#include <ios>
#include "../helper.h"
#include "../Pieces/Pieces.h"
#include "../game.h"
using namespace std;

void print_board(vector<std::vector<Piece *>> pieces) {

    for(int i = 0; i < 8; i++) {
        cout << 8-i << "| ";
        for(int j = 0; j < 8; j++){
            if(!pieces[i][j]) cout << setw(6) << "☠" << right << "";
            else{
                cout << setw(6) << right;
                pieces[i][j]->GetC();
            }
        }
        cout << endl;
    }
    std::cout << "――――――――――――――――――――――――――――――";

    std::cout << std::endl;
    for(int i = 0; i < 8; i++){
        std::cout << std::setw(5) << std::internal;
        std::cout << (char)((int)'a' + i);
    }
    std::cout << std::endl;
}

void print_history(History history){
    for(int i = 0; i < history.number; i++){
        std::cout << (i+1) << ". " << history.move[i] << std::endl;
    }
}

void print_formal(History history){
    for(int i = 0; i < history.number; i+=2){
        std::cout << (i/2+1) << ". " << history.formal[i] << " ";
        if(i+1 <= history.number) std::cout << history.formal[i+1] << std::endl;
    }
}

void print_state(State state){
    switch (state) {
        case State::Now:
            cout << "Now" << endl;
            break;
        case State::New:
            cout << "New" << endl;
            break;
        case State::No:
            cout << "No" << endl;
            break;
        case State::End:
            cout << "End" << endl;
            break;
        default:
            break;
    }
}

void print_verdict(Verdict verdict){
    switch (verdict) {
        case Verdict::Mate:
            cout << "Mate" << endl;
            break;
        case Verdict::Stalemate:
            cout << "Stalemate" << endl;
            break;
        case Verdict::Check:
            cout << "Check" << endl;
            break;
        case Verdict::Nothing:
            cout << "Nothing" << endl;
            break;
        case Verdict::Time:
            cout << "Time" << endl;
            break;
        default:
            break;
    }
}