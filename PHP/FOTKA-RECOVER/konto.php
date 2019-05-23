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
	
<div id="container">
<header>Moje konto</header>
<div id="galeria">
 <nav class="navbar navbar-default">
  <div class="container-fluid">
          <ul class="nav navbar-nav wyjustowanie" >
           <li><a href="konto.php?Mod=dane">Moje dane</a></li>
	       <li><a href="konto.php?Mod=albumy">Moje albumy</a></li>
		   <li><a href="konto.php?Mod=zdjecia">Moje zdjecia</a></li>
		  
          </ul>
       
      </div>
	  </nav>
	   
<?php
	//ZMIANA DANYCH
	if(isset($_GET['Mod'])){
		if($_GET['Mod']=='dane')
		{
			
	echo '<div id="trocheprawo" style="margin-left:50px">';
	echo '<form action="" method="GET">';
	echo '<table><b class="ttl">Zmień dane:</b><br><br>';
	echo '<tr><td><input  class="reginput" placeholder="Hasło" name="rhaslo" type="password" id="rhaslo"  />( Hasło od 6 do 20 znaków, minimum 1 duża litera, 1 mała litera i 1 cyfra)</td></tr>';
	echo '<tr><td><input class="reginput"  placeholder="E-mail" name="rmail" type="email" id="rmail" /></td></tr>';
	echo '<tr><td><input class="przycisk" type="submit" name="wyslij" value="Updatuj" /> </td></tr>';
	echo '</table>';
	echo '</form>';
	echo '</div>';
		}
		//ZMIANA ALBUMÓW
	if($_GET['Mod']=='albumy'){
	echo '<form action="" method="GET">';
	echo '<center><select name="albums" id="albums">';
	echo  '<option value="-1">Wybierz Album!</option>';
	$query = 'SELECT * from albumy
	WHERE id_uzytkownika='.$_SESSION['user']['id'].'';
	$result = mysqli_query($conn, $query);
	while($row = mysqli_fetch_assoc($result)){
		echo   '<option value="'.$row['id'].'">'.$row['tytul'].'</option>';
			}
							
	echo '</select></center><br>
	<h2> Nowa nazwa</h2>';
	echo '<tr><td><input class="reginput" placeholder="Nazwa" name="nownazwa"  id="nownazwa"  />';
	echo '<tr><td><input class="przycisk" type="submit" name="wyslij" value="Zmień nazwę" /> </td></tr><br><br>';
	echo '<tr><td><input class="przycisk" type="submit" name="wyslij" value="Usuń album" /> </td></tr></form>';
		}
		//Zmiana zdjecia
		if($_GET['Mod']=='zdjecia'){
			if(isset($_GET['zdjid'])){
			echo "<center><img class='dymek' src='img/".$_SESSION['albumid']."/".$_SESSION['zdjid']."' width='180px' height='180px'></center>";
				echo '<form action="" method="GET">';
		echo'<h2> Nowa nazwa</h2>';
		echo '<tr><td><input type="hidden" name="zdjid" id=""/>';
	echo '<tr><td><input class="reginput" placeholder="Nazwa" name="nownazwazdj"  id="nownazwa"  />';
	echo '<tr><td><input class="przycisk" type="submit" name="wyslij" value="Zmień tytul" /> </td></tr><br><br>';
	echo '<tr><td><input class="przycisk" type="submit" name="wyslij" value="Usuń zdjecie" /> </td></tr></form>';
			}
	else{
				$query = "SELECT * FROM zadjecia WHERE id_uzytkownika=".$_SESSION['user']['id'];
				
				$result = mysqli_query($conn,$query);			
			while($row = mysqli_fetch_assoc($result))
			{
				
				$id_albumu = $row['id_albumu'];
				$id_zdj = $row['id'];
				$tytul = $row['tytul'];
				$data = $row['data'];
				$_SESSION['albumid']=$id_albumu;
				$_SESSION['zdjid']=$id_zdj;
				echo "<a class='dymek' href='konto.php?Mod=zdjecia&zdjid=$id_zdj'><img class='dymek' src='img/$id_albumu/$id_zdj' width='180px' height='180px'><span>Tytuł Foty: $tytul<br>Data utworzenia: $data</span></a>";
			}
			}
		}
	}
		else 
	{
		echo "Login: " . $_SESSION['user']['login'] . "<br/>";
		echo "Hasło: " . $_SESSION['user']['hasło'] . "<br/>";
		echo "Email: " . $_SESSION['user']['email'] . "<br/>";
		}
		//POCZĄTEK WYSYŁANIA
		if(isset($_GET['wyslij'])){
			
		if(isset($_GET['rhaslo'])){
		if (preg_match('/[A-Z]/', $_GET['rhaslo']) && 
		preg_match('/[0-9]/', $_GET['rhaslo']) &&
		preg_match('/[a-z]/', $_GET['rhaslo']) &&
		strlen($_GET['rhaslo'])>=6 && strlen($_GET['rhaslo'])<=20 
		)
{
		$haselo=md5($_GET['rhaslo']);
		$query="UPDATE uzytkownicy
		SET hasło='".$haselo."'
		WHERE id=".$_SESSION['user']['id'];
		mysqli_query($conn,$query);
		echo 'Zmieniono Hasło<br>';
	}else{
		echo "Błędne hasło<br>";
	}
		}
		if(isset($_GET['rmail'])){
		$query="SELECT count(*) as ile from uzytkownicy WHERE email='".$_GET['rmail']."'";
		$result =mysqli_query($conn,$query);
		$row = mysqli_fetch_assoc($result);	
		if($row['ile']==0){
		$query="UPDATE uzytkownicy
		SET email='".$_GET['rmail']."'
		WHERE id=".$_SESSION['user']['id'];
		$resutl =mysqli_query($conn,$query);
		echo "Zmieniono mail<br>";		
		}else{echo 'Jest już taki mail<br>';
		}
		}
		
		if($_GET['wyslij']=="Zmień nazwę"){
		$query="UPDATE albumy SET tytul='".$_GET['nownazwa']."' 
		WHERE id=".$_GET['albums'];
		mysqli_query($conn,$query);
		}
		
		
		if($_GET['wyslij']=="Usuń album"){
			$query="SELECT id from zadjecia WHERE id_albumu=".$_GET['albums'];
			$result = mysqli_query($conn, $query);
			while($row =mysqli_fetch_assoc($result)){
			$query ="DELETE from zadjecia_komentarze WHERE id_zdjecia=".$row['id'];
		mysqli_query($conn,$query);
		$query = "DELETE from zadjecia_oceny WHERE id_zdjecia=".$row['id'];
		mysqli_query($conn,$query);	
			}
		$query ="DELETE from albumy WHERE id=".$_GET['albums'];
		mysqli_query($conn,$query);
		$query = "DELETE from zadjecia WHERE id_albumu=".$_GET['albums'];
		mysqli_query($conn,$query);	
		
		$path = "img/".$_GET['albums'];
		if (strtoupper(substr(PHP_OS, 0, 3)) === 'WIN'){
			exec(sprintf("rd /s /q %s", escapeshellarg($path)));}
		else{
			exec(sprintf("rm -rf %s", escapeshellarg($path)));}
		}
			
		if(isset($_GET['nownazwazdj']) && $_GET['wyslij']=="Zmień tytul"){
			$query="UPDATE zadjecia SET tytul='".$_GET['nownazwazdj']."' WHERE id=".$_SESSION['zdjid'];
			mysqli_query($conn, $query);
		} 
		
		if($_GET['wyslij']=="Usuń zdjecie"){
			$query ="DELETE from zadjecia_komentarze WHERE id_zdjecia=".$_SESSION['zdjid'];
		mysqli_query($conn,$query);
		$query = "DELETE from zadjecia_oceny WHERE id_zdjecia=".$_SESSION['zdjid'];
		mysqli_query($conn,$query);	
			$query ="DELETE from zadjecia WHERE id=".$_SESSION['zdjid'];
			mysqli_query($conn,$query);
			unlink('img/'.$_SESSION['albumid'].'/'.$_SESSION['zdjid'].'');
		}
		}
		//KONIEC WYSYŁANIA
		

		?>
	</div>
	</body>
	</html>