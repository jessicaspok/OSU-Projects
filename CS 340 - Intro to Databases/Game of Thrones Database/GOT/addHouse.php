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
	if(!($stmt = $mysqli->prepare("INSERT INTO `House`(Name, Motto) VALUES (?,?)"))){
		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	if(!($stmt->bind_param("ss",$_POST['Name'],$_POST['Motto']))){
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	if(!$stmt->execute()){
		echo "Execute failed: "  . $stmt->errno . " " . $stmt->error . "<br>" . "Only one House " . $_POST['Name']. " can exist";
	} 
	
	else {
		echo "Added house: " . $_POST['Name'] . ".";
	}
	
	$stmt->close();
?>

<html>
	<body>
		<div>
			<p> Click <a href="showHouse.php">here</a> to see the updated list of houses.</p>
		</div>
	</body>
</html>