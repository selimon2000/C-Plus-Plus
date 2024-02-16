string gridChallenge(vector<string> grid)
{
    int rows=grid.size(), columns = grid[0].size();
    
    //sort the 'grid' vector
    for (int i =0; i<rows; i++)
    {sort(grid[i].begin(), grid[i].end());}
        
    for (int i=0; i<rows-1; i++)
    {
        for (int j=0; j<columns; j++)
        {
            if (grid[i][j]>grid[i+1][j]) 
            {return "NO";}
        }
    }
    return "YES";
}