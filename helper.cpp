#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

vector<int> coordinates(string &move){
    if (move.size() != 2) {
        exit;
    }
    vector <int> coo = {8-(move[1]-'0'), move[0]-97}; //x y
    return coo;
}

string to_move(vector<int> &coo){
    string move = "";
    move += (char)('a' + coo[1]);
    move += to_string(8-coo[0]);
    return move;
}

void print_moves(vector<string> &moves){
    cout << "Choose move" << endl;
    for(int i = 0; i < moves.size(); i++)
        cout << moves[i] << " ";
    cout << "NO" << endl;
}

void collision(int x, int y, string &from, vector<string> &moves, vector<string> &possible){
    vector <int> coo, s(2);
    string t;
    int l1 = 0, l2 = 0;
    coo = coordinates(from);

    if(x != 0) l1 = x/abs(x);
    else l1 = 0;
    if(y != 0) l2 = y/abs(y);
    else l2 = 0;

    for(int i = max(abs(y)+1, abs(x)+1); i < 8; i++){
        s[0] = coo[0]+i*l1, s[1] = coo[1]+i*l2;
        if(s[0] >= 0 && s[0] <= 7 && s[1] >= 0 && s[1] <= 7) {
            //cout << s[0] << ' ' << s[1] << endl;
            t = to_move(s);
            possible.push_back(t);
        }
    }
}

bool enter(string &move, const string &msg){
    while(true) {
        cout << msg;
        cin >> move;
        vector<int> coo;
        coo = coordinates(move);
        if(move == "end" || move == "END" || move == "End") return true;
        if(move.size() != 2) {
            cout << "Incoorrect input" << endl;
            continue;
        }
        else if(coo[0] <= 7 && coo[0] >= 0 && coo[1] <= 7 && coo[1] >= 0) break;
        else {
            cout << "Incoorrect input" << endl;
            continue;
        }
    }
    return false;
}

bool condition(vector <int> &coo){
    if(coo[0] >= 0 && coo[1] >= 0 && coo[0] <= 7 && coo[1] <= 7) return true;
    else return false;
}

void time_minutes(float time){
    int minutes = 0;
    float seconds = 0;
    if(time > 60){
        minutes = time / 60;
        seconds = time - minutes*60;
    }
    else seconds = time;

    cout << "Your time is: " << minutes << " minutes, " << (int)seconds << " seconds" <<std::endl;
}

