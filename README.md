#Is The Floor Feeding?
An indicator for the ITP floor to show whether or not there is active feeding happening in the lounge area. 

#Design Specs
##FOOD
###POST
/food/yes Change the status of food
/food/no
###GET 
/food/ Return the status of food
##FOOD AMOUNT
###POST 
/amount/4 (full) Change the amount of food
/amount/3
/amount/2
/amount/1 (empty)
###GET
/amount/    Return the amount of food
##FOODTYPE
###POST
/type/sweet Change the type of food
/type/savory
/type/neutral
###GET
/type/ Return the type of food

##INTERFACE:
###INPUT
The lever shown above.
###OUTPUT
Webpage that displays if food is available and if so, how much and what type.
A physical light for the Shop and the Lobby that alerts if food is available

- http://www.itp.danmelancon.com/uncategorized/a-simple-rest-api-to-alert-for-food/