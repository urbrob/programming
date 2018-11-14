       <nav class="navbar navbar-default">
  <div class="container-fluid">
          <ul class="nav navbar-nav wyjustowanie" >
           <li><a href="galeria.php">Galeria</a></li>
	      <li><a href="dodaj-album.php">Załóż album</a></li>
      <li><a href="dodaj-foto.php">Dodaj zdjęcie</a></li>
      <li><a href="top-foto.php">Najlepiej oceniane</a></li>
	  <li><a href="nowe-foto.php">Najnowsze</a></li>
	  <?php
	  
		if(isset($_SESSION['user']['aktywny'])){
	 echo " <li><a href='konto.php'><span class='glyphicon glyphicon-user' text-align='right'> Moje konto</span></a></li>";
	 echo " <li><a href='wyloguj.php'><span class='glyphicon glyphicon-log-in' text-align='right'> Wyloguj się</span></a></li>";
	 
		if($_SESSION['user']['uprawnienia']=='administrator' || $_SESSION['user']['uprawnienia']=='moderator' ){
	  echo "  <li><a href='admin/index.php'>Panel administracyjny</a></li>";
	   }}	
	  else{
	   echo " <li><a href='index.php'><span class='glyphicon glyphicon-user' text-align='right'></span> Zaloguj Się</a></li>";
	   echo " <li><a href='index.php'><span class='glyphicon glyphicon-log-in' text-align='right'></span> Zarejestruj się</a></li>";
	   
      
	  }
    ?>
          </ul>
       
      </div>
	   </nav>

  
	