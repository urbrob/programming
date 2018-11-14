<!DOCTYPE html>
<html>
<head>
	<title>Strona testowa</title>
	<meta charset="UTF-8">
	<link rel="stylesheet" type="text/css" href="css/style.css">
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
<link href="https://fonts.googleapis.com/css?family=Play:400,700" rel="stylesheet">
</head>
<body>
	<?php
	include 'connect.php';
	include 'menu.php';
		
	
	?>
	<div id="reg">
	<form method="post" >
	<table>
			<tr><td><input type="text" name="album"  value=""  ></td></tr>
			<tr><td><input class="przycisk" type="submit" name="wyslij" value="Dodaj album" /></td></tr>
		</table>
		</form>
	</div>
	
	<?php
	if(isset($_POST['album'])){
	$nazwa = str_replace('"', "&quot;", $_POST['album']);
	$nazwa = str_replace("'", "&#039;", $nazwa);

	$czas = date('Y-m-d');
	if (strlen($_POST['album'])>=3 && strlen($_POST['album'])<=20 ){
		$sql = "INSERT INTO albumy(tytul,data,id_uzytkownika)
		VALUES ('".$nazwa."', '".$czas."', '".$_SESSION['user']['id']."')";
				
	}else
	if(isset($_POST['album'])){
		echo 'Więcej niż 3 znaki, mniej niż 20. Tylko cyfry i litery.';
	}
	if($sql){
	if (mysqli_query($conn, $sql)) {
		 $ostatni =mysqli_insert_id($conn);
		if (!file_exists('img/'.$ostatni)) {
    mkdir('img/'.$ostatni, 0777, true);
	echo "<script type='text/javascript'>alert('Dodano album');</script>";
}
header ("location:dodaj-foto.php");
				exit;
			
exit();
		
	} else {
		$_SESSION['error'] .= "Błąd: " . $sql . "<br>" . mysqli_error($conn);
	}
	}}
		if(!isset($_SESSION['user']['login'])){
				header ("location: index.php");
				exit;
			}
	?>
	
	
	</ul>
  </div>
</nav>

	
</body>
</html>