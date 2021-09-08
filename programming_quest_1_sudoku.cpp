#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
using namespace std;

//to keep copies of the puzzle
int backupPuzzle[9][9];
int tempPuzzle[9][9];

/*--------------------------------------
  Funtion       -   copy array to another array
  Parameters    -   sudoku grid
                    the array we want to which we want to be copied         
--------------------------------------*/
void copyPuzzle(int puzzleArray[9][9], int bcPuzzle[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            bcPuzzle[i][j] = puzzleArray[i][j];
        }
    }
}

/*--------------------------------------
  Funtion       -  printing the Puzzle Grid  
  Parameters    -  integer array
                   (sudoku grid)           
--------------------------------------*/
void printPuzzle(int puzzleArray[][9])
{
    cout << "----------------------" << endl;
    for (int i = 0; i < 9; i++)
    {
        cout << "|";
        for (int j = 0; j < 9; j++)
        {
            cout << puzzleArray[i][j] << " ";
            if ((j + 1) % 3 == 0)
            {
                cout << "|";
            }
        }
        cout << endl;
        if ((i + 1) % 3 == 0)
        {
            cout << "----------------------" << endl;
        }
    }
}

/*--------------------------------------
  Funtion       - finding whether a value is
                 in the corresponding row
  Parameters    -  integer array
                   (sudoku grid) 
                   number going to add
                   row number          
--------------------------------------*/
bool isInRow(int puzzleArray[][9], int num, int row)
{
    bool inRow = false;
    for (int i = 0; i < 9; i++)
    {
        if (puzzleArray[row][i] == num)
        {
            inRow = true;
        }
    }
    return inRow;
}

/*--------------------------------------
  Funtion       - finding whether a value is
                 in the corresponding column
  Parameters    -  integer array
                   (sudoku grid) 
                   number going to add
                   column number          
--------------------------------------*/
bool isInColumn(int puzzleArray[][9], int num, int column)
{
    bool inColumn = false;
    for (int i = 0; i < 9; i++)
    {
        if (puzzleArray[i][column] == num)
        {
            inColumn = true;
        }
    }
    return inColumn;
}

/*--------------------------------------
  Funtion       -   finding the starting
                    the starting column
                    of the 3x3 sub grids
  Parameters    -   column number         
--------------------------------------*/
int startColumn(int column)
{
    if (column >= 0 && column <= 2)
    {
        return 0;
    }
    if (column >= 3 && column <= 5)
    {
        return 3;
    }
    if (column >= 6 && column <= 8)
    {
        return 6;
    }
}

/*--------------------------------------
  Funtion       -   finding the starting
                    starting row
                    of the 3x3 sub grids
  Parameters    -   row number         
--------------------------------------*/
int startRow(int row)
{
    if (row >= 0 && row <= 2)
    {
        return 0;
    }
    if (row >= 3 && row <= 5)
    {
        return 3;
    }
    if (row >= 6 && row <= 8)
    {
        return 6;
    }
}

/*--------------------------------------
  Funtion       -   finding whether a value is
                    in the corresponding
                    3x3 sub grid
  Parameters    -   sudoku grid
                    number which is going to add
                    column number
                    row number         
--------------------------------------*/
bool isInBox(int puzzleArray[][9], int num, int column, int row)
{
    int beginRow = startRow(row);
    int beginColumn = startColumn(column);
    bool inTheBox = false;
    for (int i = beginRow; i < beginRow + 3; i++)
    {
        for (int j = beginColumn; j < beginColumn + 3; j++)
        {
            if (puzzleArray[i][j] == num)
            {
                inTheBox = true;
            }
        }
    }
    return inTheBox;
}

/*--------------------------------------
  Funtion       -   finding whether it is
                    possible to add the number 
                    to the sudoku grid
  Parameters    -   sudoku grid
                    row number
                    column number
                    the number goint to be added         
--------------------------------------*/
bool isSafeToAdd(int puzzle[9][9], int row, int column, int num)
{
    if (isInRow(puzzle, num, row) || isInColumn(puzzle, num, column) || isInBox(puzzle, num, column, row))
    {
        return false;
    }
    return true;
}

/*--------------------------------------
  Funtion       -   to Generate and
                    to solve a Sudoku grid
  Parameters    -   sudoku grid
                    row number
                    column number
                    whether to generate or to solve
  Specifications-   If solOrGen = 0
                        The puzzle will be generated
                        the steps will not be shown
                    else
                        The puzzle will be solved
                        the steps will be shown        
--------------------------------------*/
bool sudokuSolverAndGenerator(int puzzle[9][9], int row, int column, int solOrGen)
{
    //check whether the 8th row and
    //9th column is reached
    if (row == 9 - 1 && column == 9)
        return true;

    // check whether the 9th column is reached
    //if so moving to next row col=0
    if (column == 9)
    {
        row++;
        column = 0;
    }

    //if the current cell has a value
    // go to the next cell
    if (puzzle[row][column] > 0)
        return sudokuSolverAndGenerator(puzzle, row, column + 1, solOrGen);

    for (int num = 1; num <= 9; num++)
    {

        //to check if the value if eligible to add to the cell
        //if so add it to the cell
        if (isSafeToAdd(puzzle, row, column, num))
        {

            //adding the value to the cell
            puzzle[row][column] = num;
            //if we are solving the puzzle
            //this prints the steps
            if (solOrGen == 1)
            {
                printPuzzle(puzzle);
                cout << "Row: " << row + 1 << " Column: " << column + 1 << " Replaced with: " << num << endl;
            }

            //goint to next cell
            if (sudokuSolverAndGenerator(puzzle, row, column + 1, solOrGen))
            {
                return true;
            }
            else
            {
                if (solOrGen == 1)
                {
                    cout << "Wrong Value @ [row][Column] = [" << row + 1 << "][" << column + 1 << "]\n";
                    cout << "Do you wish to continue ?\n";
                    cout << "\t\t 1-Remove the wrong number, start the solving process from previous step\n";
                    cout << "\t\t 2-Start over the solving process\n";
                    cout << "\t\t YOUR ANSWER: ";
                    int choice;
                    cin >> choice;
                    if (choice == 2)
                    {
                        cout << "Re calculating the solution\n";
                        copyPuzzle(backupPuzzle, tempPuzzle);
                        sudokuSolverAndGenerator(tempPuzzle, 0, 0, 1);

                        exit(0);
                    }
                }
            }
        }

        //if any above case is failed
        //undo the value
        puzzle[row][column] = 0;
    }
    return false;
}

/*--------------------------------------
  Funtion       -   filling the diagonal with
                    random numbers
                    (so each time a unique
                    sudoku grid will be generated)
  Parameters    -   sudoku grid         
--------------------------------------*/
void fillDiagonal(int puzzleArray[][9])
{
    srand(time(0));
    int randomNumber = (rand() % 9) + 1;
    vector<int> diagonaNumbers = {0};
    for (int i = 0; i < 9; i++)
    {
        while (true)
        {
            if (count(diagonaNumbers.begin(), diagonaNumbers.end(), randomNumber))
            {
                randomNumber = (rand() % 9) + 1;
            }
            else
            {
                puzzleArray[i][i] = randomNumber;
                diagonaNumbers.push_back(randomNumber);
                break;
            }
        }
    }
}

/*--------------------------------------
  Funtion       -   filling the grid with
                    zeros
  Parameters    -   sudoku grid         
--------------------------------------*/
void fillWithZeros(int puzzleArray[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            puzzleArray[i][j] = 0;
        }
    }
}

/*--------------------------------------
  Funtion       -   replace some values as missing
                    according to the user input value
  Parameters    -   sudoku grid 
                    user Input value
                    (number of missing values
                    in a row)        
--------------------------------------*/
void replaceWithZeros(int puzzle[9][9], int missingValues)
{
    srand(time(0));

    for (int i = 0; i < 9; i++)
    {
        vector<int> columns = {0};
        for (int j = 0; j < missingValues; j++)
        {
            int randomIndex = (rand() % 8);
            while (true)
            {
                if (count(columns.begin(), columns.end(), randomIndex) && columns.size() != 3)
                {
                    randomIndex = (rand() % 9) + 1;
                }
                else
                {
                    columns.push_back(randomIndex);
                    puzzle[i][randomIndex] = 0;
                    break;
                }
            }
        }
    }
}

/*--------------------------------------
  Funtion       -   Main Function    
--------------------------------------*/
int main()
{
    //Welcome screen
    cout << "---------------------------\n";
    cout << "SUDOKU GENERATOR AND SOLVER\n";
    cout << "---------------------------\n";
    int puzzle[9][9];
    int missingValues;
    //getting correct user input
    while (true)
    {
        cout << " Enter the number of empty cells in a row in Sudoku Board(2-4): ";
        cin >> missingValues;
        if (missingValues < 2 || missingValues > 4)
        {
            cout << "Please enter a value between 2 and 4 !\n";
        }
        else
        {
            cout << "Input is valid\n";
            break;
        }
    }
    cout << "---------------------------\n";
    cout << "PUZZLE GENERATED\n";
    cout << "---------------------------\n";

    //generating the sudoku grid
    fillWithZeros(puzzle);
    fillDiagonal(puzzle);
    //Last argument is 0
    // as we want to generate
    // we don't want to see generating steps
    sudokuSolverAndGenerator(puzzle, 0, 0, 0);

    replaceWithZeros(puzzle, missingValues);
    printPuzzle(puzzle);
    copyPuzzle(puzzle, backupPuzzle);
    cout << "---------------------------\n";
    cout << "Would you like to see the solution with steps\n";
    cout << "\t\t 1-Yes\n";
    cout << "\t\t 2-Exit the program\n";
    cout << "\t\t YOUR ANSWER: ";
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        sudokuSolverAndGenerator(puzzle, 0, 0, 1);
        cout << "---------------------------\n";
        cout << "Final Solution\n";
        printPuzzle(puzzle);
    }
    cout << endl;
    cout << "Have a nice day";
    return 0;
}