//Preston Zimmerman

- To the best of my knowledge this program works perfectly. The cpp file is basically just ported from lab8 with minor
changes. I did improve a few things such as when you search for a word that is not in the index it gives a "Word not 
found error" rather than just repeating the options imediatly. I also added a cin failstate check when asking for input
incase you write letters or something while its looking for an int. This way it doesnt infinite loop anymore and it will clear the cin buffer and ask for another input. 

- I used the AvlTree.h file that was uploaded to piaza by someone last weekend. I have seen some people who are using a slightly different .h file from an updated text book that changes the insert function slightly. In the version I used
there is not balance function instead while inserting it handles the balancing. This leads to more key comparisons in
the insert function. In the updated .h file that uses a balance function it looks at the height rather than comparing 
keys. 
