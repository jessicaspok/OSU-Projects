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
			<h2>Game of Thrones Ties</h2>
			<table>
				<tr>
					<th>FIRST NAME</th>
					<th>LAST NAME</th>
					<th>CONNECTION</th>
					<th>FIRST NAME</th>
					<th>LAST NAME</th>
				</tr>
				<?php
				if(!($stmt = $mysqli->prepare("SELECT DISTINCT c1.F_name, c1.L_name, Connection_Type.Description, c2.F_name, c2.L_name FROM Ties INNER JOIN Characters AS c1 ON Ties.Char1_ID = c1.id INNER JOIN Characters AS c2 ON Ties.Char2_ID = c2.id INNER JOIN Connection_Type ON CT_ID = Connection_Type.id ORDER BY c1.F_name"))){
					echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}

				if(!$stmt->execute()){
					echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				
				if(!$stmt->bind_result($c1F_name, $c1L_name, $Desc, $c2F_name, $c2L_name)){
					echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				
				while($stmt->fetch()){
					echo "<tr>\n<td>\n" . $c1F_name . "\n</td>\n<td>\n" . $c1L_name . "\n</td>\n<td>\n" . " is the " . $Desc . " of " . "\n</td>\n<td>\n" . $c2F_name . "\n</td>\n<td>\n" . $c2L_name . "\n</td>\n</tr>" ;
				}
				
				$stmt->close();
				?>
			</table>
		</div>
	</body>
</html>