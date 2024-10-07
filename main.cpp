#include <iostream>
#include <vector>

#include "service/Service.h"

const int inf = 1e9;

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> matrix = {{inf, inf, inf, inf, inf},
                                          {inf, 0, 10, inf, inf},
                                          {inf, 10, 0, 40, 10},
                                          {inf, inf, 40, 0, 5},
                                          {inf, inf, 10, 5, 0}};
  Service service(n, m, matrix);
  for (int i = 0; i < 1999; ++i) {
    int c;
    std::cin >> c;
    if (c == 'n') service.nextStep(30);
    if (c == 's') {
        int from, to;
        std::cin >> from >> to;
        service.getRequest(from, to);
    }
  }
}