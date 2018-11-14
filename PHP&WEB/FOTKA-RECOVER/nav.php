<nav>
	<?php
		echo "<a href='galeria.php'>Galeria</a>";
		echo "<a href='top-foto.php'>Najlepiej oceniane</a>";
		echo "<a href='nowe-foto.php'>Najnowsze</a>";

		//niezalogowany
		if(!isset($_SESSION["user"]))
		{
			echo "<a href='index.php'>Załóż album</a>";
			echo "<a href='index.php'>Dodaj zdjęcie</a>";
			echo "<a href='index.php'>Zaloguj się</a>";
			echo "<a href='index.php'>Rejestracja</a>";
		}
		//zalogowany
		else
		{
			echo "<a href='dodaj-album.php'>Załóż album</a>";
			echo "<a href='dodaj-foto.php'>Dodaj zdjęcie</a>";
			echo "<a href='konto.php'>Moje konto</a>";
			echo "<a href='index.php?logout'>Wyloguj się</a>";
		}

		if(($_SESSION["user"]["uprawnienia"]=='moderator')OR($_SESSION["userData"]["uprawnienia"]=='administrator'))
		{	echo "<a href='admin/index.php'>Panel administracyjny</a>";	}
	?>
</nav>