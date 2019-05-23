<?php
include 'connect.php';

$pytanie = "SELECT * FROM uzytkownicy WHERE 
login = '".$_POST['login']."' and hasło=md5('".$_POST['haslo']."')" ;
echo $pytanie;

$result = mysqli_query($conn,$pytanie);
if (mysqli_num_rows($result) >= 1) {

$logon=true;
}else{
$_SESSION['loginbaza'] .= 'Źle wpisane dane';
$logon=false;
}

if (isset($logon)){
if($logon){	
$_SESSION['login']= $_POST['login'];
$_SESSION['user'] = mysqli_fetch_assoc($result);
$_SESSION['loginbaza'] .= '';
header('location: galeria.php');
exit();
}else if(!$logon){
	header('location: index.php');
	exit();
}
}
//Sprawdź czy już jest taki rekord
//$_SESSION['loginbaza'] .= 'Jest taki login';
?>