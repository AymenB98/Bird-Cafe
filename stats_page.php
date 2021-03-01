<!DOCTYPE html>
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
<p style="color:#c966a4;font-size:70px;"> Take a look at some in-depth stats about your bird feeder!</p>


<?php
// Mock class to track the number of birds visiting the feeder.
class VisitStats
{
public $totalVisits;

	function birdCount($totalVisits)
	{
		return $this->totalVisits = $totalVisits;
	}

}

// Create data about birds that have visited (10 crows and 5 sparrows)
$crow = new VisitStats();
$crowNumber = $crow->birdCount(10);
$sparrow = new VisitStats();
$sparrowNumber = $sparrow->birdCount(5);

// Data that will be written to .csv file
// This will be a table that is turned into a graph
// The user will see the graph when they open the stats page
$stats = array(
	// The x-axis should show the date and y-axis the number of birds/imposters
	array("date", "Birds", "Imposters"), 
	// Fill this with fake data until integration with other code is completed
	array(date("Y-m-d"), $crowNumber, 2),
	// In future, find a way to append a row of data to the .csv file in use
	array("2021-3-2", $sparrowNumber, 1));
// Open .csv file
$statsFile = fopen("visits.csv", "w");

// Place the arrays in the .csv file
foreach($stats as $line)
{
	fputcsv($statsFile, $line);
}

// Now that .csv file has been adapted, close it
fclose($statsFile);

?>


<!-- Mock graph which shows how many birds have visisted the feeder over time (also imposters) -->
	<div id="graphdiv"></div>
	<script type="text/javascript">
	 g = new Dygraph(
	     document.getElementById("graphdiv"),
	     "visits.csv",
             {
                 legend:'always',
                 ticker: Dygraph.dateTicker
             }
	 );
	</script>   

</body>
</html>
