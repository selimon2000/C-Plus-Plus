void minimumBribes(vector<int> q)
{
    int len=q.size(), totalBribes=0, j, bribesAdd, bribesTotal, flag;
    
    for (int i=len-1; i>0; i--)
    {   
        bribesAdd=0;
             
        for(j=i; q[j]!=i+1;j--)
        {bribesAdd++;}
        
        for (int s=i-bribesAdd; s<i; s++)
        {swap(q[s],q[s+1]);}        
                
        if (bribesAdd>2)
        {flag=1;}
        totalBribes+=bribesAdd;
    }    
    
    if (flag==1)
    {cout<<"Too chaotic"<<endl;
    cout<<totalBribes;}
    else
    {cout<<totalBribes;}
}