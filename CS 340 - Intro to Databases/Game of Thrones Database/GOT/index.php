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
			h1, h2 {
				text-align: center;
			}
			
			p {
				font-size: 25px;
				text-align: center;
			}
			
			img {
				display: block;
				margin: auto;
				width: 50%;
				border: 3px solid black;
			}
		</style>
	</head>
	
	<body>
		<div>
			<h1> CS 340 - Game of Thrones Database </h1>
			<h2> by Jessica Spokoyny </h2>
			</br>
			<p>This is a database of the Characters and their relationships from the TV show, Game of Thrones.</p>
			<p>Please use the menu above to Add to, Search, Delete from, or View the database information</p>
			</br></br>
			<img src="http://cdn-static.denofgeek.com/sites/denofgeek/files/styles/article_main_wide_image/public/game_of_thrones_logo_9_12_11_0.jpg" alt="got" width=700 height=400">
			</br>
		</div>
	</body>
</html>