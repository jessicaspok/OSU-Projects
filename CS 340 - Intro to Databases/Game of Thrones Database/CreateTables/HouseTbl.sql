DROP TABLE IF EXISTS `House`;

-- Create House Table
CREATE TABLE House (
	id INT NOT NULL AUTO_INCREMENT,
	Name VARCHAR(255) NOT NULL UNIQUE,
	Motto VARCHAR(255),
	PRIMARY KEY (id)
) ENGINE=InnoDB;