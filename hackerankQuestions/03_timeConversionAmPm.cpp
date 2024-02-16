#include <bits/stdc++.h>
using namespace std;

/*  Given a time in -hour AM/PM format, convert it to military (24-hour) time.
Note: - 12:00:00AM on a 12-hour clock is 00:00:00 on a 24-hour clock.
- 12:00:00PM on a 12-hour clock is 12:00:00 on a 24-hour clock. */

string timeConversion(string s)
{
    string ampm = {s[8], s[9]};
    string hour = {s[0], s[1]};
    string minute = {s[3], s[4]};
    string second = {s[6], s[7]};

    if ((ampm == "AM") && (hour == "12"))
    {hour = "00";}

    else if (ampm == "PM")
    {
        int hours = stoi(hour);
        hours = (hours % 12) + 12;
        hour = to_string(hours);
    }
    string final = hour + ":" + minute + ":" + second;
    return final;
}

int main()
{
    // Test Case 1:
    string v1 = "07:05:45PM";
    cout << timeConversion(v1) << "\n";

    // Test Case 2:
    string v2 = "12:45:54PM";
    cout << timeConversion(v2) << "\n";
}