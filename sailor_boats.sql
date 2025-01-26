CREATE TABLE Sailors (
   sid INT(5) PRIMARY KEY,
   sname VARCHAR(50) NOT NULL,
   age FLOAT(5,2) NOT NULL,
   rating INT(3) NOT NULL
);

CREATE TABLE Boats (
	bid INT PRIMARY KEY,
	bname VARCHAR(50) NOT NULL,
	color VARCHAR(50) NOT NULL
);

create table empl ( 
  eno int(3) NOT NULL PRIMARY KEY,
  ename varchar(50) NOT NULL,
  job_type varchar(50) NOT NULL,
  manager char(5),
  hire_date DATE NOT NULL,
  dno int,
  commission decimal(10,2),
  salary decimal(7,2) NOT NULL,
  FOREIGN KEY (dno) REFERENCES department(dno),
  FOREIGN KEY (manager) REFERENCES empl(eno)
) ENGINE=InnoDB;

create table department (
  dno int NOT NULL PRIMARY KEY,
  dname varchar(50) DEFAULT NULL,
  location varchar(50) DEFAULT 'Delhi',
) ENGINE=InnoDB;


CREATE TABLE Reserves (
	sid INT,
	bid INT,
	day DATE NOT NULL,
	PRIMARY KEY (sid, bid, day),
	FOREIGN KEY (sid) REFERENCES Sailors(sid),
	FOREIGN KEY (bid) REFERENCES Boats(bid),
);

INSERT INTO Sailors (sid, sname, age, rating) VALUES
	(101, 'Sailor A', 21, 7),
	(102, 'Sailor B', 17, 9),
	(103, 'Sailor C', 24, 2),
	(104, 'Sailor D', 18, 5),
	(105, 'Sailor E', 25, 7),
	(106, 'Sailor F', 24, 2),
	(107, 'Sailor G', 22, 9),
	(108, 'Sailor H', 20, 5);

INSERT INTO Boats (bid, bname, color) VALUES
	(201, 'Titanic', 'Red'),
	(202, 'Atalanta', 'Green'),
	(203, 'Marines', 'Blue'),
	(204, 'Unicorn', 'Yellow');

INSERT INTO Reserves (sid, bid, day) VALUES
	(101, 201, '2024-06-01'),
	(102, 202, '2024-06-06'),
	(103, 203, '2024-06-03'),
	(104, 204, '2024-06-07'),
	(101, 204, '2024-06-08'),
	(103, 201, '2024-06-10'),
	(104, 201, '2024-06-17'),
	(102, 203, '2024-06-18'),
	(101, 202, '2024-06-01'),
	(103, 204, '2024-06-10'),
	(104, 203, '2024-06-17'),
	(102, 201, '2024-06-06');

-- 1
SELECT sname,age from Sailors;

-- 2
SELECT sname, rating FROM Sailors WHERE rating > 7;

-- 3
SELECT s.sname FROM Sailors s JOIN Reserves r ON s.sid = r.sid WHERE r.bid = 203;

-- 4
SELECT s.sname FROM Sailors s JOIN Reserves r ON s.sid = r.sid JOIN Boats b ON r.bid = b.bid WHERE b.color = 'Red';

-- 5
SELECT s.sname FROM Sailors s JOIN Reserves r ON s.sid = r.sid GROUP BY s.sname HAVING COUNT(DISTINCT r.bid) >= 1;

-- OR (5)
SELECT s.sname, GROUP_CONCAT(DISTINCT b.color) AS boat_colors FROM Sailors s JOIN Reserves r ON s.sid = r.sid JOIN Boats b ON r.bid = b.bid
GROUP BY s.sname;

-- 6
SELECT DISTINCT b.color FROM Sailors s JOIN Reserves r ON s.sid = r.sid JOIN Boats b ON r.bid = b.bid WHERE s.sname = 'Sailors A';

-- 7
SELECT s.sname, s.rating + 1 AS new_rating
FROM Sailors s
JOIN Reserves r1 ON s.sid = r1.sid
JOIN Reserves r2 ON s.sid = r2.sid AND r1.day = r2.day
WHERE r1.bid <> r2.bid
GROUP BY s.sid
HAVING COUNT(DISTINCT r1.bid) >= 2;

-- 8
SELECT s.sname
FROM Sailors s, Boats b, Reserves r
WHERE s.sid=r.sid AND r.bid=b.bid
AND (b.color='Red' OR b.color='Green');

-- 9
SELECT s.sname
FROM Sailors s
WHERE EXISTS (
	SELECT 1
	FROM Reserves r1, Boats b1
	WHERE s.sid = r1.sid AND r1.bid = b1.bid AND
	b1.color='Red'
)
AND EXISTS (
	SELECT 1
	FROM Reserves r2, Boats b2
	WHERE s.sid = r2.sid AND r2.bid = b2.bid AND
	b2.color = 'Green'
);

-- 10
SELECT s.sid
FROM Sailors s, Boats b, Reserves r
WHERE s.sid = r.sid AND r.bid = b.bid AND b.color = 'Red'
EXCEPT
SELECT s2.sid
FROM Sailors s2, Boats b2, Reserves r2
WHERE s2.sid = r2.sid AND r2.bid = b2.bid AND
b2.color = 'Green';

-- 11
SELECT s.sname
FROM Sailors s
WHERE s.sid NOT IN (
	SELECT r.sid
	FROM Reserves r
	JOIN Boats b ON r.bid = b.bid
	WHERE b.color = 'Red'
);

-- 12
SELECT s1.sname
FROM Sailors s1
WHERE s1.rating > (
	SELECT s2.rating
	FROM Sailors s2
	WHERE s2.sname = 'Sailor A'
);

-- 13
SELECT s.sid
FROM Sailors s
WHERE s.rating >= ALL (
	SELECT s2.rating
	FROM Sailors s2
);

-- 14
SELECT s.age
FROM Sailors s
WHERE s.sname LIKE 'S_%_%_%C';

-- 15
SELECT s.sname
FROM Sailors s 
WHERE NOT EXISTS (
	SELECT b.bid
	FROM Boats b
	WHERE NOT EXISTS (
		SELECT r.bid
		FROM Reserves r
		WHERE r.sid = s.sid AND r.bid = b.bid
	)
);

-- 16
SELECT s.sname,s.age
FROM Sailors s
WHERE s.age = (SELECT MAX(age) FROM Sailors);

-- 17
SELECT s.sname, s.age
FROM Sailors s
WHERE s.age > (
SELECT MAX(s2.age)
FROM Sailors s2
WHERE s2.rating = 7
);

-- 18
SELECT s.rating, MIN(s.age) as minage
FROM Sailors s
WHERE s.age>=18
GROUP BY s.rating
HAVING (
SELECT COUNT(*)
FROM Sailors s2
WHERE s.rating=s2.rating)>1;

-- 19
SELECT s.rating, MIN(s.age) AS minage
FROM Sailors s
WHERE s.age >= 18
GROUP BY s.rating
HAVING COUNT(*) > 1;

-- 20
CREATE VIEW temp AS (
SELECT rating, AVG(age) AS avg_age FROM Sailors
GROUP BY rating);

SELECT temp.rating, temp.avg_age FROM temp WHERE temp.avg_age=(SELECT MIN(temp.avg_age) FROM temp);
