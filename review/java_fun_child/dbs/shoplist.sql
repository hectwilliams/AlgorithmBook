DROP DATABASE IF EXISTS shop;
DROP TABLE IF EXISTS properties;
DROP TABLE IF EXISTS shoplist; 

CREATE DATABASE shop; 

CREATE TABLE shop.shoplist (
    id INTEGER NOT NULL AUTO_INCREMENT ,
    item VARCHAR(255),
    quantity INTEGER,
    
    PRIMARY KEY(id)
);

ALTER TABLE shop.shoplist 
ADD UNIQUE(item) ;

CREATE TABLE shop.properties  (
    id INTEGER NOT NULL AUTO_INCREMENT,
    item_name VARCHAR(255),
    location VARCHAR(255)  DEFAULT 'San Francisco',
    
    PRIMARY KEY(id)
);

ALTER TABLE shop.properties
ADD FOREIGN KEY (item_name) REFERENCES shop.shoplist(item);
