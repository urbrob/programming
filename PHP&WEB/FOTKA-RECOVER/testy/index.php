<?php
if((isset($_POST['width']) || isset($_POST['height'])) && (intval($_POST['width']) > 0 || intval($_POST['height']) > 0))
{	// dołączenie klasy ze skalowaniem gragiki
	include_once "class.img.php";
	
	// nowy obiekt klasy Image
	$img = new Image('img/1.jpg');

	if(intval($_POST['width']) > 0 && intval($_POST['height']) > 0)
	{	//skalowanie do podanej wysokości i szerokości
		$img->SetSize($_POST['width'], $_POST['height']);
		$file_name = 'w_'.$_POST['width'].'_h_'.$_POST['height'].'.jpg';
	}
	elseif(intval($_POST['width']) > 0)
	{	//skalowanie do podanej szerokości
		$img->SetWidth($_POST['width']);
		$file_name = 'w_'.$_POST['width'].'.jpg';
	}
	elseif(intval($_POST['height']) > 0)
	{	//skalowanie do podanej wysokości
		$img->SetHeight($_POST['height']);
		$file_name = 'h_'.$_POST['height'].'.jpg';
	}
	
	// zapisanie zdjęcia do katalogu
	$img->Save('img/'.$file_name);
}
?>

<!DOCTYPE HTML>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<title>Biblioteka GD</title>
	<style type="text/css">
	body	{
		margin:0;
		font-family:Verdana, Geneva, sans-serif;
		font-size:12px;
	}
	input[type=text]	{
		border:1px solid #000;
		width:100px;
		text-align:right;
		padding-right:5px;
	}
	input[type=submit]	{
		border:1px outset #700;
		background-color:#900;
		color:#fff;
	}
	p	{ text-align : center;}
	</style>
</head>
<body>
<form method="post" action="index.php">
<table width="300" border="0" cellspacing="0" cellpadding="10" align="center">
<tr><td>Nowa szerokość:</td>
	<td><input type="text" name="width"> px</td></tr>
<tr><td>Nowa wysokość:</td>
	<td><input type="text" name="height"> px</td></tr>
<tr><td>&nbsp;</td>
	<td><input type="submit" name="zapisz" value="Zmień i zapisz"></td></tr>
</table>
<p>Jeżeli podasz tylko szerokość lub wysokość, to drugi wymiar zostanie przeskalowany proporcjonalnie.</p>
<p>Jeżeli podasz oba wymiary, to obraz będzie miał dokłądnie podane wymiary.</p>
</form>

<br clear="all">
<?php
// wyświetlenie wszystkich zdjęć poza oryginałem z katalogu IMG
$d = dir("img");
while (false !== ($entry = $d->read()))
{	if($entry != '.' && $entry != '..' && $entry != '1.jpg')
	echo '<img src="img/'.$entry.'" style="display:block;clear:all;margin:10px;">';
}
$d->close();
?>
</body>
</html>
