#include <iostream>

int main() {

    int multi_array[2][2][3] = { { {0,1,2},
                                   {3,4,5} },
                                 { {6,7,8},
                                   {9,10,11 }}
                               };
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 3; ++k) {
            std::cout << "multi_array[" <<i <<"]["<<j<<"]["<<k<<"] =" 
                      << multi_array[i][j][k] 
                      << std ::endl;
            }
        }
    }
    return 0;
}