#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>

char box[8][4]{};
char temp_box1[8][4]{};
char temp_box2[8][4]{};
char temp_box3[8][4]{};

const unsigned short int max_length{20};
char player_name[max_length]{"JOHN"};

unsigned short int play_mode{3};
unsigned short int choice[2]{};
unsigned short int y[4];
unsigned short int x[4];
bool moved_by_knock{false};
unsigned short int temp_y[20]{};
unsigned short int temp_x[20]{};
unsigned short int y1_store[20]{};
unsigned short int x1_store[20]{};

void reset_board();
void print_board();

void player();
bool choice_processing(int index);
bool select_piece_player();
bool move_piece_player();
bool more_knocks();

void computer();
bool knocks_checking(int *total_knocks);
unsigned short int total_compMoves();
unsigned short int total_unknock_moves();
void select_piece_comp();
void move_piece_comp(char knock);
void best_move();
bool triple_play(int *);
bool players_knock();
int maxKnocks_comp();
bool future_more_knocks();
int maxKnocks_player();
bool playersKnock_remove();
bool playersKnock_block();
bool knock_antidote();

int main()
{
    srand(time(0));
    /*
    bool end{true};
    bool winner{false};

    std::cout << '\n';
    std::cout << "        Enter your name dear: ";

    char temp_name[max_length]{};
    std::cin.getline(temp_name, max_length);

    for (short int i{}; i < std::size(temp_name); ++i)
    {
        if (temp_name[i] == ' ')
        {
            break;
        }
        temp_name[i] = std::toupper(temp_name[i]);
        player_name[i] = temp_name[i];
    }

    std::cout << std::endl;
    std::cout << "                       ID  |  MODE" << std::endl;
    std::cout << "                    -------|--------------" << std::endl;
    std::cout << "                        1  |  Easy" << std::endl;
    std::cout << "                        2  |  Intermediate" << std::endl;
    std::cout << "                        3  |  Normal" << std::endl;
    std::cout << "                    -------|--------------" << std::endl;
    std::cout << std::endl;

    while (play_mode != 1 && play_mode != 2 && play_mode != 3)
    {
        std::cout << "                    Enter mode ID: ";
        if (!(std::cin >> play_mode))
        {
            std::cout << "                Invalid input! Try again!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::cout << '\n';*/
    reset_board();

    for (short int i = 0; i < 1; i++)
    {
        computer();
        player();
    }

    std::cout << "\n        PROGRAM ENDS WELL" << std::endl;
    return 0;
}

void reset_board()
{
    for (short int s = 0; s < 8; s++)
    {
        for (short int t = 0; t < 4; t++)
        {
            box[s][t] = ' ';
            temp_box1[s][t] = ' ';
            temp_box2[s][t] = ' ';
            temp_box3[s][t] = ' ';
        }
    }

    // player
    for (short int s = 0; s < 3; s++)
    {
        for (short int t = 0; t < 4; t++)
        {
            box[s][t] = ' ';
        }
    }

    // comp
    for (short int s = 5; s <= 7; s++)
    {
        for (short int t = 0; t < 4; t++)
        {
            box[s][t] = ' ';
        }
    }

    box[1][2] = 'o';
    box[1][3] = 'o';
    box[2][3] = 'X';
    box[4][0] = 'O';
    box[4][1] = 'x';
    box[4][2] = 'x';
    box[5][1] = 'o';
    box[6][1] = 'x';
    box[6][2] = 'x';
    box[7][0] = 'O';

    y[0] = 1;
    y[1] = 0;
    x[0] = 2;
    x[1] = 2;
}

void print_board()
{
    std::cout << '\n';
    std::cout << "              1   2   3   4   5   6   7   8  " << std::endl;
    std::cout << '\n';
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        8   | " << box[7][0] << " |   | " << box[7][1] << " |   | " << box[7][2] << " |   | " << box[7][3] << " |   |   8" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        7   |   | " << box[6][0] << " |   | " << box[6][1] << " |   | " << box[6][2] << " |   | " << box[6][3] << " |   7" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        6   | " << box[5][0] << " |   | " << box[5][1] << " |   | " << box[5][2] << " |   | " << box[5][3] << " |   |   6" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        5   |   | " << box[4][0] << " |   | " << box[4][1] << " |   | " << box[4][2] << " |   | " << box[4][3] << " |   5" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        4   | " << box[3][0] << " |   | " << box[3][1] << " |   | " << box[3][2] << " |   | " << box[3][3] << " |   |   4" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        3   |   | " << box[2][0] << " |   | " << box[2][1] << " |   | " << box[2][2] << " |   | " << box[2][3] << " |   3" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        2   | " << box[1][0] << " |   | " << box[1][1] << " |   | " << box[1][2] << " |   | " << box[1][3] << " |   |   2" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        1   |   | " << box[0][0] << " |   | " << box[0][1] << " |   | " << box[0][2] << " |   | " << box[0][3] << " |   1" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "              1   2   3   4   5   6   7   8  " << std::endl;
    std::cout << "" << std::endl;
}

void player()
{
    std::cout << "        =========================================" << std::endl;
    std::cout << "                       YOUR TURN" << std::endl;
    std::cout << "        =========================================" << std::endl;
    std::cout << '\n';

    // removing '.'
    for (short int i = 0; i < 8; i++)
    {
        for (short int j = 0; j < 4; j++)
        {
            if (box[i][j] == '.')
            {
                box[i][j] = ' ';
            }
        }
    }

    bool moved{false};
    bool knock_available{false};
    bool selected{false};
    bool invalid_input{false};

    do
    {
        do
        {
            std::cout << "           Enter piece row# column# e.g 32: ";

            if (!(std::cin >> choice[0]))
            {
                print_board();
                std::cout << "           Invalid input! Try again!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                invalid_input = choice_processing(0);
                if (invalid_input)
                {
                    print_board();
                    std::cout << "           Invalid input! Try again!" << std::endl;
                }
            }

        } while (invalid_input);

        selected = select_piece_player();

        if (!selected)
        {
            print_board();
            std::cout << "           Invalid piece entry! Try again!" << std::endl;
        }

    } while (!selected);

    print_board();
    std::cout << "        -----------------------------------------" << std::endl;
    std::cout << "           SELECTED " << player_name << std::endl;
    std::cout << "        -----------------------------------------" << std::endl;

    while (!moved)
    {
        do
        {
            std::cout << "           Enter target row# column# e.g 43: ";

            if (!(std::cin >> choice[1]))
            {
                print_board();
                std::cout << "           Invalid input! Try again!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                invalid_input = choice_processing(1);
                if (invalid_input)
                {
                    print_board();
                    std::cout << "           Invalid input! Try again!" << std::endl;
                }
            }

        } while (invalid_input);

        moved = move_piece_player();
        if (!moved)
        {
            print_board();
            std::cout << "           Invalid input! Try again!" << std::endl;
        }
    }

    while ((knock_available = more_knocks()) && moved_by_knock)
    {
        if (box[y[1]][x[1]] == 'X')
        {
            box[y[1]][x[1]] = 'S';
        }
        else if (box[y[1]][x[1]] == 'x')
        {
            box[y[1]][x[1]] = 's';
        }

        y[0] = y[1];
        x[0] = x[1];

        print_board();
        std::cout << "        -----------------------------------------" << std::endl;
        std::cout << "               CONSECUTIVE KNOCK AVAILABLE " << std::endl;
        std::cout << "        -----------------------------------------" << std::endl;

        do
        {
            do
            {
                std::cout << "           Enter target row# column# e.g 54: ";

                if (!(std::cin >> choice[1]))
                {
                    std::cout << "           Invalid input! Try again!" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    print_board();
                }

                else
                {
                    invalid_input = choice_processing(1);
                    if (invalid_input)
                    {
                        std::cout << "           Invalid input! Try again!" << std::endl;
                        print_board();
                    }
                }

            } while (invalid_input);

            moved = move_piece_player();
            if (!moved)
            {
                std::cout << "           Invalid input! Try again!" << std::endl;
                print_board();
            }

        } while (!moved);
    }

    print_board();
    std::cout << "        MOVED " << player_name << "." << std::endl;
    std::cout << std::endl;
}

bool choice_processing(int index)
{
    bool invalid_choice{true};

    if (choice[index] == 11 || choice[index] == 13 || choice[index] == 15 || choice[index] == 17 || choice[index] == 22 || choice[index] == 24 || choice[index] == 26 || choice[index] == 28 || choice[index] == 31 || choice[index] == 33 || choice[index] == 35 || choice[index] == 37 || choice[index] == 42 || choice[index] == 44 || choice[index] == 46 || choice[index] == 48)
    {
        invalid_choice = true;
    }
    else if (choice[index] == 51 || choice[index] == 53 || choice[index] == 55 || choice[index] == 57 || choice[index] == 62 || choice[index] == 64 || choice[index] == 66 || choice[index] == 68 || choice[index] == 71 || choice[index] == 73 || choice[index] == 75 || choice[index] == 77 || choice[index] == 82 || choice[index] == 84 || choice[index] == 86 || choice[index] == 88)
    {
        invalid_choice = true;
    }
    else if (choice[index] >= 12 && choice[index] <= 87)
    {
        y[index] = choice[index] / 10;
        x[index] = choice[index] % 10;

        if (y[index] == 8 || y[index] == 6 || y[index] == 4 || y[index] == 2)
        {
            if (x[index] == 1)
            {
                x[index] = 0;
            }
            else if (x[index] == 3)
            {
                x[index] = 1;
            }
            else if (x[index] == 5)
            {
                x[index] = 2;
            }
            else if (x[index] == 7)
            {
                x[index] = 3;
            }
            y[index] = y[index] - 1;
            invalid_choice = false;
        }
        else if (y[index] == 7 || y[index] == 5 || y[index] == 3 || y[index] == 1)
        {
            if (x[index] == 2)
            {
                x[index] = 0;
            }
            else if (x[index] == 4)
            {
                x[index] = 1;
            }
            else if (x[index] == 6)
            {
                x[index] = 2;
            }
            else if (x[index] == 8)
            {
                x[index] = 3;
            }
            y[index] = y[index] - 1;

            invalid_choice = false;
        }
    }

    return invalid_choice;
}

bool select_piece_player()
{
    bool selected{false};

    if (box[y[0]][x[0]] == 'x' || box[y[0]][x[0]] == 'X')
    {
        // moving up without knock
        if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && (box[y[0] + 1][x[0]] == ' ' || box[y[0] + 1][x[0]] == '.'))
        {
            if (box[y[0]][x[0]] == 'x')
            {
                box[y[0]][x[0]] = 's';
            }
            else
            {
                box[y[0]][x[0]] = 'S';
            }

            selected = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (box[y[0] + 1][x[0] + 1] == ' ' || box[y[0] + 1][x[0] + 1] == '.'))
        {
            if (box[y[0]][x[0]] == 'x')
            {
                box[y[0]][x[0]] = 's';
            }
            else
            {
                box[y[0]][x[0]] = 'S';
            }

            selected = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && (box[y[0] + 1][x[0]] == ' ' || box[y[0] + 1][x[0]] == '.'))
        {
            if (box[y[0]][x[0]] == 'x')
            {
                box[y[0]][x[0]] = 's';
            }
            else
            {
                box[y[0]][x[0]] = 'S';
            }

            selected = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] + 1][x[0] - 1] == ' ' || box[y[0] + 1][x[0] - 1] == '.'))
        {
            if (box[y[0]][x[0]] == 'x')
            {
                box[y[0]][x[0]] = 's';
            }
            else
            {
                box[y[0]][x[0]] = 'S';
            }

            selected = true;
        }
        // moving up with knock
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] + 1][x[0] + 1] == 'o' || box[y[0] + 1][x[0] + 1] == 'O') &&
                 (box[y[0] + 2][x[0] + 1] == ' ' || box[y[0] + 2][x[0] + 1] == '.'))
        {
            if (box[y[0]][x[0]] == 'x')
            {
                box[y[0]][x[0]] = 's';
            }
            else
            {
                box[y[0]][x[0]] = 'S';
            }

            selected = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] + 1][x[0]] == 'o' || box[y[0] + 1][x[0]] == 'O') &&
                 (box[y[0] + 2][x[0] - 1] == ' ' || box[y[0] + 2][x[0] - 1] == '.'))
        {
            if (box[y[0]][x[0]] == 'x')
            {
                box[y[0]][x[0]] = 's';
            }
            else
            {
                box[y[0]][x[0]] = 'S';
            }

            selected = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] + 1][x[0]] == 'o' || box[y[0] + 1][x[0]] == 'O') &&
                 (box[y[0] + 2][x[0] + 1] == ' ' || box[y[0] + 2][x[0] + 1] == '.'))
        {
            if (box[y[0]][x[0]] == 'x')
            {
                box[y[0]][x[0]] = 's';
            }
            else
            {
                box[y[0]][x[0]] = 'S';
            }

            selected = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] + 1][x[0] - 1] == 'o' || box[y[0] + 1][x[0] - 1] == 'O') &&
                 (box[y[0] + 2][x[0] - 1] == ' ' || box[y[0] + 2][x[0] - 1] == '.'))
        {
            if (box[y[0]][x[0]] == 'x')
            {
                box[y[0]][x[0]] = 's';
            }
            else
            {
                box[y[0]][x[0]] = 'S';
            }

            selected = true;
        }
    }
    if (box[y[0]][x[0]] == 'X' && !selected)
    {
        // moving down without knock
        if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && (box[y[0] - 1][x[0]] == ' ' || box[y[0] - 1][x[0]] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (box[y[0] - 1][x[0] + 1] == ' ' || box[y[0] - 1][x[0] + 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && (box[y[0] - 1][x[0]] == ' ' || box[y[0] - 1][x[0]] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && (box[y[0] - 1][x[0] - 1] == ' ' || box[y[0] - 1][x[0] - 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            selected = true;
        }

        // moving down with knock
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] - 1][x[0] + 1] == 'o' || box[y[0] - 1][x[0] + 1] == 'O') &&
                 (box[y[0] - 2][x[0] + 1] == ' ' || box[y[0] - 2][x[0] + 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] - 1][x[0]] == 'o' || box[y[0] - 1][x[0]] == 'O') &&
                 (box[y[0] - 2][x[0] - 1] == ' ' || box[y[0] - 2][x[0] - 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] - 1][x[0]] == 'o' || box[y[0] - 1][x[0]] == 'O') &&
                 (box[y[0] - 2][x[0] + 1] == ' ' || box[y[0] - 2][x[0] + 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] - 1][x[0] - 1] == 'o' || box[y[0] - 1][x[0] - 1] == 'O') &&
                 (box[y[0] - 2][x[0] - 1] == ' ' || box[y[0] - 2][x[0] - 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            selected = true;
        }
    }

    return selected;
}

bool move_piece_player()
{
    bool moved{false};

    if (y[0] + 1 == y[1] && (box[y[0]][x[0]] == 'S' || box[y[0]][x[0]] == 's'))
    {
        if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && (x[0] == x[1] || x[0] + 1 == x[1]))
        {
            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {

            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && (x[0] == x[1] || x[0] - 1 == x[1]))
        {

            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] == 0 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {

            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            moved = true;
        }

        moved_by_knock = false;
    }

    else if (y[0] - 1 == y[1] && box[y[0]][x[0]] == 'S')
    {
        if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (x[0] == x[1] || x[0] + 1 == x[1]) &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            box[y[1]][x[1]] = 'X';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            box[y[1]][x[1]] = 'X';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && (x[0] == x[1] || x[0] - 1 == x[1]) &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            box[y[1]][x[1]] = 'X';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] == 0 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            box[y[1]][x[1]] = 'X';
            box[y[0]][x[0]] = '.';
            moved = true;
        }

        moved_by_knock = false;
    }

    // up --> knock
    else if (y[0] + 2 == y[1] && (box[y[0]][x[0]] == 'S' || box[y[0]][x[0]] == 's'))
    {
        if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] + 1][x[0] - 1] == 'o' || box[y[0] + 1][x[0] - 1] == 'O') &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {

            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0] - 1] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] + 1][x[0]] == 'o' || box[y[0] + 1][x[0]] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {

            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] + 1][x[0]] == 'o' || box[y[0] + 1][x[0]] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {

            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] + 1][x[0] + 1] == 'o' || box[y[0] + 1][x[0] + 1] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {

            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0] + 1] = '.';
            moved = true;
        }

        moved_by_knock = true;
    }

    // down --> knock
    else if (y[0] - 2 == y[1] && box[y[0]][x[0]] == 'S')
    {
        if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] - 1][x[0] - 1] == 'o' || box[y[0] - 1][x[0] - 1] == 'O') &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            box[y[1]][x[1]] = 'X';
            box[y[0] - 1][x[0] - 1] = '.';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] - 1][x[0]] == 'o' || box[y[0] - 1][x[0]] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            box[y[1]][x[1]] = 'X';
            box[y[0] - 1][x[0]] = '.';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] - 1][x[0]] == 'o' || box[y[0] - 1][x[0]] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            box[y[1]][x[1]] = 'X';
            box[y[0] - 1][x[0]] = '.';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] - 1][x[0] + 1] == 'o' || box[y[0] - 1][x[0] + 1] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            box[y[1]][x[1]] = 'X';
            box[y[0] - 1][x[0] + 1] = '.';
            box[y[0]][x[0]] = '.';
            moved = true;
        }

        moved_by_knock = true;
    }

    for (short int column = 0; column < 4; column++)
    {
        if (box[7][column] == 'x')
        {
            box[7][column] = 'X';
        }
    }

    return moved;
}

bool more_knocks()
{
    bool knock_present{false};

    if ((box[y[1]][x[1]] == 'x' || box[y[1]][x[1]] == 'X'))
    {
        if ((y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (box[y[1] + 1][x[1] - 1] == 'o' || box[y[1] + 1][x[1] - 1] == 'O') &&
            (box[y[1] + 2][x[1] - 1] == ' ' || box[y[1] + 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (box[y[1] + 1][x[1]] == 'o' || box[y[1] + 1][x[1]] == 'O') &&
            (box[y[1] + 2][x[1] + 1] == ' ' || box[y[1] + 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (box[y[1] + 1][x[1]] == 'o' || box[y[1] + 1][x[1]] == 'O') &&
            (box[y[1] + 2][x[1] - 1] == ' ' || box[y[1] + 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (box[y[1] + 1][x[1] + 1] == 'o' || box[y[1] + 1][x[1] + 1] == 'O') &&
            (box[y[1] + 2][x[1] + 1] == ' ' || box[y[1] + 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
    }
    if (box[y[1]][x[1]] == 'X')
    {
        if ((y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (box[y[1] - 1][x[1] - 1] == 'o' || box[y[1] - 1][x[1] - 1] == 'O') &&
            (box[y[1] - 2][x[1] - 1] == ' ' || box[y[1] - 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (box[y[1] - 1][x[1]] == 'o' || box[y[1] - 1][x[1]] == 'O') &&
            (box[y[1] - 2][x[1] + 1] == ' ' || box[y[1] - 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (box[y[1] - 1][x[1]] == 'o' || box[y[1] - 1][x[1]] == 'O') &&
            (box[y[1] - 2][x[1] - 1] == ' ' || box[y[1] - 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (box[y[1] - 1][x[1] + 1] == 'o' || box[y[1] - 1][x[1] + 1] == 'O') &&
            (box[y[1] - 2][x[1] + 1] == ' ' || box[y[1] - 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
    }
    if ((box[y[1]][x[1]] == 'o' || box[y[1]][x[1]] == 'O'))
    {
        if ((y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (box[y[1] - 1][x[1] - 1] == 'x' || box[y[1] - 1][x[1] - 1] == 'X') &&
            (box[y[1] - 2][x[1] - 1] == ' ' || box[y[1] - 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (box[y[1] - 1][x[1]] == 'x' || box[y[1] - 1][x[1]] == 'X') &&
            (box[y[1] - 2][x[1] + 1] == ' ' || box[y[1] - 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (box[y[1] - 1][x[1]] == 'x' || box[y[1] - 1][x[1]] == 'X') &&
            (box[y[1] - 2][x[1] - 1] == ' ' || box[y[1] - 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (box[y[1] - 1][x[1] + 1] == 'x' || box[y[1] - 1][x[1] + 1] == 'X') &&
            (box[y[1] - 2][x[1] + 1] == ' ' || box[y[1] - 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
    }
    if (box[y[1]][x[1]] == 'O')
    {
        if ((y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (box[y[1] + 1][x[1] - 1] == 'x' || box[y[1] + 1][x[1] - 1] == 'X') &&
            (box[y[1] + 2][x[1] - 1] == ' ' || box[y[1] + 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (box[y[1] + 1][x[1]] == 'x' || box[y[1] + 1][x[1]] == 'X') &&
            (box[y[1] + 2][x[1] + 1] == ' ' || box[y[1] + 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (box[y[1] + 1][x[1]] == 'x' || box[y[1] + 1][x[1]] == 'X') &&
            (box[y[1] + 2][x[1] - 1] == ' ' || box[y[1] + 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (box[y[1] + 1][x[1] + 1] == 'x' || box[y[1] + 1][x[1] + 1] == 'X') &&
            (box[y[1] + 2][x[1] + 1] == ' ' || box[y[1] + 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
    }

    return knock_present;
}

void computer()
{
    std::cout << "        =========================================" << std::endl;
    std::cout << "                      COMP'S TURN" << std::endl;
    std::cout << "        ========================================= ";

    for (short int f{}; f < 8; f++)
    {
        for (short int g{}; g < 4; g++)
        {
            if (box[f][g] == '.')
            {
                box[f][g] = ' ';
            }
        }
    }

    int total_knocks{};
    short int rand_num{};
    bool selected{false};
    bool moved{false};
    bool removed_knock{false};
    bool blocked_knock{false};
    char temp_board[8][4]{};

    bool knock_present = knocks_checking(&total_knocks);

    if (play_mode == 1)
    {
        rand_num = rand() % 3;
        auto total_moves = total_compMoves();

        if (total_moves == 0 && knock_present)
        {
            rand_num = 1;
        }

        if (rand_num == 1 && knock_present)
        {
            knocks_checking(&total_knocks);
            rand_num = rand() % total_knocks;

            y[0] = temp_y[rand_num];
            x[0] = temp_x[rand_num];
            y[1] = y1_store[rand_num];
            x[1] = x1_store[rand_num];

            move_piece_comp('Y');

            while (knock_present = knocks_checking(&total_knocks))
            {
                rand_num = rand() % total_knocks;

                y[0] = temp_y[rand_num];
                x[0] = temp_x[rand_num];
                y[1] = y1_store[rand_num];
                x[1] = x1_store[rand_num];

                move_piece_comp('Y');
            }

            moved = true;
        }

        if (!moved)
        {
            select_piece_comp();
            move_piece_comp('N');
        }
    }
    else if (play_mode == 2)
    {
        if (knock_present)
        {
            rand_num = rand() % 4;
            if (rand_num == 1 || rand_num == 3)
            {
                short int max_knocks{};
                short int index{};

                do
                {
                    y[0] = temp_y[index];
                    x[0] = temp_x[index];

                    auto total_comp_knocks = maxKnocks_comp();
                    auto total_player_knocks = maxKnocks_player();

                    if (total_comp_knocks > max_knocks && total_player_knocks <= total_comp_knocks)
                    {
                        max_knocks = total_comp_knocks;
                        for (short int c = 0; c < 8; c++)
                        {
                            for (short int d = 0; d < 4; d++)
                            {
                                temp_board[c][d] = temp_box2[c][d];
                            }
                        }

                        selected = true;
                    }

                    index++;

                } while (index < total_knocks);

                if (selected)
                {
                    for (short int c = 0; c < 8; c++)
                    {
                        for (short int d = 0; d < 4; d++)
                        {
                            box[c][d] = temp_board[c][d];
                        }
                    }

                    moved = true;
                }
            }
            else if (rand_num == 0 || rand_num == 2)
            {
                knocks_checking(&total_knocks);
                rand_num = rand() % total_knocks;

                y[0] = temp_y[rand_num];
                x[0] = temp_x[rand_num];
                y[1] = y1_store[rand_num];
                x[1] = x1_store[rand_num];

                move_piece_comp('Y');

                while (knock_present = knocks_checking(&total_knocks))
                {
                    rand_num = rand() % total_knocks;

                    y[0] = temp_y[rand_num];
                    x[0] = temp_x[rand_num];
                    y[1] = y1_store[rand_num];
                    x[1] = x1_store[rand_num];

                    move_piece_comp('Y');
                }

                moved = true;
            }
        }

        if (!moved)
        {
            removed_knock = playersKnock_remove();
            if (!removed_knock)
            {
                blocked_knock = playersKnock_block();
                if (blocked_knock)
                {
                    for (short int s = 0; s < 8; s++)
                    {
                        for (short int t = 0; t < 4; t++)
                        {
                            box[s][t] = temp_box1[s][t];
                        }
                    }
                }
            }
            else if (removed_knock)
            {
                for (short int s = 0; s < 8; s++)
                {
                    for (short int t = 0; t < 4; t++)
                    {
                        box[s][t] = temp_box1[s][t];
                    }
                }
            }

            while (!moved && !removed_knock && !blocked_knock)
            {
                for (short int re_do = 0; re_do < 100000; re_do++)
                {
                    select_piece_comp();
                    bool future_knock = players_knock();

                    if (!future_knock)
                    {
                        for (short int c = 0; c < 8; c++)
                        {
                            for (short int d = 0; d < 4; d++)
                            {
                                box[c][d] = temp_box1[c][d];
                            }
                        }

                        moved = true;
                    }

                    if (moved)
                        break;
                    else if (!moved && re_do == 100)
                    {
                        select_piece_comp();
                        move_piece_comp('N');

                        moved = true;
                        break;
                    }
                }
            }
        }
    }
    else if (play_mode == 3)
    {
        if (knock_present)
        {
            short int max_knocks{};
            short int index{};

            while (index < total_knocks)
            {
                y[0] = temp_y[index];
                x[0] = temp_x[index];

                auto total_comp_knocks = maxKnocks_comp();
                auto total_player_knocks = maxKnocks_player();

                if (total_comp_knocks > max_knocks && total_player_knocks <= total_comp_knocks)
                {
                    max_knocks = total_comp_knocks;
                    for (short int c = 0; c < 8; c++)
                    {
                        for (short int d = 0; d < 4; d++)
                        {
                            temp_board[c][d] = temp_box2[c][d];
                        }
                    }

                    selected = true;
                }

                index++;
            }

            if (selected)
            {
                for (short int c = 0; c < 8; c++)
                {
                    for (short int d = 0; d < 4; d++)
                    {
                        box[c][d] = temp_board[c][d];
                    }
                }

                moved = true;
            }
        }
        
        if (!moved)
        {
            best_move();
        }
    }

    std::cout << std::endl;
    print_board();
}

bool knocks_checking(int *total_knocks)
{
    bool knock_present{false};
    *total_knocks = 0;

    for (short int q = 0; q <= 7; q++)
    {
        for (short int r = 0; r < 4; r++)
        {
            // checking upwards

            if ((q == 0 || q == 2 || q == 4) && r != 3 && (box[q + 1][r + 1] == 'x' || box[q + 1][r + 1] == 'X') &&
                (box[q + 2][r + 1] == ' ' || box[q + 2][r + 1] == '.') && box[q][r] == 'O')
            {
                temp_y[*total_knocks] = q;
                temp_x[*total_knocks] = r;
                y1_store[*total_knocks] = q + 2;
                x1_store[*total_knocks] = r + 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((q == 0 || q == 2 || q == 4) && r != 0 && (box[q + 1][r] == 'x' || box[q + 1][r] == 'X') &&
                (box[q + 2][r - 1] == ' ' || box[q + 2][r - 1] == '.') && box[q][r] == 'O')
            {
                temp_y[*total_knocks] = q;
                temp_x[*total_knocks] = r;
                y1_store[*total_knocks] = q + 2;
                x1_store[*total_knocks] = r - 1; // *x1_store[*total_knocks] = r = 1;*  expensive error
                *total_knocks = *total_knocks + 1;
            }
            if ((q == 1 || q == 3 || q == 5) && r != 3 && (box[q + 1][r] == 'x' || box[q + 1][r] == 'X') &&
                (box[q + 2][r + 1] == ' ' || box[q + 2][r + 1] == '.') && box[q][r] == 'O')
            {
                temp_y[*total_knocks] = q;
                temp_x[*total_knocks] = r;
                y1_store[*total_knocks] = q + 2;
                x1_store[*total_knocks] = r + 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((q == 1 || q == 3 || q == 5) && r != 0 && (box[q + 1][r - 1] == 'x' || box[q + 1][r - 1] == 'X') &&
                (box[q + 2][r - 1] == ' ' || box[q + 2][r - 1] == '.') && box[q][r] == 'O')
            {
                temp_y[*total_knocks] = q;
                temp_x[*total_knocks] = r;
                y1_store[*total_knocks] = q + 2;
                x1_store[*total_knocks] = r - 1;
                *total_knocks = *total_knocks + 1;
            }
            // checking downwards

            if ((q == 6 || q == 2 || q == 4) && r != 3 && (box[q - 1][r + 1] == 'x' || box[q - 1][r + 1] == 'X') &&
                (box[q - 2][r + 1] == ' ' || box[q - 2][r + 1] == '.') && (box[q][r] == 'o' || box[q][r] == 'O'))
            {
                temp_y[*total_knocks] = q;
                temp_x[*total_knocks] = r;
                y1_store[*total_knocks] = q - 2;
                x1_store[*total_knocks] = r + 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((q == 6 || q == 2 || q == 4) && r != 0 && (box[q - 1][r] == 'x' || box[q - 1][r] == 'X') &&
                (box[q - 2][r - 1] == ' ' || box[q - 2][r - 1] == '.') && (box[q][r] == 'o' || box[q][r] == 'O'))
            {
                temp_y[*total_knocks] = q;
                temp_x[*total_knocks] = r;
                y1_store[*total_knocks] = q - 2;
                x1_store[*total_knocks] = r - 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((q == 7 || q == 3 || q == 5) && r != 3 && (box[q - 1][r] == 'x' || box[q - 1][r] == 'X') &&
                (box[q - 2][r + 1] == ' ' || box[q - 2][r + 1] == '.') && (box[q][r] == 'o' || box[q][r] == 'O'))
            {
                temp_y[*total_knocks] = q;
                temp_x[*total_knocks] = r;
                y1_store[*total_knocks] = q - 2;
                x1_store[*total_knocks] = r + 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((q == 7 || q == 3 || q == 5) && r != 0 && (box[q - 1][r - 1] == 'x' || box[q - 1][r - 1] == 'X') &&
                (box[q - 2][r - 1] == ' ' || box[q - 2][r - 1] == '.') && (box[q][r] == 'o' || box[q][r] == 'O'))
            {
                temp_y[*total_knocks] = q;
                temp_x[*total_knocks] = r;
                y1_store[*total_knocks] = q - 2;
                x1_store[*total_knocks] = r - 1;
                *total_knocks = *total_knocks + 1;
            }
        }
    }

    if (*total_knocks > 0)
        knock_present = true;

    return knock_present;
}

unsigned short int total_compMoves()
{
    int count{};

    for (short int u = 0; u < 8; u++)
    {
        for (short int v{}; v < 4; v++)
        {
            // downwards rightwards - odd
            if ((u == 7 || u == 5 || u == 3 || u == 1) && (box[u][v] == 'O' || box[u][v] == 'o') && box[u - 1][v] == ' ')
            {
                count++;
            }

            // downwards leftwards - odd
            if ((u == 7 || u == 5 || u == 3 || u == 1) && v != 0 && (box[u][v] == 'O' || box[u][v] == 'o') && box[u - 1][v - 1] == ' ')
            {
                count++;
            }

            // downwards rightwards - even
            if ((u == 6 || u == 4 || u == 2) && v != 3 && (box[u][v] == 'O' || box[u][v] == 'o') && box[u - 1][v + 1] == ' ')
            {
                count++;
            }

            // downwards leftwards - even
            if ((u == 6 || u == 4 || u == 2) && v != 0 && (box[u][v] == 'O' || box[u][v] == 'o') && box[u - 1][v] == ' ')
            {
                count++;
            }

            // upwards rightwards - odd
            if ((u == 1 || u == 5 || u == 3) && box[u][v] == 'O' && box[u + 1][v] == ' ')
            {
                count++;
            }

            // upwards leftwards - odd
            if ((u == 1 || u == 5 || u == 3) && v != 0 && box[u][v] == 'O' && box[u + 1][v - 1] == ' ')
            {
                count++;
            }

            // upwards rightwards - even
            if ((u == 0 || u == 4 || u == 2 || u == 6) && v != 3 && box[u][v] == 'O' && box[u + 1][v + 1] == ' ')
            {
                count++;
            }

            // upwards leftwards - even
            if ((u == 0 || u == 4 || u == 2) && box[u][v] == 'O' && box[u + 1][v] == ' ')
            {
                count++;
            }
        }
    }

    return count;
}

unsigned short int total_unknock_moves()
{
    unsigned short int count{};

    for (short int a = 0; a < 8; a++)
    {
        for (short int b = 0; b < 4; b++)
        {
            // upwards rightwards
            if ((a == 0 || a == 2 || a == 4) && b != 3 && box[a + 1][b + 1] == ' ' && box[a + 2][b + 1] != 'X' &&
                ((box[a][b + 1] != 'x' && box[a][b + 1] != 'X') || ((box[a][b + 1] == 'x' || box[a][b + 1] == 'X') && box[a + 2][b] != ' ')) &&
                (box[a + 2][b] != 'X' || (box[a + 2][b] == 'X' && box[a][b + 1] != ' ')) && box[a][b] == 'O')
            {
                temp_y[count] = a;
                temp_x[count] = b;
                y1_store[count] = a + 1;
                x1_store[count] = b + 1;
                count++;
            }
            if (a == 6 && b != 3 && box[a + 1][b + 1] == ' ' && box[a][b] == 'O')
            {
                temp_y[count] = a;
                temp_x[count] = b;
                y1_store[count] = a + 1;
                x1_store[count] = b + 1;
                count++;
            }
            if ((a == 1 || a == 3 || a == 5) && b != 3 && box[a + 1][b] == ' ' && box[a + 2][b + 1] != 'X' &&
                ((box[a][b + 1] != 'x' && box[a][b + 1] != 'X') || ((box[a][b + 1] == 'x' || box[a][b + 1] == 'X') && box[a + 2][b] != ' ')) &&
                (box[a + 2][b] != 'X' || (box[a + 2][b] == 'X' && box[a][b + 1] != ' ')) && box[a][b] == 'O')
            {
                temp_y[count] = a;
                temp_x[count] = b;
                y1_store[count] = a + 1;
                x1_store[count] = b;
                count++;
            }
            if ((a == 1 || a == 3 || a == 5) && b == 3 && box[a + 1][b] == ' ' && box[a][b] == 'O')
            {
                temp_y[count] = a;
                temp_x[count] = b;
                y1_store[count] = a + 1;
                x1_store[count] = b;
                count++;
            }

            // upwards leftwards
            if ((a == 0 || a == 2 || a == 4) && b != 0 && box[a + 1][b] == ' ' && box[a + 2][b - 1] != 'X' &&
                ((box[a][b - 1] != 'x' && box[a][b - 1] != 'X') || ((box[a][b - 1] == 'x' || box[a][b - 1] == 'X') && box[a + 2][b] != ' ')) &&
                (box[a + 2][b] != 'X' || (box[a + 2][b] == 'X' && box[a][b - 1] != ' ')) && box[a][b] == 'O')
            {
                temp_y[count] = a;
                temp_x[count] = b;
                y1_store[count] = a + 1;
                x1_store[count] = b;
                count++;
            }
            if (a == 6 && box[a + 1][b] == ' ' && box[a][b] == 'O')
            {
                temp_y[count] = a;
                temp_x[count] = b;
                y1_store[count] = a + 1;
                x1_store[count] = b;
                count++;
            }
            if ((a == 0 || a == 2 || a == 4) && b == 0 && box[a + 1][b] == ' ' && box[a][b] == 'O')
            {
                temp_y[count] = a;
                temp_x[count] = b;
                y1_store[count] = a + 1;
                x1_store[count] = b;
                count++;
            }
            if ((a == 1 || a == 3 || a == 5) && b != 0 && box[a + 1][b - 1] == ' ' && box[a + 2][b - 1] != 'X' &&
                ((box[a][b - 1] != 'x' && box[a][b - 1] != 'X') || ((box[a][b - 1] == 'x' || box[a][b - 1] == 'X') && box[a + 2][b] != ' ')) &&
                (box[a + 2][b] != 'X' || (box[a + 2][b] == 'X' && box[a][b - 1] != ' ')) && box[a][b] == 'O')
            {
                temp_y[count] = a;
                temp_x[count] = b;
                y1_store[count] = a + 1;
                x1_store[count] = b - 1;
                count++;
            }

            // downwards rightwards
            if ((a == 7 || a == 5 || a == 3) && b != 3 && box[a - 1][b] == ' ' && box[a - 2][b + 1] != 'X' && box[a - 2][b + 1] != 'x' &&
                ((box[a - 2][b] != 'x' && box[a - 2][b] != 'X') || ((box[a - 2][b] == 'x' || box[a - 2][b] == 'X') && box[a][b + 1] != ' ')) &&
                (box[a][b + 1] != 'X' || (box[a][b + 1] == 'X' && box[a - 2][b] != ' ')) && (box[a][b] == 'O' || box[a][b] == 'o'))
            {
                temp_y[count] = a;
                temp_x[count] = b;
                y1_store[count] = a - 1;
                x1_store[count] = b;
                count++;
            }
            if ((a == 7 || a == 5 || a == 3) && b == 3 && box[a - 1][b] == ' ' && (box[a][b] == 'O' || box[a][b] == 'o'))
            {
                temp_y[count] = a;
                temp_x[count] = b;
                y1_store[count] = a - 1;
                x1_store[count] = b;
                count++;
            }
            if (a == 1 && box[a - 1][b] == ' ' && (box[a][b] == 'O' || box[a][b] == 'o'))
            {
                temp_y[count] = a;
                temp_x[count] = b;
                y1_store[count] = a - 1;
                x1_store[count] = b;
                count++;
            }
            if ((a == 6 || a == 4 || a == 2) && b != 3 && box[a - 1][b + 1] == ' ' && box[a - 2][b + 1] != 'X' && box[a - 2][b + 1] != 'x' &&
                ((box[a - 2][b] != 'x' && box[a - 2][b] != 'X') || ((box[a - 2][b] == 'x' || box[a - 2][b] == 'X') && box[a][b + 1] != ' ')) &&
                (box[a][b + 1] != 'X' || (box[a][b + 1] == 'X' && box[a - 2][b] != ' ')) && (box[a][b] == 'O' || box[a][b] == 'o'))
            {
                temp_y[count] = a;
                temp_x[count] = b;
                y1_store[count] = a - 1;
                x1_store[count] = b + 1;
                count++;
            }

            // downwards leftwards
            if ((a == 7 || a == 5 || a == 3) && b != 0 && box[a - 1][b - 1] == ' ' && box[a - 2][b - 1] != 'X' && box[a - 2][b - 1] != 'x' &&
                ((box[a - 2][b] != 'x' && box[a - 2][b] != 'X') || ((box[a - 2][b] == 'x' || box[a - 2][b] == 'X') && box[a][b - 1] != ' ')) &&
                (box[a][b - 1] != 'X' || (box[a][b - 1] == 'X' && box[a - 2][b] != ' ')) && (box[a][b] == 'O' || box[a][b] == 'o'))
            {
                temp_y[count] = a;
                temp_x[count] = b;
                y1_store[count] = a - 1;
                x1_store[count] = b - 1;
                count++;
            }
            if (a == 1 && b != 0 && box[a - 1][b - 1] == ' ' && (box[a][b] == 'O' || box[a][b] == 'o'))
            {
                temp_y[count] = a;
                temp_x[count] = b;
                y1_store[count] = a - 1;
                x1_store[count] = b - 1;
                count++;
            }
            if ((a == 6 || a == 4 || a == 2) && b != 0 && box[a - 1][b] == ' ' && box[a - 2][b - 1] != 'X' && box[a - 2][b - 1] != 'x' &&
                ((box[a - 2][b] != 'x' && box[a - 2][b] != 'X') || ((box[a - 2][b] == 'x' || box[a - 2][b] == 'X') && box[a][b - 1] != ' ')) &&
                (box[a][b - 1] != 'X' || (box[a][b - 1] == 'X' && box[a - 2][b] != ' ')) && (box[a][b] == 'O' || box[a][b] == 'o'))
            {
                temp_y[count] = a;
                temp_x[count] = b;
                y1_store[count] = a - 1;
                x1_store[count] = b;
                count++;
            }
            if ((a == 6 || a == 4 || a == 2) && b == 0 && box[a - 1][b] == ' ' && (box[a][b] == 'O' || box[a][b] == 'o'))
            {
                temp_y[count] = a;
                temp_x[count] = b;
                y1_store[count] = a - 1;
                x1_store[count] = b;
                count++;
            }
        }
    }

    return count;
}

void select_piece_comp()
{
    auto temp_play_mode{play_mode};

    if (play_mode == 2 || play_mode == 3)
    {
        auto total_moves{total_unknock_moves()};
        // std::cout << "total_moves: " << total_moves;

        if (total_moves == 0)
            temp_play_mode = 1;

        else if (total_moves > 0)
        {
            auto rand_num{rand() % total_moves};
            y[0] = temp_y[rand_num];
            x[0] = temp_x[rand_num];
        }
        // std::cout << " y[0]:" << y[0] << " x[0]:" << x[0] << '\n';
    }

    int count{};
    bool selected{false};

    while (!selected && temp_play_mode == 1)
    {
        y[0] = rand() % 8;

        for (short int w = 0; w < 500; w++)
        {
            x[0] = rand() % 4;
            choice[0] = rand() % 8;
            count = 0;

            do
            {
                // moving up without knock
                if (choice[0] == 0 && (y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && box[y[0] + 1][x[0]] == ' ' && box[y[0]][x[0]] == 'O')
                {
                    selected = true;
                }
                else if (choice[0] == 1 && (y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && box[y[0] + 1][x[0] + 1] == ' ' && box[y[0]][x[0]] == 'O')
                {
                    selected = true;
                }
                else if (choice[0] == 2 && (y[0] == 1 || y[0] == 3 || y[0] == 5) && box[y[0] + 1][x[0]] == ' ' && box[y[0]][x[0]] == 'O')
                {
                    selected = true;
                }
                else if (choice[0] == 3 && (y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && box[y[0] + 1][x[0] - 1] == ' ' && box[y[0]][x[0]] == 'O')
                {
                    selected = true;
                }

                // moving down without knock
                else if (choice[0] == 4 && (y[0] == 2 || y[0] == 4 || y[0] == 6) && box[y[0] - 1][x[0]] == ' ' && (box[y[0]][x[0]] == 'o' || box[y[0]][x[0]] == 'O'))
                {
                    selected = true;
                }
                else if (choice[0] == 5 && (y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && box[y[0] - 1][x[0] + 1] == ' ' && (box[y[0]][x[0]] == 'o' || box[y[0]][x[0]] == 'O'))
                {
                    selected = true;
                }
                else if (choice[0] == 6 && (y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && box[y[0] - 1][x[0]] == ' ' && (box[y[0]][x[0]] == 'o' || box[y[0]][x[0]] == 'O'))
                {
                    selected = true;
                }
                else if (choice[0] == 7 && (y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && box[y[0] - 1][x[0] - 1] == ' ' && (box[y[0]][x[0]] == 'o' || box[y[0]][x[0]] == 'O'))
                {
                    selected = true;
                }

                count++;
                choice[0]++;
                if (choice[0] == 8)
                    choice[0] = 0;

            } while (count <= 8 && !selected);

            if (selected)
                break;
        }
    }

    count = 0;

    // Available targets
    // downwards rightwards - odd
    if ((y[0] == 7 || y[0] == 5 || y[0] == 3 || y[0] == 1) && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
    {
        temp_y[count] = y[0] - 1;
        temp_x[count] = x[0];
        count++;
    }

    // downwards leftwards - odd
    if ((y[0] == 7 || y[0] == 5 || y[0] == 3 || y[0] == 1) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] - 1] == ' ')
    {
        temp_y[count] = y[0] - 1;
        temp_x[count] = x[0] - 1;
        count++;
    }

    // downwards rightwards - even
    if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] + 1] == ' ')
    {
        temp_y[count] = y[0] - 1;
        temp_x[count] = x[0] + 1;
        count++;
    }

    // downwards leftwards - even
    if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
    {
        temp_y[count] = y[0] - 1;
        temp_x[count] = x[0];
        count++;
    }

    // upwards rightwards - odd
    if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
    {
        temp_y[count] = y[0] + 1;
        temp_x[count] = x[0];
        count++;
    }

    // upwards leftwards - odd
    if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] != 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] - 1] == ' ')
    {
        temp_y[count] = y[0] + 1;
        temp_x[count] = x[0] - 1;
        count++;
    }

    // upwards rightwards - even
    if ((y[0] == 0 || y[0] == 4 || y[0] == 2 || y[0] == 6) && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] + 1] == ' ')
    {
        temp_y[count] = y[0] + 1;
        temp_x[count] = x[0] + 1;
        count++;
    }

    // upwards leftwards - even
    if ((y[0] == 0 || y[0] == 4 || y[0] == 2) && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
    {
        temp_y[count] = y[0] + 1;
        temp_x[count] = x[0];
        count++;
    }

    short int rand_num = rand() % count;
    y[1] = temp_y[rand_num];
    x[1] = temp_x[rand_num];

    // std::cout << "\n        y[0]:" << y[0] << " x[0]:" << x[0] << " y[1]:" << y[1] << " x[1]:" << x[1] << '\n';
}

void move_piece_comp(char knock)
{
    bool moved{false};

    // moving up without knock

    if (y[0] + 1 == y[1] && knock == 'N' && box[y[0]][x[0]] == 'O')
    {
        if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 &&
            box[y[1]][x[1]] == ' ' && (x[0] == x[1] || x[0] + 1 == x[1]))
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] && box[y[1]][x[1]] == ' ')
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && box[y[1]][x[1]] == ' ' && (x[0] == x[1] || x[0] - 1 == x[1]))
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] == 0 && x[0] == x[1] &&
                 box[y[1]][x[1]] == ' ')
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
    }

    // moving down without knock

    else if (y[0] - 1 == y[1] && knock == 'N' && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o'))
    {
        if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (x[0] == x[1] || x[0] + 1 == x[1]) && box[y[1]][x[1]] == ' ')
        {
            if (box[y[0]][x[0]] == 'O')
            {
                box[y[1]][x[1]] = 'O';
            }
            else
            {
                box[y[1]][x[1]] = 'o';
            }

            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] && box[y[1]][x[1]] == ' ')
        {
            if (box[y[0]][x[0]] == 'O')
            {
                box[y[1]][x[1]] = 'O';
            }
            else
            {
                box[y[1]][x[1]] = 'o';
            }

            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && (x[0] == x[1] || x[0] - 1 == x[1]) && box[y[1]][x[1]] == ' ')
        {
            if (box[y[0]][x[0]] == 'O')
            {
                box[y[1]][x[1]] = 'O';
            }
            else
            {
                box[y[1]][x[1]] = 'o';
            }

            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] == 0 && x[0] == x[1] && box[y[1]][x[1]] == ' ')
        {
            if (box[y[0]][x[0]] == 'O')
            {
                box[y[1]][x[1]] = 'O';
            }
            else
            {
                box[y[1]][x[1]] = 'o';
            }

            box[y[0]][x[0]] = '.';
            moved = true;
        }
    }

    // moving up with knock

    else if (y[0] + 2 == y[1] && box[y[0]][x[0]] == 'O' && knock == 'Y')
    {
        if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] + 1][x[0] - 1] == 'x' || box[y[0] + 1][x[0] - 1] == 'X') &&
            box[y[1]][x[1]] == ' ' && x[0] - 1 == x[1])
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0] - 1] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] + 1][x[0]] == 'x' || box[y[0] + 1][x[0]] == 'X') &&
                 box[y[1]][x[1]] == ' ' && x[0] + 1 == x[1])
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] + 1][x[0]] == 'x' || box[y[0] + 1][x[0]] == 'X') &&
                 box[y[1]][x[1]] == ' ' && x[0] - 1 == x[1])
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] + 1][x[0] + 1] == 'x' || box[y[0] + 1][x[0] + 1] == 'X') &&
                 box[y[1]][x[1]] == ' ' && x[0] + 1 == x[1])
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0] + 1] = '.';
            moved = true;
        }
    }

    // moving down with knock

    else if (y[0] - 2 == y[1] && knock == 'Y' && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o'))
    {
        if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] - 1][x[0] - 1] == 'x' || box[y[0] - 1][x[0] - 1] == 'X') &&
            box[y[1]][x[1]] == ' ' && x[0] - 1 == x[1])
        {
            if (box[y[0]][x[0]] == 'O')
            {
                box[y[1]][x[1]] = 'O';
            }
            else
            {
                box[y[1]][x[1]] = 'o';
            }

            box[y[0] - 1][x[0] - 1] = '.';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] - 1][x[0]] == 'x' || box[y[0] - 1][x[0]] == 'X') &&
                 box[y[1]][x[1]] == ' ' && x[0] + 1 == x[1])
        {
            if (box[y[0]][x[0]] == 'O')
            {
                box[y[1]][x[1]] = 'O';
            }
            else
            {
                box[y[1]][x[1]] = 'o';
            }

            box[y[0] - 1][x[0]] = '.';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] - 1][x[0]] == 'x' || box[y[0] - 1][x[0]] == 'X') &&
                 box[y[1]][x[1]] == ' ' && x[0] - 1 == x[1])
        {
            if (box[y[0]][x[0]] == 'O')
            {
                box[y[1]][x[1]] = 'O';
            }
            else
            {
                box[y[1]][x[1]] = 'o';
            }

            box[y[0] - 1][x[0]] = '.';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] - 1][x[0] + 1] == 'x' || box[y[0] - 1][x[0] + 1] == 'X') &&
                 box[y[1]][x[1]] == ' ' && x[0] + 1 == x[1])
        {
            if (box[y[0]][x[0]] == 'O')
            {
                box[y[1]][x[1]] = 'O';
            }
            else
            {
                box[y[1]][x[1]] = 'o';
            }

            box[y[0] - 1][x[0] + 1] = '.';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
    }

    // king
    for (short int i = 0; i < 4; i++)
    {
        if (box[0][i] == 'o')
        {
            box[0][i] = 'O';
        }
    }

    // std::cout << "\n        WARNING!!! COMP PIECE NOT MOVED!" << std::endl;
    // std::cout << "\n        y[0]:" << y[0] << " x[0]:" << x[0] << " y[1]:" << y[1] << " x[1]:" << x[1] << '\n';
}

void best_move()
{
    char final_board[8][4]{};
    bool target_chosen{false};
    int total_comp_knocks1{};
    int total_comp_knocks2{};
    bool knock_present{false};

    bool knock_chosen = knock_antidote();
    if (knock_chosen)
    {
        for (short int s = 0; s < 8; s++)
        {
            for (short int t = 0; t < 4; t++)
            {
                final_board[s][t] = temp_box1[s][t];
            }
        }

        y[0] = 0;
        y[1] = 0;
        x[0] = 0;
        x[1] = 0;

        triple_play(&total_comp_knocks1);
        target_chosen = true;
    }

    auto total_moves = total_unknock_moves();
    if (total_moves == 0)
    {
        for (y[0] = 0; y[0] < 8; y[0]++)
        {
            for (x[0] = 0; x[0] < 4; x[0]++)
            {
                if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && box[y[0] + 1][x[0]] == ' ' && box[y[0]][x[0]] == 'O')
                {
                    temp_y[total_moves] = y[0];
                    temp_x[total_moves] = x[0];
                    y1_store[total_moves] = y[0] + 1;
                    x1_store[total_moves] = x[0];
                    total_moves++;
                }
                if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && box[y[0] + 1][x[0] + 1] == ' ' && box[y[0]][x[0]] == 'O')
                {
                    temp_y[total_moves] = y[0];
                    temp_x[total_moves] = x[0];
                    y1_store[total_moves] = y[0] + 1;
                    x1_store[total_moves] = x[0] + 1;
                    total_moves++;
                }
                if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && box[y[0] + 1][x[0]] == ' ' && box[y[0]][x[0]] == 'O')
                {
                    temp_y[total_moves] = y[0];
                    temp_x[total_moves] = x[0];
                    y1_store[total_moves] = y[0] + 1;
                    x1_store[total_moves] = x[0];
                    total_moves++;
                }
                if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && box[y[0] + 1][x[0] - 1] == ' ' && box[y[0]][x[0]] == 'O')
                {
                    temp_y[total_moves] = y[0];
                    temp_x[total_moves] = x[0];
                    y1_store[total_moves] = y[0] + 1;
                    x1_store[total_moves] = x[0] - 1;
                    total_moves++;
                }
                if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && box[y[0] - 1][x[0]] == ' ' && (box[y[0]][x[0]] == 'o' || box[y[0]][x[0]] == 'O'))
                {
                    temp_y[total_moves] = y[0];
                    temp_x[total_moves] = x[0];
                    y1_store[total_moves] = y[0] - 1;
                    x1_store[total_moves] = x[0];
                    total_moves++;
                }
                if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && box[y[0] - 1][x[0] + 1] == ' ' && (box[y[0]][x[0]] == 'o' || box[y[0]][x[0]] == 'O'))
                {
                    temp_y[total_moves] = y[0];
                    temp_x[total_moves] = x[0];
                    y1_store[total_moves] = y[0] - 1;
                    x1_store[total_moves] = x[0] + 1;
                    total_moves++;
                }
                if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && box[y[0] - 1][x[0]] == ' ' && (box[y[0]][x[0]] == 'o' || box[y[0]][x[0]] == 'O'))
                {
                    temp_y[total_moves] = y[0];
                    temp_x[total_moves] = x[0];
                    y1_store[total_moves] = y[0] - 1;
                    x1_store[total_moves] = x[0];
                    total_moves++;
                }
                if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && box[y[0] - 1][x[0] - 1] == ' ' && (box[y[0]][x[0]] == 'o' || box[y[0]][x[0]] == 'O'))
                {
                    temp_y[total_moves] = y[0];
                    temp_x[total_moves] = x[0];
                    y1_store[total_moves] = y[0] - 1;
                    x1_store[total_moves] = x[0] - 1;
                    total_moves++;
                }
            }
        }
    }

    short int count{};
    if (target_chosen)
    {
        while (count < total_moves)
        {
            y[0] = temp_y[count];
            x[0] = temp_x[count];
            y[1] = y1_store[count];
            x[1] = x1_store[count];

            knock_present = triple_play(&total_comp_knocks2);
            if (knock_present && total_comp_knocks2 > total_comp_knocks1)
            {
                for (short int s = 0; s < 8; s++)
                {
                    for (short int t = 0; t < 4; t++)
                    {
                        final_board[s][t] = temp_box2[s][t];
                    }
                }
            }

            count++;
        }
    }
    else if (!target_chosen)
    {
        short int index = rand() % total_moves;
        while (count <= total_moves + 1)
        {
            y[0] = temp_y[index];
            x[0] = temp_x[index];
            y[1] = y1_store[index];
            x[1] = x1_store[index];

            knock_present = triple_play(&total_comp_knocks1);
            if (knock_present && total_comp_knocks1 > total_comp_knocks2)
            {
                for (short int s = 0; s < 8; s++)
                {
                    for (short int t = 0; t < 4; t++)
                    {
                        final_board[s][t] = temp_box2[s][t];
                        target_chosen = true;
                    }
                }
            }

            index++;
            if (index == total_moves)
                index = 0;

            y[0] = temp_y[index];
            x[0] = temp_x[index];
            y[1] = y1_store[index];
            x[1] = x1_store[index];

            knock_present = triple_play(&total_comp_knocks2);
            if (knock_present && total_comp_knocks2 > total_comp_knocks1)
            {
                for (short int s = 0; s < 8; s++)
                {
                    for (short int t = 0; t < 4; t++)
                    {
                        final_board[s][t] = temp_box2[s][t];
                        target_chosen = true;
                    }
                }
            }

            count++;
        }
        if (!target_chosen)
        {
            while (index != total_moves)
            {
                auto rand_num{rand() % total_moves};

                y[0] = temp_y[rand_num];
                x[0] = temp_x[rand_num];
                y[1] = y1_store[rand_num];
                x[1] = x1_store[rand_num];

                move_piece_comp('N');
            }
        }
    }

    if (target_chosen)
    {
        for (short int s = 0; s < 8; s++)
        {
            for (short int t = 0; t < 4; t++)
            {
                box[s][t] = final_board[s][t];
            }
        }
    }

    std::cout << "\n        target_chosen: " << std::boolalpha << target_chosen;
}

bool triple_play(int *total_comp_knocks)
{
    bool knock_available{false};
    *total_comp_knocks = 0;
    players_knock();

    for (short int s = 0; s < 8; s++)
    {
        for (short int t = 0; t < 4; t++)
        {
            temp_box2[s][t] = temp_box1[s][t];
        }
    }

    auto totalKnocks_p = maxKnocks_player();
    // std::cout << "totalKnocks_p: " << totalKnocks_p << '\n';
    //* /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int totalKnocks_c{};
    for (short int re_do = 0; re_do < 51; re_do++)
    {
        for (temp_y[18] = 0; temp_y[18] < 8; temp_y[18]++)
        {
            for (temp_x[18] = 0; temp_x[18] < 4; temp_x[18]++)
            {
                for (short int m{}; m < 8; m++)
                {
                    for (short int n{}; n < 4; n++)
                    {
                        temp_box1[m][n] = temp_box3[m][n];
                    }
                }

                if (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o')
                {
                    const unsigned short int initial_Y = temp_y[18];
                    const unsigned short int initial_X = temp_x[18];

                    int total_knocks{};

                    for (temp_y[19] = 0; temp_y[19] < 8; temp_y[19]++)
                    {
                        const unsigned short int temp_y19 = temp_y[19];

                        for (temp_x[19] = 0; temp_x[19] < 4; temp_x[19]++)
                        {
                            const unsigned short int temp_x19 = temp_x[19];

                            bool knock_present{false};
                            bool proceed{false};

                            do
                            {
                                if (temp_y[18] + 2 == temp_y[19] && temp_box1[temp_y[18]][temp_x[18]] == 'O')
                                {
                                    if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'X') &&
                                        (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                                    {
                                        proceed = true;
                                        temp_box1[temp_y[19]][temp_x[19]] = 'O';
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                        temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                                    }
                                    else if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                                    {
                                        proceed = true;
                                        temp_box1[temp_y[19]][temp_x[19]] = 'O';
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                                    }
                                    else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                                    {
                                        proceed = true;
                                        temp_box1[temp_y[19]][temp_x[19]] = 'O';
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                                    }
                                    else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'X') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                                    {
                                        proceed = true;
                                        temp_box1[temp_y[19]][temp_x[19]] = 'O';
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                        temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                                    }
                                }
                                else if (temp_y[18] - 2 == temp_y[19])
                                {
                                    if ((temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X') &&
                                        (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                                    {
                                        proceed = true;
                                        if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'O';
                                        }
                                        else
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'o';
                                        }
                                        temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                    }
                                    else if ((temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                                    {
                                        proceed = true;
                                        if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'O';
                                        }
                                        else
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'o';
                                        }
                                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                    }
                                    else if ((temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                                    {
                                        proceed = true;
                                        if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'O';
                                        }
                                        else
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'o';
                                        }
                                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                    }
                                    else if ((temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'X') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                                    {
                                        proceed = true;
                                        if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'O';
                                        }
                                        else
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'o';
                                        }
                                        temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                    }
                                }

                                if (proceed)
                                {
                                    total_knocks++;

                                    temp_y[18] = temp_y[19];
                                    temp_x[18] = temp_x[19];

                                    totalKnocks_c = (total_knocks > totalKnocks_c) ? total_knocks : totalKnocks_c;

                                    for (short int t = 0; t < 4; t++)
                                    {
                                        if (temp_box1[0][t] == 'o')
                                        {
                                            temp_box1[0][t] = 'O';
                                        }
                                    }

                                    knock_present = future_more_knocks();
                                }

                            } while (knock_present);

                            total_knocks = 0;

                            temp_y[18] = initial_Y;
                            temp_x[18] = initial_X;

                            for (short int m{}; m < 8; m++)
                            {
                                for (short int n{}; n < 4; n++)
                                {
                                    temp_box1[m][n] = temp_box3[m][n];
                                }
                            }

                            temp_x[19] = temp_x19;
                        }

                        temp_y[19] = temp_y19;
                    }
                }
            }
        }
    }

    //* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // std::cout << "totalKnocks_c: " << totalKnocks_c << '\n';

    if (totalKnocks_p > 0 || totalKnocks_c > 0)
    {
        knock_available = true;
        *total_comp_knocks = totalKnocks_c;
    }

    return knock_available;
}
bool players_knock()
{
    for (int c = 0; c < 8; c++)
    {
        for (int d = 0; d < 4; d++)
        {
            temp_box1[c][d] = box[c][d];
        }
    }

    temp_y[18] = y[0];
    temp_x[18] = x[0];
    temp_y[19] = y[1];
    temp_x[19] = x[1];

    // MOVING DOWNWARDS WITHOUT KNOCK
    if (temp_y[18] - 1 == temp_y[19])
    {
        // rightwards - odd
        if ((temp_y[18] == 7 || temp_y[18] == 5 || temp_y[18] == 3 || temp_y[18] == 1) && (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o') && temp_box1[temp_y[19]][temp_x[19]] == ' ' && temp_x[18] == temp_x[19])
        {
            if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
            {
                temp_box1[temp_y[19]][temp_x[19]] = 'O';
            }
            else
            {
                temp_box1[temp_y[19]][temp_x[19]] = 'o';
            }

            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }

        // leftwards - odd
        else if ((temp_y[18] == 7 || temp_y[18] == 5 || temp_y[18] == 3 || temp_y[18] == 1) && temp_x[18] != 0 && (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o') && temp_box1[temp_y[19]][temp_x[19]] == ' ' && temp_x[18] - 1 == temp_x[19])
        {
            if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
            {
                temp_box1[temp_y[19]][temp_x[19]] = 'O';
            }
            else
            {
                temp_box1[temp_y[19]][temp_x[19]] = 'o';
            }

            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }

        // rightwards - even
        else if ((temp_y[18] == 6 || temp_y[18] == 4 || temp_y[18] == 2) && temp_x[18] != 3 && (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o') && temp_box1[temp_y[19]][temp_x[19]] == ' ' && temp_x[18] + 1 == temp_x[19])
        {
            if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
            {
                temp_box1[temp_y[19]][temp_x[19]] = 'O';
            }
            else
            {
                temp_box1[temp_y[19]][temp_x[19]] = 'o';
            }

            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }

        // leftwards - even
        else if ((temp_y[18] == 6 || temp_y[18] == 4 || temp_y[18] == 2) && (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o') && temp_box1[temp_y[19]][temp_x[19]] == ' ' && temp_x[18] == temp_x[19])
        {
            if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
            {
                temp_box1[temp_y[19]][temp_x[19]] = 'O';
            }
            else
            {
                temp_box1[temp_y[19]][temp_x[19]] = 'o';
            }

            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }
    }

    // MOVING UPWARDS WITHOUT KNOCK
    else if (temp_y[18] + 1 == temp_y[19])
    {
        // rightwards - odd
        if ((temp_y[18] == 1 || temp_y[18] == 5 || temp_y[18] == 3) && temp_box1[temp_y[18]][temp_x[18]] == 'O' && temp_box1[temp_y[19]][temp_x[19]] == ' ' && temp_x[18] == temp_x[19])
        {
            temp_box1[temp_y[19]][temp_x[19]] = 'O';
            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }

        // checking upwards leftwards - odd
        else if ((temp_y[18] == 1 || temp_y[18] == 5 || temp_y[18] == 3) && temp_x[18] != 0 && temp_box1[temp_y[18]][temp_x[18]] == 'O' && temp_box1[temp_y[19]][temp_x[19]] == ' ' && temp_x[18] - 1 == temp_x[19])
        {
            temp_box1[temp_y[19]][temp_x[19]] = 'O';
            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }

        // rightwards - even
        else if ((temp_y[18] == 0 || temp_y[18] == 4 || temp_y[18] == 2 || temp_y[18] == 6) && temp_x[18] != 3 && temp_box1[temp_y[18]][temp_x[18]] == 'O' && temp_box1[temp_y[19]][temp_x[19]] == ' ' && temp_x[18] + 1 == temp_x[19])
        {
            temp_box1[temp_y[19]][temp_x[19]] = 'O';
            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }

        // leftwards - even
        else if ((temp_y[18] == 0 || temp_y[18] == 4 || temp_y[18] == 2) && temp_box1[temp_y[18]][temp_x[18]] == 'O' && temp_box1[temp_y[19]][temp_x[19]] == ' ' && temp_x[18] == temp_x[19])
        {
            temp_box1[temp_y[19]][temp_x[19]] = 'O';
            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }
    }

    for (short int t = 0; t < 4; t++)
    {
        if (temp_box1[0][t] == 'o')
        {
            temp_box1[0][t] = 'O';
        }
    }

    // checking for future player knock

    bool future_knock{false};

    for (int a = 0; a < 8; a++)
    {
        for (int b = 0; b < 4; b++)
        {
            // checking upwards
            if ((a == 0 || a == 2 || a == 4) && b != 3 && (temp_box1[a + 1][b + 1] == 'o' || temp_box1[a + 1][b + 1] == 'O') &&
                (temp_box1[a + 2][b + 1] == ' ' || temp_box1[a + 2][b + 1] == '.') && (temp_box1[a][b] == 'x' || temp_box1[a][b] == 'X'))
            {
                future_knock = true;
            }
            if ((a == 0 || a == 2 || a == 4) && b != 0 && (temp_box1[a + 1][b] == 'o' || temp_box1[a + 1][b] == 'O') &&
                (temp_box1[a + 2][b - 1] == ' ' || temp_box1[a + 2][b - 1] == '.') && (temp_box1[a][b] == 'x' || temp_box1[a][b] == 'X'))
            {
                future_knock = true;
            }
            if ((a == 1 || a == 3 || a == 5) && b != 3 && (temp_box1[a + 1][b] == 'o' || temp_box1[a + 1][b] == 'O') &&
                (temp_box1[a + 2][b + 1] == ' ' || temp_box1[a + 2][b + 1] == '.') && (temp_box1[a][b] == 'x' || temp_box1[a][b] == 'X'))
            {
                future_knock = true;
            }
            if ((a == 1 || a == 3 || a == 5) && b != 0 && (temp_box1[a + 1][b - 1] == 'o' || temp_box1[a + 1][b - 1] == 'O') &&
                (temp_box1[a + 2][b - 1] == ' ' || temp_box1[a + 2][b - 1] == '.') && (temp_box1[a][b] == 'x' || temp_box1[a][b] == 'X'))
            {
                future_knock = true;
            }

            // checking downwards
            if ((a == 6 || a == 2 || a == 4) && b != 3 && (temp_box1[a - 1][b + 1] == 'o' || temp_box1[a - 1][b + 1] == 'O') &&
                (temp_box1[a - 2][b + 1] == ' ' || temp_box1[a - 2][b + 1] == '.') && temp_box1[a][b] == 'X')
            {
                future_knock = true;
            }
            if ((a == 6 || a == 2 || a == 4) && b != 0 && (temp_box1[a - 1][b] == 'o' || temp_box1[a - 1][b] == 'O') &&
                (temp_box1[a - 2][b - 1] == ' ' || temp_box1[a - 2][b - 1] == '.') && temp_box1[a][b] == 'X')
            {
                future_knock = true;
            }
            if ((a == 7 || a == 3 || a == 5) && b != 3 && (temp_box1[a - 1][b] == 'o' || temp_box1[a - 1][b] == 'O') &&
                (temp_box1[a - 2][b + 1] == ' ' || temp_box1[a - 2][b + 1] == '.') && temp_box1[a][b] == 'X')
            {
                future_knock = true;
            }
            if ((a == 7 || a == 3 || a == 5) && b != 0 && (temp_box1[a - 1][b - 1] == 'o' || temp_box1[a - 1][b - 1] == 'O') &&
                (temp_box1[a - 2][b - 1] == ' ' || temp_box1[a - 2][b - 1] == '.') && temp_box1[a][b] == 'X')
            {
                future_knock = true;
            }
        }
    }

    return future_knock;
}

int maxKnocks_comp()
{
    int max_knocks{};

    for (short int re_do = 0; re_do < 51; re_do++)
    {

        int total_knocks{};

        for (short int m{}; m < 8; m++)
        {
            for (short int n{}; n < 4; n++)
            {
                temp_box1[m][n] = box[m][n];
            }
        }

        temp_y[18] = y[0];
        temp_x[18] = x[0];

        const unsigned short int initial_Y = y[0];
        const unsigned short int initial_X = x[0];

        for (temp_y[19] = 0; temp_y[19] < 8; temp_y[19]++)
        {
            const unsigned short int temp_y19 = temp_y[19];

            for (temp_x[19] = 0; temp_x[19] < 4; temp_x[19]++)
            {
                const unsigned short int temp_x19 = temp_x[19];

                bool knock_present{false};
                bool proceed{false};

                do
                {
                    // std::cout << ".";
                    // moving up with knock
                    if (temp_y[18] + 2 == temp_y[19] && temp_box1[temp_y[18]][temp_x[18]] == 'O')
                    {
                        if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'X') &&
                            (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                        {
                            proceed = true;
                            temp_box1[temp_y[19]][temp_x[19]] = 'O';
                            temp_box1[temp_y[18]][temp_x[18]] = '.';
                            temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                        }
                        else if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') &&
                                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                        {
                            proceed = true;
                            temp_box1[temp_y[19]][temp_x[19]] = 'O';
                            temp_box1[temp_y[18]][temp_x[18]] = '.';
                            temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') &&
                                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                        {
                            proceed = true;
                            temp_box1[temp_y[19]][temp_x[19]] = 'O';
                            temp_box1[temp_y[18]][temp_x[18]] = '.';
                            temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'X') &&
                                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                        {
                            proceed = true;
                            temp_box1[temp_y[19]][temp_x[19]] = 'O';
                            temp_box1[temp_y[18]][temp_x[18]] = '.';
                            temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                        }
                    }
                    // moving down with knock
                    else if (temp_y[18] - 2 == temp_y[19])
                    {
                        if ((temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X') &&
                            (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                        {
                            proceed = true;
                            if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
                            {
                                temp_box1[temp_y[19]][temp_x[19]] = 'O';
                            }
                            else
                            {
                                temp_box1[temp_y[19]][temp_x[19]] = 'o';
                            }
                            temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                            temp_box1[temp_y[18]][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') &&
                                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                        {
                            proceed = true;
                            if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
                            {
                                temp_box1[temp_y[19]][temp_x[19]] = 'O';
                            }
                            else
                            {
                                temp_box1[temp_y[19]][temp_x[19]] = 'o';
                            }
                            temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                            temp_box1[temp_y[18]][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') &&
                                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                        {
                            proceed = true;
                            if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
                            {
                                temp_box1[temp_y[19]][temp_x[19]] = 'O';
                            }
                            else
                            {
                                temp_box1[temp_y[19]][temp_x[19]] = 'o';
                            }
                            temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                            temp_box1[temp_y[18]][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'X') &&
                                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                        {
                            proceed = true;
                            if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
                            {
                                temp_box1[temp_y[19]][temp_x[19]] = 'O';
                            }
                            else
                            {
                                temp_box1[temp_y[19]][temp_x[19]] = 'o';
                            }
                            temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                            temp_box1[temp_y[18]][temp_x[18]] = '.';
                        }
                    }

                    if (proceed)
                    {
                        total_knocks++;

                        temp_y[18] = temp_y[19];
                        temp_x[18] = temp_x[19];

                        if (total_knocks > max_knocks)
                        {
                            max_knocks = total_knocks;

                            for (short int m{}; m < 8; m++)
                            {
                                for (short int n{}; n < 4; n++)
                                {
                                    temp_box2[m][n] = temp_box1[m][n];
                                }
                            }
                        }
                        // king
                        for (short int i = 0; i < 4; i++)
                        {
                            if (temp_box1[0][i] == 'o')
                            {
                                temp_box1[0][i] = 'O';
                                temp_box2[0][i] = 'O';
                            }
                        }

                        knock_present = future_more_knocks();
                    }

                } while (knock_present);

                total_knocks = 0;

                temp_y[18] = initial_Y;
                temp_x[18] = initial_X;

                for (short int m{}; m < 8; m++)
                {
                    for (short int n{}; n < 4; n++)
                    {
                        temp_box1[m][n] = box[m][n];
                    }
                }

                temp_x[19] = temp_x19;
            }

            temp_y[19] = temp_y19;
        }
    }

    return max_knocks;
}

bool future_more_knocks()
{
    bool knock_present{false};

    choice[0] = rand() % 8;

    if (choice[1] == choice[0])
    {
        choice[0]++;
        if (choice[0] == 8)
            choice[0] = 0;
    }

    choice[1] = choice[0];

    if (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o')
    {
        unsigned short int count{};

        while (count < 8)
        {
            // downwards

            if (choice[0] == 0 && (temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X') &&
                (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] - 1] == '.') && (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o'))
            {
                knock_present = true;
                temp_y[19] = temp_y[18] - 2;
                temp_x[19] = temp_x[18] - 1;
                break;
            }
            if (choice[0] == 1 && (temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') &&
                (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] + 1] == '.') && (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o'))
            {
                knock_present = true;
                temp_y[19] = temp_y[18] - 2;
                temp_x[19] = temp_x[18] + 1;
                break;
            }
            if (choice[0] == 2 && (temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') &&
                (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] - 1] == '.') && (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o'))
            {
                knock_present = true;
                temp_y[19] = temp_y[18] - 2;
                temp_x[19] = temp_x[18] - 1;
                break;
            }
            if (choice[0] == 3 && (temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'X') &&
                (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] + 1] == '.') && (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o'))
            {
                knock_present = true;
                temp_y[19] = temp_y[18] - 2;
                temp_x[19] = temp_x[18] + 1;
                break;
            }

            // upwards

            if (choice[0] == 4 && (temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'X') &&
                (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] - 1] == '.') && temp_box1[temp_y[18]][temp_x[18]] == 'O')
            {
                knock_present = true;
                temp_y[19] = temp_y[18] + 2;
                temp_x[19] = temp_x[18] - 1;
                break;
            }
            if (choice[0] == 5 && (temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') &&
                (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] + 1] == '.') && temp_box1[temp_y[18]][temp_x[18]] == 'O')
            {
                knock_present = true;
                temp_y[19] = temp_y[18] + 2;
                temp_x[19] = temp_x[18] + 1;
                break;
            }
            if (choice[0] == 6 && (temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') &&
                (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] - 1] == '.') && temp_box1[temp_y[18]][temp_x[18]] == 'O')
            {
                knock_present = true;
                temp_y[19] = temp_y[18] + 2;
                temp_x[19] = temp_x[18] - 1;
                break;
            }
            if (choice[0] == 7 && (temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'X') &&
                (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] + 1] == '.') && temp_box1[temp_y[18]][temp_x[18]] == 'O')
            {
                knock_present = true;
                temp_y[19] = temp_y[18] + 2;
                temp_x[19] = temp_x[18] + 1;
                break;
            }

            count++;
            choice[0]++;
            if (choice[0] == 8)
                choice[0] = 0;
        }
    }

    else if (temp_box1[temp_y[18]][temp_x[18]] == 'X' || temp_box1[temp_y[18]][temp_x[18]] == 'x')
    {
        unsigned short int count{};

        while (count < 8)
        {
            // upwards

            if (choice[0] == 0 && (temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'o' || temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O') &&
                (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] - 1] == '.') && (temp_box1[temp_y[18]][temp_x[18]] == 'x' || temp_box1[temp_y[18]][temp_x[18]] == 'X'))
            {
                knock_present = true;
                temp_y[19] = temp_y[18] + 2;
                temp_x[19] = temp_x[18] - 1;
                break;
            }
            if (choice[0] == 1 && (temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'o' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'O') &&
                (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] + 1] == '.') && (temp_box1[temp_y[18]][temp_x[18]] == 'x' || temp_box1[temp_y[18]][temp_x[18]] == 'X'))
            {
                knock_present = true;
                temp_y[19] = temp_y[18] + 2;
                temp_x[19] = temp_x[18] + 1;
                break;
            }
            if (choice[0] == 2 && (temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'o' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'O') &&
                (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] - 1] == '.') && (temp_box1[temp_y[18]][temp_x[18]] == 'x' || temp_box1[temp_y[18]][temp_x[18]] == 'X'))
            {
                knock_present = true;
                temp_y[19] = temp_y[18] + 2;
                temp_x[19] = temp_x[18] - 1;
                break;
            }
            if (choice[0] == 3 && (temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'o' || temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'O') &&
                (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] + 1] == '.') && (temp_box1[temp_y[18]][temp_x[18]] == 'x' || temp_box1[temp_y[18]][temp_x[18]] == 'X'))
            {
                knock_present = true;
                temp_y[19] = temp_y[18] + 2;
                temp_x[19] = temp_x[18] + 1;
                break;
            }

            // downwards

            if (choice[0] == 4 && (temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O') &&
                (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] - 1] == '.') && temp_box1[temp_y[18]][temp_x[18]] == 'X')
            {
                knock_present = true;
                temp_y[19] = temp_y[18] - 2;
                temp_x[19] = temp_x[18] - 1;
                break;
            }
            if (choice[0] == 5 && (temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'O') &&
                (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] + 1] == '.') && temp_box1[temp_y[18]][temp_x[18]] == 'X')
            {
                knock_present = true;
                temp_y[19] = temp_y[18] - 2;
                temp_x[19] = temp_x[18] + 1;
                break;
            }
            if (choice[0] == 6 && (temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'O') &&
                (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] - 1] == '.') && temp_box1[temp_y[18]][temp_x[18]] == 'X')
            {
                knock_present = true;
                temp_y[19] = temp_y[18] - 2;
                temp_x[19] = temp_x[18] - 1;
                break;
            }
            if (choice[0] == 7 && (temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'O') &&
                (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] + 1] == '.') && temp_box1[temp_y[18]][temp_x[18]] == 'X')
            {
                knock_present = true;
                temp_y[19] = temp_y[18] - 2;
                temp_x[19] = temp_x[18] + 1;
                break;
            }

            count++;
            choice[0]++;
            if (choice[0] == 8)
                choice[0] = 0;
        }
    }

    return knock_present;
}

int maxKnocks_player()
{
    int max_knocks{};

    for (short int re_do = 0; re_do < 51; re_do++)
    {
        for (temp_y[18] = 0; temp_y[18] < 8; temp_y[18]++)
        {
            for (temp_x[18] = 0; temp_x[18] < 4; temp_x[18]++)
            {
                for (short int m{}; m < 8; m++)
                {
                    for (short int n{}; n < 4; n++)
                    {
                        temp_box1[m][n] = temp_box2[m][n];
                    }
                }

                if (temp_box1[temp_y[18]][temp_x[18]] == 'x' || temp_box1[temp_y[18]][temp_x[18]] == 'X')
                {
                    const unsigned short int initial_Y = temp_y[18];
                    const unsigned short int initial_X = temp_x[18];

                    int total_knocks{};

                    for (temp_y[19] = 0; temp_y[19] < 8; temp_y[19]++)
                    {
                        const unsigned short int temp_y19 = temp_y[19];

                        for (temp_x[19] = 0; temp_x[19] < 4; temp_x[19]++)
                        {
                            const unsigned short int temp_x19 = temp_x[19];

                            bool knock_present{false};
                            bool proceed{false};

                            do
                            {
                                // moving up with knock

                                if (temp_y[18] + 2 == temp_y[19])
                                {
                                    if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'o' || temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O') &&
                                        (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                                    {
                                        proceed = true;

                                        if (temp_box1[temp_y[18]][temp_x[18]] == 'X')
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'X';
                                        }
                                        else
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'x';
                                        }
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                        temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                                    }
                                    else if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'o' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'O') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                                    {
                                        proceed = true;

                                        if (temp_box1[temp_y[18]][temp_x[18]] == 'X')
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'X';
                                        }
                                        else
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'x';
                                        }
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                                    }
                                    else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'o' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'O') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                                    {
                                        proceed = true;

                                        if (temp_box1[temp_y[18]][temp_x[18]] == 'X')
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'X';
                                        }
                                        else
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'x';
                                        }
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                                    }
                                    else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'o' || temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'O') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                                    {
                                        proceed = true;

                                        if (temp_box1[temp_y[18]][temp_x[18]] == 'X')
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'X';
                                        }
                                        else
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'x';
                                        }
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                        temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                                    }
                                }

                                // moving down with knock

                                else if (temp_y[18] - 2 == temp_y[19] && temp_box1[temp_y[18]][temp_x[18]] == 'X')
                                {
                                    if ((temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O') &&
                                        (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                                    {
                                        proceed = true;
                                        temp_box1[temp_y[19]][temp_x[19]] = 'X';
                                        temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                    }
                                    else if ((temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'O') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                                    {
                                        proceed = true;
                                        temp_box1[temp_y[19]][temp_x[19]] = 'X';
                                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                    }
                                    else if ((temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'O') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                                    {
                                        proceed = true;
                                        temp_box1[temp_y[19]][temp_x[19]] = 'X';
                                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                    }
                                    else if ((temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'O') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                                    {
                                        proceed = true;
                                        temp_box1[temp_y[19]][temp_x[19]] = 'X';
                                        temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                    }
                                }

                                if (proceed)
                                {
                                    total_knocks++;

                                    temp_y[18] = temp_y[19];
                                    temp_x[18] = temp_x[19];

                                    if (total_knocks > max_knocks)
                                    {
                                        max_knocks = total_knocks;

                                        for (short int s = 0; s < 8; s++)
                                        {
                                            for (short int t = 0; t < 4; t++)
                                            {
                                                temp_box3[s][t] = temp_box1[s][t];
                                            }
                                        }
                                    }

                                    // king
                                    for (short int t = 0; t < 4; t++)
                                    {
                                        if (temp_box1[7][t] == 'x')
                                        {
                                            temp_box1[7][t] = 'X';
                                            temp_box3[7][t] = 'X';
                                        }
                                    }

                                    knock_present = future_more_knocks();
                                }

                            } while (knock_present);

                            total_knocks = 0;

                            temp_y[18] = initial_Y;
                            temp_x[18] = initial_X;

                            for (short int m{}; m < 8; m++)
                            {
                                for (short int n{}; n < 4; n++)
                                {
                                    temp_box1[m][n] = temp_box2[m][n];
                                }
                            }

                            temp_x[19] = temp_x19;
                        }

                        temp_y[19] = temp_y19;
                    }
                }
            }
        }
    }

    return max_knocks;
}

bool playersKnock_remove()
{
    bool removed_knock{false};
    short int count{};

    if (play_mode != 3)
    {
        for (short int s = 0; s < 8; s++)
        {
            for (short int t = 0; t < 4; t++)
            {
                temp_box1[s][t] = box[s][t];
            }
        }

        for (int a = 0; a < 8; a++)
        {
            for (int b = 0; b < 4; b++)
            {
                if ((a == 0 || a == 2 || a == 4) && b != 3 && (temp_box1[a + 1][b + 1] == 'o' || temp_box1[a + 1][b + 1] == 'O') &&
                    (temp_box1[a + 2][b + 1] == ' ' || temp_box1[a + 2][b + 1] == '.') && (temp_box1[a][b] == 'x' || temp_box1[a][b] == 'X'))
                {
                    temp_y[count] = a;
                    temp_x[count] = b;
                    y1_store[count] = a + 2;
                    x1_store[count] = b + 1;
                    count++;
                }
                if ((a == 0 || a == 2 || a == 4) && b != 0 && (temp_box1[a + 1][b] == 'o' || temp_box1[a + 1][b] == 'O') &&
                    (temp_box1[a + 2][b - 1] == ' ' || temp_box1[a + 2][b - 1] == '.') && (temp_box1[a][b] == 'x' || temp_box1[a][b] == 'X'))
                {
                    temp_y[count] = a;
                    temp_x[count] = b;
                    y1_store[count] = a + 2;
                    x1_store[count] = b - 1;
                    count++;
                }
                if ((a == 1 || a == 3 || a == 5) && b != 3 && (temp_box1[a + 1][b] == 'o' || temp_box1[a + 1][b] == 'O') &&
                    (temp_box1[a + 2][b + 1] == ' ' || temp_box1[a + 2][b + 1] == '.') && (temp_box1[a][b] == 'x' || temp_box1[a][b] == 'X'))
                {
                    temp_y[count] = a;
                    temp_x[count] = b;
                    y1_store[count] = a + 2;
                    x1_store[count] = b + 1;
                    count++;
                }
                if ((a == 1 || a == 3 || a == 5) && b != 0 && (temp_box1[a + 1][b - 1] == 'o' || temp_box1[a + 1][b - 1] == 'O') &&
                    (temp_box1[a + 2][b - 1] == ' ' || temp_box1[a + 2][b - 1] == '.') && (temp_box1[a][b] == 'x' || temp_box1[a][b] == 'X'))
                {
                    temp_y[count] = a;
                    temp_x[count] = b;
                    y1_store[count] = a + 2;
                    x1_store[count] = b - 1;
                    count++;
                }

                if ((a == 6 || a == 2 || a == 4) && b != 3 && (temp_box1[a - 1][b + 1] == 'o' || temp_box1[a - 1][b + 1] == 'O') &&
                    (temp_box1[a - 2][b + 1] == ' ' || temp_box1[a - 2][b + 1] == '.') && temp_box1[a][b] == 'X')
                {
                    temp_y[count] = a;
                    temp_x[count] = b;
                    y1_store[count] = a - 2;
                    x1_store[count] = b + 1;
                    count++;
                }
                if ((a == 6 || a == 2 || a == 4) && b != 0 && (temp_box1[a - 1][b] == 'o' || temp_box1[a - 1][b] == 'O') &&
                    (temp_box1[a - 2][b - 1] == ' ' || temp_box1[a - 2][b - 1] == '.') && temp_box1[a][b] == 'X')
                {
                    temp_y[count] = a;
                    temp_x[count] = b;
                    y1_store[count] = a - 2;
                    x1_store[count] = b - 1;
                    count++;
                }
                if ((a == 7 || a == 3 || a == 5) && b != 3 && (temp_box1[a - 1][b] == 'o' || temp_box1[a - 1][b] == 'O') &&
                    (temp_box1[a - 2][b + 1] == ' ' || temp_box1[a - 2][b + 1] == '.') && temp_box1[a][b] == 'X')
                {
                    temp_y[count] = a;
                    temp_x[count] = b;
                    y1_store[count] = a - 2;
                    x1_store[count] = b + 1;
                    count++;
                }
                if ((a == 7 || a == 3 || a == 5) && b != 0 && (temp_box1[a - 1][b - 1] == 'o' || temp_box1[a - 1][b - 1] == 'O') &&
                    (temp_box1[a - 2][b - 1] == ' ' || temp_box1[a - 2][b - 1] == '.') && temp_box1[a][b] == 'X')
                {
                    temp_y[count] = a;
                    temp_x[count] = b;
                    y1_store[count] = a - 2;
                    x1_store[count] = b - 1;
                    count++;
                }
            }
        }

        if (count > 0)
        {

            auto rand_num{rand() % count};

            temp_y[18] = temp_y[rand_num];
            temp_x[18] = temp_x[rand_num];
            temp_y[19] = y1_store[rand_num];
            temp_x[19] = x1_store[rand_num];
        }
    }

    if (count > 0 || play_mode == 3)
    {
        count = 0;

        // downwards rightwards... y0 --> 7
        if (temp_y[18] == 7 && temp_y[19] == temp_y[18] - 2 && temp_x[19] == temp_x[18] + 1 && temp_x[18] != 3)
        {
            if (temp_x[18] == 0)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] - 2][temp_x[18]] == ' ' && choice[0] == 0)
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] + 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18]] == 'O')
                    {
                        temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'X' &&
                             ((temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18]] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != ' ')) &&
                             (temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18]] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] + 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] + 1] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[18] == 1 || temp_x[18] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] - 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'X' &&
                        ((temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18]] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != ' ')) &&
                        (temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18]] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] + 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18]] == 'O')
                    {
                        temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'X' &&
                             ((temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18]] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != ' ')) &&
                             (temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18]] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] + 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] + 1] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        // downwards leftwards... y0 --> 7
        else if (temp_y[18] == 7 && temp_y[19] == temp_y[18] - 2 && temp_x[19] == temp_x[18] - 1 && temp_x[18] != 0)
        {
            if (temp_x[18] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' && choice[0] == 0)
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] - 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] - 1] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] - 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O')
                    {
                        temp_box1[temp_y[18]][temp_x[18] - 1] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] - 2][temp_x[18]] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X' &&
                             ((temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18] - 1] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18]] != ' ')) &&
                             (temp_box1[temp_y[18] - 1][temp_x[18]] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18]] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[18] == 2 || temp_x[18] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] - 3][temp_x[18] - 2] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18] - 2] != 'X' &&
                        ((temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18] - 1] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18] - 2] != ' ')) &&
                        (temp_box1[temp_y[18] - 1][temp_x[18] - 2] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18] - 2] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] - 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] - 1] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] - 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O')
                    {
                        temp_box1[temp_y[18]][temp_x[18] - 1] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] - 2][temp_x[18]] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X' &&
                             ((temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18] - 1] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18]] != ' ')) &&
                             (temp_box1[temp_y[18] - 1][temp_x[18]] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18]] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        // downwards rightwards... y0 --> 6/4
        else if ((temp_y[18] == 6 || temp_y[18] == 4) && temp_y[19] == temp_y[18] - 2 && temp_x[19] == temp_x[18] + 1 && temp_x[18] != 3)
        {
            if (temp_x[18] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] - 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X' &&
                        ((temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18] + 1] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != ' ')) &&
                        (temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] + 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'O')
                    {
                        temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' && choice[0] == 2)
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] + 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] + 1] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[18] == 0 || temp_x[18] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] - 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X' &&
                        ((temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18] + 1] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != ' ')) &&
                        (temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] + 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'O' && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'X' &&
                             ((temp_box1[temp_y[18] - 1][temp_x[18] + 2] != 'x' && temp_box1[temp_y[18] - 1][temp_x[18] + 2] != 'X') || ((temp_box1[temp_y[18] - 1][temp_x[18] + 2] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] + 2] == 'X') && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != ' ')) &&
                             (temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'X' || (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'X' && temp_box1[temp_y[18] - 1][temp_x[18] + 2] != ' ')))
                    {
                        temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] - 3][temp_x[18] + 2] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18] + 2] != 'X' &&
                             ((temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18] + 1] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18] + 2] != ' ')) &&
                             (temp_box1[temp_y[18] - 1][temp_x[18] + 2] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18] + 2] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] + 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] + 1] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        // downwards leftwards... y0 --> 6/4
        else if ((temp_y[18] == 6 || temp_y[18] == 4) && temp_y[19] == temp_y[18] - 2 && temp_x[19] == temp_x[18] - 1 && temp_x[18] != 0)
        {
            if (temp_x[18] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'X' &&
                        ((temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18]] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != ' ')) &&
                        (temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18]] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] - 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] - 1] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] - 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18]] == 'O' && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'X' &&
                             ((temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'X') || ((temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X') && temp_box1[temp_y[18] + 1][temp_x[18]] != ' ')) &&
                             (temp_box1[temp_y[18] + 1][temp_x[18]] != 'X' || (temp_box1[temp_y[18] + 1][temp_x[18]] == 'X' && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != ' ')))
                    {
                        temp_box1[temp_y[18]][temp_x[18] - 1] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] - 2][temp_x[18]] == ' ' && choice[0] == 2)
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[18] == 1 || temp_x[18] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'X' &&
                        ((temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18]] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != ' ')) &&
                        (temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18]] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] - 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] - 1] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] - 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18]] == 'O' && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'X' &&
                             ((temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'X') || ((temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X') && temp_box1[temp_y[18] + 1][temp_x[18]] != ' ')) &&
                             (temp_box1[temp_y[18] + 1][temp_x[18]] != 'X' || (temp_box1[temp_y[18] + 1][temp_x[18]] == 'X' && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != ' ')))
                    {
                        temp_box1[temp_y[18]][temp_x[18] - 1] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] - 2][temp_x[18]] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'X' && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'X' &&
                             ((temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18]] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != ' ')) &&
                             (temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18]] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        // downwards rightwards... y0 --> 5/3
        else if ((temp_y[18] == 5 || temp_y[18] == 3) && temp_y[19] == temp_y[18] - 2 && temp_x[19] == temp_x[18] + 1 && temp_x[18] != 3)
        {
            if (temp_x[18] == 0)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] - 2][temp_x[18]] == ' ' && choice[0] == 0)
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] + 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18]] == 'O' && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'X' &&
                             ((temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'x' && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'X') || ((temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'X') && temp_box1[temp_y[18] + 1][temp_x[18]] != ' ')) &&
                             (temp_box1[temp_y[18] + 1][temp_x[18]] != 'X' || (temp_box1[temp_y[18] + 1][temp_x[18]] == 'X' && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != ' ')))
                    {
                        temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'X' && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'x' &&
                             ((temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18]] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != ' ')) &&
                             (temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18]] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] + 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] + 1] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[18] == 1 || temp_x[18] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] - 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'X' && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'x' &&
                        ((temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18]] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != ' ')) &&
                        (temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18]] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] + 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18]] == 'O' && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'X' &&
                             ((temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'x' && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'X') || ((temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'X') && temp_box1[temp_y[18] + 1][temp_x[18]] != ' ')) &&
                             (temp_box1[temp_y[18] + 1][temp_x[18]] != 'X' || (temp_box1[temp_y[18] + 1][temp_x[18]] == 'X' && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != ' ')))
                    {
                        temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'X' && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'x' &&
                             ((temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18]] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != ' ')) &&
                             (temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18]] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] + 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] + 1] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        // downwards leftwards... y0 --> 5/3
        else if ((temp_y[18] == 5 || temp_y[18] == 3) && temp_y[19] == temp_y[18] - 2 && temp_x[19] == temp_x[18] - 1 && temp_x[18] != 0)
        {
            if (temp_x[18] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' && choice[0] == 0)
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] - 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] - 1] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] - 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O')
                    {
                        temp_box1[temp_y[18]][temp_x[18] - 1] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] - 2][temp_x[18]] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' &&
                             ((temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18] - 1] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18]] != ' ')) &&
                             (temp_box1[temp_y[18] - 1][temp_x[18]] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18]] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[18] == 2 || temp_x[18] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] - 3][temp_x[18] - 2] != 'X' && temp_box1[temp_y[18] - 3][temp_x[18] - 2] != 'x' &&
                        ((temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18]] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != ' ')) &&
                        (temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18]] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] - 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18] - 1] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] - 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O' && temp_box1[temp_y[18] + 1][temp_x[18] - 2] != 'X' && temp_box1[temp_y[18] + 1][temp_x[18] - 2] != 'x' &&
                             ((temp_box1[temp_y[18] - 1][temp_x[18] - 2] != 'x' && temp_box1[temp_y[18] - 1][temp_x[18] - 2] != 'X') || ((temp_box1[temp_y[18] - 1][temp_x[18] - 2] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] - 2] == 'X') && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != ' ')) &&
                             (temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'X' || (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'X' && temp_box1[temp_y[18] - 1][temp_x[18] - 2] != ' ')))
                    {
                        temp_box1[temp_y[18]][temp_x[18] - 1] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] - 2][temp_x[18]] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' &&
                             ((temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'X') || ((temp_box1[temp_y[18] - 3][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 3][temp_x[18] - 1] == 'X') && temp_box1[temp_y[18] - 1][temp_x[18]] != ' ')) &&
                             (temp_box1[temp_y[18] - 1][temp_x[18]] != 'X' || (temp_box1[temp_y[18] - 1][temp_x[18]] == 'X' && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != ' ')))
                    {
                        if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'O';
                        }
                        else if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'o')
                        {
                            temp_box1[temp_y[18] - 2][temp_x[18]] = 'o';
                        }

                        temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        // downwards rightwards... y0 --> 2
        else if (temp_y[18] == 2 && temp_y[19] == temp_y[18] - 2 && temp_x[19] == temp_x[18] + 1 && temp_x[18] != 3)
        {
            if (temp_x[18] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] - 2][temp_x[18]] == ' ' && choice[0] == 0)
                    {
                        temp_box1[temp_y[18] - 2][temp_x[18]] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] + 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'O')
                    {
                        temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' && choice[0] == 2)
                    {
                        temp_box1[temp_y[18] - 2][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[18] == 0 || temp_x[18] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] - 2][temp_x[18]] == ' ' && choice[0] == 0)
                    {
                        temp_box1[temp_y[18] - 2][temp_x[18]] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] + 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'O' && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'X' &&
                             ((temp_box1[temp_y[18] - 1][temp_x[18] + 2] != 'x' && temp_box1[temp_y[18] - 1][temp_x[18] + 2] != 'X') || ((temp_box1[temp_y[18] - 1][temp_x[18] + 2] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] + 2] == 'X') && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != ' ')) &&
                             (temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'X' || (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'X' && temp_box1[temp_y[18] - 1][temp_x[18] + 2] != ' ')))
                    {
                        temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' && choice[0] == 2)
                    {
                        temp_box1[temp_y[18] - 2][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        // downwards leftwards... y0 --> 2
        else if (temp_y[18] == 2 && temp_y[19] == temp_y[18] - 2 && temp_x[19] == temp_x[18] - 1 && temp_x[18] != 0)
        {
            choice[0] = rand() % 3;

            do
            {
                if (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' && choice[0] == 0)
                {
                    temp_box1[temp_y[18] - 2][temp_x[18] - 1] = 'O';
                    temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                    removed_knock = true;
                }
                else if (temp_box1[temp_y[18]][temp_x[18] - 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18]] == 'O' && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'X' &&
                         ((temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'X') || ((temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X') && temp_box1[temp_y[18] + 1][temp_x[18]] != ' ')) &&
                         (temp_box1[temp_y[18] + 1][temp_x[18]] != 'X' || (temp_box1[temp_y[18] + 1][temp_x[18]] == 'X' && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != ' ')))
                {
                    temp_box1[temp_y[18]][temp_x[18] - 1] = 'O';
                    temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                    removed_knock = true;
                }
                else if (temp_box1[temp_y[18] - 2][temp_x[18]] == ' ' && choice[0] == 2)
                {
                    temp_box1[temp_y[18] - 2][temp_x[18]] = 'O';
                    temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                    removed_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;

            } while (count < 4 && !removed_knock);
        }

        //  upwards rightwards --> 0
        else if (temp_y[18] == 0 && temp_y[19] == temp_y[18] + 2 && temp_x[19] == temp_x[18] + 1 && temp_x[18] != 3)
        {
            if (temp_x[18] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] + 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] + 3][temp_x[18]] != 'X' &&
                        ((temp_box1[temp_y[18] + 1][temp_x[18]] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18] + 1] != ' ')) &&
                        (temp_box1[temp_y[18] + 3][temp_x[18] + 1] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18] + 1] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18]] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18]] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] + 1] == ' ' && choice[0] == 1)
                    {
                        temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'O')
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[18] == 0 || temp_x[18] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] + 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] + 3][temp_x[18]] != 'X' &&
                        ((temp_box1[temp_y[18] + 1][temp_x[18]] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18] + 1] != ' ')) &&
                        (temp_box1[temp_y[18] + 3][temp_x[18] + 1] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18] + 1] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18]] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18]] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] + 1] == ' ' && choice[0] == 1)
                    {
                        temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18] + 2] != 'X' &&
                             ((temp_box1[temp_y[18] + 1][temp_x[18] + 2] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18] + 2] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18] + 2] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] + 2] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18] + 1] != ' ')) &&
                             (temp_box1[temp_y[18] + 3][temp_x[18] + 1] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18] + 1] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18] + 2] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        //  upwards leftwards --> 0
        else if (temp_y[18] == 0 && temp_y[19] == temp_y[18] + 2 && temp_x[19] == temp_x[18] - 1 && temp_x[18] != 0)
        {
            if (temp_x[18] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] + 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] + 1][temp_x[18]] == 'O')
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18]] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] - 1] == ' ' && choice[0] == 1)
                    {
                        temp_box1[temp_y[18]][temp_x[18] - 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] + 1][temp_x[18]] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18] - 1] != 'X' &&
                             ((temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18]] != ' ')) &&
                             (temp_box1[temp_y[18] + 3][temp_x[18]] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18]] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18] - 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[18] == 1 || temp_x[18] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] + 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] + 1][temp_x[18]] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18] + 1] != 'X' &&
                        ((temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18]] != ' ')) &&
                        (temp_box1[temp_y[18] + 3][temp_x[18]] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18]] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18]] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] - 1] == ' ' && choice[0] == 1)
                    {
                        temp_box1[temp_y[18]][temp_x[18] - 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] + 1][temp_x[18]] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18] - 1] != 'X' &&
                             ((temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18]] != ' ')) &&
                             (temp_box1[temp_y[18] + 3][temp_x[18]] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18]] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18] - 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        //  upwards rightwards --> 1/3
        else if ((temp_y[18] == 1 || temp_y[18] == 3) && temp_y[19] == temp_y[18] + 2 && temp_x[19] == temp_x[18] + 1 && temp_x[18] != 3)
        {
            if (temp_x[18] == 0)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] + 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] + 1][temp_x[18]] == 'O')
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18]] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] + 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'X' && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'x' &&
                             ((temp_box1[temp_y[18] - 1][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 1][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != ' ')) &&
                             (temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'X' || (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'X' && temp_box1[temp_y[18] - 1][temp_x[18]] != ' ')))
                    {
                        if (temp_box1[temp_y[18] + 1][temp_x[18]] == 'O')
                        {

                            temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] + 1][temp_x[18]] == 'o')
                        {

                            temp_box1[temp_y[18]][temp_x[18] + 1] = 'o';
                        }

                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] + 1][temp_x[18]] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18] + 1] != 'X' &&
                             ((temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18]] != ' ')) &&
                             (temp_box1[temp_y[18] + 3][temp_x[18]] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18]] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[18] == 1 || temp_x[18] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] + 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] + 1][temp_x[18]] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18] - 1] != 'X' &&
                        ((temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18]] != ' ')) &&
                        (temp_box1[temp_y[18] + 3][temp_x[18]] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18]] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18]] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] + 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'X' && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'x' &&
                             ((temp_box1[temp_y[18] - 1][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 1][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != ' ')) &&
                             (temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'X' || (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'X' && temp_box1[temp_y[18] - 1][temp_x[18]] != ' ')))
                    {
                        if (temp_box1[temp_y[18] + 1][temp_x[18]] == 'O')
                        {

                            temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] + 1][temp_x[18]] == 'o')
                        {

                            temp_box1[temp_y[18]][temp_x[18] + 1] = 'o';
                        }

                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] + 1][temp_x[18]] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18] + 1] != 'X' &&
                             ((temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18]] != ' ')) &&
                             (temp_box1[temp_y[18] + 3][temp_x[18]] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18]] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        //  upwards leftwards --> 1/3
        else if ((temp_y[18] == 1 || temp_y[18] == 3) && temp_y[19] == temp_y[18] + 2 && temp_x[19] == temp_x[18] - 1 && temp_x[18] != 0)
        {
            if (temp_x[18] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] + 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18]] != 'X' &&
                        ((temp_box1[temp_y[18] + 1][temp_x[18]] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18] - 1] != ' ')) &&
                        (temp_box1[temp_y[18] + 3][temp_x[18] - 1] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18] - 1] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18]] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18]] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] - 1] == ' ' && choice[0] == 1)
                    {
                        if (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O')
                        {

                            temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'o')
                        {

                            temp_box1[temp_y[18]][temp_x[18] + 1] = 'o';
                        }

                        temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O')
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18] - 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[18] == 2 || temp_x[18] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] + 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18]] != 'X' &&
                        ((temp_box1[temp_y[18] + 1][temp_x[18]] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18] - 1] != ' ')) &&
                        (temp_box1[temp_y[18] + 3][temp_x[18] - 1] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18] - 1] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18]] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18]] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] - 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] - 2] != 'X' && temp_box1[temp_y[18] - 1][temp_x[18] - 2] != 'x' &&
                             ((temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'X') || ((temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X') && temp_box1[temp_y[18] + 1][temp_x[18] - 2] != ' ')) &&
                             (temp_box1[temp_y[18] + 1][temp_x[18] - 2] != 'X' || (temp_box1[temp_y[18] + 1][temp_x[18] - 2] == 'X' && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != ' ')))
                    {
                        if (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O')
                        {

                            temp_box1[temp_y[18]][temp_x[18] - 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'o')
                        {

                            temp_box1[temp_y[18]][temp_x[18] - 1] = 'o';
                        }

                        temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18] - 2] != 'X' &&
                             ((temp_box1[temp_y[18] + 1][temp_x[18] - 2] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18] - 2] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18] - 2] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] - 2] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18] - 1] != ' ')) &&
                             (temp_box1[temp_y[18] + 3][temp_x[18] - 1] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18] - 1] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18] - 2] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18] - 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        //  upwards rightwards --> 2/4
        else if ((temp_y[18] == 2 || temp_y[18] == 4) && temp_y[19] == temp_y[18] + 2 && temp_x[19] == temp_x[18] + 1 && temp_x[18] != 3)
        {
            if (temp_x[18] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] + 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18]] != 'X' &&
                        ((temp_box1[temp_y[18] + 1][temp_x[18]] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18] + 1] != ' ')) &&
                        (temp_box1[temp_y[18] + 3][temp_x[18] + 1] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18] + 1] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18]] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18]] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] + 1] == ' ' && choice[0] == 1)
                    {
                        if (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'O')
                        {

                            temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'o')
                        {

                            temp_box1[temp_y[18]][temp_x[18] + 1] = 'o';
                        }

                        temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'O')
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[18] == 1 || temp_x[18] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] + 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18]] != 'X' &&
                        ((temp_box1[temp_y[18] + 1][temp_x[18]] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18] + 1] != ' ')) &&
                        (temp_box1[temp_y[18] + 3][temp_x[18] + 1] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18] + 1] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18]] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18]] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] + 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] + 2] != 'X' && temp_box1[temp_y[18] - 1][temp_x[18] + 2] != 'x' &&
                             ((temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'x' && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'X') || ((temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'X') && temp_box1[temp_y[18] + 1][temp_x[18] + 2] != ' ')) &&
                             (temp_box1[temp_y[18] + 1][temp_x[18] + 2] != 'X' || (temp_box1[temp_y[18] + 1][temp_x[18] + 2] == 'X' && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != ' ')))
                    {
                        if (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'O')
                        {

                            temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'o')
                        {

                            temp_box1[temp_y[18]][temp_x[18] + 1] = 'o';
                        }

                        temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18] + 2] != 'X' &&
                             ((temp_box1[temp_y[18] + 1][temp_x[18] + 2] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18] + 2] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18] + 2] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] + 2] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18] + 1] != ' ')) &&
                             (temp_box1[temp_y[18] + 3][temp_x[18] + 1] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18] + 1] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18] + 2] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18] + 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        //  upwards leftwards --> 2/4
        else if ((temp_y[18] == 2 || temp_y[18] == 4) && temp_y[19] == temp_y[18] + 2 && temp_x[19] == temp_x[18] - 1 && temp_x[18] != 0)
        {
            if (temp_x[18] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] + 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] + 1][temp_x[18]] == 'O')
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18]] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] - 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'X' && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'x' &&
                             ((temp_box1[temp_y[18] - 1][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 1][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != ' ')) &&
                             (temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'X' || (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'X' && temp_box1[temp_y[18] - 1][temp_x[18]] != ' ')))
                    {
                        if (temp_box1[temp_y[18] + 1][temp_x[18]] == 'O')
                        {

                            temp_box1[temp_y[18]][temp_x[18] - 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] + 1][temp_x[18]] == 'o')
                        {

                            temp_box1[temp_y[18]][temp_x[18] - 1] = 'o';
                        }

                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] + 1][temp_x[18]] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18] - 1] != 'X' &&
                             ((temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18]] != ' ')) &&
                             (temp_box1[temp_y[18] + 3][temp_x[18]] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18]] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18] - 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[18] == 1 || temp_x[18] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] + 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] + 1][temp_x[18]] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18] + 1] != 'X' &&
                        ((temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18]] != ' ')) &&
                        (temp_box1[temp_y[18] + 3][temp_x[18]] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18]] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18]] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] - 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'X' && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'x' &&
                             ((temp_box1[temp_y[18] - 1][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 1][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != ' ')) &&
                             (temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'X' || (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'X' && temp_box1[temp_y[18] - 1][temp_x[18]] != ' ')))
                    {
                        if (temp_box1[temp_y[18] + 1][temp_x[18]] == 'O')
                        {

                            temp_box1[temp_y[18]][temp_x[18] - 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] + 1][temp_x[18]] == 'o')
                        {

                            temp_box1[temp_y[18]][temp_x[18] - 1] = 'o';
                        }

                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] + 1][temp_x[18]] == 'O' && temp_box1[temp_y[18] + 3][temp_x[18] - 1] != 'X' &&
                             ((temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'X') || ((temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'X') && temp_box1[temp_y[18] + 3][temp_x[18]] != ' ')) &&
                             (temp_box1[temp_y[18] + 3][temp_x[18]] != 'X' || (temp_box1[temp_y[18] + 3][temp_x[18]] == 'X' && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != ' ')))
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18] - 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        //  upwards rightwards --> 5
        else if (temp_y[18] == 5 && temp_y[19] == temp_y[18] + 2 && temp_x[19] == temp_x[18] + 1 && temp_x[18] != 3)
        {
            choice[0] = rand() % 3;

            do
            {
                if (temp_box1[temp_y[18] + 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] + 1][temp_x[18]] == 'O')
                {
                    temp_box1[temp_y[18] + 2][temp_x[18]] = 'O';
                    temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                    removed_knock = true;
                }
                else if (temp_box1[temp_y[18]][temp_x[18] + 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'X' && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'x' &&
                         ((temp_box1[temp_y[18] - 1][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 1][temp_x[18]] != 'X') || ((temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != ' ')) &&
                         (temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'X' || (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'X' && temp_box1[temp_y[18] - 1][temp_x[18]] != ' ')))
                {
                    if (temp_box1[temp_y[18] + 1][temp_x[18]] == 'O')
                    {

                        temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                    }
                    else if (temp_box1[temp_y[18] + 1][temp_x[18]] == 'o')
                    {

                        temp_box1[temp_y[18]][temp_x[18] + 1] = 'o';
                    }

                    temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                    removed_knock = true;
                }
                else if (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] + 1][temp_x[18]] == 'O')
                {
                    temp_box1[temp_y[18] + 2][temp_x[18] + 1] = 'O';
                    temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                    removed_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;

            } while (count < 4 && !removed_knock);
        }

        //  upwards leftwards --> 5
        else if (temp_y[18] == 5 && temp_y[19] == temp_y[18] + 2 && temp_x[19] == temp_x[18] - 1 && temp_x[18] != 0)
        {
            if (temp_x[18] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] + 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O')
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18]] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] - 1] == ' ' && choice[0] == 1)
                    {
                        if (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O')
                        {

                            temp_box1[temp_y[18]][temp_x[18] + 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'o')
                        {

                            temp_box1[temp_y[18]][temp_x[18] + 1] = 'o';
                        }

                        temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O')
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18] - 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[18] == 2 || temp_x[18] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_box1[temp_y[18] + 2][temp_x[18]] == ' ' && choice[0] == 0 && temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O')
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18]] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18]][temp_x[18] - 1] == ' ' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] - 2] != 'X' && temp_box1[temp_y[18] - 1][temp_x[18] - 2] != 'x' &&
                             ((temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'x' && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'X') || ((temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X') && temp_box1[temp_y[18] + 1][temp_x[18] - 2] != ' ')) &&
                             (temp_box1[temp_y[18] + 1][temp_x[18] - 2] != 'X' || (temp_box1[temp_y[18] + 1][temp_x[18] - 2] == 'X' && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != ' ')))
                    {
                        if (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O')
                        {

                            temp_box1[temp_y[18]][temp_x[18] - 1] = 'O';
                        }
                        else if (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'o')
                        {

                            temp_box1[temp_y[18]][temp_x[18] - 1] = 'o';
                        }

                        temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' && choice[0] == 2 && temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O')
                    {
                        temp_box1[temp_y[18] + 2][temp_x[18] - 1] = 'O';
                        temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }
    }

    // if (removed_knock)
    //     std::cout << "\n        players knock removed\n";

    return removed_knock;
}

bool playersKnock_block()
{
    bool blocked_knock{false};
    short int count{};

    if (play_mode != 3)
    {
        for (short int s = 0; s < 8; s++)
        {
            for (short int t = 0; t < 4; t++)
            {
                temp_box1[s][t] = box[s][t];
            }
        }

        for (int a = 0; a < 8; a++)
        {
            for (int b = 0; b < 4; b++)
            {
                if ((a == 0 || a == 2 || a == 4) && b != 3 && (temp_box1[a + 1][b + 1] == 'o' || temp_box1[a + 1][b + 1] == 'O') &&
                    (temp_box1[a + 2][b + 1] == ' ' || temp_box1[a + 2][b + 1] == '.') && (temp_box1[a][b] == 'x' || temp_box1[a][b] == 'X'))
                {
                    temp_y[count] = a;
                    temp_x[count] = b;
                    y1_store[count] = a + 2;
                    x1_store[count] = b + 1;
                    count++;
                }
                if ((a == 0 || a == 2 || a == 4) && b != 0 && (temp_box1[a + 1][b] == 'o' || temp_box1[a + 1][b] == 'O') &&
                    (temp_box1[a + 2][b - 1] == ' ' || temp_box1[a + 2][b - 1] == '.') && (temp_box1[a][b] == 'x' || temp_box1[a][b] == 'X'))
                {
                    temp_y[count] = a;
                    temp_x[count] = b;
                    y1_store[count] = a + 2;
                    x1_store[count] = b - 1;
                    count++;
                }
                if ((a == 1 || a == 3 || a == 5) && b != 3 && (temp_box1[a + 1][b] == 'o' || temp_box1[a + 1][b] == 'O') &&
                    (temp_box1[a + 2][b + 1] == ' ' || temp_box1[a + 2][b + 1] == '.') && (temp_box1[a][b] == 'x' || temp_box1[a][b] == 'X'))
                {
                    temp_y[count] = a;
                    temp_x[count] = b;
                    y1_store[count] = a + 2;
                    x1_store[count] = b + 1;
                    count++;
                }
                if ((a == 1 || a == 3 || a == 5) && b != 0 && (temp_box1[a + 1][b - 1] == 'o' || temp_box1[a + 1][b - 1] == 'O') &&
                    (temp_box1[a + 2][b - 1] == ' ' || temp_box1[a + 2][b - 1] == '.') && (temp_box1[a][b] == 'x' || temp_box1[a][b] == 'X'))
                {
                    temp_y[count] = a;
                    temp_x[count] = b;
                    y1_store[count] = a + 2;
                    x1_store[count] = b - 1;
                    count++;
                }

                if ((a == 6 || a == 2 || a == 4) && b != 3 && (temp_box1[a - 1][b + 1] == 'o' || temp_box1[a - 1][b + 1] == 'O') &&
                    (temp_box1[a - 2][b + 1] == ' ' || temp_box1[a - 2][b + 1] == '.') && temp_box1[a][b] == 'X')
                {
                    temp_y[count] = a;
                    temp_x[count] = b;
                    y1_store[count] = a - 2;
                    x1_store[count] = b + 1;
                    count++;
                }
                if ((a == 6 || a == 2 || a == 4) && b != 0 && (temp_box1[a - 1][b] == 'o' || temp_box1[a - 1][b] == 'O') &&
                    (temp_box1[a - 2][b - 1] == ' ' || temp_box1[a - 2][b - 1] == '.') && temp_box1[a][b] == 'X')
                {
                    temp_y[count] = a;
                    temp_x[count] = b;
                    y1_store[count] = a - 2;
                    x1_store[count] = b - 1;
                    count++;
                }
                if ((a == 7 || a == 3 || a == 5) && b != 3 && (temp_box1[a - 1][b] == 'o' || temp_box1[a - 1][b] == 'O') &&
                    (temp_box1[a - 2][b + 1] == ' ' || temp_box1[a - 2][b + 1] == '.') && temp_box1[a][b] == 'X')
                {
                    temp_y[count] = a;
                    temp_x[count] = b;
                    y1_store[count] = a - 2;
                    x1_store[count] = b + 1;
                    count++;
                }
                if ((a == 7 || a == 3 || a == 5) && b != 0 && (temp_box1[a - 1][b - 1] == 'o' || temp_box1[a - 1][b - 1] == 'O') &&
                    (temp_box1[a - 2][b - 1] == ' ' || temp_box1[a - 2][b - 1] == '.') && temp_box1[a][b] == 'X')
                {
                    temp_y[count] = a;
                    temp_x[count] = b;
                    y1_store[count] = a - 2;
                    x1_store[count] = b - 1;
                    count++;
                }
            }
        }

        if (count > 0)
        {
            auto rand_num{rand() % count};

            temp_y[18] = temp_y[rand_num];
            temp_x[18] = temp_x[rand_num];
            temp_y[19] = y1_store[rand_num];
            temp_x[19] = x1_store[rand_num];
        }
    }

    if (count > 0 || play_mode == 3)
    {
        count = 0;

        // downwards rightwards... y0 --> 7/5/3
        if ((temp_y[18] == 7 || temp_y[18] == 5 || temp_y[18] == 3) && temp_y[19] == temp_y[18] - 2 && temp_x[19] == temp_x[18] + 1 && temp_x[18] != 3)
        {
            choice[0] = rand() % 2;

            do
            {
                if ((temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'O') && choice[0] == 0 && temp_box1[temp_y[18] - 3][temp_x[18]] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X')
                {
                    if (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'O')
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    }
                    else
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'o';
                    }

                    temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                    blocked_knock = true;
                }
                else if (temp_box1[temp_y[18] - 3][temp_x[18]] == 'O' && choice[0] == 1 && temp_box1[temp_y[18] - 1][temp_x[18] + 1] != 'X')
                {
                    temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    temp_box1[temp_y[18] - 3][temp_x[18]] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 2)
                    choice[0] = 0;

            } while (count < 3 && !blocked_knock);
        }

        // downwards leftwards... y0 --> 7/5/3
        else if ((temp_y[18] == 7 || temp_y[18] == 5 || temp_y[18] == 3) && temp_y[19] == temp_y[18] - 2 && temp_x[19] == temp_x[18] - 1 && temp_x[18] != 0)
        {
            choice[0] = rand() % 3;

            do
            {
                if (temp_box1[temp_y[18] - 3][temp_x[18] - 1] == 'O' && choice[0] == 0 && temp_x[19] == 0)
                {
                    temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    temp_box1[temp_y[18] - 3][temp_x[18] - 1] = '.';
                    blocked_knock = true;
                }
                else if (temp_box1[temp_y[18] - 3][temp_x[18] - 1] == 'O' && choice[0] == 1 && temp_x[19] != 0 && temp_box1[temp_y[18] - 1][temp_x[18] - 2] != 'X')
                {
                    temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    temp_box1[temp_y[18] - 3][temp_x[18] - 1] = '.';
                    blocked_knock = true;
                }
                else if ((temp_box1[temp_y[18] - 1][temp_x[18] - 2] == 'O' || temp_box1[temp_y[18] - 1][temp_x[18] - 2] == 'o') && choice[0] == 2 && temp_x[19] != 0 && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'X' && temp_box1[temp_y[18] - 3][temp_x[18] - 1] != 'x')
                {
                    if (temp_box1[temp_y[18] - 1][temp_x[18] - 2] == 'O')
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    }
                    else
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'o';
                    }

                    temp_box1[temp_y[18] - 1][temp_x[18] - 2] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;

            } while (count < 4 && !blocked_knock);
        }

        // downwards rightwards... y0 --> 6/4
        else if ((temp_y[18] == 6 || temp_y[18] == 4) && temp_y[19] == temp_y[18] - 2 && temp_x[19] == temp_x[18] + 1 && temp_x[18] != 3)
        {
            choice[0] = rand() % 3;

            do
            {
                if ((temp_box1[temp_y[18] - 1][temp_x[18] + 2] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18] + 2] == 'O') && choice[0] == 0 && temp_x[19] != 3 && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'x' && temp_box1[temp_y[18] - 3][temp_x[18] + 1] != 'X')
                {
                    if (temp_box1[temp_y[18] - 1][temp_x[18] + 2] == 'O')
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    }
                    else
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'o';
                    }

                    temp_box1[temp_y[18] - 1][temp_x[18] + 2] = '.';
                    blocked_knock = true;
                }
                else if (temp_box1[temp_y[18] - 3][temp_x[18] + 1] == 'O' && choice[0] == 1 && temp_x[19] != 3 && temp_box1[temp_y[18] - 1][temp_x[18] + 2] != 'X')
                {
                    temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    temp_box1[temp_y[18] - 3][temp_x[18] + 1] = '.';
                    blocked_knock = true;
                }
                else if (temp_box1[temp_y[18] - 3][temp_x[18] + 1] == 'O' && choice[0] == 2 && temp_x[19] == 3)
                {
                    temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    temp_box1[temp_y[18] - 3][temp_x[18] + 1] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;

            } while (count < 4 && !blocked_knock);
        }

        // downwards leftwards... y0 --> 6/4
        else if ((temp_y[18] == 6 || temp_y[18] == 4) && temp_y[19] == temp_y[18] - 2 && temp_x[19] == temp_x[18] - 1 && temp_x[18] != 0)
        {
            choice[0] = rand() % 2;

            do
            {
                if (temp_box1[temp_y[18] - 3][temp_x[18]] == 'O' && choice[0] == 0 && temp_box1[temp_y[18] - 1][temp_x[18] - 1] != 'X')
                {
                    temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    temp_box1[temp_y[18] - 3][temp_x[18]] = '.';
                    blocked_knock = true;
                }
                else if ((temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'o') && choice[0] == 1 && temp_box1[temp_y[18] - 3][temp_x[18]] != 'X' && temp_box1[temp_y[18] - 3][temp_x[18]] != 'x')
                {
                    if (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O')
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    }
                    else
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'o';
                    }

                    temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 2)
                    choice[0] = 0;

            } while (count < 3 && !blocked_knock);
        }

        // downwards rightwards... y0 --> 2
        else if (temp_y[18] == 2 && temp_y[19] == temp_y[18] - 2 && temp_x[19] == temp_x[18] + 1 && temp_x[18] != 3 && temp_x[18] != 2 &&
                 (temp_box1[temp_y[18] - 1][temp_x[18] + 2] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18] + 2] == 'O'))
        {
            temp_box1[temp_y[19]][temp_x[19]] = 'O';
            temp_box1[temp_y[18] - 1][temp_x[18] + 2] = '.';
            blocked_knock = true;
        }

        // downwards leftwards... y0 --> 2
        else if (temp_y[18] == 2 && temp_y[19] == temp_y[18] - 2 && temp_x[19] == temp_x[18] - 1 && temp_x[18] != 0 &&
                 (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'o'))
        {
            temp_box1[temp_y[19]][temp_x[19]] = 'O';
            temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
            blocked_knock = true;
        }

        //  upwards rightwards --> 0/2/4
        else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_y[19] == temp_y[18] + 2 && temp_x[19] == temp_x[18] + 1 && temp_x[18] != 3)
        {
            choice[0] = rand() % 3;

            do
            {
                if ((temp_box1[temp_y[18] + 3][temp_x[18] + 1] == 'o' || temp_box1[temp_y[18] + 3][temp_x[18] + 1] == 'O') && choice[0] == 0 && temp_x[19] != 3 && temp_box1[temp_y[18] + 1][temp_x[18] + 2] != 'x' && temp_box1[temp_y[18] + 1][temp_x[18] + 2] != 'X')
                {
                    if (temp_box1[temp_y[18] + 3][temp_x[18] + 1] == 'O')
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    }
                    else
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'o';
                    }

                    temp_box1[temp_y[18] + 3][temp_x[18] + 1] = '.';
                    blocked_knock = true;
                }
                else if ((temp_box1[temp_y[18] + 3][temp_x[18] + 1] == 'o' || temp_box1[temp_y[18] + 3][temp_x[18] + 1] == 'O') && choice[0] == 1 && temp_x[19] == 3)
                {
                    if (temp_box1[temp_y[18] + 3][temp_x[18] + 1] == 'O')
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    }
                    else
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'o';
                    }

                    temp_box1[temp_y[18] + 3][temp_x[18] + 1] = '.';
                    blocked_knock = true;
                }
                else if (temp_box1[temp_y[18] + 1][temp_x[18] + 2] == 'O' && choice[0] == 2 && temp_x[19] != 3 && temp_box1[temp_y[18] + 3][temp_x[18] + 1] != 'X')
                {
                    temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    temp_box1[temp_y[18] + 1][temp_x[18] + 2] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;

            } while (count < 4 && !blocked_knock);
        }

        //  upwards leftwards --> 0/2/4
        else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_y[19] == temp_y[18] + 2 && temp_x[19] == temp_x[18] - 1 && temp_x[18] != 0)
        {
            choice[0] = rand() % 2;

            do
            {
                if ((temp_box1[temp_y[18] + 3][temp_x[18]] == 'O' || temp_box1[temp_y[18] + 3][temp_x[18]] == 'o') && choice[0] == 0 && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'X' && temp_box1[temp_y[18] + 1][temp_x[18] - 1] != 'x')
                {
                    if (temp_box1[temp_y[18] + 3][temp_x[18]] == 'O')
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    }
                    else
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'o';
                    }

                    temp_box1[temp_y[18] + 3][temp_x[18]] = '.';
                    blocked_knock = true;
                }
                else if (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O' && choice[0] == 1 && temp_box1[temp_y[18] + 3][temp_x[18]] != 'X')
                {
                    temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 2)
                    choice[0] = 0;

            } while (count < 3 && !blocked_knock);
        }

        //  upwards rightwards --> 1/3
        else if ((temp_y[18] == 1 || temp_y[18] == 3) && temp_y[19] == temp_y[18] + 2 && temp_x[19] == temp_x[18] + 1 && temp_x[18] != 3)
        {
            choice[0] = rand() % 2;

            do
            {
                if (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'O' && choice[0] == 0 && temp_box1[temp_y[18] + 3][temp_x[18]] != 'X')
                {
                    temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                    blocked_knock = true;
                }
                else if ((temp_box1[temp_y[18] + 3][temp_x[18]] == 'o' || temp_box1[temp_y[18] + 3][temp_x[18]] == 'O') && choice[0] == 1 && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'X' && temp_box1[temp_y[18] + 1][temp_x[18] + 1] != 'x')
                {
                    if (temp_box1[temp_y[18] + 3][temp_x[18]] == 'O')
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    }
                    else
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'o';
                    }

                    temp_box1[temp_y[18] + 3][temp_x[18]] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 2)
                    choice[0] = 0;

            } while (count < 3 && !blocked_knock);
        }

        //  upwards leftwards --> 1/3
        else if ((temp_y[18] == 1 || temp_y[18] == 3) && temp_y[19] == temp_y[18] + 2 && temp_x[19] == temp_x[18] - 1 && temp_x[18] != 0)
        {
            choice[0] = rand() % 3;

            do
            {
                if ((temp_box1[temp_y[18] + 3][temp_x[18] - 1] == 'O' || temp_box1[temp_y[18] + 3][temp_x[18] - 1] == 'o') && choice[0] == 0 && temp_x[19] != 0 && temp_box1[temp_y[18] + 1][temp_x[18] - 2] != 'X' && temp_box1[temp_y[18] + 1][temp_x[18] - 2] != 'x')
                {
                    if (temp_box1[temp_y[18] + 3][temp_x[18] - 1] == 'O')
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    }
                    else
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'o';
                    }

                    temp_box1[temp_y[18] + 3][temp_x[18] - 1] = '.';
                    blocked_knock = true;
                }
                else if ((temp_box1[temp_y[18] + 3][temp_x[18] - 1] == 'O' || temp_box1[temp_y[18] + 3][temp_x[18] - 1] == 'o') && choice[0] == 1 && temp_x[19] == 0)
                {
                    if (temp_box1[temp_y[18] + 3][temp_x[18] - 1] == 'O')
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    }
                    else
                    {
                        temp_box1[temp_y[19]][temp_x[19]] = 'o';
                    }

                    temp_box1[temp_y[18] + 3][temp_x[18] - 1] = '.';
                    blocked_knock = true;
                }
                else if (temp_box1[temp_y[18] + 1][temp_x[18] - 2] == 'O' && choice[0] == 2 && temp_x[19] != 0 && temp_box1[temp_y[18] + 3][temp_x[18] - 1] != 'X')
                {
                    temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    temp_box1[temp_y[18] + 1][temp_x[18] - 2] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;

            } while (count < 4 && !blocked_knock);
        }

        //  upwards rightwards --> 5
        else if (temp_y[18] == 5 && temp_y[19] == temp_y[18] + 2 && temp_x[19] == temp_x[18] + 1 && temp_x[18] != 3 &&
                 temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'O')
        {
            temp_box1[temp_y[19]][temp_x[19]] = 'O';
            temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
            blocked_knock = true;
        }

        //  upwards leftwards --> 5
        else if (temp_y[18] == 5 && temp_y[19] == temp_y[18] + 2 && temp_x[19] == temp_x[18] - 1 && temp_x[18] != 0 && temp_x[18] != 1 &&
                 temp_box1[temp_y[18] + 1][temp_x[18] - 2] == 'O')
        {
            temp_box1[temp_y[19]][temp_x[19]] = 'O';
            temp_box1[temp_y[18] + 1][temp_x[18] - 2] = '.';
            blocked_knock = true;
        }
    }

    // if (blocked_knock)
    //     std::cout << "\n        players knock blocked\n";

    return blocked_knock;
}

bool knock_antidote()
{
    short int count{};
    bool knock_chosen{false};

    short int temp_y0[18]{};
    short int temp_y1[18]{};
    short int temp_x0[18]{};
    short int temp_x1[18]{};

    for (int a = 0; a < 8; a++)
    {
        for (int b = 0; b < 4; b++)
        {
            if ((a == 0 || a == 2 || a == 4) && b != 3 && (box[a + 1][b + 1] == 'o' || box[a + 1][b + 1] == 'O') &&
                (box[a + 2][b + 1] == ' ' || box[a + 2][b + 1] == '.') && (box[a][b] == 'x' || box[a][b] == 'X'))
            {
                temp_y0[count] = a;
                temp_x0[count] = b;
                temp_y1[count] = a + 2;
                temp_x1[count] = b + 1;
                count++;
            }
            if ((a == 0 || a == 2 || a == 4) && b != 0 && (box[a + 1][b] == 'o' || box[a + 1][b] == 'O') &&
                (box[a + 2][b - 1] == ' ' || box[a + 2][b - 1] == '.') && (box[a][b] == 'x' || box[a][b] == 'X'))
            {
                temp_y0[count] = a;
                temp_x0[count] = b;
                temp_y1[count] = a + 2;
                temp_x1[count] = b - 1;
                count++;
            }
            if ((a == 1 || a == 3 || a == 5) && b != 3 && (box[a + 1][b] == 'o' || box[a + 1][b] == 'O') &&
                (box[a + 2][b + 1] == ' ' || box[a + 2][b + 1] == '.') && (box[a][b] == 'x' || box[a][b] == 'X'))
            {
                temp_y0[count] = a;
                temp_x0[count] = b;
                temp_y1[count] = a + 2;
                temp_x1[count] = b + 1;
                count++;
            }
            if ((a == 1 || a == 3 || a == 5) && b != 0 && (box[a + 1][b - 1] == 'o' || box[a + 1][b - 1] == 'O') &&
                (box[a + 2][b - 1] == ' ' || box[a + 2][b - 1] == '.') && (box[a][b] == 'x' || box[a][b] == 'X'))
            {
                temp_y0[count] = a;
                temp_x0[count] = b;
                temp_y1[count] = a + 2;
                temp_x1[count] = b - 1;
                count++;
            }

            if ((a == 6 || a == 2 || a == 4) && b != 3 && (box[a - 1][b + 1] == 'o' || box[a - 1][b + 1] == 'O') &&
                (box[a - 2][b + 1] == ' ' || box[a - 2][b + 1] == '.') && box[a][b] == 'X')
            {
                temp_y0[count] = a;
                temp_x0[count] = b;
                temp_y1[count] = a - 2;
                temp_x1[count] = b + 1;
                count++;
            }
            if ((a == 6 || a == 2 || a == 4) && b != 0 && (box[a - 1][b] == 'o' || box[a - 1][b] == 'O') &&
                (box[a - 2][b - 1] == ' ' || box[a - 2][b - 1] == '.') && box[a][b] == 'X')
            {
                temp_y0[count] = a;
                temp_x0[count] = b;
                temp_y1[count] = a - 2;
                temp_x1[count] = b - 1;
                count++;
            }
            if ((a == 7 || a == 3 || a == 5) && b != 3 && (box[a - 1][b] == 'o' || box[a - 1][b] == 'O') &&
                (box[a - 2][b + 1] == ' ' || box[a - 2][b + 1] == '.') && box[a][b] == 'X')
            {
                temp_y0[count] = a;
                temp_x0[count] = b;
                temp_y1[count] = a - 2;
                temp_x1[count] = b + 1;
                count++;
            }
            if ((a == 7 || a == 3 || a == 5) && b != 0 && (box[a - 1][b - 1] == 'o' || box[a - 1][b - 1] == 'O') &&
                (box[a - 2][b - 1] == ' ' || box[a - 2][b - 1] == '.') && box[a][b] == 'X')
            {
                temp_y0[count] = a;
                temp_x0[count] = b;
                temp_y1[count] = a - 2;
                temp_x1[count] = b - 1;
                count++;
            }
        }
    }

    if (count > 0)
    {
        short int index{};
        short int totalKnocks_b{};
        short int totalKnocks_r{};
        char final_board[8][4]{};

        while (index < count)
        {
            y[2] = temp_y0[index];
            x[2] = temp_x0[index];
            y[3] = temp_y1[index];
            x[3] = temp_x1[index];

            temp_y[18] = y[2];
            temp_y[19] = y[3];
            temp_x[18] = x[2];
            temp_x[19] = x[3];

            for (short int s = 0; s < 8; s++)
            {
                for (short int t = 0; t < 4; t++)
                {
                    temp_box1[s][t] = box[s][t];
                }
            }

            bool knock_blocked = playersKnock_block();
            for (short int s = 0; s < 8; s++)
            {
                for (short int t = 0; t < 4; t++)
                {
                    temp_box2[s][t] = temp_box1[s][t];
                }
            }

            totalKnocks_b = maxKnocks_player();

            if ((knock_blocked && !knock_chosen) || totalKnocks_b < totalKnocks_r)
            {
                knock_chosen = true;
                for (short int s = 0; s < 8; s++)
                {
                    for (short int t = 0; t < 4; t++)
                    {
                        final_board[s][t] = temp_box2[s][t];
                        temp_box1[s][t] = box[s][t];
                    }
                }
            }

            temp_y[18] = y[2];
            temp_y[19] = y[3];
            temp_x[18] = x[2];
            temp_x[19] = x[3];

            bool knock_removed = playersKnock_remove();
            for (short int s = 0; s < 8; s++)
            {
                for (short int t = 0; t < 4; t++)
                {
                    temp_box2[s][t] = temp_box1[s][t];
                }
            }

            totalKnocks_r = maxKnocks_player();

            if ((knock_removed && !knock_chosen) || totalKnocks_r < totalKnocks_b)
            {
                knock_chosen = true;
                for (short int s = 0; s < 8; s++)
                {
                    for (short int t = 0; t < 4; t++)
                    {
                        final_board[s][t] = temp_box2[s][t];
                    }
                }
            }

            index++;
        }

        if (knock_chosen)
        {
            for (short int s = 0; s < 8; s++)
            {
                for (short int t = 0; t < 4; t++)
                {
                    temp_box1[s][t] = final_board[s][t];
                }
            }
        }
    }

    // if (knock_chosen)
    //     std::cout << "\n        removed/blocked knock\n";

    return knock_chosen;
}