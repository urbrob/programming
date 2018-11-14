<?php
function sended($wyslanie){
	if(isset($wyslanie)){
if(!$wyslanie){
header('location: index.php');	
exit();
}else if($wyslanie){
	header('location: rejestracja-ok.php');
	exit();
}
}

}
include 'connect.php';
if(!preg_match('/^[A-Za-z0-9]{6,20}$/', $_POST['rlogin'])){
$_SESSION['error'] .= 'Niepoprawny login<br>';
$blady++;	
$loginek=false;
}else {
	$_SESSION['error'] .= 'Poprawny login<br>';
	$loginek=true;
}
if(!filter_var($_POST['rmail'], FILTER_VALIDATE_EMAIL)){
	$_SESSION['error'] .= 'Niepoprawny mail<br>';
	$blady++;
}
if (preg_match('/[A-Z]/', $_POST['rhaslo']) && 
		preg_match('/[0-9]/', $_POST['rhaslo']) &&
		preg_match('/[a-z]/', $_POST['rhaslo']) &&
		strlen($_POST['rhaslo'])>=6 && strlen($_POST['rhaslo'])<=20 
		)
{$_SESSION['error'] .= 'Poprawne hasło<br>';
}else{
    $_SESSION['error'] .= 'Niewystarczająco bezpieczne hasło<br>';
	$blady++;
}
if($_POST['rhaslo']!=$_POST['prhaslo']){
	$_SESSION['error'] .= 'Niepoprawnie przepisane hasło<br>';
	$blady++;
}
$query = "SELECT * FROM uzytkownicy WHERE 
login = '". mysqli_real_escape_string($conn, $_POST['rlogin']) ."'" ;
$result = mysqli_query($conn,$query);
if (mysqli_num_rows($result) >= 1) {
$_SESSION['error'] .= 'Jest już taki login w bazie';
$blady++;
} else if($loginek){
$_SESSION['error'] .= 'Login jest dostępny';
}


if($blady==0){
	$czas = date('Y-m-d');
	$haselo= md5($_POST['rhaslo']);
	$sql = "INSERT INTO uzytkownicy(login,hasło,email,zarejestrowany,uprawnienia,aktywny)
VALUES ('".$_POST['rlogin']."','".$haselo."', '".$_POST['rmail']."', '".$czas."', 'uzytkownik', '1')";

}else{
	sended(false);
}
if($sql){
	if (mysqli_query($conn, $sql)) {
		$_SESSION['error'] .= "Nowe konto zostało dodane<br>
		";
		sended(true);
		
	} else {
		$_SESSION['error'] .= "Błąd: " . $sql . "<br>" . mysqli_error($conn);
	}
}


?>