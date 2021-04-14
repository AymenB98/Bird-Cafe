<!DOCTYPE html>
<!-- 
Author: Aymen Benylles
This code was adapted from the following GitHub repo:
https://github.com/berndporr/rpi_AD7705_daq
This was adapted from the file "graph.php" by Bernd Porr
-->
<html>
<head>
<!-- Refresh page every second-->
<!-- <meta http-equiv="refresh" content="1"> -->
<!-- Webpage title -->
<title>Welcome to the Bird Cafe!</title>
<style>
    body {
        width: 35em;
        margin: 0 auto;
        font-family: Tahoma, Verdana, Arial, sans-serif;
		font-size: 55px;
		color: #c966a4;
    }
</style>
</head>
<body>
<!-- Greeting message is centred just like all other text in the file -->
<center><h1 style="font-size:60px;">Welcome to the Bird Cafe!!!</h1>

<!-- Display product logo -->
<img src="bird_logo_pink.jpg">

<!--Until hardware is introduced to project, placeholder number of "0" is used for the bird count" -->
<h1 style="color:#c966a4;font-size:60px;"><b></b></h1>

<!-- PHP code to display the current date -->
<?php 
// Author: Aymen Benylles
// This code was adapted from the following GitHub repo:
// https://github.com/berndporr/rpi_AD7705_daq
// This was adapted from the file "graph.php" by Bernd Porr

/* @brief 	Class which creates and binds UDP socket
 * 
 */
class UdpSocket
{	
	public $socket, $errorCode, $birds, $imposters, $lastDate;
	/* @brief	Constructor which receives data via UDP socket
	 * 
	 * @return none 
	 */
	function __construct()
	{
		// Create socket
		$socket = socket_create(AF_INET, SOCK_DGRAM, 0);
		// Set timeout for socket to 0.5 seconds
		socket_set_option($socket,SOL_SOCKET,SO_RCVTIMEO, array("sec"=>1,"usec"=>0));
		// IP address of pi
		$ip = "127.0.0.1";
		// Use port number 5000
		$port = 5000;
		// Print correct error message if socket creation fails
		if(!$socket)
		{
			$errorCode = socket_last_error();
			$errorMsg = socket_strerror($errorCode);
			
		}
		
		// Bind socket
		$bind = socket_bind($socket, $ip, $port);

		if(!$bind)
		{
			$errorCode = socket_last_error();
			$errorMsg = socket_strerror($errorCode);
			
		}
		
		// Receive data
		$rcvStatus = socket_recvfrom($socket, $data, 1, 0, $ip, $port);
		
		// Session is closed if no packet is received
		if($rcvStatus == FALSE)
		{
			echo "<b> Session closed. </br>";
			
		}
		// Only append data if packet received
		else
		{
			// Use RX packet to update stats
			$timeStamp = $this->csvAppend($data);
			// Calculate time since last visit
			$this->lastVisit($timeStamp);
			echo "<b>" .$data. " visit(s) in this session.</br>";

		}
		socket_close($socket);
		

		return $this->socket = $socket;
	}

	/* @brief	Retreive contents of .csv file and place in 2D array
	 * 
	 * @return $fullArray 2D array with full csv contents 
	 */
	function csvContents($csvHandle)
	{
	// Create empty 2D array where contents of .csv file will be placed
	$fullArray = array();

	// Read each line of .csv file until the last line is reached
	while(($entry = fgetcsv($csvHandle, 500, ",")) !== FALSE)
	{
		// Add each line to the empty array
		array_push($fullArray, $entry);
	}

	return $this->fullArray = $fullArray;
	}

	/* @brief	Append array onto .csv file based on RX packet
	 * 
	 * @param $updateCode Character determining what kind of visit has occurred.
	 * 
	 * @return $lastTime How long since last visit 
	 */
	function csvAppend($message)
	{
		// Open .csv file
		$statsFile = fopen("official.csv", "a+") or die("Cannot open file.");
		// Get last entry of csv count
		$csvArray = $this->csvContents($statsFile);

		// Fill array with 0s if file is empty
		if(filesize("official.csv") == 0)
		{
			for($i = 0; $i < 3; $i++)
			{
				// Fill with valid entries
				$csvArray[0][$i] = 0;
			}
		}

		//Get the number of rows in the array
		$rows = count($csvArray);

		// Do not append data if no new visits have been registered
		if($message != ($csvArray[$rows - 1][1]))
		{
			// Create array with current time
			$currentTime = time()*1000;
			$trialArray = array($currentTime, $message);

			// Append array to .csv file
			fputcsv($statsFile, $trialArray) or die("Cannot write to file.");
		}

		fclose($statsFile) or die("Cannot close file.");

		// Get last time stamp to calculte time since last visit
		$lastTime = $csvArray[$rows - 1][0];
		return $this->lastTime = $lastTime;
	}

	/* @brief	Calculate and display time since last visit.
	 * 
	 * @param $lastStamp Most recent time stamp from .csv file.
	 * 
	 * @return none
	 */
	function lastVisit($lastStamp)
	{
		$timeDiffSeconds = time() - ($lastStamp / 1000); 
		$timeDiffMins = $timeDiffSeconds / 60;
		$timeDiffHours = $timeDiffMins / 60;
		$timeDiffDays = $timeDiffHours / 24;
		
		if($timeDiffMins < 1)
		{
			echo "<b>" .round($timeDiffSeconds). "s since last visit </br>";
		}
		else if($timeDiffHours < 1)
		{
			echo "<b>" .round($timeDiffMins). " minute(s) since last visit </br>";
		}
		else if($timeDiffDays < 1)
		{
			echo "<b>" .round($timeDiffHours). " hour(s) since last visit </br>";
		}
		else if($timeDiffDays >= 1)
		{
			if($timeDiffDays > 1000)
			{
				echo "<b> No visit registered in this session (yet). </br>";
			}
			echo "<b>" .round($timeDiffDays). " day(s) since last visit </br>";
		}

		return $this->timeDiffMins = $timeDiffDays;
	}
}

$listenSocket = new UdpSocket();	

?>

<!-- Provide a link to the statistics page -->
<a style="color:#c966a4;font-size:50px;" href="stats_page.html"> View more bird feeder stats!</a>
<!-- Links to social media sites and GitHub -->
<p style="font-size:30px;" You can view the code for this project at the following link:</p>
<a style="font-size:30px;" href="https://github.com/AymenB98/Bird-Cafe">Bird Cafe GitHub repo - </a>
<a style="font-size:30px;" href="https://twitter.com/smartbirdcafe">Twitter - </a>
<a style="font-size:30px;" href="https://www.instagram.com/smartbirdcafe/?igshid=xx0j8aub0pb4">Instagram</a>

</centre>
</body>
</html>