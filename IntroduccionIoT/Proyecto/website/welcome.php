<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="icon" type="image/x-icon" href="img/iconesp32IA.ico">
  <link rel="stylesheet" href="css/styleSignIn.css">
  <title>Data Logs</title>
</head>
<body>
  <header>
    <img src="img/LogoSecurity.png" width="100px" alt="pic1" style="float: right;">
    <img src="img/iconesp32IA.png" width="100px" alt="pic2" style="float: left;">
    <h1 class="titulo">Data log</h1>
    <h2>Welcome></h2>
  </header>
  <main>
    <table border="1" class="tabla"><!-- Class table-->
      <thead>
        <tr>
          <th>Id</th>
          <th>Time</th>
          <th>IP Source</th>
          <th>IP Destine</th>
          <th>Protocol</th>
          <th>Size of Packet</th>
          <th>Info</th>
        </tr>
      </thead>
      <tbody>
        <?php
          // Conect to database
          $db = new mysqli("localhost", "root", "root", "ids");

          // Check database
          $query = "SELECT * FROM traffic";
          $result = $db->query($query);

          // Data loop
          while ($row = $result->fetch_assoc()) {
            echo "<tr>";
            echo "<td>" . $row["id"] . "</td>";
            echo "<td>" . $row["time"] . "</td>";
            echo "<td>" . $row["ipsrc"] . "</td>";
            echo "<td>" . $row["ipdst"] . "</td>";
            echo "<td>" . $row["protocol"] . "</td>";
            echo "<td>" . $row["packlen"] . "</td>";
            echo "<td>" . $row["info"] . "</td>";
            echo "</tr>";
          }
        ?>
      </tbody>
    </table>
    <div class="form_container">
        <a href="index.php"  class="form_submit" onclick="session_destroy();">Sign out</a>
    </div>
  </main>
</body>
</html>
