<?php
 include 'connectDB.php';
 include 'header.php';
 
//Turn on error reporting
ini_set('display_errors', 'On');
$mysqli = new mysqli($dbhost, $dbuser, $dbpass, $dbname);

if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
	
//INSERT VALUE INTO TABLE	
if(!($stmt = $mysqli->prepare("INSERT INTO `Connection_Type`(`Description`) VALUES (?)"
))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("s",$_POST['Description']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error . "<br>" . "Only one Connection Type " . $_POST['Description']. " can exist";
} else {
	echo "Added connection type: " . $_POST['Description'] . ".";
}
$stmt->close();
?>

<html>
	<body>
		<div>
			<p> Click <a href="showConn.php">here</a> to see the updated list of connection types.</p>
		</div>
	</body>
</html>