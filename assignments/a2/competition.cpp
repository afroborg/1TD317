#include <iostream>
using namespace std;

/**
 * Prints the results of the competition based on the number of
 * contestants, the winning number and the winning time
 * @param winningNbr The number of the fastest contestant
 * @param winningTime The fastest time
 * @param nbrOfContestants How many contestants were entered
 */
void printResults(int winningNbr, int winningTime, int nbrOfContestants) {
  // if we have no contestants, print "No contestants" and return
  if (nbrOfContestants <= 0) {
    cout << "Inga tävlande" << endl;
    return;
  }

  // converts the winning time back to Hours, minutes and seconds
  int winningTimeH = winningTime / 3600;
  int winningTimeMin = (winningTime % 3600) / 60;
  int winningTimeSec = winningTime % 60;

  // prints the new lines for the results
  cout << "Vinnare är startnr: " << winningNbr << endl;
  cout << "Tim: " << winningTimeH << " Min: " << winningTimeMin
       << " Sek: " << winningTimeSec << endl;
  cout << "Antal tävlande: " << nbrOfContestants << endl;
}

/**
 * converts a time in hours to seconds
 * @param hours the time in hours
 * @return int the time in seconds
 */
int hourToSeconds(int hours) { return hours * 60 * 60; }

/**
 * Converts a time in minutes to seconds
 * @param time the num
 * @return int the minutes converted to seconds
 */
int minuteToSeconds(int minutes) { return minutes * 60; }

/**
 * Converts parameters of hours, minutes and seconds to an integer of seconds.
 * @param hours the number of hours
 * @param mintes the number of minutes
 * @param seconds the number of seconds
 * @return int the total amount of seconds
 */
int toSeconds(int hours, int mintes, int seconds) {
  return hourToSeconds(hours) + minuteToSeconds(mintes) + seconds;
}

int main() {
  int nbrOfContestants = 0;           // how many contestants are registered
  int winningNbr;                     // the winning number
  int currentWinningTime = INT32_MAX; // the best time, initialized to the max

  // run until we get a startnumber that breaks this while loop
  while (true) {
    int startNbr;

    // read the startnumber from the users input
    cout << "Startnummer? ";
    cin >> startNbr;

    // if the startNumber is less than zero, exit the while loop
    if (startNbr < 0) {
      break;
    }

    // register the times needed to be read from the user
    int startTimeH, startTimeMin, startTimeSec;
    int endTimeH, endTimeMin, endTimeSec;

    cout << "Starttid? "; // start time in format HH mm ss
    cin >> startTimeH >> startTimeMin >> startTimeSec;

    cout << "Måltid? "; // end time in format HH mm ss
    cin >> endTimeH >> endTimeMin >> endTimeSec;

    // convert the start and end times to seconds to compare them
    int totalStartTime = toSeconds(startTimeH, startTimeMin, startTimeSec);
    int totalEndTime = toSeconds(endTimeH, endTimeMin, endTimeSec);

    // adjust for new day
    if (totalStartTime > totalEndTime) {
      totalEndTime += hourToSeconds(24); // add 24h
    }

    // the time difference between start and end time
    int timeDiff = totalEndTime - totalStartTime;

    // check if this is a new best time
    if (timeDiff < currentWinningTime) {
      // if it is, set the data for the new best time
      currentWinningTime = timeDiff;
      winningNbr = startNbr;
    }

    // increase the number of contestants
    nbrOfContestants++;

    // print a linebreak to make the output more readable
    cout << endl;
  }

  // print the results to the user
  printResults(winningNbr, currentWinningTime, nbrOfContestants);

  cout << "Programmet avslutas" << endl;

  return 0;
}
