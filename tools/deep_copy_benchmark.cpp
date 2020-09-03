#include <boost/optional.hpp>
#include <adm/adm.hpp>
#include <adm/utilities/object_creation.hpp>
#include <chrono>
#include <iostream>

int main () {
  auto doc = adm::Document::create();
  for(auto i = 0; i != 500; ++i) {
    auto holder = adm::createSimpleObject(std::string(std::to_string(i)));
    doc->add(holder.audioObject);
  }
  std::cout << "starting bench" << std::endl;
  auto startPoint = std::chrono::high_resolution_clock::now();
  auto copy = doc->deepCopy();
  auto endPoint = std::chrono::high_resolution_clock::now();
  auto duration = endPoint - startPoint;
  std::cout << std::chrono::nanoseconds(duration).count() << std::endl;
  std::cout << copy->getElements<adm::AudioObject>().size() << '\n'; // just to stop it getting optimised out
  return 0;
}