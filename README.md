# ButtonArray
## Overview
ButtonArray is an Arduino library/class which is used to measure an array of buttons. It uses an update-function to measure the buttons and a void function with an integer as parameter can be given to the object, which will be executed when a pressed button is found in the update-function.

New, saves the results in an uint8_t array. You can get the pointer to that using the getResultArray function.
