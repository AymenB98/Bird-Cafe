<!DOCTYPE html>
<!-- Author: Aymen Benylles -->
<html>
<head>
<!-- Webpage title -->
<title>Cafe stats</title>
<style>
    body {
        width: 35em;
        margin: 0 auto;
        font-family: Tahoma, Verdana, Arial, sans-serif;
    }
</style>

<script src="//cdnjs.cloudflare.com/ajax/libs/dygraph/2.1.0/dygraph.min.js"></script>
<link rel="stylesheet" href="//cdnjs.cloudflare.com/ajax/libs/dygraph/2.1.0/dygraph.min.css"/>

</head>

<body>
<!-- Greeting message is centred just like all other text in the file -->
<center><h1 style="font-size:80px;">Cafe Statistics</h1>
<!-- Tell the user what this page is for. -->
<p style="color:#c966a4;font-size:55px;"> Take a look at some in-depth stats about your bird feeder!</p>


<?php
// Author: Aymen Benylles
// This code was adapted from the following GitHub repo:
// https://github.com/berndporr/rpi_AD7705_daq
// This was adapted from the file "graph.php" by Bernd Porr

/* @brief 	Mock class to track the number of birds visiting the feeder.
 * 
 */
class VisitStats
{
public $totalVisits;
	/* @brief 	Mock class to track the number of birds visiting the feeder.
	 * 
	 * @param $totalVisits how many visits has the feeder had
	 * 
	 * @return $totalVisits
	 */
	function birdCount($totalVisits)
	{
		return $this->totalVisits = $totalVisits;
	}

}

/* @brief 	Class which creates a .csv file with bird stats to display to user.
 * 
 */
class CsvCreate
{	
public $birdNumber, $imposterNumber, $statsFile, $stats, $pythonResult, $execResult, $append;
	/* @brief	Create .csv file so it can be displayed to user
	 * 
	 * @param $birdNumber How many birds have visited the feeder
	 * @param $imposterNumber How many animals have visited that are not birds
	 * 
	 * @return none 
	 */
	function __construct($birdNumber, $imposterNumber)
	{
		$today = date("Ymd");
		$appendEntry = array($today, $birdNumber, $imposterNumber);
							
		// Open .csv file
		$statsFile = fopen("official.csv", "a+") or die("Cannot open file");
		
		// Write data to csv file.
		// Dygraph labels mean that PHP code does not need to check for
		// empty line.
		fputcsv($statsFile, $appendEntry);
		
		// Now that .csv file has been adapted, close it
		fclose($statsFile) or die("Cannot close file");
	}
	
	/* @brief	Execute external Python script
	 * 
	 * @return $execResult Null when execution has failed, equal to script output when
	 * successful
	 */
	function pythonScript()
	{
		// Perform python script
		$execResult = system("python helloworld.py", $pythonResult);
		return $execResult;
	}
}
// Create (mock) data about birds that have visited
$crow = new VisitStats();
$crowNumber = $crow->birdCount(7);

// Create new object which will create .csv for user graph
$csvGraph = new CsvCreate($crowNumber, 1);
// Execute Python script
$csvGraph->pythonScript();
?>

<!-- Mock graph which shows how many birds have visisted the feeder over time (also imposters) -->
	<div id="graphdiv2" style="width: 500px; height: 500px;"></div>
	<script type="text/javascript">
	 g2 = new Dygraph(
		document.getElementById("graphdiv2"),
		"official.csv",
		{
			// Label data to make php entry simpler
			labels:["Date", "Birds", "Imposters"],
			// Display legend
			legend: 'always',
			// Show rolling average
			rollPeriod: 1,
			// Allow user to change rolling period
			showRoller: true,
		}        
	  );
	</script>   

</body>
</html>
