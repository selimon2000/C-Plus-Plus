int diagonalDifference(vector<vector<int>> arr) {
    int length=arr.size();
    int sumI=0, sumJ=0;
    
    for (int i=0, j=length-1; i<length; i++, j--) 
    {
        sumI+=arr[i][i];
        sumJ+=arr[i][j];
    }
    
    return abs(sumI-sumJ);
}