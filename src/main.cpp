#include "config.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {

  /* Code adapted from the SFML 2 "Window" example */

  cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << endl;

  sf::Window App(sf::VideoMode(800, 600), "Constellations " + to_string(myproject_VERSION_MAJOR) + "." + to_string(myproject_VERSION_MINOR) , sf::Style::Resize);

  while (App.isOpen()) {
    sf::Event Event;
    while (App.pollEvent(Event)) {
      if (Event.type == sf::Event::Closed)
        App.close();
    }
    App.display();
  }
}
