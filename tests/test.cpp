#include "threadPool.h"
#include "memPool.h"
#include "conPool.h"
#include "http.h"
#include <iostream>

int main(int argc, const char** argv) {
	MemPool<HttpConn> memPool(2, 5);
	ThreadPool<HttpConn> threadPool(4);

	for (int i = 0; i < 10; ++i) {
		HttpConn* con = new (&memPool) HttpConn(&memPool);
		threadPool.addTask(*con);
	}

	ConnPool connPool("localhost", "root", "", "mydb", 0, 5);
	MYSQL* conn1 = connPool.getConn();
	MYSQL* conn2 = connPool.getConn();
	MYSQL* conn3 = connPool.getConn();
	MYSQL* conn4 = connPool.getConn();
	MYSQL* conn5 = connPool.getConn();

	if (mysql_query(conn1, "CREATE TABLE mytable(Id INT PRIMARY KEY AUTO_INCREMENT, first_name VARCHAR(14), last_name VARCHAR(14), hire_date DATE)"))
	{
		std::cout << "Create table to database failed : " << mysql_error(conn1) << std::endl;
	}


	if (mysql_query(conn2, "INSERT INTO mytable(first_name, last_name, hire_date) VALUES('John', 'Doe', '2006-06-06')"))
	{
		std::cout << "Error writing to database: " << mysql_error(conn2) << std::endl;
		std::cout << "FAILED" << std::endl;
		return -1;
	}

	if (mysql_query(conn3, "SELECT first_name, last_name FROM mytable"))
	{
		std::cout << "Error query to database: " << mysql_error(conn3) << std::endl;
		std::cout << "FAILED" << std::endl;
		return -1;
	}

	MYSQL_RES* result = mysql_store_result(conn3);

	if (result == NULL)
	{
		std::cout << "Bad results: " << mysql_error(conn3) << std::endl;
		std::cout << "FAILED" << std::endl;
		return -1;
	}

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;

	while ((row = mysql_fetch_row(result)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			std::cout << row[i] << std::endl;
		}
	}

	mysql_free_result(result);

	connPool.releaseConn(conn1);
	connPool.releaseConn(conn2);
	connPool.releaseConn(conn3);
	
	std::cout << "PASSED" << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(2));
	return 0;
}