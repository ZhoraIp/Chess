#include <iostream>
#include "game.h"
#include "view/view.h"
#include <unistd.h>
using namespace std;

bool dialog(){
    bool h = false;
    string s;
    Game g;
    g.new_game();
    print_board(g.GetBoard());

    while(g.GetState() == State::Now){
        g.make_move();
        print_board(g.GetBoard());
        print_state(g.GetState());
        print_verdict(g.GetVerdict());
    }

    //print_history(g.GetHistory());
    print_formal(g.GetHistory());

    cout << "New game? (Y/N)" << endl;
    cin >> s;
    if(s == "Y" || s == "Yes" || s == "YES" || s == "yes") return true;
    else return false;
}

int main() {
    bool h = true;
    while(h){
        h = dialog();
    }
}
