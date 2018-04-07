#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

//   TroubleSort(L): // L is a 0-indexed list of integers
//     let done := false
//     while not done:
//       done = true
//       for i := 0; i < len(L)-2; i++:
//         if L[i] > L[i+2]:
//           done = false
//           reverse the sublist from L[i] to L[i+2], inclusive

void troublesort(vector<int>& vec)
{
    auto done = false;
    while (!done)
    {
        done = true;
        for (auto i=0;i<vec.size()-2;++i) {
            if (vec[i]>vec[i+2]) {
                done = false;
                swap(vec[i],vec[i+2]);
            }
        }
    }
}

size_t badsort(vector<int>& vec)
{
    for (auto i=0;i<vec.size()-1;++i) {
        if (vec[i]>vec[i+1])
            return i;
    }
    return string::npos;
}

main()
{
    // read number of tests
    auto tests=0;
    cin >> tests;

    // for all tests
    for (auto i=1; i<=tests;++i) {
        // read int count
        auto count=0;
        cin >> count;
        vector<int> vec(count);

        // read in integer vector
        for (auto n=0;n<count;++n) {
            auto val = 0;
            cin >> val;
            vec[n]=val;
        }

        // sort it
        troublesort(vec);
        assert(vec.size()==count);

        // check for errors
        auto pos = badsort(vec);
        if (pos==string::npos) cout << "Case #" << i << ": OK\n";
        else cout << "Case #" << i << ": " << pos << endl;
    }
}