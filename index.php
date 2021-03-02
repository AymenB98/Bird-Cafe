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
<h1 style="color:#c966a4;font-size:60px;"><b>0</b></h1>

<!-- PHP code to display the current date -->
<?php echo "Birds have visted your cafe today: " . date("d/m/y") . "</br>"; ?>

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
