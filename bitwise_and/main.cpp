#include <iostream>

using namespace std;
bool is_space(char s) {
    return s == ' ';
}

bool is_num(char s) {
    return s >= '0' && s <= '9';
}

bool is_e(char s) {
    return s == 'e';
}

bool is_dot(char s) {
    return s == '.';
}

bool is_sign(char s) {
    return s == '+' || s == '-';
}

bool is_out_of_range(int i, int size) {
    return i >= size;
}

bool isNumber(string s) {

    if(s.empty()) {
        return false;
    }

    //_ at the beggining
    int i = 0;

    int size = s.size();

    while(!is_out_of_range(i,size) && is_space(s[i])) {
        ++i;
    }

    if(is_out_of_range(i,size)) {
        return false;
    }

    //sign
    if(is_sign(s[i])) {
        ++i;
        if(is_out_of_range(i,size)) {
            return false;
        }
    }

    //first number
    bool first_num = false;

    if(is_num(s[i])) {
        first_num = true;

        while(!is_out_of_range(i,size) && is_num(s[i])) {
            ++i;
        }

        if(is_out_of_range(i,size)) {
            return true;
        }

        if(is_space(s[i])) {
            while(!is_out_of_range(i,size) && is_space(s[i])) {
                ++i;
            }

            if(is_out_of_range(i,size)) {
                return true;
            }
            return false;
        }
    }

    bool dot = false;
    if(is_dot(s[i])) {
        ++i;

        dot = true;

        if(is_out_of_range(i,size)) {
            return first_num;
        }

        if(is_space(s[i])) {
            while(!is_out_of_range(i,size) && is_space(s[i])) {
                ++i;
            }

            if(is_out_of_range(i,size)) {
                return first_num;
            }
            return false;
        }
    }

    bool e = false;
    if(is_e(s[i])) {

        if((!first_num)) {
            return false;
        }

        i++;
        e = true;

        if(is_out_of_range(i,size)) {
            return false;
        }
    }

    bool second_num = false;

    if(is_num(s[i])) {
        second_num = true;

        while(!is_out_of_range(i,size) && is_num(s[i])) {
            ++i;
        }

        if(is_out_of_range(i,size)) {
            return true;
        }
    }

    bool third_num = false;
    if(is_e(s[i])) {

        if((!first_num && !second_num) || e) {
            return false;
        }

        i++;
        e = true;

        if(is_out_of_range(i,size)) {
            return false;
        }

        if(is_num(s[i])) {
            third_num = true;

            while(!is_out_of_range(i,size) && is_num(s[i])) {
                ++i;
            }
        } else {
            return false;
        }
    }

    while(!is_out_of_range(i,size) && is_space(s[i])) {
        ++i;
    }

    if(!is_out_of_range(i,size)) {
        return false;
    }

    if(e && !second_num && !third_num) {
        return false;
    }

    if(dot && !first_num && !second_num) {
        return false;
    }

    return true;
}

int main() {
    cout << "Hello, World!" << endl;
    //rangeBitwiseAnd(1,3);
    isNumber("0e ");
    return 0;
}