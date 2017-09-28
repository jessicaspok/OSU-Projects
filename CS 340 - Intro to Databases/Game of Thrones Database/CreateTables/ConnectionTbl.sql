DROP TABLE IF EXISTS `Connection_Type`;

-- Create Connection Type Table
CREATE TABLE Connection_Type (
	id INT NOT NULL AUTO_INCREMENT,
	Description VARCHAR(255) NOT NULL UNIQUE,
	PRIMARY KEY(id)
) ENGINE=InnoDB;