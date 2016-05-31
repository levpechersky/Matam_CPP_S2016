/*
 * Apartment.cpp
 *
 *  Created on: May 29, 2016
 */

#include "Apartment.h"
#include <algorithm>

//************************************************************************
//**********************Static functions of the Class*********************
//************************************************************************
Apartment:: SquareType** Apartment::allocateBoard(int length, int width){
	SquareType**layout=new SquareType*[length];
	for (int i = 0; i < length; i++){
		layout[i] = new SquareType[width];
	}
	return layout;
}

Apartment:: SquareType** Apartment::copyBoard
          (Apartment::SquareType**squares, int length, int width){
	SquareType**layout=allocateBoard(length,width);
	for (int i = 0; i < length; i++){
		for(int j=0; j<width; j++){
			layout[i][j]=squares[i][j];
		}
	}
	return layout;
}

void Apartment::destroyBoard(Apartment::SquareType**squares, int length){
	for (int i = 0; i < length; i++){
	   delete[] squares[i];
	}
	delete[] squares;
}

//************************************************************************
//*******************************Methods**********************************
//************************************************************************
int Apartment::getPrice() const{
	return price;
}
int Apartment::getLength() const{
	return length;
}
int Apartment::getWidth() const{
	return width;
}
int Apartment::getTotalArea() const{
	int counter=0;
	for (int i = 0; i < length; i++){
		for(int j=0; j<width; j++){
			if(layout[i][j]==EMPTY) counter++;
		}
	}
	return counter;
}
//************************************************************************
//*******************************Operators********************************
//************************************************************************
Apartment& Apartment::operator= (const Apartment& apartment){
	if(this==&apartment) return *this;
	destroyBoard(apartment.layout,apartment.length);
	length=apartment.length;
	width=apartment.width;
	price=apartment.price;
	layout=copyBoard(apartment.layout,length,width);
	return *this;
}
//************************************************************************
//***************************C'tors, D'tor********************************
//************************************************************************
Apartment::Apartment(SquareType** squares, int length, int width, int price){
	if(!(squares && length>0 && width>0 && price>=0)) throw IllegalArgException();
	this->length=length;
	this->width=width;
	this->price=price;
	layout=copyBoard(squares,length,width);
}
Apartment::Apartment(const Apartment& apartment) :
	length(apartment.length),
	width(apartment.width),
	price(apartment.price),
	layout(copyBoard(apartment.layout,length,width)){
}
Apartment::~Apartment() {
	destroyBoard(layout,length);
}
