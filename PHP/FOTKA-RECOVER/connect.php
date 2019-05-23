	<?php
	$servername = "localhost";
$username = "root";
$password = "";
$dbname = "ave";
session_start();
$_SESSION['error'] = '';
$conn = mysqli_connect($servername, $username, $password, $dbname);
mysqli_query($conn, 'SET NAMES utf8');
mysqli_query($conn, 'SET CHARACTER SET utf8');
mysqli_query($conn, "SET collation_connection = utf8_polish_ci");
$blady = 0;
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

	
	?>