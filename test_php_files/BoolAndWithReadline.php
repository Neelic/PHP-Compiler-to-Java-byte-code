<?php

function left(){
	echo "Left!";
	
	return false;
}

function right(){
	echo "Right!";
	return true;
}

if (((boolean) readline()) && right()){
	echo "true!";
} else {
	echo "False!";
}