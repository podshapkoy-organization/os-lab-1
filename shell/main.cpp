#include <boost/process.hpp>
#include <boost/chrono.hpp>
#include <iostream>
#include <string>

namespace bp = boost::process;
namespace bc = boost::chrono;

void commands(const std::string &command) {
    if (command.substr(0, 3) == "cd ") {
        std::string path = command.substr(3);
        if (chdir(path.c_str()) != 0) {
            std::cout << "cd: " << path << ": No such file on directory\n";
        }
        return;
    }

    bc::steady_clock::time_point start = bc::steady_clock::now();
    try {
        bp::child c(command, bp::std_out > stdout, bp::std_err > stderr);
        c.wait();
        if (c.exit_code() != 0) {
            std::cout << "Unable to find application named " << command.substr(8) << "\n";
        }
    } catch (const bp::process_error &e) {
        std::cout << command << ": command not found\n";
    }

    bc::steady_clock::time_point end = bc::steady_clock::now();
    bc::duration<double> elapsed = end - start;

    std::cout << "Execution time: " << elapsed.count() << " seconds\n";
}

int main() {
    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);
        if (command == "exit") {
            break;
        }
        commands(command);
    }
    return 0;
}
