class Solution
{
public:

    void remove_and_pushback(int &num_, string &returnString_, string push_back_string, int divisor)
    {
        if (num_ >= divisor)
        {
            for (int i = 0; i < num_ / divisor; i++)
                {returnString_+=push_back_string;}
            num_ %= divisor;
        }
    }

    string intToRoman(int num)
    {
        string returnString;

        remove_and_pushback(num, returnString, "M", 1000);
        remove_and_pushback(num, returnString, "CM", 1000-100);
        remove_and_pushback(num, returnString, "D", 500);
        remove_and_pushback(num, returnString, "CD", 500-100);

        remove_and_pushback(num, returnString, "C", 100);
        remove_and_pushback(num, returnString, "XC", 100-10);
        remove_and_pushback(num, returnString, "L", 50);
        remove_and_pushback(num, returnString, "XL", 50-10);

        remove_and_pushback(num, returnString, "X", 10);
        remove_and_pushback(num, returnString, "IX", 10-1);
        remove_and_pushback(num, returnString, "V", 5);
        remove_and_pushback(num, returnString, "IV", 5-1);

        remove_and_pushback(num, returnString, "I", 1);

        return returnString;
    }
};