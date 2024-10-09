#include "./Frontend/MainDispetcherWindow/MainDispetcherWindow.h"
#include "QApplication"

int main(int argc, char **argv) {
  QApplication a(argc, argv);
  MainDispetcherWindow main_dispetcher_window;
  main_dispetcher_window.show();
  return a.exec();
}