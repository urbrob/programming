﻿<html>
	
	<head>
	<link rel="stylesheet" type="text/css" href="css/style.css">
 <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
<link href="https://fonts.googleapis.com/css?family=Play:400,700" rel="stylesheet">
		<title>Hello World</title>
		<meta charset = "utf-8">
	</head>
	<body>
	  <?php
	include 'connect.php';
	include 'menu.php';
    ?>
	
<div id="container">

<header>Najnowsze</header>
<div id="galeria">
<?php
$query = "SELECT * FROM ZADJECIA 
			ORDER BY data ASC
			LIMIT 20 ";
$result = mysqli_query($conn, $query);
while($row = mysqli_fetch_assoc($result))
			{
				$id_albumu = $row['id_albumu'];
				$id_zdj = $row['id'];
				$tytul = $row['tytul'];
				
				$data = $row['data'];
				
				echo "<a class='dymek' href='foto.php?id_foto=$id_zdj'><img class='dymek' src='img/$id_albumu/$id_zdj' width='180px' height='180px'><span>Tytuł galerii: $tytul<br>Data utworzenia: $data</span></a>";
			}


?>

	
	
	
	</div>
</div>

	</body>
	</html>