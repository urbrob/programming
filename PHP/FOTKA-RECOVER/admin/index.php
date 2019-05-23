<html>
	<head>
	<link rel="stylesheet" type="text/css" href="../css/style.css">
 <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
<link href="https://fonts.googleapis.com/css?family=Play:400,700" rel="stylesheet">
		<title>Hello World</title>
		<meta charset = "utf-8">
		
	</head>
	<body>
	

	  <?php
	include '..\connect.php';
    ?>
	
<div id="container">
<header>Panel Admina</header>
<div id="galeria">
 <nav class="navbar navbar-default">
  <div class="container-fluid">
          <ul class="nav navbar-nav wyjustowanie">
           
	       <li><a href="index.php?Mod=zdjecia">Zdjecia</a></li>
		   <li><a href="index.php?Mod=komentarze">Komentarze</a></li>
		<?php if($_SESSION['user']['uprawnienia']=='administrator') {
			echo '<li><a href="index.php?Mod=albumy">Albumy</a></li>';
			echo '<li><a href="index.php?Mod=uzytkownicy">Użytkownicy</a></li>';
			
		}			
		?>
		   <li><a href="..\galeria.php">Powrót</a></li>
          </ul>   
      </div>
	  </nav>
	  <?php 
	
	  if(isset($_GET['Mod'])){
		  //ZMIANA ALBUMÓW
	if($_GET['Mod']=='albumy'){
	echo '<form action="" method="GET">';
	echo '<center><select name="albums" id="albums">';
	echo  '<option value="-1">Wybierz Album!</option>';
	$query = 'SELECT * from albumy';
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
		//Zdjęcia Edycja
			if($_GET['Mod']=='zdjecia'){
			if(isset($_GET['zdjid'])){
			echo "<center><img class='dymek' src='../img/".$_SESSION['albumid']."/".$_SESSION['zdjid']."' width='180px' height='180px'></center>";
				echo '<form action="" method="GET">';
		echo'<h2> Nowa nazwa</h2>';
		echo '<tr><td><input type="hidden" name="zdjid" id=""/>';
	echo '<tr><td><input class="reginput" placeholder="Nazwa" name="nownazwazdj"  id="nownazwa"  />';
	echo '<tr><td><input class="przycisk" type="submit" name="wyslij" value="Zmień tytul" /> </td></tr><br><br>';
	echo '<tr><td><input class="przycisk" type="submit" name="wyslij" value="Usuń zdjecie" /> </td></tr></form>';
			}
	else{
				$query = "SELECT * FROM zadjecia";
				$result = mysqli_query($conn,$query);			
			while($row = mysqli_fetch_assoc($result))
			{
				$id_albumu = $row['id_albumu'];
				$id_zdj = $row['id'];
				$tytul = $row['tytul'];
				$data = $row['data'];
				$_SESSION['albumid']=$id_albumu;
				$_SESSION['zdjid']=$id_zdj;
				echo "<a class='dymek' href='index.php?Mod=zdjecia&zdjid=$id_zdj'><img class='dymek' src='../img/$id_albumu/$id_zdj' width='180px' height='180px'><span>Tytuł Foty: $tytul<br>Data utworzenia: $data</span></a>";
			}
			}
		}
		
		//Użytkownicy 
		
	  if($_GET['Mod']=='uzytkownicy'){	
	  if(isset($_GET['login'])){
		    echo '<form action="" method="GET">';
		
			echo '<input type="hidden" name="loginid" value="'.$_GET['login'].'"/>';
			echo '<center><select name="uprawnienia" id="uprawnienia">';
			echo  '<option value="administrator">Administrator</option>';
			echo  '<option value="moderator">Moderator</option>';
			echo  '<option value="uzytkownik">Uzytkownik</option>';
	  echo '</select></center><br>';
	  	echo '<center><select name="aktywny" id="aktywny">';
			echo  '<option value="1">Aktywny</option>';
			echo  '<option value="0">Zablokowany</option>';
	  echo '</select></center><br>';
	  echo '<tr><td><input class="przycisk" name="wyslij" type="submit" value="Edytuj login" /> </td></tr>
			<tr><td><input class="przycisk" name="wyslij" type="submit" value="Usun login" /> </td></tr>
	  </form>';
	 
	  }else{
	  echo '<form action="" method="GET">';
	  echo '<input type="hidden" name="Mod" value="uzytkownicy" />';
	echo '<center><select name="login" id="login">';
	echo  '<option value="-1">Wybierz Login!</option>';
	$query = 'SELECT * from uzytkownicy';
	$result = mysqli_query($conn, $query);
	while($row = mysqli_fetch_assoc($result)){
		echo   '<option value="'.$row['id'].'">'.$row['login'].'</option>';
			}
							
	  echo '</select></center><br>';
	  echo '<tr><td><input class="przycisk" type="submit" value="Edytuj" /> </td></tr></form>';
	  }
	
	echo '<table class="table table-bordered">';
	echo '<tr><th></th><th><a href=index.php?Mod=uzytkownicy&grupa=administrator>Admini</a></th><th><a href=index.php?Mod=uzytkownicy&grupa=moderator>Moderatorzy</a></th><th><a href=index.php?Mod=uzytkownicy&grupa=uzytkownik>Użytkownicy</a></th><th><a href=index.php?Mod=uzytkownicy&grupa=wszyscy>Wszyscy </a></th></tr>';
	echo '<tr><th>Login</th><th>Ranga</th><th>Data utworzenia</th><th>E-mail</th><th>Aktywny</th></tr>';
	if(isset($_GET['grupa'])){
	if($_GET['grupa']=='administrator'){
	$query="SELECT * from uzytkownicy WHERE uprawnienia='".$_GET['grupa']."'";
	$result = mysqli_query($conn,$query);
	while($row = mysqli_fetch_assoc($result)){
	echo "<tr><th>".$row['login']."</th><th>".$row['uprawnienia']."</th><th>".$row['zarejestrowany']."</th><th>".$row['email']."</th><th>".$row['aktywny']."</th></tr>";
	}
	}
	if($_GET['grupa']=='moderator'){
	$query="SELECT * from uzytkownicy WHERE uprawnienia='".$_GET['grupa']."'";
	$result = mysqli_query($conn,$query);
	while($row = mysqli_fetch_assoc($result)){
	echo "<tr><th>".$row['login']."</th><th>".$row['uprawnienia']."</th><th>".$row['zarejestrowany']."</th><th>".$row['email']."</th><th>".$row['aktywny']."</th></tr>";
	}
	}
	if($_GET['grupa']=='uzytkownik'){
	$query="SELECT * from uzytkownicy WHERE uprawnienia='".$_GET['grupa']."'";
	$result = mysqli_query($conn,$query);
	while($row = mysqli_fetch_assoc($result)){
	echo "<tr><th>".$row['login']."</th><th>".$row['uprawnienia']."</th><th>".$row['zarejestrowany']."</th><th>".$row['email']."</th><th>".$row['aktywny']."</th></tr>";
	}
	}
	if($_GET['grupa']=='wszyscy'){
	$query="SELECT * from uzytkownicy";
	$result = mysqli_query($conn,$query);
	while($row = mysqli_fetch_assoc($result)){
	echo "<tr><th>".$row['login']."</th><th>".$row['uprawnienia']."</th><th>".$row['zarejestrowany']."</th><th>".$row['email']."</th><th>".$row['aktywny']."</th></tr>";
	}
	}
	echo '</table>';
		 }  
	  }	 
	  
		//Komentatrze Inwigilacja
	  if($_GET['Mod']=='komentarze'){	
	  echo '<form method="GET" style="text-align:center;" action="index.php?Mod=komentarze">';
			echo '	<textarea rows="3" cols="50" name="komentedit"></textarea>';
				echo '<tr><td><input type="hidden" name="Mod" value="komentarze"/>';
			echo '<center><select name="idkoment" id="idkoment">';
			echo  '<option value="-1">Wybierz komentarz!</option>';
			$query = 'SELECT * from zadjecia_komentarze';
			$result = mysqli_query($conn, $query);
			while($row = mysqli_fetch_assoc($result)){
				echo   '<option value="'.$row['ID'].'">'.$row['komentarz'].'</option>';
					}
				echo '</select></center><br>	';
echo '	<input type="submit" name="wyslij" value="Edytuj Komentarz"></form>';

	
	
	
	
	
	echo '<table class="table table-bordered">';
	echo '<tr><th></th><th><a href=index.php?Mod=komentarze&komenty=oczekujące>Oczekujące</a></th><th><a href=index.php?Mod=komentarze&komenty=zaakceptowane>Zaakceptowane</a></th><th></th><th></th></tr>';
	echo '<tr><th>ID</th><th>Użytkownik</th><th>Komentarze</th><th></th><th></th></tr>';
	if(isset($_GET['komenty'])){
	if($_GET['komenty']=='zaakceptowane'){
	$query="SELECT k.komentarz as koment, k.zaakceptowany, k.id as id, u.login as login from zadjecia_komentarze as k JOIN uzytkownicy as u ON k.id_uzytkownika=u.id WHERE k.zaakceptowany=1" ;
	$result = mysqli_query($conn,$query);
	while($row = mysqli_fetch_assoc($result)){
	echo "<tr><th>".$row['id']."</th><th>".$row['login']."</th><th>".$row['koment']."</th><th><a href='index.php?Mod=komentarze&komenty=zaakceptowane&idks=".$row['id']."&co=usun'>Usuń</a></th><th></th></tr>";
	}
	}
	if($_GET['komenty']=='oczekujące'){
	$query="SELECT k.komentarz as koment, k.zaakceptowany, k.id as id, u.login as login from zadjecia_komentarze as k JOIN uzytkownicy as u ON k.id_uzytkownika=u.id WHERE k.zaakceptowany=0" ;
	$result = mysqli_query($conn,$query);
	while($row = mysqli_fetch_assoc($result)){
	echo "<tr><th>".$row['id']."</th><th>".$row['login']."</th><th>".$row['koment']."</th><th><a href='index.php?Mod=komentarze&komenty=oczekujące&idks=".$row['id']."&co=usun'>Usuń</a></th><th><a href='index.php?Mod=komentarze&komenty=oczekujące&idks=".$row['id']."&co=akcp'>Zaakceptuj</a></th></tr>";
	}
	}
	echo '</table>';
		 }  
	  }	
	  }	  
	 
	  //POCZĄTEK WYSYŁANIA
		if(isset($_GET['wyslij'])){
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
		
		$path = "../img/".$_GET['albums'];
		if (strtoupper(substr(PHP_OS, 0, 3)) === 'WIN'){
			exec(sprintf("rd /s /q %s", escapeshellarg($path)));}
		else{
			exec(sprintf("rm -rf %s", escapeshellarg($path)));}
		}
			if($_GET['wyslij']=="Zmień nazwę"){
				
		$query="UPDATE albumy SET tytul='".$_GET['nownazwa']."' 
		WHERE id=".$_GET['albums'];
		
		mysqli_query($conn,$query);
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
			unlink('../img/'.$_SESSION['albumid'].'/'.$_SESSION['zdjid'].'');
		}
			
	if($_GET['wyslij']=="Edytuj Komentarz"){
		$query="UPDATE zadjecia_komentarze SET komentarz='".$_GET['komentedit']."' WHERE ID=".$_GET['idkoment'];
		
		mysqli_query($conn, $query);
		
	}
	if($_GET['wyslij']=="Edytuj login"){
		$query="UPDATE uzytkownicy SET aktywny=".$_GET['aktywny']." WHERE id=".$_GET['loginid'];
		mysqli_query($conn, $query);
		$query="UPDATE uzytkownicy SET uprawnienia='".$_GET['uprawnienia']."' WHERE id=".$_GET['loginid'];
		mysqli_query($conn, $query);
		
	}
	if($_GET['wyslij']=="Usun login"){
		$query="DELETE from zadjecia WHERE id_uzytkownika=".$_GET['loginid'];
		mysqli_query($conn,$query);
		$query="DELETE from albumy WHERE id_uzytkownika=".$_GET['loginid'];
		mysqli_query($conn,$query);
		$query="SELECT * FROM albumy WHERE id_uzytkownika=".$_GET['loginid'];
		echo $query;
		$resutl =mysqli_query($conn, $query);
		while($row = mysqli_fetch_assoc($resutl)){
		$path = "img/".$row['id'];
		if (strtoupper(substr(PHP_OS, 0, 3)) === 'WIN'){
			exec(sprintf("rd /s /q %s", escapeshellarg($path)));}
		else{
			exec(sprintf("rm -rf %s", escapeshellarg($path)));}
		}
		$query="DELETE from uzytkownicy WHERE id=".$_GET['loginid'];
		mysqli_query($conn,$query);
	}
		}
		if(isset($_GET['co'])){
			if($_GET['co']=="usun"){
			$query="DELETE from zadjecia_komentarze WHERE id=".$_GET['idks'];
			mysqli_query($conn, $query);
		}
		if($_GET['co']=="akcp"){
			$query="UPDATE zadjecia_komentarze SET zaakceptowany=1 WHERE id=".$_GET['idks'];
			echo $query;
			mysqli_query($conn, $query);
		}
		}
	  ?>
	  
	 </div>
	</body>
	</html>