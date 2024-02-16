#include <iostream> // Includes std::cout and friends so we can output to console
#include "person.h"
#include "processing.h"


int main(void)
{
  //! Your main is not tested, we unit test classes you develop
  //! However, to assist your own development you can
  //! use the main to create objects, use functions of them
  //! and check the output

  //! TASK 3
  //! Create a vector of Person's (crowd)
  //!
  //! --  Example is below 5 elements --
  //! Alice, 32 year old, vaccinated
  //! Bob, 62 year old male, unvaccinated
  //! Carol, 72 year old female, vaccinated
  //! John, 82 year old male, unvaccinated
  //! Karen, 42 year old female, vaccinated
unsigned int ageCutoff= 62;

  Person P1("Alice", 32, true);
  Person P2("Bob", 62, false);
  Person P3("Carol", 72, true);
  Person P4("John", 82, false);
  Person P5("Richard", 61, false);
  Person P6("Tom", 62, false);

  std::vector<Person> crowd{P1, P2, P3, P4, P5, P6};

  //! Call
  std::vector<Person> oldest = oldestPerson(crowd);
  
  //! TASK 4
  //!
  //! specify and age cutoff and call
  std::vector<Person> newVector= eligibleForVaccine( crowd, ageCutoff);

  for (int i = 0; i < newVector.capacity(); i++)
  {
    std::cout<<newVector[i].getName()<<std::endl;
  }
  
  
}
