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
	if(!($stmt = $mysqli->prepare("INSERT INTO `City`(`Name`, `RegionID`) VALUES (?,?)"))){
		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	if(!($stmt->bind_param("si", $_POST['Name'],$_POST['RegionID']))){
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	if(!$stmt->execute()){
		echo "Execute failed: "  . $stmt->errno . " " . $stmt->error . "<br>" . "Only one City " . $_POST['Name']. " can exist";
	} 
	
	else {
		echo "Added city: " . $_POST['Name'] . ".";
	}
	
	$stmt->close();
?>

<html>
	<body>
		<div>
			<p> Click <a href="showCity.php">here</a> to see the updated list of cities.</p>
		</div>
	</body>
</html>

