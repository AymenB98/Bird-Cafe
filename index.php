<!DOCTYPE html>
<!-- 
Author: Aymen Benylles
This code was adapted from the following GitHub repo:
https://github.com/berndporr/rpi_AD7705_daq
This was adapted from the file "graph.php" by Bernd Porr
-->
<html>
<head>
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

<h1 style="color:#c966a4;font-size:60px;"><b></b></h1>

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
			// Display number of visits in last session
			$visits = $this->lastSessionVisits();
			echo "<b>" .$visits. " visit(s) were registered in your last session.</br>";
			
		}
		// Only append data if packet received
		else
		{
			// Use RX packet to update stats
			$timeStamp = $this->csvAppend($data);
			// Calculate time since last visit
			$this->lastUpdateTime($timeStamp);
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

		// Create array with current time
		$currentTime = time()*1000;
		$trialArray = array($currentTime, $message);

		// Append array to .csv file
		fputcsv($statsFile, $trialArray) or die("Cannot write to file.");

		fclose($statsFile) or die("Cannot close file.");

		// Get last time stamp to calculte time since last visit
		$lastTime = $csvArray[$rows - 1][0];
		return $this->lastTime = $lastTime;
	}

	/* @brief	Calculate and display time since last visit.
	 * 
	 * @param $lastStamp Most recent time stamp from .csv file.
	 * 
	 * @return $timeDiffMins Time ellapsed since last .csv entry (mins)
	 */
	function lastUpdateTime($lastStamp)
	{
		$timeDiffSeconds = time() - ($lastStamp / 1000); 
		$timeDiffMins = $timeDiffSeconds / 60;
		$timeDiffHours = $timeDiffMins / 60;
		$timeDiffDays = $timeDiffHours / 24;
		
		// Display the time so that a human can read it
		// This is when the user last clicked refresh
		$lastUpdateEpoch = time();
		echo "<b>This page was last updated at: " .date("r", $lastUpdateEpoch). "</br>";
		return $this->timeDiffMins = $timeDiffMins;
	}


	/* @brief	Determine number of visits in last session
	 *
	 * 
	 * @return $lastTotal How many visits registered in last session
	 */
	function lastSessionVisits()
	{
		// Open file
		$statsFile = fopen("official.csv", "a+") or die("Cannot open file.");
		// Get last entry of csv count
		$csvArray = $this->csvContents($statsFile);
		// Get number of rows in array
		$rows = count($csvArray);
		// Return number of visits in last session
		$lastTotal = $csvArray[$rows - 1][1];
		if($lastTotal > 7)
		{
			echo "<b> Wow! You had a lot of visits in your last session. </br>";
			echo "<b> Remember to clean your feeder to keep the local birds as healthy as possible. </br></br>"; 
		}
		return $this->lastTotal = $lastTotal;
	}
}

$listenSocket = new UdpSocket();

?>

<!-- Links to social media sites and GitHub -->
<p style="font-size:60px;" You can view the code for this project at the following link:</p>
<a style="font-size:60px;" href="https://github.com/AymenB98/Bird-Cafe">Bird Cafe GitHub repo - </a>
<a style="font-size:60px;" href="https://twitter.com/smartbirdcafe">Twitter - </a>
<a style="font-size:60px;" href="https://www.instagram.com/smartbirdcafe/?igshid=xx0j8aub0pb4">Instagram</a>

</centre>
</body>
</html>