<?php
	include 'connectDB.php';
	include 'header.php';

	//Turn on error reporting
	ini_set('display_errors', 'On');
	$mysqli = new mysqli($dbhost, $dbuser, $dbpass, $dbname);

	if($mysqli->connect_errno){
		echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
?>

<html>	
	<body>
		<!--Delete a Character-->
		<h3>Delete a Character</h3>
		<div>
			<form method="post" action="deleteChar.php"> 
				<fieldset>
					<p>Character Name: 
						<select name="CharID">
						<?php
							if(!($stmt = $mysqli->prepare("SELECT id, F_name FROM Characters"))){
								echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
							}

							if(!$stmt->execute()){
								echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							
							if(!$stmt->bind_result($id, $fname)){
								echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							
							while($stmt->fetch()){
								echo '<option value=" '. $id . ' "> ' . $fname . '</option>\n';
							}
							
							$stmt->close();
						?>
						</select></p>
				</fieldset>
				<p><input type="submit" /> note: deleting this character will also delete any ties the character is a part of</p>
			</form>
		</div>
		
		</br>
			
		<!--Delete a City-->
		<h3>Delete a City</h3>
		<div>
			<form method="post" action="deleteCity.php"> 
				<fieldset>
					<p>City Name: 
						<select name="CityID">
						<?php
							if(!($stmt = $mysqli->prepare("SELECT id, Name FROM City"))){
								echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
							}

							if(!$stmt->execute()){
								echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							
							if(!$stmt->bind_result($id, $cname)){
								echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							
							while($stmt->fetch()){
								echo '<option value=" '. $id . ' "> ' . $cname . '</option>\n';
							}
							
							$stmt->close();
						?>
						</select></p>
				</fieldset>
				<p><input type="submit" /> note: deleting this city will also delete any characters who come from this city</p>
			</form>
		</div>
		
		</br>
	
		<!--Delete a Region-->
		<h3>Delete a Region</h3>
		<div>
			<form method="post" action="deleteRegion.php"> 
				<fieldset>
					<p>Region Name: <select name="RegionID">
						<?php
							if(!($stmt = $mysqli->prepare("SELECT id, Name FROM Region"))){
								echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
							}

							if(!$stmt->execute()){
								echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							
							if(!$stmt->bind_result($id, $rname)){
								echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							
							while($stmt->fetch()){
								echo '<option value=" '. $id . ' "> ' . $rname . '</option>\n';
							}
							
							$stmt->close();
						?>
						</select></p>
				</fieldset>
				<p><input type="submit" /> note: deleting this region will also delete any cities located in this region</p>
			</form>
		</div>
		
		</br>
			
		<!--Delete a House-->
		<h3>Delete a House</h3>
		<div>
			<form method="post" action="deleteHouse.php"> 
				<fieldset>
					<p>House Name: 
						<select name="HouseID">
						<?php
							if(!($stmt = $mysqli->prepare("SELECT id, Name FROM House"))){
								echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
							}

							if(!$stmt->execute()){
								echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							
							if(!$stmt->bind_result($id, $hname)){
								echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							
							while($stmt->fetch()){
								echo '<option value=" '. $id . ' "> ' . $hname . '</option>\n';
							}
							
							$stmt->close();
						?>
						</select></p>
				</fieldset>
				<p><input type="submit" /> note: deleting this house will also delete any characters who belong to this house</p>
			</form>
		</div>
		
		</br>
			
		<!--Delete a Connection Type-->
		<h3>Delete a Connection Type</h3>
		<div>
			<form method="post" action="deleteConn.php"> 
				<fieldset>
					<p>Connection Type: <select name="ConnID">
						<?php
							if(!($stmt = $mysqli->prepare("SELECT id, Description FROM Connection_Type"))){
								echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
							}

							if(!$stmt->execute()){
								echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							
							if(!$stmt->bind_result($id, $desc)){
								echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							
							while($stmt->fetch()){
								echo '<option value=" '. $id . ' "> ' . $desc . '</option>\n';
							}
							
							$stmt->close();
						?>
						</select></p>
				</fieldset>
				<p><input type="submit" /> note: deleting this connection type will also delete any ties associated with this type</p>
			</form>
		</div>
	</body>
</html>