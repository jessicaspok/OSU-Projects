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
	<head>
		<style>
			table {
				border: 2px solid black;
				border-collapse: collapse;
			}
			
			th, td {
				border: 1px solid black;
				padding: 15px;
				height: 30px;
				width: 200px;
			}
			
			tr:nth-child(even) {
				background-color: lightgrey;
			}
		</style>
	</head>
	<body>
		<div>
			<h2>Game of Thrones Characters by Region</h2>
			<table>
				<tr>
					<th>TITLE</th>
					<th>FIRST NAME</th>
					<th>LAST NAME</th>
					<th>STATUS (Alive: 1)</th>
					<th>HOME CITY</th>
					<th>REGION</th>
					<th>CONTINENT</th>
					<th>HOUSE</th>
				</tr>
				<?php
					if(!($stmt = $mysqli->prepare("SELECT F_name, L_name, Title, isAlive, City.Name, Region.Name, Region.Continent, House.Name FROM Characters 
						INNER JOIN City ON CityID = City.id INNER JOIN Region ON City.RegionID = Region.id LEFT JOIN House ON HouseID = House.id WHERE Region.id = ? ORDER BY F_name"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}
					
					if(!($stmt->bind_param("i", $_POST['RegionID']))){
						echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
					}
					
					if(!$stmt->execute()){
						echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
					}

					if(!$stmt->bind_result($F_name, $L_name, $Title, $isAlive, $City, $Region, $Continent, $House)){
						echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					} 

					while($stmt->fetch()){
						echo "<tr>\n<td>\n" . $Title . "\n</td>\n<td>\n" . $F_name . "\n</td>\n<td>\n" . $L_name . "\n</td>\n<td>\n" . $isAlive . "\n</td>\n<td>\n" . $City . "\n</td>\n<td>\n"  . $Region . "\n</td>\n<td>\n"  . $Continent . "\n</td>\n<td>\n"  . $House . "\n</td>\n</tr>" ;
					}
					
					$stmt->close();
				?>
			</table>
		</div>
	</body>
</html>