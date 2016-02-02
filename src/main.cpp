#include "config.h"
#include <iostream>
#include "Core.h"

#include "JSON.h"
#include "JSONSerialiser.h"

using namespace std;

int main(int argc, char* argv[]) {

  /* Code adapted from the SFML 2 "Window" example */

  cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << endl;
  j::Value v{
    {"Hello","World"},
    {"Obj", {
              {"Bonjour", "aurevoir"},
              {"Number", 89},
              {"Tatata", true},
              {"List", j::VArray{"Bla", "Caca", 2,true}}
          }
      }
  };

  j::Value u = j::readFromString(j::writeToString(v));
  if(v == u)
  {
      cout << "SUCCESS!" << endl;
  }

  cout << j::writeToString(v) << endl;

  Core core;
  core.init();
  return core.start();

}
