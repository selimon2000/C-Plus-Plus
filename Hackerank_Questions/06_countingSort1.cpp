vector<int> countingSort(vector<int> arrA) 
{   
    sort(arrA.begin(), arrA.end());
    int lengthA=arrA.size();
    int lengthB=arrA.back()+1;
    cout<<lengthA<<"   "<<lengthB<<endl;
    
    vector<int> arrB(lengthB);
            
    for (int i=0; i<lengthA;i++)
    {arrB[arrA[i]]++;}
    
    return arrB;
}