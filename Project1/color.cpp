#include "colormod.h" // namespace Color
#include <iostream>
using namespace std;
int main() {
    Color::Setting red(Color::FG_RED);
    Color::Setting def(Color::FG_DEFAULT);
    cout << "This ->" << red << "Hello, world!" << def << "<- is red." << endl;
}
