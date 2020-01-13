# Name: Tamir Enkhjargal
# Date: January 10, 2020
# Title: Lab 1 - First Code, no changes
# Description: Posting logistics of user and home properties, as well as prompting user for length
#     and width to calculate the area of a rectangle

#!/bin/sh

# Printing logistics and process information
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$

# Check who is running this script
user=`whoami`

# Check how many logged in
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."

# If user is [me], then continue to rest of program
if [ $user = "salagtash" ]
then
    echo "Now you can proceed!"
else
    echo "Check who logged in!"
    exit 1
fi

# While loop to calculate area of rectangle(s)
response="Yes"
while [ $response != "No" ]
do
    echo "Enter height of rectangle:"
    read height
    echo "Enter width of rectangle:"
    read width
    area=`expr $height \* $width`
    echo "The area of the rectangle is $area"

    echo "Would you like to repeat for another rectangle [Yes/No]?"
    read response

done
