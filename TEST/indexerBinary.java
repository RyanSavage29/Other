import java.util.ArrayList;
import java.io.*;
import java.util.Scanner;



public class indexerBinary{
	public static void main(String[] args){
		int numFiles = 21;
		int freqLimit = 50;//minimum frequency needed to be put into output file
		String outputFileName = "nytIndex.txt";//name of output file
		String[] files = new String[numFiles];//check number of files
		int startYear = 1987;//name of first file
		int endYear = startYear + numFiles;
		int counter = 0;
		String filename = null;
		for(int i = startYear; i < endYear; ++i){//make sure the loop is right
			filename = "" + i;
			files[counter] = filename;
			counter++;
		}
		
		ArrayList<Token> tokenList = new ArrayList<Token>();
		String curLine = null;
		String curText = null;
		String curString = null;
		boolean tokenExists = false;
		int listCounter = 0;
		int tokenCounter = 0;
		int swapIndex = 0;
		int docTotal = 0;
		
		for(int i = 0; i < files.length; ++i){
			try{
				Scanner scan = new Scanner(new FileReader(files[i])); //use a list of words to ignore when going through data
				while(scan.hasNext()){
					++docTotal;
					curLine = scan.nextLine();
					curLine = scan.nextLine();
					curLine = scan.nextLine();
					Scanner liner = new Scanner(curLine).useDelimiter("[^\\w]+");
					while(liner.hasNext()){
						curString = liner.next();
						curString = curString.toLowerCase();
						tokenExists = false;
						int checkVal = tokenList.size()/2;
						int lowVal = 0;
						int highVal = tokenList.size() -1;
						
						if (tokenList.isEmpty())
						{
							tokenList.add(new Token(curString));
						}
						else
						{
							while(lowVal < highVal){//collects tokens from list
								checkVal = lowVal + ((highVal - lowVal) / 2);
								if(curString.compareTo(tokenList.get(checkVal).getToken()) == 0){//increases frequency counts of existing tokens
									tokenList.get(checkVal).iterateToken();
									tokenExists = true;
									break;
								}
								else if(curString.compareTo(tokenList.get(checkVal).getToken()) < 0){
									highVal = checkVal-1;
								}
								else if(curString.compareTo(tokenList.get(checkVal).getToken()) > 0){
									lowVal = checkVal+1;
								}
								else
								{
								}
							}
							
							checkVal = lowVal + ((highVal - lowVal) / 2);
							
							if (curString.compareTo(tokenList.get(checkVal).getToken()) == 0)
							{
								tokenList.get(checkVal).iterateToken();
							}
							else if (curString.compareTo(tokenList.get(checkVal).getToken()) < 0)
							{
								tokenList.add(checkVal, new Token(curString));
							}
							else if (curString.compareTo(tokenList.get(checkVal).getToken()) > 0)
							{
								if (checkVal == tokenList.size() - 1)
									tokenList.add(new Token(curString));
								else
									tokenList.add(checkVal + 1, new Token(curString));
							}
						}
					}
				}
				scan.close();
			}catch(IOException e){
					e.printStackTrace();
			}
		}
		try {//outputs tokens to an index file
			File outputFile = new File(outputFileName);
            FileOutputStream outStream = new FileOutputStream(outputFile);
            OutputStreamWriter outStreamWriter = new OutputStreamWriter(outStream);    
            Writer write = new BufferedWriter(outStreamWriter);
            for(int i = 0; i < tokenList.size(); ++i){
				if(tokenList.get(i).getFrequency() < freqLimit){
					continue;
				}
				write.write(tokenList.get(i).toString() + "\n");
			}
            write.close();
        } catch (IOException e) {
            System.err.println("Problem writing to the file.");
        }
		System.out.println("Number of Documents: " + docTotal); //outputs the number of total documents at the end
	}
}