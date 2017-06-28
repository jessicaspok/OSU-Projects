<?php
	include 'connectDB.php';
	include 'header.php';
	 
	//Turn on error reporting
	ini_set('display_errors', 'On');
	$mysqli = new mysqli($dbhost, $dbuser, $dbpass, $dbname);

	if($mysqli->connect_errno){
		echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
		
	//DELETE FROM HOUSE TBL
	if(!($stmt = $mysqli->prepare("DELETE FROM `Connection_Type` WHERE id = ?"))){
		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	if(!($stmt->bind_param("i",$_POST['ConnID']))){
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	if(!$stmt->execute()){
		echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	else{
		echo "The connection type has been deleted";
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