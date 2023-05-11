#include "analysis.h"
#include <iostream> // Only here for showing the code is working
#include <thread>

Analysis::Analysis(std::shared_ptr<Radar> radarPtr) : radarPtr_(radarPtr)
{
  start = std::chrono::high_resolution_clock::now();
}

//! @todo
//! TASK 1 and 2 - Same implementation, just being called twice Refer to README.md and the Header file for full description
void Analysis::computeScanningSpeed(unsigned int samples, double &scanningSpeed)
{
  unsigned int newSamples = 0;

  while (newSamples < 100)
  {
    radarPtr_->getData();
    newSamples++;
  }

  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> duration = end - start;
  long double elapsed_time = (long double)duration.count();
  // elapsed_time /= 1000;                                                                                                                                                                                                                                 

  scanningSpeed = elapsed_time / samples;
}