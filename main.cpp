#include <iostream>
#include <vector>

#include "./service/Service.h"

const int inf = 1e9;

int main() {
    int n, m;
    std::cout << "Enter n and m" << std::endl;
    std::cin >> n >> m;
    std::vector<std::vector<int>> matrix = {{inf, inf, inf, inf, inf},
                                            {inf, 0,   10,  inf, inf},
                                            {inf, 10,  0,   40,  10},
                                            {inf, inf, 40,  0,   5},
                                            {inf, inf, 10,  5,   0}};
    Service service(m, n, matrix);
    std::cout << "Service has been created" << std::endl;
    for (int i = 0; i < 1999; ++i) {
        std::cout << "Enter command n or s" << std::endl;
        char c;
        std::cin >> c;
        if (c == 'n') {
            std::cout << "Enter step" << std::endl;
            int step;
            std::cin >> step;
            service.nextStep(step);
        } else if (c == 's') {
            std::cout << "Enter from and to id" << std::endl;
            int from, to;
            std::cin >> from >> to;
            service.getRequest(from, to);
        } else std::cout << "Invalid command" << std::endl;
    }
}