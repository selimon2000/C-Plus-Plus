string caesarCipher(string s, int k)
{
    k%=26;
    int temp, newEntry, len=s.length();
    
    for(int i=0;i<len;i++)
    {
        temp=int(s[i]);
        newEntry=temp+k;
        
        if(temp>=65 && temp<= 90)
        {
            if (newEntry>90)
            {
                newEntry%=90;
                newEntry+=65-1;
            }
            s[i]=newEntry;
        } 
        else if(temp>=97 && temp<= 122)
        {
            if (newEntry>122)
            {
                newEntry%=122;
                newEntry+=97-1;
            }
            s[i]=newEntry;
        }
    }
 
    return s;
}