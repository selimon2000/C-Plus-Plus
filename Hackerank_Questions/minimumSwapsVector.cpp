#include <iostream>
#include <vector>
using namespace std;

int minimumSwaps(vector<int> vec)
{
    int len = vec.size();
    int temp, greatestValueLocation, swapCount = 0;

    for (int i = 0; i < len-1; i++)
    {
        greatestValueLocation = i;

        // find with the next biggest value available
        for (int j = i + 1; j < len; j++)
        {
            if (vec[j] > vec[greatestValueLocation])
            {greatestValueLocation = j;}
        }
        
        //swap with the biggest value
        if (greatestValueLocation != i)
        {   
            //Debugging: // cout<<"greatest one located at "<<greatestValueLocation<<" with a value of: "<<vec[greatestValueLocation]<<"   Swapping location: "<<i<<" with location: "<<greatestValueLocation<<endl;
            // swap with the next biggest one available
            swap(vec[i], vec[greatestValueLocation]);
            swapCount++;
        }
    }
     //Debugging:
    // printf("final answer:\n");
    // for (int i=0;i<len;i++)
    // {cout<<vec[i]<<", ";}
    // cout<<endl;

    return swapCount;
}

int main()
{
    vector<int> v1 = {4, 3, 1, 2, 8, 9};
    cout << endl << minimumSwaps(v1) << endl;
}