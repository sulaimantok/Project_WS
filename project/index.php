<?php
  include("function.php");
   
  $conn = databaseConnect();
 
  if(isset($_GET['message']))
  {
    echo $_GET['message'];
    echo "<br>";
    echo "<br>";
  }
  $sql = "SELECT * FROM arduino_data";
  $result = $conn->query($sql);
 
  echo "<html>";
  echo "<head>";
  echo "<meta http-equiv='refresh' content='10'>";
  echo "<title>Smart Water</title>";
  echo "<link  href='cantik.css' rel='stylesheet'>";
  echo "<link  href='icon2.ico' rel='shortcut icon'>";
  echo "</head>";
  echo "<body>";
  echo "</br>";
  echo "</br>";
  echo "<h1><span>DISWAV Data</span></h1>";
  echo "</br>";
  echo "<table border='1' align='center' >";
  echo "<tr>";
  echo "<td width='50' class='pilih' >No</td><td width='100' class='pilih'>Debit</td><td width='200' class='pilih'>Volume</td>";
  echo "</tr>";
  if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
      echo "<tr>";
      echo "<td>".$row["id"]."</td><td>".$row["variabel"]."</td><td>".$row["nilai"]. "</td>";
      echo "</tr>";
    }
  } else {
    echo "<td colspan='3'>";
    echo("tidak ada data");
    echo "</td>";
  }
  echo "</table>";
   
  echo "<form align='center' action='dariBrowser.php' method=GET>";
  echo "<input type='hidden' name='aksi' value='hapus'><br>";
  echo "<input type='submit' value='Hapus semua data'>";
  echo "</form>";
 
  echo "<br><h1><span> Kirim data ke Server</span></h1><br>";
  echo "<form align='center' action='dariBrowser.php' method=GET>";
  echo "<p align='center'>Nama variabel:</p><input type='number' min='1' max='5' name='variabel'><br>";
  echo "<p align='center'>Nilai:<br><input type='number' min='0' max='1' name='nilai'><br><br>";
  echo "<input type='submit' value='Kirim'>";
  echo "</form>";
  echo "</body>";
  echo "</html>";
 
  $conn->close();
?> 