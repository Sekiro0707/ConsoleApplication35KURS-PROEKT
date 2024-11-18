#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class Game {
private:
    const int SIZE = 3;
    vector<vector<T>> board;
    int x1 = 0;
    int o1 = 0;
    int n1 = 0;

    void reset_board() {
        char counter = '1';
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                board[i][j] = counter++;
            }
        }
    }

public:
    Game() {
        board.resize(SIZE, vector<T>(SIZE));
        reset_board();
    }

    void print_board() const {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                cout << board[i][j];
                if (j < SIZE - 1) cout << " | ";
            }
            cout << endl;
            if (i < SIZE - 1) cout << "--|---|--" << endl;
        }
        cout << endl;
    }

    bool is_win(T player) const {
        for (int i = 0; i < SIZE; ++i) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
        }
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
        return false;
    }

    bool is_draw() const {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] != 'X' && board[i][j] != 'O') return false;
            }
        }
        return true;
    }

    void make_move(T player) {
        int post;
        while (true) {
            try {
                cout << "Игрок " << player << ", выберите позицию (1-9): ";
                cin >> post;

                if (!cin) {
                    throw std::invalid_argument("Ошибка ввода: введите число!");
                }

                if (post < 1 || post > 9) {
                    throw std::out_of_range("Ошибка: Позиция должна быть в диапазоне от 1 до 9!");
                }

                int row = (post - 1) / SIZE;
                int col = (post - 1) % SIZE;

                if (board[row][col] == 'X' || board[row][col] == 'O') {
                    throw std::runtime_error("Эта позиция уже занята, выберите другую!");
                }

                board[row][col] = player;
                break;
            }
            catch (const std::invalid_argument& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            catch (const std::out_of_range& e) {
                cout << e.what() << endl;
            }
            catch (const std::runtime_error& e) {
                cout << e.what() << endl;
            }
        }
    }

    void computer_move() {
        int row, col;
        while (true) {
            row = rand() % SIZE;
            col = rand() % SIZE;
            if (board[row][col] != 'X' && board[row][col] != 'O') {
                board[row][col] = 'O';
                break;
            }
        }
        cout << "Компьютер сделал ход!" << endl;
    }

    void play_game(bool single_player) {
        T curst = 'X';
        while (true) {
            print_board();  // Просто печатаем доску, без очистки экрана
            if (single_player && curst == 'O') {
                computer_move();
            }
            else {
                make_move(curst);
            }

            if (is_win(curst)) {
                print_board();
                cout << "Игрок " << curst << " победил!!!" << endl;
                if (curst == 'X') {
                    x1++;
                }
                else {
                    o1++;
                }
                break;
            }

            if (is_draw()) {
                print_board();
                cout << "Ничья!" << endl;
                n1++;
                break;
            }

            curst = (curst == 'X') ? 'O' : 'X';
        }
        reset_board();
    }

    void print_stats() const {
        cout << "\n=== Статистика ===\n";
        cout << "Победы игрока X: " << x1 << endl;
        cout << "Победы игрока O: " << o1 << endl;
        cout << "Ничьи: " << n1 << endl;
        cout << "===================" << endl;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));
    setlocale(LC_ALL, "Russian");
    Game<char> game;

    while (true) {
        try {
            cout << "Выберите режим игры:\n1. Один игрок\n2. Два игрока\n3. Показать статистику\n4. Выход\nВаш выбор: ";
            int ch1;
            cin >> ch1;

            if (!cin) {
                throw std::invalid_argument("Ошибка ввода: введите число!");
            }

            if (ch1 == 1) {
                game.play_game(true);
            }
            else if (ch1 == 2) {
                game.play_game(false);
            }
            else if (ch1 == 3) {
                game.print_stats();
            }
            else if (ch1 == 4) {
                cout << "Спасибо за игру!" << endl;
                break;
            }
            else {
                throw std::out_of_range("Ошибка: Неверный выбор!");
            }
        }
        catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (const std::out_of_range& e) {
            cerr << e.what() << endl;
        }
    }

    return 0;
}
