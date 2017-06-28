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
		<!--Add Character-->
		<h3>Add Character</h3>
		<div>
			<form method="post" action="addChar.php"> 
				<fieldset>
					<p>First Name: <input type="text" name="F_name" /></p>
					<p>Last Name: <input type="text" name="L_name" /></p>
					<p>Title: <input type="text" name="Title" /></p>
					<p>Status: <input type="number" name="isAlive" min="0" max="1" placeholder="Alive = 1 / Dead = 0" style="width: 150px;" /></p>
					<p>Home City: 
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
					<p>House: 
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
	
		<!--Add City-->
		<h3>Add City</h3>
		<div>
			<form method="post" action="addCity.php"> 
				<fieldset>
					<p>City Name: <input type="text" name="Name" /></p>
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
		
		<!--Add Region-->
		<h3>Add Region</h3>
		<div>
			<form method="post" action="addRegion.php"> 
				<fieldset>
					<p>Region Name: <input type="text" name="Name" /></p>
					<p>Continent Name: <input type="text" name="Continent" /></p>
				</fieldset>
				<p><input type="submit" /></p>
			</form>
		</div>
		
		</br>
		
		<!--Add House-->
		<h3>Add House</h3>
		<div>
			<form method="post" action="addHouse.php"> 
				<fieldset>
					<p>House Name: <input type="text" name="Name" /></p>
					<p>House Motto: <input type="text" name="Motto" /></p>
				</fieldset>
				<p><input type="submit" /></p>
			</form>
		</div>
		
		</br>
		
		<!--Add Connection Type-->
		<h3>Add Connection Type</h3>
		<div>
			<form method="post" action="addConn.php"> 

				<fieldset>
					<p>Connection Type Description: <input type="text" name="Description" /></p>
				</fieldset>
				<p><input type="submit" /></p>
			</form>
		</div>
		
		</br>
		
		<!--Add Ties-->
		<h3>Add Ties</h3>
		<div>
			<form method="post" action="addTies.php"> 
				<fieldset>
					<p>Character 1: 
						<select name="Char1_ID">
						<?php
							if(!($stmt = $mysqli->prepare("SELECT id, F_name FROM Characters"))){
								echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
							}

							if(!$stmt->execute()){
								echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							
							if(!$stmt->bind_result($id, $c1name)){
								echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							
							while($stmt->fetch()){
								echo '<option value=" '. $id . ' "> ' . $c1name . '</option>\n';
							}
							
							$stmt->close();
						?>
						</select></p>
				
					<p>Connection: 
						<select name="CT_ID">
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
				
					<p>Character 2: 
						<select name="Char2_ID">
						<?php
							if(!($stmt = $mysqli->prepare("SELECT id, F_name FROM Characters"))){
								echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
							}

							if(!$stmt->execute()){
								echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							
							if(!$stmt->bind_result($id, $c2name)){
								echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							
							while($stmt->fetch()){
								echo '<option value=" '. $id . ' "> ' . $c2name . '</option>\n';
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