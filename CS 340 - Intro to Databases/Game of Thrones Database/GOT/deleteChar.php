<?php
	include 'connectDB.php';
	include 'header.php';
	 
	//Turn on error reporting
	ini_set('display_errors', 'On');
	$mysqli = new mysqli($dbhost, $dbuser, $dbpass, $dbname);

	if($mysqli->connect_errno){
		echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
		
	//DELETE FROM CHARACTERS TBL
	if(!($stmt = $mysqli->prepare("DELETE FROM `Characters` WHERE id = ?"))){
		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	if(!($stmt->bind_param("i",$_POST['CharID']))){
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	if(!$stmt->execute()){
		echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	else{
		echo "The character has been deleted";
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