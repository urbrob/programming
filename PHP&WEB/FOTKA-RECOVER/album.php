<html>
	
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
	  
	include 'menu.php';
    ?>
	
	</ul>
  </div>
</nav>
<div id="container">

<header>GALERIA</header>
<div id="galeria">
<pre>
<?php

include 'connect.php';
$pom = 2; //20;
			$page = (isset($_GET['strona'])) ? $_GET['strona'] : 1;
$sqlpage = $pom*($page-1);
		$sortuj = (isset($_SESSION['sortuj'])) ? $_SESSION['sortuj'] : 'a.tytul';
			$query = "SELECT zadjecia.id
									FROM zadjecia
									WHERE id_albumu=".$_GET['id_albumu']." and
									zaakceptowane=1";
			$result = mysqli_query($conn,$query);
			$ile = mysqli_num_rows($result);
			$pages = ceil($ile/$pom); 

			$query = "SELECT a.id AS id_a, z.id AS id_z, a.tytul AS tytul, u.login AS login, a.data AS data, a.zaakceptowane AS acpt FROM zadjecia	AS a 					JOIN uzytkownicy AS u 
									ON a.id_uzytkownika=u.id 
									JOIN albumy AS z
									ON z.id=a.id_albumu
									WHERE z.id=".$_GET['id_albumu']." and
									a.zaakceptowane=1
									GROUP BY a.id
									limit $sqlpage,$pom";
			$result = mysqli_query($conn,$query);			
			while($row = mysqli_fetch_assoc($result))
			{
				$id_albumu = $row['id_z'];
				$id_zdj = $row['id_a'];
				$tytul = $row['tytul'];
				$login = $row['login'];
				$data = $row['data'];
				$acpt = $row['acpt'];
				echo "<a class='dymek' href='foto.php?id_foto=$id_zdj'><img class='dymek' src='img/$id_albumu/$id_zdj' width='180px' height='180px'><span>Tytuł galerii: $tytul<br>Autor: $login<br>Data utworzenia: $data</span></a>";
			}

?>
</pre>

	
	
		
		<?php
			//STRONNICOWANIE - PRZYCISKI
			if($pages<=1){
			echo "<a class='btn btn-default' href='galeria.php?strona=1'>1</a>";}
			else{
			for($i=1; $i<=$pages; $i++)
			{
				echo "<a class='btn btn-default' href='album.php?strona=$i&id_albumu=".$id_albumu."'>$i</a>";
			}}
			echo "<a href='galeria.php'>Powrót do galerii</a>";
		?>
	
	</div>
	</body>
	
	</html>