//function which check closed boxes in each move and return no. of boxes closed if exist
int checkbox(int row, int col, int size, char grid[][size], int gamer, int Moves, int GameDetails[][8])
{
    int boxes = 0;

    if(row%2 == 0)  //check if vertical then check right and left sides
    {
        if(col+2 < size)  // check the right box
        {
            if(grid[row+1][col+1] != 32)
            {
                if(grid[row][col+2] != 32)
                {
                    if(grid[row-1][col+1] != 32)
                    {

                            if(gamer == 1)
                            {
                                grid[row][col+1] = 'A';
                            }
                            else if(gamer == 2)
                            {
                                grid[row][col+1] = 'B';
                            }
                        //record the box indexes
                        GameDetails[Moves-1][3] = row;
                        GameDetails[Moves-1][4] = col+1;
                        boxes++;
                    }
                }
            }
        }
        if(col-2 > 0)  // check the left box
        {
            if(grid[row+1][col-1] != 32)
            {
                if(grid[row][col-2] != 32)
                {
                    if(grid[row-1][col-1] != 32)
                    {

                            if(gamer == 1)
                            {
                                grid[row][col-1] = 'A';
                            }
                            else if(gamer == 2)
                            {
                                grid[row][col-1] = 'B';
                            }
                        //record the box indexes
                        GameDetails[Moves-1][5] = row;
                        GameDetails[Moves-1][6] = col-1;
                        boxes++;
                    }
                }
            }
        }
    }
    else if(col%2 == 0)  //check if horizontal then check up and down
    {
        if(row+2 < size)  //check down
        {
            if(grid[row+1][col+1] != 32)
            {
                if(grid[row+2][col] != 32)
                {
                    if(grid[row+1][col-1] != 32)
                    {

                            if(gamer == 1)
                            {
                                grid[row+1][col] = 'A';
                            }
                            else if(gamer == 2)
                            {
                                grid[row+1][col] = 'B';
                            }
                        //record box indexes
                        GameDetails[Moves-1][3] = row+1;
                        GameDetails[Moves-1][4] = col;
                        boxes++;
                    }
                }
            }
        }
        if(row-2 > 0)  //check up
        {
            if(grid[row-1][col+1] != 32)
            {
                if(grid[row-2][col] != 32)
                {
                    if(grid[row-1][col-1] != 32)
                    {

                            if(gamer == 1)
                            {
                                grid[row-1][col] = 'A';
                            }
                            else if(gamer == 2)
                            {
                                grid[row-1][col] = 'B';
                            }
                        //record box indexes
                        GameDetails[Moves-1][5] = row-1;
                        GameDetails[Moves-1][6] = col;
                        boxes++;
                    }
                }
            }
        }
    }
    return boxes;
}

