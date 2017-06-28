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
	if(!($stmt = $mysqli->prepare("INSERT INTO `Characters`(`F_name`, `L_name`, `Title`, `isAlive`, `CityID`, `HouseID`) VALUES (?,?,?,?,?,?)"))){
		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	if(!($stmt->bind_param("sssiii", $_POST['F_name'],$_POST['L_name'],$_POST['Title'],$_POST['isAlive'],$_POST['CityID'],$_POST['HouseID']))){
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	if(!$stmt->execute()){
		echo "Execute failed: "  . $stmt->errno . " " . $stmt->error . "<br>" . "Only one Character " . $_POST['F_name']. " can exist";
	} 
	
	else {
		echo "Added character: " . $_POST['F_name'] . " " . $_POST['L_name'] . ".";
	}
	
	$stmt->close();
?>

<html>
	<body>
		<div>
			<p> Click <a href="showChar.php">here</a> to see the updated list of characters.</p>
		</div>
	</body>
</html>
