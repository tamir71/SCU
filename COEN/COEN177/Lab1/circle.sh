# Name: Tamir Enkhjargal
# Date: January 10, 2020
# Title: Lab 1 - Area of Circle
# Description: Posting logistics of user and home properties, as well as prompting user for length
#     and width to calculate the area of a circle

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
if [ $user = "tenkhjar" ]
then
    echo "Now you can proceed!"
else
    echo "Check who logged in!"
    exit 1
fi

# While loop to calculate area of circle(s)
response="Yes"
pi="3.1415"

while [ $response != "No" ]
do
    echo "Enter radius of circle (integer):"
    read radius
    area=`expr $radius \* $radius`
    echo "The area of the circle is $area*pi = `expr $area\*$pi | bc`"

    echo "Would you like to repeat for another circle [Yes/No]?"
    read response

done
