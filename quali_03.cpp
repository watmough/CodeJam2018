#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

// go gopher!



void next_pos(vector<char>& area, int width, int height, int& x, int& y)
{
    // step x,y to next 9-neighborhood if no blanks
    if (area[x-1+(y-1)*1000]==0||area[x+(y-1)*1000]==0  ||area[x+1+(y-1)*1000]==0||
        area[x-1+y*1000]==0    ||area[x+y*1000]==0      ||area[x+1+y*1000]==0    ||
        area[x-1+(y+1)*1000]==0||area[x+(y+1)*1000]==0  ||area[x+1+(y+1)*1000]==0)
        return;
    // need to step
    if (++x>width-1) {
        x = 2;
        y++;
    }
}



main()
{
    // read number of test cases
    auto tests=0;
    cin >> tests;

    // for each test case
    for (auto i=1;i<=tests;++i)
    {
        // orchard array
        vector<char> vec(1000*1000);

        // read desired area
        auto area=0;
        cin >> area;

        // factor area into height x width<999
        auto height = 3;
        auto width = 3;
        while (height*width<area) {
            if (height>width) width++;
            else height++;
        }

        // start at 2,2
        auto row=2, col=2;
        auto arow=0, acol=0;

        // while true
        while (1)
        {
            // request a dig
            next_pos(vec,width,height,col,row);
            cout << row << " " << col << endl;

            // what was dug
            cin >> arow >> acol;

            // done?
            if (arow==0 && acol==0)
                break;
            if (arow==-1 && acol==-1)
                exit(0);

            // assign as dug
            vec[arow*1000+acol]=1;
        }
    }
}