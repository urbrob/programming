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
include 'connect.php';

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



$query = "SELECT a.id AS ile, a.tytul AS tytul 
									FROM albumy AS a
									JOIN zadjecia AS z
									ON a.id=z.id_albumu
									GROUP BY a.id
									HAVING SUM(z.zaakceptowane)>0";
$result = mysqli_query($conn,$query);
$ile = mysqli_num_rows($result);
$pom = 1; //20;

			$pages = $ile/$pom; 
			$page = (isset($_GET['strona'])) ? $_GET['strona'] : 1;
			$sqlpage = $pom*($page-1);
			if(isset($_GET['sortuj'])){
			switch ($_GET['sortuj']) 
			{
				case 'tytul':
					$_SESSION['sortuj'] = 'a.tytul';
					break;

				case 'data':
					$_SESSION['sortuj'] = 'a.data';
					break;
				
				case 'nick':
					$_SESSION['sortuj'] = 'u.login';
					break;
			}}
			$sortuj = (isset($_SESSION['sortuj'])) ? $_SESSION['sortuj'] : 'a.tytul';
			$query = "SELECT a.id AS id_a, z.id AS id_z, a.tytul AS tytul, u.login AS login, a.data AS data, z.zaakceptowane AS acpt
									FROM albumy AS a
									JOIN uzytkownicy AS u
									ON a.id_uzytkownika=u.id
									JOIN zadjecia AS z
									ON a.id=z.id_albumu
									WHERE z.zaakceptowane>0
									GROUP BY a.id
									HAVING SUM(z.zaakceptowane)>0
									ORDER BY $sortuj
									limit $sqlpage,$pom";
			$result = mysqli_query($conn,$query);
			while($row = mysqli_fetch_assoc($result))
			{
				$id_albumu = $row['id_a'];
				$id_zdj = $row['id_z'];
				$tytul = $row['tytul'];
				$login = $row['login'];
				$data = $row['data'];
				$acpt = $row['acpt'];
				echo "<a class='dymek' href='album.php?id_albumu=$id_albumu'><img class='dymek' src='img/$id_albumu/$id_zdj' width='180px' height='180px'><span>Tytuł galerii: $tytul<br>Autor: $login<br>Data utworzenia: $data</span></a>";
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
				echo "<a class='btn btn-default' href='galeria.php?strona=$i'>$i</a>";
			}}
		?>
		<br><a class="btn btn-success" href='galeria.php?sortuj=tytul'>Nazwa</a>
		<a class="btn btn-danger" href='galeria.php?sortuj=data'>Data</a>
		<a class="btn btn-danger" href='galeria.php?sortuj=nick'>Autor</a>
	</div>
	</body>
	
	</html>