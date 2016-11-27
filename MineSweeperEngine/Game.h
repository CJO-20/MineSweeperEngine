//
//  Game.h
//  MineSweeperEngine
//
//  Created by Chris on 11/2/16.
//  Copyright © 2016 Chris. All rights reserved.
//

#ifndef Game_h
#define Game_h

#ifndef nullptr
#define nullptr 0
#endif

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

class Square
{
protected:
    bool explosive, revealed;
    int flagged;
    Square * northWestNeighbor;
    Square * northCentralNeighbor;
    Square * northEastNeighbor;
    Square * westCentralNeighbor;
    Square * eastCentralNeighbor;
    Square * southWestNeighbor;
    Square * southCentralNeighbor;
    Square * southEastNeighbor;
    
public:
    Square() : explosive(false), revealed(false), flagged(0),
               northWestNeighbor(nullptr), northCentralNeighbor(nullptr),
               northEastNeighbor(nullptr), westCentralNeighbor(nullptr),
               eastCentralNeighbor(nullptr), southWestNeighbor(nullptr),
               southCentralNeighbor(nullptr), southEastNeighbor(nullptr)
    {}
    void setExplosive(bool hasMine){explosive = hasMine;}
    void setFlag(int flag)
    {
        flagged = flag;
    }
    int getFlag(void)
    {
        return flagged;
    }
    void toggleFlag(void)
    {
        if (flagged == 0)
            flagged = 1;
        else
            flagged = 0;
    }
    void reveal(void)
    {
        if (!isRevealed() && !isFlagged())
        {
            revealed = true;
            
            if (getNumberClue() == 0 && !hasMine())
            {
                if (northWestNeighbor != nullptr)
                {
                    northWestNeighbor->reveal();
                }
                
                if (northCentralNeighbor != nullptr)
                {
                    northCentralNeighbor->reveal();
                }
                
                if (northEastNeighbor != nullptr)
                {
                    northEastNeighbor->reveal();
                }
                
                if (westCentralNeighbor != nullptr)
                {
                    westCentralNeighbor->reveal();
                }
                
                if (eastCentralNeighbor != nullptr)
                {
                    eastCentralNeighbor->reveal();
                }
                
                if (southWestNeighbor != nullptr)
                {
                    southWestNeighbor->reveal();
                }
                
                if (southCentralNeighbor != nullptr)
                {
                    southCentralNeighbor->reveal();
                }
                
                if (southEastNeighbor != nullptr)
                {
                    southEastNeighbor->reveal();
                }
            }
        }
    }
    void reset(void)
    {
        explosive = false;
        revealed = false;
        flagged = false;
    }
    void setNorthWestNeighbor(Square * n){northWestNeighbor = n;}
    void setNorthCentralNeighbor(Square * n){northCentralNeighbor = n;}
    void setNorthEastNeighbor(Square * n){northEastNeighbor = n;}
    void setWestCentralNeighbor(Square * n){westCentralNeighbor = n;}
    void setEastCentralNeighbor(Square * n){eastCentralNeighbor = n;}
    void setSouthWestNeighbor(Square * n){southWestNeighbor = n;}
    void setSouthCentralNeighbor(Square * n){southCentralNeighbor = n;}
    void setSouthEastNeighbor(Square * n){southEastNeighbor = n;}
    bool hasMine(void)
    {
        return explosive;
    }
    bool isRevealed(void)
    {
        return revealed;
    }
    bool isFlagged(void)
    {
        return (flagged != 0);
    }
    int getNumberClue ()
    {
        int num = 0;
        
        if (northWestNeighbor != nullptr)
            if (northWestNeighbor->hasMine()) //conditions are separated into two if's in case of nullptr -> bad access
                num++;
        
        if (northCentralNeighbor != nullptr)
            if (northCentralNeighbor->hasMine()) //conditions are separated into two if's in case of nullptr -> bad access
                num++;
        
        if (northEastNeighbor != nullptr)
            if (northEastNeighbor->hasMine()) //conditions are separated into two if's in case of nullptr -> bad access
                num++;
        
        if (westCentralNeighbor != nullptr)
            if (westCentralNeighbor->hasMine()) //conditions are separated into two if's in case of nullptr -> bad access
                num++;
        
        if (eastCentralNeighbor != nullptr)
            if (eastCentralNeighbor->hasMine()) //conditions are separated into two if's in case of nullptr -> bad access
                num++;
        
        if (southWestNeighbor != nullptr)
            if (southWestNeighbor->hasMine()) //conditions are separated into two if's in case of nullptr -> bad access
                num++;
        
        if (southCentralNeighbor != nullptr)
            if (southCentralNeighbor->hasMine()) //conditions are separated into two if's in case of nullptr -> bad access
                num++;
        
        if (southEastNeighbor != nullptr)
            if (southEastNeighbor->hasMine()) //conditions are separated into two if's in case of nullptr -> bad access
                num++;
        
        return num;
    }
    char toChar()
    {
        if (!isRevealed())
        {
            if (isFlagged())
            {
                if (getFlag() == 1)
                    return '!'; //indicates a flag
                else
                    return '?'; //indicates an uncertainty -> occurs when trying to reveal a flagged square
            }
            else
                return '#'; //indicates unrevealed square
        }
        else if (getFlag() == 1 && !hasMine())
            return 'X';  //indicates a misflag (no mine present)
        
        if (hasMine())
            return '*'; //indicates a revealed mine -> loss
        
        if (getNumberClue() == 0)
            return '-'; //indicates an "empty" revealed square with no mines in close proximity
        
        return getNumberClue() + '0'; //indicates a revealed square with mines in close proximity
    }
};

class Game
{
protected:
    Square * gridPtr;
    int rows, columns, numMines;
    bool flagMode, minesPlanted;
public:
    Game(int rows, int cols, int numMines) : rows(rows), columns(cols), numMines(numMines), flagMode(false),
                                             minesPlanted(false)
    {
        gridPtr = new Square [rows * cols];
        
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                if (c != 0) // can add central west neighbor
                    (gridPtr + r * cols + c)->setWestCentralNeighbor(gridPtr + r * cols + (c - 1));
                
                if (c != cols - 1) // can add central east neighbor
                    (gridPtr + r * cols + c)->setEastCentralNeighbor(gridPtr + r * cols + (c + 1));
                
                if (r != 0) //If can add north neighbors
                {
                    (gridPtr + r * cols + c)->setNorthCentralNeighbor(gridPtr + (r - 1) * cols + c);
                    
                    if (c != 0) //If can add northwest neighbors
                        (gridPtr + r * cols + c)->setNorthWestNeighbor(gridPtr + (r - 1) * cols + (c - 1));
                    
                    if (c != cols - 1) //If can add northeast neighbors
                        (gridPtr + r * cols + c)->setNorthEastNeighbor(gridPtr + (r - 1) * cols + (c + 1));
                }
                
                if (r != rows - 1)
                {
                    (gridPtr + r * cols + c)->setSouthCentralNeighbor(gridPtr + (r + 1) * cols + c);
                    
                    if (c != 0) //If can add southwest neighbors
                        (gridPtr + r * cols + c)->setSouthWestNeighbor(gridPtr + (r + 1) * cols + (c - 1));
                    
                    if (c != cols - 1) //If can add southeast neighbors
                        (gridPtr + r * cols + c)->setSouthEastNeighbor(gridPtr + (r + 1) * cols + (c + 1));
                }
            }
        }
    }
    ~Game(void){delete [] gridPtr;}
    void toggleFlagMode(void){flagMode = !flagMode;}
    bool isFlagMode(void){return flagMode;}
    bool hasDetonatedMine(void)
    {
        for (int i = 0; i < rows * columns; i++)
        {
            if ((gridPtr + i)->hasMine() && (gridPtr + i)->isRevealed())
            {
                return true;
            }
        }
        
        return false;
    }
    int getNumVisibleFlags(void) //does not include uncertainty flags
    {
        int numFlags = 0;
        
        for (int i = 0; i < rows * columns; i++)
        {
            if (!(gridPtr + i)->isRevealed() && (gridPtr + i)->getFlag() == 1)
            {
                numFlags++;
            }
        }
        
        return numFlags;
    }
    int getNumMines(void)
    {
        return numMines;
    }
    int getNumUnusedFlags(void)
    {
        return numMines - getNumVisibleFlags();
    }
    int getNumUnrevealedSquares(void)
    {
        int num = rows * columns;
        
        for (int i = 0; i < rows * columns; i++)
            if ((gridPtr + i)->isRevealed())
                num--;
        
        return num;
    }
    //Returns true if changes to the board were made
    bool processClickForSquareAt (int row, int col)
    {
        if (isFinished())
            return false;
        
        bool success;
        
        if (isFlagMode())
            success = processToggleFlagForSquareAt(row, col);
        else
            success = processRevealForSquareAt(row, col);
        
        if (isFinished())
        {
            if (victoryAchieved())
            {
                for (int i = 0; i < rows * columns; i++)
                    if (!(gridPtr + i)->isRevealed() && (gridPtr + i)->hasMine())
                        (gridPtr + i)->setFlag(1);
            }
            else
            {
                for (int i = 0; i < rows * columns; i++)
                    if (!(gridPtr + i)->isRevealed())
                        (gridPtr + i)->reveal();
            }
        }
        
        return success;
        
    }
    //Returns true if reveal was successful
    bool processRevealForSquareAt(int row, int col)
    {
        Square * s = (gridPtr + (row * columns) + col);
        
        if (!minesPlanted)
        {
            plantMines(numMines, row, col);
            minesPlanted = true;
        }
        
        if (s->isRevealed())
        {
            return false;
        }
        else
        {
            if (s->isFlagged())
            {
                if (s->getFlag() == 1)
                    s->setFlag(2);
                else
                    s->setFlag(1);
            }
            else
                s->reveal();
            
            return true;
        }
            
    }
    //Returns true if flag toggle was successful
    bool processToggleFlagForSquareAt (int row, int col)
    {
        Square * s = (gridPtr + (row * columns) + col);
        
        if (s->isRevealed()) //num unused flags will never be less than 0, it's just good practice
        {
            return false;
        }
        else
        {
            if (!s->isFlagged() && getNumUnusedFlags() <= 0)
                return false;
            
            s->toggleFlag();
            return true;
        }
    }
    void reset(void)
    {
        flagMode = minesPlanted = false;
        
        for (int i = 0; i < rows * columns; i++)
            (gridPtr + i)->reset();
    }
    void plantMines(int numMines, int omitRowCoord, int omitColCoord)
    {
        if (numMines < rows * columns)
        {
            Square * omit = gridPtr + (omitRowCoord * columns) + omitColCoord;
            
            vector<Square *> sampleBatch;
            
            for (int i = 0; i < rows * columns; i++)
                if (gridPtr + i != omit)
                    sampleBatch.push_back(gridPtr + i);
            
            random_device rd;
            
            mt19937 rng(rd());
            
            uniform_int_distribution<uint32_t> dist(0, (int)(sampleBatch.size() - 1));
            
            for (int k = 0; k < numMines; k++)
            {
                uint32_t randIndex = dist(rng) % sampleBatch.size();
                Square * mineSquare = sampleBatch.at(randIndex);
                mineSquare->setExplosive(true);
                
                vector<Square *> modifiedBatch;
                for (int i = 0; i < sampleBatch.size(); i++)
                {
                    if (i != randIndex)
                        modifiedBatch.push_back(sampleBatch.at(i));
                }
                sampleBatch.swap(modifiedBatch);
                
            }
        }
    }
    string toString(void)
    {
        stringstream ss;
        
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < columns; c++)
            {
                ss << (gridPtr + (r * columns) + c)->toChar();
                
                if (c != columns - 1)
                    ss << ' ';
            }
            
            ss << endl;
        }
        
        return ss.str();
    }
    bool victoryAchieved(void){return (getNumUnrevealedSquares() == getNumMines() && !isDefeat());}
    bool isDefeat(void){return hasDetonatedMine();}
    bool isFinished(void){return (victoryAchieved() || isDefeat());}
    
};

#endif /* Game_h */
