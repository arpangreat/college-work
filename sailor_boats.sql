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
	FOREIGN KEY (bid) REFERENCES Boats(bid)
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
select sname, age
from sailor
;

-- 2
select sname, rating
from sailor
where rating > 7
;

-- 3
select s.sname
from sailor s
join reserves r on s.sid = r.sid
where r.bid = 203
;

-- 4
select s.sname
from sailor s
join reserves r on s.sid = r.sid
join boats b on r.bid = b.bid
where b.color = 'Red'
;

-- 5
select s.sname
from sailor s
join reserves r on s.sid = r.sid
group by s.sname
having count(distinct r.bid) >= 1
;

-- OR (5)
select s.sname, group_concat(distinct b.color) as boat_colors
from sailor s
join reserves r on s.sid = r.sid
join boats b on r.bid = b.bid
group by s.sname
;

-- 6
select distinct b.color
from sailor s
join reserves r on s.sid = r.sid
join boats b on r.bid = b.bid
where s.sname = 'Sailor A'
;

-- 7
select s.sname, s.rating + 1 as new_rating
from sailor s
join reserves r1 on s.sid = r1.sid
join reserves r2 on s.sid = r2.sid and r1.day = r2.day
where r1.bid <> r2.bid
group by s.sid
having count(distinct r1.bid) >= 2
;

-- 8
select s.sname
from sailor s, boats b, reserves r
where s.sid = r.sid and r.bid = b.bid and (b.color = 'Red' or b.color = 'Green')

-- 9
select s.sname
from sailor s
where
    exists (
        select 1
        from reserves r1, boats b1
        where s.sid = r1.sid and r1.bid = b1.bid and b1.color = 'Red'
    )
    and exists (
        select 1
        from reserves r2, boats b2
        where s.sid = r2.sid and r2.bid = b2.bid and b2.color = 'Green'
    )

-- 10
select s.sid
from sailor s, boats b, reserves r
where s.sid = r.sid and r.bid = b.bid and b.color = 'Red'
except
select s2.sid
from sailor s2, boats b2, reserves r2
where s2.sid = r2.sid and r2.bid = b2.bid and b2.color = 'Green'

-- 12
select s.sname
from sailor s
where
    s.sid not in (
        select r.sid from reserves r join boats b on r.bid = b.bid where b.color = 'Red'
    )
;

-- 13
select s1.sname
from sailor s1
where s1.rating > (select s2.rating from sailor s2 where s2.sname = 'Sailor A')
;

-- 14
select s.sid
from sailor s
where s.rating >= all(select s2.rating from sailor s2)
;

-- 15
select s.age
from sailor s
where s.sname like 'S_%_%_%C'
;

-- 16
select s.sname
from sailor s
where
    not exists (
        select b.bid
        from boats b
        where
            not exists (
                select r.bid from reserves r where r.sid = s.sid and r.bid = b.bid
            )
    )
;

-- 16
select s.sname, s.age
from sailor s
where s.age = (select max(age) from sailor)
;

-- 17
select s.sname, s.age
from sailor s
where s.age > (select max(s2.age) from sailor s2 where s2.rating = 7)
;

-- 18
select s.rating, min(s.age) as minage
from sailor s
where s.age >= 18
group by s.rating
having (select count(*) from sailor s2 where s.rating = s2.rating) > 1
;

-- 19
select s.rating, min(s.age) as minage
from sailor s
where s.age >= 18
group by s.rating
having count(*) > 1
;

-- 20
-- step-1 creat a view temp
CREATE VIEW temp AS (
SELECT rating, AVG(age) AS avg_age FROM Sailor
GROUP BY rating);

-- step-2 query
select temp.rating, temp.avg_age
from temp
where temp.avg_age = (select min(temp.avg_age) from temp)
;

-- step-3 Drop view after usage
DROP VIEW temp;

