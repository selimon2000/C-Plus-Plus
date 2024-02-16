int towerBreakers(int n, int m)
{
    cout<<"n:"<<n<<endl;
    cout<<"m:"<<m<<endl;

    int player=0;
    
    for (int i=m-1; i>0;i--)
    {
        if(m%i==0)
        {
            m/=i;
            player++;
            cout<<"i:"<<i<<endl;   
        }
    }
    cout<<"number of factors:"<<player<<endl;
    
    player*=n;
    cout<<"number of factors mulitplied by number of towers: "<<player<<endl;
    
    player=((player+1)%2)+1;
    cout<<"player winning: "<<player<<endl;
    
    return player;
}