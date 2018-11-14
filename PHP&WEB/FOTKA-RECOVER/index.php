<html>
	
	<head>
	<link rel="stylesheet" type="text/css" href="css/style.css">
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
<link href="https://fonts.googleapis.com/css?family=Play:400,700" rel="stylesheet">
		<title>Hello World</title>
		<meta charset = "utf-8">
	</head>
	
	<body>
<?php

?>

	<div id='log'>
	<form action='logowanie.php' method='post'>
	<div id="logowanie">
	<table>
	<b class="ttl">Zaloguj się:</b>
	<tr><td><input class="loginput" placeholder="Login" type='text' name="login" required id="login"  /></td></tr>
	<tr><td><input class="loginput"  placeholder="Hasło"type='password' name="haslo" required id="haslo"  /></td></tr>
	<tr><td><input class="przycisk" type="submit" name="wyslij" value="Zaloguj" /></td></tr>
	<tr><td><a href="galeria.php">Zaloguj jako gość</a></td></tr>
		
	</table>
	 </div>
	 <?php
include 'connect.php';
	
?>
	</form>
	</div>
	<div id='reg'>
	<form action='rejestracja.php' method='post'>
	<div id="rejestracja">
	<table>
	<b class="ttl">Zarejestruj się:</b><br><br>
	<tr><td><input class="reginput" placeholder="Login" type='text' name="rlogin" required id="rlogin"/>( Login od 6 do 20 znaków, tylko litery i cyfry)</td></tr>
	<tr><td><input  class="reginput" placeholder="Hasło" name="rhaslo" type='password' id="rhaslo"  required />( Hasło od 6 do 20 znaków, minimum 1 duża litera, 1 mała litera i 1 cyfra)</td></tr>
	<tr><td><input class="reginput" placeholder="Potwierdź hasło" type='password' name="prhaslo" required id="prhaslo"  /></td></tr>
	<tr><td><input class="reginput"  placeholder="E-mail" name="rmail" type='email' required id="rmail"  /></td></tr>
	<tr><td><input class="przycisk" type="submit" name="wyslij" value="Zarejestruj"> </td></tr>
	</table>
	 </div>
	</form>
	</div><br>
	
<?php
	echo '<div id="reg">';
	if(isset($_SESSION['error'])){
		for($i=0;$i==$_SESSION['error'];$i++){
			echo $_SESSION['error'];
		}
		echo '</div>';
	}
?>

</div>
	</body>
	</html>