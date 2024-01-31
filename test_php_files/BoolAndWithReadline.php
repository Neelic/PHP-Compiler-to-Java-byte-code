<?php

function left(){
	echo "Left!\n";
	
	return false;
}

function right(){
	echo "Right!\n";
	return true;
}

if ( readline()< 5 || right()){
	echo "true!\n";
} else {
	echo "False!\n";
}