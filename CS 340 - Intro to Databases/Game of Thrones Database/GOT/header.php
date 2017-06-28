<?php
	include 'connectDB.php';
?>

<html>
    <head>
		<style>
			body {
				background-color: grey;
			}		

			ul {
				list-style-type: none;
				margin: 0;
				padding: 0;
				overflow: hidden;
				background-color: #333;
			}

			li {
				float: left;
				font-family: Arial, Helvetica, sans-serif;
				font-size: 20px;
			}

			li a, .dropbtn {
				display: inline-block;
				color: white;
				text-align: center;
				padding: 14px 16px;
				text-decoration: none;
			}

			li a:hover, .dropdown:hover .dropbtn {
				background-color: red;
			}

			li.dropdown {
				display: inline-block;
			}

			.dropdown-content {
				display: none;
				position: absolute;
				background-color: #f9f9f9;
				min-width: 160px;
				box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);
			}

			.dropdown-content a {
				color: black;
				padding: 12px 16px;
				text-decoration: none;
				display: block;
				text-align: left;
			}

			.dropdown-content a:hover {
				background-color: #f1f1f1
			}

			.dropdown:hover .dropdown-content {
				display: block;
			}
		</style>
	</head>
	
	<body>
		<ul class="nav">
		  <li><a href="index.php">Game of Thrones Database</a></li>
		  <li><a href="add.php">Add</a></li>
		  <li><a href="search.php">Search</a></li>
		  <li><a href="delete.php">Delete</a></li>
		  <li class="dropdown">
			<a href="#" class="dropbtn">View</a>
			<div class="dropdown-content">
			  <a href="showChar.php">Characters</a>
			  <a href="showCity.php">Cities</a>
			  <a href="showRegion.php">Regions</a>
			  <a href="showHouse.php">Houses</a>
			  <a href="showConn.php">Connection Types</a>
			  <a href="showTies.php">Ties</a>
		</ul>
	
		<div style="padding:20px;margin:30px;background-color:#F5F5F5;">
	</body>
</html>