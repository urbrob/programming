

<?php

$q = intval($_GET['q']);
include 'connect.php';
$sql="SELECT * FROM zadjecia WHERE id_albumu = '".$q."'";
$result = mysqli_query($conn,$sql);
while($row = mysqli_fetch_array($result)) {
	if (file_exists('img/'.$q.'/'.$row['id'])) {
  echo "<a class='dymek' href='album.php?id_albumu=".$q."'><img class='dymek' src='img/".$q."/".$row['id']."' width='180' height='180'>";
	} }

mysqli_close($conn);
?>
