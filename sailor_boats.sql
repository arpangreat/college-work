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
	(104, 'Sailor D', 18, 5);

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

SELECT sname,age from Sailor;

SELECT sname, rating FROM Sailor WHERE rating > 7;

SELECT s.sname FROM Sailor s JOIN Reserves r ON s.sid = r.sid WHERE r.bid = 203;

SELECT s.sname FROM Sailor s JOIN Reserves r ON s.sid = r.sid JOIN Boats b ON r.bid = b.bid WHERE b.color = 'Red';

SELECT s.sname FROM Sailor s JOIN Reserves r ON s.sid = r.sid GROUP BY s.sname HAVING COUNT(DISTINCT r.bid) >= 1;

SELECT s.sname, GROUP_CONCAT(DISTINCT b.color) AS boat_colors FROM Sailor s JOIN Reserves r ON s.sid = r.sid JOIN Boats b ON r.bid = b.bid
GROUP BY s.sname;

SELECT DISTINCT b.color FROM Sailor s JOIN Reserves r ON s.sid = r.sid JOIN Boats b ON r.bid = b.bid WHERE s.sname = 'Sailor A';

SELECT s.sname, s.rating + 1 AS new_rating
FROM Sailor s
JOIN Reserves r1 ON s.sid = r1.sid
JOIN Reserves r2 ON s.sid = r2.sid AND r1.day = r2.day
WHERE r1.bid <> r2.bid
GROUP BY s.sid
HAVING COUNT(DISTINCT r1.bid) >= 2;

SELECT s.sname
FROM Sailor s, Boats b, Reserves r
WHERE s.sid=r.sid AND r.bid=b.bid
AND (b.color='Red' OR b.color='Green')

SELECT s.sname
FROM Sailor s
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
)

SELECT s.sid
FROM Sailor s, Boats b, Reserves r
WHERE s.sid = r.sid AND r.bid = b.bid AND b.color = 'Red'
EXCEPT
SELECT s2.sid
FROM Sailor s2, Boats b2, Reserves r2
WHERE s2.sid = r2.sid AND r2.bid = b2.bid AND
b2.color = 'Green'

SELECT s.sname
FROM Sailor s
WHERE s.sid NOT IN (
	SELECT r.sid
	FROM Reserves r
	JOIN Boats b ON r.bid = b.bid
	WHERE b.color = 'Red'
);

SELECT s1.sname
FROM Sailor s1
WHERE s1.rating > (
	SELECT s2.rating
	FROM Sailor s2
	WHERE s2.sname = 'Sailor A'
);

SELECT s.sid
FROM Sailor s
WHERE s.rating >= ALL (
	SELECT s2.rating
	FROM Sailor s2
);

SELECT s.age
FROM Sailor s
WHERE s.sname LIKE 'S_%_%_%C';

SELECT s.sname
FROM Sailor s 
WHERE NOT EXISTS (
	SELECT b.bid
	FROM Boats b
	WHERE NOT EXISTS (
		SELECT r.bid
		FROM Reserves r
		WHERE r.sid = s.sid AND r.bid = b.bid
	)
);
