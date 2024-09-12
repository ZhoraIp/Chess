#include <iostream>
#include "game.h"
#include "Vector/my_vector.h"
#include "gtest/gtest.h"
using namespace std;

TEST(Vector, con1) {
    Vector <int> v;
    EXPECT_EQ(v.capacity(), 0);
    EXPECT_EQ(v.size(), 0);
}

TEST(Vector, con2) {
    Vector <int> v(10);
    EXPECT_EQ(v.capacity(), 10);
    EXPECT_EQ(v.size(), 10);
}

TEST(Vector, con3) {
    Vector <string> v(10, "A");
    EXPECT_EQ(v.capacity(), 10);
    EXPECT_EQ(v.size(), 10);
    EXPECT_EQ(v[3], "A");
}

TEST(Vector, con4) {
    Vector< Vector <Piece*> > v{ {new Rook(1, "a8"), new Knight(1, "b8"), new Bishop(1, "c8"), new Queen(1, "d8"), new King(1, "e8"), new Bishop(1, "f8"), new Knight(1, "g8"), new Rook(1, "h8")},
                                 {new Pawn(1, "a7"), new Pawn(1, "b7"), new Pawn(1, "c7"), new Pawn(1, "d7"), new Pawn(1, "e7"), new Pawn(1, "f7"), new Pawn(1, "g7"), new Pawn(1, "h8")},
                                 {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                 {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                 {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                 {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                 {new Pawn(0, "a7"), new Pawn(0, "b7"), new Pawn(0, "c2"), new Pawn(0, "d2"), new Pawn(0, "e2"), new Pawn(0, "f2"), new Pawn(0, "g2"), new Pawn(0, "h2")},
                                 {new Rook(0, "a1"), new Knight(0, "b1"), new Bishop(0, "c1"), new Queen(0, "d1"), new King(0, "e1"), new Bishop(0, "f1"), new Knight(0, "g1"), new Rook(0, "h1")}
    };

//    for(int i = 0; i < 8; i++){
//        for(int j = 0; j < 8; j++){
//            if(v[i][j] != nullptr) cout << v[i][j]->GetN();
//        }
//        cout << endl;
//    }
    EXPECT_EQ(v.size(), 8);
    EXPECT_EQ(v[7][7]->GetN(), "Rook");

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            delete v[i][j];
        }
    }
}

TEST(Vector, size) {
    Vector <string> v(10, "A");
    EXPECT_EQ(v.size(), 10);
}

TEST(Vector, capacity) {
    Vector <string> v(10, "A");
    EXPECT_EQ(v.capacity(), 10);
}

TEST(Vector, reserve) {
    Vector <string> v;
    v.reserve(10);
    EXPECT_EQ(v.capacity(), 10);
    EXPECT_EQ(v.size(), 0);
}

TEST(Vector, resize) {
    Vector <string> v(10, "A");
    v.resize(20, "B");
    EXPECT_EQ(v.capacity(), 20);
    EXPECT_EQ(v.size(), 10);
    EXPECT_EQ(v[9], "A");
    EXPECT_EQ(v[15], "B");
}

TEST(Vector, push_back) {
    Vector <Piece*> v;
    v.push_back(new Rook(1, "a8"));
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0]->GetN(), "Rook");
    delete v[0];
}

TEST(Vector, pop_back) {
    Vector <int> v(10, 5);
    v.pop_back();

    EXPECT_EQ(v.size(), 9);
    EXPECT_EQ(v[1], 5);
}

TEST(Vector, operator_ind) {
    Vector <int> v;
    v.push_back(10);
    EXPECT_EQ(v[0], 10);
}

TEST(Vector, piece){
    Vector < Vector<Piece*> > v{ {new Rook(1, "a8"), new King(1, "a7"), nullptr},
                                 {new Rook(1, "a8"), new King(1, "a7"), new Pawn(1, "a7")}};
    EXPECT_EQ(v.size(), 2);
    Vector < Vector<Piece*> > p;
    p = v;
    cout << v.size() << " ";
    cout << v[0].size() << " " << v[1].size();

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 3; j++)
            if(v[i][j] != nullptr) {
                EXPECT_EQ(p[i][j]->GetN(), v[i][j]->GetN());
            }

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 3; j++)
            delete v[i][j];
}

TEST(Vector, operator_eq) {
    Vector< Vector <Piece*> > v{ {new Rook(1, "a8"), new Knight(1, "b8"), new Bishop(1, "c8"), new Queen(1, "d8"), new King(1, "e8"), new Bishop(1, "f8"), new Knight(1, "g8"), new Rook(1, "h8")},
                                 {new Pawn(1, "a7"), new Pawn(1, "b7"), new Pawn(1, "c7"), new Pawn(1, "d7"), new Pawn(1, "e7"), new Pawn(1, "f7"), new Pawn(1, "g7"), new Pawn(1, "h8")},
                                 {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                 {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                 {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                 {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                 {new Pawn(0, "a7"), new Pawn(0, "b7"), new Pawn(0, "c2"), new Pawn(0, "d2"), new Pawn(0, "e2"), new Pawn(0, "f2"), new Pawn(0, "g2"), new Pawn(0, "h2")},
                                 {new Rook(0, "a1"), new Knight(0, "b1"), new Bishop(0, "c1"), new Queen(0, "d1"), new King(0, "e1"), new Bishop(0, "f1"), new Knight(0, "g1"), new Rook(0, "h1")}
    };

    Vector< Vector<Piece*> > p;
    p = v;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(v[i][j] != nullptr){
                EXPECT_EQ(v[i][j]->GetN(), p[i][j]->GetN());
            }
        }
    }

    for(auto &i : v){
        for(auto &j : i){
            delete j;
        }
    }
}

TEST(Vector, begin) {
    Vector <int> v(10, 0);
    v[0] = 1;
    v[9] = 10;
    EXPECT_EQ(*v.begin(), 1);
}

TEST(Vector, end) {
    Vector <int> v(10, 0);
    v[0] = 1;
    v[9] = 10;
    Vector <int>::iterator it = v.end();
    --it;
    EXPECT_EQ(*it, 10);
}

TEST(Vector, incr_decr_pref){
    Vector <int> v(10, 0);
    v[1] = 1;
    v[9] = 10;
    Vector <int>::iterator it1 = v.end();
    Vector <int>::iterator it2 = v.begin();
    --it1;
    EXPECT_EQ(*(it1), 10);
    ++it2;
    EXPECT_EQ(*(it2), 1);
}

TEST(Vector, incr_decr_post){
    Vector <int> v(10, 0);
    v[1] = 1;
    v[9] = 10;
    Vector <int>::iterator it = v.begin();
    it++;
    EXPECT_EQ(*(it), 1);
}

TEST(Vector, empty) {
    Vector <int> v;
    EXPECT_EQ(v.empty(), true);
    v.push_back(10);
    EXPECT_EQ(v.empty(), false);
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}