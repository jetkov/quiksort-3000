// QuickSort 3000
// The workings behind the innovative coin sorter and dispenser robot.

// References Hardware.c and Interface.c

#include "Interface.c"
#include "Hardware.c"

// The QuikSort 3000's main function sets up the system to be ready to accept coins,
// and then enter a loop in which it would ask the user to request an amount of
// change, and attempts to dispense that amount.

// AUTHOR: Alex Petkovic
task main()
{
	// Start the automatic hopper intake system to run in the background
	startTask(autoHopper);
	// Home the Tetix servos
	homeServos();

	// Main program loop
  while (getButtonPress(buttonBack) == 0)
  {
    int change = getInputAmounts(); // Gets the user to request an amount of change

		// Setting up the logic variables, to keep track of coins to dispense, coins actually dispensed, and coin availability
    int nNickels = -1, nDimes = -1, nQuarters = -1, nLoonies = -1, nToonies = -1;
    int nNickelsR = 0, nDimesR = 0, nQuartersR = 0, nLooniesR = 0, nTooniesR = 0;
    bool yNickels = true, yDimes = true, yQuarters = true, yLoonies = true, yToonies = true;

		// Main program loop, which runs while change left to dispense is greater than zero, and there is at least one type of coin available.
    while (change > 0 && (yNickels || yDimes || yQuarters || yLoonies || yToonies))
  	{

			// Converts the change value to actual quantities of coins to dispense
  		coinsToDispense(change, nNickels, nDimes, nQuarters, nLoonies, nToonies,
    						  	  yNickels, yDimes, yQuarters, yLoonies, yToonies);

    	eraseDisplay();

    	displayBigTextLine(5, " Attempting:");
    	displayBigTextLine(7, "    $%02.2f", change / 100.0);

    	displayTextLine(14, "Attempting to Dispense: ");
    	displayTextLine(15, "%dN %dD %dQ %dL %dT", nNickels, nDimes, nQuarters, nLoonies, nToonies);

    	delay(500);

    	// Tries to output coins, and stores number of each coin actually output in nCoin
	    nNickelsR = getCoins(0, nNickels);
	    nDimesR = getCoins(1, nDimes);
	    nQuartersR = getCoins(2, nQuarters);
	    nLooniesR = getCoins(3, nLoonies);
	    nTooniesR = getCoins(4, nToonies);

	    // Comares wanted outout to what actually got but if was false before remains false
	    yNickels = yNickels && nNickelsR == nNickels;
	    yDimes = yDimes && nDimesR == nDimes;
	    yQuarters = yQuarters && nQuartersR == nQuarters;
	    yLoonies = yLoonies && nLooniesR == nLoonies;
	    yToonies = yToonies && nTooniesR == nToonies;

			// Calculates the new remaining change value to dispense
	    change = change - (nNickelsR * 5 + nDimesR * 10 + nQuartersR * 25 + nLooniesR * 100 + nTooniesR * 200);

			// Error message for when no coins are available
	    if (!(yNickels || yDimes || yQuarters || yLoonies || yToonies))
		  {
		  	eraseDisplay();
		  	displayBigTextLine(5, " Sorry. Not");
		  	displayBigTextLine(7, " enough coins!");
		  	delay(1000);
		  	eraseDisplay();
			}

	    if (change > 0)
	    {
	    	displayTextLine(7, "Not enough coins.");
    		displayTextLine(8, "Trying next closest amount.");
	  	}

			// For monitoring the details of the coin dispensing process
	    displayTextLine(12, "Available (0/false, 1/true): ");
	    displayTextLine(13, "%dN %dD %dQ %dL %dT", yNickels, yDimes, yQuarters, yLoonies, yToonies);
	    displayTextLine(14, "Number Dispensed: ");
	    displayTextLine(15, "%dN %dD %dQ %dL %dT CHANGE LEFT: %d", nNickelsR, nDimesR, nQuartersR, nLooniesR, nTooniesR, change);

	    delay(500);

	 	}

  }
}
