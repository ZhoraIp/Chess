#include <iostream>
#include <iomanip>
#include <ios>
#include <cmath>
#include "game.h"
#include "helper.h"

State Game::GetState(){
    return this->state;
}

std::vector<std::vector<Piece *>> Game::GetBoard() {
    return this->pieces;
}

History Game::GetHistory(){
    return this->history;
}

Verdict Game::GetVerdict(){
    return this->verdict;
}

void Game::new_game(){
    state = State::New;
    std::string s = "";
    std::cout << "Press Y if you ready" << std::endl;
    while (s != "Y")
        std::cin >> s;

    std::cout << "Set time(minutes)" << std::endl;
    std::cin >> s;
    this->set_time(std::stof(s)*60);
    std::cout << "Set addition(seconds)" << std::endl;
    std::cin >> s;
    this->set_addition(stof(s));
    state = State::Now;
}

void Game::set_time(float time) {
    player[0].clock.Set_Time(time);
    player[1].clock.Set_Time(time);
}

void Game::set_addition(float addition) {
    player[0].clock.Set_Addition(addition);
    player[1].clock.Set_Addition(addition);
}

void Game::check_moves(std::vector< std::vector <Piece*> > &pieces, std::vector<std::string> &moves, std::string &from, int move){
    std::vector<int> coo, cof;
    std::vector<std::string> possible;
    cof = coordinates(from);
    for(int i = 0; i < moves.size(); i++){
        coo = coordinates(moves[i]);
        if(pieces[coo[0]][coo[1]] != nullptr && pieces[cof[0]][cof[1]]->GetN() != "Pawn"){
            //if(pieces[cof[0]][cof[1]]->GetN() == "King" )
            if(move == pieces[coo[0]][coo[1]]->GetColor()) possible.push_back(moves[i]);
            int x = coo[0] - cof[0], y = coo[1] - cof[1];
            collision(x, y, from, moves, possible);
        }
        else if(pieces[cof[0]][cof[1]]->GetN() == "Pawn"){
            if(pieces[coo[0]][coo[1]] != nullptr && move == pieces[coo[0]][coo[1]]->GetColor()){
                possible.push_back(moves[i]);
            }
            else if(pieces[coo[0]][coo[1]] != nullptr && move != pieces[coo[0]][coo[1]]->GetColor()){
                int x = coo[0] - cof[0], y = coo[1] - cof[1];
                if(!(abs(x)*abs(y))) possible.push_back((moves[i]));
            }
            else if(pieces[coo[0]][coo[1]] == nullptr){
                int x = coo[0] - cof[0], y = coo[1] - cof[1];
                if((abs(x)*abs(y))) possible.push_back((moves[i]));
            }
        }
    }
    for(int i = 0; i < moves.size(); i++){
        for(int j = 0; j < possible.size(); j++){
            if(moves[i] == possible[j]){
                moves.erase(moves.begin()+i);
                i--;
                break;
            }
        }
    }
}

void Game::impossible_move(std::vector<std::string> &moves, std::string &from, int move){
    std::vector<int> cof = coordinates(from);
    for(int i = 0; i < moves.size(); i++){
        std::vector<std::vector<Piece *> > virtual_board = this->GetBoard();
        std::vector<int> coo = coordinates(moves[i]);
        virtual_board[coo[0]][coo[1]] = virtual_board[cof[0]][cof[1]];
        virtual_board[cof[0]][cof[1]] = nullptr;
        //print_board(virtual_board);
        if (this->check((move + 1) % 2, virtual_board)) {
            moves.erase(moves.begin() + i);
            i--;
        }
    }
}

std::string Game::en_passant(std::vector< std::vector <Piece*> > &pieces, std::vector<std::string> &moves, std::string &from, int move){
    std::vector<int> coo = coordinates(from);
    bool h = false;
    if(!history.number) return "";
    std::string s = history.move[history.number-1];
    std::string x = "  ";
    x[0] = s[2]; x[1] = s[3];
    std:std::vector<int> cof = coordinates(x);
    x = "";
    if(pieces[coo[0]][coo[1]] && pieces[coo[0]][coo[1]]->GetN() != "Pawn") return x;
    if(move){
        if(coo[0] != 4 || s[1] != '2' || s[3] != '4') return x;
        else if(pieces[cof[0]][cof[1]] == nullptr) return x;
        else if(pieces[cof[0]][cof[1]]->GetN() != "Pawn") return x;
        else if(abs(cof[1]-coo[1]) != 1) return x;
        else{
            cof[0]++;
            x = to_move(cof);
            moves.push_back(x);
            return x;
        }
    }
    else{
        if(coo[0] != 3 || s[1] != '7' || s[3] != '5') return x;
        else if(pieces[cof[0]][cof[1]]->GetN() != "Pawn") return x;
        else if(abs(cof[1]-coo[1]) != 1) return x;
        else{
            cof[0]--;
            x = to_move(cof);
            moves.push_back(x);
            return x;
        }
    }
}

bool Game::castling(std::vector< std::vector <Piece*> > &pieces, std::vector<std::string> &moves, std::string &from, int move){
    std::vector<int> coo = coordinates(from);
    std::vector <std::vector <Piece *>> board = pieces;
    bool h = false;
    if(pieces[coo[0]][coo[1]]->GetN() != "King" || pieces[coo[0]][coo[1]]->GetM()) return false;
    if(move){
        if(pieces[0][7] != nullptr && pieces[0][7]->GetM() == 0 && !pieces[0][6] && !pieces[0][5]){
            if(check((move+1)%2, board)) return false;
            //delete board[0][4];
            board[0][4] = nullptr;
            board[0][6] = new King(move, "g8");
            if(check((move+1)%2, board)){
                delete board[0][6];
                board[0][6] = nullptr;
                return false;
            }
            else{
                delete board[0][6];
                board[0][6] = nullptr;
            }
            board[0][6] = nullptr;
            board[0][5] = new King(move, "f8");
            if(check((move+1)%2, board)){
                delete board[0][5];
                board[0][5] = nullptr;
                return false;
            }
            else{
                delete board[0][5];
                board[0][5] = nullptr;
            }
            moves.push_back("g8");
            h = true;
        }
        board = pieces;
        if(pieces[0][0] != nullptr && pieces[0][0]->GetM() == 0 && !pieces[0][1] && !pieces[0][2] && !pieces[0][3]){
            if(check((move+1)%2, board)) return false;
            //delete board[0][4];
            board[0][4] = nullptr;
            board[0][2] = new King(move, "c8");
            if(check((move+1)%2, board)) {
                delete board[0][2];
                board[0][2] = nullptr;
                return false;
            }
            else{
                delete board[0][2];
                board[0][2] = nullptr;
            }
            board[0][2] = nullptr;
            board[0][3] = new King(move, "d8");
            if(check((move+1)%2, board)){
                delete board[0][3];
                board[0][3] = nullptr;
                return false;
            }
            else{
                delete board[0][3];
                board[0][3] = nullptr;
            }
            moves.push_back("c8");
            h = true;
        }
    }
    else{
        if(pieces[7][7] != nullptr && pieces[7][7]->GetM() == 0 && !pieces[7][6] && !pieces[7][5]){
            if(check((move+1)%2, board)) return false;
            //delete board[7][4];
            board[7][4] = nullptr;
            board[7][6] = new King(move, "g1");
            if(check((move+1)%2, board)){
                delete board[7][6];
                board[7][6] = nullptr;
                return false;
            }
            else{
                delete board[7][6];
                board[7][6] = nullptr;
            }
            board[7][6] = nullptr;
            board[7][5] = new King(move, "f1");
            if(check((move+1)%2, board)){
                delete board[7][5];
                board[7][5] = nullptr;
                return false;
            }
            else {
                delete board[7][5];
                board[7][5] = nullptr;
            }
            moves.push_back("g1");
            h = true;
        }
        board = pieces;
        if(pieces[7][0] != nullptr && pieces[7][0]->GetM() == 0 && !pieces[7][1] && !pieces[7][2] && !pieces[7][3]){
            if(check((move+1)%2, board)) return false;
            //delete board[7][4];
            board[7][4] = nullptr;
            board[7][2] = new King(move, "c1");
            if(check((move+1)%2, board)){
                delete board[7][2];
                board[7][2] = nullptr;
                return false;
            }
            else{
                delete board[7][2];
                board[7][2] = nullptr;
            }
            board[7][2] = nullptr;
            board[7][3] = new King(move, "d1");
            if(check((move+1)%2, board)){
                delete board[7][3];
                board[7][3] = nullptr;
                return false;
            }
            else{
                delete board[7][3];
                board[7][3] = nullptr;
            }
            moves.push_back("c1");
            h = true;
        }
    }
    return h;
}

void Game::pawn_revolution(std::vector <int> coo, std::vector <int> s){
    std::string v;
    if(this->pieces[coo[0]][coo[1]]->GetColor() && s[0] == 7){
        delete this->pieces[coo[0]][coo[1]];
        std::cout << "Select piece:\n"
                     "1.Queen\n"
                     "2.Rook\n"
                     "3.Bishop\n"
                     "4.Knight\n";
        std::cin >> v;
        if(v == "1") this->pieces[coo[0]][coo[1]] = new Queen(1, to_move(s));
        else if(v == "2") this->pieces[coo[0]][coo[1]] = new Rook(1, to_move(s));
        else if(v == "3") this->pieces[coo[0]][coo[1]] = new Bishop(1, to_move(s));
        else if(v == "4") this->pieces[coo[0]][coo[1]] = new Knight(1, to_move(s));
        else this->pieces[coo[0]][coo[1]] = new Queen(1, to_move(s));
    }
    else if(this->pieces[coo[0]][coo[1]]->GetColor() == 0 && s[0] == 0){
        delete this->pieces[coo[0]][coo[1]];
        std::cout << "Select piece:\n"
                     "1.Queen\n"
                     "2.Rook\n"
                     "3.Bishop\n"
                     "4.Knight\n";
        std::cin >> v;
        if(v == "1") this->pieces[coo[0]][coo[1]] = new Queen(0, to_move(s));
        else if(v == "2") this->pieces[coo[0]][coo[1]] = new Rook(0, to_move(s));
        else if(v == "3") this->pieces[coo[0]][coo[1]] = new Bishop(0, to_move(s));
        else if(v == "4") this->pieces[coo[0]][coo[1]] = new Knight(0, to_move(s));
        else this->pieces[coo[0]][coo[1]] = new Queen(0, to_move(s));
    }
}

void Game::make_move(){
    bool h = true, castle = false, special = false;
    std::string formal = "";
    std::string en_pass;
    std::string from, to;
    bool ff = false;
    this->player[this->move].clock.clock_start();
    if(!this->move) std::cout << std::endl << "White to move" << std::endl;
    else std::cout << std::endl << "Black to move" << std::endl;

    while(h) {
        ff = enter(from, "Choose cell, example: e2. Or (end) to surrender\n");
        if(ff){
            if(this->move) std::cout << "White wins" << std::endl;
            else std::cout << "Black wins" << std::endl;
            state = State::End;
            return;
        }
        std::vector<int> coo = coordinates(from);
        std::vector <std::string> moves;
        if(this->pieces[coo[0]][coo[1]] == nullptr) {
            std::cout << "There is no piece" << std::endl;
            continue;
        }
        if(this->pieces[coo[0]][coo[1]]->GetColor() != this->move) {
            std::cout << "You can't move this piece" << std::endl;
            continue;
        }
        moves = this->pieces[coo[0]][coo[1]]->possible_moves(from);
        check_moves(this->pieces, moves, from, this->move);
        impossible_move(moves, from, this->move);
        castle = castling(this->pieces, moves, from, this->move);
        en_pass = en_passant(this->pieces, moves, from, this->move);
        print_moves(moves);
        std::cin >> to;
        for(int i = 0; i < moves.size(); i++){
            if(to == moves[i]){
                if(this->pieces[coo[0]][coo[1]]->GetN() == "Pawn"){
                    std::vector<int> s = coordinates(to);
                    pawn_revolution(coo, s);
                }
                h = false;
                break;
            }
            else h = true;
        }
    }

    this->player[this->move].clock.clock_end();
    this->player[this->move].clock.add();

    float t = this->player[this->move].clock.Get_Time();
    if(t < 0) {
        this->verdict = Verdict::Time;
        this->state = State::End;
        if(this->move) std::cout << "White wins" << std::endl;
        else std::cout << "Black wins" << std::endl;
        return;
    }
    time_minutes(t);

    std::vector <int> coo1 = coordinates(from);
    std::vector <int> coo2 = coordinates(to);

    //std::vector<std::string> a = this->pieces[coo1[0]][coo1[1]]->possible_moves(from);

    if(castle){
        if(to == "g8"){
            pieces[0][5] = pieces[0][7];
            pieces[0][5]->increment();
            pieces[0][7] = nullptr;
            special = true;
            history.formal.push_back("0-0");
        }
        else if(to == "c8"){
            pieces[0][3] = pieces[0][0];
            pieces[0][3]->increment();
            pieces[0][0] = nullptr;
            special = true;
            history.formal.push_back("0-0-0");
        }
        else if(to == "g1"){
            pieces[7][5] = pieces[7][7];
            pieces[7][5]->increment();
            pieces[7][7] = nullptr;
            special = true;
            history.formal.push_back("0-0");
        }
        else if(to == "c1"){
            pieces[7][3] = pieces[7][0];
            pieces[7][3]->increment();
            pieces[7][0] = nullptr;
            special = true;
            history.formal.push_back("0-0-0");
        }
    }
    else if(!en_pass.empty()){
        if(to == en_pass){
            std::vector <int> xy = coordinates(en_pass);
            if(this->move){
                delete pieces[xy[0]-1][xy[1]];
                pieces[xy[0]-1][xy[1]] = nullptr;
            }
            else {
                delete pieces[xy[0] + 1][xy[1]];
                pieces[xy[0] + 1][xy[1]] = nullptr;
            }
            special = true;
            history.formal.push_back(from+"x"+to+" e.p");
        }
    }
    if(!special && this->pieces[coo2[0]][coo2[1]] != nullptr){
        if(this->pieces[coo1[0]][coo1[1]]->GetN()[0] == 'P') formal += from+"x"+to;
        else formal += this->pieces[coo1[0]][coo1[1]]->GetN()[0]+from+"x"+to;
    }
    else if(!special && this->pieces[coo2[0]][coo2[1]] == nullptr){
        if(this->pieces[coo1[0]][coo1[1]]->GetN()[0] == 'P') formal += from+"—"+to;
        else formal += this->pieces[coo1[0]][coo1[1]]->GetN()[0]+from+"—"+to;
    }
    delete this->pieces[coo2[0]][coo2[1]];
    this->pieces[coo2[0]][coo2[1]] = this->pieces[coo1[0]][coo1[1]];
    this->pieces[coo2[0]][coo2[1]]->increment();
    this->pieces[coo1[0]][coo1[1]] = nullptr;

    if(this->check(this->move, this->pieces)){
        this->verdict = Verdict::Check;
        if(this->mate((this->move + 1) % 2, this->pieces)){
            this->verdict = Verdict::Mate;
            this->state = State::End;
            formal += "#";
            if(this->move) std::cout << "Black wins" << std::endl;
            else std::cout << "White wins" << std::endl;
        }
        else formal += "+";
    }
    else this->verdict = Verdict::Nothing;

    if(!special) history.formal.push_back(formal);
    history.move.push_back(from+to);
    history.number++;

    this->move = (this->move + 1) % 2;
}

bool Game::check(int color,  std::vector< std::vector <Piece*> > &pieces){
    std::string king;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            std::vector<int> coo = {i, j};
            if(pieces[i][j] != nullptr && pieces[i][j]->GetN() == "King"){
                if(pieces[i][j]->GetColor() != color) king = to_move(coo);
            }
        }
    }
    std::vector <std::vector <bool> > moves_c(8, std::vector <bool> (8, false));
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            std::vector<int> coo = {i, j};
            std::string piece = to_move(coo);
            std::vector <std::string> moves;
            if(pieces[coo[0]][coo[1]] == nullptr)
                continue;
            if(pieces[coo[0]][coo[1]]->GetColor() != color)
                continue;
            if(pieces[coo[0]][coo[1]]->GetN() == "Pawn"){
                std::vector<int> s(2);
                if(pieces[coo[0]][coo[1]]->GetColor()) {
                    s[0] = coo[0] + 1;
                    s[1] = coo[1] - 1;
                    if (condition(s)) moves.push_back(to_move(s));
                    s[0] = coo[0] + 1;
                    s[1] = coo[1] + 1;
                    if (condition(s)) moves.push_back(to_move(s));
                }
                else{
                    s[0] = coo[0] - 1;
                    s[1] = coo[1] - 1;
                    if (condition(s)) moves.push_back(to_move(s));
                    s[0] = coo[0] - 1;
                    s[1] = coo[1] + 1;
                    if (condition(s)) moves.push_back(to_move(s));
                }
            }
            else moves = pieces[coo[0]][coo[1]]->possible_moves(piece);
            check_moves(pieces, moves, piece, color);
            for(int k = 0; k < moves.size(); k++){
                std::vector<int> cof = coordinates(moves[k]);
                if(pieces[i][j]->GetColor() == color)
                    moves_c[cof[0]][cof[1]] = true;
            }
        }
    }

    if(moves_c[coordinates(king)[0]][coordinates(king)[1]]) return true;

    return false;
}

bool Game::mate(int color, std::vector< std::vector <Piece*> > &pieces){
    for(int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::vector<int> coo = {i, j};
            std::string piece = to_move(coo);
            std::vector<std::string> moves;
            if(pieces[coo[0]][coo[1]] == nullptr)
                continue;
            if(pieces[coo[0]][coo[1]]->GetColor() != color)
                continue;
            moves = pieces[coo[0]][coo[1]]->possible_moves(piece);
            check_moves(pieces, moves, piece, color);
            impossible_move(moves, piece, color);
            if(!moves.empty()) return false;
        }
    }
    return true;
}
