#include "Pieces.h"
#include "../helper.h"
#include <iostream>
#include <vector>
using namespace std;

std::vector<std::string> Pawn::possible_moves(std::string &move) {
    vector <string> moves;
    vector <int> coo = coordinates(move), s(2);

    //cout << move << " " << to_move(coo) << endl;

    if(!this->GetColor()){
        if(coo[0] == 6){
            s[0] = coo[0]-2; s[1] = coo[1];
            if(condition(s)) moves.push_back(to_move(s));
            s[0] = coo[0]-1; s[1] = coo[1];
            if(condition(s)) moves.push_back(to_move(s));
            s[0] = coo[0]-1; s[1] = coo[1]-1;
            if(condition(s)) moves.push_back(to_move(s));
            s[0] = coo[0]-1; s[1] = coo[1]+1;
            if(condition(s)) moves.push_back(to_move(s));
        }
        else{
            s[0] = coo[0]-1; s[1] = coo[1];
            if(condition(s)) moves.push_back(to_move(s));
            s[0] = coo[0]-1; s[1] = coo[1]-1;
            if(condition(s)) moves.push_back(to_move(s));
            s[0] = coo[0]-1; s[1] = coo[1]+1;
            if(condition(s)) moves.push_back(to_move(s));
        }
    }
    else {
        if(coo[0] == 1){
            s[0] = coo[0]+2; s[1] = coo[1];
            if(condition(s)) moves.push_back(to_move(s));
            s[0] = coo[0]+1; s[1] = coo[1];
            if(condition(s)) moves.push_back(to_move(s));
            s[0] = coo[0]+1; s[1] = coo[1]-1;
            if(condition(s)) moves.push_back(to_move(s));
            s[0] = coo[0]+1; s[1] = coo[1]+1;
            if(condition(s)) moves.push_back(to_move(s));
        }
        else{
            s[0] = coo[0]+1; s[1] = coo[1];
            if(condition(s)) moves.push_back(to_move(s));
            s[0] = coo[0]+1; s[1] = coo[1]-1;
            if(condition(s)) moves.push_back(to_move(s));
            s[0] = coo[0]+1; s[1] = coo[1]+1;
            if(condition(s)) moves.push_back(to_move(s));
        }
    }
    return moves;
}

std::vector<std::string> King::possible_moves(std::string &move) {
    vector <string> moves;
    vector <int> coo = coordinates(move), s(2);
    s[0] = coo[0]+1; s[1] = coo[1];
    if(condition(s)) moves.push_back(to_move(s));
    s[0] = coo[0]+1; s[1] = coo[1]+1;
    if(condition(s)) moves.push_back(to_move(s));
    s[0] = coo[0]; s[1] = coo[1]+1;
    if(condition(s)) moves.push_back(to_move(s));
    s[0] = coo[0]-1; s[1] = coo[1];
    if(condition(s)) moves.push_back(to_move(s));
    s[0] = coo[0]-1; s[1] = coo[1]-1;
    if(condition(s)) moves.push_back(to_move(s));
    s[0] = coo[0]; s[1] = coo[1]-1;
    if(condition(s)) moves.push_back(to_move(s));
    s[0] = coo[0]+1; s[1] = coo[1]-1;
    if(condition(s)) moves.push_back(to_move(s));
    s[0] = coo[0]-1; s[1] = coo[1]+1;
    if(condition(s)) moves.push_back(to_move(s));
    return moves;
}

std::vector<std::string> Queen::possible_moves(std::string &move) {
    vector <string> moves;
    vector <int> coo = coordinates(move), s(2);
    for(int i = 1; i < 8; i++){
        s[0] = coo[0]+i; s[1] = coo[1];
        if(condition(s)) moves.push_back(to_move(s));
        s[0] = coo[0]+i; s[1] = coo[1]+i;
        if(condition(s)) moves.push_back(to_move(s));
        s[0] = coo[0]; s[1] = coo[1]+i;
        if(condition(s)) moves.push_back(to_move(s));
        s[0] = coo[0]-i; s[1] = coo[1];
        if(condition(s)) moves.push_back(to_move(s));
        s[0] = coo[0]-i; s[1] = coo[1]-i;
        if(condition(s)) moves.push_back(to_move(s));
        s[0] = coo[0]; s[1] = coo[1]-i;
        if(condition(s)) moves.push_back(to_move(s));
        s[0] = coo[0]+i; s[1] = coo[1]-i;
        if(condition(s)) moves.push_back(to_move(s));
        s[0] = coo[0]-i; s[1] = coo[1]+i;
        if(condition(s)) moves.push_back(to_move(s));
    }
    return moves;
}

std::vector<std::string> Bishop::possible_moves(std::string &move) {
    vector <string> moves;
    vector <int> coo = coordinates(move), s(2);
    for(int i = 1; i < 8; i++){
        s[0] = coo[0]+i; s[1] = coo[1]-i;
        if(condition(s)) moves.push_back(to_move(s));
        s[0] = coo[0]-i; s[1] = coo[1]+i;
        if(condition(s)) moves.push_back(to_move(s));
        s[0] = coo[0]+i; s[1] = coo[1]+i;
        if(condition(s)) moves.push_back(to_move(s));
        s[0] = coo[0]-i; s[1] = coo[1]-i;
        if(condition(s)) moves.push_back(to_move(s));
    }
    return moves;
}

std::vector<std::string> Knight::possible_moves(std::string &move) {
    vector <string> moves;
    vector <int> coo = coordinates(move), s(2);
    s[0] = coo[0]+2; s[1] = coo[1]+1;
    if(condition(s)) moves.push_back(to_move(s));
    s[0] = coo[0]+1; s[1] = coo[1]+2;
    if(condition(s)) moves.push_back(to_move(s));
    s[0] = coo[0]+2; s[1] = coo[1]-1;
    if(condition(s)) moves.push_back(to_move(s));
    s[0] = coo[0]-2; s[1] = coo[1]+1;
    if(condition(s)) moves.push_back(to_move(s));
    s[0] = coo[0]-2; s[1] = coo[1]-1;
    if(condition(s)) moves.push_back(to_move(s));
    s[0] = coo[0]-1; s[1] = coo[1]-2;
    if(condition(s)) moves.push_back(to_move(s));
    s[0] = coo[0]+1; s[1] = coo[1]-2;
    if(condition(s)) moves.push_back(to_move(s));
    s[0] = coo[0]-1; s[1] = coo[1]+2;
    if(condition(s)) moves.push_back(to_move(s));
    return moves;
}

std::vector<std::string> Rook::possible_moves(std::string &move) {
    vector <string> moves;
    vector <int> coo = coordinates(move), s(2);
    for(int i = 1; i < 8; i++){
        s[0] = coo[0]+i; s[1] = coo[1];
        if(condition(s)) moves.push_back(to_move(s));
        s[0] = coo[0]; s[1] = coo[1]+i;
        if(condition(s)) moves.push_back(to_move(s));
        s[0] = coo[0]-i; s[1] = coo[1];
        if(condition(s)) moves.push_back(to_move(s));
        s[0] = coo[0]; s[1] = coo[1]-i;
        if(condition(s)) moves.push_back(to_move(s));
    }
    return moves;
}
