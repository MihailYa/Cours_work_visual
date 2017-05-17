#pragma once

#define INF 10000
#define _CRT_SECURE_NO_WARNINGS
#define MAX_ITER 200

namespace coursework
{

	/**
	* Error codes:
	* 1 - problem with opening/closing file
	* 2 - Ford algorithm make too many iterations( > MAX_ITER)
	* 3 - Ford: can't found source or sink
	* 4 - Error with input information in form
	* 5 - Too many iterations in Humori Ford
	* 6 - Something wrong with mode parametr of Form_ class
	* 7 - Problem with queue
	* 8 - Problem with stack
	*/
	struct T_exception
	{
		short code;
		std::string text;
		std::string solution;
	};

}
