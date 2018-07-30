// gas.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get City::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;               // max number of rows in a city
const int MAXCOLS = 30;               // max number of columns in a city
const int MAXFLATULANS = 100;         // max number of Flatulans allowed

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

void doBasicTests();


class City;  // This is needed to let the compiler know that City is a
// type name, since it's mentioned in the Flatulan declaration.

class Flatulan
{
public:
    // Constructor
    Flatulan(City* cp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool possiblyGetConverted();
    
private:
    City* m_city;
    int   m_row;
    int   m_col;
};

class Player
{
public:
    // Constructor
    Player(City *cp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    int  health() const;
    bool isPassedOut() const;
    
    // Mutators
    void  preach();
    void  move(int dir);
    void  getGassed();
    
private:
    City* m_city;
    int   m_row;
    int   m_col;
    int   m_age;
    int   m_health;
    // i added m_health to private variable type
    // DONE: You'll probably find that a player object needs an additional
    //       data member to support your implementation of the behavior
    //       affected by being blast with gas.
};

class City
{
public:
    // Constructor/destructor
    City(int nRows, int nCols);
    ~City();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     flatulanCount() const;
    int     nFlatulansAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;
    
    // Mutators
    bool  addFlatulan(int r, int c);
    bool  addPlayer(int r, int c);
    void  preachToFlatulansAroundPlayer();
    void  moveFlatulans();
    
private:
    int       m_rows;
    int       m_cols;
    Player  * m_player;
    Flatulan* m_flatulans[MAXFLATULANS];
    int       m_nFlatulans;
    
    // Helper functions
    bool isInBounds(int r, int c) const;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();
    
    // Mutators
    void play();
    
private:
    City* m_city;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Flatulan implementation
///////////////////////////////////////////////////////////////////////////

Flatulan::Flatulan(City* cp, int r, int c)
{
    if (cp == nullptr)
    {
        cout << "***** A Flatulan must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols())
    {
        cout << "***** Flatulan created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
}

int Flatulan::row() const
{
    return m_row;
}

int Flatulan::col() const
{
    // DONE: TRIVIAL:  Return the column the Flatulan is at.
    // Delete the following line and replace it with the correct code.
    return m_col;  // This implementation edited
}

void Flatulan::move() //MUST FINISH THIS!!!!!!!!!!!!!!!!!!!!!!!!
{
    int dir = randInt(0, NUMDIRS-1);
    int r = m_row;
    int c = m_col;
    
    m_city->determineNewPosition(r, c, dir);
    Player* p = m_city-> player();
    if (r!=p->row() || c!=p->col())
    {
        m_row = r;
        m_col = c;
    }
    
    // DONE:  Move in the appropriate direction if allowed
}

bool Flatulan::possiblyGetConverted()  // return true if converted
{
    int x = randInt(1, 3);
    
    if (x == 1 || x == 2)
        return true;
    else
        return false;

    // Be converted with 2/3 probability
    // DONE: this has been edited
    // Delete the following line and replace it with the correct code.
    // This implementation compiles, but is incorrect.
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(City* cp, int r, int c)
{
    if (cp == nullptr)
    {
        cout << "***** The player must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_health = 10;
}

int Player::row() const
{
    // DONE: TRIVIAL:  Return the row the player is at.
    // Delete the following line and replace it with the correct code.
    return m_row;  // this has been edited
}

int Player::col() const
{
    // DONE: TRIVIAL:  Return the column the player is at.
    // Delete the following line and replace it with the correct code.
    return m_col;  // this has been edited
}

int Player::age() const
{
    // DONE: TRIVIAL:  Return the player's age.
    // Delete the following line and replace it with the correct code.
    return m_age;  // this has been edited
}

int Player::health() const
{
    // DONE: TRIVIAL:  Return the player's health status.
    // Delete the following line and replace it with the correct code.
    return m_health;  // this has been edited
}

bool Player::isPassedOut() const
{
    // DONE: TRIVIAL:  Return whether the player is passed out.
    // Delete the following line and replace it with the correct code.
    if (m_health <= 0)
        return true;
    else
        return false;  // this has been edited
}

void Player::preach()
{
    m_age++;
    m_city->preachToFlatulansAroundPlayer();
}

void Player::move(int dir) //MUST FINISH THIS!!!!!!!!!!!!!!!!!!!!!!!!
{
    m_age++;
    
    switch (dir)
    {
        case UP:
            if ((m_row > 1) && (0 == m_city->nFlatulansAt(m_row-1, m_col)))
                m_row--;
            break;
        case DOWN:
            if ((m_row < m_city-> rows() && (0 == m_city->nFlatulansAt(m_row+1, m_col))))
                m_row++;
            break;
        case LEFT:
            if ((m_col > 1) && (0 == m_city->nFlatulansAt(m_row, m_col-1)))
                m_col--;
            break;
        case RIGHT:
            if ((m_col < m_city->cols() && (0 == m_city->nFlatulansAt(m_row, m_col +1))))
                m_col++;
            break;
    }
}

void Player::getGassed()
{
    if (m_health > 0)
        m_health = m_health - 1;
    // DONE: TRIVIAL this has been edited
}

///////////////////////////////////////////////////////////////////////////
//  City implementations
///////////////////////////////////////////////////////////////////////////

City::City(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** City created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nFlatulans = 0;
}

City::~City()
{
    delete m_player;
    for (int k = 0; k < m_nFlatulans; k++)
        delete m_flatulans[k];
    // DONE:  Delete the player and all remaining dynamically allocated Flatulans.
}

int City::rows() const
{
    // DONE: TRIVIAL:  Return the number of rows in the city.
    // Delete the following line and replace it with the correct code.
    return m_rows;  // this has been edited
}

int City::cols() const
{
    // DONE: TRIVIAL:  Return the number of columns in the city.
    // Delete the following line and replace it with the correct code.
    return m_cols;  // this has been edited.
}

Player* City::player() const
{
    return m_player;
}

int City::flatulanCount() const
{
    return m_nFlatulans;
}

int City::nFlatulansAt(int r, int c) const
{
    int fCounter = 0;
    
    for (int i = 0; i < m_nFlatulans; i++)
    {
        if ((m_flatulans[i] -> row() == r) && (m_flatulans[i] -> col() == c))
            fCounter++;
    }
    // DONE:  Return the number of Flatulans at row r, column c.
    // Delete the following line and replace it with the correct code.
    return fCounter;  // this has been edited.
}

bool City::determineNewPosition(int& r, int& c, int dir) const
{
    // DONE:  If a move from row r, column c, one step in direction dir
    //        would go off the edge of the city, leave r and c unchanged and
    //        return false.  Otherwise, set r or c so that row r, column c,
    //        is now the new position resulting from the proposed move, and
    //        return true.
    switch (dir)
    {
        case UP:
            if (r-1 >= 1)
                r--;
            else
                return false;
            
            // if (isInBounds(r-1,c)
            //   r--;
            // else
            //   return false;
            // DONE:  Implement the behavior if dir is UP.
            
            break;
        case DOWN:
            if (r+1 <= rows())
                r++;
            else
                return false;
            break;
        case LEFT:
            if (c-1 >= 1)
                c--;
            else
                return false;
            break;
        
        case RIGHT:
            if (c+1 <= cols())
                c++;
            else
                return false;
            break;
            
        default:
            return false;
        // DONE:  Implement the other directions.
    }
    return true;
}

void City::display() const
{
    // Position (row,col) in the city coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    
    // Indicate each Flatulan's position
    // DONE:  If one Flatulan is at some grid point, set the char to 'F'.
    //        If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.
    // this has been completed
    
    int count = 0;
    for (r = 1; r < rows()+1; r++)
    {
        for (c = 1; c < cols()+1; c++)
        {
            count = count+ nFlatulansAt(r, c);
            if (nFlatulansAt(r, c) >= 9)
                grid[r-1][c-1] = 9 + '0';
            else if (nFlatulansAt(r,c) >= 2)
                grid[r-1][c-1] = nFlatulansAt(r, c) + '0';
            else if (nFlatulansAt(r,c) == 1)
                grid[r-1][c-1] = 'F';
        }
    }
    // Indicate player's position
    if (m_player != nullptr)
    {
        // Set the char to '@', unless there's also a Flatulan there
        // (which should never happen), in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
    // Write message, Flatulan, and player info
    cout << "There are " << m_nFlatulans << " unconverted Flatulans remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isPassedOut())
            cout << "The player has passed out." << endl;
        else
            cout << "The player's health level is " << m_player->health() << endl;
    }
}

bool City::addFlatulan(int r, int c)
{
    if (! isInBounds(r, c))
        return false;
    
    // Don't add a Flatulan on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    
    // If there are MAXFLATULANS unconverted Flatulans, return false.
    // Otherwise, dynamically allocate a new Flatulan at coordinates (r,c).
    // Save the pointer to the newly allocated Flatulan and return true.
    
    if (m_nFlatulans >= MAXFLATULANS)
        return false;
    
    else
    {
        m_flatulans[m_nFlatulans] = new Flatulan(this, r, c);
        m_nFlatulans++;
        return true;
    }
    // Your function must work as specified in the preceding paragraph even
    // in this scenario (which won't occur in this game):  MAXFLATULANS
    // are added, then some are converted, then more are added.
    
    // DONE:  Implement this.
    // this has been edited
}

bool City::addPlayer(int r, int c)
{
    if (! isInBounds(r, c))
        return false;
    
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    
    // Don't add a player on a spot with a Flatulan
    if (nFlatulansAt(r, c) > 0)
        return false;
    
    // Dynamically allocate a new Player and add it to the city
    m_player = new Player(this, r, c);
    return true;
}

void City::preachToFlatulansAroundPlayer() //MUST FINISH THIS!!!!!!!!!!!!!!!!!!!!!!!!
{
    for (int i = 0; i < m_nFlatulans; i++)
    {
        if ((m_flatulans[i]->row() == m_player->row()-1) && (m_flatulans[i]->col() == m_player->col()-1)) //minus minus
        {
            if (m_flatulans[i]->possiblyGetConverted())
            {
                delete m_flatulans[i];
                if (i != m_nFlatulans -1)
                {
                    for (int k = i; k < m_nFlatulans-1; k++)
                        m_flatulans[k] = m_flatulans[k+1];
                }
                m_nFlatulans--;
                i--;
            }
        }
        else if ((m_flatulans[i]->row() == m_player->row()-1) && (m_flatulans[i]->col() == m_player->col()+1)) //minus plus
        {
            if (m_flatulans[i]->possiblyGetConverted())
            {
                delete m_flatulans[i];
                if (i != m_nFlatulans -1)
                {
                    for (int k = i; k < m_nFlatulans-1; k++)
                        m_flatulans[k] = m_flatulans[k+1];
                }
                m_nFlatulans--;
                i--;
            }
        }
        else if ((m_flatulans[i]->row() == m_player->row()+1) && (m_flatulans[i]->col() == m_player->col()+1)) //plus plus
        {
            if (m_flatulans[i]->possiblyGetConverted())
            {
                delete m_flatulans[i];
                if (i != m_nFlatulans -1)
                {
                    for (int k = i; k < m_nFlatulans-1; k++)
                        m_flatulans[k] = m_flatulans[k+1];
                }
                m_nFlatulans--;
                i--;
            }
        }
        else if ((m_flatulans[i]->row() == m_player->row()) && (m_flatulans[i]->col() == m_player->col()+1)) //plus on col
        {
            if (m_flatulans[i]->possiblyGetConverted())
            {
                delete m_flatulans[i];
                if (i != m_nFlatulans -1)
                {
                    for (int k = i; k < m_nFlatulans-1; k++)
                        m_flatulans[k] = m_flatulans[k+1];
                }
                m_nFlatulans--;
                i--;
            }
        }
        else if ((m_flatulans[i]->row() == m_player->row()) && (m_flatulans[i]->col() == m_player->col()-1)) //minus on col
        {
            if (m_flatulans[i]->possiblyGetConverted())
            {
                delete m_flatulans[i];
                if (i != m_nFlatulans -1)
                {
                    for (int k = i; k < m_nFlatulans-1; k++)
                        m_flatulans[k] = m_flatulans[k+1];
                }
                m_nFlatulans--;
                i--;

            }
        }
        else if ((m_flatulans[i]->row() == m_player->row()+1) && (m_flatulans[i]->col() == m_player->col()-1)) //plus minus
        {
            if (m_flatulans[i]->possiblyGetConverted())
            {
                delete m_flatulans[i];
                if (i != m_nFlatulans -1)
                {
                    for (int k = i; k < m_nFlatulans-1; k++)
                        m_flatulans[k] = m_flatulans[k+1];
                }
                m_nFlatulans--;
                i--;
            }
        }
        else if ((m_flatulans[i]->row() == m_player->row()-1) && (m_flatulans[i]->col() == m_player->col())) //minus on row
        {
            if (m_flatulans[i]->possiblyGetConverted())
            {
                delete m_flatulans[i];
                if (i != m_nFlatulans -1)
                {
                    for (int k = i; k < m_nFlatulans-1; k++)
                        m_flatulans[k] = m_flatulans[k+1];
                }
                m_nFlatulans--;
                i--;
            }
        }
        else if ((m_flatulans[i]->row() == m_player->row()+1) && (m_flatulans[i]->col() == m_player->col())) //plus on row
        {
            if (m_flatulans[i]->possiblyGetConverted())
            {
                delete m_flatulans[i];
                if (i != m_nFlatulans -1)
                {
                    for (int k = i; k < m_nFlatulans-1; k++)
                        m_flatulans[k] = m_flatulans[k+1];
                }
                m_nFlatulans--;
                i--;
            }
        }
    // Preach to Flatulans orthogonally or diagonally adjacent to player.
    // If a Flatulan is converted, destroy it and remove it from the city,
    // since we have no further need to display it or have it interact with
    // the player.
    
    // DONE:  Implement this. this has been edited
    }
}

void City::moveFlatulans()
{
    for (int k = 0; k < m_nFlatulans; k++)
    {
        m_flatulans[k] -> move();
        //check each flatulan location
        if (m_flatulans[k]-> row() == m_player-> row()-1 && m_flatulans[k]->col() == m_player-> col())
            m_player -> getGassed();
        if (m_flatulans[k]-> row() == m_player-> row()+1 && m_flatulans[k]->col() == m_player-> col())
            m_player -> getGassed();
        if (m_flatulans[k]-> row() == m_player-> row() && m_flatulans[k]->col() == m_player-> col()-1)
            m_player -> getGassed();
        if (m_flatulans[k]-> row() == m_player-> row() && m_flatulans[k]->col() == m_player-> col()+1)
            m_player -> getGassed();
        
        // DONE:  Have the k-th Flatulan in the city make one move.
        //        If that move results in that Flatulan being orthogonally
        //        adjacent to the player, the player suffers a gas blast.
    }
}

bool City::isInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nFlatulans)
{
    if (nFlatulans < 0)
    {
        cout << "***** Cannot create Game with negative number of Flatulans!" << endl;
        exit(1);
    }
    if (nFlatulans > MAXFLATULANS)
    {
        cout << "***** Trying to create Game with " << nFlatulans
        << " Flatulans; only " << MAXFLATULANS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nFlatulans > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the Flatulans!" << endl;
        exit(1);
    }
    
    // Create city
    m_city = new City(rows, cols);
    
    // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_city->addPlayer(rPlayer, cPlayer);
    
    // Populate with Flatulans
    while (nFlatulans > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        // Don't put a Flatulan where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_city->addFlatulan(r, c);
        nFlatulans--;
    }
}

Game::~Game()
{
    delete m_city;
}

void Game::play()
{
    m_city->display();
    Player* p = m_city->player();
    if (p == nullptr)
        return;
    
    while ( ! p->isPassedOut()  &&  m_city->flatulanCount() > 0)
    {
        cout << "Move (u/d/l/r//q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)  // player preaches
            p->preach();
        else
        {
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    p->move(decodeDirection(action[0]));
                    break;
            }
        }
        m_city->moveFlatulans();
        m_city->display();
    }
    if (p->isPassedOut())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
        case 'u':  return UP;
        case 'd':  return DOWN;
        case 'l':  return LEFT;
        case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

// Return a random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
   
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);
    
    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif


