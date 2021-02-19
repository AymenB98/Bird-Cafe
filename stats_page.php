<!DOCTYPE html> <html> <head> <!-- Webpage title --> <title>Cafe 
stats</title> <style>
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
<!-- Mock class to track the number of birds visiting the feeder. -->
class VisitStats
{
public $totalVisits;

	function birdCount($totalVisits)
	{
		return $this->totalVisits = $totalVisits;
	}

}

$crow = new VisitStats();
$crow->birdCount(10);
?>


<!-- Mock graph which shows how many birds have visisted the feeder over time (also imposters) -->
	<div id="graphdiv"></div>
	<script type="text/javascript">
	 g = new Dygraph(
	     document.getElementById("graphdiv"),
	     "bird_stats_new.csv",
             {
                 legend:'always',
                 ticker: Dygraph.dateTicker
             }
	 );
	</script>   

</body>
</html>

