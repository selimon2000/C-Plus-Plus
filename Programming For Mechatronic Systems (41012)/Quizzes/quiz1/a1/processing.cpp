#include "processing.h"
// You can add additional STL headers needed here, such as <algortithm>
#include <limits>

// 3) TASK Implement function according to specification in header file
std::vector<Person> oldestPerson(std::vector<Person> crowd)
{
  int oldestAgeFound = 0;
  int currentAgeofPerson;
  std::vector<Person> returnVector;

  // finding oldest age
  for (int i = 0; i < crowd.capacity(); i++)
  {
    currentAgeofPerson = crowd[i].getAge();
    if (currentAgeofPerson > oldestAgeFound)
    {
      oldestAgeFound = currentAgeofPerson;
    }
  }

  // adding people of oldestAgeFound to the new list which is to be returned
  for (int i = 0; i < crowd.capacity(); i++)
  {
    if (crowd[i].getAge() == oldestAgeFound)
    {
      returnVector.push_back(crowd[i]);
    }
  }

  return returnVector;
}

// 4) TASK Implement function according to specification in header file
std::vector<Person> eligibleForVaccine(std::vector<Person> crowd, unsigned int ageCutoff)
{
  std::vector<Person> returnVector;

  for (int i = 0; i < crowd.capacity(); i++)
  {
    if ((crowd[i].getAge() >= ageCutoff) && (crowd[i].getVaccinatedStatus() == false))
    {
      returnVector.push_back(crowd[i]);
    }
  }
  return returnVector;
}