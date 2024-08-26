#include "qtgui/asio_manager.h"
#include "qtgui/main_controller.h"
#include <QApplication>

int main(int argc, char* argv[]) {
  /* we want to use boost asio and Qt together */
  boost::asio::io_service io_service;
  QApplication qapp(argc, argv);

  /* a simple timer to poll for events to avoid blocking the Qt UI */
  asio_manager io_service_manager(io_service);

  /* start the application. don't ceate it on the stack. */
  std::shared_ptr<main_controller> controller = std::make_shared<main_controller>(io_service);
  return qapp.exec();
}
