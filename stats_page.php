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
<link rel="stylesheet" href="//cdnjs.cloudflare.com/ajax/libs/dygraph/2.1.0/dygraph.min.css" />

</head>

<body>
<!-- Greeting message is centred just like all other text in the file -->
<center><h1 style="font-size:80px;">Cafe Statistics</h1>
<!-- Tell the user what this page is for. -->
<p style="color:#c966a4;font-size:55px;"> Take a look at some in-depth stats about your bird feeder!</p>


<?php
/* @brief 	Mock class to track the number of birds visiting the feeder.
 * 
 */
class VisitStats
{
public $totalVisits;

	function birdCount($totalVisits)
	{
		return $this->totalVisits = $totalVisits;
	}

}

/* @brief	Create .csv file so it can be displayed to user
 * 
 * @param $birdNumber How many birds have visited the feeder
 * @param $imposterNumber How many animals have visited that are not birds
 * 
 * @retrn none 
 */
function csvCreate($birdNumber, $imposterNumber)
{	
	// Data that will be written to .csv file
	// This will be a table that is turned into a graph
	// The user will see the graph when they open the stats page
	$stats = array(
		// The x-axis should show the date and y-axis the number of birds/imposters
		array("date", "Birds", "Imposters"), 
		// Fill this with fake data until integration with other code is completed
		array(date("Y-m-d"), $birdNumber, $imposterNumber));
	// Open .csv file
	$statsFile = fopen("visits.csv", "w") or die("Cannot open file");

	// Place the arrays in the .csv file
	foreach($stats as $line)
	{
		fputcsv($statsFile, $line);
	}

	csvAppend($birdNumber, $imposterNumber, $statsFile);
}

/* @brief	Append data to .csv file and close it
 * 
 * @param $birdNumber How many birds have visited the feeder
 * @param $imposterNumber How many animals have visited that are not birds
 * @param $csvFile File handle for .csv file used to generate graph		
 * 
 * @retrn none 
 */
function csvAppend($birdNumber, $imposterNumber, $csvFile)
{
	// Append row to .csv file
	$append = array(date("Y-m-d"), $birdNumber, $imposterNumber);
	fputcsv($csvFile, $append);

	// Append some more data to fill in the graph
	$appendTrialData = array("2021-3-4", 5, 1); 
	fputcsv($csvFile, $appendTrialData);
		
	// Now that .csv file has been adapted, close it
	fclose($csvFile);	
}

// Create (mock) data about birds that have visited (10 crows and 5 sparrows)
$crow = new VisitStats();
$crowNumber = $crow->birdCount(7);
$sparrow = new VisitStats();
$sparrowNumber = $sparrow->birdCount(5);

csvCreate($crowNumber, $sparrowNumber);

?>

<!-- Mock graph which shows how many birds have visisted the feeder over time (also imposters) -->
	<div id="graphdiv" style="width: 500px; height: 500px; color: #c966a4;"></div>
	<script type="text/javascript">
	 g = new Dygraph(
	     document.getElementById("graphdiv"),
	     "visits.csv",
             {
                 legend:'always',
		 color: '#c966a4',
             }
	 );
	</script>   

</body>
</html>
