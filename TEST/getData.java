/*
* written by Tyler Reich
* last modified 4/30/17
* takes in a file from the New York Times (the ones titled "part-0", which should be renamed to something else) and outputs the title, date and body text in a text file
* for each document, three lines in the output file are created, in this format:
* title
* date
* body text
*/

import java.util.ArrayList;
import java.io.*;
import java.util.*;
import java.util.Set;
import java.util.Scanner;
import java.util.Collections;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class getData
{
	public static void main(String[] args)
	{	
		String fileName = args[0];
		System.out.println(args[0]);
		Scanner input;
		Pattern findTitle = Pattern.compile("<title>(.*)<\\/title>");  //pattern for detecting titles
		Pattern findDate = Pattern.compile("<pubdata date.publication=\"([0-9A-Z]*)\"");  //pattern for detecting date fields
		Pattern startBody = Pattern.compile("<block class=\"full_text\">");  //pattern for detecting the beginning of body text
		Pattern endBody = Pattern.compile("<\\/block>"); //pattern for detecting the end of body text
		Pattern start = Pattern.compile("<nitf");           //pattern for detecting the beginning of a document
		Pattern stop = Pattern.compile("<\\/nitf>");  //pattern for detecting the end of a document
		Matcher finder;
		String bodyText = "";
		String title = "";
		String date = "";
		boolean readIn = false;
		boolean startDoc = false;
		
		try
		{
			//initialize variables not already initalized
			File newFile = new File(fileName);
			input = new Scanner(newFile);
			
			File outputFile = new File("output" + fileName + ".txt");
			FileOutputStream outStream = new FileOutputStream(outputFile);
			OutputStreamWriter outStreamWriter = new OutputStreamWriter(outStream);    
			Writer write = new BufferedWriter(outStreamWriter);
			
			//read through file
			while (input.hasNextLine()) //for each line in file
			{
				String temp = input.nextLine();
				Matcher findStart = start.matcher(temp);
				Matcher findStop = stop.matcher(temp);	
				Matcher isDate = findDate.matcher(temp);
				Matcher isTitle = findTitle.matcher(temp);
				Matcher findStartBody = startBody.matcher(temp);
				Matcher findEndBody = endBody.matcher(temp);
				
				//if the beginning of a document is found
				if (findStart.find())  
				{
					startDoc = true;
					title = "";
					date = "";
					bodyText = "";
					readIn = false;
					//System.out.println("Start");
				}
				
				//if a title is found
				if(startDoc && isTitle.find())
					title = isTitle.group(1);
				
				//if a date is found
				if(startDoc && isDate.find())
					date = isDate.group(1);
				
				//if the beginning of body text is found
				if(startDoc && findStartBody.find())
					readIn = true;
				
				//when reading bodytext, store each line
				if (startDoc && readIn)
				{
					temp = temp.replaceAll("<.*?>|\\s+"," "); //weed out any html tags
					bodyText += temp;
				}
				
				//stop reading in lines when the end of the body is found
				if (findEndBody.find())
					readIn = false;
	
				//when the end of a document is found, create an entry for it in the output
				if (findStop.find() && startDoc)
				{
					startDoc = false;
					write.write(title + "\n");
					write.write(date + "\n");
					write.write(bodyText + "\n");
				}
			}
			write.close();
			input.close();
		}
		catch(FileNotFoundException e)
		{
			e.printStackTrace();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
}