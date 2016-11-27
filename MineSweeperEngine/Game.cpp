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
    
    cout << "Minesweeper V2.0" << endl << endl;
    cout << "# Rows: ";
    cin >> rows;
    cin.ignore();
    cout << "# Cols: ";
    cin >> cols;
    cin.ignore();
    cout << "# Mines: ";
    cin >> numMines;
    cin.ignore();
    cout << endl;
    
    Game minesweeper(rows, cols, numMines);
    
    string o;
    
    while (!minesweeper.isFinished())
    {
        cout << "(1) Print Board" << endl;
        cout << "(2) Toggle Flag Mode" << endl;
        cout << "(3) Process Square" << endl << endl;
        
        getline(cin, o);
        int choice = o.at(0) - '0';
        cout << endl;
        
        switch (choice)
        {
            case 1:
                cout << minesweeper.toString() << endl;
                break;
            
            case 2:
                minesweeper.toggleFlagMode();
                break;
                
            case 3:
                cout << "Enter the row and column indeces for the square on the same line " <<
                "with a whitespace in between(i.e. \"1 2\"): ";
                getline(cin, o);
                cout << endl;
                stringstream ss(o);
                string _row, _col;
                ss >> _row;
                ss >> _col;
                int r = atoi(_row.c_str());
                int c = atoi(_col.c_str());
                minesweeper.processClickForSquareAt(r, c);
                cout << minesweeper.toString() << endl;
                break;
        }
    }
    
    cout << ((minesweeper.victoryAchieved()) ? "You won" : "You lost") << endl << endl;
    
    return 0;
}