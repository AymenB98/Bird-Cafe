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
		// IP address of pi
		$ip = "127.0.0.1";
		// Use port number 5000
		$port = 5000;
		// Print correct error message if socket creation fails
		if(!$socket)
		{
			$errorCode = socket_last_error();
			$errorMsg = socket_strerror($errorCode);
			
			die("Could not create socket: [$errorCode] $errorMsg \n");
		}
		
		// Bind socket
		$bind = socket_bind($socket, $ip, $port);
		// Print correct error message if socket binding fails
		if(!$bind)
		{
			$errorCode = socket_last_error();
			$errorMsg = socket_strerror($errorCode);
			
			die("Could not bind socket: [$errorCode] $errorMsg \n");
		}
		
		// Receive data
		$rcvStatus = socket_recvfrom($socket, $data, 1, 0, $ip, $port);
		
		// Use RX packet to update stats
		packetCount($data);

		socket_close($socket);
		return $this->socket = $socket;
	}
}

/* @brief	Retreive contents of .csv file and place in 2D array
 * 
 * @return $fullArray 2D array with full csv contents 
 */
function csvContents()
{
	// Create empty 2D array where contents of .csv file will be placed
	$fullArray = array();
	// Open .csv file
	$statsFile = fopen("official.csv", "a+") or die("Cannot open file");

	// Read each line of .csv file until the last line is reached
	while(($entry = fgetcsv($statsFile, 100, ",")) !== FALSE)
	{
		// Add each line to the empty array
		array_push($fullArray, $entry);
	}

	fclose($statsFile);
	return $fullArray;
}

/* @brief	Read number of birds previously logged in csv file
 * 
 * @return $birdNumber	Number of birds logged in csv file
 */
function getBirdCount()
{
	// Get contents of .csv file into array 
	$fileArray = file("official.csv");
	// Get the size of the array (rows)
	$size = count($fileArray);
	// Extract the last entry for the no. of birds
	$lastEntry = csvContents();
	$birds = $lastEntry[$size - 1][1];
	// Convert string to int
	$birdNumber = intval($birds);

	return $birdNumber;
}

/* @brief	Read number of imposters previously logged in csv file
 * 
 * @return $imposterNumber	Number of imposters logged in csv file
 */
function getImposterCount()
{
	// Get contents of .csv file into array 
	$fileArray = file("official.csv");
	// Get the size of the array (rows)
	$size = count($fileArray);
	// Extract the last entry for the no. of imposters
	$lastEntry = csvContents();
	$imposters = $lastEntry[$size - 1][2];
	// Convert string to int
	$imposterNumber = intval($imposters);

	return $imposterNumber;
}

/* @brief	Check the most recent date entry
 * 
 * @return $status	True if last date was the same as today's date
 */
function dateCheck()
{
	// Open .csv file
	$statsFile = fopen("official.csv", "a+") or die("Cannot open file");
	// Extract contents of .csv file into an array
	$fileArray = file("official.csv");
	// Get size of array (rows)
	$arraySize = count($fileArray);
	// Extract last entry for date
	$lastEntry = csvContents();
	$lastDate = $lastEntry[$arraySize - 1][0];

	fclose($statsFile);

	if($lastDate != date("Ymd"))
	{
		$status = false;
	}
	else
	{
		$status = true;
	}
	return $status;
}


/* @brief	Change display of visitor numbers based on received packet

 * @param $rcvPacket UDP packet received from C++ code
 * 
 * @return none
 */
function packetCount($rcvPacket)
{
	// Get current bird and imposter counts
	$birds = getBirdCount();
	$imposters = getImposterCount();
	// Check the date
	$dateStatus = dateCheck();

	$statsFile = fopen("official.csv", "a+");

	switch($rcvPacket)
	{
		// Bird detected
		case "b":
			if($dateStatus)
			{
				// Increment count if last entry matches today's date
				$birds++;
			}
			else
			{
				// Reset count if this is first entry of the day
				$birds = 1;
				$imposters = 0;
			}

			// Create new entry for .csv file
			$entryArray = array(date("Ymd"), $birds, $imposters);
			fputcsv($statsFile, $entryArray);

			break;

		// Imposter detected
		case "i":
			if($dateStatus)
			{
				$imposters++;
			}
			else
			{
				$birds =  0;
				$imposters = 1;
			}

			// Create new entry for .csv file
			$entryArray = array(date("Ymd"), $birds, $imposters);
			fputcsv($statsFile, $entryArray);

			break;
		
		// No update, packet still needs to be received so page is loaded
		case "n":
			// Do nothing
			break;
	}

	fclose($statsFile);

	// Display the number of birds to user
	echo "<b>" .$birds. " bird(s) have visited your cafe today: " .date("d/m/y"). "</br>";
	echo "<b>" .$imposters. " imposter(s) have visited your cafe today </br>";
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