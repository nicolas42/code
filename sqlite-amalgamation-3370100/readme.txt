

Getting started 
-------------------

1. Use make 
2. run the interpreter (a.out)
3. copy/past sample.sql into the terminal
4. sample.png shows the fields that are common to the different tables
5. Try some structured queries.






SQLite 
----------------

SQLite is the most used database engine in the world apparently.
https://sqlite.org/download.html

https://www.sqlitetutorial.net/sqlite-commands/


Example database
https://www.mikedane.com/databases/sql/creating-company-database/

Online SQL interpreter https://www.w3schools.com/sql/



Misc 
----------


SELECT * FROM   ORDERS INNER JOIN CUSTOMER   ON ORDERS.CUST_CODE = CUSTOMER.CUST_CODE;



Join combines two tables
------------------------------------
SELECT *
FROM OrderDetails
INNER JOIN Orders
ON Orders.OrderID = OrderDetails.OrderID;



