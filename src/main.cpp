#include "config.h"
#include <iostream>
#include "Core.h"

#include "JSON.h"
#include "JSONSerialiser.h"

using namespace std;

int main(int argc, char* argv[]) {

  /* Code adapted from the SFML 2 "Window" example */

  cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << endl;

  Core core;
  core.init();
  return core.start();

}
