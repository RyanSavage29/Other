import java.util.ArrayList;
import java.io.*;
import java.util.Scanner;


public class VectorOutput{
	public static void main(String[] args){
		int numFiles = 21;//number of files to be read in
		String indexName = "PolEntIDF.txt";//name of comparison index
		String outputFileName = "docVectors.txt";//name of output file
		int startYear = 1987;//name of first file
		int endYear = startYear + numFiles;
		String[] files = new String[numFiles];
		int counter = 0;
		String filename = null;
		for(int i = startYear; i < endYear; ++i){//reads in all file names
			filename = "" + i;
			files[counter] = filename;
			counter++;
		}
		String indexToken = null;
		String indexFrequency = null;
		int numFrequency = 0;
		String indexIDF = null;
		double dubIDF = 0.0;
		String indexType = null;
		ArrayList<Token> tokenList = new ArrayList<Token>();
		try{//scans the index of pol-ent words into an array
			Scanner token = new Scanner(new FileReader(indexName));
			while(token.hasNext()){
				indexToken = token.next();
				indexFrequency = token.next();
				numFrequency = Integer.parseInt(indexFrequency);
				indexIDF = token.next();
				dubIDF = Double.parseDouble(indexIDF);
				indexType = token.next();
				tokenList.add(new Token(indexToken, numFrequency, dubIDF, indexType));
			}
			token.close();
		}catch (IOException e) {
            System.err.println("Problem writing to the file.");
        }
		
		String curTitle = null;
		String curDate = null;
		String curLine = null;
		String curText = null;
		String curString = null;
		boolean tokenExists = false;
		int docNumber = -1;
		ArrayList<PageVector> vectorList = new ArrayList<PageVector>();
		
		for(int i = 0; i < files.length; ++i){//creates vector objects for each article and adds up their vectors
			try{
				Scanner scan = new Scanner(new FileReader(files[i])); //use a list of words to ignore when going through data
				while(scan.hasNext()){
					docNumber++;
					curTitle = scan.nextLine();
					curDate = scan.nextLine();
					vectorList.add(new PageVector(curTitle, curDate)); //creates the current page being scanned
					curLine = scan.nextLine();
					Scanner liner = new Scanner(curLine).useDelimiter("[^\\w]+");
					while(liner.hasNext()){
						curString = liner.next();
						curString = curString.toLowerCase();
						tokenExists = false;
						int checkVal = tokenList.size()/2;
						int lowVal = 0;
						int highVal = tokenList.size() -1;
						
						while(lowVal < highVal){//collects tokens from list
							checkVal = lowVal + ((highVal - lowVal) / 2);
							if(curString.compareTo(tokenList.get(checkVal).getToken()) == 0){//increases frequency counts of existing tokens
								vectorList.get(docNumber).increaseVector(tokenList.get(checkVal).getType(), tokenList.get(checkVal).getIDF());
								tokenExists = true;
								break;
							}
							else if(curString.compareTo(tokenList.get(checkVal).getToken()) < 0){
								highVal = checkVal-1;
							}
							else if(curString.compareTo(tokenList.get(checkVal).getToken()) > 0){
								lowVal = checkVal+1;
							}
						}
							
						checkVal = lowVal + ((highVal - lowVal) / 2);
						
						if (curString.compareTo(tokenList.get(checkVal).getToken()) == 0)
						{
							vectorList.get(docNumber).increaseVector(tokenList.get(checkVal).getType(), tokenList.get(checkVal).getIDF());
						}
					}
				}
			scan.close();
			}catch(IOException e){
					e.printStackTrace();
			}
		}
		try {
			File outputFile = new File(outputFileName);
            FileOutputStream outStream = new FileOutputStream(outputFile);
            OutputStreamWriter outStreamWriter = new OutputStreamWriter(outStream);    
            Writer write = new BufferedWriter(outStreamWriter);
            for(int i = 0; i < vectorList.size(); ++i){
				write.write(vectorList.get(i).toString() + "\n");
			}
            write.close();
        } catch (IOException e) {
            System.err.println("Problem writing to the file.");
        }
	}
}