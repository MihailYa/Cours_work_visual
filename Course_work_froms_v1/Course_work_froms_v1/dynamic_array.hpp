#pragma once
#include "stdafx.hpp"
#include "globals.hpp"

namespace coursework
{

	/**
	* Create dynamic array n x m
	* @param n rows
	* @param m cols
	* @return pointer on array
	*/
	template<typename T>
	T** create_array(int n, int m)
	{
		T **temp;
		temp = new T*[n];
		for (int i = 0; i < n; i++)
			temp[i] = new T[m];

		return temp;
	}

	/**
	* Delete dynamic array n x m
	* @param arr pointer on array
	* @param n rows
	*/
	template<typename T>
	void delete_array(T** arr, int n)
	{
		if (arr == nullptr)
		{
			T_exception e;
			e.code = 10;
			e.text = "Не можливо звільнити пам'ять.";
			throw(e);
		}

		for (int i = 0; i < n; i++)
			delete[] arr[i];
		if (arr == nullptr)
		{
			T_exception e;
			e.code = 10;
			e.text = "Не можливо звільнити пам'ять.";
			throw(e);
		}
		delete[] arr;
		arr = nullptr;
	}
}
