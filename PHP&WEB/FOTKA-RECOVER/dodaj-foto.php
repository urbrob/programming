<!DOCTYPE html>
<html>
<head>
	<title>Strona testowa</title>
	<meta charset="UTF-8">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
	<link rel="stylesheet" type="text/css" href="css/style.css">
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
<link href="https://fonts.googleapis.com/css?family=Play:400,700" rel="stylesheet">
</head>

<script>

function WyswietlAlbumy(str)
{	$.ajax({
		url: 'zdjeciawys.php',
		data: {q:str},
		success: function(data){
		$("#zdjhint").html(data);
		$("#albumid").val(str);
		}
	})}
	
</script>

<body>

	<?php
	include 'connect.php';

		if(!isset($_SESSION['login'])){
				header ("location: index.php");
				exit;
			}
		include 'menu.php';
	
	?><br>
	<div id="reg">
	<p>Wybierz album<p>
	<form>
	<select name='albums' id="albums" onchange="WyswietlAlbumy(this.value)">
	<br>
	<?php
		echo   '<option value="-1">Wybierz Album!</option>';
		$query = 'SELECT * from albumy
		WHERE id_uzytkownika='.$_SESSION['user']['id'].'';
		$result = mysqli_query($conn, $query);
		while($row = mysqli_fetch_assoc($result)){
			
			echo   '<option value="'.$row['id'].'">'.$row['tytul'].'</option>';
		}	
	
	?>
	
	</select>
	</form>

	<br>
	
	<br>
  
	
		<form method="POST" ENCTYPE="multipart/form-data" >
		<input type="hidden" name="albumid" id="albumid">
		<input type="file" name="plik" required>
		<input type="text" name="komendy" required>
		<input type="submit" onclick="return document.getElementById('albums').value!=-1">
		</form>
		</div>
		<br>
		<div id="zdjhint"></div>

<?php
if(isset($_POST['komendy']) && !empty($_POST["komendy"]) ){
 include_once "class.img.php";

$imageFileType = @pathinfo($target_file,PATHINFO_EXTENSION);
    $check = @getimagesize($_FILES["plik"]["tmp_name"]);
    if($check !== false) {
        $uploadOk = 1;
		  $sql ="INSERT INTO zadjecia(id_albumu,tytul,data,id_uzytkownika,zaakceptowane)
VALUES ('".$_POST['albumid']."','".$_POST['komendy']."', CURRENT_DATE, '".$_SESSION['user']['id']."','0')";
$result =  @mysqli_query($conn, $sql);
 $ostatni =@mysqli_insert_id($conn);
if($result){
$target_dir = "img/".$_POST['albumid']."/";
$target_file = $target_dir .$ostatni;
$img = new Image($_FILES["plik"]["tmp_name"]);
$img -> setmaxsize(1200);
}else{
	echo "<SCRIPT type='text/javascript'>
        alert('Nie udało się dodać do bazy Twojego zdjęcia');
        window.location.replace(\" dodaj-foto.php\");
    </SCRIPT>";
}
    } else {
        
		echo "<SCRIPT type='text/javascript'>
        alert('Plik nie jest zdjęciem');
    </SCRIPT>";
	$uploadOk = 0;
    }
if ($uploadOk == 0) {
	echo "<SCRIPT type='text/javascript'>
        alert('Nie udało się wstawić');
        window.location.replace(\" dodaj-foto.php\");
    </SCRIPT>";
} 
	
if($uploadOk == 1){
    if ($img->Save($target_file)) {
     echo "<SCRIPT type='text/javascript'>
        alert('Dodano');
        window.location.replace(\" dodaj-foto.php\");
    </SCRIPT>";
		
    } else{
		echo "<SCRIPT type='text/javascript'>
        alert('Dodano');
        window.location.replace(\" dodaj-foto.php\");
    </SCRIPT>";
    }


}




}
?>

</body>
</html>