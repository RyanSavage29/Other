********************************************************************************************************************
* Programmers: Nicholas Waszkiewicz Tyler Reich
* Professor: Dr. Tao
* Final Project
* getData.java, indexerBinary.java, Token.java, VectorOutput.java, PageVector.java, NYTCG2.pde
* Ranks articles in the NYT corpus in terms of political and entertainment content, and sorted by date
********************************************************************************************************************

***EXPLANATION OF CODE***
This project utilizes the New York Times corpus to create a graphical representation of all the articles within using a vector model.
The vectors utilized in the project are an entertainment vector, political vector, and a date of posting vector. While the date vector is given
for each article by the corpus, the political and entertainment vector are calculated using a political and entertainment word index we've created.
In this index, each line contains a token, an IDF value, and a char character representation whether it is politcal or entertainment.
From here, it scans through all the articles within the corpus and adds the IDF value to that articles vector each time that word is found.
This creates a TF-IDF vector for the article for both entertainment and political content. At the end, these two values are normalized and output
to a vector index along with the article's title and its date vector. Finally, Processing is used to give a visual representation of the data by reading
in all the article vectors.

***FUNCTIONS***
*getData.java*
It takes a New York Time Corpus xml file and outputs the title, date, and body text of that file
To run, open a command line window, navigate to the directory with getData.java in it, and run

	java getData <filename>
	
where <filename> is the name of the NYTC file you want to extract data from. The NYTC file must be in the same directory.
The result is a text file with the name <filename>output.txt. Each document takes up three lines, using for format

title
date
body text

All html tags are striped from the body text during extraction.


*indexerBinary.java*
This program goes through the files created by getData.java to create a complete index of all tokens within the corpus in alphabetical order and
output them into an output file in the format

token collectionFrequency IDFvalue

Terms below a certain collection frequency can be ignored when writing to the output file. By default, this is set to 50.

To run this file, the files to be read must be in the directory and named by year. (Ex: 1987) The program reads files incrementally by year. The number
of files must be specified as well. It runs simply via

	java indexerBinary


*VectorOutput.java*
This part utilizes the index that is handmade from the complete index created by indexerBinary.java. The format of that index is

token collectionFrequency IDFvalue typeChar

This program takes the index of political and entertainment words and compares it against the body text of each article. It adds the IDF value of
index terms that appear in the text to that article's vector for the specified type (political or entertainment). This creates a TF-IDF value for that article
since it takes the term frequency * IDF and gets the TF-IDF for each term and adds it into the corresponding vector. Once all arcticles are processed,
vectors are normalized and output to files in the format

TITLE___politicalVector___entertainmentVector___dateVector

To run this file, the files to be read must be in the directory and named by year. (Ex: 1987) The program reads files incrementally by year. The number
of files must be specified as well. Finally, the index must be in the directory as well, with the name specified. By default, the name is "PolEntIDF.txt"
It runs simply via

	java VectorOutput
	

*Token.java*
This class file is utilized in both indexerBinary.java and VectorOutput.java. It is used for token objects and collects the collection frequency,
document frequency, whether it is a political or entertainment word, the name of the token itself, and has a function for calculating the IDF once
all documents have been accounted for.


*PageVector.java*
This class file is used by VectorOutput.java to hold all article objects. It contains the title of the article, and its three vectors: Entertainment, politics,
and date. While date is calculated upon creation of the object, entertainment and politics are added up as the article body text is processed. It has a
normalization function that normalizes the political and entertainment vectors for once the article has been fully processed.


*NYTCG2.pde*
This is a Processing 3 file and so Processing 3 must be installed on your system to run it. However, you can still see the contents by viewing it within a
regular text editor.

This script takes requires that a documents containing document vectors be in the same directory.
For each line, it reads in the title, political score, entertainment score, and date, storing each in a separate arraylist. The data cannot be output into the
graphical output at this time, as first must find the largest values for the score and the largest and smallest values for the date. These are used for scaling
purposes when creating the graphical output.

When all the data is read in, it is then output into the graphical window. This process may take a about a minute to a minute and a half on a decent machine. 
The result is an outout graphing the vectors on a 3-dimentional plane, with dimentions for political score, entertainment score, and date.


***LIMITATIONS***
Although the graph is 3-dimensional, it is only able to be displayed as a 2-dimensional figure.

While the index of political and entertainment words are of considerable quality, other words which fit a political or entertainment background may
have been missed due to personal error.

Requires a few separate steps in order to get the end result.


***FEATURES***
All word indexes are in alphabetical order so that a binary search method can be used to find terms, lowering the time complexity to find a term to O(logn).

Index of over 1,800 poltical and entertainment words were handpicked to ensure high quality results.

Creates a complete index of all terms within the corpus along with their collection frequency and document frequency as a side product.

Graphs all articles in a uniform manner in terms of date along a 3-dimensional graph.

This project can be utilized for any set of files in a format similar to the NYT corpus.

It can utilize any index provided by the user for comparison and vector usage.

