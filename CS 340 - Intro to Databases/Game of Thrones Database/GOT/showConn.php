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
			<h2>Connection Types</h2>
			<table>
				<tr>
					<th>DESCRIPTION</th>
				</tr>
				<?php
				if(!($stmt = $mysqli->prepare("SELECT Description FROM Connection_Type ORDER BY Description"))){
					echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}

				if(!$stmt->execute()){
					echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				
				if(!$stmt->bind_result($Desc)){
					echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				
				while($stmt->fetch()){
					echo "<tr>\n<td>\n" . $Desc . "\n</td>\n</tr>" ;
				}
				
				$stmt->close();
				?>
			</table>
		</div>
	</body>
</html>