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
		<!--Search by Character-->
		<h3>Search for a Character by Name</h3>
		<div>
			<form method="post" action="searchChar.php"> 
				<fieldset>
					<p>First Name: 
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
				<p><input type="submit" /></p>
			</form>
		</div>
	
		</br>
	
		<!--Search by City-->
		<h3>Search for Characters by City</h3>
		<div>
			<form method="post" action="searchCity.php"> 
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
				<p><input type="submit" /></p>
			</form>
		</div>
		
		</br>
		
		<!--Search by Region-->
		<h3>Search for Characters by Region</h3>
		<div>
			<form method="post" action="searchRegion.php"> 
				<fieldset>
					<p>Region Name: 
						<select name="RegionID">
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
				<p><input type="submit" /></p>
			</form>
		</div>
		
		</br>
			
		<!--Search by House-->
		<h3>Search for Characters by House</h3>
		<div>
			<form method="post" action="searchHouse.php"> 
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
				<p><input type="submit" /></p>
			</form>
		</div>
		
		</br>
		
		<!--Search Connections -->
		<h3>Search for Ties by Connection Type</h3>
		<div>
			<form method="post" action="searchConn.php"> 
				<fieldset>
					<p>Connection Type: 
						<select name="ConnID">
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
				<p><input type="submit" /></p>
			</form>
		</div>
		
		</br>
		
		<!--Search Ties -->
		<h3>Search for Ties by Character</h3>
		<div>
			<form method="post" action="searchTies.php"> 
				<fieldset>
					<p>First Name: 
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
				<p><input type="submit" /></p>
			</form>
		</div>
	</body>
</html>