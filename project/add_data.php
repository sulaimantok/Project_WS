
<?php include "function.php";
date_default_timezone_set('Asia/Jakarta');

$asap = $_GET['variabel'];
$api = $_GET['nilai'];
echo $asap,$api;

  
  $q = "INSERT INTO arduino_data (variabel, nilai) VALUES ('$asap', '$api');";
 // $hapus = "DELETE from api ORDER BY id asc LIMIT 3"
  $ck= mysqli_query($conn,$q);

 
