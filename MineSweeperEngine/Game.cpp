//
//  Grid.cpp
//  MineSweeperEngine
//
//  Created by Chris on 11/2/16.
//  Copyright © 2016 Chris. All rights reserved.
//

#include "Game.h"
#include <iostream>
#include <sstream>

int main (int argc, char** argv)
{
    int rows, cols, numMines;
    
    cout << "Minesweeper V1.0" << endl << endl;
    cout << "# Rows: ";
    cin >> rows;
    cin.ignore();
    cout << endl;
    cout << "# Cols: ";
    cin >> cols;
    cin.ignore();
    cout << endl;
    cout << "# Mines: ";
    cin >> numMines;
    cin.ignore();
    cout << endl << endl;
    
    Game minesweeper(rows, cols, numMines);
    Grid * grid = minesweeper.getGrid();
    
    string o;
    
    while (!minesweeper.isFinished())
    {
        cout << "(1) Print board" << endl;
        cout << "(2) Toggle Flag Mode" << endl;
        cout << "(3) Process Square" << endl << endl;
        
        getline(cin, o);
        int choice = o.at(0) - '0';
        cout << endl << endl;
        
        switch (choice)
        {
            case 1:
                cout << grid->toString() << endl;
                break;
            
            case 2:
                grid->toggleFlagMode();
                break;
            
            case 3:
                cout << "Enter the row and column for the square on the same line " <<
                        "with a whitespace in between(i.e. \"1 2\"): ";
                getline(cin, o);
                cout << endl;
                stringstream ss(o);
                string _row, _col;
                ss >> _row;
                ss >> _col;
                int r = _row.at(0) - '0';
                int c = _col.at(0) - '0';
                grid->processClickForSquareAt(r, c);
                break;
        }
    }
    
    cout << endl << ((minesweeper.victoryAchieved()) ? "You won" : "You lost") << endl << endl;
    
    cout << grid->toString() << endl;
    
    return 0;
}