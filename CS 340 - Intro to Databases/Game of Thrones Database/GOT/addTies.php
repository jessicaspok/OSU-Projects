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
	if(!($stmt = $mysqli->prepare("INSERT INTO `Ties`(`Char1_ID`, `Char2_ID`, `CT_ID`) VALUES (?,?,?)"))){
		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	if(!($stmt->bind_param("iii",$_POST['Char1_ID'],$_POST['Char2_ID'],$_POST['CT_ID']))){
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	if(!$stmt->execute()){
		echo "Execute failed: "  . $stmt->errno . " " . $stmt->error . "<br>" . "There already exists a tie can exist for these characters.";
	} 
	
	else {
		echo "Added tie successfully.";
	}
	
	$stmt->close();
?>

<html>
	<body>
		<div>
			<p> Click <a href="showTies.php">here</a> to see the updated list of ties.</p>
		</div>
	</body>
</html>


