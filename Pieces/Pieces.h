#ifndef CHESS_PIECES_H
#define CHESS_PIECES_H

#include <utility>
#include <iostream>
#include <vector>

/**
 * @brief Структура абстрактной фигуры
 */
struct Piece{
protected:
    //! Цвет фигуры
    int color{}; // black, white
    //! Название фигуры
    std::string name;
    //! Позиция фигуры на доске
    std::string position;
    //! Символ фигуры
    std::string c;
    //! Количество совершенных ходов фигурой
    int moves = 0;
public:
    /**
     * @brief Функция возможных ходов
     * @param move Позиция фигуры на доске
     * @return Все возможные ходы
     */
    virtual std::vector<std::string> possible_moves(std::string &move) = 0;
    virtual void check_move() = 0;
    /**
     * @brief Функция получения названия
     * @return Название фигуры
     */
    virtual std::string GetN() = 0;
    /**
     * @brief Функция получения символа фигуры
     * @return Печатается символ фигуры
     */
    virtual void GetC() = 0;
     /**
     * @brief Функция получения цвета фигуры
     * @return Цвет фигуры
     */
    virtual int GetColor() = 0;
    /**
     * @brief Функция увеличения количества ходов
     */
    virtual void increment() = 0;
    /**
     * @brief Функция получения сделанных фигурой ходов
     * @return Количество сделанных ходов
     */
    virtual int GetM() = 0;
    //virtual ~Piece() = default;
};

/**
 * @brief Структура короля
 */
struct King: public Piece{
public:
    /**
     * @brief Конструктор короля
     */
    King(int color, std::string position){
        name = "King";
        this->color = color;
        this->position = std::move(position);
        if(color == 1) c = "♚";
        else c = "♔";
    }
    std::vector<std::string> possible_moves(std::string &move) override;
    void check_move() override{}
    std::string GetN() override{
        return this->name;
    }
    void GetC() override{
        std::cout << this->c;
    }
    int GetColor() override{
        return this->color;
    }
    void increment() override{
        this->moves++;
    }
    int GetM() override{
        return this->moves;
    }
};

/**
 * @brief Структура королевы
 */
struct Queen: public Piece{
public:
    /**
     * @brief Конструктор королевы
     */
    Queen(int color, std::string position){
        name = "Queen";
        this->color = color;
        this->position = std::move(position);
        if(color == 1) c = "♛";
        else c = "♕";
    }
    std::vector<std::string> possible_moves(std::string &move) override;
    void check_move() override{}
    std::string GetN() override{
        return this->name;
    }
    void GetC() override{
        std::cout << this->c;
    }
    int GetColor() override{
        return this->color;
    }
    void increment() override{
        this->moves++;
    }
    int GetM() override{
        return this->moves;
    }
};

/**
 * @brief Структура слона
 */
struct Bishop: public Piece{
public:
    /**
     * @brief Конструктор слона
     */
    Bishop(int color, std::string position){
        name = "Bishop";
        this->color = color;
        this->position = std::move(position);
        if(color == 1) c = "♝";
        else c = "♗";
    }
    std::vector<std::string> possible_moves(std::string &move) override;
    void check_move() override{}
    std::string GetN() override{
        return this->name;
    }
    void GetC() override{
        std::cout << this->c;
    }
    int GetColor() override{
        return this->color;
    }
    void increment() override{
        this->moves++;
    }
    int GetM() override{
        return this->moves;
    }
};

/**
 * @brief Структура коня
 */
struct Knight: public Piece{
public:
    /**
     * @brief Конструктор коня
     */
    Knight(int color, std::string position){
        name = "Knight";
        this->color = color;
        this->position = std::move(position);
        if(color == 1) c = "♞";
        else c = "♘";
    }
    std::vector<std::string> possible_moves(std::string &move) override;
    void check_move() override{}
    std::string GetN() override{
        return this->name;
    }
    void GetC() override{
        std::cout << this->c;
    }
    int GetColor() override{
        return this->color;
    }
    void increment() override{
        this->moves++;
    }
    int GetM() override{
        return this->moves;
    }
};

/**
 * @brief Структура ладьи
 */
struct Rook: public Piece{
public:
    /**
     * @brief Конструктор ладьи
     */
    Rook(int color, std::string position){
        name = "Rook";
        this->color = color;
        this->position = std::move(position);
        if(color == 1) c = "♜";
        else c = "♖";
    }
    std::vector<std::string> possible_moves(std::string &move) override;
    void check_move() override{}
    std::string GetN() override{
        return this->name;
    }
    void GetC() override{
        std::cout << this->c;
    }
    int GetColor() override{
        return this->color;
    }
    void increment() override{
        this->moves++;
    }
    int GetM() override{
        return this->moves;
    }
};

/**
 * @brief Структура пешки
 */
struct Pawn: public Piece{
public:
    /**
     * @brief Конструктор пешки
     */
    Pawn(int color, std::string position){
        name = "Pawn";
        this->color = color;
        this->position = std::move(position);
        if(color == 1) c = "♟";
        else c = "♙";
    }
    std::vector<std::string> possible_moves(std::string &move) override;
    void check_move() override{}
    std::string GetN() override{
        return this->name;
    }
    void GetC() override{
        std::cout << this->c;
    }
    int GetColor() override{
        return this->color;
    }
    void increment() override{
        this->moves++;
    }
    int GetM() override{
        return this->moves;
    }
};

#endif //CHESS_PIECES_H
