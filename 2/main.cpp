#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

int isSafe(std::vector<int>&, bool);

int main() {
    std::string file_name = "input.txt";

    std::ifstream input_file(file_name);

    if (!input_file) {
        std::cerr << "WHATTTTT?`??";
        return 1;
    }

    int safe_reports = 0;
    int safe_reports_with_dampen = 0;

    std::string line;
    while (std::getline(input_file, line)) {
        std::istringstream iss(line);
        std::vector<int> reports;

        int num;
        while (iss >> num) {
            reports.push_back(num);
        }

        //safe_reports = safe_reports + isSafe(reports, 0);
        safe_reports_with_dampen = safe_reports_with_dampen + isSafe(reports, 1);
    }
    // std::cout << "Number of safe reports: " << safe_reports << std::endl;
    std::cout << "Number of safe reports with dampen: " <<
        safe_reports_with_dampen << std::endl;

}

int isSafe(std::vector<int>& report, bool dampen) {
    int report_is_safe = 1;
    int i = 0;
    if (report.size() == 1)
        return 1;

    // 0 means not defined
    int rising = 0;

    while (i<report.size()-1 && report_is_safe) {
        if (rising == 0)
            rising = 1 - 2*(report[i] > report[i+1]);
        if (rising * report[i] >= rising * report[i+1] ||
                abs(report[i] - report[i+1]) < 1 ||
                abs(report[i] - report[i+1]) > 3)
            report_is_safe = 0;
        if (report_is_safe)
            i++;
    }


    // Possibility to dampen
    if (dampen) {
        int rem = 0;
        while (report_is_safe==0 && rem<report.size()) {
            // Hopefully copies vector!!
            std::vector<int> copy = report;
            copy.erase(std::next(copy.begin(), rem));

            // Will get 1 if copied report was safe.
            report_is_safe = report_is_safe + isSafe(copy, 0);
            rem++;
        }

    }


    // Debugging...
    //std::string prefix = "";
    //if (!dampen)
    //    prefix = "      -->";

    //std::cout << prefix << "Report: ";
    //for (int lvl: report) {
    //    std::cout <<  " " << lvl;
    //}
    //std::cout <<  std::endl;

    //std::cout <<prefix << "Risin? " << rising << " safe? " << report_is_safe << std::endl;

    return report_is_safe;
}
