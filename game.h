#ifndef CHESS_GAME_H
#define CHESS_GAME_H
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <string>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <memory>
#include "Pieces/Pieces.h"

class Clock{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    float time = 0;
    float addition = 0;
public:

    Clock() = default;

    void clock_start(){
        start = std::chrono::high_resolution_clock::now();
    }

    void clock_end(){
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        float a = duration.count();
        time -= duration.count();
        //std::cout << duration.count() << std::endl;
    }

    void Set_Time(float time) {
        this->time = time;
    }

    void Set_Addition(float addition) {
        this->addition = addition;
    }

    void add(){
        time += addition;
    }

    float Get_Time() const{
        float t = this->time;
        return t;
    }

};

enum State{
    //int state = 0; // 0 - no game, 1 - new game, 2 - now game, 3 - end game.
    No,
    New,
    Now,
    End
};

enum Verdict{
    // 0 - mate, 1 - stalemate, 2 - check, 3 - nothing
    Mate = 0,
    Stalemate = 1,
    Check = 2,
    Nothing = 3,
    Time
};

struct Player{
    int elo;
    std::string name;
    Clock clock;
};

struct History{
    int number = 0;
    std::vector <std::string> move;
    std::vector <std::string> formal;
};

class Game{
private:
    /*
     8  r k b q k b k r
     7  p p p p p p p p
     6  0 0 0 0 0 0 0 0
     5  0 0 0 0 0 0 0 0
     4  0 0 0 0 0 0 0 0
     3  0 0 0 0 0 0 0 0
     2  p p p p p p p p
     1  r k b q k b k r
        a b c d e f g h
     */
    int move = 0; //0, 1: white, black
    Player player[2]; // name + rating + clock
    float timing;
    History history; // game history
    State state = State::No;
    Verdict verdict;
    std::vector< std::vector <Piece*> > pieces;
public:
    Game(){
        std::vector< std::vector <Piece*> > v{ {new Rook(1, "a8"), new Knight(1, "b8"), new Bishop(1, "c8"), new Queen(1, "d8"), new King(1, "e8"), new Bishop(1, "f8"), new Knight(1, "g8"), new Rook(1, "h8")},
                                               {new Pawn(1, "a7"), new Pawn(1, "b7"), new Pawn(1, "c7"), new Pawn(1, "d7"), new Pawn(1, "e7"), new Pawn(1, "f7"), new Pawn(1, "g7"), new Pawn(1, "h8")},
                                               {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                               {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                               {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                               {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                               {new Pawn(0, "a7"), new Pawn(0, "b7"), new Pawn(0, "c2"), new Pawn(0, "d2"), new Pawn(0, "e2"), new Pawn(0, "f2"), new Pawn(0, "g2"), new Pawn(0, "h2")},
                                               {new Rook(0, "a1"), new Knight(0, "b1"), new Bishop(0, "c1"), new Queen(0, "d1"), new King(0, "e1"), new Bishop(0, "f1"), new Knight(0, "g1"), new Rook(0, "h1")}
                                                };
        pieces = v;
    }
    std::vector< std::vector <Piece*>> GetBoard();

    History GetHistory();

    State GetState();

    Verdict GetVerdict();

    void make_move();

    void check_moves(std::vector< std::vector <Piece*> > &pieces, std::vector<std::string> &moves, std::string &from, int move);

    void impossible_move(std::vector<std::string> &moves, std::string &from, int move);

    bool check(int color, std::vector< std::vector <Piece*> > &pieces);

    bool mate(int color, std::vector< std::vector <Piece*> > &pieces);

    std::string en_passant(std::vector< std::vector <Piece*> > &pieces, std::vector<std::string> &moves, std::string &from, int move);

    bool castling(std::vector< std::vector <Piece*> > &pieces, std::vector<std::string> &moves, std::string &from, int move);

    void pawn_revolution(std::vector <int> coo, std::vector <int> s);

    void set_time(float time);

    void set_addition(float addition);

    void new_game();


    ~Game(){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                delete pieces[i][j];
            }
        }
    }
};

#endif //CHESS_GAME_H
