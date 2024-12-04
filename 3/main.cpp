#include <cctype>
#include <cstdio>
#include <iostream>
#include <ostream>


int main() {
    FILE* fp;
    char c;

    char file_name[] = "input.txt";

    if (!(fp = fopen(file_name, "rt"))) {
        std::cerr << "YooOOOO";
    }

    char mul[] = "mul(xxx,yyy)";
    char found[] = "xxxxxxxxxxxxx";
    char check[] = "0000000000000";
    long long int result = 0;
    int x = 0;
    int y = 0;
    int xsf = 0;
    int ysf = 0;
    int step = 0;
    int asdf = 0;

    bool do_mul = 1;
    while ((c = fgetc(fp)) != EOF && asdf < 2000) {
        // asdf++;
        // std::cout << "Step: " << step << "; c: " << c << " -- ";
        if (step == 0) {
            x = 0;
            y = 0;
            if (c == 'm') {
                step = 1;
            } else  if (c == 'd') {
                step = -1;
            } else {
                step = 0;
            }
        } else if (step == 1) {
            if (c == 'u') {
                step = 2;
            } else {
                step = 0;
            }
        } else if (step == 2) {
            if (c == 'l') {
                step = 3;
            } else {
                step = 0;
            }
        } else if (step == 3) {
            if (c == '(') {
                step = 4;
            } else {
                step = 0;
            }
        } else if (step == 4) {
            if (xsf == 0) {
                if (isdigit(c)) {
                    x = c - '0';
                    xsf = 1;
                } else {
                    step = 0;
                    xsf = 0;
                }
            } else if (xsf < 3) {
                if (isdigit(c)) {
                    x = 10*x + c - '0';
                    xsf = xsf + 1;
                } else {
                    if (c == ',') {
                        step = 5;
                        xsf = 0;
                    } else {
                        step = 0;
                        xsf = 0;
                    }
                }
            } else if (xsf == 3) {
                if (c == ',') {
                    step = 5;
                    xsf = 0;
                } else {
                    step = 0;
                    xsf = 0;
                }
            } else {
                std::cout << "Something weird..." << std::endl;
                std::cout << xsf << std::endl;
            }
        } else if (step == 5) {
            if (ysf == 0) {
                if (isdigit(c)) {
                    y = c - '0';
                    ysf = 1;
                } else {
                    step = 0;
                    ysf = 0;
                }
            } else if (0 < ysf && ysf < 3) {
                if (isdigit(c)) {
                    y = 10*y + c - '0';
                    ysf = ysf + 1;
                } else {
                    if (c == ')') {
                        result = result + x*y*do_mul;
                        step = 0;
                        ysf = 0;
                    } else {
                        step = 0;
                        ysf = 0;
                    }
                }
            } else if (ysf == 3) {
                if (c == ')') {
                    result = result + x*y*do_mul;
                    step = 0;
                    ysf = 0;
                } else {
                    step = 0;
                    ysf = 0;
                }
            } else {
                std::cout << "Something weird..." << std::endl;
                std::cout << ysf << std::endl;
            }
        } else if (step == -1) {
            if (c == 'o') {
                step = -2;
            } else if (c == 'm') {
                step = 1;
            } else {
                step = 0;
            }
        } else if (step == -2) {
            if (c == 'n') {
                step = -3;
            } else if (c == '(') {
                step = -10;
            } else if (c == 'm') {
                step = 1;
            } else {
                step = 0;
            }
        } else if (step == -3) {
            if (c == '\'') {
                step = -4;
            } else if (c == 'm') {
                step = 1;
            } else {
                step = 0;
            }
        } else if (step == -4) {
            if (c == 't') {
                step = -5;
            } else if (c == 'm') {
                step = 1;
            } else {
                step = 0;
            }
        } else if (step == -5) {
            if (c == '(') {
                step = -6;
            } else if (c == 'm') {
                step = 1;
            } else {
                step = 0;
            }
        } else if (step == -6) {
            if (c == ')') {
                do_mul = 0;
                step = 0;
            } else if (c == 'm') {
                step = 1;
            } else {
                step = 0;
            }
        } else if (step == -10) {
            if (c == ')') {
                do_mul = 1;
                step = 0;
            } else if (c == 'm') {
                step = 1;
            } else {
                step = 0;
            }
        } else {
            std::cout << "Weird..." << std::endl;
        }
        // std::cout << "step after: " << step << " do dont? "  << do_mul << " --- x and y: " << x << " and " << y << " --> Result: " << result << std::endl;

    }
    fclose(fp);
    std::cout << "Result: " << result << std::endl;
    return 0;


}
