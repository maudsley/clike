#include "test_common.h"
#include <fstream>
#include <sstream>

class main_application {
public:

  main_application(int argc, char* argv[]) {
    if (argc != 2) {
      std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
      return;
    }

    std::stringstream ss;
    ss << "../../" << argv[1];

    try {
      BasicTestInterpreter interpeter(ss.str());
      uint64_t result = interpeter.evaluate();
      std::cout << "Finished: " << result << std::endl;
    } catch (const std::runtime_error& exception) {
      throw exception;
    }
  }

  void run() {
  }

};

int main(int argc, char* argv[]) {
  main_application app(argc, argv);
  app.run();
  return 0;
}
