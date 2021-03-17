<!DOCTYPE html>
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

/* @brief 	Class which creates and binds UDP socket
 * 
 */
class UdpSocket
{	
	public $socket, $errorCode;
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
		// Display on web page
		echo "<b>" .$data. "</b>";
		socket_close($socket);
		return $this->socket = $socket;
	}
	/* @brief	Destrcutor which closes socket automatically
	 * 
	 * @return none 
	 */
	//function __destruct()
	//{
		//socket_close($this->socket);
	//}
	
}

$listenSocket = new UdpSocket();
echo "<b> Birds have visted your cafe today: " . date("d/m/y") . "</br>";


?>

<!-- Provide a link to the statistics page -->
<a style="color:#c966a4;font-size:50px;" href="stats_page.php"> View more bird feeder stats!</a>
<!-- Links to social media sites and GitHub -->
<p style="font-size:30px;" You can view the code for this project at the following link:</p>
<a style="font-size:30px;" href="https://github.com/AymenB98/Bird-Cafe">Bird Cafe GitHub repo - </a>
<a style="font-size:30px;" href="https://twitter.com/smartbirdcafe">Twitter - </a>
<a style="font-size:30px;" href="https://www.instagram.com/smartbirdcafe/?igshid=xx0j8aub0pb4">Instagram</a>

</centre>
</body>
</html>
