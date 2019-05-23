<html>
	
	<head>
	<link rel="stylesheet" href="//netdna.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.min.css">
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
	include 'connect.php';
    ?>
	
	</ul>
  </div>
</nav>
<div id="container">

<header>GALERIA</header>
<div id="galeria">
<pre>
	  <?php 
	  if(isset($_GET['komentarz'])){
	  $komentarz = trim(htmlspecialchars((strip_tags($_GET['komentarz'])),ENT_QUOTES));
	  $sqlwyslij = "INSERT INTO `zadjecia_komentarze` (`id_zdjecia`, `id_uzytkownika`, `data`, `komentarz`, `zaakceptowany`) 
	  VALUES (".$_GET['id_foto'].", ".$_SESSION['user']['id'].", CURRENT_DATE, '".$_GET['komentarz']."', 1)";
	  $result = mysqli_query($conn, $sqlwyslij);
	  header ("location: foto.php?id_foto=".$_GET['id_foto']."");
	  exit;
	  unset($_GET['komentarz']);
	  }
  ?>
<?php

if(isset($_GET['star'])){
$pytanie = "INSERT INTO `zadjecia_oceny`(`id_zdjecia`, `id_uzytkownika`, `ocena`)
 VALUES (".$_GET['id_foto'].",".$_SESSION['user']['id'].",".$_GET['star'].")";
 mysqli_query($conn, $pytanie);
   header ("location: foto.php?id_foto=".$_GET['id_foto']."");
				exit;
 unset($_GET['star']);
 


 }
				$query = "SELECT *
				FROM zadjecia 
				WHERE id=".$_GET['id_foto']."";
				$result = mysqli_query($conn,$query);
				$row = mysqli_fetch_assoc($result);
				$id_albumu = $row['id_albumu'];
				$id_zdj = $row['id'];
				$tytul = $row['tytul'];
				$id_uzytkownika = $row['id_uzytkownika'];
				$data = $row['data'];
				$query = "SELECT * from uzytkownicy
							WHERE id=".$id_uzytkownika."";
				$result = mysqli_query($conn,$query);
				$row = mysqli_fetch_assoc($result);
				$login = $row['login'];
				$query = "SELECT * from albumy
					WHERE id=".$id_albumu."";
						$result = mysqli_query($conn,$query);
				$row = mysqli_fetch_assoc($result);
				$tytulalb = $row['tytul'];
				echo '<table class="table">
					<tr class="Warning">
					<th>Data dodania</th>
					<th>Login Użytkownika</th>
					<th>Nazwa zdjęcia</th>
					<th>Album</th></tr>
					<tr class="info">
					<th>'.$data.'</th>
					<th>'.$login.'</th>
					<th>'.$tytul.'</th>
					<th><a href="album.php?id_albumu='.$id_albumu.'">'.$tytulalb.'</th></tr></table>';
				echo "<center><img src='img/".$id_albumu."/".$_GET['id_foto']."' ></center>";
				$query = "SELECT avg(ocena) as ocena, count(*) as ile from zadjecia_oceny
					WHERE id_zdjecia=".$id_zdj."";
						$result = mysqli_query($conn,$query);
						$row = mysqli_fetch_assoc($result);
						
			

?>
</div>
<?php 
				echo "<center><h2>Średnia ocen: ".round($row['ocena'], 1)." Przy ilości ".$row['ile']." ocen</h2></center>";
?>
<?php if(isset($_SESSION['user']['login'])){?>
<div class="stars">
		<form action="" style="text-align:center;">
			  <?php $sql = "SELECT count(*) as jestes FROM zadjecia_oceny WHERE id_uzytkownika=".$_SESSION['user']['id']." AND id_zdjecia=".$_GET['id_foto'];
					$result= mysqli_query($conn, $sql);
					$rowek = mysqli_fetch_assoc($result);
					if($rowek['jestes']==0){
				?>

			    <input type="hidden" value="<?php echo $_GET['id_foto']; ?>" name="id_foto">
			    <input class="star star-10" id="star-5" type="radio" value="10" name="star"/>
				<label class="star star-10" for="star-5"></label>
				<input class="star star-9" id="star-9" type="radio" value="9" name="star"/>
				<label class="star star-9" for="star-9"></label>
				<input class="star star-8" id="star-8" type="radio" value="8" name="star"/>
				<label class="star star-8" for="star-8"></label>
				<input class="star star-7" id="star-7" type="radio" value="7" name="star"/>
				<label class="star star-7" for="star-7"></label>
				<input class="star star-6" id="star-6" type="radio" value="6" name="star"/>
				<label class="star star-6" for="star-6"></label>
				<input class="star star-5" id="star-10" type="radio" value="5" name="star"/>
				<label class="star star-5" for="star-10"></label>
				<input class="star star-4" id="star-4" type="radio" value="4" name="star"/>
				<label class="star star-4" for="star-4"></label>
				<input class="star star-3" id="star-3" type="radio" value="3" name="star"/>
				<label class="star star-3" for="star-3"></label>
				<input class="star star-2" id="star-2" type="radio" value="2" name="star"/>
				<label class="star star-2" for="star-2"></label>
				<input class="star star-1" id="star-1" type="radio" value="1" name="star"/>
				<label class="star star-1" for="star-1"></label>
	<br>
	<input type="submit" value="Oceń">
	<?php } ?>
	</form>
	
				<form action="" style="text-align:center;">
				<input type="hidden" value="<?php echo $_GET['id_foto']; ?>" name="id_foto">
				<textarea rows="3" cols="50" name="komentarz"></textarea>
				<input type="submit" value="Komentuj TO!">
				</form>
<?php } ?>
  <?php
  $sqlkom = 'SELECT * from zadjecia_komentarze
			JOIN uzytkownicy 
			on uzytkownicy.id=zadjecia_komentarze.id_uzytkownika 
			WHERE id_zdjecia='.$_GET['id_foto'].'
			AND zadjecia_komentarze.zaakceptowany=1';
  $result = mysqli_query($conn, $sqlkom);
  while($row = mysqli_fetch_assoc($result)){
	  
		echo '<center><div class="container">';
		echo '<div class="row">';
		echo '<div class="col-sm-5">';
		echo '<div class="panel panel-default">';
		echo '<div class="panel-heading">';
		echo '<strong>'.$row['login'].'</strong> <span class="text-muted">'.$row['data'].'</span></div>';
		echo '<div class="panel-body">';
		echo $row['komentarz'];
		echo '</div></div></div></div></div></center>';
  }
  if (mysqli_num_rows($result)==0) { 
  echo '<div class="container"><div class="panel-heading"><div class="panel-body">Nie ma jeszcze dodanego żednego komentarza</div></div></div>';
  }
 echo' <center><a href="album.php?id_albumu='.$id_albumu.'">Powrót do albumu</a></center>'
	?>
	
</pre>
	</body>
	
	</html>