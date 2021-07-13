#ifndef ELIMINATIONANALYSER_H
#define ELIMINATIONANALYSER_H

class EliminationAnalyser
{
	/*
	 * 1. Load config file.
	 * 2. Enumerate video directory.
	 * 3. Iterate over the files, opening them in OpenCV.
	 * 4. For each frame, check for the "ELIMINATED {PLAYERNAME}" text.
	 * 5. If found, save the player name into a vector.
	 * 6. Once all the files have been processed, write the results to a CSV at the file location defined in the config file.
	 *
	 * * CSV file should be in the form of:
	 *		player name, times eliminated by you, eliminated at begin, eliminated at end, file name
	 *
	 *	* Info:
	 *		Player name is self-explanatory
	 *		Times eliminated by you is a simple int counter of how many times the player name occurs.
	 *		Eliminated at begin is the timestamp in the video the elimination occurred at, minus x seconds (or the start of the video of < 0.00s).
	 *		Eliminated at end is the timestamp in the video the elimination occurred at, plus x seconds (or the end of the video if + 2.00 is over the video length).
	 *		File name is the source video file's name (not path).
	 *
	 *	The time x value is defined within the config file.
	 */
};

#endif // ELIMINATIONANALYSER_H