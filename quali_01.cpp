#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int damage(string p)
{
    int power=1,damage=0;
    for_each(begin(p),end(p),
    [&](char c){
        if (c=='C') power*=2;
        else if (c=='S') damage+=power;
    });
    return damage;
}

bool canhack(string p)
{
    auto fc = p.find_first_of('C');
    auto fs = p.find_last_of('S');
    // check if no C's or no S's
    if (fc==string::npos || fs==string::npos) 
        return false;
    // is there a charge before a shot
    return fc<fs;
}

string swapCS(string p)
{
    // find last CS and swap them
    auto pos = p.rfind("CS");
    swap(p[pos],p[pos+1]);
    return p;
}

main() 
{
    // read test cases count
    auto cases=0;
    cin >> cases;

    // for each test case
    for (auto i=1;i<=cases;++i)
    {
        // read max damage + program
        auto maxdamage = 0;
        auto prog = ""s;
        auto hacks = 0;
        cin >> maxdamage >> prog;

        // while damage > max damage
        while (1)
        {
            // are we done?
            if (damage(prog)<=maxdamage) {
                cout << "Case #" << i << ": " << hacks << "\n";
                break;
            }

            // can we hack?
            if (damage(prog)>maxdamage && !canhack(prog)) {
                cout << "Case #" << i << ": IMPOSSIBLE\n";
                break;
            }

            // do a hack
            prog = swapCS(prog);
            hacks++;
        }
    }
}
